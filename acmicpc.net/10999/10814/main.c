#include <stdio.h>
#include <stdlib.h>
#define N_MAX 100000

typedef struct person {
    int age, name_i;
} person;

int N;
person people[N_MAX];
char names[N_MAX][101];

int static cmp_age(const void* first, const void* second);
int static cmp_order(const void* first, const void* second);

int main() {
    scanf("%d\n", &N);
    for (int n = 0; n < N; n++) {
        scanf("%d %s", &(people[n].age), names[n]);
        people[n].name_i = n;
    }
    qsort(people, N, sizeof(person), cmp_age);
    for (int i = 0; i < N; i++) {
        int start = i, start_age = people[i].age, end = N;
        for (int j = start + 1; j < N; j++) {
            if (people[j].age != start_age) {
                end = j;
                break;
            }
        }
        qsort(people + start, end - start, sizeof(person), cmp_order);
        i = end - 1;
    }
    for (int i = 0; i < N; i++)
        printf("%d %s\n", people[i].age, names[people[i].name_i]);
    return 0;
}

int static cmp_age(const void* first, const void* second) {
    if (((person*)first)->age > ((person*)second)->age)
        return 1;
    else if (((person*)first)->age < ((person*)second)->age)
        return -1;
    else
        return 0;
}
int static cmp_order(const void* first, const void* second) {
    if (((person*)first)->name_i > ((person*)second)->name_i)
        return 1;
    else if (((person*)first)->name_i < ((person*)second)->name_i)
        return -1;
    else
        return 0;
}
