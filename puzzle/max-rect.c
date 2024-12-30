#include <stdio.h>
#include <limits.h>

int main() {
    int W, H;
    scanf("%d %d", &W, &H);

    int grid[H][W];
    for (int i = 0; i < H; i++) {
        for (int j = 0; j < W; j++) {
            scanf("%d", &grid[i][j]);
        }
    }

    int maxSum = INT_MIN;

    // Iterate over all pairs of rows (top and bottom)
    for (int top = 0; top < H; top++) {
        int temp[W];  // Array to store column sums between rows top and bottom
        for (int i = 0; i < W; i++) {
            temp[i] = 0;
        }

        for (int bottom = top; bottom < H; bottom++) {
            // Add the values from the current row (bottom) to the temporary array
            for (int col = 0; col < W; col++) {
                temp[col] += grid[bottom][col];
            }

            // Now apply Kadane's algorithm to find the max subarray sum in this 1D array (temp)
            int sum = 0, localMax = INT_MIN;
            for (int i = 0; i < W; i++) {
                sum += temp[i];
                if (sum > localMax) {
                    localMax = sum;
                }
                if (sum < 0) {
                    sum = 0;
                }
            }

            // Update the overall max sum
            if (localMax > maxSum) {
                maxSum = localMax;
            }
        }
    }

    printf("%d\n", maxSum);

    return 0;
}
