#include<stdio.h>
int MaxSum(int A[], int left, int right);

int main(){
    int A[] = {3, -9, 5, 6, -2, 8, 7, -4, -8, 4};
    int left = 0;
    int right = 9;

    int result = MaxSum(A, left, right);

    printf("The MSC of this sequence is: %d", result);
    return 0;
}

int MaxSum(int *A, int left, int right){
    int maxLeftSum;
    int maxRightSum;
    int maxLeftBorderSum = 0, maxRightBorderSum = 0;
    int leftSum = 0;
    int rightSum = 0;
    if (left >= right) {
        return A[left];
    }

    int middle = (left+right) / 2;
    maxLeftSum = MaxSum(A, left, middle);
    maxRightSum = MaxSum(A, middle + 1, right);

    for(int i = middle; i >= left; i--) {
        leftSum += A[i];
        if (leftSum > maxLeftSum) {
            maxLeftBorderSum = leftSum;
        }
    }
    
    for(int i = middle + 1; i <= right; i++) {
        rightSum += A[i];
        if (rightSum > maxRightBorderSum) {
            maxRightBorderSum = rightSum;
        }
    }
    int maxMiddleSum = maxLeftBorderSum + maxRightBorderSum;
    if(maxLeftBorderSum > maxRightBorderSum) {
        if(maxLeftBorderSum > maxMiddleSum){
            printf("");
            return maxLeftBorderSum;
        }
    }
    else if(maxMiddleSum > maxLeftBorderSum) {
        if(maxMiddleSum > maxRightBorderSum){
            return maxMiddleSum;
        }
    }
    else {
        return maxRightBorderSum;
    }
    return maxRightBorderSum;
}
// #include<stdio.h>
// int mid_MCS(int *a,int left, int right);
// int MCS(int *a,int left, int right);

// int main(){
//  int a[7]={1,-1,9,10,-10,32,-34};
 /*
 for(int i = 0;i<7;i++){
  printf("%d\n",a[i]);
 }
 */
//  int max = MCS(a,0,6);
//  printf("答案是：%d\n",max);
// }


// int mid_MCS(int *a,int left, int right){
//  if(left>=right)
//   return a[left];

//  int mid_place=(left+right)/2;
//  int leftF = 0;
//  int rightF = 0;
//  int l_max = -999;
//  int r_max = -999;

//  for(int i = mid_place;i>=left;i--){
//   leftF+=a[i];
//   if(l_max<leftF)
//    l_max=leftF;
//  }

//  for(int i = mid_place+1;i<=right;i++){
//   rightF+=a[i];
//   if(r_max<rightF)
//    r_max=rightF;
//  }
//  return r_max+l_max;
// }

// int MCS(int *a,int left, int right){
//  if(left>=right)
//   return a[left];
//  int mid_place = (left+right)/2;
//  int left_max = MCS(a,left,mid_place);
//  int right_max = MCS(a,mid_place+1,right);
//  int mid_max = mid_MCS(a,left,right);
//  int max = left_max;
//  if(right_max>max)
//   max=right_max;
//  if(mid_max>max)
//   max=mid_max;
//  return max;
// }