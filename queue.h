#ifndef QUEUE_H
#define QUEUE_H

struct information;

typedef struct queue {
    struct information *head;
    struct information *tail;
    int size;
} queue;

queue *new_queue();
struct information *new_information();
int queue_put_in(queue *table, struct information person);
int queue_get (queue *table, struct information *person);
int get(queue *table, char **id, int *time_arrived, int *time_service);
int put(queue *table, char *id, int time_arrived, int time_service);
void queue_delete(queue *table);
void queue_print(queue *table);
int queue_make(queue *table);
int queue_is_empty(queue *table);
void resize(queue *table, int new_size);
void queue_sort(queue* table);
int is_time(queue *table);
int time_to_out(queue *table);
void retime(queue *table, int ta, int ts);

#endif

