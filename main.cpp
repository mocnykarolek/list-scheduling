

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
    

} proc;

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

    memmove(a+ insertion_index+1, (a+insertion_index), elements_to_move * sizeof(task));

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

    if(r->next == nullptr){
        return;
    }


    clear_linked_list(r->next);
    free(r);
    

}
/*
    (B) Basic list scheduling
*/
void bls(task*array, int m, int tasks_number){
    int time;
    proc* processors = (proc*)malloc(sizeof(proc)*m);
    int Cmax = 0;
    int sigmaC = 0;

    for (int i = 0; i < m; i++)
    {
        processors[i].p_number = i+1;
        processors[i].time_usage = 0;
        processors[i].tasks_cnt = 0;
        // processors[i].records = (Record*)malloc(sizeof(Record));
        processors[i].records = nullptr;
        
    }
    


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
    }
    
    
    

    free(processors);

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
    
    while(condition){

        char o;
        scanf(" %c", &o);

        switch (o)
        {
        case '+':
            {
                int k,p;

                scanf(" %d", &k);

                scanf(" %d", &p);

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