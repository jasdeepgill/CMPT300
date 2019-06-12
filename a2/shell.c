// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>

#include <sys/types.h>
#include <sys/wait.h>
#include <sys/signal.h>
#include <ctype.h>

#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
#define MAX_BUF 1024
#define HISTORY_DEPTH 10
char history[HISTORY_DEPTH][COMMAND_LENGTH];
int cmdNum[HISTORY_DEPTH];
int count = 0;
int inc;
// @global var
// Inc will be the tail of both history array and cmdNum
// count will count the number of commands. 

/**
 * Command Input and Processing
 */

/*
 * Tokenize the string in 'buff' into 'tokens'.
 * buff: Character array containing string to tokenize.
 *       Will be modified: all whitespace replaced with '\0'
 * tokens: array of pointers of size at least COMMAND_LENGTH/2 + 1.
 *       Will be modified so tokens[i] points to the i'th token
 *       in the string buff. All returned tokens will be non-empty.
 *       NOTE: pointers in tokens[] will all point into buff!
 *       Ends with a null pointer.
 * returns: number of tokens.
 */
int tokenize_command(char *buff, char *tokens[])
{
	int token_count = 0;
	_Bool in_token = false;
	int num_chars = strnlen(buff, COMMAND_LENGTH);
	for (int i = 0; i < num_chars; i++) {
		switch (buff[i]) {
		// Handle token delimiters (ends):
		case ' ':
		case '\t':
		case '\n':
			buff[i] = '\0';
			in_token = false;
			break;

		// Handle other characters (may be start)
		default:
			if (!in_token) {
				tokens[token_count] = &buff[i];
				token_count++;
				in_token = true;
			}
		}
	}
	tokens[token_count] = NULL;
	return token_count;
}

/**
 * Read a command from the keyboard into the buffer 'buff' and tokenize it
 * such that 'tokens[i]' points into 'buff' to the i'th token in the command.
 * buff: Buffer allocated by the calling code. Must be at least
 *       COMMAND_LENGTH bytes long.
 * tokens[]: Array of character pointers which point into 'buff'. Must be at
 *       least NUM_TOKENS long. Will strip out up to one final '&' token.
 *       tokens will be NULL terminated (a NULL pointer indicates end of tokens).
 * in_background: pointer to a boolean variable. Set to true if user entered
 *       an & as their last token; otherwise set to false.
 */
void read_command(char *buff, char *tokens[], _Bool *in_background)
{
	*in_background = false;

	// Read input
	int length = read(STDIN_FILENO, buff, COMMAND_LENGTH-1);

	if (length < 0 && errno != EINTR) {
		perror("Unable to read command from keyboard. Terminating.\n");
		exit(-1);
	}

	// Null terminate and strip \n.
	buff[length] = '\0';
	if (buff[strlen(buff) - 1] == '\n') {
		buff[strlen(buff) - 1] = '\0';
	}

	// Tokenize (saving original command string)
	int token_count = tokenize_command(buff, tokens);
	if (token_count == 0) {
		return;
	}

	// Extract if running in background:
	if (token_count > 0 && strcmp(tokens[token_count - 1], "&") == 0) {
		*in_background = true;
		tokens[token_count - 1] = 0;
	}
}

void print(char* s)
{
	write(STDOUT_FILENO, s, strlen(s));
}

void print_char(char c)
{
	char s[1024];
	s[0] = c;
	s[1] = '\0';
	write(STDOUT_FILENO, s, strlen(s));
}

void print_int(int i)
{
	char a[1024];
	sprintf(a, "%d", i);
	print(a);
}

void print_char_by_int(char c)
{
	int i = (int) c;
	print_int(i);
} 

void clearHistorySlot(int index)
{
	memset(history[index], 0, sizeof(char)*COMMAND_LENGTH);
}

void dequeue()
{
	// assert inc == 9
	for (int i = 0; i < inc; ++i)
	{
		cmdNum[i] = cmdNum[i+1];
		int j = 0;
		clearHistorySlot(i);
		while(history[i+1][j] != '\0')
		{
			history[i][j] = history[i+1][j];
			j++;
		}
	}
	clearHistorySlot(inc);
}



void queueSave(char* cmd[], _Bool inBackground)
{
	if(errno != EINTR)
	{
	count++;
	
	if (count > 10)
	{
			inc--;
		dequeue();

	}
	
	cmdNum[inc] = count;
	int i = 0;
	int j = 0;
	
	while(cmd[i] != NULL)
	{
		// print("doubleweed\n");
		int w = 0;
		while(cmd[i][w] != '\0')
		{
			history[inc][j] = cmd[i][w];
			w++;
			j++;
			// printf("%s %d\n", history[inc], j);
		}
		// char f[80];
		// sprintf(f, "%d", j);
		// print("j=");
		// print(f);
		// print("\n");
		history[inc][j] = ' ';
		j++;
		i++;
	}
	// print("history[inc-1]=");
	// print(history[inc-1]);
	// print("\n");
	// print("j=");
	// print_int(j);
	// print("\n");
	// print("history[inc][j-6]=");
	// print_char_by_int(history[inc][j-6]);
	// print("\n");
	if (inBackground)
		{
			history[inc][j] = '&'; 
			history[inc][j+1] = '\0';
		}	
	else
	{
		history[inc][j] = '\0';
	}
	// print("cmd[1]=");
	// print(cmd[1]);
	// print("\n");
	// print("history[inc]=");
	// print(history[inc]);
	// print("\n");
	inc++;
	// history[count-1] = cmd[1];
	}
	errno = 0;
}

void hist()
{
	for (int i = 0; i < inc; ++i)
	{
		char stuff[1024];
		sprintf(stuff, "%d", cmdNum[i]);
		print(stuff);
		print("	");

		print(history[i]);
		print("\n");
	}
}

void handle_SIGINT()
{
	print("\n");
	hist();
	return;
}

void wait_for_child(pid_t pid, _Bool inBackground)
{
	int status;
	if (inBackground)
		{
			// print("IN BACKGROUND.\n");
			while (waitpid(-1, &status, WNOHANG) > 0);
		}
		else
		{
			// return waitpid(pid, &status, 0);
			waitpid(pid, &status, 0);
		}
	// status = 0 child terminated normally
	// status = 1 child terminated with error
	// print("pid=");
	// print_int(pid);
	// print("\n");
	// print("Status of child: ");
	// print_int(status);
	// print("\n");
	// print("Exit status: ");
	// status = WIFEXITED(status);
	// print_int(status);
	// print("\n");
	// return 100;
}

void new_child_process(char* tokens[], _Bool inBackground)
{
	pid_t child_pid;
	child_pid = fork();
	if (child_pid == 0)
	{
		if(errno == EINTR)
			{
				exit(0);
			}
			if (tokens[0] != NULL)
			{
				
				
				if (tokens[0][0] != '!')
				{
					if (strcmp(tokens[0], "exit") != 0 && strcmp(tokens[0], "pwd") != 0 && strcmp(tokens[0], "cd") != 0 && strcmp(tokens[0], "history") != 0)
					{
						if(execvp(tokens[0], tokens) < 0){ print("Error 02.1: Invalid command or arguments for command: "); print(tokens[0]); print("\n"); exit(-1);}
							
						
					}
				}
				else
				{
					print(tokens[0]);
					print(": ");
					print("Unknown command.\n");
				}
				
			}
			exit(0);
	}
	else
	{
		wait_for_child(child_pid, inBackground);
	}
}

void hist_select_helper(char* tokens[], _Bool inBackground)
{
	if (tokens[0] != NULL)
		{
			if (errno != EINTR)
				{
					if (strcmp(tokens[0], "exit") == 0)
					{
					
						exit(0);
					}
					else if (strcmp(tokens[0], "pwd") == 0)
					{
						size_t size = sizeof(char) * MAX_BUF;
						char* buf = (char *) malloc(size);
						char* cwd;
						

						cwd = getcwd(buf, size);
						if (cwd == NULL)
						{
							perror("Error 01.3");
						}
						print(cwd);
						print("\n");
						free(buf);
					}
					else if (strcmp(tokens[0], "cd") == 0)
					{
						if (chdir(tokens[1]) == -1)
						{
							perror("Error 01.4");
						}
					}
					else if (strcmp(tokens[0], "history") == 0)
					{	
						
						hist();
					}
				}	
			
			
		}
}

void hist_select(char* cmd[], _Bool inBackground)
{
	if (count > 0)
	{
		if (cmd[0][1] == '!' && cmd[0][2] == '\0')
		{
			
			// char* prev_cmd = history[inc-1];
			char prev_cmd[1024];
			int h = 0;
			while(history[inc-1][h] != '\0')
			{
				prev_cmd[h] = history[inc-1][h];
				h++;
			}
			prev_cmd[h] = '\0';
			// print("prev_cmd=");
			// print(prev_cmd);
			// print("\n");
			print(prev_cmd);
			print("\n");
			char* tokens[NUM_TOKENS];
			int num_tokens;
			num_tokens = tokenize_command(prev_cmd, tokens);
			// print("Found tokens: ");
			// print_int(num_tokens);
			// print("\n");
			if (strcmp(tokens[num_tokens-1], "&") == 0)
			{
				inBackground = 1;
				tokens[num_tokens-1] = 0;
			}
			queueSave(tokens, inBackground);
			// print("history[inc-2]=");
			// print(history[inc-2]);
			// print("\n");
			new_child_process(tokens, inBackground);
			hist_select_helper(tokens, inBackground);
		}
		else if (isdigit(cmd[0][1]))
		{

			char num[1024];
			int cmd_num;
			int i = 1;
			while(cmd[0][i] != '\0')
			{
				if (isalpha(cmd[0][i]))
				{
					print("Command does not exist.\n");
					return;
				}
				num[i-1] = cmd[0][i];
				i++;
				// print_int(i);
			}
			num[i-1] = '\0';
			cmd_num = atoi(num);
			// print("cmd[0]=");
			// print(cmd[0]);
			// print("\n");
			// print("num=");
			// print(num);
			// print("\n");
			// print("cmd_num=");
			// print_int(cmd_num);
			// print("\n");
			_Bool inHistory = false;
			i = 0;
			while(i < inc)
			{
				if (cmdNum[i] == cmd_num)
				{
					inHistory = true;
				}
				i++;
			}
			if (!inHistory)
			{
				print("Error 04: Not in history.\n");
			}
			else
			{
				i = 0;
				while(cmdNum[i] != cmd_num)
				{
					i++;
				}
				// char* selected_cmd = history[i];
				char selected_cmd[1024];
				int l = 0;
				while(history[i][l] != '\0')
				{
					selected_cmd[l] = history[i][l];
					l++;
				}
				selected_cmd[l] = '\0';
				// print("selected_cmd=");
				// print(selected_cmd);
				// print("\n");
				print(selected_cmd);
				print("\n");
				char* tokens[NUM_TOKENS];
				int num_tokens;
				num_tokens = tokenize_command(selected_cmd, tokens);
				// print("Found tokens: ");
				// print_int(num_tokens);
				// print("\n");
				if (strcmp(tokens[num_tokens-1], "&") == 0)
				{
					inBackground = 1;
					tokens[num_tokens-1] = 0;
				}
				queueSave(tokens, inBackground);
				new_child_process(tokens, inBackground);
				hist_select_helper(tokens, inBackground);
			}
			

		}
		else
		{
			print("Error 03: Invalid history commmand (NaN).\n");
		}
	}
	else
	{
		print("Error 05: There is no previous history of commmands.\n");
	}
	
}


/**
 * Main and Execute Commands
 */
int main(int argc, char* argv[])
{
	char input_buffer[COMMAND_LENGTH];
	char *tokens[NUM_TOKENS];
	while (true) {

		pid_t childPID;
		size_t size = sizeof(char) * MAX_BUF;
		char* buf = (char *) malloc(size);
		char* cwd;
		
		struct sigaction handler;
		handler.sa_handler = handle_SIGINT;
		handler.sa_flags = 0;
		sigemptyset(&handler.sa_mask);
		sigaction(SIGINT, &handler, NULL);	

		cwd = getcwd(buf, size);
		if (cwd == NULL)
		{
			perror("Error 01.2");
		}
		print(cwd);
		free(buf);
		// Get command
		// Use write because we need to use read() to work with
		// signals, and read() is incompatible with printf().
		write(STDOUT_FILENO, "> ", strlen("> "));
		_Bool in_background = false;
		read_command(input_buffer, tokens, &in_background);

		

		// DEBUG: Dump out arguments:
		// for (int i = 0; tokens[i] != NULL; i++) {
		// 	write(STDOUT_FILENO, "   Token: ", strlen("   Token: "));
		// 	write(STDOUT_FILENO, tokens[i], strlen(tokens[i]));
		// 	write(STDOUT_FILENO, "\n", strlen("\n"));
		// }
		if (in_background) {
			write(STDOUT_FILENO, "Run in background.\n", strlen("Run in background.\n"));
		}

		/**
		 * Steps For Basic Shell:
		 * 1. Fork a child process
		 * 2. Child process invokes execvp() using results in token array.
		 * 3. If in_background is false, parent waits for
		 *    child to finish. Otherwise, parent loops back to
		 *    read_command() again immediately.
		 */

		childPID = fork();
		// print("Child pid: ");
		// print_int(childPID);
		// print("\n");
		if (childPID == 0)
		{
			if(errno == EINTR)
			{
				exit(0);
			}
			if (tokens[0] != NULL)
			{
				
				
				if (tokens[0][0] != '!')
				{
					if (strcmp(tokens[0], "exit") != 0 && strcmp(tokens[0], "pwd") != 0 && strcmp(tokens[0], "cd") != 0 && strcmp(tokens[0], "history") != 0)
					{
						if(execvp(tokens[0], tokens) < 0){ print("Error 02: Invalid command or arguments for command: "); print(tokens[0]); print("\n"); exit(-1);}
							
						
					}
				}
				
				exit(0);
			}

			print(tokens[0]);
			print(": ");
			print("Unknown command.\n");
				
			exit(0);
			
		}
		
		else
		{
		
		
		// pid_t stat;
		// stat = waitpid(childPID, NULL, 0);
		// print("wtf\n");
		// wait_for_child(childPID, in_background);
		// wait_for_child(childPID, in_background);
		wait_for_child(childPID, in_background);
		// if (stat == 0)
		// {
		// 	print("Child terminated normally.\n");
		// }
		// else if (stat == -1)
		// {
		// 	print("Child terminated with error.\n");
		// }
		// print("Child pid: ");
		// print_int(childPID);
		// print("\n");
		// pid_t pid1 = wait_for_child(childPID, in_background);
		// print("Done waiting for pid: ");
		// print_int(pid1);
		// print("\n");
		// pid_t pid2 = wait_for_child(childPID, in_background);
		// print("Done waiting for pid: ");
		// print_int(pid2);
		// print("\n");

		
		if (tokens[0] != NULL)
		{
			
		// print("ERRNO: ");
		// print_int(errno);
		// print("\n");
		if(errno != EINTR)
		{


			if (tokens[0][0] == '!')
			{
				hist_select(tokens, in_background);
			}
			else
			{
				queueSave(tokens, in_background);
			
				if (strcmp(tokens[0], "exit") == 0)
				{
					
					exit(0);
				}
				else if (strcmp(tokens[0], "pwd") == 0)
				{
					char* buf = (char *) malloc(size);
					char* cwd;
					cwd = getcwd(buf, size);
					if (cwd == NULL)
					{
						perror("Error 01.1");
					}
					print(cwd);
					free(buf);
					print("\n");
				}
				else if (strcmp(tokens[0], "cd") == 0)
				{
					if (chdir(tokens[1]) == -1)
					{
						perror("Error 01");
					}
				}
				else if (strcmp(tokens[0], "history") == 0)
				{	
					
					hist();
				}
			}
			}
			
		}
		else if (tokens[0] == NULL && in_background)
		{
			print("&: Unknown command.\n");
		}
		errno = 0;
		// wait_for_child(childPID, in_background);
		}
	}

	return 0;
}
