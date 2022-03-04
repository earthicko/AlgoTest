#include <stdio.h>

int permutation[7];
int broken[10], usable[10];
int usable_n, digits;
int N, M;
int min_deviation = __INT32_MAX__;
int reset_permutation();
int permutate();

int main() {
    scanf("%d%d", &N, &M);
    for (int i = 0; i < M; i++) scanf("%d", &broken[i]);
    for (int num = 0; num <= 9; num++) {
        int is_usable = 1;
        for (int j = 0; j < M; j++) {
            if (broken[j] == num) {
                is_usable = 0;
                break;
            }
        }
        if (is_usable) usable[usable_n++] = num;
    }

    int min_channel_num;
    if (usable_n > 0) {
        for (int max_digits = 1; max_digits < 7; max_digits++) {
            for (int i = 0; i < 7; i++) permutation[i] = 0;

            while (permutation[max_digits] != 1) {
                int channel = 0;
                int pow_10 = 1;
                for (int i = 0; i < max_digits; i++) {
                    channel += pow_10 * usable[permutation[i]];
                    pow_10 *= 10;
                    // printf("%d ", permutation[i]);
                }
                // printf("\n");
                int deviation = N - channel;
                if (deviation < 0) deviation = -deviation;
                if (deviation < min_deviation) {
                    min_deviation = deviation;
                    digits = max_digits;
                }

                permutation[0]++;
                for (int i = 0; i < max_digits; i++)
                    if (permutation[i] == usable_n) {
                        permutation[i + 1]++;
                        permutation[i] = 0;
                    }
            }
        }
        min_channel_num = min_deviation + digits;
    } else {
        min_channel_num = __INT32_MAX__;
    }

    int min_plus_minus = N - 100;
    if (min_plus_minus < 0) min_plus_minus = -min_plus_minus;

    int min_press =
        (min_plus_minus < min_channel_num) ? min_plus_minus : min_channel_num;
    printf("%d\n", min_press);
    return 0;
}
