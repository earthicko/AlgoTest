#include <stdio.h>

// int main() {
//     int N, last_digit = 1, count = 0;
//     scanf("%d", &N);
//     for (int n = 2; n <= N; n++) {
//         last_digit = last_digit * n;
//         while (last_digit % 10 == 0) {
//             count++;
//             last_digit /= 10;
//         }
//         if (last_digit > 10) last_digit %= 10;
//     }
//     printf("%d", count);
//     return 0;
// }
int main() {
    int N, twos = 0, fives = 0;
    scanf("%d", &N);
    for (int n = 2; n <= N; n++) {
        int temp = n;
        while (temp % 2 == 0) {
            twos++;
            temp = temp / 2;
        }
        while (temp % 5 == 0) {
            fives++;
            temp = temp / 5;
        }
    }
    printf("%d", (twos < fives) ? twos : fives);
    return 0;
}
// 00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,00000,0000
// 124