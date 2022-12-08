#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>

int* global_arr;
int size;

int rand_num(){
    srand(time(NULL));
    return rand() % 10 + 1;
}

void* status_arr(void*){
    int flag = 0;
    while(1){
        flag = 0;
        for(int i = 0; i < size;i++){
            if(global_arr[i] == 0){
                flag = 1;
            }
            fprintf(stdout,"thread[%d] = %d\n",i, global_arr[i]);
        }
        fprintf(stdout,"------------------------------------\n");
        if(flag == 0){
                fprintf(stdout,"Thread exit. Array fill!!!\n");
                return 0;
        }
        sleep(1);
    }
    return NULL;
}

void* thread_function(void* thread_arg){
    int number_thread = *(int*) thread_arg;
    fprintf(stdout,"num thread = %d\n", number_thread);
    sleep(number_thread);
    global_arr[number_thread] = rand_num();
    sleep(global_arr[number_thread]);
    return NULL;
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Enter numbers of threads!!!\n");
        return 0;
    }
    int NUM_THREADS = atoi(argv[1]);
    size = NUM_THREADS;
    global_arr = (int*)malloc(sizeof(int) * size);
    pthread_t thread[NUM_THREADS];
    pthread_attr_t attr;
    pthread_t thread_atr;
    for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&thread[i], NULL, &thread_function, &i) != 0) {
            fprintf(stderr,"main error: can't create thread, num = %d\n", i);
            return 1;
        }
        sleep(1);
    }
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&thread_atr, &attr, &status_arr, NULL);
    pthread_attr_destroy(&attr);
    for (int i = 0; i < NUM_THREADS; i++) {
        if(pthread_join(thread[i], NULL) != 0){
            fprintf(stderr, "Join error thread num = %d\n", i);
            return 1;
        }
        fprintf(stdout,"joined with num address = %d\n", i);
    }
    return 0;
}