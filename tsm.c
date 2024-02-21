#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
// Function to generate a random array of unique elements
int* generateRandomArray(int n) {
    int* arr = (int*)malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        arr[i] = i + 2;
    }
    for (int i = n - 2; i > 0; i--) {
        int j = rand() % (i + 1);
        // Swap arr[i] and arr[j]
        int temp = arr[i];
        arr[i] = arr[j];
        arr[j] = temp;
    }
    return arr;
}
// Function to perform crossover between two arrays
int* crossoverArrays(int* arr1, int* arr2, int n) {
    int* newArr = (int*)malloc((n - 1) * sizeof(int));
    int crossoverPoint1 = rand() % (n - 1);
    int crossoverPoint2 = rand() % (n - 1);
    while (crossoverPoint1 == crossoverPoint2) {
        crossoverPoint2 = rand() % (n - 1);
    }
    if (crossoverPoint1 > crossoverPoint2) {
        int temp = crossoverPoint1;
        crossoverPoint1 = crossoverPoint2;
        crossoverPoint2 = temp;
    }
    for (int i = 0; i <= crossoverPoint1; i++) {
        newArr[i] = arr1[i];
    }
    int newArrIndex = crossoverPoint1 + 1;
    for (int i = 0; i < n - 1; i++) {
        bool isDuplicate = false;
        for (int j = 0; j <= crossoverPoint1; j++) {
            if (arr2[i] == arr1[j]) {
                isDuplicate = true;
                break;
            }
        }
        if (!isDuplicate) {
            newArr[newArrIndex] = arr2[i];
            newArrIndex++;
        }
    }
    return newArr;
}
// Function to perform mutation within an array
int* mutateArray(int* arr, int n) {
    int* mutatedArr = (int*)malloc((n - 1) * sizeof(int));
    for (int i = 0; i < n - 1; i++) {
        mutatedArr[i] = arr[i];
    }
    int mutationPoint1 = rand() % (n - 1);
    int mutationPoint2 = rand() % (n - 1);
    while (mutationPoint1 == mutationPoint2) {
        mutationPoint2 = rand() % (n - 1);
    }
    // Swap elements at mutationPoint1 and mutationPoint2
    int temp = mutatedArr[mutationPoint1];
    mutatedArr[mutationPoint1] = mutatedArr[mutationPoint2];
    mutatedArr[mutationPoint2] = temp;
    return mutatedArr;
}
int main() {
    int n;
    printf("Enter the number of cities (n): ");
    scanf("%d", &n);
    if (n < 2) {
        printf("'n' must be at least 2\n");
        return 1;
    }
    // Initialize random seed
    srand(time(NULL));
    // Create and initialize the 2D array to store distances between cities
    int** cityDistances = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        cityDistances[i] = (int*)malloc(n * sizeof(int));
    }
    // Input city distances from the user
    printf("Enter the distances between cities:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("Distance from city %d to city %d: ", i + 1, j + 1);
            scanf("%d", &cityDistances[i][j]);
        }
    }
    int* arrays[95];
    int numArrays = 0;
    for (int i = 0; i < 50; i++) {
        int* arr = generateRandomArray(n);
        arrays[numArrays] = arr;
        numArrays++;
    }
    for (int i = 0; i < 25; i++) {
        int randIdx1 = rand() % numArrays;
        int randIdx2 = rand() % numArrays;
        
        int* arr1 = arrays[randIdx1];
        int* arr2 = arrays[randIdx2];
        
        int* crossedArr = crossoverArrays(arr1, arr2, n);
        arrays[numArrays] = crossedArr;
        numArrays++;
    }
    for (int i = 0; i < 20; i++) {
        int randIdx = rand() % numArrays;
        int* arr = arrays[randIdx];
        
        int* mutatedArr = mutateArray(arr, n);
        arrays[numArrays] = mutatedArr;
        numArrays++;
    }
    // Display all 95 arrays
    for (int i = 0; i < numArrays; i++) {
        printf("Array %d: ", i + 1);
        for (int j = 0; j < n - 1; j++) {
            printf("%d ", arrays[i][j]);
        }
        printf("\n");
    }
    // Display the city distance 2D array
    printf("City Distances:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", cityDistances[i][j]);
        }
        printf("\n");
    }
  int dist=0;
  static int x=1;
  int a=arrays[0][0];
int b=cityDistances[x-1][a-1];
dist=dist+b;
for(int i=1;i<n-1;i++)
{
    int c=arrays[0][i];
    int d=cityDistances[a-1][c-1];
    a=c;
    dist=dist+d;
}
int e=cityDistances[a-1][x-1];
dist=dist+e;
int requiredarraynumber = 0;
    for(int f=1;f<95;f++)
    {
    int newdist=0,first=0;
    first= arrays[f][0];
    newdist = newdist + cityDistances[x-1][first-1];
    for (int g = 1; g<n-1;g++)
    {
    
    int h = arrays[f][g];
    newdist=newdist+cityDistances[first-1][h-1];
    first=h;}
    newdist=newdist+cityDistances[first-1][x-1];
    if(newdist<dist)
    {dist=newdist;
    requiredarraynumber = f;}
    }
    printf("The optimal solution :%d\n",dist);
    printf("The optimal solution array :%d\n",requiredarraynumber+1);
    printf("The optimal solution path : %d",x);
    for(int k=0;k<n-1;k++)
    {printf("->%d",arrays[requiredarraynumber][k]);}
    printf("-> %d",x);
    return 0;
}