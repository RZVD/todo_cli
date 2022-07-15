#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	char* task_title;
	bool completed;
	struct tm created_at;
    struct tm completed_at;
} task_t;

typedef struct node{
	task_t task;
	struct node* next;
}list_node_t;

typedef struct{
	list_node_t* head;
	list_node_t* tail;
}task_list_t;



struct tm* get_current_time(){
    time_t time_now = time(NULL);
    struct tm *local_time = localtime(&time_now);
    return local_time;
}

task_list_t* new_list(){
	task_list_t* list = (task_list_t*) malloc(sizeof(task_list_t));  


    list-> head = NULL;
    list-> tail = NULL;

    return list;

}

task_t create_new_task(char* task_title){
    
    task_t task = {
        task_title,
        false, 
        *(get_current_time())
    };
    return task;
}

list_node_t* new_task_node(char* task_title){
    list_node_t* new_task = (list_node_t*) malloc(sizeof(list_node_t));

    new_task-> next = NULL;
    new_task-> task = create_new_task(task_title); 

    return new_task;
}
void append_node(task_list_t* list, list_node_t* node){
    if(!list-> head){
        list-> head = node;
        list-> tail = node;
    } 
    else{
        list-> tail-> next = node;
        list-> tail = list-> tail-> next;
    }
}


char* time_to_string(struct tm time_to_convert){
    char* to_return = (char*) malloc(sizeof(char) * 64);
    char s[64];
    assert(strftime(s, sizeof(s), "%c", &time_to_convert));
    
    
    strcpy(to_return, s);
    
    return to_return;
}   


int main(int argc,char** argv) {
    task_list_t* tasks = new_list();

    append_node(tasks, new_task_node("Eat fud"));

    sleep(60);
    append_node(tasks, new_task_node("Do dishes"));

    list_node_t* test = tasks-> head;

    while(test){
        puts(time_to_string(test->task.created_at));
        
        test = test-> next;
    } 

    test = tasks-> head;
    puts("\n");
    while(test){
        puts(time_to_string(test->task.created_at));
        
        test = test-> next;
        
    }

    puts("\n\ncompiled succesfully");
    
    return 0;
}

