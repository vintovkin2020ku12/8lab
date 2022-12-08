#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<malloc.h>

void* allocate_buffer(size_t size){
    return malloc(size);
}

void deallocate_buffer(void* buffer){
    free(buffer);
}

void do_some_work(){
    void* temp_buffer = allocate_buffer(1024);
    pthread_cleanup_push(deallocate_buffer, temp_buffer);
    pthread_cleanup_pop(1);
}

void* thread_function(void*){
    for(int i = 0;i != -1;i++){
        fprintf(stdout, "Hello world! num iteration = %d\n", i);
        do_some_work();
        sleep(1);
    }
    return NULL;
}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stdout, "Enter time ping!!!");
    }
    int ping = atoi(argv[1]);
    pthread_t thread;
    pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS, NULL);
    if(pthread_create(&thread, NULL, &thread_function, NULL) != 0){
            fprintf(stderr,"main error: can't create thread\n");
            return 1;
    }

    sleep(ping);
    int result = pthread_cancel(thread);
    if(result == 0)
        fprintf(stderr, "pthread_cancel work!!!\n");
    else
        fprintf(stderr, "pthread_cancel not working!!!\n");
    if(pthread_join(thread, NULL) != 0){
            fprintf(stderr, "Join error thread\n");
            return 1;
        }
    return 0;
}