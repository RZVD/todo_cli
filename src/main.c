#include "datastructures.h"
#include <time.h>



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
    if(file) store_data(tasks, file);

}

int main(int argc, char** argv) {
    char filename[] = "/home/razvan/repos/todo_cli/list.csv";
    bool flag = argc == 1 ? true : false; 
    char* arg1 = flag ? NULL: strdup(argv[1]);
    char* arg2 = argc >= 3 ? strdup(argv[2]) : NULL;

    task_list_t* tasks = new_list();
    
    
    FILE* file = fopen ( filename, "r" );
    int loaded_tasks = 0;
    if (file != NULL) {
        char line [100] = {0};
        
        while(fgets(line, sizeof(line), file)){
            loaded_tasks ++;
            process_line(tasks, line);
        }
    }
    else {
        perror(filename);
    }
    
    fclose(file);

    if(!flag){    
        FILE* file2 = fopen(filename, "w");

        if(!strcmp(arg1, "-add")){
            command_add(tasks, arg2, file2);
        }
        else if(!strcmp(arg1, "-complete")){
            command_complete(tasks, arg2, file2);
        }
        else if(!strcmp(arg1, "-delete")){
            command_delete(tasks, arg2, file2);
        } 
        else if(!strcmp(arg1, "-print")) {
            command_print(tasks, file2);
        }
        else{
            puts("ERROR! Invalid Command!");
            store_data(tasks, file2);
            exit(-1);
        }
   }
   else{
    command_print(tasks, NULL);
   }
    return 0;
}

