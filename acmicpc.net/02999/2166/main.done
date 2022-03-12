#include <math.h>
#include <stdio.h>

int main() {
    int n;
    double sum;
    double coord[10000][2];
    scanf("%d", &n);
    for (int i = 0; i < n; i++) scanf("%lf %lf", &coord[i][0], &coord[i][1]);
    for (int i = 0; i < n; i++) {
        double xa, xb, ya, yb;
        xa = coord[i][0];
        xb = (i == n - 1) ? coord[0][0] : coord[i + 1][0];
        ya = coord[i][1];
        yb = (i == n - 1) ? coord[0][1] : coord[i + 1][1];
        sum += (xa + xb) * (ya - yb);
    }
    sum /= 2;
    double area = ceil(sum * 10) / 10;
    if (area < 0) area = -area;
    printf("%0.1lf", area);
    return 0;
}