#include<stdio.h>
int stepWay(int n);
int main(){
    int n;
    printf("Please enter the numbers of steps: ");
    scanf("%d", &n);
    int res = stepWay(n);
    printf("There are %d ways to reach", res);
}

int stepWay(int n){
    if(n == 1 || n == 0)
        return 2;
    if(n == 2)
        return 4;
    if(n == 3)
        return 7;
    return stepWay(n-1)+stepWay(n-2)+stepWay(n-3);
}