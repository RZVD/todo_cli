#include <assert.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

typedef struct {
	char* title;
	bool completed;
	struct tm created_at;
    struct tm completed_at;
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


struct tm* get_current_time(){
    time_t time_now = time(NULL);
    struct tm *local_time = localtime(&time_now);
    return local_time;
}

task_list_t* new_list(){
    task_list_t* list = (task_list_t*) malloc(sizeof(task_list_t));

    list-> head = NULL;
    list-> tail = NULL;
    list-> size = 0;
    return list;

}

task_t create_new_task(char* task_title){
    
    task_t task = {
        .title = task_title,
        .completed = false, 
        .created_at = *(get_current_time())
    };
    return task;
}

list_node_t* new_task_node(char* task_title){
    
    if(strlen(task_title) > 32)  {
        puts("Task title too long\nChoose something shorter");
        exit(0);
    }
    else{ 
        list_node_t* new_task = (list_node_t*) malloc(sizeof(list_node_t));

        new_task-> next = NULL;
        new_task-> task = create_new_task(task_title); 
        

        return new_task;
    }
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
    list-> size++;
}


char* time_to_string(struct tm time_to_convert){
    char* to_return = (char*) malloc(sizeof(char) * 33);
    char s[33];
    assert(strftime(s, sizeof(s), "%c", &time_to_convert));
    if(strcmp(s, "Sun Jan  0 00:00:00 1900") == 0) strcpy(to_return, "Not completed");
    else strcpy(to_return, s);
    
    return to_return;
}   

char* format_task(task_t task, int index){
    char *when_created = time_to_string(task.created_at);
    char *when_done = time_to_string(task.completed_at);
    char* formatted_task = (char*) malloc(sizeof(char) * 110);
    sprintf(formatted_task,"| %d | %-32s | %s | %s |      %-19s|", 
    index, task.title, task.completed ? "true " : "false", when_created, when_done);
    free(when_created);
    free(when_done);

    return formatted_task;
}


void print_tasks(task_list_t* tasks){
    list_node_t* iterator = tasks-> head;
    int i = 0;
    char horizontal_delimiter[] = "═════════════════════════════════════════════════════════════════════════════════════════════════════"; 
    puts(horizontal_delimiter);
    printf("| # |               Task               | Done? |         CreatedAt        |       CompletedAt       |\n");
    puts(horizontal_delimiter);
    while(iterator){
        puts(format_task(iterator-> task, ++i));
        
        iterator = iterator-> next;
    } 
    puts(horizontal_delimiter);

}

void complete_task(task_list_t* tasks, int index){
    list_node_t* iterator = tasks-> head;
    int i = 0;
    while(iterator){
        if(index == ++i) {
            iterator->task.completed = true;
            break;
        }
        iterator = iterator-> next;
    }
}

void remove_task(task_list_t* tasks, int index){
    if(index > tasks-> size){
        printf("Error! Task number %d doesn't exist", index);
        exit(0);
    }
    else if(index == 1) {
        tasks-> head = tasks-> head-> next;
        tasks-> size--;
        return;
    }
    
    list_node_t* iterator = tasks-> head;
    
    if(!iterator-> next) {
        printf("Error! element %d doesn't exist", index);
        return;
    }
    else if(index != tasks-> size){
        int i = 1;
        while(iterator-> next-> next){
            if(index == ++i) {
                list_node_t* aux = iterator-> next;
                iterator-> next = iterator-> next-> next;
                free(aux);
                tasks-> size--;
                return;
            }
            iterator = iterator-> next;
        }
    }
    else{
        for(int i = 0; i< tasks-> size - 2; i++){
            iterator = iterator-> next;
        }
        list_node_t* aux = iterator-> next;
        iterator-> next = NULL;
        tasks-> tail = iterator;
        free(aux);
        tasks-> size--;
    }
}

int main(int argc, char** argv) {
    task_list_t* tasks = new_list();

    append_node(tasks, new_task_node("Pula bahama"));

    append_node(tasks, new_task_node("Do dishes"));

    append_node(tasks, new_task_node("Clean room"));    
    print_tasks(tasks);
    puts("");
    complete_task(tasks, 3);
    print_tasks(tasks);
    puts("");

    remove_task(tasks, 3);
    print_tasks(tasks);
    printf("%d", tasks-> size);
    
    puts("\n\ncompiled succesfully");
    
    return 0;
}

