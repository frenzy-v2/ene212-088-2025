#include <stdio.h>

#define BUFFER_SIZE 5

typedef struct {
    int data[BUFFER_SIZE];
    int head;   /* next write position */
    int count;  /* number of valid samples (max BUFFER_SIZE) */
} CircularBuffer;

void init(CircularBuffer *cb) {
    cb->head = 0;
    cb->count = 0;
}

void insert_sample(CircularBuffer *cb, int value) {
    cb->data[cb->head] = value;
    cb->head = (cb->head + 1) % BUFFER_SIZE;   /* circular indexing */
    if (cb->count < BUFFER_SIZE)
        cb->count++;
}

void print_samples(const CircularBuffer *cb) {
    if (cb->count == 0) {
        printf("Buffer is empty.\n");
        return;
    }
    /* oldest index: 0 until full, then head */
    int start = (cb->count == BUFFER_SIZE) ? cb->head : 0;

    printf("Samples (oldest -> newest): ");
    for (int i = 0; i < cb->count; i++) {
        int idx = (start + i) % BUFFER_SIZE;
        printf("%d ", cb->data[idx]);
    }
    printf("\n");
}

int main() {
    CircularBuffer cb;
    init(&cb);

    int value;
    printf("Circular Data Logger (BUFFER_SIZE = %d)\n", BUFFER_SIZE);
    printf("Enter sensor values. Enter -1 to stop.\n");

    while (1) {
        printf("Enter value: ");
        if (scanf("%d", &value) != 1 || value == -1)
            break;
        insert_sample(&cb, value);
        print_samples(&cb);
    }

    printf("\nFinal contents:\n");
    print_samples(&cb);
    return 0;
}

