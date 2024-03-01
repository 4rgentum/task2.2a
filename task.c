#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "queue.h"
#include "task.h"

int random_int(int low, int high) {
    return rand() % (high - low + 1) + low;
}

void delete_stations(queue** stations, int number_of_stations) {
  for (int i = 0; i < number_of_stations; i++) {
    queue_delete(stations[i]);
  }
}

int choose_station(queue** stations, int number_of_stations) {
  int fst_ind = random_int(0, number_of_stations - 1);
  int snd_ind = random_int(0, number_of_stations - 1);
  while (snd_ind == fst_ind) {
    snd_ind = random_int(0, number_of_stations - 1);
  }
  if (stations[fst_ind]->size < stations[snd_ind]->size) {
    return fst_ind;
  } else {
    return snd_ind;
  }
}

void registration_desk(int number_of_stations, queue* table, queue** stations) {
  
  for (int j = 0; j < number_of_stations; j++) {
    stations[j] = new_queue();
    resize(stations[j], table->size);
  }
  
  int num_of_pas = table->size, timer = 0, change = 0, flag = 1;
  while (flag) {
    timer++;
    change = 0;
    flag = 0;

    for (int i = 0; i < number_of_stations; i++) {
      if (queue_is_empty(stations[i])) {
        if (time_to_out(stations[i]) == timer) {
          char *id = (char *) calloc(1, sizeof(char));
          int ta = 0, ts = 0;
          get(stations[i], &id, &ta, &ts);
          if (queue_is_empty(stations[i])) {
            retime(stations[i], ta, ts);
          }
          free(id);
          change = 1;
        }
      }
    }
    
    if (queue_is_empty(table)) {
      if (is_time(table) == timer) {
        char *id = (char *) calloc(1, sizeof(char));
        int ta = 0, ts = 0;
        get(table, &id, &ta, &ts);
        put(stations[choose_station(stations, number_of_stations)], id, ta, ts);
        free(id);
        change = 1;
      }
    }
    
    for (int i = 0; i < number_of_stations; i++) {
      if (queue_is_empty(stations[i]) || queue_is_empty(table)) {
        flag = 1;
        break;
      }
    }

    if (change) {
      printf("Now time is: %d\n", timer);
      for (int i = 0; i < number_of_stations; i++) {
        printf("Station Number %d:", (i + 1));
        queue_print(stations[i]);
      }
    }
    
  }

  printf("End Of Queue");
  printf("\n===========\n\n");
  
  delete_stations(stations, number_of_stations);
}
