#include <stdio.h>
#include <stdlib.h>

typedef enum
{
    WHITE,
    BLACK,
    EMPTY,
    NUM_PLAYERS
} players;

typedef enum
{
    UP,
    DOWN,
    RIGHT,
    LEFT,
    UP_LEFT,
    UP_RIGHT,
    DOWN_LEFT,
    DOWN_RIGHT,
    NUM_AROUND
} srounding;

typedef struct
{
    int x;
    int y;
} point;

static int g_board_size = -1;
static const char g_player[NUM_PLAYERS] = {'O', 'X', ' '};
static char** g_board;

/* main methods */
int GetBoardSizeFromUser();
char** InitGame();
void PrintBoard();
void RunGame();

/* RunGameFlow */
int HaveMoves(players turn);
void ReceiveMoveFromPlayer(point* move, players turn);
void PlayTheMove(point* move, players turn);
int IsGameOver();

/* HaveMoves & ReceiveMove */
int IsMoveValid(point* p, players turn);
int HaveColorAround(point* p);

/* Enable moving */
point UpdatePos(point* p, srounding s);
int IsColorHere(point* p, players color);
int IsPosValid(point* p);

/* PlayTheMove */
int CheckDirectionAndFlip(srounding s, point pos, players turn);

/* IsGameOver */
void DeclareWinner(int white, int black);

int main()
{
    g_board_size = GetBoardSizeFromUser();

    if(g_board_size != 0)
    {
        g_board = InitGame();
        if(g_board)
        {
            printf("Let's begin!\n\n");
            PrintBoard();
            RunGame();
        }
        else
        {
            printf("could not allocate memory for board.\n");
        }
    }

    printf("Goodbye!\n");

    return 0;
}

int GetBoardSizeFromUser()
{
    int received_size = -1;

    while(received_size < 0 || received_size > 3)
    {
        printf("Please choose option for board size:\n");
        printf("0. to exit\n1. 10x10\n2. 15x15\n3. 20x20\n");
        printf("(enter option number)\n");

        scanf("%d", &received_size);
    }

    switch(received_size)
    {
        case 1:
            received_size = 10;
            break;
        case 2:
            received_size = 15;
            break;
        case 3:
            received_size = 20;
            break;
        default:
            printf("You choose poorly...\n");
    }

    return received_size;
}

char** InitGame()
{
    char** new_board;

    new_board = (char **)malloc((size_t)(g_board_size * sizeof(char*)));
    
    if(new_board)
    {
        for(int i = 0; i < g_board_size; ++i)
        {
            new_board[i] = (char *)malloc((size_t)g_board_size);
            if(new_board[i])
            {
                for(int j = 0; j < g_board_size; ++j)
                {
                    new_board[i][j] = g_player[EMPTY];
                }
            }
            else
            {
                for(int k = 0; k <= i; ++k)
                {
                    free(new_board[k]);
                }
                
                free(new_board);
            }    
        }

        if(new_board)
        {
            new_board[g_board_size / 2][g_board_size / 2] = g_player[WHITE];  /* down right in middle */
            new_board[g_board_size / 2 - 1][g_board_size / 2 - 1] = g_player[WHITE];  /* up left in middle */
            new_board[g_board_size / 2][g_board_size / 2 - 1] = g_player[BLACK];  /* down left in middle */
            new_board[g_board_size / 2 - 1][g_board_size / 2] = g_player[BLACK];  /* up right in middle */
        }
    }

    return new_board;
}

void PrintBoard()
{
    /* print number of columns */
    printf("    ");
    for(int i = 0; i < g_board_size; ++i)
    {
        if(i + 1 > 9)
        {
            printf(" %d ", i + 1);    
        }
        else
        {
            printf(" %d  ", i + 1);
        }
    }
    printf("\n");

    for(int i = 0; i < g_board_size; ++i)
    {
        for(int j = 0; j < g_board_size; ++j)
        {
            if(!j)
            {
                /* print number of columns */
                if(i + 1 > 9)
                {
                    printf("%d ", i + 1);
                }
                else
                {
                    printf("%d  ", i +1);
                }
            }
            printf("| %c ", g_board[i][j]);
        }
        printf("|\n");
    }
}

void RunGame()
{
    players turn = BLACK;
    int game_over = 0;
    int have_moves = 0;
    point move = {0, 0};

    while(!game_over)
    {
        printf("It's %c turn!\n", g_player[turn]);
        have_moves = HaveMoves(turn);

        if(have_moves)
        {
            ReceiveMoveFromPlayer(&move, turn);
            PlayTheMove(&move, turn);
            PrintBoard();
            game_over = IsGameOver();
        }
        else
        {
            printf("\nNo possible moves for player %c\n", g_player[turn]);
        }

        turn = !turn;
    }
}

int HaveMoves(players turn)
{
    point p = {0 ,0};

    while(p.x < g_board_size)
    {
        p.y = 0;
        while(p.y < g_board_size)
        {
            if(IsMoveValid(&p, turn))
            {
                return 1;
            }
            ++p.y;
        }
        ++p.x;
    }

    return 0;
}

void ReceiveMoveFromPlayer(point* move, players turn)
{
    int valid = 0;

    while(!valid)
    {
        printf("\nplease enter index for your move\naccording to board printed coordinates:\n");
        printf("row: ");
        scanf("%d", &(move->x));
        printf("col: ");
        scanf("%d", &(move->y));
        --move->x;
        --move->y;

        if(IsMoveValid(move, turn))
            ++valid;
        else
            printf("\nposition is not valid.\n");
    }
}

void PlayTheMove(point* move, players turn)
{
    g_board[move->x][move->y] = g_player[turn];

    for(srounding s = 0; s < NUM_AROUND; ++s)
    {
        CheckDirectionAndFlip(s, UpdatePos(move, s), turn);
    }
}

int IsMoveValid(point* p, players turn)
{
    return IsPosValid(p) && g_board[p->x][p->y] == g_player[EMPTY] && HaveColorAround(p);
}

int HaveColorAround(point* p)
{
    srounding s = 0;
    point new_p;

    while(s < NUM_AROUND)
    {
        new_p = UpdatePos(p, s);
        if(IsPosValid(&new_p) && g_board[new_p.x][new_p.y] != g_player[EMPTY])
        {
            return 1;
        }
        ++s;
    }

    return 0;
}

int IsColorHere(point* p, players color)
{
    return IsPosValid(p) && g_board[p->x][p->y] == g_player[color];
}

int IsPosValid(point* p)
{
    return p->x >= 0 && p->x < g_board_size && p->y >= 0 && p->y < g_board_size;
}

point UpdatePos(point* p, srounding s)
{
    point new_point = *p;

    switch(s)
    {
        case UP:
            --new_point.x;
            break;
        case DOWN:
            ++new_point.x;
            break;
        case  RIGHT:
            ++new_point.y;
            break;
        case LEFT:
            --new_point.y;
            break;
        case UP_LEFT:
            --new_point.x;
            --new_point.y;
            break;
        case UP_RIGHT:
            --new_point.x;
            ++new_point.y;
            break;
        case DOWN_LEFT:
            ++new_point.x;
            --new_point.y;
            break;
        case DOWN_RIGHT:
            ++new_point.x;
            ++new_point.y;
            break;
        default:
            break;
    }

    return new_point;
}

int CheckDirectionAndFlip(srounding s, point pos, players turn)
{
    if(IsColorHere(&pos, !turn))
    {
        if(CheckDirectionAndFlip(s, UpdatePos(&pos, s), turn))
        {
            g_board[pos.x][pos.y] = g_player[turn]; /* flip and continue flip until the starting pos. */
            return 1;
        }
    }
    else if(IsColorHere(&pos, turn))
    {
        return 1;   /* means found the closing point. all between this and the start should be flipped. */
    }

    return 0;   /* means empty or ended without the same color. */
}

int IsGameOver()
{
    point pos = {0, 0};
    int white_score = 0;
    int black_score = 0;
    
    while(pos.x < g_board_size)
    {
        pos.y = 0;
        while(pos.y < g_board_size)
        {
            if(g_board[pos.x][pos.y] == g_player[EMPTY])
                return 0; /* here means there are still empty cells - the game is not over */
            else if(g_board[pos.x][pos.y] == g_player[WHITE])
                ++white_score;
            else
                ++black_score;
            ++pos.y;
        }
        ++pos.x;
    }

    /* here means game over */
    DeclareWinner(white_score, black_score);

    return 1;
}

void DeclareWinner(int white, int black)
{
    if(white > black)
    {
        printf("\n\n%c player win!! with %d points over %d points!!!\n\n", g_player[WHITE], white, black);
    }
    else if(black > white)
    {
        printf("\n\n%c player win!! with %d points over %d points!!!\n\n", g_player[BLACK], black, white);
    }
    else
    {
        printf("\n\nIt's.... a tie....\n\n");
    }
}