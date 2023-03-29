#include <cstdio>

// #define _DEBUG

#ifdef _DEBUG
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(x, ...)
#endif

#define MAX_N 100
#define MAX_L 100

#define RIGHT 0
#define UP 1
#define LEFT 2
#define DOWN 3
#define APPLE 8
#define EMPTY 9

typedef struct action
{
	int tick;
	char dir;
}	action;

// L: increment, D: decrement
// 0: right, 1: up, 2: left, 3: down
const int dirs[4][2] = {{0, 1, }, {-1, 0, }, {0, -1, }, {1, 0, }, };

int n;
int k;
int l;
int board[MAX_N][MAX_N];
action actions[MAX_L];
int actionIdx;
int headrow, headcol;
int tailrow, tailcol;
int dir;
int time;

void printBoard(void)
{
	for (int col = 0; col < n; col++)
		DEBUG_PRINTF("--");
	DEBUG_PRINTF("\n");
	for (int row = 0; row < n; row++)
	{
		for (int col = 0; col < n; col++)
		{
			switch (board[row][col])
			{
			case APPLE:
				DEBUG_PRINTF("A ");
				break;
			case UP:
				DEBUG_PRINTF("U ");
				break;
			case DOWN:
				DEBUG_PRINTF("D ");
				break;
			case RIGHT:
				DEBUG_PRINTF("R ");
				break;
			case LEFT:
				DEBUG_PRINTF("L ");
				break;
			default:
				DEBUG_PRINTF(". ");
				break;
			}
		}
		DEBUG_PRINTF("\n");
	}
}

bool doOneTick(void)
{
	if (actions[actionIdx].tick == time)
	{
		if (actions[actionIdx].dir == 'L')
			dir = (dir + 1) % 4;
		else
			dir = (dir - 1 + 4) % 4;
		actionIdx++;
	}
	time++;
	board[headrow][headcol] = dir;
	int headnewrow = headrow + dirs[dir][0];
	int headnewcol = headcol + dirs[dir][1];
	DEBUG_PRINTF("dir %d, now (%d, %d), next (%d, %d)\n", dir, headrow, headcol, headnewrow, headnewcol);
	if (headnewrow < 0 || headnewrow >= n || headnewcol < 0 || headnewcol >= n)
		return (false);
	if (board[headnewrow][headnewcol] != EMPTY && board[headnewrow][headnewcol] != APPLE)
		return (false);
	if (board[headnewrow][headnewcol] == EMPTY)
	{
		int tailnewrow = tailrow + dirs[board[tailrow][tailcol]][0];
		int tailnewcol = tailcol + dirs[board[tailrow][tailcol]][1];
		board[tailrow][tailcol] = EMPTY;
		tailrow = tailnewrow;
		tailcol = tailnewcol;
	}
	board[headnewrow][headnewcol] = dir;
	headrow = headnewrow;
	headcol = headnewcol;
	return (true);
}

int main(void)
{
	scanf("%d%d", &n, &k);
	for (int row = 0; row < n; row++)
		for (int col = 0; col < n; col++)
			board[row][col] = EMPTY;
	board[0][0] = RIGHT;
	for (int i = 0; i < k; i++)
	{
		int applerow, applecol;
		scanf("%d%d", &applerow, &applecol);
		board[applerow - 1][applecol - 1] = APPLE;
	}
	scanf("%d", &l);
	for (int i = 0; i < l; i++)
		scanf("%d %c", &actions[i].tick, &actions[i].dir);

	for (int i = 0; i < l; i++)
		DEBUG_PRINTF("%d %c\n", actions[i].tick, actions[i].dir);

	while (true)
	{
		printBoard();
		if (doOneTick() == false)
			break;
	}

	printf("%d\n", time);

	return (0);
}
