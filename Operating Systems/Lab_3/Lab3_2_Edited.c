// Name: Soren Madsen
// Date: 23 Jan 2020
// Title: Lab 3 Step 3: Modify Lab_3_2.c so the write passes the output of the "ls" command
// Description: Uses write to pipe the output of ls to a loop that prints it in a special way.
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <string.h>
#include <sys/wait.h> 

// main
int main(int argc,char *argv[]){
   int  fds[2];
   char buff[60];
   char exec_buff[60];
   int count;
   int i;
   pipe(fds);
   
   if (fork()==0){
       printf("\nWriter on the upstream end of the pipe -> \"ls\" command \n");
       close(fds[0]);
       dup2(fds[1], 1);
       execlp("ls", "ls", 0);
       exit(0);
   }
   else if(fork()==0){
       printf("\nReader on the downstream end of the pipe \n");
       close(fds[1]);
       dup2(fds[0], 0);
       while((count=read(fds[0],buff,60))>0){
           for(i=0;i<count;i++){
               write(1,buff+i,1);
               write(1," ",1);
           }
           printf("\n");
       }
       exit(0);
    }
   else{     
      close(fds[0]);
      close(fds[1]);
      wait(0);
      wait(0);
   }
return 0;
}
