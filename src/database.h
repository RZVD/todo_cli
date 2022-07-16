#include "datastructures.h"


void process_line(task_list_t* tasks, char* line);

void store_data(task_list_t* tasks, FILE* file);

void command_add(task_list_t* tasks, char* arg, FILE* file);

void command_complete(task_list_t* tasks, char* arg, FILE* file);

void command_delete(task_list_t* tasks, char* arg, FILE* file);

void command_print(task_list_t* tasks, FILE* file);