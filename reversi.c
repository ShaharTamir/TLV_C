#include <stdio.h>
#include <stdlib.h>

#define FIRST_DEPTH 0
#define BOTH_DONT_HAVE_MOVES 2

typedef enum
{
    DONT_FLIP,
    FLIP
} toFlip;

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
static int g_empty_cells = 0;
static const char g_player[NUM_PLAYERS] = {'O', 'X', ' '};
static char** g_board;
static point g_scores = {0, 0};

/* main methods */
int GetBoardSizeFromUser();
char** InitGame();
void PrintBoard();
void RunGame();

/* RunGameFlow */
int HaveMoves(players turn);
void ReceiveMoveFromPlayer(point* move, players turn);
void PlayTheMove(point* move, players turn);
int GameOver();

/* HaveMoves & ReceiveMove */
int IsMoveValid(point* p, players turn);
/* PlayTheMove & IsMoveValid*/
int CheckDirectionAndFlip(srounding s, point pos, players turn, int depth, char toFlip);

/* Enable moving */
point UpdatePos(point* p, srounding s);
int IsColorHere(point* p, players color);
int IsPosValid(point* p);

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
            printf("could not allocate memory for board.\n");
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
            received_size = 4;
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
                for(int j = 0; j < g_board_size; ++j)
                    new_board[i][j] = g_player[EMPTY];

            else
            {
                for(int k = 0; k <= i; ++k)
                    free(new_board[k]);
                
                free(new_board);
                return NULL; /* failed to init board */
            }    
        }

        new_board[g_board_size / 2][g_board_size / 2] = g_player[WHITE];  /* down right in middle */
        new_board[g_board_size / 2 - 1][g_board_size / 2 - 1] = g_player[WHITE];  /* up left in middle */
        new_board[g_board_size / 2][g_board_size / 2 - 1] = g_player[BLACK];  /* down left in middle */
        new_board[g_board_size / 2 - 1][g_board_size / 2] = g_player[BLACK];  /* up right in middle */
        g_empty_cells = g_board_size * g_board_size - 4;
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
            printf(" %d ", i + 1);    
        else
            printf(" %d  ", i + 1);
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
                    printf("%d ", i + 1);
                else
                    printf("%d  ", i +1);
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
    int no_moves_counter = 0;
    point move = {0, 0};

    while(g_empty_cells && no_moves_counter < BOTH_DONT_HAVE_MOVES)
    {
        printf("It's %c turn!\n", g_player[turn]);
        have_moves = HaveMoves(turn);

        if(have_moves)
        {
            no_moves_counter = 0;
            ReceiveMoveFromPlayer(&move, turn);
            PlayTheMove(&move, turn);
            PrintBoard();
        }
        else
        {
            printf("\nNo possible moves for player %c\n", g_player[turn]);
            ++no_moves_counter;
        }

        turn = !turn;
    }
    
    GameOver();
    
    if(g_scores.x > g_scores.y)
        printf("\n\n%c player win!! with %d points over %d points!!!\n\n", g_player[WHITE], g_scores.x, g_scores.y);
    else if(g_scores.y > g_scores.x)
        printf("\n\n%c player win!! with %d points over %d points!!!\n\n", g_player[BLACK], g_scores.y, g_scores.x);
    else
        printf("\n\nIt's.... a tie....\n\n");
}

int HaveMoves(players turn)
{
    point p = {0 ,0};

    for(p.x = 0; p.x < g_board_size; ++p.x)
        for(p.y = 0; p.y < g_board_size; ++p.y)
            if(IsMoveValid(&p, turn))
                    return 1;

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
    --g_empty_cells;

    for(srounding s = 0; s < NUM_AROUND; ++s)
        CheckDirectionAndFlip(s, UpdatePos(move, s), turn, FIRST_DEPTH, FLIP);
}

int GameOver()
{
    point pos = {0, 0};
    g_scores.x = 0;
    g_scores.y = 0;
    
    for(;pos.x < g_board_size; ++pos.x)
        for(pos.y = 0; pos.y < g_board_size; ++pos.y)
        {
            if(g_board[pos.x][pos.y] == g_player[WHITE])
                ++g_scores.x;
            else if(g_board[pos.x][pos.y] == g_player[BLACK])
                ++g_scores.y;
        }

    return 1;
}

int IsMoveValid(point* p, players turn)
{
    if(IsPosValid(p) && g_board[p->x][p->y] == g_player[EMPTY])
        for(srounding s = 0; s < NUM_AROUND; ++s)
            if(CheckDirectionAndFlip(s, UpdatePos(p, s), turn, FIRST_DEPTH, DONT_FLIP))
                return 1;
    
    return 0;
}

int CheckDirectionAndFlip(srounding s, point pos, players turn, int depth, char toFlip)
{
    if(IsColorHere(&pos, !turn))
    {
        if(CheckDirectionAndFlip(s, UpdatePos(&pos, s), turn, depth + 1, toFlip))
        {
            if(toFlip)
                g_board[pos.x][pos.y] = g_player[turn]; /* flip and continue flip until the starting pos. */
            return 1;
        }
    }
    else if(IsColorHere(&pos, turn) && depth)
        return 1;   /* means found the closing point. all between this and the start should be flipped. */

    return 0;   /* means empty or ended without the same color. */
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