#include <stdio.h>
#include <pthread.h>

int race = 0;

void* adder(void * p)
{
    int i;
    for (i = 0; i < 20000000; i++)
    {
        __sync_add_and_fetch(&race, 1);
    }  
    return 0;
}

void* subtractor(void * p)
{
    int i;
    for (i = 0; i < 20000000; i++)
    {
       __sync_sub_and_fetch(&race, 1);
    }  
    return 0;
}

int main(int argc, char* argv[])
{
    //adder();
    //subtractor();

    pthread_t t_add;
    pthread_t t_sub;

    pthread_create(&t_add, NULL, adder, NULL);
    pthread_create(&t_sub, NULL, subtractor, NULL);

    pthread_join(t_add, NULL);
    pthread_join(t_sub, NULL);

    printf("%d\n", race);

    return 0;
}
