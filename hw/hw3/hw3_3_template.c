/* ID 2015112525        - REPLACE WITH YOUR ID
 * NAME Lee Joon Byeong       - REPLACE WITH YOUR NAME */

//////////////////////////////////////////////////////////////////
// If you have referred any code, leave the comments like this
// to avoid "COPY"
// SOURCE for heapify: https://www.geeksforgeeks.org/heap-sort/
///////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MEASURE_TIME	// to measure execution time
// from GJANG: not sure if the time measurement code works with Windows
// If it works, execution time will be printed.
// Otherwise, comment out the line "#define MEASURE_TIME" and compile again.

/////////////////////////////////////////////////////////////////////
// to compute execution time in seconds
/////////////////////////////////////////////////////////////////////
#ifdef MEASURE_TIME
#include<time.h>
#endif

/////////////////////////////////////////////////////////////////////
// homework programming assignment 3-3
/////////////////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////////////
// function to find median using min heap and max heap
// to find median value from an array, use the following heap architecture
// 1) store all the data to heap L and heap R
// 2) all values in L < any value in R
// 3) if the number of total items is N,
//   odd  N: number of items in L = N/2+1, number of items in R = N/2
//   even N: number of items in L = number of items in R = N/2
//     i.e. n_L = n_R or n_L = n_R+1
// 4) keep L as max heap, keep R as min heap, then the median is root(L)
//   *in many definitions of median, when N is even, the median is
//    defined as an average of item N/2 and item N/2+1, but we assume
//    it is root(L) (item ceiling(N/2)) to make the problem simple
//   *all values in L <= root(L), so it also satisfies definition of median
//   *Reference:
// https://www.quora.com/How-do-you-find-the-median-from-a-set-of-even-numbers
// https://www.dkfindout.com/us/math/averages/more-about-medians/
//
// What to do:
// 1) Implement
//    Heap4Median_AddItem(int L[], int *p_n_L, int R[], int *p_n_R, int value)
//    to add a value to L and R
//    heaps L and R should satisfy the above conditions
// 2) Implement
//    Heap4Median_Build(int A[], int N, int L[], int *p_n_L, int R[], int *p_n_R)
//    For an unsorted array, it builds heaps L and R from empty heaps
//    A: size N array
//    L: size ceil(N/2) array,  R: size floor(N/2) array
//    the array memory should be allocated in advance
// 3) Implement
//    Heap4Median_Sort(int L[], int n_L, int R[], int n_R, int A[], int p_N)
//    For Heap4Median given by L and R (with their number of elements by n_L and n_R)
//    fill the array A in an ascending order
///////////////////////////////////////////////////////////////////

/////////////////////////////////////////////////////////////////////
void swap(int *a, int *b){
    int temp;
    temp=*a;
    *a=*b;
    *b=temp;
}

void MaxHeapifyUp(int A[],int n){
    int temp;
    if (n != 1 && A[n] > A[n/2]){
        temp=A[n];
        A[n]=A[n/2];
        A[n/2]=temp;
        MaxHeapifyUp(A,n/2);
    }
}
void MinHeapifyUp(int A[],int n){
    int temp;
    if (n != 1 && A[n] < A[n/2]){
        temp=A[n];
        A[n]=A[n/2];
        A[n/2]=temp;
        MinHeapifyUp(A,n/2);
    }
}
/////////////////////////////////////////////////////////////////////
int L_i=1, R_i=1;

void Heap4Median_AddItem(int L[], int *p_n_L, int R[], int *p_n_R, int value)
{
    L[L_i]=value;
    for(int i=L_i;i>0;i--){
        MaxHeapifyUp(L, i);
    }
    if(L_i>*p_n_L){
        R[R_i]=L[1];
        MinHeapifyUp(R,R_i);
        R_i++;

        swap(&L[1],&L[L_i]);
        L_i--;
    }

    for(int i=L_i;i>0;i--){
        MaxHeapifyUp(L, i);
    }

    MaxHeapifyUp(L, L_i);

    L_i++;
}

void Heap4Median_Build(int A[], int N, int L[], int *p_n_L, int R[], int *p_n_R)
{
    *p_n_L=(N+1)/2;
    *p_n_R=N/2;

    for(int i=1;i<=N;i++){
        Heap4Median_AddItem(L,p_n_L,R,p_n_R,A[i]);
    }
}

void Heap4Median_Sort(int L[], int n_L, int R[], int n_R, int A[], int *p_N)
{
    int L_s=n_L, R_s=n_R,k=1;

    for(int i=L_s;i>0;i--){
        A[i]=L[1];
        swap(&L[1],&L[i]);
        n_L--;
        for(int j=n_L;j>0;j--){
            MaxHeapifyUp(L, j);
        }
    }
    for(int i=L_s+1;i<=L_s+R_s;i++){
        A[i]=R[1];
        swap(&R[1],&R[n_R]);
        n_R--;
        for(int j=n_R;j>0;j--){
            MinHeapifyUp(R, j);
        }
        k+=2;
    }
}

/////////////////////////////////////////////////////////////////////
// test your implementation
/////////////////////////////////////////////////////////////////////
int main()
{
  int i, N;
  int *A, *L, *R;
  int n_L, n_R;

  // 0. read input
  fscanf(stdin, "%d", &N);

  // allocate interger arrays and read input values
  // In the textbook, the array indexing is 1-based (i.e. starts with 1)
  // so this template code is written for 1-based indexing
  // (starts with 1, leaving A[0] untouched.
  // If you prefer 0-based indexing, you may modify the example code below
  // ex.) "for (i=1; i<=N; i++) " --> "for (i=0; i<N; i++) "
  // "median = L[1]; " --> "median = L[0]; "
  A = (int*)malloc(sizeof(int)*(N+1));
  for (i=1; i<=N; i++) {
    if ( fscanf(stdin, "%d", A+i) != 1 ) {
      fprintf(stderr, "cannot read integer from standard input.\n");
      free(A);
      exit(0);
    }
  }

  L = (int*)malloc(sizeof(int)*(N/2+1+1));
  R = (int*)malloc(sizeof(int)*(N/2+1+1));

#ifdef MEASURE_TIME
  clock_t start, end;
  double cpu_time_used;

  start = clock();
#endif
  /////////////////////////////////////////////////////////////////////
  // ***FILL*** :  invoke Heap4Median_Build(...) to obtain sub-heaps L and R
  /////////////////////////////////////////////////////////////////////
  Heap4Median_Build(A, N, L, &n_L, R, &n_R);

  // output for evaluation: print median only
  fprintf(stdout,"%d\n",L[1]);

  Heap4Median_Sort(L, n_L, R, n_R, A, &N);

#ifdef MEASURE_TIME
  end = clock();
  cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;
  fprintf(stderr,">> Execution time: %.5f seconds\n",cpu_time_used);
#endif

  // output for evaluation: sorted list
  for (i=1; i<=N; i++) fprintf(stdout, "%d ", A[i]);
  fprintf(stdout, "\n");

  // free memory
  free(A);
  free(L);
  free(R);

  return 0;
}

