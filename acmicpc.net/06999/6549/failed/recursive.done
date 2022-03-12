/*
논리 경로

a ~ b 범위에 대해 연산하는 함수는
- a ~ (a + b) / 2 에 대해 한번, (a + b) / 2 + 1 ~ b 에 대해 한번 재귀 호출한다.
- 빈 노드 하나를 만든다.
- 반환된 노드 2개에 대해:
    노드가 빌 때까지:
        - 노드에서 직사각형을 하나 뽑는다.
        - 직사각형이 확장 가능하면 확장한다.
            - 왼쪽 직사각형일 경우 max가, 오른쪽은 min이 경계에 닿음
            - 반대 방향으로 높이보다 작은 수가 나올때까지 배열을 탐색
        - 노드에 저장된 직사각형 중 높이와 너비가 같은 직사각형이 없을 시 노드에
        넣는다.
- a == b 일 시 높이 * 1의 직사각형을 반환한다.

연산이 완료된 후 넓이가 가장 큰 것을 찾는다.

필요 자료형
직사각형: 높이, 시작, 끝
노드: 직사각형 수, 직사각형 연결 리스트 (스택인듯)
*/
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#define MAP_SIZE 100000

typedef unsigned long long int ull;
typedef struct height {
    int h, s, e;  // height, start, end
    struct height* front;
} height;
typedef struct stack {
    int num;
    height* top;
    height* (*push)(struct stack* this, height* new);
    height* (*pop)(struct stack* this);
} stack;

int map[MAP_SIZE];
int n;

stack* solver(int left, int right);

height* rect_(int _h, int _s, int _e);
stack* stack_();
int stack__(stack* del);
height* push_stack(stack* this, height* new);
height* pop_stack(stack* this);

int main() {
    while (1) {
        scanf("%d", &n);
        if (n == 0) break;

        for (int i = 0; i < n; i++) scanf("%d", map + i);
        stack* rects = solver(0, n - 1);

        ull result = 0;
        while (rects->num > 0) {
            height* new = rects->pop(rects);
            ull width = new->e - new->s + 1;
            ull area = width * (ull) new->h;
            if (area > result) result = area;
        }
        printf("%lld\n", result);
    }
    return 0;
}

int is_expandable(height* this, int from, int dir) {
    if (dir == 1 && this->e != from) return 0;
    if (dir == -1 && this->s != from) return 0;

    int counter = 0;
    from += dir;
    while (from >= 0 && from < n) {
        if (map[from] < this->h) break;
        from += dir;
        counter++;
    }
    return counter;
}

int is_duplicate(stack* at, height* this) {
    height* cursor = at->top;
    while (cursor != NULL) {
        if (cursor->h == this->h && cursor->s == this->s &&
            cursor->e == this->e)
            return 1;
        cursor = cursor->front;
    }
    return 0;
}

stack* solver(int left, int right) {
    stack* output = stack_();
    if (left == right) {
        height* new = rect_(map[left], left, left);
        output->push(output, new);
        return output;
    }
    stack* mte[2];
    mte[0] = solver(left, (left + right) / 2);
    mte[1] = solver((left + right) / 2 + 1, right);
    for (int i = 0; i < 2; i++) {
        while (mte[i]->num > 0) {
            height* curr = mte[i]->pop(mte[i]);
            int from = (i == 0) ? (left + right) / 2 : (left + right) / 2 + 1;
            int dir = (i == 0) ? 1 : -1;
            int expand_range = is_expandable(curr, from, dir);
            if (i == 0)
                curr->e += expand_range;
            else
                curr->s -= expand_range;
            if (!is_duplicate(output, curr)) output->push(output, curr);
        }
        stack__(mte[i]);
    }
    return output;
}

height* rect_(int _h, int _s, int _e) {
    height* new = (height*)malloc(sizeof(height));
    new->h = _h;
    new->s = _s;
    new->e = _e;
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
    height* this = del->top;
    while (this != NULL) {
        height* next = this->front;
        free(this);
        this = next;
    }
    free(del);
    return 0;
}

height* push_stack(stack* this, height* new) {
    new->front = this->top;
    this->top = new;
    this->num++;
}

height* pop_stack(stack* this) {
    height* output = this->top;
    this->top = output->front;
    output->front = NULL;
    this->num--;
    return output;
}