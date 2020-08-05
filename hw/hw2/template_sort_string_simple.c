/* ID: 2015112525
 * Name: Lee Joon Byeong
 * School of Electronics Engineering, Kyungpook National University
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>	// string library

// struct to store string
#define MAX_STR_LEN	256
struct String {
  char s[MAX_STR_LEN];	// for simplicity, the maximum length is fixed
};

/////////////////////////////////////////////////////////////
// print string array
/////////////////////////////////////////////////////////////
void print_string_array( FILE *fp, struct String A[], int N )
  // A[]: struct String array to print
  // N:   size of the array
  // fp:  file pointer, stdout or stderr for screen display
{
  int i;
  fprintf(fp,"%d\n",N);
  for (i=0; i<N; i++) fprintf(fp,"%s ",A[i].s);
  fprintf(fp,"\n");
}

/////////////////////////////////////////////////////////////
// read words from a text file
/////////////////////////////////////////////////////////////
struct String *read_string_textfile( const char infile[], int *pN )
  // returns an array of words, with its size stored in
  // the memory indicated by integer pointer variable pN
  // the retured memory should freed by the caller
{
  struct String *A;
  char tmp[MAX_STR_LEN];
  int i;
  FILE *fp;

  // check for input file name
  if ( infile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return NULL;
  }

  // check for file existence
  fp = fopen(infile,"r");
  if ( !fp ) {
    fprintf(stderr, "cannot open file %s\n",infile);
    return NULL;
  }
  else {
    // check for number of elements
    if ( fscanf(fp, "%d", pN) != 1 || *pN <= 0 ) {
      fprintf(stderr, "cannot read number of elements %s\n",infile);
      return NULL;
    }
    else {
      A = (struct String*)malloc(sizeof(struct String)*(*pN));
      for (i=0; i<(*pN); i++) {
	if ( fscanf(fp, "%s", tmp) != 1 ) {
	  fprintf(stderr, "cannot read value at %d/%d\n",i+1,(*pN));
	  *pN = i;	// read data items
	  return A;
	}
	else strcpy(A[i].s, tmp);
      }
    }
    fclose(fp);
    return A;
  }
}

/////////////////////////////////////////////////////////////
// write words to a text file
/////////////////////////////////////////////////////////////
void write_string_textfile( const char outfile[], struct String A[], int N )
  // write the given array of int string words, with its sie N
  // to file whose name given by outfile[]
  // uses print_string_array
{
  FILE *fp;

  // check for output filename
  if ( outfile == NULL ) {
    fprintf(stderr, "NULL file name\n");
    return;
  }

  // check for file existence
  fp = fopen(outfile,"w");
  if ( !fp ) {
    fprintf(stderr, "cannot open file for write %s\n",outfile);
  }
  else {
    print_string_array(fp,A,N);
    fclose(fp);
  }
}

/////////////////////////////////////////////////////////////
// insertion sort
/////////////////////////////////////////////////////////////
void insertion_sort_string ( struct String arr[], int n ) {
    char tmp[256];
    for(int i=1;i<n;i++){
    strcpy(tmp,arr[i].s);
    for(int j=0;j<i;j++){
        if(strcmp(tmp,arr[j].s)<0){
            for(int k=i;k>j;k--){
                strcpy(arr[k].s,arr[k-1].s);
            }
            strcpy(arr[j].s,tmp);
            break;
        }
    }
  }
}

/////////////////////////////////////////////////////////////
// selection sort
/////////////////////////////////////////////////////////////
void selection_sort_string(struct String arr[], const int n) {
  char temp[256],min[256];
  int index;
  for(int i=0;i<n;i++){
    strcpy(min,arr[i].s);
    for(int j=i+1;j<n;j++){
        if(strcmp(min,arr[j].s)>0){
            strcpy(min,arr[j].s);
            index=j;
        }
    }
    strcpy(temp,arr[i].s);
    strcpy(arr[i].s,arr[index].s);
    strcpy(arr[index].s,temp);
  }
}

/////////////////////////////////////////////////////////////
// bubble sort
/////////////////////////////////////////////////////////////
void bubble_sort_string(struct String arr[], int n) {
  /* sample reference
   * source: https://ko.wikipedia.org/ modified for char array string */
  int i, j;
  char temp[MAX_STR_LEN];
  for (i=n-1; i>0; i--) {
    for (j=0; j<i; j++) {\
      if (strcmp(arr[j].s, arr[j+1].s) > 0 ) {
        strcpy(temp, arr[j].s);
        strcpy(arr[j].s, arr[j+1].s);
        strcpy(arr[j+1].s, temp);
      }
    }
  }
}


/////////////////////////////////////////////////////////////
// main function
/////////////////////////////////////////////////////////////
int main()
  /* Input file name by scanf read, typed in the terminal */
{
  int numElements;
  struct String *A;	// to store data to be sorted

  /* for file name, max length 1023 including path */
  char infile[1024], outfile[1024];
  int method;	// which sorting method

  /* file name given by keyboard */
  printf("Input file name? ");
  scanf("%s",infile);
  printf("Output file name? ");
  scanf("%s",outfile);

  printf("Method (1: insertion, 2: selection, 3: bubble)? ");
  scanf("%d",&method);

  /* read text file of words:
   * number_of_intergers word1 word2 ... */
  A = read_string_textfile(infile, &numElements);

  if ( A != NULL && numElements > 0 ) {
    switch ( method ) {
      case 1:	// insertion sort
	//insertion_sort(A, numElements);
	insertion_sort_string(A, numElements);
	break;
      case 2:	// selection sort
	//selection_sort(A, numElements);
	selection_sort_string(A, numElements);
	break;
      case 3:	// bubble sort
	//bubble_sort(A, numElements);
	bubble_sort_string(A, numElements);
	break;
      default:
	break;
    }

    // save results
    write_string_textfile(outfile, A, numElements);

    // once allocated, should be freed after use
    free(A);
  }

  return 0;
}

