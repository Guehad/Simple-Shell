#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAXIMUM 600

int flag =0;

void removeEOL(char line[]){
    int i=0;
    while (line[i] !='\n')
     i++;

  line[i]='\0';

//  if (flag == 1)
 // {   int i=0;
   // while (line[i] !='&')
     //i++;

  //line[i]='\0';
 // }
}

void readInput(char line[]){

    fgets (line,MAXIMUM,stdin);
    setflag(line);
   // if (strchr (line,'&') != NULL)
    //{printf("no");
    //flagg=1;
    //}


}

void parsing(char* args [],char line []){

int i=0;
args[i] = strtok(line," ");



 while (args [i] != NULL )

{
     i++;
     args[i] = strtok(NULL," ");
}
//if (strcmp (args[0],"exit")==0){
 //exit(0);
 //}

if (strcmp (args[0],"cd")==0){
changeDirectory(args);
}
}


int readandparse( char* args [],char line []){
int i=0;
readInput(line);
removeEOL(line);


parsing(args,line);

//if (strcmp (args[0],"exit")==0){
 //exit(0);
 //}
return 1;

}


void showdirect()
{
 char sp[1024];
    getcwd(sp,sizeof(sp));
    printf("shell%s: ",sp);
}

int setflag(char* line)
{
    if(strchr(line,'&'))
   {    printf("i found it\n");
        flag=1;
        return 1;
   }
    else
    flag=0;
return 0;
}
int changeDirectory(char** args)
{

    //hay default 3al home
    if (args[1] == NULL) {
        chdir(getenv("HOME"));

        return 1;
    }
    // hay append el directory el sa7
    char  gdir[1024];
    char  *dir;
    char  *to;
            getcwd(gdir, sizeof(gdir));
            dir = strcat(gdir, "/");
            to = strcat(dir, args[1]);
            chdir(to);
        if (chdir(to) == -1) {
            perror("error occured");
            return -1;
        }

  return 0;
}
void startFork(char *args []){
FILE *log_file= fopen("LogFile3", "w");
int j=1;
pid_t pid = fork();
    if(pid<0)
    {
        fprintf(stderr , "Can't create a child \n");
        exit(-1);
    }

    else if (pid==0) //Child process
    {
        if (execvp( args[0] , args) )
        printf("child process running now \n");

    }

    else //Parent process
    {

        if(!flag)
       {
//do {
  //    waitpid(pid, &status, WUNTRACED);
    //} while (!WIFEXITED(status) && !WIFSIGNALED(status));
  //}
          printf("Parent process is Waiting for child process to finish \n");
            wait(NULL);

         printf("Child process is done\n");
         fprintf(log_file,"Child Process %d is terminated \n", j++);



    }
}
}


int main()
{  int fg=1;
   char* args [15]; //max number of words
   char line [MAXIMUM]; //max number of letters in line

   while (fg=1) {
showdirect();
readandparse (args,line);
/*pid_t child_pid;
int status=0;
   child_pid = fork();
   if(child_pid >=0)
{
    if (child_pid ==0)
    {
        execvp (args[0],args);

    }

    else {
        //waitpid (child_pid,0);
        wait(NULL);
 }   }*/
// if (strcmp(args[0]=="cd")) changeDirectory(args);
  //else {


//}

if(!strcmp(line,"exit"))
   { fg=0;
   exit(0);
   }
if (!strcmp(line,"clear")) system("clear");
startFork(args);

}
    return 0;

}
