#include "datastructures.h"
#define __USE_XOPEN
#include <time.h>





int main(int argc, char** argv) {
    
    FILE* json = fopen("list.json", "a+");
    if(!json){
        printf("Error, local storage can't be accessed");
    }
    fprintf(json, "w+");
    

    task_list_t* tasks = new_list();

    append_node(tasks, new_task_node("Pula bahama"));

    append_node(tasks, new_task_node("Do dishes"));

    append_node(tasks, new_task_node("Clean room"));    
    print_tasks(tasks);
    puts("");
    complete_task(tasks, 2);
    print_tasks(tasks);
    puts("");

    remove_task(tasks, 3);
    print_tasks(tasks);
    printf("%d", tasks-> size);
    
    puts("\n\ncompiled succesfully");

    puts("\n");
    /* printf("%s", time_to_string(string_to_time("Fri Jul 15 18:46:28 2022"))); */

    return 0;
}

