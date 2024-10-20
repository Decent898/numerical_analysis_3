#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int N;

// 打印矩阵
void printMatrix(double matrix[N + 1][N + 2])
{
    printf("┌───");

    for (int j = 1; j <= N; j++)
        printf("───────────────");
    printf("┬────────────────┐\n");

    for (int i = 1; i <= N; i++)
    {
        printf("│");
        for (int j = 1; j <= N; j++)
        {
            printf("%15.8f ", matrix[i][j]);
        }
        printf("│%15.8f │\n", matrix[i][N + 1]);

        if (i < N)
        {
            printf("├───");
            for (int j = 1; j <= N; j++)
                printf("───────────────");
            printf("┼────────────────┤\n");
        }
    }

    printf("└───");
    for (int j = 1; j <= N; j++)
        printf("───────────────");
    printf("┴────────────────┘\n");
}

// 高斯消元法
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

// crout
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

    int choice;
    printf("请选择消元法类型:\n");
    printf("1. 高斯消元法\n");
    printf("2. 克劳特消元法\n");
    scanf("%d", &choice);
    printf("请输入方程组的阶数 N: ");
    scanf("%d", &N);

    double matrix[N + 1][N + 2];
    double u[N + 1][N + 2];
    double l[N + 1][N + 2];

    memset(matrix, 0, sizeof(matrix));
    printf("请输入增广矩阵的系数 (每行元素用空格分开):\n");
    for (int i = 1; i <= N; i++)
    {
        for (int j = 1; j <= N + 1; j++)
        {
            scanf("%lf", &matrix[i][j]);
        }
    }

    double result[N];

    printf("\n初始矩阵:\n");
    printMatrix(matrix);
    
    if (choice == 1)
        gaussianSimplify(matrix, u, l);
    else if (choice == 2)
        croutSimplify(matrix, u, l);

    printf("\n上三角矩阵 U:\n");
    printMatrix(u);

    printf("\n下三角矩阵 L:\n");
    printMatrix(l);

    solve(u, result);

    printf("\n求解结果:\n");
    for (int i = 1; i <= N; i++)
    {
        printf("x%d = %.4f\n", i, result[i]);
    }

    return 0;
}
