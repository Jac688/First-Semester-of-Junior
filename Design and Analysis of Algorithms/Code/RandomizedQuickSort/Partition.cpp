#include<stdio.h>
#include<stdlib.h>

void Exchange(int* a, int *b);
int  Partition(int* A, int p, int r);
int  Randomized_Partition(int* A, int p, int r);
void Randomized_Quicksort(int* A, int p, int r);
int  Randomized_Select(int* A, int p, int r, int i);
int main() {
    int A[] = {9, 8, 7, 6, 5, 4, 3, 2, 1};
    int p = 0;
    int r = (sizeof(A) / sizeof(A[0])) - 1;
    int i = 0;
    // Randomized_Partition(A, p, r);
    // for(int i=0; i < r+1; i++){
    //     printf("%d ", A[i]);
    // }

    printf("\n");
    Randomized_Quicksort(A, p, r);
    for(int i=0; i < r+1; i++){
        printf("%d ", A[i]);
    }

    printf("\nPlease enter the ith number: ");
    scanf("%d", &i);
    int result = Randomized_Select(A, p, r, i);
    printf("The ith number is: %d", result);
    return 0;
}

int Partition(int* A, int p, int r) {
    int key = A[r];
    int i = p - 1;
    for(int j = p; j < r; j++) {
        if(A[j] <= key){
            i++;
            Exchange(&A[i], &A[j]);
        }
    }
    Exchange(&A[i+1], &A[r]);
    return i+1;
} 

int Randomized_Partition(int *A, int p, int r) {

    int j = (rand() % (r-p+1)) + p;
    printf("j = %d\n", j);
    Exchange(&A[r], &A[j]);

    // printf("\n");
    int q = Partition(A, p, r);
    return q;
}

void Randomized_Quicksort(int* A, int p, int r) {
    if(p >= r) {
        return (void)NULL;
    }
    if(p < r) {
        int q = Randomized_Partition(A, p, r);
        Randomized_Quicksort(A, p, q-1);
        Randomized_Quicksort(A, q+1, r);
    }
}

// Should recognize that:
// The order begins at 1 but array begins at 0
// i is the order we want to find
// If q is selected as the pivot, then it can return the number
// If q is smaller or larger than pivot's position, then it should keep on recursing 
// Not stop until there's only one number left or meet the pivot
// !!! If q is larger than the pivot, i = i - k

int  Randomized_Select(int* A, int p, int r, int i){
    int result = 0;
    if(p >= r) {
        return A[p];
    }
    else {
        int q = Randomized_Partition(A, p, r);
        int k = q - p + 1;
        
        if(i == k){
           result =  A[q];
           return result;
        }
        else if(i < k) {
            result = Randomized_Select(A, p, q-1, i);
            return result;
        }
        else {
            result = Randomized_Select(A, q+1, r, i-k);
            return result;
        }
    }
    return result;
}

void Exchange(int* a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
    return (void)NULL;
}