#ifndef GAME_LOGIC_H_INCLUDED
#define GAME_LOGIC_H_INCLUDED

struct game
{
    char board[2][8][8]; //plansza
    int X, Y;            //współrzędne wybranej figury
    int Player[2];       //addresy graczy
    char Player_symbol;  //kolor gracza wykonującego ruch
    char castling[4];    //sprawdzanie czy wierze wykonały ruch, ważne dla roszady
    int W_king[2];       //współrzędne białego króla
    int B_king[2];       //współrzędne czarnego króla
};

void new_game(struct game *G);

void find_action(int x, int y, struct game *G);

int action(int x, int y, struct game *G);

int checkmate(struct game *G);

void change(struct game *G, int x, int y, char f);

#endif // GAME_LOGIC_H_INCLUDED
