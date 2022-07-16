#include "database.h"

void process_line(task_list_t* tasks, char* line){
    
    char* p = strtok(line, ",");
    int i = 0;
    
    list_node_t* dummy = new_task_node("");
    
    while(p){
        switch (i){
            case 0 :
                dummy->task.title = strdup(p); 
                break;
            case 1 :
                dummy-> task.completed = strcmp(p, "false") == 0 ? false : true;
                break;
            case 2 :
                dummy-> task.created_at = atoi(p);
                break;
            case 3 :
                dummy-> task.completed_at = strcmp(p, "Thu Jan  1 02:00:00 1970") == 0 ?
                 0 : atoi(p);
                break;
        }
        i++;
        p = strtok(NULL, ",");
    }
    append_node(tasks, dummy);
}



void store_data(task_list_t* tasks, FILE* file){
    list_node_t* dummy = tasks-> head;

    while(dummy){
        char s[1000];
        sprintf(s, "%s,%s,%ld,%ld\n",
            dummy-> task.title,
            dummy-> task.completed == false ? "false" : "true",
            dummy-> task.created_at,
            dummy-> task.completed_at
        );
        fputs(s, file);
        
        dummy = dummy-> next; 
    }

    fclose(file);
}


void command_add(task_list_t* tasks, char* arg, FILE* file){
    append_node(tasks, new_task_node(arg));
    store_data(tasks, file);
}
void command_complete(task_list_t* tasks, char* arg, FILE* file){
    complete_task(tasks, atoi(arg));
    store_data(tasks, file);
}
void command_delete(task_list_t* tasks, char* arg, FILE* file){
    remove_task(tasks, atoi(arg));
    store_data(tasks, file);
}

void command_print(task_list_t* tasks, FILE* file){
    print_tasks(tasks);
    store_data(tasks, file);

}
