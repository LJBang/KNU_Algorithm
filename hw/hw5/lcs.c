// 2015112525
// Lee Joon-Byeong

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int max_n(int a, int b){
    if(a>=b) return a;
    else return b;
}

int main(){
    char *A= (char*)malloc(sizeof(char) * 50);
    char *B= (char*)malloc(sizeof(char) * 50);
    char *L= (char*)malloc(sizeof(char) * 50);
    int A_s, B_s, LCS_s=0, i, j;

    fscanf(stdin,"%s",A);
    A_s = strlen(A)+1;

    fscanf(stdin,"%s",B);
    B_s = strlen(B)+1;


    int mat[A_s][B_s];

    // LCS Length Algorithm
    for(i=0; i<A_s; i++){
        for(j=0; j<B_s; j++){
            if(i==0 || j==0){
                mat[i][j]=0;
            }
            else if(A[i-1]==B[j-1]){
                mat[i][j]=mat[i-1][j-1]+1;
            }
            else{
                mat[i][j]=1;
                mat[i][j]=max_n(mat[i-1][j],mat[i][j-1]);
            }
        }
    }

    i--;
    j--;
    int k= mat[i][j];
    L[k]='\0';
    k--;

    while(1){
        if(i==0 || j==0) break;

        else if(mat[i][j]==mat[i-1][j]){
            i--;
        }
        else if(mat[i][j]==mat[i][j-1]){
            j--;
        }
        else if(mat[i][j]==mat[i-1][j-1]+1){
            L[k]=A[i-1];
            k--;
            i--;
            j--;
        }
    }

    //print part
    printf("LCS: %s\n    ",L);
    for(int i=0;i<B_s;i++){
        printf("%c ",B[i]);
    }
    printf("\n");
    for(int i=0;i<A_s;i++){
        if(i==0)
            printf("  ");
        else
            printf("%c ",A[i-1]);
        for(int j=0; j<B_s; j++){
            printf("%d ",mat[i][j]);
        }
        printf("\n");
    }

    free(A);
    free(B);
    free(L);
    return 0;
}
