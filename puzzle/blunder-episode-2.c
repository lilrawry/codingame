#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EXIT -1
#define MAX_N 10000

struct Room {
    int id, money, top, right;
};

struct Room rooms[MAX_N];
int results_memoized[MAX_N];

// DFS function to calculate the maximum money from a given room
int DFS(int index) {
    // If the result for this room is already computed, return it
    if (results_memoized[index] != -1)
        return results_memoized[index];

    struct Room c = rooms[index];
    int result = c.money;

    // If both doors lead to other rooms, explore both
    if (c.top != EXIT && c.right != EXIT) {
        int top_money = DFS(c.top);
        int right_money = DFS(c.right);
        result = c.money + (top_money > right_money ? top_money : right_money);
    } else {
        // If one door leads to "E", explore the valid door
        if (c.top != EXIT) {
            result = c.money + DFS(c.top);
        } else if (c.right != EXIT) {
            result = c.money + DFS(c.right);
        }
    }

    // Store the result in the memoization array
    results_memoized[index] = result;
    return result;
}

int main() {
    int N;
    scanf("%d\n", &N);

    // Initialize rooms and memoized results
    for (int i = 0; i < N; i++) {
        rooms[i].id = -1;
        rooms[i].money = 0;
        rooms[i].top = EXIT;
        rooms[i].right = EXIT;
        results_memoized[i] = -1;
    }

    // Read room data
    for (int i = 0; i < N; i++) {
        char edgeT[10], edgeR[10];
        struct Room *r = &rooms[i];
        scanf("%d %d %s %s", &r->id, &r->money, edgeT, edgeR);

        // Handle edge cases where a door leads to "E" (exit)
        if (strcmp(edgeT, "E") != 0) r->top = atoi(edgeT);
        if (strcmp(edgeR, "E") != 0) r->right = atoi(edgeR);
    }

    // Perform DFS starting from room 0 and print the maximum money collected
    printf("%d\n", DFS(0));
    return 0;
}
