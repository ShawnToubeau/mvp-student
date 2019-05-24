double *allocVec(int n);

double **allocMat(int n);

void assignVec(int n, double *vector);

void assign1dMat(int n, double *matrix);

void assign2dMat(int n, double **matrix);

double *mvp1(double *mat, double *vec, int n);

double *mvp2(double **mat, double *vec, int n);

void print1dMatVec(int n, double *vec, double *mat, double *sol);

void print2dMatVec(int n, double *vec, double **mat, double *sol);

void free1dMat(double *matrix);

void free2dMat(int n, double **matrix);