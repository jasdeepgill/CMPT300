#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include <pthread.h>
#include <unistd.h>
#include "bbuff.h"
#include "stats.h"

#define MAX_THREADS 1000
#define RAND_LOWER 0
#define RAND_UPPER 3

// Prototype Declaration
double current_time_in_ms(void);

typedef struct  {
    int factory_number;
    double time_stamp_in_ms;
} candy_t;

// pthread_mutex_t lock;

_Bool stop_thread = false;
void* factory_thread_function(void* arg) {
    while (!stop_thread) {
    	candy_t factory_data = *((candy_t *) arg);
    	int rand_wait_time;
    	rand_wait_time = (rand() % (RAND_UPPER - RAND_LOWER + 1)) + RAND_LOWER;
    	printf("\tFactory %d ships candy & waits %ds\n", factory_data.factory_number, rand_wait_time);
    	void *new_candy = malloc(sizeof(void*));
    	factory_data.time_stamp_in_ms = current_time_in_ms();
    	new_candy = &factory_data;
    	bbuff_blocking_insert(new_candy);
    	sleep(rand_wait_time);
    }
    // printf("BRUH\n");
    // candy_t factory_data = *((candy_t *) arg);
    // printf("%d %lf\n", factory_data.factory_number, factory_data.time_stamp_in_ms);
    // free(arg);
    return NULL;
}

void* kid_thread_function(void* arg)
{
	do{
		candy_t extracted_candy = *((candy_t *) bbuff_blocking_extract());
		printf("Got candy from factory %d\n", extracted_candy.factory_number);
		sleep(rand() % 2);
	}while(true);
}

double current_time_in_ms(void)
{
    struct timespec now;
    clock_gettime(CLOCK_REALTIME, &now);
    return now.tv_sec * 1000.0 + now.tv_nsec/1000000.0;
}

int main(int argc, char const *argv[])
{
	int factories = atoi(argv[1]);
	int kids = atoi(argv[2]);
	int seconds = atoi(argv[3]);
	pthread_t f_id_list[MAX_THREADS];
	pthread_t k_id_list[MAX_THREADS];
	if (argc < 4)
	{
		printf("Error: Too few arguments.\n");
		exit(-1);
	}
	else if (argc > 4)
	{
		printf("Error: Too many arguments.\n");
		exit(-1);
	}
	
	if (factories < 0 || kids < 0 || seconds < 0)
	{
		printf("Error: value less than zero.\n");
		exit(-1);
	}

	candy_t data[MAX_THREADS];
	// pthread_mutex_init(&lock, NULL);
	srand(time(0));
	bbuff_init();
	// stats_init(factories);
	for (int i = 0; i < factories; ++i)
	{
		pthread_t f_thread_id;
		data[i].factory_number = i;
		// data[i].time_stamp_in_ms = current_time_in_ms();
		pthread_create(&f_thread_id, NULL, factory_thread_function, &data[i]);
		f_id_list[i] = f_thread_id;
	}
	for (int j = 0; j < kids; ++j)
	{
		pthread_t k_thread_id;
		pthread_create(&k_thread_id, NULL, kid_thread_function, NULL);
		k_id_list[j] = k_thread_id;
	}
	for (int k = 0; k < seconds; ++k)
	{
		printf("Time %ds:\n", k);
		sleep(1);
	}
	printf("Stopping candy factories...\n");
	stop_thread = true;
	for (int n = 0; n < factories; ++n)
	{
		pthread_join(f_id_list[n], NULL);
		printf("Candy-factory %d done\n", n);
	}
	// printf("Waiting for all candy to be consumed...\n");
	while(!bbuff_is_empty())
	{
		printf("Waiting for all candy to be consumed...\n");
		sleep(1);
	}
	printf("Stopping kids...\n");
	for (int m = 0; m < kids; ++m)
	{
		pthread_cancel(k_id_list[m]);
		pthread_join(k_id_list[m], NULL);
	}
	return 0;
}