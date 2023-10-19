/**
 * @file main.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <stdio.h> /* /usr/include is where these are stored */
#include <stdlib.h>

#define BUFFER 256;

/* Need to rename file to batchpro and it will recieve 2 args, the first
   being the number of max processes that can be executed at once and the 
   second being a batch file which contains various program calls */

int main(int argc, char *argv[])
{
    /* We will be using the fork command which is on fork(2) of the man pages.
       Requires the <unistd.h> header and prototype is pit_t fork(void); 
       Duplicates the calling process and the old will be a parent and the new is
       the child. The child will have a unique process ID. The child process will
       continue on and be mindful using fork in a loop as it can go infinite. You will
       want to display the new process ID of the child. 

       getpid() finds the process ID
       getppid() finds the parents process ID
       getuid() finds the owner's user ID

       <sys/types.h> is needed for getuid()

       We cannot use system since it basically does the entire thing we are doing.
       Use exec and fork functions

       We will be using the code from the first two assignments. Slides on the functions exec and fork are 
       on the class website.

      Brief definitions: 
       fork: duplicates a process
       getpid: obtains a process ID number 
       getppid: obtains a parent process ID number
       exit: terminates a process 
       wait: waits for child process
       exec: replaces the code, data, and stack of a process


      Example:
       Parent process PID 34 running shell -> duplicate using fork()
         - child process pid 35 running shell
         - parent is watiing for child with wait()
         - child process differentiates with exec()
         - child process will swap over to running a utility
         - terminate the child process, and once terminated, signal back to parent who is waiting
         - parent process will then proceed once the child is finished. Be sure to use wait because you can create an orphan by not waiting
         - The signal will cause the wait function to suspend and cause the parent to awaken
      */



      int pid, status ,childPid;
      pid = fork(); /* Duplicate and the child will execute code below this function */
      if(pid!=0)
      {
         prinft("I'm parent process\n");
         childPid = wait(&status); /* wait for child process */
         prinft("A child process with PID childPid and terminated with exit code");


      }
      else
      {
         printf("I am child process and my PID is ~~~~~\n");

         exit(42); /* Exit with any int number to specify what happened */
      }


      /*
         For the while loop, 
      
      
      
      
      
      
      
      
      
      */



       



    return 0;
}