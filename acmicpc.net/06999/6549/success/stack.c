/*
스택 이용

스택 하나를 준비
{0, 0} 푸시
최대 넓이 max = 0;
N 번 높이를 scanf
1에서 n번째로 scanf한 수 H(n)에 대하여:
    스택이 빌 때까지:
        스택 맨 위를 확인; H(n) <= H(top):
            하나를 뽑는다 {m, H(m)}
            너비 결정: n - i(top) - 1 || n
            높이 결정: H(m)
            넓이 계산 후 갱신
    스택에 {n, H(n)} 푸시
N번까지 끝난 후 {N + 1, 0}을 푸시

max 확인
*/

#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long int ull;
typedef struct stick {
    int idx, h;  // index, height
    struct stick* front;
} stick;
typedef struct stack {
    int num;
    stick* top;
    stick* (*push)(struct stack* this, stick* new);
    stick* (*pop)(struct stack* this);
} stack;

stick* stick_(int _i, int _h);
stack* stack_();
int stack__(stack* del);
stick* push_stack(stack* this, stick* new);
stick* pop_stack(stack* this);

int main() {
    while (1) {
        int N;
        scanf("%d", &N);
        if (N == 0) break;

        stack* histogram = stack_();
        ull max_a = 0;

        for (int n = 0; n <= N; n++) {
            int h_curr = 0;
            if (n < N) scanf("%d", &h_curr);
            stick* curr = stick_(n, h_curr);

            while (1) {
                if (histogram->num == 0) break;
                if (curr->h > histogram->top->h) break;

                stick* prev = histogram->pop(histogram);
                ull width =
                    (histogram->num == 0) ? n : n - histogram->top->idx - 1;
                ull height = prev->h;
                ull new_a = width * height;
                if (new_a > max_a) max_a = new_a;
                free(prev);
            }
            histogram->push(histogram, curr);
        }
        printf("%lld\n", max_a);
        
        stack__(histogram);
    }
}

stick* stick_(int _i, int _h) {
    stick* new = (stick*)malloc(sizeof(stick));
    new->idx = _i;
    new->h = _h;
    new->front = NULL;
    return new;
}

stack* stack_() {
    stack* new = (stack*)malloc(sizeof(stack));
    new->num = 0;
    new->top = NULL;
    new->push = push_stack;
    new->pop = pop_stack;
    return new;
}

int stack__(stack* del) {
    stick* this = del->top;
    while (this != NULL) {
        stick* next = this->front;
        free(this);
        this = next;
    }
    free(del);
    return 0;
}

stick* push_stack(stack* this, stick* new) {
    new->front = this->top;
    this->top = new;
    this->num++;
    return new;
}

stick* pop_stack(stack* this) {
    stick* output = this->top;
    this->top = output->front;
    output->front = NULL;
    this->num--;
    return output;
}