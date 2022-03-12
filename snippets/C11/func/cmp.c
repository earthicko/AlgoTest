int cmp(const void* a, const void* b) {  // 오름차순
    if (*(int*)a > *(int*)b) return 1;
    if (*(int*)a < *(int*)b) return -1;
    return 0;
}