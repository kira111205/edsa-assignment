
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 6
#define MAX_LEN 20
#define LOG_SIZE 6

// Queue (FIFO)
typedef struct {
    char items[SIZE][MAX_LEN];
    int front, rear;
} Queue;

void initQueue(Queue *q) {
    q->front = 0;
    q->rear = -1;
}

int isQueueFull(Queue *q) {
    return q->rear == SIZE - 1;
}

int isQueueEmpty(Queue *q) {
    return q->front > q->rear;
}

void enqueue(Queue *q, char *item) {
    if (!isQueueFull(q)) {
        q->rear++;
        strcpy(q->items[q->rear], item);
    }
}

char* dequeue(Queue *q) {
    if (!isQueueEmpty(q)) {
        return q->items[q->front++];
    }
    return NULL;
}

// Stack (LIFO)
typedef struct {
    char items[SIZE][MAX_LEN];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

int isStackFull(Stack *s) {
    return s->top == SIZE - 1;
}

int isStackEmpty(Stack *s) {
    return s->top == -1;
}

void push(Stack *s, char *item) {
    if (!isStackFull(s)) {
        strcpy(s->items[++(s->top)], item);
    }
}

char* pop(Stack *s) {
    if (!isStackEmpty(s)) {
        return s->items[(s->top)--];
    }
    return NULL;
}

// A. Request and Dispatch
void requestAndDispatch() {
    Queue q;
    Stack s;
    char *deliveries[SIZE] = {"Food", "Medicine", "Tools", "Water", "Parts", "Fuel"};

    initQueue(&q);
    initStack(&s);

    for (int i = 0; i < SIZE; i++) {
        enqueue(&q, deliveries[i]);
    }

    while (!isQueueEmpty(&q)) {
        char *item = dequeue(&q);
        push(&s, item);
    }

    printf("Urgent Dispatch Order (LIFO):\n");
    while (!isStackEmpty(&s)) {
        printf("%s\n", pop(&s));
    }
}

// B. Flight Log Unit
void flightLogSimulation() {
    char *log[LOG_SIZE] = {NULL};
    char *deliveries[8] = {"Del1", "Del2", "Del3", "Del4", "Del5", "Del6", "Del7", "Del8"};
    int start = 0;

    for (int i = 0; i < 8; i++) {
        int pos = (start + i) % LOG_SIZE;
        log[pos] = deliveries[i];

        if (i >= LOG_SIZE) {
            start = (start + 1) % LOG_SIZE;
        }

        printf("Logged: %s\n", deliveries[i]);
    }

    printf("\nCurrent Log:\n");
    for (int i = 0; i < LOG_SIZE; i++) {
        printf("%s\n", log[(start + i) % LOG_SIZE]);
    }
}

// C. Overloaded Drone Tracker
typedef struct Node {
    char name[10];
    struct Node *next;
} Node;

typedef struct DNode {
    char name[10];
    struct DNode *prev, *next;
} DNode;

Node *overloaded = NULL;
DNode *serviced = NULL;

void insertSingly(char *name) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->name, name);
    newNode->next = overloaded;
    overloaded = newNode;
}

void moveToDoubly(char *name) {
    Node *temp = overloaded, *prev = NULL;

    while (temp != NULL && strcmp(temp->name, name) != 0) {
        prev = temp;
        temp = temp->next;
    }

    if (temp) {
        if (prev) prev->next = temp->next;
        else overloaded = temp->next;

        DNode *dNode = (DNode *)malloc(sizeof(DNode));
        strcpy(dNode->name, name);
        dNode->next = serviced;
        dNode->prev = NULL;

        if (serviced) serviced->prev = dNode;
        serviced = dNode;

        free(temp);
    }
}

void traverseDoubly() {
    DNode *curr = serviced;
    printf("Forward:\n");
    while (curr) {
        printf("%s\n", curr->name);
        if (!curr->next) break;
        curr = curr->next;
    }

    printf("Backward:\n");
    while (curr) {
        printf("%s\n", curr->name);
        curr = curr->prev;
    }
}

// D. Emergency Rerouting
typedef struct CNode {
    char name[10];
    struct CNode *next;
} CNode;

CNode *emergencyHead = NULL;

void insertCircular(char *name) {
    CNode *newNode = (CNode *)malloc(sizeof(CNode));
    strcpy(newNode->name, name);

    if (emergencyHead == NULL) {
        emergencyHead = newNode;
        newNode->next = newNode;
    } else {
        CNode *temp = emergencyHead;
        while (temp->next != emergencyHead) {
            temp = temp->next;
        }
        temp->next = newNode;
        newNode->next = emergencyHead;
    }
}

void traverseCircular(int times) {
    if (!emergencyHead) return;

    CNode *curr = emergencyHead;
    int count = 0;
    printf("Emergency Reroute Drones:\n");
    while (count < times) {
        printf("%s\n", curr->name);
        curr = curr->next;
        if (curr == emergencyHead) count++;
    }
}

// Main Function
int main() {
    printf("=== A. Request and Dispatch ===\n");
    requestAndDispatch();

    printf("\n=== B. Flight Log ===\n");
    flightLogSimulation();

    printf("\n=== C. Overloaded Drones ===\n");
    insertSingly("Drone3");
    insertSingly("Drone6");
    moveToDoubly("Drone3");
    traverseDoubly();

    printf("\n=== D. Emergency Rerouting ===\n");
    insertCircular("Drone1");
    insertCircular("Drone4");
    traverseCircular(2);

    return 0;
}
