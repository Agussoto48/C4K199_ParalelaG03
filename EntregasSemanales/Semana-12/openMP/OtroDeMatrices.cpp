#include <stdio.h>
#include <stdlib.h>
#include<omp.h>

/* Global variables */
int thread_count;
int m, n;
double *A;
double *x;
double *y;

/* Serial functions */
void Usage(char *prog_name);
void Read_matrix(char *prompt, double A[], int m, int n);
void Read_vector(char *prompt, double x[], int n);
void Print_matrix(char *title, double A[], int m, int n);
void Print_vector(char *title, double y[], double m);

/* Parallel function */
void Pth_mat_vect(int rank);

/*------------------------------------------------------------------*/
int main(int argc, char *argv[])
{
    long thread;
    pthread_t *thread_handles;

    if (argc != 2)
        Usage(argv[0]);
    thread_count = atoi(argv[1]);
    thread_handles = new pthread_t[thread_count];
    

    printf("Enter m and n\n");
    scanf("%d%d", &m, &n);

    A = new double[m*n];
    x = new double[n];
    y = new double[m];

    Read_matrix("Enter the matrix", A, m, n);
    Print_matrix("We read", A, m, n);

    Read_vector("Enter the vector", x, n);
    Print_vector("We read", x, n);

    
    Pth_mat_vect(thread);
    
    
    // for (thread = 0; thread < thread_count; thread++)
    //     pthread_create(&thread_handles[thread], NULL, Pth_mat_vect, (void *)thread);

    // for (thread = 0; thread < thread_count; thread++)
    //     pthread_join(thread_handles[thread], NULL);

    Print_vector("The product is", y, m);

    delete[] A;
    delete x;
    delete y;
    delete[] thread_handles;

    return 0;
} /* main */

void Usage(char *prog_name)
{
    fprintf(stderr, "usage: %s <thread_count>\n", prog_name);
    exit(0);
}

void Read_matrix(char *prompt, double A[], int m, int n)
{
    int i, j;

    printf("%s\n", prompt);
    for (i = 0; i < m; i++)
        for (j = 0; j < n; j++)
            scanf("%lf", &A[i * n + j]);
} 


void Read_vector(char *prompt, double x[], int n)
{
    int i;

    printf("%s\n", prompt);
    for (i = 0; i < n; i++)
        scanf("%lf", &x[i]);
} 

void Pth_mat_vect(int rank)
{
    int i, j;

    #pragma omp parallel for private(i, j) shared(A, y, x, m)
    for (i = 0; i <= m; i++)
    {
        y[i] = 0.0;
        for (j = 0; j < n; j++)
            y[i] += A[i * n + j] * x[j];
    }
}


void Print_matrix(char *title, double A[], int m, int n)
{
    int i, j;

    printf("%s\n", title);
    for (i = 0; i < m; i++)
    {
        for (j = 0; j < n; j++)
            printf("%4.1f ", A[i * n + j]);
        printf("\n");
    }
} 


void Print_vector(char *title, double y[], double m)
{
    int i;

    printf("%s\n", title);
    for (i = 0; i < m; i++)
        printf("%4.1f ", y[i]);
    printf("\n");
}
