#include <stdlib.h>
#include <stdio.h>
#include <string.h>
void setZeroes(int** matrix, int matrixSize, int* matrixColSize){
    int *m = (int *)malloc(sizeof(int) * matrixSize);
    int *n = (int *)malloc(sizeof(int) * matrixColSize[0]);
    int i  = 0, j = 0;
    for(i = 0; i < matrixSize; i++)
    {
           m[i] = 0;
    }
    for(j =0; j < matrixColSize[0]; i++)
    {
        n[j] = 0;
    }
    for(i = 0; i< matrixSize; i++)
    {
        for(j = 0; j < matrixColSize[0]; j++)
        {
           if(matrix[i][j] == 0)
           {
               m[i] = n[j] = 1;
           }

        }
    }
    for(i = 0; i < matrixSize; i++)
    {
        if(m[i])
        {
            for(j = 0; j < matrixColSize[0]; j++)
            {
                matrix[i][j] = 0;
            }
        }
    }
    for(j = 0; j < matrixColSize[0]; j++)
    {
        if(n[j])
        {
            for(i = 0; i < matrixSize; i++)
            {
                matrix[i][j] = 0;
            }
        }
    }
}
void main()
{
    int matrixSize = 2;
    int matrixColSize = 1;
    int arr[2][1] = {{0},{1}};
    int *p1 = arr[0];
    int *p2 = arr[1];
    int *p3 = arr[2];
    int *ap[] = {p1,p2,p3};
    int **p_lv2 = ap;
    int i = 0, j = 0;

    //
    int *tap[3] = {arr[0],arr[1],arr[2]};
    //int *tap1[3] = arr;
    setZeroes(ap,matrixSize,&matrixColSize);
    for(i = 0; i < matrixSize; i++)
    {
        for(j = 0; j < matrixColSize; j++)
        {
            printf("ap[%d][%d] = %d\t", i, j, ap[i][j]);
        }
        printf("\n");
    }

    getchar();
}