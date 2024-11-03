#include <stdio.h>
#include <stdlib.h>

struct Matrix {
    int max;
    int unit;
    int current; // same as allocation
};

struct Matrix *P;         // For processes' maximum requests
struct Matrix *resources; // For resource units
int maxNumProcesses;
int maxNumResources;      // number of resources

void printMatrix();
int enterParameters() {
    printf("Enter total number of processes: ");
    scanf("%d", &maxNumProcesses);

    printf("Enter number of resources: ");
    scanf("%d", &maxNumResources);

    int maxClaim[maxNumProcesses][maxNumResources]; // Declare a 2D array
    int allocation[maxNumProcesses][maxNumResources];
    int storingResources[maxNumResources];
    int need[maxNumProcesses][maxNumResources];

    // resources array:
    printf("Enter number of units for resources (r0 to r2): ");
    for(int i = 0; i < maxNumResources; i++){
        scanf("%d", &storingResources[i]);
    }

    for (int i = 0; i < maxNumProcesses; i++) {
        printf("Enter maximum number of units process p%d will request from each resource (r0 to r2): ", i);
        for (int j = 0; j < maxNumResources; j++) {
            //printf("Resource[%d][%d]: ", i, j);
            scanf("%d", &maxClaim[i][j]);
        }
    }

    for(int i = 0; i < maxNumProcesses; i++){
        printf("Enter number of units of each resource (r0 to r2) allocated to process p%d: ", i);
        for (int j = 0; j < maxNumResources; j++) {
            scanf("%d", &allocation[i][j]);
        }
    }

    for(int i = 0; i < maxNumProcesses; i++){
        for (int j = 0; j < maxNumResources; j++) {
            need[i][j] = maxClaim[i][j] - allocation[i][j]; 
            //printf("need is: %d", need[i][j]);
        }
    }
    
    // Print out the array to confirm input 
    //P = (struct Matrix *)calloc(maxNumProcesses, sizeof(struct Matrix));
    //resources = (struct Matrix *)calloc(maxNumResources, sizeof(struct Matrix));

    printMatrix(maxNumProcesses, maxNumResources, maxClaim, allocation, need);
    return 0;
}


void printMatrix(int maxNumProcesses, int maxNumResources, int maxClaim[][maxNumResources], int allocation[][maxNumResources], int need[][maxNumResources]) {
    // Print header
    printf("        Max Claim           Current         Potential\n");
    printf("        ");
    for (int i = 0; i < maxNumResources; i++) printf("r%d   ", i);
    printf("\t");
    for (int i = 0; i < maxNumResources; i++) printf("r%d   ", i);
    printf("\t");
    for (int i = 0; i < maxNumResources; i++) printf("r%d   ", i);
    printf("\n------------------------------------------------------------\n");

    // Print each process's data
    for (int i = 0; i < maxNumProcesses; i++) {
        printf("p%d:    ", i);

        // Print Max Claim values
        for (int j = 0; j < maxNumResources; j++) {
            printf("%d    ", maxClaim[i][j]);
        }

        printf("\t");

        // Print Current (Allocation) values
        for (int j = 0; j < maxNumResources; j++) {
            printf("%d    ", allocation[i][j]); 
        }

        for(int j = 0; j < maxNumResources; j++) {
            printf("%d    ", need[i][j]);
        }
        printf("\n");
    }

}

int menu() {
    int option;
    printf("Banker's Algorithm\n");
    printf("------------------\n");
    printf("1) Enter parameters\n");
    printf("2) Run the Banker's algorithm to determine a safe sequence\n");
    printf("3) Quit program and free memory\n");

    scanf("%d", &option);
    return option;
}

int main() {
    int selection;
    while (1) {
        selection = menu();
        switch (selection) {
        case 1:
            enterParameters(); // Enter parameters
            break;
        case 2:
            // Call your Banker's algorithm function here
            break;
        case 3:
            // Free allocated memory before quitting
            free(P);
            free(resources);
            printf("Memory freed. Exiting program.\n");
            return 0;
        default:
            printf("Invalid option! Try it again.\n");
            break;
        }
    }
    return 0;
}