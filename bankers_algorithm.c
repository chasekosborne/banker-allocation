#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define MAX_P 10 // max processes
#define MAX_R 10 // max resources

// initialization
void calculateNeed(int need[MAX_P][MAX_R], int max[MAX_P][MAX_R], int allocation[MAX_P][MAX_R], int P, int R) {
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            need[i][j] = max[i][j] - allocation[i][j];
        }
    }
}

// debugging
void printMatrix(const char* name, int matrix[MAX_P][MAX_R], int P, int R) {
    printf("%s:\n", name);
    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

void printArray(const char* name, int array[], int size) {
    printf("%s: ", name);
    for (int i = 0; i < size; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

// algorithm
bool isSafe(int processes[], int available[], int max[MAX_P][MAX_R], int allocation[MAX_P][MAX_R], int P, int R) {
    
    // need matrix
    int need[MAX_P][MAX_R];
    calculateNeed(need, max, allocation, P, R);

    printMatrix("Need Matrix", need, P, R);
    printArray("Available Resources", available, R);

    bool finish[MAX_P] = {0}; // completed processes
    int safeSequence[MAX_P];  // safe sequence
    int work[MAX_R];          // simulate available resources
    
    for (int i = 0; i < R; i++) {
        work[i] = available[i];
    }

    printArray("Initial Work", work, R);

    int count = 0;
    while (count < P) {
        bool found = false;

        for (int i = 0; i < P; i++) {
            if (!finish[i]) {
                // check if process can be allocated
                bool canAllocate = true;
                for (int j = 0; j < R; j++) {
                    if (need[i][j] > work[j]) {
                        canAllocate = false;
                        break;
                    }
                }

                if (canAllocate) {
                    printf("Process P%d can be allocated\n", i);
                    for (int j = 0; j < R; j++) {
                        work[j] += allocation[i][j];
                    }
                    safeSequence[count++] = processes[i];
                    finish[i] = true;
                    found = true;

                    printArray("Updated Work", work, R);
                    break;
                }
            }
        }

        if (!found) {
            printf("System is not in a safe state.\n");
            return false;
        }
    }

    printf("System is in a safe state.\nSafe sequence is: ");
    for (int i = 0; i < P; i++) {
        printf("P%d ", safeSequence[i]);
    }
    printf("\n");
    return true;
}

int main() {
    int P, R; // processes and resources
    int allocation[MAX_P][MAX_R] = {0};
    int max[MAX_P][MAX_R] = {0};
    int available[MAX_R] = {0};
    int processes[MAX_P];

    FILE *file = fopen("table.txt", "r");
    if (file == NULL) {
        printf("Error: Unable to open file.\n");
        return 1;
    }

    if (fscanf(file, "%d %d", &P, &R) != 2) {
        printf("Error: Failed to read number of processes and resources.\n");
        fclose(file);
        return 1;
    }

    for (int i = 0; i < P; i++) {
        processes[i] = i;
    }

    for (int i = 0; i < R; i++) {
        if (fscanf(file, "%d", &available[i]) != 1) {
            printf("Error: Failed to read available resources.\n");
            fclose(file);
            return 1;
        }
    }

    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            if (fscanf(file, "%d", &allocation[i][j]) != 1) {
                printf("Error: Failed to read allocation matrix.\n");
                fclose(file);
                return 1;
            }
        }
    }

    for (int i = 0; i < P; i++) {
        for (int j = 0; j < R; j++) {
            if (fscanf(file, "%d", &max[i][j]) != 1) {
                printf("Error: Failed to read max matrix.\n");
                fclose(file);
                return 1;
            }
        }
    }

    fclose(file);

    printMatrix("Allocation Matrix", allocation, P, R);
    printMatrix("Max Matrix", max, P, R);

    isSafe(processes, available, max, allocation, P, R);

    return 0;
}

