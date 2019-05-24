#include "mvp-func.h"
#include <stdio.h>
#include <stdlib.h>

// Allocates space for the vector and 1D matrix
double *allocVec(int n)
{
  double *vector = (double *)malloc(n * sizeof(double));
  return vector;
}

// Allocates space for the 2D matrix
double **allocMat(int n)
{
  // Allocates the addresses for the pointers which will point
  // to the sub-arrays
  double **matrix = (double **)malloc(n * sizeof(double *));
  // Because we're working with a 2D matrix, we need to loop over the
  // already allocated pointer addresses and allocate the sub-arrays
  for (int i = 0; i < n; i++)
  {
    matrix[i] = (double *)malloc(n * sizeof(double));
  }
  return matrix;
}

// Populates the vector with all 1's
void assignVec(int n, double *vector)
{
  for (int i = 0; i < n; i++)
  {
    vector[i] = 1.0;
  }
}

// Populates the 1D matrix with 2's on the diagonal, 1's on
// the flank, and 0's everywhere else
void assign1dMat(int n, double *matrix)
{
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      // This allows us to access the indexes in the 1D matrix
      // even though we are treating it like a 2D matrix
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

// Populates the 2D matrix with 2's on the diagonal, 1's on
// the flank, and 0's everywhere else
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

// Calculates the dot product of the 1D matrix and the vector
double *mvp1(double *mat, double *vec, int n)
{
  // Solution vector
  double *solution = allocVec(n);

  for (int i = 0; i < n; i++)
  {
    // Stores the summed products of each row
    double row = 0.0;
    for (int j = 0; j < n; j++)
    {
      // This allows us to access the indexes in the 1D matrix
      // even though we are treating it like a 2D matrix
      int index = i + (n * j);
      row += mat[index] * vec[j];
    }
    solution[i] = row;
  }

  return solution;
};

// Calculates the dot product of the 2D matrix and the vector
double *mvp2(double **mat, double *vec, int n)
{
  double *solution = allocVec(n);

  for (int i = 0; i < n; i++)
  {
    // Storesthe summed products of each row
    double row = 0.0;
    for (int j = 0; j < n; j++)
    {
      row += mat[i][j] * vec[j];
    }
    solution[i] = row;
  }

  return solution;
}

// Prints the solution from the 1D matrix
void print1dMatVec(int n, double *vec, double *mat, double *sol)
{
  printf("-----Solution for MVP1-----\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      // This allows us to access the indexes in the 1D matrix
      // even though we are treating it like a 2D matrix
      int index = i + (n * j);

      printf("%f ", mat[index]);
    }
    // Conditional printing to add the '*' and '=' characters
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

// Prints the solution from the 2D matrix
void print2dMatVec(int n, double *vec, double **mat, double *sol)
{
  printf("-----Solution for MVP2-----\n");
  for (int i = 0; i < n; i++)
  {
    for (int j = 0; j < n; j++)
    {
      printf("%f ", mat[i][j]);
    }
    // Conditional printing to add the '*' and '=' characters
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

// Frees the memory of the 1D matrix
void free1dMat(double *matrix)
{
  free(matrix);
}

// Free the memory of the 2D matrix
void free2dMat(int n, double **matrix)
{
  // Loops over the pointers and frees the sub-arrays first
  for (int i = 0; i < n; i++)
  {
    free(matrix[i]);
  }
  // Then frees all the pointers
  free(matrix);
}

//Main function
int main(int argc, char **argv)
{
  if (!argv[1])
  {
    printf("Please supply a argument for n in the command line\n");
    return 0;
  }
  int n = atoi(argv[1]);

  //printf("Enter a size for the matrix/vector:\n");
  //scanf("%d", &n);
  //printf("\n");

  // Declarations + allocation
  double *vec = allocVec(n);
  double *mat1 = allocVec(n * n);
  double **mat2 = allocMat(n);

  // Population
  assignVec(n, vec);
  assign1dMat(n, mat1);
  assign2dMat(n, mat2);

  // Calculations
  double *sol1 = mvp1(mat1, vec, n);
  double *sol2 = mvp2(mat2, vec, n);

  // Printing
  print1dMatVec(n, vec, mat1, sol1);
  print2dMatVec(n, vec, mat2, sol2);

  // Free memory
  free1dMat(vec);
  free1dMat(mat1);
  free2dMat(n, mat2);
  free1dMat(sol1);
  free1dMat(sol2);

  return 0;
}
