#include <time.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

typedef struct {
	char* title;
	bool completed;
	time_t created_at;
    time_t completed_at;
} task_t;

typedef struct node{
	task_t task;
	struct node* next;
} list_node_t;

typedef struct{
	list_node_t* head;
	list_node_t* tail;
    int size;
} task_list_t;


struct tm* get_current_time();
task_list_t* new_list();
task_t create_new_task(char* task_title);
list_node_t* new_task_node(char* task_title);
void append_node(task_list_t* list, list_node_t* node);
char* time_to_string(struct tm time_to_convert);
char* format_task(task_t task, int index);
void print_tasks(task_list_t* tasks);
void complete_task(task_list_t* tasks, int index);
void remove_task(task_list_t* tasks, int index);