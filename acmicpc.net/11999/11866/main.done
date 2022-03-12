#include <stdio.h>

int main() {
    int n, k;
    scanf("%d %d", &n, &k);
    int people[1000];
    for (int i = 0; i < n; i++) people[i] = i + 1;
    printf("<");
    int cur = k - 1;
    int n_people = n;
    while (n_people > 1) {
        printf("%d, ", people[cur]);
        n_people--;
        for (int i = cur; i < n_people; i++) people[i] = people[i + 1];
        cur = (cur + k - 1) % n_people;
    }
    printf("%d>\n", people[cur]);
    return 0;
}