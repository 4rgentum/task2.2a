#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "get.h"

char* readline() {
    char buffer[81] = {0};
    char *my_string = NULL;
    int length = 0;
    int element = 0;
    do {
        int flag = 0;
        element = scanf("%80[^\n]%n", buffer, &flag);
        if (element < 0 || flag == EOF) {
            if (!my_string) {
                return NULL;
            } else if (flag == EOF) {
                break;
            }
        } else if (element > 0 && flag != EOF) {
            int chunk_len = strlen(buffer);
            int str_len = length + chunk_len;
            char* temp = realloc(my_string, str_len + 1);
            if (!temp) {
                free(my_string);
                return NULL;
            }
            my_string = temp;
            memcpy(my_string + length, buffer, chunk_len);
            length = str_len;
            my_string[str_len] = '\0';
        } else {
            scanf("%*[^\n]");
            scanf("%*c");
        }
    } while (element > 0);
    if (my_string) {
        char* temp = realloc(my_string, length + 1);
        if (!temp) {
            free(my_string);
            return NULL;
        }
        my_string = temp;
        my_string[length] = '\0';
    } else {
        my_string = calloc(1, sizeof(char));
    }
    return my_string;
}

char** split_string(char* input_string, int* number_of_persons) {
    char** tokens = NULL;
    char* token = strtok(input_string, " ");
    int count = 0;
    while (token != NULL) {
        token[strlen(token)] = '\0';
        count++;
        tokens = (char **) realloc(tokens, count * sizeof(char *));
        tokens[count - 1] = strdup(token);
        if (tokens[count - 1] == NULL) {
            for (int i = 0; i < count - 1; i++) {
                free(tokens[i]);
            }
            free(tokens);
            return NULL;
        }
        token = strtok(NULL, " ");
    }
    *number_of_persons = count;
    return tokens;
}

int power(int base, int exponent) {
    int result = 1;
    for (int i = 0; i < exponent; i++) {
        result *= base;
    }
    return result;
}

int get_int(int *number) {
  int flag;
  flag = scanf("%d", number);
  if (flag == EOF) {
    return -1;
  } 
  if(flag != 1 || number < 0) {
    while (flag != 1) {
      printf("\nInvalid Input");
      printf("\nEnter Correct Integer Number:\n");
      scanf("%*[^\n]");
      scanf("%*c");
      flag = scanf("%d", number);
      if (flag == EOF) {
        return -1;
      }
    }
  }
  return 0;
}
