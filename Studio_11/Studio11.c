#include <stdio.h>
#include <pthread.h>

int race = 0;

void* adder(void * p)
{
    int i;
    pthread_mutex_t* mutex = (pthread_mutex_t*)p;
    //pthread_mutex_lock(mutex);
    for (i = 0; i < 20000000; i++)
    {
        pthread_mutex_lock(mutex);
        race++;
        pthread_mutex_unlock(mutex);
    }  
    //pthread_mutex_unlock(mutex);
    return 0;
}

void* subtractor(void * p)
{
    pthread_mutex_t* mutex = (pthread_mutex_t*)p;
    //pthread_mutex_lock(mutex);
    int i;
    for (i = 0; i < 20000000; i++)
    {
        pthread_mutex_lock(mutex);
        race--;
        pthread_mutex_unlock(mutex);
    }  
    //pthread_mutex_unlock(mutex);
    return 0;
}

int main(int argc, char* argv[])
{
    //adder();
    //subtractor();
    pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER; 
  
    pthread_t t_add;
    pthread_t t_sub;

    pthread_create(&t_add, NULL, adder, &mutex);
    pthread_create(&t_sub, NULL, subtractor, &mutex);

    pthread_join(t_add, NULL);
    pthread_join(t_sub, NULL);

    printf("%d\n", race);

    return 0;
}
