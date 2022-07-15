#include "datastructures.h"


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

