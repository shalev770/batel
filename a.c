/*
                            Sub-Marine
    -----------------------------------------------------------
        General	: Sub-Marin game
    -----------------------------------------------------------
        Input	:
    -----------------------------------------------------------
        Process : A game of two player submarine
    -----------------------------------------------------------
        Output	: Winner
    -----------------------------------------------------------
        Author	: Avishay Shriki,shalev avni.
        Date	: 06/11/24
    -----------------------------------------------------------
*/
#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>

#define MIN_SIZE_BOARD 25
#define MAX_SIZE_BOARD 39
#define B_RED "\033[0;41m"
#define B_GREEN "\033[0;42m"
#define B_YELLOW "\033[0;43m"
#define B_BLUE "\033[0;44m"
#define B_PURPLE "\033[0;45m"
#define RESET "\033[0m"
#define RED "\033[0;31m"
#define GREEN "\033[0;32m"
#define YELLOW "\033[0;33m"
#define BLUE "\033[0;34m"
#define PURPLE "\033[0;35m"

int show_submarine = 1, player = 0, count_of_hit[2] = { 0,0 };

void welcome_message();
void clear_screen();
int choose_board_size();
void draw_board(int board_size,char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD]);
void place_submarine(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD],int board_size);
void place_instructions();
int check_place_validation(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size, int x, int y, int direction, int size_ship);
void update_board(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int x, int y, int direction, int size_ship);
void change_player();
void start_game_massage();
void make_move(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size);
int is_cell_shouted(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size, int x, int y);
int is_shot_valid(int board_size, int x, int y);
void update_hit_board(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD],int x,int y);


int main() {
    
    char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD] = { 0 };
    int board_size;
    welcome_message();
    board_size = choose_board_size();
    draw_board(board_size, board_players);
    place_submarine(board_players,board_size);
    change_player();
    place_submarine(board_players, board_size);
    start_game_massage();
    while (count_of_hit[0] < 35 && count_of_hit[1] < 35) {
        change_player();
        make_move(board_players, board_size);
    }
    if (count_of_hit[0] == 35) {
        printf("player 1 win");
    }
    else{
        printf("player 2 win");
    }
    return 0;
}


void clear_screen() {
    printf("Press Enter to continue...\n");
    getchar();
    system("cls");
}
void welcome_message()
{
    printf("--------------------------------------------------------------------------\n");
    printf("Welcome to 'SUBMARINE GAME' \n");
    printf("this is a game for 2 players to drawn the other player submarines!\n");
    printf("the winner is the first one that drawn all the other player submarines \n");
    printf("--------------------------------------------------------------------------\n");
    printf("\n");
    clear_screen();
}
int choose_board_size()
{
    int board_size;
    do
    {
        printf("pleas enter the size of the board (min %d, max %d):\n", MIN_SIZE_BOARD, MAX_SIZE_BOARD);
        scanf("%d", &board_size);
        if (board_size<MIN_SIZE_BOARD || board_size > MAX_SIZE_BOARD) {
            printf("invalid value, pleas enter again\n");
        }
    } while (board_size<MIN_SIZE_BOARD || board_size > MAX_SIZE_BOARD);
    printf("\n");
    return board_size;
}
void draw_board(int board_size, char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD]) {
    int line,col,cell_value;
    printf("  |");
    for (line = 0; line < board_size; line++) {
        printf(GREEN"%2d"RESET"|", line + 1);
    }
    printf("\n");
    for (line = 0; line < board_size; line++) {
        printf(PURPLE"%2d"RESET, line + 1);
        for (col = 0; col < board_size; col++) {
            if (player) {
                cell_value = board_players[line][col]/10;
            }
            else {
                cell_value = board_players[line][col] %10;
            }
            printf("|");
            switch (cell_value)
            {
            case 0:
                printf(B_BLUE"  "RESET);
                break;
            case 1:
                printf(B_YELLOW"  "RESET);
                break;
            case 2:
                show_submarine ? printf(B_GREEN"  "RESET): printf(B_BLUE"  "RESET);
                break;
            case 3:
                printf(B_RED"  "RESET);
                break;
            default:
                printf(B_PURPLE"  "RESET);
                break;
            }
        }
        printf("|");
        printf("\n");
    }
    printf("\n");
}
void place_instructions()
{
    printf("entering submarine in this former:" GREEN"x"RESET "," PURPLE"y"RESET  "(like 28 4)\n");
    printf("when the firs number is the row and the second is the square in the row\n");
    printf("the location is the submarine head, if you place it horizontally it will place to the right\n");
    printf("if you place it vertically it will place towards down\n");
    printf("\n");
}
void place_submarine(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD],int board_size) {
    int size_ship, j,x,y, direction=1, is_valid_place=1;
    clear_screen();
    place_instructions();
    for (size_ship = 1; size_ship <= 5; size_ship++) {
        for (j = 1; j <= 6 - size_ship; j++) {
            do {
                draw_board(board_size, board_players);
                if (size_ship > 1) {
                    do {
                        printf("pleas choose the submarine direction, if down enter '1' if right '2':\n");
                        scanf("%d", &direction);
                        if (direction != 1 && direction != 2) {
                            printf("The direction not ok enter 1 or 2");
                        }
                    } while (direction != 1 && direction != 2);
                }
                do {
                    if (!is_valid_place) {
                        printf("The coordinates that you put is not ok");
                    }
                    printf("Please enter the place of the submarine %d square. you have left %d submarine\n", size_ship, 6 - size_ship - j);
                    scanf("%d%d", &x, &y);
                    x--;
                    y--;
                } while (x > MAX_SIZE_BOARD || y > MAX_SIZE_BOARD);
                clear_screen();
                is_valid_place = check_place_validation(board_players, board_size,x,y,direction,size_ship);
            } while (!is_valid_place);
            update_board(board_players, x, y, direction, size_ship);
        }
    }
}
int check_place_validation(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size,int x,int y,int direction,int size_ship) {
    int is_valid_place=1,i,j;
    if (direction == 1) {
        if (y + size_ship > board_size) {
            is_valid_place = 0;
        }
        else{
            for (i = x - 1; i <= x + 1; i++) {
                for (j = y - 1; j <= y + size_ship; j++) {
                    if (i>=0 && j>=0 && i<board_size && j<board_size) {
                        if (player)
                        {
                            if (board_players[j][i] / 10 == 2)
                            {
                                is_valid_place = 0;
                            }
                        }
                        else
                        {
                            if (board_players[j][i] % 10 == 2)
                            {
                                is_valid_place = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    else {
        if (x + size_ship > board_size) {
            is_valid_place = 0;
        }
        else {
            for (i = x - 1; i <= x + size_ship; i++) {
                for (j = y - 1; j <= y + 1; j++) {
                    if (i >= 0 && j >= 0 && i <= board_size && j <= board_size) {
                        if (player)
                        {
                            if (board_players[j][i] / 10 == 2)
                            {
                                is_valid_place = 0;
                            }
                        }
                        else
                        {
                            if (board_players[j][i] % 10 == 2)
                            {
                                is_valid_place = 0;
                            }
                        }
                    }
                }
            }
        }
    }
    return is_valid_place;
}
void update_board(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD],int x,int y,int direction,int size_ship) {
    int i,value=2;
    if (player) {
        value = 20;
    }
    if (direction == 1) {
        for (i = y; i < y + size_ship; i++) {
            board_players[i][x] += value;
        }
    }
    else {
        for (i = x; i < x + size_ship; i++) {
            board_players[y][i] += value;
        }
    }
}
void change_player()
{
    player = !player;
}
void start_game_massage()
{
    clear_screen();
    printf("Now you will start the game\n");
    printf("Every torn tou can make one move \n");
    printf("You can chose one coordination to shot a missile and try to hit a sub-marine\n");
}
void make_move(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size)
{
    int show_bord = 0, valid_shot = 1, shoted_cell = 1;
    int x, y;
    show_submarine = 1;
    printf("This is player %d torn to shot a missile\n", player + 1);
    printf("IF you want to see your bord first enter 1 else enter 2\n");
    scanf("%d", &show_bord);
    if (show_bord == 1)
    {
        draw_board(board_size,board_players);
    }
    show_submarine = 0;
    getchar();
    clear_screen();
    change_player();
    draw_board(board_size, board_players);
    printf("The place that you already shot will be in color yellow or red(red if you hit a sub-marine and yellow if you hit the water) \n");
    do
    {
        if (!shoted_cell) {
            printf("the cell that you chose is already been shot\n");
        }
        printf("Please chose a coordinates where to shot (" GREEN "x" RESET "," PURPLE "y" RESET ")\n");
        scanf("%d%d", &x, &y);
        x--;
        y--;
        valid_shot = is_shot_valid(board_size, x, y);
        if (!valid_shot)
        {
            printf("The coordination that you enter is illegal\n");
        }
        else
        {
            shoted_cell = is_cell_shouted(board_players, board_size, x, y);
        }
    } while (!valid_shot || !shoted_cell);
    update_hit_board(board_players, x, y);
    change_player();
}
int is_cell_shouted(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int board_size, int x, int y)
{
    int shoted_cell = 1;
    if (player)
    {
                if (board_players[y][x] / 10 == 1|| board_players[y][x] / 10 == 3)
                {
                    shoted_cell = 0;
                }
    }
    else
    {
                if (board_players[y][x] % 10 == 1|| board_players[y][x] % 10 == 3)
                {
                    shoted_cell = 0;
                }
    }
    return shoted_cell;
}
int is_shot_valid(int board_size, int x, int y)
{
    int is_valide = 1;
    if (x >= board_size || y >= board_size)
    {
        is_valide = 0;
    }

    return is_valide;
}
void update_hit_board(char board_players[MAX_SIZE_BOARD][MAX_SIZE_BOARD], int x, int y) {
    if (player) {
        board_players[y][x] += 10;
        if (board_players[y][x] / 10 == 3) {
            printf("you hit submarine ");
            count_of_hit[!player]++;
        }
        else {
            printf("you hit the water ");
        }
    }
    else {
        board_players[y][x] += 1;
        if (board_players[y][x] % 10 == 3) {
            printf("you hit submarine ");
            count_of_hit[!player]++;
        }
        else {
            printf("you hit the water ");
        }
    }
}