#ifndef TASK_H
#define TASK_H

//#include "queue.h"


struct queue;

int random_int(int low, int high);
int choose_station(struct queue** stations, int number_of_stations);
void delete_stations(struct queue** stations, int number_of_stations);
void registration_desk(int number_of_stations, struct queue* table, struct queue** stations);

#endif

