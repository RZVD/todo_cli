#include "datastructures.h"
#include <time.h>


void process_line(task_list_t* tasks, char* line){
    char* p = strtok(line, " ");
    int i = 0;
    list_node_t* dummy;

    
     while(p){
        switch (i){
        case 0:
            dummy = new_task_node(p);
            break;
        case 1:
            dummy-> task.completed = strcmp(p, "false") == 0 ? false : true;
            break;
        case 2:
            dummy-> task.created_at = atoi(p); 
            break;
        case 3:
            dummy-> task.completed_at = strcmp(p, "Thu Jan  1 02:00:00 1970") == 0 ?
                 0 : atoi(p);  
            break;     
        }
        
        p = strtok(NULL, " ");
        i++;
    } 
    append_node(tasks, dummy); 
}


int main(int argc, char** argv) {




    task_list_t* tasks = new_list();
    char filename[] = "list.txt";
    FILE *file = fopen ( filename, "a+" );

    if (file != NULL) {
        char line [1000];
        while(fgets(line, 1000, file)){

            process_line(tasks, line);
        }
        
        fclose(file);
  }
    else {
        perror(filename); //print the error message on stderr.
  }


    /* append_node(tasks, new_task_node("Pula bahama"));

    append_node(tasks, new_task_node("Do dishes"));

    append_node(tasks, new_task_node("Clean room"));    
    print_tasks(tasks);
    puts("");
    complete_task(tasks, 2);
    print_tasks(tasks);
    puts("");

    remove_task(tasks, 3);
    append_node(tasks, new_task_node("fute-l pe cret"));
    printf("%d", tasks-> size);
     */
    print_tasks(tasks);


    puts("\n\ncompiled succesfully");

    puts("\n");
 
    return 0;
}

