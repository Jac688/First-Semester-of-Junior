#include <stdio.h>
#include <cmath>


bool rootBinarySearch(int num, int lower, int upper) {
    if ((int)abs(upper - lower) <= 1) {
        // printf("%d  ", (int)abs(upper - lower));
        if (int(upper) * int(upper) == num || int(lower) * int(lower) == num)
            return true;
        else if (int(upper+1) * int(upper+1) == num || int(lower+1) * int(lower+1) == num)
            return true;
        else
            return false;  
    }
    
    if (upper * upper > num) {
        lower = upper;
        upper /= 2;
        // printf("1. %d  %d\n", upper, lower);
        rootBinarySearch(num, lower, upper);
    }
    else if (upper * upper < num && lower *lower > num){
        lower = (lower + upper) / 2;
        // printf("2. %d  %d\n", upper, lower);
        rootBinarySearch(num, lower, upper);
    }
    else if (upper * upper < num && lower *lower > num){
        lower = (lower + upper) / 2;
        // printf("2. %d  %d\n", upper, lower);
        rootBinarySearch(num, lower, upper);
    }
    else if (upper * upper < num && lower *lower < num){
        // printf("3. %d  %d\n", lower, upper*2);
        rootBinarySearch(num, upper*2, lower);
    }
}

int main(){
    int n = 0;
    printf("Please enter a number: ");
    scanf("%d", &n);
    int res = rootBinarySearch(n, 0, n);

    if(res == 0){
        printf("%d is not a perfect square number.", n);
    }
    else{
        printf("%d is a perfect square number.", n);
    }
}