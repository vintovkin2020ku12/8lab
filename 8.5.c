#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<time.h>
#include<malloc.h>

static pthread_key_t thread_log_key;

void write_to_thred_log(const char* message){
    FILE* thread_log = (FILE*)pthread_getspecific(thread_log_key);
    fprintf(thread_log, "%s\n", message);
}

void close_thred_log(void* thread_log){
    fclose((FILE*)thread_log);
}

int rand_num(){
    srand(time(NULL));
    return rand() % 10 + 1;
}


void* thread_function(void* thread_arg){
    int number_thread = *(int*) thread_arg;
    char thread_log_filename[20];
    FILE* thread_log;
    sprintf(thread_log_filename, "thread%d.log",number_thread);
    thread_log = fopen(thread_log_filename, "w");
    pthread_setspecific(thread_log_key, thread_log);
    write_to_thred_log("Thread starting.");
    for(int i = 0;i < number_thread;i++)
        fprintf(thread_log,"hello%d,num thread = %d, rand_num = %d\n",number_thread, number_thread, rand_num());
    sleep(1);
    return NULL;
}

int main(int argc, char** argv){
    if(argc != 2){
        printf("Enter numbers of threads!!!\n");
        return 0;
    }
    int NUM_THREADS = atoi(argv[1]);
    pthread_t thread[NUM_THREADS];
    pthread_key_create(&thread_log_key, close_thred_log);
 
  
    for (int i = 0; i < NUM_THREADS; i++) {
    if (pthread_create(&thread[i], NULL, &thread_function, &i) != 0) {
            fprintf(stderr,"main error: can't create thread, num = %d\n", i);
            return 1;
        }
        sleep(1);
    }

    for (int i = 0; i < NUM_THREADS; i++) {
        if(pthread_join(thread[i], NULL) != 0){
            fprintf(stderr, "Join error thread num = %d\n", i);
            return 1;
        }
        fprintf(stdout,"joined with num address = %d\n", i);
    }
    return 0;
}