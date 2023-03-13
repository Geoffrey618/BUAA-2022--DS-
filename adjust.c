//
// Created by 继续宠爱 on 2022/6/19.
//
#include <stdio.h>
#include <stdlib.h>

struct Gate {
    int id, capacity, order, fa;
} tree[300], out[100];
int numOut, i, id[100], no, capacity;
int fa, son;

int cmp1(const void *a, const void *b) {
    struct Gate *pa = (struct Gate *) a;
    struct Gate *pb = (struct Gate *) b;
    return pa->order > pb->order ? 1 : -1;
}

int cmp2(const void *a, const void *b) {
    struct Gate *pa = (struct Gate *) a;
    struct Gate *pb = (struct Gate *) b;
    return pa->capacity > pb->capacity ? -1 :
           pa->capacity < pb->capacity ? 1 :
           pa->id > pb->id ? 1 : -1;
}

int main() {
    while (scanf("%d", &fa)) {
        if (fa == -1) break;
        i = 0;
        while (scanf("%d", &son)) {
            if (son == -1) break;
            tree[son].id = son;
            tree[son].order = 3 * tree[fa].order + i + 1;
            i++;
        }
    }
    while (scanf("%d %d", &no, &capacity) == 2) tree[no].capacity = capacity;
    for (i = 0; i < 200; ++i) {
        if (0 < tree[i].id && tree[i].id < 100) out[numOut++] = tree[i];
    }
    qsort(out, numOut, sizeof(struct Gate), cmp1);
    for (i = 0; i < numOut; i++) id[i] = out[i].id;
    qsort(out, numOut, sizeof(struct Gate), cmp2);
    for (i = 0; i < numOut; i++) printf("%d->%d\n", out[i].id, id[i]);
    return 0;
}

