#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
#include <string.h>

using namespace std;

char *cmd1[] = { "/bin/ls", "ls -l", 0};
char *cmd2[] = { "/bin/wc", "-l", 0 };
char *cmd3[] = { "sort", 0};

void run2com(int[]);

int main(int argc, char **argv)
{
	int pid, status;
	int fd[2];

string input;
cout << "$myShell>";
cin >> input;
string pi = "|";
while(input.compare("exit") != 0){
	pipe(fd);
  
	int inputPi = input.find(pi);
	if(inputPi == std::string::npos)
  {
		strcpy(cmd1[1], input.c_str());
	  strcpy(cmd2[1], '\0');
	}
	else
  {
		strcpy(cmd1[1],input.substr(0, inputPi).c_str());
		strcpy(cmd2[1],input.substr(inputPi + 1, input.size()).c_str());
	}
	pid = fork();
	if (pid == 0) {
		run2com(fd);
		exit(0);
	} else if (pid > 0) {
		while ((pid = wait(&status)) != -1)
		 fprintf(stderr, "process %d exits with %d\n", pid, WEXITSTATUS(status));
	} else {
		perror("fork");
		exit(1);
	}
	cout << "$myShell>";
	cin >> input;
}
	exit(0);

}


void run2com(int pfd[])

{
	int pid;
	pid = fork();
	if (pid ==0) {
		dup2(pfd[0], 0);
		close(pfd[1]);	
		execvp(cmd2[0], cmd2);
		perror(cmd2[0]);
	} else if (pid > 0) {
		dup2(pfd[1], 1);
		close(pfd[0]);	
		execvp(cmd1[0], cmd1);
		perror(cmd1[0]);
	} else {
		perror("fork");
		exit(1);
	}
}
