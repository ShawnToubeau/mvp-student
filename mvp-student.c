#include <stdio.h>
#include <stdlib.h>

/*
Function prototypes for the matrix vector product.
You MUST implement both of these functions
in addition to the others listed in the PDF
*/

void free1dMat(double *matrix)
{
  free(matrix);
}

void free2dMat(int n, double **matrix)
{
  for (int i = 0; i < n; i++)
  {
    free(matrix[i]);
  }
  free(matrix);
}

void assign1dMat(int n, double *matrix)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int index = i + (n * j);

      if (i == j)
      {
        matrix[index] = 2.0;
      }
      else if (i - j == 1 || i - j == -1)
      {
        matrix[index] = 1.0;
      }
      else
      {
        matrix[index] = 0.0;
      }
    }
  }
}

void assign2dMat(int n, double **matrix)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      if (i == j)
      {
        matrix[i][j] = 2.0;
      }
      else if (i - j == 1 || i - j == -1)
      {
        matrix[i][j] = 1.0;
      }
      else
      {
        matrix[i][j] = 0.0;
      }
    }
  }
}

void assignVec(int n, double *vector)
{
  for (int i = 0; i < n; i++)
  {
    vector[i] = 1.0;
  }
}

void print1dMatVec(int n, double *vec, double *mat, double *sol)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      int index = i + (n * j);

      printf("%f ", mat[index]);
    }
    if (i == n / 2)
    {
      printf("* %f = %f\n", vec[i], sol[i]);
    }
    else
    {
      printf("  %f   %f\n", vec[i], sol[i]);
    }
  }
  printf("\n");
}

void print2dMatVec(int n, double *vec, double **mat, double *sol)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%f ", mat[i][j]);
    }
    if (i == n / 2)
    {
      printf("* %f = %f\n", vec[i], sol[i]);
    }
    else
    {
      printf("  %f   %f\n", vec[i], sol[i]);
    }
  }
}

double *allocVec(int n)
{
  double *vector = (double *)malloc(n * sizeof(double));
  return vector;
}

double **allocMat(int n)
{
  double **matrix = (double **)malloc(n * sizeof(double *));
  for (int i = 0; i < n; i++)
  {
    matrix[i] = (double *)malloc(n * sizeof(double));
  }
  return matrix;
}

double *mvp1(double *mat, double *vec, int n)
{
  double *solution = allocVec(n);

  for (int i = 0; i < n; i++)
  {
    double row = 0.0;
    for (int j = 0; j < n; j++)
    {
      int index = i + (n * j);
      row += mat[index] * vec[j];
    }
    solution[i] = row;
  }

  return solution;
};

double *mvp2(double **mat, double *vec, int n)
{
  double *solution = allocVec(n);

  for (int i = 0; i < n; i++)
  {
    double row = 0.0;
    for (int j = 0; j < n; j++)
    {
      row += mat[i][j] * vec[j];
    }
    solution[i] = row;
  }

  return solution;
}

//Main function
int main(int argc, char **argv)
{
  int n;

  printf("Enter a size for the matrix/vector:\n");
  scanf("%d", &n);

  double *vec = allocVec(n);
  double *mat1 = allocVec(n * n);
  double **mat2 = allocMat(n);

  assignVec(n, vec);
  assign1dMat(n, mat1);
  assign2dMat(n, mat2);

  double *sol1 = mvp1(mat1, vec, n);
  double *sol2 = mvp2(mat2, vec, n);

  print1dMatVec(n, vec, mat1, sol1);
  print2dMatVec(n, vec, mat2, sol2);

  free1dMat(mat1);
  free2dMat(n, mat2);

  return 0;
}
