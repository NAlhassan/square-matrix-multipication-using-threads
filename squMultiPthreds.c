#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <time.h>


float *A, *B, *R;
int n;


void prnt(float * a){
  for(int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			printf("%f ",*(a + i*n + j));
		}
		printf("\n");
	}

  printf("************************\n\n");

}

void filling(float *a){
	srand(time(0));
	for (int i = 0; i < n; i++){
		for (int j = 0; j < n; j++){
			*(a + i*n + j) = rand();
		}
	}
}


void* multi(void * arg){
	float s = 0;
  int i = *((int*) arg);
	for(int j = 0; j < n; j++){
		for(int k = 0; k < n; k++){
			s += *(A + i*n + j) * *(B + i*n + j);
		}
		*(R + i*n + j) = s;
		s = 0;
	}
}



int main(int argc, char *argv[]){
	n = atoi(argv[argc - 1]);
	//printf("%f\n",n);
  

	pthread_t t[n];

	A = (float *)malloc(n*n*sizeof(float));
	B = (float *)malloc(n*n*sizeof(float));
	R = (float *)malloc(n*n*sizeof(float));

	filling(A);
	filling(B);

  clock_t start, end;
	double total_time = 0;

  start = clock();

	for(int i = 0; i < n; i++){
    int* arg = malloc(sizeof(*arg));
    *arg = i;
		pthread_create(&(t[i]), NULL, &multi, arg);
	}


	pthread_join(t[n-1], NULL);

  end = clock();
  total_time = (double) (end - start) / CLOCKS_PER_SEC; //Total time
  printf("%f\n\n", total_time);
  //prnt(A);
  //prnt(B);
  //prnt(R);
  

//free the matrices
	free(A);
	free(B);
	free(R);

	return 0;
}
