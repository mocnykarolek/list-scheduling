

#include "stdio.h"
#include "stdlib.h"
#include "string.h"


typedef struct task{

    int id;
    int time;



}task;

typedef struct Record{
    
    int finish_time;
    int task_id;
    struct Record* next;

} Record;

typedef struct proc{
    int p_number;
    int time_usage;
    int tasks_cnt;

    Record* records;
    task* tasks;
    int tasks_capacity;

} proc;


int partition(task*array, int start, int end, int c){

    int pivot = array[end].time;
    int i = start -1;
    for (int j = start; j <= end-1; j++)
    {
        if(c == 1){
            // asc
        if(array[j].time < pivot || (array[j].time == pivot && array[j].id < array[end].id) ){ // malejacy lub rosnacy
            i++;
            task temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        }
        else{
            // desc
            if(array[j].time > pivot || (array[j].time == pivot && array[j].id > array[end].id)  ){ // malejacy lub rosnacy 
            i++;
            task temp = array[i];
            array[i] = array[j];
            array[j] = temp;
        }
        }
    }
    i++;
    task temp = array[i];
    array[i] = array[end];
    array[end] = temp;

    return i;

}
/*
    1 - ascending, 0- descending
*/
void quicksort(task*array, int start, int end, int c){

    if(end <= start) return;

    int pivot = partition(array, start,end,c);
    quicksort(array, start, pivot-1,c);
    quicksort(array, pivot+1, end,c);


}


Record* append(Record* first,Record node){
    Record* newNode = (Record*)malloc(sizeof(Record));
    newNode->finish_time = node.finish_time;
    newNode->task_id = node.task_id;
    
    newNode->next = nullptr;
    if( first == nullptr){
        return newNode;
    }
    
    newNode->next = nullptr;
    Record* tmp = first;

    while(tmp->next != nullptr){
        tmp = tmp->next;

    }
    tmp->next = newNode;
    return first;
    


}

/*
    creates array with n+1 size
*/
task* array_addition(task*a, int insertion_index, int input_time, int* real_arr_size, int* tasks_number, int* next_task_id){
    // task* new_array;
    if(*tasks_number +1 > *real_arr_size){
        *real_arr_size = (*real_arr_size) * 2;
        task* tmp = (task*)realloc(a, *real_arr_size * sizeof(task));
        if(tmp == nullptr){
            printf("reallocation do not succeded");
            return a;
        }
        a = tmp;
        // new_array = (task*)malloc(sizeof(task)* (*real_arr_size));
    }

    int elements_to_move = *tasks_number - insertion_index; 
    if(elements_to_move > 0) memmove(a+ insertion_index+1, (a+insertion_index), elements_to_move * sizeof(task));

    a[insertion_index].time = input_time;
    a[insertion_index].id = *next_task_id;
    (*next_task_id)++;
    (*tasks_number)++;

    
    
    return a;
}


task* removing_element(int id_to_remove, task*a, int*tasks_number){

    for (int i = 0; i < *tasks_number; i++)
    {
        if(a[i].id == id_to_remove){
            int elements_to_move = *tasks_number - i -1;
            memmove(a+i, a+i+1, elements_to_move * sizeof(task));
            (*tasks_number)--;
            break;
        }
    }
    
    return a;

}


int findMinUsage(proc* processors, int m){

    int min = 0;
    for (int i = 1; i < m; i++)
    {
        if(processors[i].time_usage < processors[min].time_usage){
            min = i;


        }else if(processors[i].time_usage == processors[min].time_usage && processors[i].p_number < processors[min].p_number){

            min = i;

        }
    }
    return min;
}
// Record* getAtPosition(Record* first, int position){

//     Record* tmp = first;
//     while(tmp != nullptr){
//         if(position ==0){
//             return tmp;
//         }
//         position--;
//         tmp = tmp->next;
//     }
//     return nullptr;

// }
void clear_linked_list(Record* r){

    if(r == nullptr){
        return;
    }


    clear_linked_list(r->next);
    free(r);
    

}
/*
l_d 1- linked list, 0- dynamic array
*/
proc* init_processors(int m, int l_d){

    proc* processors = (proc*)malloc(sizeof(proc)*m);

    for (int i = 0; i < m; i++)
    {
        processors[i].p_number = i+1;
        processors[i].time_usage = 0;
        processors[i].tasks_cnt = 0;
        processors[i].records = nullptr;
        processors[i].tasks = nullptr;
        if(l_d == 1){ // linked list
        
            
            processors[i].tasks = nullptr;
            processors[i].tasks_capacity = 0;


        }
        else{ // dyn array

            processors[i].tasks_capacity = 1;
            processors[i].tasks = (task*)malloc(sizeof(task));

            
        }

        
    }
    return processors;

}
void print_output(proc* processors, int m, int sigmaC, int Cmax){
    printf("Cmax: %d\n", Cmax);
    printf("sigmaC: %d\n", sigmaC);

    for (int i = 0; i < m; i++)
    {   
        
        printf("M%d:", processors[i].p_number);
        
        // Record* rec = getAtPosition(processors[i].records, i);
        // printf("( C%d = %d )", rec->task_id, rec->finish_time );
        // for (int j = 0; j < processors[i].tasks_cnt; j++)
        // {
            
        // }
        Record* current = processors[i].records;
    
        while(current != nullptr){
            printf("( C%d = %d )", current->task_id, current->finish_time);
            current = current->next;
        }
        

        printf("\n");
        clear_linked_list(processors[i].records);
        if(processors[i].tasks != nullptr){
            free(processors[i].tasks);
        }
    }
}

/*
    (B) Basic list scheduling
*/
void bls(task*array, int m, int tasks_number){
    int time;
    proc* processors = init_processors(m, 1);
    int Cmax = 0;
    int sigmaC = 0;
 
    for (int i = 0; i < tasks_number; i++)
    {   
        int optimal_processor = findMinUsage(processors,m);
        processors[optimal_processor].tasks_cnt++;
        processors[optimal_processor].time_usage += array[i].time;
        sigmaC += processors[optimal_processor].time_usage;
        Record rec;
        rec.finish_time = processors[optimal_processor].time_usage;
        rec.task_id = array[i].id;
        processors[optimal_processor].records = append(processors[optimal_processor].records,rec);
        
        
    }

    for (int i = 0; i < m; i++)
    {
        if(processors[i].time_usage > Cmax){
            Cmax = processors[i].time_usage;
        }
    }
    
    print_output(processors, m, sigmaC, Cmax);

    free(processors);

}




/*
    (L) Longest Processing Time First algorithm
*/
void lpt(task*array, int m, int tasks_number, int real_array_length){
    
    task* copied_array = (task*)malloc(sizeof(task)* real_array_length);
    memcpy(copied_array, array, sizeof(task)* real_array_length);
    
    quicksort(copied_array, 0, tasks_number-1,0);

    // for (int i = 0; i < tasks_number; i++)
    //     {
    //         printf("Id: %d, Task time: %d\n", copied_array[i].id, copied_array[i].time);
    //     }

    bls(copied_array, m, tasks_number);

    free(copied_array);

}

void add_task(proc* processor, task t){
    
    if(processor->tasks_capacity <= processor->tasks_cnt+1){
        processor->tasks_capacity= processor->tasks_capacity*2;
        processor->tasks = (task*)realloc(processor->tasks, processor->tasks_capacity * sizeof(task));
    }
    processor->tasks[processor->tasks_cnt] = t;
    processor->tasks_cnt++;
    



}

void l(){


}

/*
    (S) Shortest Processing Time First algorithm
*/
void spt(task*array, int m, int tasks_number, int real_array_length){
    int Cmax = 0;
    int sigmaC = 0;
    task* copied_array = (task*)malloc(sizeof(task)* real_array_length);
    memcpy(copied_array, array, sizeof(task)* real_array_length);
    
    quicksort(copied_array, 0, tasks_number-1,0);

    proc* processors = init_processors(m, 0);


    int tasks_left = tasks_number;
    int index = 0;
    while(tasks_left > 0){
        
        add_task(processors + (index%m), copied_array[index]);
        index++;
        tasks_left--;
        
    }

    for (int i = 0; i < m; i++)
    {
        quicksort(processors[i].tasks, 0, processors[i].tasks_cnt-1, 1);
        int current_stage_task_time = 0;
        for (int j = 0; j < processors[i].tasks_cnt; j++)
        {   
            current_stage_task_time += processors[i].tasks[j].time;
            sigmaC += current_stage_task_time;
            Record rec;
            rec.finish_time = current_stage_task_time;
            rec.task_id = processors[i].tasks[j].id;

            processors[i].records = append(processors[i].records, rec);
            

        }
        if(current_stage_task_time > Cmax) Cmax = current_stage_task_time;

    }

    print_output(processors,m, sigmaC, Cmax);

    free(copied_array);

}
/*
    (A) returns optimal Cmax
*/
void optimal_way(task*array, int m){




    
}


int main(){

    int initial_array_length;

    scanf("%d", &initial_array_length);
    int real_array_length = initial_array_length;

    int tasks_number = initial_array_length;

    int next_task_id = real_array_length +1;

    task *task_array = (task*)malloc(sizeof(task)*real_array_length);

    // baisic input array input handling
    for (int i = 0; i < initial_array_length; i++)
    {
        int task_time_input;
        scanf("%d", &task_time_input);
        task_array[i].id = i+1;
        task_array[i].time = task_time_input;
    }
    // int current_largest_id = initial_array_length+1;


    
    

    int condition = 1;
    char o;
    while(condition && scanf(" %c", &o) == 1){

        
        // scanf(" %c", &o);

        switch (o)
        {
        case '+':
            {
                int k,p;

                scanf(" %d", &k);

                scanf(" %d", &p);
                k=k-1;
                task_array = array_addition(task_array,k,p,&real_array_length,&tasks_number,&next_task_id);

                break;
            }
        case '-':{
            int id_to_remove;
            scanf(" %d", &id_to_remove);
            task_array = removing_element(id_to_remove, task_array, &tasks_number);

            break;
        }

        
        case 'p':{

            for (int i = 0; i < tasks_number; i++)
            {
                printf("Id: %d, Task time: %d\n", task_array[i].id, task_array[i].time);
            }
            break;
        }
        case 'B':{
            int m;
            scanf("%d", &m);
            bls(task_array,m,tasks_number);
            break;
        }
        case 'L':{
            int m;
            scanf(" %d", &m);
            lpt(task_array,m,tasks_number, real_array_length);
            break;
        }
        case 'S':{
            int m;
            scanf(" %d", &m);
            spt(task_array,m,tasks_number, real_array_length);
            break;
        }

        case 'e':{
            condition = 0;
            break;
        }
        
        default:{
            break;
        }
            
        }


    }


    free(task_array);
    
    return 0;
}