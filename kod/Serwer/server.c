/*#include <sys/types.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <signal.h>
#include <time.h>*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <pthread.h>
#include <string.h>
#include "game_logic.h"

#define SERVER_PORT 1234
#define QUEUE_SIZE 5

struct players
{
    int addr1, addr2;
};

void player_swap(struct game *G, struct players *P)
{ //zmiana aktywnego gracza
    int Temp = P->addr1;
    P->addr1 = P->addr2;
    P->addr2 = Temp;
    if (G->Player_symbol == 'W')
        G->Player_symbol = 'B';
    else
        G->Player_symbol = 'W';
}

int game_send(int sock, struct game *G, char S)
{

    int W, i, j, x = 0;
    char buff[130];

    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < 8; i++)
        {
            buff[x] = G->board[0][i][j];
            buff[x + 64] = G->board[1][i][j];
            x++;
        }
    }
    buff[128] = G->Player_symbol;
    buff[129] = S;

    W = write(sock, buff, sizeof(buff));

    return W;
}

void *ThreadBehavior(void *data)
{
    pthread_detach(pthread_self());
    struct players *P = (struct players *)data;

    int x, y, A, K1, K2, CM = 1;

    char buff[3];

    struct game *G;
    G = malloc(sizeof(struct game));
    new_game(G);

    printf("nowa gra\n");

    K1 = game_send(P->addr1, G, 'W');
    K2 = game_send(P->addr2, G, 'B');

    while ((CM & 1) && ((K1 > 0) && (K2 > 0)))
    {
        K2 = game_send(P->addr2, G, 'S');
        if (!(K2 > 0))
            break;
        K1 = game_send(P->addr1, G, 'S');
        if (!(K1 > 0))
            break;
        do
        {
            K1 = read(P->addr1, buff, sizeof(buff));
            if (!(K1 > 0))
                break;
            sscanf(buff, "%d-%d", &x, &y);
            A = action(x, y, G);
            if (A == 0)
            {
                find_action(x, y, G);
                game_send(P->addr1, G, '0');
            }
            if (A == 3)
            {
                game_send(P->addr1, G, 'C');
                do
                {
                    K1 = read(P->addr1, buff, sizeof(buff));
                    if (!(K1 > 0))
                        break;
                } while (buff[0] != 'S');
                change(G, x, y, buff[2]);
            }

        } while (A == 0);
        if (K1 > 0)
        {
            player_swap(G, P);
            CM = checkmate(G);
        }
        else
            break;
    }
    if ((K1 > 0) && (K2 > 0))
    {
        game_send(P->addr1, G, 'L');
        game_send(P->addr2, G, 'V');
    }
    else if (K1 > 0)
        game_send(P->addr1, G, 'V');
    else if (K2 > 0)
        game_send(P->addr2, G, 'V');

    free(G);
    free(P);
    pthread_exit(NULL);
}

int main(int argc, char *argv[])
{
    struct players *data;
    int server_socket_descriptor;
    int result;
    char reuse_addr_val = 1;
    struct sockaddr_in server_address;

    memset(&server_address, 0, sizeof(struct sockaddr));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = htonl(INADDR_ANY);
    server_address.sin_port = htons(SERVER_PORT);

    server_socket_descriptor = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket_descriptor < 0)
    {
        printf("%s: Błąd przy próbie utworzenia gniazda..\n", argv[0]);
        exit(1);
    }
    setsockopt(server_socket_descriptor, SOL_SOCKET, SO_REUSEADDR, (char *)&reuse_addr_val, sizeof(reuse_addr_val));

    result = bind(server_socket_descriptor, (struct sockaddr *)&server_address, sizeof(struct sockaddr));
    if (result < 0)
    {
        printf("%s: Błąd przy próbie dowiązania adresu IP i numeru portu do gniazda.\n", argv[0]);
        exit(1);
    }

    result = listen(server_socket_descriptor, QUEUE_SIZE);
    if (result < 0)
    {
        printf("%s: Błąd przy próbie ustawienia wielkości kolejki.\n", argv[0]);
        exit(1);
    }

    printf("Serwer aktywny\n");

    while (1)
    {
        data = malloc(sizeof(struct players));
        data->addr1 = accept(server_socket_descriptor, NULL, NULL);
        if (data->addr1 < 0)
        {
            printf("%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
            free(data);
            exit(1);
        }

        data->addr2 = accept(server_socket_descriptor, NULL, NULL);
        if (data->addr2 < 0)
        {
            printf("%s: Błąd przy próbie utworzenia gniazda dla połączenia.\n", argv[0]);
            free(data);
            exit(1);
        }

        pthread_t thread;
        result = pthread_create(&thread, NULL, ThreadBehavior, (void *)data);
        if (result)
        {
            printf("Błąd przy próbie utworzenia wątku, kod błędu: %d\n", result);
            free(data);
            exit(-1);
        }
    }

    close(server_socket_descriptor);
    return (0);
}
