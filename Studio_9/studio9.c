//Nabeel Sait and Cemil Can Ali Marandi
//2/7/2020
//This program assists in learning threads

#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

struct my_struct {
   int arg1;
   char arg2[100];
   int ret;
};

void* thread_entry(void* args)
{
  struct my_struct* arg_ptr = (struct my_struct*)args;
  printf("thread arg1: %d\n", arg_ptr->arg1);
  printf("thread arg2: %s\n", arg_ptr->arg2);
  printf("threat ret: %d\n", arg_ptr->ret);
  arg_ptr->ret = 15;
  return NULL;
}

int main(int argc, char* argv[])
{
    int num_threads = 5;
    pthread_t thread_id[num_threads];
    struct my_struct structures[num_threads];
    unsigned bufSize = 100;

    int i;
    for(i = 0; i < num_threads; i++) 
    {
      structures[i].arg1 = i;
      structures[i].ret = i+1;
      snprintf(structures[i].arg2, bufSize, "This is thread %d", i);
    }

    for(i = 0; i < num_threads; i++) 
    {
       pthread_create(&thread_id[i], NULL, thread_entry, &structures[i]);
    }
     
    for(i = 0; i < num_threads; i++) 
    {
       pthread_join(thread_id[i], NULL);
    }

    printf("thread return value is now: %d\n", structures[0].ret);
}    
