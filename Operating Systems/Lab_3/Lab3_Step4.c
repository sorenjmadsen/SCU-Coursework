// Name: Soren Madsen
// Date: 23 Jan 2020
// Title: Lab 3 Step 4
// Description: Using a pipe, this implements the shell command:  cat /etc/passwd | grep root

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h> 
#include <sys/wait.h> 
//main
int main() {
 	int fds[2];
 	pipe(fds);

	if (fork() == 0) {
		dup2(fds[0], 0);							// 0 denotes stdin
		close(fds[1]);
		execlp("grep", "grep", "root", 0);          // Uses extra argument in execlp() for the grep argument
	}
	
	else if (fork() == 0) {
		dup2(fds[1], 1);							// 1 denotes stdout
		close(fds[0]);
		execlp("cat", "cat", "/etc/passwd", 0);     // Same situation as a bove, but with cat
	}
	else {  /*parent closes both ends and wait for children*/
		close(fds[0]);
		close(fds[1]);
		wait(0);
		wait(0); 
	}
} 
