#include <cstdio>
#include <limits.h>
#include <assert.h>

// #define _DEBUG

#ifdef _DEBUG
#define DEBUG_PRINTF(...) printf(__VA_ARGS__)
#else
#define DEBUG_PRINTF(x, ...)
#endif

#define MAX_N 100

typedef struct tankscope
{
	int xmax;
	int xmin;
	int ymax;
	int ymin;
}	tankscope;

int n;
int k;
int tank[MAX_N][MAX_N];
int tanktmp[MAX_N][MAX_N];
tankscope scope;
int fishmin;
int fishmax;
int counter;
// int dir[4][2] = {{0, 1,}, {0, -1,}, {1, 0,}, {-1, 0},};
int dir[2][2] = {{0, 1,}, {1, 0,},};

bool done(void)
{
	return (fishmax - fishmin <= k);
}

void printTank(int t[MAX_N][MAX_N])
{
	for (int y = scope.ymax - 1; y >= scope.ymin; y--)
	{
		DEBUG_PRINTF("%3d | ", y);
		for (int x = scope.xmin; x < scope.xmax; x++)
		{
			if (t[y][x] == 0)
				DEBUG_PRINTF("    ");
			else
				DEBUG_PRINTF("%3d ", t[y][x]);
		}
		DEBUG_PRINTF("\n");
	}
	DEBUG_PRINTF("----- ");
	for (int x = scope.xmin; x < scope.xmax; x++)
		DEBUG_PRINTF("%3d ", x);
	DEBUG_PRINTF("\n");
}

void addOneFishToMinFishTanks(void)
{
	for (int i = scope.xmin; i < scope.xmax; i++)
	{
		if (tank[0][i] == fishmin)
			tank[0][i]++;
	}
}

void liftLeftermostTank(void)
{
	assert(scope.xmin == 0);
	assert(scope.ymin == 0 && scope.ymax == 1);
	tank[scope.xmin + 1][1] = tank[scope.xmin][0];
	tank[scope.xmin][0] = 0;
	scope.xmin++;
	scope.ymax++;
}

// 다음 공중부양을 계속 해야하는지 반환
bool firstTankLifting(void)
{
	tankscope	origin;
	tankscope	target;
	int			remainingHeight;

	DEBUG_PRINTF("scope x: (%d, %d) y: (%d, %d)\n", scope.xmin, scope.xmax, scope.ymin, scope.ymax);
	origin.xmin = scope.xmin;
	origin.xmax = scope.xmin;
	for(int x = scope.xmin; x < scope.xmax; x++)
	{
		origin.xmax = x;
		if (tank[scope.ymax - 1][x] == 0)
		{
			for (int y = scope.ymax - 1; y >= scope.ymin; y--)
			{
				if (tank[y][x] > 0)
				{
					target.ymin = y + 1;
					break;
				}
			}
			break;
		}
	}
	if (origin.xmax == scope.xmax)
		return (false);
	origin.ymin = scope.ymin;
	origin.ymax = scope.ymax;

	target.ymax = target.ymin + (origin.xmax - origin.xmin);
	target.xmin = scope.xmin + (origin.xmax - origin.xmin);
	target.xmax = target.xmin + (origin.ymax - origin.ymin);
	DEBUG_PRINTF("origin x: (%d, %d) y: (%d, %d)\n", origin.xmin, origin.xmax, origin.ymin, origin.ymax);
	DEBUG_PRINTF("target x: (%d, %d) y: (%d, %d)\n", target.xmin, target.xmax, target.ymin, target.ymax);
	if (target.xmax > scope.xmax)
	{
		DEBUG_PRINTF("target is too wide\n");
		return (false);
	}

	{
		int targetx = target.xmin;
		int targety = target.ymax - 1;
		for (int x = origin.xmin; x < origin.xmax; x++)
		{
			for (int y = origin.ymin; y < origin.ymax; y++)
			{
				tank[targety][targetx] = tank[y][x];
				tank[y][x] = 0;
				targetx++;
			}
			targetx = target.xmin;
			targety--;
		}
	}
	scope.xmin = target.xmin;
	scope.ymax = target.ymax;
	return (true);
}

void repeatFirstTankLifting(void)
{
	while (true)
	{
		if (!firstTankLifting())
			break;
		printTank(tank);
	}
}

void repopulateTank(void)
{
	for (int x = scope.xmin; x < scope.xmax; x++)
		for (int y = scope.ymin; y < scope.ymax; y++)
			tanktmp[y][x] = tank[y][x];
	
	for (int x = scope.xmin; x < scope.xmax; x++)
	{
		for (int y = scope.ymin; y < scope.ymax; y++)
		{
			// for (int i = 0; i < 4; i++)
			for (int i = 0; i < 2; i++)
			{
				int newx = x + dir[i][0];
				int newy = y + dir[i][1];
				if (newx < scope.xmin || newx >= scope.xmax || newy < scope.ymin || newy >= scope.ymax)
					continue;
				if (tank[y][x] == 0 || tank[newy][newx] == 0)
					continue;
				int d = (tank[y][x] - tank[newy][newx]) / 5;
				if (d == 0)
					continue;
				DEBUG_PRINTF("d %d [%d][%d](%d) [%d][%d](%d)\n", d, x, y, tank[y][x], newx, newy, tank[newy][newx]);
				tanktmp[y][x] -= d;
				tanktmp[newy][newx] += d;
				DEBUG_PRINTF("after [%d][%d](%d) [%d][%d](%d)\n", x, y, tanktmp[y][x], newx, newy, tanktmp[newy][newx]);
				printTank(tanktmp);
			}
		}
	}
	for (int x = scope.xmin; x < scope.xmax; x++)
		for (int y = scope.ymin; y < scope.ymax; y++)
			tank[y][x] = 0;
}

void serializeTank(void)
{
	fishmin = INT_MAX;
	fishmax = INT_MIN;
	int newx = 0;
	for (int x = scope.xmin; x < scope.xmax; x++)
	{
		for (int y = scope.ymin; y < scope.ymax; y++)
		{
			if (tanktmp[y][x] == 0)
				continue;
			tank[0][newx] = tanktmp[y][x];
			if (tank[0][newx] < fishmin)
				fishmin = tank[0][newx];
			if (tank[0][newx] > fishmax)
				fishmax = tank[0][newx];
			newx++;
		}
	}
	scope.xmin = 0;
	scope.xmax = newx;
	scope.ymin = 0;
	scope.ymax = 1;
}

void secondTankLifting(void)
{
	tankscope	origin;
	tankscope	target;

	origin.xmin = scope.xmin;
	origin.xmax = origin.xmin + (scope.xmax - scope.xmin) / 2;
	origin.ymin = scope.ymin;
	origin.ymax = scope.ymax;

	target.xmin = scope.xmin + (scope.xmax - scope.xmin) / 2;
	target.xmax = target.xmin + (scope.xmax - scope.xmin) / 2;
	target.ymin = scope.ymax;
	target.ymax = target.ymin + (scope.ymax - scope.ymin);

	{
		int targetx = target.xmax - 1;
		int targety = target.ymax - 1;
		for (int y = origin.ymin; y < origin.ymax; y++)
		{
			for (int x = origin.xmin; x < origin.xmax; x++)
			{
				tank[targety][targetx] = tank[y][x];
				tank[y][x] = 0;
				targetx--;
			}
			targetx = target.xmax - 1;
			targety--;
		}
	}
	scope.xmin = target.xmin;
	scope.ymax = target.ymax;
}

void repeatSecondTankLifting(void)
{
	secondTankLifting();
	secondTankLifting();
}

void doCycle(void)
{
	while (true)
	{
		if (done())
			break;
		DEBUG_PRINTF("Init:\n");
		printTank(tank);
		addOneFishToMinFishTanks();
		DEBUG_PRINTF("After addOneFishToMinFishTanks\n");
		printTank(tank);
		liftLeftermostTank();
		DEBUG_PRINTF("After liftLeftermostTank\n");
		printTank(tank);
		repeatFirstTankLifting();
		DEBUG_PRINTF("After repeatFirstTankLifting\n");
		printTank(tank);
		repopulateTank();
		DEBUG_PRINTF("After repopulateTank\n");
		printTank(tanktmp);
		serializeTank();
		DEBUG_PRINTF("After serializeTank\n");
		printTank(tank);
		repeatSecondTankLifting();
		DEBUG_PRINTF("After repeatSecondTankLifting\n");
		printTank(tank);
		repopulateTank();
		DEBUG_PRINTF("After repopulateTank\n");
		printTank(tanktmp);
		serializeTank();
		DEBUG_PRINTF("After serializeTank\n");
		printTank(tank);
		counter++;
	}
}

int main(void)
{
	fishmin = INT_MAX;
	fishmax = INT_MIN;

	scanf("%d%d", &n, &k);
	scope.xmin = 0;
	scope.xmax = n;
	scope.ymin = 0;
	scope.ymax = 1;
	for (int i = 0; i < n; i++)
	{
		scanf("%d", &tank[0][i]);
		if (tank[0][i] < fishmin)
			fishmin = tank[0][i];
		if (tank[0][i] > fishmax)
			fishmax = tank[0][i];
	}
	doCycle();
	printf("%d\n", counter);
	return (0);
}
