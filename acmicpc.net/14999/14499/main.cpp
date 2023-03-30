#include <cstdio>

#define MAX_N 20

typedef bool (*roller_t)(void);

typedef struct dice_s
{
	int face[6];
} dice_t;

int n, m;
int x, y;
int k;
dice_t dice;
int board[MAX_N][MAX_N];

void copyFace(void)
{
	if (board[x][y] == 0)
	{
		board[x][y] = dice.face[5];
	}
	else
	{
		dice.face[5] = board[x][y];
		board[x][y] = 0;
	}
}

bool rollEast(void)
{
	int newx = x;
	int newy = y + 1;
	if (newx < 0 || newx >= n || newy < 0 || newy >= m)
		return (false);
	x = newx;
	y = newy;
	dice_t newdice;
	newdice.face[1] = dice.face[1];
	newdice.face[3] = dice.face[3];
	newdice.face[0] = dice.face[2];
	newdice.face[2] = dice.face[5];
	newdice.face[5] = dice.face[4];
	newdice.face[4] = dice.face[0];
	dice = newdice;
	return (true);
}

bool rollWest(void)
{
	int newx = x;
	int newy = y - 1;
	if (newx < 0 || newx >= n || newy < 0 || newy >= m)
		return (false);
	x = newx;
	y = newy;
	dice_t newdice;
	newdice.face[1] = dice.face[1];
	newdice.face[3] = dice.face[3];
	newdice.face[0] = dice.face[4];
	newdice.face[4] = dice.face[5];
	newdice.face[5] = dice.face[2];
	newdice.face[2] = dice.face[0];
	dice = newdice;
	return (true);
}

bool rollNorth(void)
{
	int newx = x - 1;
	int newy = y;
	if (newx < 0 || newx >= n || newy < 0 || newy >= m)
		return (false);
	x = newx;
	y = newy;
	dice_t newdice;
	newdice.face[2] = dice.face[2];
	newdice.face[4] = dice.face[4];
	newdice.face[0] = dice.face[3];
	newdice.face[3] = dice.face[5];
	newdice.face[5] = dice.face[1];
	newdice.face[1] = dice.face[0];
	dice = newdice;
	return (true);
}

bool rollSouth(void)
{
	int newx = x + 1;
	int newy = y;
	if (newx < 0 || newx >= n || newy < 0 || newy >= m)
		return (false);
	x = newx;
	y = newy;
	dice_t newdice;
	newdice.face[2] = dice.face[2];
	newdice.face[4] = dice.face[4];
	newdice.face[0] = dice.face[1];
	newdice.face[1] = dice.face[5];
	newdice.face[5] = dice.face[3];
	newdice.face[3] = dice.face[0];
	dice = newdice;
	return (true);
}

int main(void)
{
	scanf("%d %d %d %d %d", &n, &m, &x, &y, &k);
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			scanf("%d", &board[i][j]);

	for (int i = 0; i < k; i++)
	{
		const roller_t rollers[5] = {0, rollEast, rollWest, rollNorth, rollSouth};
		int command;
		scanf("%d", &command);
		if (rollers[command]())
		{
			copyFace();
			printf("%d\n", dice.face[0]);
		}
	}
	return (0);
}
