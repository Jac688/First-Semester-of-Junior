#include<stdio.h>
#include<stdlib.h>
#include <math.h>

long polyMult(long a, long b , int n1, int n2);

int main() {

    long a = 0, b = 0; 
    printf("Please enter two integer: ");
    scanf("%d %d", &a, &b);
    long test = a * b;
    printf("test a*b = %ld", test);
    int n1 = 0, n2 = 0;
    for(int i = a; i > 0; i/=10){
        n1++;
    }
    for(int i = b; i > 0; i/=10){
        n2++;
    }

    long result = polyMult(a, b, n1, n2);
    printf("result = %ld", result);
    return 0;
}

// long polyMult(long X, long Y, int xn, int yn)
// {
//     if (X == 0 || Y == 0)
//         return 0;
//     else if ((xn == 1 && yn == 1) || xn == 1 || yn == 1)
//         return X * Y;
//     else
//     {
//         int xn0 = xn / 2, yn0 = yn / 2;
//         int xn1 = xn - xn0, yn1 = yn - yn0;
 
//         long A = (long)(X / pow(10, xn0));
//         long B = (long)(X % (long)pow(10, xn0));
//         long C = (long)(Y / pow(10, yn0));
//         long D = (long)(Y % (long)pow(10, yn0));
 
//         long AC = polyMult(A, C, xn1, yn1);
//         long BD = polyMult(B, D, xn0, yn0);
//         long ABCD = polyMult((long)(A * pow(10, xn0) - B), (long)(D - C * pow(10, yn0)), xn1, yn1);
 
//         return (long)(2 * AC * pow(10, (xn0 + yn0)) + ABCD + 2 * BD);
//     }
// }

// long polyMult(long a, long b, int n1, int n2) {

//     if(a == 0 || b == 0){
//         return 0;
//     }
//     else if(n1 == 1 || n2 == 1) {
//         return  a*b;
//     }
//     // a
//     else {
//         int n1_left = n1/2;
//         int n1_right = n1 - n1_left; 
//         int n2_left = n2/2;
//         int n2_right = n2 - n2_left; 
//         long a0 = (long)(a / pow(10.0, int(n1_left)));
//         long a1 = (long)(a % (long)pow(10.0, int(n1_left)));
//         // b
//         printf("a0 = %d", a0);

//         long b0 = (long)(b / pow(10.0, int(n2_left)));
//         long b1 = (long)(b % (long)pow(10.0, int(n2_left)));
//         printf("b0 = %d", b0);
//         long a0_b0 = polyMult(a0, b0, n1_right, n2_right);
//         long a1_b1 = polyMult(a1, b1, n1_left, n2_left);

//         long a0a1_b0b1 = polyMult((long)(a0* pow(10, n1_left) - a1), (long)(b1 - b0 * pow(10, n2_left)), n1_right, n2_right);
//         //printf("a0a1_b0b1 = %d \t", a0a1_b0b1);
//         return (long)(2 * a0_b0 * pow(10, (n1_left+n2_left)) + a0a1_b0b1 + 2 * a1_b1);  
//     }
// }

long polyMult(long a, long b, int n1, int n2) {

    if(a == 0 || b == 0){
        return 0;
    }
    else if(n1 == 1 || n2 == 1) {
        return  a*b;
    }
    // a
    else {
        int n1_left = n1/2;
        int n1_right = n1 - n1_left; 
        int n2_left = n2/2;
        int n2_right = n2 - n2_left; 
        long a0 = (long)(a / pow(10.0, int(n1_left)));
        long a1 = (long)(a % (long)pow(10.0, int(n1_left)));
        // b
        printf(" a0 = %d ", a0);

        long b0 = (long)(b / pow(10.0, int(n2_left)));
        long b1 = (long)(b % (long)pow(10.0, int(n2_left)));
        printf(" b0 = %d ", b0);
        long a0_b0 = polyMult(a0, b0, n1_left, n2_left);
        long a1_b1 = polyMult(a1, b1, n1_right, n2_right);

        // Method 1:
        // long a0a1_b0b1 = polyMult((long)(a0* pow(10, n1_left) - a1), (long)(b1 - b0 * pow(10, n2_left)), n1_right, n2_right);
        // return (long)(2 * a0_b0 * pow(10, (n1_left+n2_left)) + a0a1_b0b1 + 2 * a1_b1);  
        
        // Method 2:
        long a0a1_b0b1 = polyMult((long)(a0 + a1), (long)(b1 + b0), n1_right, n2_right);
        //printf("a0a1_b0b1 = %d \t", a0a1_b0b1);
        return (long)(a0_b0*pow(10, (n1_left+n2_left)) + (a0a1_b0b1-a0_b0-a1_b1)*pow(10, n1_left) + a1_b1);  
    }
}