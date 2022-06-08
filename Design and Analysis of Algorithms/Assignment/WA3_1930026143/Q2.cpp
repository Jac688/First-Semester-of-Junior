#include <stdio.h>
#include <string.h>
int LCS(char* str1, char* str2){
    int m = strlen(str1);
    int n = strlen(str2);  
    int d[m][n];
    int i_max = 0, p_max = 0;
    for (int i = 0; i < m; i++)
        d[i][0] = 0;
    for (int j = 0; j < n; j++)
        d[0][j] = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++){
            if (str1[i] != str2[j])
                d[i][j] = 0;
            else {
                d[i][j] = d[i-1][j-1]+1;
                if (d[i][j]>i_max){
                    i_max = d[i][j];
                    p_max = i;
                }
            }
        }
    }
    return i_max;
}
int main() {
    char str1[100];
    char str2[100];
    printf("Please input the first string: ");
    scanf("%s", str1);
    printf("Please input the first string: ");
    scanf("%s", str2);
    int res = LCS(str1, str2);
    printf("%d", res);
}