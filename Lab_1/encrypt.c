// Nabeel Sait and Cecil Can Ali Marandi
// 1/15/2020
// Run-length encoding

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char* argv[]) {


   if (argc != 5)
   {
      char usage[] = "usage: ./rle <input_file> <output_file> <compression length> <mode>";
      write(STDOUT_FILENO, usage, 67);
      printf("\n");
      exit(-1);
   }

   char* inputFileName = argv[1];
   char* outputFileName = argv[2];
   int k = strtol(argv[3], NULL, 10);
   int mode = strtol(argv[4], NULL, 10);

   if (k < 1)
   {
      fprintf(stdout, "Error: compression length must be greater than 1 \n");
      exit(-1);
   }

   if ((mode != 0) && (mode != 1))
   {
      fprintf(stdout, "Error: mode must be either 1 or 0 \n");
      exit(-1);
   }

   int inputFD = open(inputFileName, O_CREAT, S_IRUSR);
   if (inputFD == -1)
   {
      perror("open(inputFileName, O_CREAT, S_IRUSR)");
      exit(-1);
   }

   int outputFD = open(outputFileName, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR);
   if (outputFD == -1)
   {
      perror("open(outputFileName, O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR)");
      exit(-1);
   }

   if (mode == 0)
   {
      char buffer[k];
      char prev[k];
      int bytes_read = read(inputFD, buffer, k);
      int count = 0;
      memcpy(prev, buffer, k);

      while (1)
      {
         if (bytes_read == -1)
         {
            perror("read(inputFD, buffer, k)");
            exit(-1);
         }

         if ((strcmp(prev, buffer) != 0) || (count >= 255))
         {
            if (write(outputFD, &count, 1) == -1)
            {
               perror("write(outputFD, &count, 1)");
               exit(-1);
            }

            if(write(outputFD, prev, k) == -1)
            {
               perror("write(ouputFD, prev, k)");
               exit(-1);
            }

            count = 1;
            memcpy(prev, buffer, k);
         }
         else
         {
            count ++;
         }

         int temp = read(inputFD, buffer, k);
         if (temp <= 0)
           break;
         else
           bytes_read = temp;
      }

      write(outputFD, &count, 1);
      write(outputFD, prev, bytes_read);
   }

   if (mode == 1)
   {
      int num = 0;
      int check_end = read(inputFD, &num, 1);
      while(check_end > 0)
      {
         if (check_end == -1)
         {
            perror("read(inputFD, &num, 1)");
            exit(-1);
         }
         char buffer[k];

         //printf("%d", num);
         //printf("\n");
         int bytes_read = read(inputFD, buffer, k);
         if (bytes_read == -1)
         {
            perror("read(inputFD, buffer, k)");
            exit(-1);
         }
         
         int count = 0;
   
         while (count < num)
         {
            //printf("%d", num);
            if (write(outputFD, buffer, bytes_read) == -1)
            {
               perror("write(outputFD, buffer, k)");
               exit(-1);
            }

            count++;
         }
         check_end = read(inputFD, &num, 1);
      }
   }
   close(inputFD);
   close(outputFD);
}
