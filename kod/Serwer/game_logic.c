#include <string.h>
#include "game_logic.h"

void new_game(struct game *G)
{ //początkowe ustawienie tablic gry.
    int i, j;
    memset(G->castling, '1', 4 * sizeof(char));
    G->W_king[0] = 4;
    G->W_king[1] = 7;
    G->B_king[0] = 4;
    G->B_king[1] = 0;
    G->Player_symbol = 'W';
    G->rule50 = 0;
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < 8; i++)
        {
            G->board[1][i][j] = '0';
            switch (j)
            {
            case 0:
                switch (i)
                {
                case 0:
                case 7:
                    G->board[0][i][j] = 'R';
                    break;
                case 1:
                case 6:
                    G->board[0][i][j] = 'H';
                    break;
                case 2:
                case 5:
                    G->board[0][i][j] = 'B';
                    break;
                case 3:
                    G->board[0][i][j] = 'Q';
                    break;
                case 4:
                    G->board[0][i][j] = 'K';
                    break;
                default:
                    G->board[0][i][j] = '0';
                    break;
                }
                break;
            case 1:
                G->board[0][i][j] = 'P';
                break;
            case 6:
                G->board[0][i][j] = 'p';
                break;
            case 7:
                switch (i)
                {
                case 0:
                case 7:
                    G->board[0][i][j] = 'r';
                    break;
                case 1:
                case 6:
                    G->board[0][i][j] = 'h';
                    break;
                case 2:
                case 5:
                    G->board[0][i][j] = 'b';
                    break;
                case 3:
                    G->board[0][i][j] = 'q';
                    break;
                case 4:
                    G->board[0][i][j] = 'k';
                    break;
                default:
                    G->board[0][i][j] = '0';
                    break;
                }
                break;
            default:
                G->board[0][i][j] = '0';
                break;
            }
        }
    }
}

void clear_board(int c, struct game *G)
{ //wyczyszczenie tablicy.
    int i, j;
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < 8; i++)
        {
            G->board[c][i][j] = '0';
        }
    }
}

int is_safe(int x, int y, struct game *G)
{ //sprawdzenie czy pole (x,y) jest bezpieczne

    int S = 1, i, j;

    if (G->Player_symbol == 'W')
    {
        if ((y > 0) && (x > 0) && (G->board[0][x - 1][y - 1] == 'P'))
            S = 0;
        if ((y > 0) && (x < 7) && (G->board[0][x + 1][y - 1] == 'P'))
            S = 0;
    }
    if (G->Player_symbol == 'B')
    {
        if ((y < 7) && (x > 0) && (G->board[0][x - 1][y + 1] == 'p'))
            S = 0;
        if ((y < 7) && (x < 7) && (G->board[0][x + 1][y + 1] == 'p'))
            S = 0;
    }

    i = x + 1;
    while ((i <= 7) && (G->board[0][i][y] == '0'))
        i++;
    if ((i <= 7) && (((G->Player_symbol == 'W') && ((G->board[0][i][y] == 'R') || (G->board[0][i][y] == 'Q'))) || ((G->Player_symbol == 'B') && ((G->board[0][i][y] == 'r') || (G->board[0][i][y] == 'q')))))
        S = 0;

    i = y + 1;
    while ((i <= 7) && (G->board[0][x][i] == '0'))
        i++;
    if ((i <= 7) && (((G->Player_symbol == 'W') && ((G->board[0][x][i] == 'R') || (G->board[0][x][i] == 'Q'))) || ((G->Player_symbol == 'B') && ((G->board[0][x][i] == 'r') || (G->board[0][x][i] == 'q')))))
        S = 0;

    i = x - 1;
    while ((i >= 0) && (G->board[0][i][y] == '0'))
        i--;
    if ((i >= 0) && (((G->Player_symbol == 'W') && ((G->board[0][i][y] == 'R') || (G->board[0][i][y] == 'Q'))) || ((G->Player_symbol == 'B') && ((G->board[0][i][y] == 'r') || (G->board[0][i][y] == 'q')))))
        S = 0;

    i = y - 1;
    while ((i >= 0) && (G->board[0][x][i] == '0'))
        i--;
    if ((i >= 0) && (((G->Player_symbol == 'W') && ((G->board[0][x][i] == 'R') || (G->board[0][x][i] == 'Q'))) || ((G->Player_symbol == 'B') && ((G->board[0][x][i] == 'r') || (G->board[0][x][i] == 'q')))))
        S = 0;

    i = x + 1;
    j = y - 1;
    while ((i <= 7) && (j >= 0) && (G->board[0][i][j] == '0'))
    {
        i++;
        j--;
    }
    if ((i <= 7) && (j >= 0) && (((G->Player_symbol == 'W') && ((G->board[0][i][j] == 'B') || (G->board[0][i][j] == 'Q'))) || ((G->Player_symbol == 'B') && ((G->board[0][i][j] == 'b') || (G->board[0][i][j] == 'q')))))
        S = 0;

    i = x + 1;
    j = y + 1;
    while ((i <= 7) && (j <= 7) && (G->board[0][i][j] == '0'))
    {
        i++;
        j++;
    }
    if ((i <= 7) && (j <= 7) && (((G->Player_symbol == 'W') && ((G->board[0][i][j] == 'B') || (G->board[0][i][j] == 'Q'))) || ((G->Player_symbol == 'B') && ((G->board[0][i][j] == 'b') || (G->board[0][i][j] == 'q')))))
        S = 0;

    i = x - 1;
    j = y + 1;
    while ((i >= 0) && (j <= 7) && (G->board[0][i][j] == '0'))
    {
        i--;
        j++;
    }
    if ((i >= 0) && (j <= 7) && (((G->Player_symbol == 'W') && ((G->board[0][i][j] == 'B') || (G->board[0][i][j] == 'Q'))) || ((G->Player_symbol == 'B') && ((G->board[0][i][j] == 'b') || (G->board[0][i][j] == 'q')))))
        S = 0;

    i = x - 1;
    j = y - 1;
    while ((i >= 0) && (j >= 0) && (G->board[0][i][j] == '0'))
    {
        i--;
        j--;
    }
    if ((i >= 0) && (j >= 0) && (((G->Player_symbol == 'W') && ((G->board[0][i][j] == 'B') || (G->board[0][i][j] == 'Q'))) || ((G->Player_symbol == 'B') && ((G->board[0][i][j] == 'b') || (G->board[0][i][j] == 'q')))))
        S = 0;

    if ((x > 0) && (y > 1) && (((G->Player_symbol == 'W') && (G->board[0][x - 1][y - 2] == 'H')) || ((G->Player_symbol == 'B') && (G->board[0][x - 1][y - 2] == 'h'))))
        S = 0;
    if ((x < 7) && (y > 1) && (((G->Player_symbol == 'W') && (G->board[0][x + 1][y - 2] == 'H')) || ((G->Player_symbol == 'B') && (G->board[0][x + 1][y - 2] == 'h'))))
        S = 0;
    if ((x < 6) && (y > 0) && (((G->Player_symbol == 'W') && (G->board[0][x + 2][y - 1] == 'H')) || ((G->Player_symbol == 'B') && (G->board[0][x + 2][y - 1] == 'h'))))
        S = 0;
    if ((x < 6) && (y < 7) && (((G->Player_symbol == 'W') && (G->board[0][x + 2][y + 1] == 'H')) || ((G->Player_symbol == 'B') && (G->board[0][x + 2][y + 1] == 'h'))))
        S = 0;
    if ((x < 7) && (y < 6) && (((G->Player_symbol == 'W') && (G->board[0][x + 1][y + 2] == 'H')) || ((G->Player_symbol == 'B') && (G->board[0][x + 1][y + 2] == 'h'))))
        S = 0;
    if ((x > 0) && (y < 6) && (((G->Player_symbol == 'W') && (G->board[0][x - 1][y + 2] == 'H')) || ((G->Player_symbol == 'B') && (G->board[0][x - 1][y + 2] == 'h'))))
        S = 0;
    if ((x > 1) && (y < 7) && (((G->Player_symbol == 'W') && (G->board[0][x - 2][y + 1] == 'H')) || ((G->Player_symbol == 'B') && (G->board[0][x - 2][y + 1] == 'h'))))
        S = 0;
    if ((x > 1) && (y > 0) && (((G->Player_symbol == 'W') && (G->board[0][x - 2][y - 1] == 'H')) || ((G->Player_symbol == 'B') && (G->board[0][x - 2][y - 1] == 'h'))))
        S = 0;

    if ((y > 0) && (((G->Player_symbol == 'B') && (G->board[0][x][y - 1] == 'k')) || ((G->Player_symbol == 'W') && (G->board[0][x][y - 1] == 'K'))))
        S = 0;
    if ((x < 7) && (((G->Player_symbol == 'B') && (G->board[0][x + 1][y] == 'k')) || ((G->Player_symbol == 'W') && (G->board[0][x + 1][y] == 'K'))))
        S = 0;
    if ((y < 7) && (((G->Player_symbol == 'B') && (G->board[0][x][y + 1] == 'k')) || ((G->Player_symbol == 'W') && (G->board[0][x][y + 1] == 'K'))))
        S = 0;
    if ((x > 0) && (((G->Player_symbol == 'B') && (G->board[0][x - 1][y] == 'k')) || ((G->Player_symbol == 'W') && (G->board[0][x - 1][y] == 'K'))))
        S = 0;

    if ((x < 7) && (y > 0) && (((G->Player_symbol == 'B') && (G->board[0][x + 1][y - 1] == 'k')) || ((G->Player_symbol == 'W') && (G->board[0][x + 1][y - 1] == 'K'))))
        S = 0;
    if ((x < 7) && (y < 7) && (((G->Player_symbol == 'B') && (G->board[0][x + 1][y + 1] == 'k')) || ((G->Player_symbol == 'W') && (G->board[0][x + 1][y + 1] == 'K'))))
        S = 0;
    if ((x > 0) && (y < 7) && (((G->Player_symbol == 'B') && (G->board[0][x - 1][y + 1] == 'k')) || ((G->Player_symbol == 'W') && (G->board[0][x - 1][y + 1] == 'K'))))
        S = 0;
    if ((x > 0) && (y > 0) && (((G->Player_symbol == 'B') && (G->board[0][x - 1][y - 1] == 'k')) || ((G->Player_symbol == 'W') && (G->board[0][x - 1][y - 1] == 'K'))))
        S = 0;

    /*
    S=0 pole jest atakowane
    S=1 pole jest bezpieczne
    */
    return S;
}

int is_king_safe(struct game *G)
{
    if (G->Player_symbol == 'W')
        return is_safe(G->W_king[0], G->W_king[1], G);
    else
        return is_safe(G->B_king[0], G->B_king[1], G);
}

char figure_color(int x, int y, struct game *G)
{ //określenie koloru figury na polu (x,y)
    char P;

    switch (G->board[0][x][y])
    {
    case 'p':
    case 'r':
    case 'b':
    case 'h':
    case 'q':
    case 'k':
        P = 'W';
        break;
    case 'P':
    case 'R':
    case 'B':
    case 'H':
    case 'Q':
    case 'K':
        P = 'B';
        break;
    default:
        P = '0';
        break;
    }

    return P;
}

int your_figure(int x, int y, struct game *G)
{
    if (((G->Player_symbol == 'W') && (figure_color(x, y, G) == 'W')) || ((G->Player_symbol == 'B') && (figure_color(x, y, G) == 'B')))
        return 1;
    else if (((G->Player_symbol == 'W') && (figure_color(x, y, G) == 'B')) || ((G->Player_symbol == 'B') && (figure_color(x, y, G) == 'W')))
        return -1;
    else
        return 0;
}

//znajdywanie ruchów i ataków figór

int w_pawn_action(int x, int y, struct game *G, int draw)
{
    int A = 0;
    char F = G->board[0][x][y], S;
    G->board[0][x][y] = '0';

    if (G->board[0][x][y - 1] == '0')
    {
        G->board[0][x][y - 1] = F;
        if (is_safe(G->W_king[0], G->W_king[1], G) == 1)
        {
            if (draw > 0)
                G->board[1][x][y - 1] = 'a';
            A = 1;
        }
        G->board[0][x][y - 1] = '0';

        if ((y == 6) && (G->board[0][x][y - 2] == '0'))
        {
            G->board[0][x][y - 2] = F;
            if (is_safe(G->W_king[0], G->W_king[1], G) == 1)
            {
                if (draw > 0)
                    G->board[1][x][y - 2] = 'a';
                A = 1;
            }
            G->board[0][x][y - 2] = '0';
        }
    }

    if ((x > 0) && ((figure_color(x - 1, y - 1, G) == 'B') || (G->board[0][x - 1][y - 1] == 's')))
    {
        S = G->board[0][x - 1][y - 1];
        G->board[0][x - 1][y - 1] = F;
        if (is_safe(G->W_king[0], G->W_king[1], G) == 1)
        {
            if (draw > 0)
                G->board[1][x - 1][y - 1] = 'a';
            A = 1;
        }
        G->board[0][x - 1][y - 1] = S;
    }
    if ((x < 7) && ((figure_color(x + 1, y - 1, G) == 'B') || (G->board[0][x + 1][y - 1] == 's')))
    {
        S = G->board[0][x + 1][y - 1];
        G->board[0][x + 1][y - 1] = F;
        if (is_safe(G->W_king[0], G->W_king[1], G) == 1)
        {
            if (draw > 0)
                G->board[1][x + 1][y - 1] = 'a';
            A = 1;
        }
        G->board[0][x + 1][y - 1] = S;
    }

    G->board[0][x][y] = F;
    return A;
}

int b_pawn_action(int x, int y, struct game *G, int draw)
{
    int A = 0;
    char F = G->board[0][x][y], S;
    G->board[0][x][y] = '0';

    if (G->board[0][x][y + 1] == '0')
    {
        G->board[0][x][y + 1] = F;
        if (is_safe(G->B_king[0], G->B_king[1], G) == 1)
        {
            if (draw > 0)
                G->board[1][x][y + 1] = 'a';
            A = 1;
        }
        G->board[0][x][y + 1] = '0';

        if ((y == 1) && (G->board[0][x][y + 2] == '0'))
        {
            G->board[0][x][y + 2] = F;
            if (is_safe(G->B_king[0], G->B_king[1], G) == 1)
            {
                if (draw > 0)
                    G->board[1][x][y + 2] = 'a';
                A = 1;
            }
            G->board[0][x][y + 2] = '0';
        }
    }

    if ((x > 0) && ((figure_color(x - 1, y + 1, G) == 'W') || (G->board[0][x - 1][y + 1] == 's')))
    {
        S = G->board[0][x - 1][y + 1];
        G->board[0][x - 1][y + 1] = F;
        if (is_safe(G->B_king[0], G->B_king[1], G) == 1)
        {
            if (draw > 0)
                G->board[1][x - 1][y + 1] = 'a';
            A = 1;
        }
        G->board[0][x - 1][y + 1] = S;
    }
    if ((x < 7) && ((figure_color(x + 1, y + 1, G) == 'W') || (G->board[0][x + 1][y + 1] == 's')))
    {
        S = G->board[0][x + 1][y + 1];
        G->board[0][x + 1][y + 1] = F;
        if (is_safe(G->B_king[0], G->B_king[1], G) == 1)
        {
            if (draw > 0)
                G->board[1][x + 1][y + 1] = 'a';
            A = 1;
        }
        G->board[0][x + 1][y + 1] = S;
    }

    G->board[0][x][y] = F;
    return A;
}

int rook_action(int x, int y, struct game *G, int draw)
{

    int i, A = 0;
    char F = G->board[0][x][y], S;

    G->board[0][x][y] = '0';

    i = x + 1;
    while ((i <= 7) && (G->board[0][i][y] == '0'))
    {
        G->board[0][i][y] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][i][y] = 'a';
            A = 1;
        }
        G->board[0][i][y] = '0';
        i++;
    }
    if ((i <= 7) && (your_figure(i, y, G) == -1))
    {
        S = G->board[0][i][y];
        G->board[0][i][y] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][i][y] = 'a';
            A = 1;
        }
        G->board[0][i][y] = S;
    }
    i = y + 1;
    while ((i <= 7) && (G->board[0][x][i] == '0'))
    {
        G->board[0][x][i] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][x][i] = 'a';
            A = 1;
        }
        G->board[0][x][i] = '0';
        i++;
    }
    if ((i <= 7) && (your_figure(x, i, G) == -1))
    {
        S = G->board[0][x][i];
        G->board[0][x][i] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][x][i] = 'a';
            A = 1;
        }
        G->board[0][x][i] = S;
    }
    i = x - 1;
    while ((i >= 0) && (G->board[0][i][y] == '0'))
    {
        G->board[0][i][y] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][y] = 'a';
            A = 1;
        }
        G->board[0][i][y] = '0';
        i--;
    }
    if ((i >= 0) && (your_figure(i, y, G) == -1))
    {
        S = G->board[0][i][y];
        G->board[0][i][y] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][y] = 'a';
            A = 1;
        }
        G->board[0][i][y] = S;
    }
    i = y - 1;
    while ((i >= 0) && (G->board[0][x][i] == '0'))
    {
        G->board[0][x][i] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][x][i] = 'a';
            A = 1;
        }
        G->board[0][x][i] = '0';
        i--;
    }
    if ((i >= 0) && (your_figure(x, i, G) == -1))
    {
        S = G->board[0][x][i];
        G->board[0][x][i] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][x][i] = 'a';
            A = 1;
        }
        G->board[0][x][i] = S;
    }

    G->board[0][x][y] = F;
    return A;
}

int bishop_action(int x, int y, struct game *G, int draw)
{

    int i, j, A = 0;
    char F = G->board[0][x][y], S;

    G->board[0][x][y] = '0';
    i = x + 1;
    j = y - 1;
    while ((i <= 7) && (j >= 0) && (G->board[0][i][j] == '0'))
    {
        G->board[0][i][j] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][j] = 'a';
            A = 1;
        }
        G->board[0][i][j] = '0';
        i++;
        j--;
    }
    if ((i <= 7) && (j >= 0) && (your_figure(i, j, G) == -1))
    {
        S = G->board[0][i][j];
        G->board[0][i][j] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][j] = 'a';
            A = 1;
        }
        G->board[0][i][j] = S;
    }
    i = x + 1;
    j = y + 1;
    while ((i <= 7) && (j <= 7) && (G->board[0][i][j] == '0'))
    {
        G->board[0][i][j] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][j] = 'a';
            A = 1;
        }
        G->board[0][i][j] = '0';
        i++;
        j++;
    }
    if ((i <= 7) && (j <= 7) && (your_figure(i, j, G)))
    {
        S = G->board[0][i][j];
        G->board[0][i][j] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][j] = 'a';
            A = 1;
        }
        G->board[0][i][j] = S;
    }
    i = x - 1;
    j = y + 1;
    while ((i >= 0) && (j <= 7) && (G->board[0][i][j] == '0'))
    {
        G->board[0][i][j] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][j] = 'a';
            A = 1;
        }
        G->board[0][i][j] = '0';
        i--;
        j++;
    }
    if ((i >= 0) && (j <= 7) && (your_figure(i, j, G)))
    {
        S = G->board[0][i][j];
        G->board[0][i][j] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][j] = 'a';
            A = 1;
        }
        G->board[0][i][j] = S;
    }
    i = x - 1;
    j = y - 1;
    while ((i >= 0) && (j >= 0) && (G->board[0][i][j] == '0'))
    {
        G->board[0][i][j] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][j] = 'a';
            A = 1;
        }
        G->board[0][i][j] = '0';
        i--;
        j--;
    }
    if ((i >= 0) && (j >= 0) && (your_figure(i, j, G) == -1))
    {
        S = G->board[0][i][j];
        G->board[0][i][j] = F;
        if (is_king_safe(G))
        {
            if (draw > 0)
                G->board[1][i][j] = 'a';
            A = 1;
        }
        G->board[0][i][j] = S;
    }

    G->board[0][x][y] = F;
    return A;
}

int knight_action(int x, int y, struct game *G, int draw)
{

    int A = 0;
    char F = G->board[0][x][y], S;

    G->board[0][x][y] = '0';
    S = G->board[0][x - 1][y - 2];
    if ((x > 0) && (y > 1) && (your_figure(x - 1, y - 2, G) != 1))
    {
        G->board[0][x - 1][y - 2] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][x - 1][y - 2] = 'a';
            A = 1;
        }
        G->board[0][x - 1][y - 2] = S;
    }
    S = G->board[0][x + 1][y - 2];
    if ((x < 7) && (y > 1) && (your_figure(x + 1, y - 2, G) != 1))
    {
        G->board[0][x + 1][y - 2] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][x + 1][y - 2] = 'a';
            A = 1;
        }
        G->board[0][x + 1][y - 2] = S;
    }
    S = G->board[0][x + 2][y - 1];
    if ((x < 6) && (y > 0) && (your_figure(x + 2, y - 1, G) != 1))
    {
        G->board[0][x + 2][y - 1] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][x + 2][y - 1] = 'a';
            A = 1;
        }
        G->board[0][x + 2][y - 1] = S;
    }
    S = G->board[0][x + 2][y + 1];
    if ((x < 6) && (y < 7) && (your_figure(x + 2, y + 1, G) != 1))
    {
        G->board[0][x + 2][y + 1] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][x + 2][y + 1] = 'a';
            A = 1;
        }
        G->board[0][x + 2][y + 1] = S;
    }
    S = G->board[0][x + 1][y + 2];
    if ((x < 7) && (y < 6) && (your_figure(x + 1, y + 2, G) != 1))
    {
        G->board[0][x + 1][y + 2] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][x + 1][y + 2] = 'a';
            A = 1;
        }
        G->board[0][x + 1][y + 2] = S;
    }
    S = G->board[0][x - 1][y + 2];
    if ((x > 0) && (y < 6) && (your_figure(x - 1, y + 2, G) != 1))
    {
        G->board[0][x - 1][y + 2] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][x - 1][y + 2] = 'a';
            A = 1;
        }
        G->board[0][x - 1][y + 2] = S;
    }
    S = G->board[0][x - 2][y + 1];
    if ((x > 1) && (y < 7) && (your_figure(x - 2, y + 1, G) != 1))
    {
        G->board[0][x - 2][y + 1] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][x - 2][y + 1] = 'a';
            A = 1;
        }
        G->board[0][x - 2][y + 1] = S;
    }
    S = G->board[0][x - 2][y - 1];
    if ((x > 1) && (y > 0) && (your_figure(x - 2, y - 1, G) != 1))
    {
        G->board[0][x - 2][y - 1] = F;
        if (is_king_safe(G) == 1)
        {
            if (draw > 0)
                G->board[1][x - 2][y - 1] = 'a';
            A = 1;
        }
        G->board[0][x - 2][y - 1] = S;
    }

    G->board[0][x][y] = F;

    return A;
}

int king_action(int x, int y, struct game *G, int draw)
{

    int A = 0;
    char F = G->board[0][x][y];

    G->board[0][x][y] = '0';

    if ((y > 0) && (is_safe(x, y - 1, G) == 1) && (your_figure(x, y - 1, G) != 1))
    {
        if (draw > 0)
            G->board[1][x][y - 1] = 'a';
        A = 1;
    }
    if ((x < 7) && (is_safe(x + 1, y, G) == 1) && (your_figure(x + 1, y, G) != 1))
    {
        if (draw > 0)
            G->board[1][x + 1][y] = 'a';
        A = 1;
    }
    if ((y < 7) && (is_safe(x, y + 1, G) == 1) && (your_figure(x, y + 1, G) != 1))
    {
        if (draw > 0)
            G->board[1][x][y + 1] = 'a';
        A = 1;
    }
    if ((x > 0) && (is_safe(x - 1, y, G) == 1) && (your_figure(x - 1, y, G) != 1))
    {
        if (draw > 0)
            G->board[1][x - 1][y] = 'a';
        A = 1;
    }

    if ((x < 7) && (y > 0) && (is_safe(x + 1, y - 1, G) == 1) && (your_figure(x + 1, y - 1, G) != 1))
    {
        if (draw > 0)
            G->board[1][x + 1][y - 1] = 'a';
        A = 1;
    }
    if ((x < 7) && (y < 7) && (is_safe(x + 1, y + 1, G) == 1) && (your_figure(x + 1, y + 1, G) != 1))
    {
        if (draw > 0)
            G->board[1][x + 1][y + 1] = 'a';
        A = 1;
    }
    if ((x > 0) && (y < 7) && (is_safe(x - 1, y + 1, G) == 1) && (your_figure(x - 1, y + 1, G) != 1))
    {
        if (draw > 0)
            G->board[1][x - 1][y + 1] = 'a';
        A = 1;
    }
    if ((x > 0) && (y > 0) && (is_safe(x - 1, y - 1, G) == 1) && (your_figure(x - 1, y - 1, G) != 1))
    {
        if (draw > 0)
            G->board[1][x - 1][y - 1] = 'a';
        A = 1;
    }

    if (F == 'K')
    {
        if ((G->castling[0] == '1') && (is_safe(2, 0, G) == 1) && (is_safe(3, 0, G) == 1) && (is_safe(4, 0, G) == 1) && (G->board[0][1][0] == '0') && (G->board[0][2][0] == '0') && (G->board[0][3][0] == '0'))
        {
            if (draw > 0)
                G->board[1][2][0] = 's';
            A = 1;
        }
        if ((G->castling[1] == '1') && (is_safe(4, 0, G) == 1) && (is_safe(5, 0, G) == 1) && (is_safe(6, 0, G) == 1) && (G->board[0][5][0] == '0') && (G->board[0][6][0] == '0'))
        {
            if (draw > 0)
                G->board[1][6][0] = 's';
            A = 1;
        }
    }
    if (F == 'k')
    {
        if ((G->castling[2] == '1') && (is_safe(2, 7, G) == 1) && (is_safe(3, 7, G) == 1) && (is_safe(3, 7, G) == 1) && (G->board[0][1][7] == '0') && (G->board[0][2][7] == '0') && (G->board[0][3][7] == '0'))
        {
            if (draw > 0)
                G->board[1][2][7] = 's';
            A = 1;
        }
        if ((G->castling[3] == '1') && (is_safe(4, 7, G) == 1) && (is_safe(5, 7, G) == 1) && (is_safe(6, 7, G) == 1) && (G->board[0][5][7] == '0') && (G->board[0][6][7] == '0'))
        {
            if (draw > 0)
                G->board[1][6][7] = 's';
            A = 1;
        }
    }

    G->board[0][x][y] = F;

    return A;
}

void find_action(int x, int y, struct game *G)
{ //znajdywanie możliwej akcji dla figury na polu (x,y)

    G->X = x;
    G->Y = y;
    clear_board(1, G);

    if (your_figure(x, y, G) == 1)
    {
        switch (G->board[0][x][y])
        {
        case 'p':
            w_pawn_action(x, y, G, 1);
            break;
        case 'P':
            b_pawn_action(x, y, G, 1);
            break;
        case 'r':
        case 'R':
            rook_action(x, y, G, 1);
            break;
        case 'b':
        case 'B':
            bishop_action(x, y, G, 1);
            break;
        case 'h':
        case 'H':
            knight_action(x, y, G, 1);
            break;
        case 'q':
        case 'Q':
            rook_action(x, y, G, 1);
            bishop_action(x, y, G, 1);
            break;
        case 'k':
        case 'K':
            king_action(x, y, G, 1);
            break;
        }
    }
}

int action(int x, int y, struct game *G)
{ //wykonanie akcji

    int A = 0;

    if (G->board[1][x][y] == 'a')
    {

        if (G->board[0][x][y] == 's')
            G->board[0][x][G->Y] = '0';

        G->board[0][x][y] = G->board[0][G->X][G->Y];
        G->board[0][G->X][G->Y] = '0';

        if (((G->X == 0) && (G->Y == 0)) || ((x == 0) && (y == 0)))
            G->castling[0] = '0';
        if (((G->X == 7) && (G->Y == 0)) || ((x == 7) && (y == 0)))
            G->castling[1] = '0';
        if (((G->X == 0) && (G->Y == 7)) || ((x == 0) && (y == 7)))
            G->castling[2] = '0';
        if (((G->X == 7) && (G->Y == 7)) || ((x == 7) && (y == 7)))
            G->castling[3] = '0';

        if (G->board[0][x][y] == 'K')
        {
            G->castling[0] = '0';
            G->castling[1] = '0';
            G->B_king[0] = x;
            G->B_king[1] = y;
        }
        if (G->board[0][x][y] == 'k')
        {
            G->castling[2] = '0';
            G->castling[3] = '0';
            G->W_king[0] = x;
            G->W_king[1] = y;
        }

        clear_board(1, G);
        A = A | 1;
    }
    if (G->board[1][x][y] == 's')
    {
        if (y == 0)
        {
            G->board[0][4][0] = '0';
            if (x == 2)
            {
                G->board[0][0][0] = '0';
                G->board[0][3][0] = 'R';
                G->board[0][2][0] = 'K';
                G->B_king[1] = 2;
            }
            if (x == 6)
            {
                G->board[0][7][0] = '0';
                G->board[0][5][0] = 'R';
                G->board[0][6][0] = 'K';
                G->B_king[1] = 6;
            }
            G->castling[0] = '0';
            G->castling[1] = '0';
        }
        if (y == 7)
        {
            G->board[0][4][7] = '0';
            if (x == 2)
            {
                G->board[0][0][7] = '0';
                G->board[0][3][7] = 'r';
                G->board[0][2][7] = 'k';
                G->W_king[1] = 2;
            }
            if (x == 6)
            {
                G->board[0][7][7] = '0';
                G->board[0][5][7] = 'r';
                G->board[0][6][7] = 'k';
                G->W_king[1] = 6;
            }
            G->castling[2] = '0';
            G->castling[3] = '0';
        }
        clear_board(1, G);
        A = A | 1;
    }
    if (A & 1)
    {
        int i, j;
        for (j = 0; j < 8; j++)
        {
            for (i = 0; i < 8; i++)
            {
                if (G->board[0][i][j] == 's')
                    G->board[0][i][j] = '0';
            }
        }
        if ((G->board[0][x][y] == 'P') && (y == 3) && (G->Y == 1))
            G->board[0][x][2] = 's';
        if ((G->board[0][x][y] == 'p') && (y == 4) && (G->Y == 6))
            G->board[0][x][5] = 's';

        if (((G->board[0][x][y] == 'p') && (y == 0)) || ((G->board[0][x][y] == 'P') && (y == 7)))
            A = A | 2;
        if ((G->board[0][x][y] == 'p') || (G->board[0][x][y] == 'P'))
            G->rule50 = 0;
        else
            G->rule50 += 1;
    }

    /*
    A=0 nic
    A=1 akcja wykonana
    A=3 pionek na ostatnim rzędzie
    */
    return A;
}

void change(struct game *G, int x, int y, char f)
{ // zamiana figury

    G->board[0][x][y] = f;

    if (G->Player_symbol == 'W')
        G->board[0][x][y] = G->board[0][x][y] + 32; // zmiana na białą figure
}

int figure_count(int figures[5])
{
    if ((figures[0] > 0) || (figures[1] > 0) || (figures[2] > 1) || (figures[3] > 1) || (figures[4] > 0) || ((figures[2] > 0) && (figures[3] > 0)))
        return 1;
    else
        return 0;
}

int checkmate(struct game *G)
{ //określenie czy aktywny gracz przegrał

    int C = 0, i, j;
    if (is_king_safe(G) == 0)
    {
        C = C | 2;
        G->rule50 = 0;
    }
    int white[5] = {0, 0, 0, 0, 0}, black[5] = {0, 0, 0, 0, 0};

    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < 8; i++)
        {
            if (your_figure(i, j, G) == 1)
            {
                switch (G->board[0][i][j])
                {
                case 'p':
                    C = C | w_pawn_action(i, j, G, 0);
                    white[0] += 1;
                    break;
                case 'r':
                    C = C | rook_action(i, j, G, 0);
                    white[1] += 1;
                    break;
                case 'b':
                    C = C | bishop_action(i, j, G, 0);
                    white[2] += 1;
                    break;
                case 'h':
                    C = C | knight_action(i, j, G, 0);
                    white[3] += 1;
                    break;
                case 'q':
                    C = C | rook_action(i, j, G, 0);
                    C = C | bishop_action(i, j, G, 0);
                    white[4] += 1;
                    break;
                case 'P':
                    C = C | b_pawn_action(i, j, G, 0);
                    black[0] += 1;
                    break;
                case 'R':
                    C = C | rook_action(i, j, G, 0);
                    black[1] += 1;
                    break;
                case 'B':
                    C = C | bishop_action(i, j, G, 0);
                    black[2] += 1;
                    break;
                case 'H':
                    C = C | knight_action(i, j, G, 0);
                    black[3] += 1;
                    break;
                case 'Q':
                    C = C | rook_action(i, j, G, 0);
                    C = C | bishop_action(i, j, G, 0);
                    black[4] += 1;
                    break;
                case 'k':
                case 'K':
                    C = C | king_action(i, j, G, 0);
                    break;
                default:
                    break;
                }
            }
        }
    }

    if ((figure_count(white) == 0) && (figure_count(black) == 0))
        C = 0;

    if (G->rule50 >= 50)
        C = 0;

    /*
    C=0 pat
    C=1 nic
    C=2 checkmate
    C=3 Check
    */
    return C;
}