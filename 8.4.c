#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>

void* thread_function(void*){
    long double pi = 3.1415;
    pi/=4;
    for(int i = 3;i < 100000;i+=2){
        int old_cancel_state;
        pthread_setcanceltype(PTHREAD_CANCEL_DISABLE, &old_cancel_state);
        pi += 1 - 1/i;
        fprintf(stdout,"pi = %Lf\n", pi);
        pthread_setcanceltype(old_cancel_state, NULL);
        sleep(); // canceled point
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
    pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
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