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


int main(int argc, char** argv) {
    bool flag = argc == 1 ? true : false;

    task_list_t* tasks = new_list();
    
    char filename[] = "list.csv";
    
    FILE* file = fopen ( filename, "r" );
    int loaded_tasks = 0;
    if (file != NULL) {
        char line [1000] = {0};
        
        while(fgets(line, 1000, file)){
            loaded_tasks ++;
            process_line(tasks, line);
        }
    }
    else {
        perror(filename); //print the error message on stderr.
    }
    fclose(file);

     if(!flag){    
        FILE* file2 = fopen(filename, "w");
        
        char* arg1 = strdup(argv[1]);
        char* arg2 = strdup(argv[2]);

        printf("%s", strcmp(arg1, "-complete") == 0 ? "true" : "false");
        
        complete_task(tasks, 3);
        
        if(!strcmp(arg1, "-add")){
            append_node(tasks, new_task_node(arg2));
            store_data(tasks, file2);
        }

        else if(!strcmp(arg1, "-complete")){
            complete_task(tasks, atoi(arg2));
            store_data(tasks, file);
        }


        else if(strcmp(arg1, "-delete")){
            remove_task(tasks, atoi(arg2));
            store_data(tasks, file);
        }
        else if(strcmp(arg1, "-print")){
            print_tasks(tasks);
            store_data(tasks, file);

        }
        else{
            puts("ERROR! Invalid Command!");
            exit(-1);
        }


   }

/*     FILE* file2 = fopen(filename, "w");
    remove_task(tasks, 6);
    store_data(tasks, file2);

    print_tasks(tasks);
 */
    
    puts("\n\ncompiled succesfully");

    puts("\n");
 
    return 0;
}

