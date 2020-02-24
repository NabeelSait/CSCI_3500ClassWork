//Nabeel Sait
//2/16/2020
//This program brute-force cracks a DES encryption

#define _GNU_SOURCE
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <crypt.h>
#include <string.h>

char alphabet[94] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!\"#$%&'()*+,-./0123456789:;<=>?@[]\\^_'{}|~";
int c_size;

struct c_args {
   char* target;
   char password[8];
   char* salt;
   int keySize;
   int a_start;
   int a_end;
   int ret;
   pthread_mutex_t mutex;
   pthread_t* thread_id;
   int threadCount;
};

char* crack(char password[8], char* target, char salt[3], int keySize, int index);

void* thread_entry(void* args);

int main(int argc, char* argv[])
{
   //Taking command line arguments
   if (argc < 4)
   {
      printf("usage: crack <thread> <keysize> <target> <useAll>");
      printf("\n");
      exit(-1);
   }
   int threadCount = strtol(argv[1], NULL, 10);
   int keySize = strtol(argv[2], NULL, 10);
   char* target = argv[3];
   c_size = 26;
   if (argc == 5)
   {
      if (strtol(argv[4],NULL,10) == 1)
      {
         c_size = 93;
      }
   }

   //Generating thread IDs and mutex
   pthread_t thread_id[threadCount];
   struct c_args structures[threadCount];
   pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

   if ((keySize <= 0) || (keySize > 8) )
   {
      printf("Error: Invalid keySize (must be greater than 0 and less than 8) \n");
      exit(-1);
   }
   if (threadCount <=0)
   {
      printf("Error: Invalid thread count \n");
      exit(-1);
   }

   //Getting salt
   char salt[3];
   strncpy(salt, target, 2);

   //Figuring out how to split threads
   int inc = c_size/threadCount;
   if ((inc*threadCount) != c_size)
      inc++;

   //Generating structs
   int i;
   for(i = 0; i < threadCount; i++)
   {
      structures[i].target = target;
      structures[i].salt = salt;
      structures[i].keySize = keySize;
      structures[i].a_start = i*inc;
      structures[i].a_end = structures[i].a_start + inc;
      structures[i].ret = 0;
      structures[i].mutex = mutex;
      structures[i].thread_id = thread_id;
      structures[i].threadCount = threadCount;
      if (structures[i].a_end > c_size)
         structures[i].a_end = c_size;
   }

   //Creating threads
   for(i = 0; i < threadCount; i++)
   {
      pthread_create(&thread_id[i], NULL, thread_entry, &structures[i]);
   }

   for(i = 0; i < threadCount; i++)
   {
      pthread_join(thread_id[i], NULL);
      if (structures[i].ret == 1)
      {
         printf("Cracked password: %s\n", structures[i].password); //Outputting cracked password
         exit(0);
      }
   }
}


char* crack(char password[8], char* target, char salt[3], int keySize, int index)
{
   //Setting up vairables
   char np[keySize];
   strncpy(np, password, keySize);
   int j;
   struct crypt_data data;
   data.initialized = 0;

   for (j = 0; j < c_size; j++) //Checking each alphabet for each position
   {
      np[index] = alphabet[j];
      strncpy(password, np, keySize);
      if (index < (keySize - 1))
      {
         char* r_res = crack(password, target, salt, keySize, index+1); //Recursing until keySize
         if (r_res != NULL)
         {
            return r_res;
         }
      }
      char* res = crypt_r(np, salt, &data); //Checking current password
      if (strcmp(res, target) == 0)
      {
         strcpy(password, np);
         return res;
      }
   }
   return NULL;
}

void* thread_entry(void* args)
{
   struct c_args* argPtr = (struct c_args*)args;
   int i;
   pthread_mutex_lock(&argPtr->mutex);
   for (i = argPtr->a_start; i < argPtr->a_end; i++) //Setting alphabet range for first character
   {
      char np[8];
      strcpy(np, argPtr->password);
      np[0] = alphabet[i];
      char* res = crack(np, argPtr->target, argPtr->salt, argPtr->keySize, 1); //Calling crack with first character set
      if (res != NULL)
      {
         strcpy(argPtr->password, np);
         pthread_mutex_unlock(&argPtr->mutex);
         argPtr->ret = 1;
         for (i = 0; i < argPtr->threadCount; i++) //CLosing all other threads once password is found
         {
            if(argPtr->thread_id[i] != pthread_self())
               pthread_cancel(argPtr->thread_id[i]);
         }
         pthread_exit(NULL);
      }
   }
   pthread_mutex_unlock(&argPtr->mutex);
}
