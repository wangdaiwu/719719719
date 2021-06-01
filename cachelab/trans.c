/* 
 * trans.c - Matrix transpose B = A^T
 *
 * Each transpose function must have a prototype of the form:
 * void trans(int M, int N, int A[N][M], int B[M][N]);
 *
 * A transpose function is evaluated by counting the number of misses
 * on a 1KB direct mapped cache with a block size of 32 bytes.
 */ 
#include <stdio.h>
#include "cachelab.h"

int is_transpose(int M, int N, int A[N][M], int B[M][N]);

/* 
 * transpose_submit - This is the solution transpose function that you
 *     will be graded on for Part B of the assignment. Do not change
 *     the description string "Transpose submission", as the driver
 *     searches for that string to identify the transpose function to
 *     be graded. 
 */
char transpose_submit_desc[] = "Transpose submission";
void transpose_submit(int M, int N, int A[N][M], int B[M][N]) {
    if (N==67&&M==61){
        int i, j, k,r;
        for(i=0;i<N;i+=23){
            for(j=0;j<M;j+=23){
                for(k=i;k<N&&k<i+23;k++){
                    for(r=j;r<M&&r<j+23;r++){
                        B[r][k]=A[k][r];
                    }
                }
            }
        }
    }
    else if(N==32&&M==32){
        int i, j, k;
        for (i = 0; i < N; i+=8) {
            for (j = 0; j < M; j+=8) {
                for(k=0;k<8;k++){
                    int temp0= A[i+k][j];        
                    int temp1= A[i+k][j+1];
                    int temp2= A[i+k][j+2];
                    int temp3= A[i+k][j+3];
                    int temp4= A[i+k][j+4];           
                    int temp5= A[i+k][j+5];
                    int temp6= A[i+k][j+6];
                    int temp7= A[i+k][j+7];
                    B[j][i+k] = temp0;  
                    B[j+1][i+k] = temp1; 
                    B[j+2][i+k] = temp2;
                    B[j+3][i+k] = temp3;
                    B[j+4][i+k] = temp4;
                    B[j+5][i+k] = temp5;  
                    B[j+6][i+k] = temp6;
                    B[j+7][i+k] = temp7;      
                }
            }
        }
    }
    else{
        int i, j, k;
        for (i = 0; i < N; i+=8) {
            for (j = 0; j < M; j+=8) {
                int a0,a1,a2,a3,a4,a5,a6,a7;
                for(k=i;k<i+4;k++){     //转置第一个块，将A第二个块转置到B的第二个块
                    a0=A[k][j];   a1=A[k][j+1]; a2=A[k][j+2]; a3=A[k][j+3];
                    a4=A[k][j+4]; a5=A[k][j+5]; a6=A[k][j+6]; a7=A[k][j+7];
                    B[j][k]=a0;   B[j+1][k]=a1;   B[j+2][k]=a2;   B[j+3][k]=a3;
                    B[j][k+4]=a4; B[j+1][k+4]=a5; B[j+2][k+4]=a6; B[j+3][k+4]=a7;
                }
                for(k=j;k<j+4;k++){     //将第三块转置到B的第二块，B的第二块平移到第三块
                    a0=A[i+4][k]; a1=A[i+5][k]; a2=A[i+6][k]; a3=A[i+7][k];
                    a4=B[k][i+4]; a5=B[k][i+5]; a6=B[k][i+6]; a7=B[k][i+7];
                    B[k][i+4]=a0; B[k][i+5]=a1;   B[k][i+6]=a2;   B[k][i+7]=a3;
                    B[k+4][i]=a4; B[k+4][i+1]=a5; B[k+4][i+2]=a6; B[k+4][i+3]=a7; 
                }
                for(k=i+4;k<i+8;k++){       //处理最后一块，将A的第四块转置到B的第四块
                    a0=A[k][j+4]; a1=A[k][j+5]; a2=A[k][j+6]; a3=A[k][j+7];
                    B[j+4][k]=a0; B[j+5][k]=a1; B[j+6][k]=a2; B[j+7][k]=a3;
                }
            }
        }
    }
}

/* 
 * You can define additional transpose functions below. We've defined
 * a simple one below to help you get started. 
 */ 


/* 
 * trans - A simple baseline transpose function, not optimized for the cache.
 */
char trans_desc[] = "Simple row-wise scan transpose";
void trans(int M, int N, int A[N][M], int B[M][N])
{
    int i, j, tmp;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; j++) {
            tmp = A[i][j];
            B[j][i] = tmp;
        }
    }    

}

/*
 * registerFunctions - This function registers your transpose
 *     functions with the driver.  At runtime, the driver will
 *     evaluate each of the registered functions and summarize their
 *     performance. This is a handy way to experiment with different
 *     transpose strategies.
 */
void registerFunctions()
{
    /* Register your solution function */
    registerTransFunction(transpose_submit, transpose_submit_desc); 

    /* Register any additional transpose functions */
    registerTransFunction(trans, trans_desc); 

}

/* 
 * is_transpose - This helper function checks if B is the transpose of
 *     A. You can check the correctness of your transpose by calling
 *     it before returning from the transpose function.
 */
int is_transpose(int M, int N, int A[N][M], int B[M][N])
{
    int i, j;

    for (i = 0; i < N; i++) {
        for (j = 0; j < M; ++j) {
            if (A[i][j] != B[j][i]) {
                return 0;
            }
        }
    }
    return 1;
}

