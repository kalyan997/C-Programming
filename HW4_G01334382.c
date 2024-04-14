//CS_531 Homework - 4
//Kalyan Baddam
//G01334382


#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<string.h>


//After sig stop, not going to parent through direct termination but working through INT
//printing of stopped by not printing


int cs531_system(char *s){
    pid_t child,w;
    
    //Using fork to create child process
    child = fork();
    int status;
    
    
    sig_t sigint_sav;
    sig_t sigquit_sav;
    
    //Handling(SIGINT and SIGQUIT) to ignore in parent process
    sigint_sav = signal(SIGINT, SIG_IGN);
    sigquit_sav = signal(SIGQUIT, SIG_IGN);
    
    //Redirecting output to terminal using dev/tty and dup
    int tt = open("/dev/tty",O_RDWR);
    
    //char *commands[2];
    /*sscanf(s,"%s %s",commands[0],commands[1]);
    printf("1st arg %s\n", commands[0]);
    printf("2nd arg %s\n", commands[1]);*/
    
    
    //Tokenzing the string passed in the argument
    /*char *token = strtok(s, " ");
      
    int i = 0;
    while (token != NULL) {
        //printf("%s\n", token);
        commands[i] = token;
        token = strtok(NULL, " ");
        i++;
    }*/
    
    switch( child )
    {
        //If fork() fails
        case -1:
        {
            // an error occurred
            perror( "fork failed" );
            exit( EXIT_FAILURE );
            break;
        }
        
        //child process
        case 0:
        {
            //int status;
            //int tt = open("/dev/tty",O_RDWR);
            
            //closing stdout and output to controlling terminal
            close(1);
            dup(tt);
            //close(2); dup(tt);
            //close(tt);
            //execlp(s,s,t,NULL);
            
            //Using execlp for shell commands
            //execlp(commands[0], commands[0], commands[1], NULL);
            execlp("sh","sh","-c", s, (char *)0);
            //closing controlling terminal
            close(tt);
            // the exec* functions never return
            // unless unable to generate
            // the child process
            //perror( "execv failed" );
            
            //catching status of child process and sending to parent
            _exit(status);
            //close(tt);
            break;
        }
            
        //parent process
        default:
        {
            //int status;
            do
            {
                //waiting for child and getting its status
                w = waitpid(child, &status, WUNTRACED | WCONTINUED);
                
                //Restoring signals to its previous process after child process
                signal(SIGINT,sigint_sav);
                signal(SIGQUIT,sigquit_sav);
                if (w == -1) {
                perror("waitpid");
                exit(EXIT_FAILURE);
                }
                    
                if (WIFEXITED(status)) {
                printf("exited, status=%d\n", WEXITSTATUS(status));
                }
                else if (WIFSIGNALED(status)) {
                printf("killed by signal %d\n", WTERMSIG(status));
                }
                else if (WIFSTOPPED(status)) {
                printf("stopped by signal %d\n", WSTOPSIG(status));
                }
                else if (WIFCONTINUED(status)) {
                printf("continued\n");
                }
    
            }while (!WIFEXITED(status) && !WIFSIGNALED(status));
                //exit(EXIT_SUCCESS);
                /*close(tt);
                //dup(stdout);
                //int file = open("out.txt", O_WRONLY | O_CREAT, 0777);
                //close(1);
                //dup(file);
                //printf("parent process is sleeping");
                //sleep(10)*/
            break;
        }
    }
    return 0;
};

int main(int argc, char *argv[]){
    int status;
    status = cs531_system(argv[1]);
    printf("\nParent process is sleeping…\n");
    sleep(10);
    return status;
}
