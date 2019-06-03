// Shell starter file
// You may make any changes to any part of this file.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/wait.h>


#define COMMAND_LENGTH 1024
#define NUM_TOKENS (COMMAND_LENGTH / 2 + 1)
#define MAX_BUF 1024
#define HISTORY_DEPTH 10
char history[HISTORY_DEPTH][COMMAND_LENGTH];
int cmdNum[HISTORY_DEPTH];
int count = 0;
int inc;

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

	if (length < 0) {
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

void print_int(int i)
{
	char a[1024];
	sprintf(a, "%d", i);
	print(a);
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
{count++;
	
	printf("%d\n", inc);
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
	if (inBackground)
		{
			history[inc][j] = '&'; 
			history[inc][j+1] = '\0';
		}	
	else
	{
		history[inc][j-1] = '\0';
	}
	// print("cmd[1]=");
	// print(cmd[1]);
	// print("\n");
	print("history[inc]=");
	print(history[inc]);
	print("\n");
	inc++;
	print("weed\n");
	// history[count-1] = cmd[1];
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

void hist_select(char* cmd[])
{
	if (cmd[0][1] == '!' && cmd[0][2] == '\0')
	{
		
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
		

		cwd = getcwd(buf, size);
		if (cwd == NULL)
		{
			perror("WTF\n");
		}
		print(cwd);
		// Get command
		// Use write because we need to use read() to work with
		// signals, and read() is incompatible with printf().
		write(STDOUT_FILENO, "> ", strlen("> "));
		_Bool in_background = false;
		read_command(input_buffer, tokens, &in_background);

		

		// DEBUG: Dump out arguments:
		for (int i = 0; tokens[i] != NULL; i++) {
			write(STDOUT_FILENO, "   Token: ", strlen("   Token: "));
			write(STDOUT_FILENO, tokens[i], strlen(tokens[i]));
			write(STDOUT_FILENO, "\n", strlen("\n"));
		}
		if (in_background) {
			write(STDOUT_FILENO, "Run in background.", strlen("Run in background."));
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
		if (childPID == 0)
		{
			// queueSave(tokens, in_background);
			pid_t parent_pid = getppid();
			print("parent pid: ");
			print_int(parent_pid);
			print("\n");
			pid_t child_pid = getpid();
			print("child pid: ");
			print_int(child_pid);
			print("\n");
			// print_int(childPID);
			// print("\n");
			print(tokens[0]);
			print("\n");
			if(execvp(tokens[0], tokens) < 0) perror("kill me.");
		else
		{
		// 	if (strcmp(tokens[0], "history") == 0)
		// {
		// 	hist();
		// }
		// else if (tokens[0][0] == '!')
		// {
		// 	hist_select(tokens);
		// }

		// 	if (in_background)
		// {
		// 	while (waitpid(-1, NULL, WNOHANG) > 0);
		// }
		// else
		// {
		// 	waitpid(-1, NULL, 0);
		// }
		
		// }
		}}
		
		// else

		// {
			// pid_t parent_pid = getpid();
			// print("Current pid: ");
			// print_int(parent_pid);
			// print("\n");
					if (in_background)
		{
			while (waitpid(-1, NULL, WNOHANG) > 0);
		}
		else
		{
			waitpid(-1, NULL, 0);
		}
		
			queueSave(tokens, in_background);
			if (strcmp(tokens[0], "exit") == 0)
		{
			print("free me boiii\n");
			free(buf);
			free(cwd);
			print("bruh\n");
			exit(0);
		}
		else if (strcmp(tokens[0], "pwd") == 0)
		{
			print(cwd);
		}
		else if (strcmp(tokens[0], "cd") == 0)
		{
			if (chdir(tokens[1]) == -1)
			{
				perror("WTF You idiot\n");
			}
		}
		else if (strcmp(tokens[0], "history") == 0)
		{	
			// print("ENTEREEEREEEEEEE\n");
			hist();
		}
		else if (tokens[0][0] == '!')
		{
			hist_select(tokens);
		}

		// print("SWAG\n");
		// }
		
	}

	return 0;
}