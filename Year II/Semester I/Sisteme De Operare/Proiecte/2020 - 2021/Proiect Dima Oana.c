/*
Sisteme de operare: Ianuarie 2021
Dima Oana, Dorneanu Alina, Badescu Gabriel
Grupa 241
*/
//se compileaza cu flag-ul: -lreadline
//inainte de compilare am instalat GNU Readline:
//$ sudo apt-get install libreadline-dev

#include<stdlib.h>
#include<errno.h>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<fcntl.h>

//biblioteci noi
#include<dirent.h>//informatii despre directoare(scandir)
#include<readline/readline.h>
#include<readline/history.h>

int bg_proc;

//Comenzi
int new_help();
int new_cd(char**);
int new_pwd();
int new_ls();
int new_cp(char**);
int new_mkdir(char**);
int new_rmdir(char**);
int new_rm(char**);
int new_clear();

int execute_command(char **, int ok);


struct command
{
 	char **argv;
};

char* commands[] =
{
	"new_help",
	"new_cd", 
	"new_pwd",
	"new_ls",
	"new_cp",
	"new_mkdir",
	"new_rmdir",
	"new_rm",
	"new_clear"
};
//functie definita ca un vector incomplet
//de pointeri la functiile din shell care primeste 
//un pointer la pointer de tip char si returneaza int

int (*functions[]) (char**) =
{
	&new_help,
	&new_cd, 
	&new_pwd,
	&new_ls,
	&new_cp,
	&new_mkdir,
	&new_rmdir,
	&new_rm,
	&new_clear
	
};

int new_help()
{
	
	printf("\nShell Commands:\n");
	printf("----------------------------------------------------------\n\n");
	
	printf("new_cd: change directory \n");
	printf("new_pwd: show the path of the current working directory \n");
	printf("new_ls: list of files from the current directory \n");
	printf("new_cp: copy files from source1 to source2 \n");
	printf("new_mkdir: create a new directory\n");
	printf("new_rmdir: delete directory \n");
	printf("new_rm: delete file \n");
	printf("new_clear: clear the terminal \n");

	printf("\n----------------------------------------------------------");

	printf("\nMade by: Dima Oana, Dorneanu Alina, Badescu Gabriel\n");
	printf("Group 241, January 2021\n\n");

	return 0;
}

int new_cd(char** args)
{
	if(args[1] == NULL)
	{
		fprintf(stderr, "Expected an argument for the directory's name!\n");
	}
	else
	{
		if(chdir(args[1]) != 0)
		{
			perror("Error!");
			return 1;
		}
	}

	return 0;
}

int new_pwd()
{
	char buff[1024];
	//ia numele directorului curent 
	//si il pune in buf
	getcwd(buff, sizeof(buff));
	printf("Directory: %s\n", buff);

	return 0;
}

int new_ls()
{
	int n;
	//structura care detine informatii 
	//despre directorii de intrare
	struct dirent** namelist;
	//functie de sistem man 3 scandir
	//alphasort sortare pe string-uri 
	//"."=scanare director parinte
	n = scandir(".", &namelist, NULL, alphasort);
	
	if(n < 0)
	{
		perror("Error scanning the directory!");
		return 1;
	}

	else
	{
		int columns = 4;
		while(n--)
		{
			//d_name are numele fisierului
			printf("%s        ", namelist[n]->d_name);
			columns--;

			if(columns == 0)
			{
				printf("\n");
				columns = 4;
			}

			free(namelist[n]);
		}
	}

	free(namelist);

	return 0;
}

int new_cp(char** args)
{
	char c;
	FILE *f1, *f2;
	
	if((f1 = fopen(args[1], "r")) == NULL)
	{
		printf("Unable to open file! \n");
		return 1;
	}

	f2 = fopen(args[2], "w");
	//citeste caracter cu caracter
	c = fgetc(f1);

	while(c != EOF)
	{
		//scrie caracter cu caracter
		fputc(c, f2);
		c = fgetc(f1);
	}

	fclose(f1);
	fclose(f2);

	return 0;
}

int new_mkdir(char** args)
{
	//creaza un nou director cu 
	//numele a ce se afla in args[1]
	//0777 (octal) este un mod de permisiune
	if(mkdir(args[1], 0777) == -1)
	{
		perror("Unable to create directory! \n");
		return 1;
	}
	else
	{
		printf("Directory created. \n");
	}

	return 0;

}

int new_rmdir(char** args)
{
	if(rmdir(args[1]) == -1)
	{
		perror("Unable to delete directory!\n");
		return 1;
	}

	else
	{
		printf("Directory deleted. \n");
	}

	return 0;
}

int new_rm(char** args)
{
	if(!remove(args[1]))
	{

		printf("File deleted.\n");
	}
	else
	{
		printf("Unable to delete file!\n");
		return 1;
	}
	return 0;
}

int new_clear()
{
	write(1, "\33[H\33[2J", 7);

	return 0;
}


char** parse_command(char *line, int* dimension)
{
	//impartirea liniei in lista de argumente
	int pos = 0;
	int buff = 64;
	
	char* p;
	char** pp = malloc(buff * sizeof(char*));
	//token memoreaza argumentele date
	//(cd, ls, rmdir, mkdir+ arg lor)
	
	if(!pp)
	{
		//specificam numele fisierului si linia
		//la care a aparut eroarea
		fprintf(stderr, "Allocation error in file %s at line # %d\n", __FILE__, __LINE__);
		exit(1);
	}
	//extragere cuvinte
	p = strtok(line, " \n");
	while(p)
	{
		//folosim strdup care retruneaza un pointer
		//catre un string care se termina in NULL 
		pp[pos] = strdup(p);

		pos++;
		if(pos >= buff)
		{
			buff += 64;
			pp = realloc(pp, buff * sizeof(char*));
			if(!pp)
			{
				fprintf(stderr, "Allocation error in file %s at line # %d\n", __FILE__, __LINE__);
				exit(1);
			}
		}
		p = strtok(NULL, " \n");
	}

	*dimension = pos;
	pp[pos] = NULL;

	return pp;
}

int bin_command(char** args)
{

	//ajunge aici pentru o comanda nedefinita
	//adica nicio comanda de tipul new_com
	int status;
	pid_t pid;
	
	pid = fork();

	if(pid == 0)
	{
		//instructiuni copil
		//execvp(args[0], args)
		//execve(s, args, NULL)==-1
		//daca punem execve(args[0], args, NULL)
		//in args[0] trebuie sa se afle calea relativa
		// /bin/ls
		char s[] = "/bin/";
		strcat(s,(char*)args[0]);

		if(execvp(args[0], args) == -1)
		{
			perror("Error child!");
			exit(1);		
	
		}
		exit(0);	
	}
	else if(pid < 0)
	{
		perror("Error creating a new process!");
		exit(1);
	}
	//instructiuni parinte

	waitpid(pid, &status, 0);

	return WEXITSTATUS(status);

}

int execute_command(char** args, int ok)
{
	int i;

	if(args[0] == NULL)
	{
		return 1;
	}
	//dimensiune comenzi

	int dimension = sizeof(commands)/sizeof(char*);

	if(args[0][strlen(args[0])-1] == '&')
	{
		args[0][strlen(args[0])-1] = 0;

	}

	for(i = 0; i < dimension; i++)
	{
		//cauta comanda printre cele definite aici
		if(strcmp(args[0], commands[i]) == 0)
		{
			
			if(ok == 0)
			{
				return (*functions[i])(args);
				//apel comanda
			}
			if (ok == 1)
			{
				printf("done command");
				return 2;
			}
		}
	}
	//daca nu e definita de noi comanda 
	//poate executa si comenzi ca ls 
	return bin_command(args);
	
	
}

int breed_process(int in, int out, struct command *cmd)
{
	pid_t pid;

	if ((pid = fork ()) == 0)
    {
		if (in != 0)
        {
        	dup2 (in, 0);
         	close (in);
        }

      	if (out != 1)
        {
          	dup2 (out, 1);
          	close (out);
        }

      	return execvp (cmd->argv [0], cmd->argv);
    }

  	return pid;
}

int f_pipes(int n, struct command *cmd)
{
	int i;
	int in, fd [2];
	pid_t pid;
	

  /* primul proces isi ia inputul din file descriptorul 0.  */
	in = 0;

	for (i = 0; i < n - 1; ++i)
    {
		pipe (fd);

      /* f[1] e w, sau in din anterioarea iteratie*/
		breed_process(in, fd [1], cmd + i);

      /* copilul va scrie aici */
		close (fd [1]);

      /* de aici va citi urmatorul copil*/
		in = fd [0];
    }

  /*  output originalul file descriptor 1. */  
	if (in != 0)
	{
		dup2 (in, 0);
	}
    

  /* ultimul pas pt procesul curent */
	return execvp (cmd [i].argv [0], cmd [i].argv);

}

int main()
{
	//Shell
	char* line;
	char** args;
	int status;
	int dimension = 0;
	struct command pipecmd [100];
	int nrp = 0;
	char **cmd1, **cmd2;
	int ok1=0;
	char* a;
	int status1;
	pid_t pid;

	do
	{
		//citire linie
		line = readline("Oana,Alina,Gabi's Shell$ ");
		if(line[0] != 0){


			//adaugare in istoric
			add_history(line);
			//separare in argumente
			
			args = parse_command(line, &dimension);
			
			//&&
			int* position = (int*)malloc(dimension*sizeof(int));
			int k = 0;

			int* position1 = (int*)malloc(dimension*sizeof(int));
			int k1 = 0;

			for(int i = 0;i < dimension; i++)
				if(strcmp(args[i], "&&") == 0)
				{
					position[k++] = i;
					
				}

			for(int i = 0; i < dimension; i++)
				if(strcmp(args[i], "|") == 0)
				{
					position1[k1++] = i;
					
				}

			//printf("%d", k1);
			//verific daca s-a dat comanda cu &&
			//la k de && => k+1 cmd-uri
			if(k > 0)
			{	
				int i = 0;//iterez prin vectorul de pozitii
				int j = 0;//iterez prin argumente
				int n = 0;
				int limit;
				do
				{
					char ** cmd;
					cmd = (char**)malloc(dimension*sizeof(char*));
					
					n = 0;
					if(i == k)
					{
						limit = dimension;
					}
					else
					{
						limit = position[i];
					}

					for(;j < limit; j++)
					{
						cmd[n] = (char*)malloc(strlen(args[j])*sizeof(char*));
						strncpy(cmd[n], args[j], strlen(args[j]));
						cmd[n][strlen(args[j])] = '\0';
						n++;
					}

						
					j = position[i]+1;
					i++;
					
					cmd[n] = NULL;


					status = execute_command(cmd, 0);
					if(status == 1)//a avut eroare
					{
						printf("Wrong command! \n");
						break;
					}
					
					free(cmd);
							
				}
				while(i <= k);
					
			
			}

			else if(k1 > 0)
			{	
				int i = 0;//iterez prin vectorul de pozitii
				int j = 0;//iterez prin argumente
				int n = 0;
				int limit;

				do
				{
					char ** cmd;
					cmd = (char**)malloc(dimension*sizeof(char*));
					
					n = 0;
					if(i == k1)
					{
						limit = dimension;
					}
					else
					{
						limit = position1[i];
					}

					for(;j<limit;j++)
					{
						cmd[n] = (char*)malloc(strlen(args[j])*sizeof(char*));
						strncpy(cmd[n], args[j], strlen(args[j]));
						cmd[n][strlen(args[j])] = '\0';
						n++;
					}

					
					j = position1[i] + 1;
					i++;
					cmd[n] = NULL;
					//cmd[0] - numele functiei
					//cmd[1] - cmd[n-1]


					pipecmd[nrp++].argv = cmd;
					
					
							
				}
				while(i <= k1);
				
				
				f_pipes(nrp, pipecmd);
			
			}	
			else if(strcmp(args[0], "history") == 0)
			{
				register HIST_ENTRY **new_history;
				register int i;

				new_history = history_list();

				printf("Ati utilizat:\n");
				for(i = 0; new_history[i]; i++)
					printf("%d: %s\n", i+history_base, new_history[i]-> line);
			}

			else
			{
				if(strcmp(args[0], "new_exit") == 0)
				{
					return 0;
				}

				else
				{
					char bk = args[0][strlen(args[0])-1];
			        if (bk =='&')
			        {
                		pid = fork();
                		if(pid == 0)
                		{
                  			daemon(1,1);
                  			ok1 = 1;
                    
                    		bg_proc = getpid();
					  		putchar('\n');
                    		execute_command(args, 1);
                    		ok1 = 1;

                    		return 1;

                    		printf(" child (%d).\n", getpid());
                
                        }

                		if(pid > 0)
                		{
                    		
                    		printf("Waiting on child (%d).\n", pid);        
                    
		                    waitpid(pid, &status1, 0);
		                    
		                    pid_t p = waitpid(bg_proc,&status1, WNOHANG );
		                    
		                    if(p == 0)
		                    {
		                     	printf("bg_proc runn:%d\n", bg_proc );
		                    }

		                  	else if(p == bg_proc)
		                  	{
		                 		printf("gata\n");
                 			} 

                     		printf("Child (%d) finished.\n", pid);

                     		printf("Parent (%d) finished.\n", getpid());

                     	}
            		}

					else
					{
						execute_command(args, 0);
					}
				
				}

			}
			
				
			free(line);
			free(args);

		}

	}
	while(1);

	return 0;
}
