#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#include "queue.h"
#include "task.h"
#include "get.h"

int main() {
  while (1) {
    printf("\nHow Many Registration Stations In Airport?\nInput Positive Integer Number:\n");
    int number_of_stations, station_flag = get_int(&number_of_stations); 
    if (station_flag == -1) {
      printf("\nEnd Of File\n");
      return 0;
    } else {
      if (number_of_stations <= 0) {
        while (number_of_stations <= 0) {
          printf("Number Of Stations Is Must Be Positive Number\n");
          scanf("%*[^\n]");
          scanf("%*c");
          station_flag = get_int(&number_of_stations);
          if (station_flag == EOF) {
            return -1;
          }
        }
      }
      queue **stations = (queue **) malloc(number_of_stations * sizeof(queue *));
      queue *table = new_queue();
      int flag = queue_make(table);
      if (flag == -1) {
        printf("\nEnd Of File\n");
        queue_delete(table);
        free(stations);
        return 0;
      } else if (flag == 1) {
        printf("\nYou're Stupid, Queue Is Full!\n");
        queue_delete(table);
        free(stations);
        return 0;
      } else if (flag == 2) {
        queue_delete(table);
      } else {
        queue_print(table);
        printf("\n===========\n\n");
        queue_sort(table);
        registration_desk(number_of_stations, table, stations);
        queue_delete(table);
      }
      free(stations);
    }
  }
  return 0;
}
