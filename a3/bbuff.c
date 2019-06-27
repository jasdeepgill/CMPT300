// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <semaphore.h>
// #include "bbuff.h"

// // Prototype Declaration
// void bbuff_init(void);
// void bbuff_blocking_insert(void* item);
// void* bbuff_blocking_extract(void);
// _Bool bbuff_is_empty(void);

// static void* bbuff[BUFFER_SIZE];
// static sem_t mutex;
// static sem_t num_items;
// static sem_t empty_slots;

// void bbuff_init(void)
// {
// 	memset(bbuff, NULL, sizeof(BUFFER_SIZE*void*));
// 	sem_init(&mutex, 0, 1);
// 	sem_init(&num_items, 0, 0);
// 	sem_init(&empty_slots, 0, BUFFER_SIZE);
// }

// void bbuff_blocking_insert(void* item)
// {
// 	do{
// 	sem_wait(&empty_slots);
// 	sem_wait(&mutex);
// 	int i = 0;
// 	while(bbuff[i] != NULL) i++;
// 	bbuff[i] = item;
// 	sem_post(&mutex);
// 	sem_post(&num_items);
// 	}while(true);
// }

// void* bbuff_blocking_extract(void)
// {
// 	do{
// 	sem_wait(&num_items);
// 	sem_wait(&mutex);
// 	int i = 0;
// 	while(bbuff[i] == NULL && !bbuff_is_empty()) i++;
// 	void *temp = malloc(sizeof(void*));
// 	if (temp == NULL)
// 	{
// 		printf("Error: Could not allocate in func bbuff_blocking_extract().\n");
// 		exit(-1);
// 	}
// 	memcpy(bbuff[i], temp, sizeof(void*));
// 	bbuff[i] = NULL;
// 	sem_post(&mutex);
// 	sem_post(&empty_slots);
// 	return temp;
// 	}while(true);
// }

// _Bool bbuff_is_empty(void)
// {
// 	int sem_val;
// 	sem_getvalue(&num_items, &sem_val);
// 	return sem_val == 0;
// }