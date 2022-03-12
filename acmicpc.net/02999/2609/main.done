#include <stdio.h>
int main() {
    int a, b;
    scanf("%d %d", &a, &b);
    int r = b, _a, _b = a;
    do {
        _a = _b;
        _b = r;
        r = _a % _b;
    } while (r != 0);
    printf("%d\n%d\n", _b, (a / _b) * (b / _b) * _b);
    return 0;
}