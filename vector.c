#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "queue.h"
#include "vector.h"
#include "get.h"

#define SIZE 4

typedef struct information {
    char *id;
    int time_arrived;
    int time_service;
} information;

queue *new_queue() {
    queue *table = (queue *) calloc(1, sizeof(queue));
    table->size = 0;
    table->head = (information *) calloc(SIZE, sizeof(information));
    table->tail = table->head;
    return table;
}

struct information *new_information() {
    information *person = (information *) calloc(1, sizeof(information));
    person->time_service = 0;
    person->time_arrived = 0;
    person->id = NULL;
    return person;
}

int is_time(queue *table) {
  return table->head->time_arrived;
}

int time_to_out(queue *table) {
  return table->head->time_arrived + table->head->time_service;
}

void retime(queue *table, int ta, int ts) {
  table->head->time_arrived = ta + ts;
}

int queue_put_in(queue *table, struct information person) {
  table->tail->id = (char *) calloc(strlen(person.id) + 1, sizeof(char));
  strcpy(table->tail->id, person.id);
  table->tail->time_arrived = person.time_arrived;
  table->tail->time_service = person.time_service;
  (table->size)++;
  (table->tail)++;
  return 0;
}

int put(queue *table, char *id, int time_arrived, int time_service) {
  table->tail->id = (char *) calloc(strlen(id) + 1, sizeof(char));
  strcpy(table->tail->id, id);
  table->tail->time_arrived = time_arrived;
  table->tail->time_service = time_service;
  (table->size)++;
  (table->tail)++;
  return 0;
}

int queue_get(queue *table, struct information *person) {
  if (table->head == table->tail) {
    return 1;
  } else {
    person->id = (char *) realloc(person->id, (strlen(table->head->id) + 1) * sizeof(char));
    strcpy(person->id, table->head->id);
    person->time_arrived = table->head->time_arrived;
    person->time_service = table->head->time_service;

    free(table->head->id);
    table->head->id = NULL;
    
     for (int i = 0; i < table->size - 1; i++) {
      table->head[i].id = (char *) realloc(table->head[i].id, (strlen(table->head[i + 1].id) + 1) * sizeof(char));
      strcpy(table->head[i].id, table->head[i + 1].id);
      table->head[i].time_arrived = table->head[i + 1].time_arrived;
      table->head[i].time_service = table->head[i + 1].time_service;
    }

    free(table->head[table->size - 1].id);
    table->head[table->size - 1].id = NULL;
    table->head[table->size - 1].time_arrived = 0;
    table->head[table->size - 1].time_service = 0;
    (table->size)--;
    (table->tail)--;
    return 0;
  }
}

int get(queue *table, char **id, int *time_arrived, int *time_service) {
  if (table->head == table->tail) {
    return 1;
  } else {
    *id = (char *) realloc(*id, (strlen(table->head->id) + 1) * sizeof(char));
    strcpy(*id, table->head->id);
    *time_arrived = table->head->time_arrived;
    *time_service = table->head->time_service;

    free(table->head->id);
    table->head->id = NULL;
    
     for (int i = 0; i < table->size - 1; i++) {
      table->head[i].id = (char *) realloc(table->head[i].id, (strlen(table->head[i + 1].id) + 1) * sizeof(char));
      strcpy(table->head[i].id, table->head[i + 1].id);
      table->head[i].time_arrived = table->head[i + 1].time_arrived;
      table->head[i].time_service = table->head[i + 1].time_service;
    }

    free(table->head[table->size - 1].id);
    table->head[table->size - 1].id = NULL;
    table->head[table->size - 1].time_arrived = 0;
    table->head[table->size - 1].time_service = 0;
    (table->size)--;
    (table->tail)--;
    return 0;
  }
}

int queue_is_empty(queue *table) {
  if (table->head == table->tail) {
    return 0;
  } else {
    return 1;
  }
}

void queue_delete(queue *table) {
    for (int i = 0; i < table->size; i++) {
      if ((table->head)[i].id) {
        free((table->head)[i].id);
      }
    }
    free(table->head);
    free(table);
}

void queue_print(queue *table) {
    for (int i = 0; i < table->size; i++) {
        printf("%s ", (table->head)[i].id);
    }
  printf("\n");
}


int comparator (const struct information* first_struct_elem, const struct information* second_struct_elem) {
    return first_struct_elem->time_arrived - second_struct_elem->time_arrived;
}

void resize(queue *table, int new_size) {
    table->head = (information *) realloc(table->head, new_size * sizeof(information));
    table->tail = table->head + table->size;
}


int queue_make(queue *table) {
  scanf("%*[^\n]");
  scanf("%*c");
  printf("\nEnter Your Example In One String In Format \"char string/positive integer number/positive integer number\"\n");
  int size = SIZE;
  char *str;
  str = readline();
  if (!str) {
    free(str);
    return -1;
  } else {
    int number_of_persons = 0;
    char **array = split_string(str, &number_of_persons);
    if (array == NULL) {
      for (int ind = 0; ind < number_of_persons; ind++) {
        free(array[ind]);
      }
      free(array);
      free(str);
      return -1;
    } else {
      while (number_of_persons > size) {
        printf("\nYour Queue Is Full, Do You Want To Increase Size Of Queue?\nInput 1, If Yes, 0, If No:\n");
        int answer, answer_flag = get_int(&answer);      
        if (answer_flag == -1) {
          for (int ind = 0; ind < number_of_persons; ind++) {
            free(array[ind]);
          }
          free(array);
          free(str);
          return -1;
        } else {
          if (answer == 1) {
            printf("\n How Much Persons Do You Want To Add?\nInput Positive Integer Number:\n");
            int add_size, size_flag = get_int(&add_size);
            if (answer_flag == -1) {
              for (int ind = 0; ind < number_of_persons; ind++) {
                free(array[ind]);
              }
              free(array);
              free(str);
              return -1;
            } else {
              size += add_size;
              resize(table, size);
            }
          } else if (answer == 0) {
            for (int ind = 0; ind < number_of_persons; ind++) {
              free(array[ind]);
            }
            free(array);
            free(str);
            return 1;
          }
        }
      }
      
      for (int i = 0; i < number_of_persons; i++) {
        information *person = new_information();
        int ind_ta = 0, ind_ts = 0, ta_size = 0, ts_size = 0, *ta = NULL, *ts = NULL;
        
        for (int ind_id = 0; ind_id < strlen(array[i]); ind_id++) {
          if (array[i][ind_id] != '/') {
            person->id = (char *) realloc(person->id, (ind_id + 2) * sizeof(char));
            (person->id)[ind_id] = array[i][ind_id];
          } else if (array[i][ind_id] == '/') {
            person->id = (char *) realloc(person->id, (ind_id + 2) * sizeof(char));
            (person->id)[ind_id] = '\0';
            ind_ta = ind_id + 1;
            break;
          } else if (array[i][ind_id] == '\0') {
            printf("\nIncorrect Input, Plese Repeat Your Input Correctly\n");
            free(person->id);
            free(person);
            for (int ind = 0; ind < number_of_persons; ind++) {
              free(array[ind]);
            }
            free(array);
            free(str);
            return 2;
          }
        }
        
        if (!(person->id) || ind_ta == 0) {
          printf("\nIncorrect Input, Plese Repeat Your Input Correctly\n");
            free(person->id);
            free(person);
            for (int ind = 0; ind < number_of_persons; ind++) {
              free(array[ind]);
            }
            free(array);
            free(str);
            return 2;
        } else {
          for (ind_ta; ind_ta <= strlen(array[i]); ind_ta++) {
            if (array[i][ind_ta] >= '0' && array[i][ind_ta] <= '9') {
              ta_size++;
              ta = (int *) realloc(ta, ta_size * sizeof(int));
              ta[ta_size - 1] = array[i][ind_ta] - '0';
            } else if (array[i][ind_ta] == '/') {
              ind_ts = ind_ta + 1;
              break;
            } else {
              printf("\nIncorrect Input, Please, Repeat Your Input Correctly\n");
              if (!ta) {
                free(ta);
              }
              free(person->id);
              free(person);
              for (int ind = 0; ind < number_of_persons; ind++) {
                free(array[ind]);
              }
              free(array);
              free(str);
              return 2;
            }
          }
          for (int k = 0; k < ta_size; k++) {
            person->time_arrived += power(10, ta_size - k - 1) * ta[k];
          }
          for (ind_ts; ind_ts < strlen(array[i]); ind_ts++) {
            if (array[i][ind_ts] < '0' || array[i][ind_ts] > '9' || array[i][ind_ts] == EOF || array[i][ind_ts] == '\0') {
              printf("\nIncorrect Input, Please, Repeat Your Input Correctly\n");
              free(ta);
              if (!ts) {
                free(ts);
              }
              free(person->id);
              free(person);
              for (int ind = 0; ind < number_of_persons; ind++) {
                free(array[ind]);
              }
              free(array);
              free(str);
              return 2;
            } else {
              ts_size++;
              ts = (int *) realloc(ts, ts_size * sizeof(int));
              ts[ts_size - 1] = array[i][ind_ts] - '0';
            }
          }
          for (int l = 0; l < ts_size; l++) {
            person->time_service += power(10, ts_size - l - 1) * ts[l];
          }
        }
        queue_put_in(table, *person);
        free(ta);
        free(ts);
        free(person->id);
        free(person);
      }
    }
    for (int ind = 0; ind < number_of_persons; ind++) {
      free(array[ind]);
    }
    free(array);
    free(str);
    return 0;
  }
}

void queue_sort(queue* table) {
  qsort(table->head, table->size, sizeof(information), (int (*)(const void *, const void *)) comparator);
}
