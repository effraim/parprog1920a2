
// compile with e.g. gcc -O2 -Wall sorting-base.c -o sorting-base
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <stdbool.h>
#include <pthread.h>
#include <string.h>

#define THREAD_NUM 4
#define N 1000000
#define CREATE_LIMIT 10
#define MESSAGES (N/OFF)

// conditional variable(receiver waits on this)
pthread_cond_t msg_in = PTHREAD_INITIALIZE;

// conditional variable(sender waits on this)
pthread_cond_t msg_out = PTHREAD_INITIALIZE;

// mutex ελέγχει ποιό thread έχει access στην κοινή πληροφορία
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZE;

int maxcounter = 0;


typedef struct {
	Info array[MESSAGES];
  int flag;
	int qin, qout;//για το msg_in msg_out
	int count; //αριθμός μυνημάτων
  int start;
	int end;
}BUFFER;

BUFFER buffer;

int main() {
double *a;
int i;
counter = 0;

  a = (double *)malloc(N*sizeof(double));
  if (a==NULL) {
    printf("error in malloc\n");
    exit(1);
  }

  // fill array with random numbers
  srand(time(NULL));
  for (i=0;i<N;i++) {
    a[i] = (double)rand()/RAND_MAX;
  }

  fill_buffer();
  send_msg(buffer); // stelnoume to prwto message
  pthread_t threads[THREADS_NUM]; 
  
  // create threads
	for(i=0;i<THREADS_NUM;i++)
		pthread_create(&threads[i],NULL,start_thread,NULL);

  


	for(i=0;i<THREADS;i++)
		pthread_join(threads[i],NULL);
 

  // check sorting
  for (i=0;i<(N-1);i++) {
    if (a[i]>a[i+1]) {
      printf("Sort failed!\n");
      break;
    }
  }  

  free(a);
  
  	

  pthread_mutex_destroy(&mutex);
  free(a);
  return 0;
}


void inssort(double *a,int n) {
int i,j;
double t;
  
  for (i=1;i<n;i++) {
    j = i;
    while ((j>0) && (a[j-1]>a[j])) {
      t = a[j-1];  a[j-1] = a[j];  a[j] = t;
      j--;
    }
  }

}


int partition(double *a,int n) {
int first,last,middle;
double t,p;
int i,j;

  // take first, last and middle positions
  first = 0;
  middle = n/2;
  last = n-1;  
  
  // put median-of-3 in the middle
  if (a[middle]<a[first]) { t = a[middle]; a[middle] = a[first]; a[first] = t; }
  if (a[last]<a[middle]) { t = a[last]; a[last] = a[middle]; a[middle] = t; }
  if (a[middle]<a[first]) { t = a[middle]; a[middle] = a[first]; a[first] = t; }
    
  // partition (first and last are already in correct half)
  p = a[middle]; // pivot
  for (i=1,j=n-2;;i++,j--) {
    while (a[i]<p) i++;
    while (p<a[j]) j--;
    if (i>=j) break;

    t = a[i]; a[i] = a[j]; a[j] = t;      
  }
  
  // return position of pivot
  return i;
}


void quicksort(double *a,int n) {
int i;
  // check if below cutoff limit
  if (n<=CUTOFF) {
    inssort(a,n);
    return;
  }
  
  // partition into two halves
  i = partition(a,n);
   
  // recursively sort halves
  quicksort(a,i);
  quicksort(a+i,n-i);
  
}
