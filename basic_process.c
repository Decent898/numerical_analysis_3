#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

// #define N 3  // 方程组的变量个数
int N;

// 打印矩阵
void printMatrix(double matrix[N + 1][N + 2])
{
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N + 1; j++)
        {
            printf("%15.8f ", matrix[i][j]);
        }
        printf("\n");
    }
}

// 使用高斯消去法求解线性方程组
void gaussianSimplify(double matrix[N + 1][N + 2], double u[N + 1][N + 2], double l[N + 1][N + 2])
{
    int i, j, k;

    memset(l, 0, sizeof(double) * (N + 1) * (N + 1));

    for (i = 0; i <= N; i++)
    {
        for (j = 0; j <= N + 1; j++)
        {
            u[i][j] = matrix[i][j];
        }
    }

    for (i = 1; i <= N - 1; i++)
    {
        l[i][i] = 1;
        for (k = i + 1; k <= N; k++)
        {
            l[k][i] = u[k][i] / u[i][i];
            for (j = i; j <= N + 1; j++)
            {
                u[k][j] = u[k][j] - l[k][i] * u[i][j];
            }
        }
    }
    l[N][N] = 1;

    return;
}

void croutSimplify(double matrix[N + 1][N + 2], double u[N + 1][N + 2], double l[N + 1][N + 2])
{
    int i, j, k;

    memset(l, 0, sizeof(double) * (N + 1) * (N + 1));

    for (i = 0; i <= N; i++)
        for (j = 0; j <= N + 1; j++)
            u[i][j] = matrix[i][j];

    for (i = 1; i <= N; i++)
    {
        l[i][i] = u[i][i];
        for (j = i; j <= N + 1; j++)
        {
            u[i][j] = u[i][j] / l[i][i];
        }
        for (k = i + 1; k <= N; k++)
        {
            l[k][i] = u[k][i];

            for (j = i; j <= N + 1; j++)
            {
                u[k][j] = u[k][j] - l[k][i] * u[i][j];
            }
        }
    }

    return;
}

void solve(double u[N + 1][N + 2], double result[N])
{
    int i, j;
    for (i = N; i >= 1; i--)
    {
        result[i] = u[i][N + 1] / u[i][i];
        for (j = i + 1; j <= N; j++)
        {
            result[i] -= u[i][j] * result[j] / u[i][i];
        }
    }
}

int main()
{
    scanf("%d", &N);
    // 系数矩阵和常数项
    // double matrix[N][N + 1] = {
    //     {2, 1, -1, 8},
    //     {-3, -1, 2, -11},
    //     {-2, 1, 2, -3}
    // };
    double matrix[N + 1][N + 2];
    double u[N + 1][N + 2];
    double l[N + 1][N + 2];

    memset(matrix, 0, sizeof(matrix));
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N + 1; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }

    // 存放解的数组
    double result[N];

    printf("Initial augmented matrix:\n");
    printMatrix(matrix);

    gaussianSimplify(matrix, u, l);
    // croutSimplify(matrix, u, l);

    // result[N] = u[N][N + 1] / u[N][N];
    // 打印u
    printf("\nUpper triangular matrix:\n");
    int i, j;
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N + 1; j++)
        {
            printf("%15.8f ", u[i][j]);
        }
        printf("\n");
    }

    printf("\nLower triangular matrix:\n");
    for (i = 1; i <= N; i++)
    {
        for (j = 1; j <= N + 1; j++)
        {
            printf("%15.8f ", l[i][j]);
        }
        printf("\n");
    }

    solve(u, result);

    // 打印解
    printf("\nSolution:\n");
    for (int i = 1; i <= N; i++)
    {
        printf("x%d = %.4f\n", i, result[i]);
    }

    // 输出解
    // printf("\nSolution:\n");
    // for (int i = 1; i <= N; i++)
    // {
    //     printf("x%d = %.4f\n", i + 1, result[i]);
    // }

    return 0;
}
