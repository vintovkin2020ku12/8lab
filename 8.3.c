#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* thread_function(void*){
    for(int i = 0;i != -1;i++){
        fprintf(stdout, "Hello world! num iteration = %d\n", i);
        sleep(1);
    }
    return NULL;
}

int main(int argc, char** argv){
    if(argc != 2){
        fprintf(stdout, "Enter time ping!!!");
    }
    void* result;
    int ping = atoi(argv[1]);
    int old_cancel_state;
    pthread_t thread;
    pthread_setcanceltype(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
    if(pthread_create(&thread, NULL, &thread_function, NULL) != 0){
            fprintf(stderr,"main error: can't create thread\n");
            return 1;
    }
    pthread_setcanceltype(old_cancel_state, NULL);
    sleep(ping);
    pthread_cancel(thread);
    
    if(!pthread_equal(pthread_self(), thread))
        pthread_join(thread, &result);

    if(result == PTHREAD_CANCELED)
        fprintf(stderr, "Canceled\n");
        
    if(pthread_join(thread, NULL) != 0){
            fprintf(stderr, "Join error thread\n");
            return 1;
        }
    return 0;
}