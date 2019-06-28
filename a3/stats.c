#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "stats.h"

// Prototype Declaration
void stats_init(int num_producers);
void stats_cleanup(void);
void stats_record_produced(int factory_number);
void stats_record_consumed(int factory_number, double delay_in_ms);
void stats_display(void);

typedef struct 
{
	int factory_number;
	int Made;
	int Eaten;
	int num;
	double sum_delay;
	double min_delay;
	double max_delay;
	double avg_delay;
} factory_info;

static int producers = 0;
static factory_info* array;

void stats_init(int num_producers)
{
	array = malloc(num_producers*sizeof(factory_info));
	// factory_info info[sizeof(factory_info)*num_producers];
	// array->factory_number = 0;
	// array->Made = 0;
	// array->Eaten = 0;
	// array->num = 0;
	// array->sum_delay = 0;
	// array->min_delay = INFINITY;
	// array->max_delay = -INFINITY;
	// array->avg_delay = 0;
	// array = info;
	producers = num_producers;
	// printf("Producers: %d\n", producers);
	// printf("Size of array: %lu\n", sizeof(array));
	// printf("Factory number: %d\n", array->factory_number);
	// printf("Made: %d\n", array->Made);
	// printf("eaten: %d\n", array->Eaten);
	// printf("delay: %lf\n", array->delay_in_ms);
	// printf("min: %lf\n", array->min_delay);
	// printf("max: %lf\n", array->max_delay);
	// printf("avg: %lf\n", array->avg_delay);
	for (int i = 0; i < num_producers; ++i)
	{
		array[i].factory_number = i;
		array[i].Made = 0;
		array[i].Eaten = 0;
		array[i].num = 0;
		array[i].sum_delay = 0;
		array[i].min_delay = INFINITY;
		array[i].max_delay = -INFINITY;
		array[i].avg_delay = 0;
		// printf("factory number: %d\n", array[i].factory_number);
	}
	return;
}

void stats_cleanup(void)
{
	free(array);
	return;
}

void stats_record_produced(int factory_number)
{
	int i = 0;
	while(i != producers)
	{
		// printf("Array factory number: %d\n",array[i].factory_number);
		// printf("factory_number: %d\n", factory_number);
		if(array[i].factory_number == factory_number)
		{
			array[i].Made++;
		}
		i++;
	}
	return;
}

void stats_record_consumed(int factory_number, double delay_in_ms)
{
	int j = 0;
	while(j != producers)
	{
		if(array[j].factory_number == factory_number)
		{
			printf("Factory: %d\nDelay: %lf\n", factory_number,delay_in_ms);
			array[j].num++;
			array[j].sum_delay += delay_in_ms; 
			array[j].Eaten++;
			if(delay_in_ms < array[j].min_delay)
			{
				array[j].min_delay = delay_in_ms;
			}
			if(delay_in_ms > array[j].max_delay)
			{
				array[j].max_delay = delay_in_ms;
			}
			array[j].avg_delay = (array[j].sum_delay/((double)array[j].num));
		}
		j++;
	}
}

void stats_display(void)
{
	printf("Statistics:\n");
	printf("%8s%10s%10s%15s%15s%15s\n", "Factory#", "#Made", "#Eaten", "Min Delay[ms]", "Avg Delay[ms]", "Max Delay[ms]");
	for (int i = 0; i < producers; ++i)
	{
		printf("%8d%10d%10d%15lf%15lf%15lf\n",array[i].factory_number,array[i].Made,array[i].Eaten,array[i].min_delay,array[i].avg_delay,array[i].max_delay);
	}
}
