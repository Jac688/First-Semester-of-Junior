#include <stdio.h>
#include <string.h>
int LCS( char *str1, char *str2, int len1, int len2 ) {
    int d[len1+1][len2+1];
    for (int i = 0; i <= len1; i++) {
        for (int j = 0; j <= len2; j++) {
            if (i == 0 || j == 0)
                d[i][j] = 0;
            else if (str1[i-1] == str2[j-1])
                d[i][j] = d[i-1][j-1] + 1;
            else
                d[i][j] = (d[i-1][j] > d[i][j-1]) ? d[i-1][j]: d[i][j-1];
        }
    }
    return d[len1][len2];
}
int main() {
    char str1[100];
    char str2[100];
    printf("Please input the first string: ");
    scanf("%s", str1);
    printf("Please input the first string: ");
    scanf("%s", str2);
    printf("Length of LCS is %d", LCS(str1, str2, strlen(str1), strlen(str2)));
    return 0;
}