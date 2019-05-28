#include "mystring.h"
#include <assert.h>
#include <sys/types.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

/*
 * The following are simple tests to help you.
 * You should develop more extensive tests to try and find bugs.
 */
int main()
{
	// buffers for strcpy
	const int SIZE = 100;
	char buffer[SIZE];
	char bufferText[100];
	char bufferEmpty[SIZE];
	char bufferEscape[SIZE];
	char bufferEscape2[SIZE];
	char bufferEscape3[5];
	char bufferEscape4[SIZE];
	char bufferSpace[200];
	char bufferSpace2[50];
	char bufferSpace3[10];
	char bufferSpace4[5];
	char bufferSlash[10];
	char bufferSlash2[20];
	char bufferSlash3[50];
	char bufferMultiSlash[SIZE];
	char bufferMultiSlash2[10];


	char testbuffer[SIZE];

	//mystrlen

	//testing an escape character in the middle of the string
	char test[20] = "cmpt300\ncmpt371";
	//testing '\0' in the middle of the string
	char a[20] = "cmpt300\0cmpt371";
	//testing all escape characters
	char b[20] = "\a\b\f\n\r\tasdf\v\\\'\"\?";
	//testing spaces and tabs
	char c[200] = "    Wow very 				cool";
	//testing mulitple slashes with an escape character
	char d[20] = "\\0";
	char e[30] = "./hello/\\\\\\";
	char f[20] = "'";

	// mystrlen testing

	// text with space
	assert(mystrlen("cmpt 300") == 8);
	// empty string
	assert(mystrlen("") == 0);
	// special characters
	assert(mystrlen("cmpt371%") == 8);
	// escape character in the string
	assert(mystrlen("cmpt300\ncmpt371") == strlen(test));
	// \0 character in the string
	assert(mystrlen("cmpt300\0cmpt371") == strlen(a));
	// mixing escape characters and text
	assert(mystrlen("\a\b\f\n\r\tasdf\v\\\'\"\?") == strlen(b));
	// text spaces and tabs
	assert(mystrlen("    Wow very 				cool") == strlen(c));
	// double slashes with 0
	assert(mystrlen("\\0") == strlen(d));
	// multiple slashes
	assert(mystrlen("./hello/\\\\\\") == strlen(e));
	// single quote
	assert(mystrlen("'") == strlen(f));

	printf("\nPassed mystrlen tests.\n");

	// mystrcpy testing

	// text with space
	mystrcpy(buffer, "I am testing my string functions!");
	assert(strcmp(buffer, "I am testing my string functions!") == 0);

	mystrcpy(bufferText, "I @m @wesome #(U$93");
	assert(strcmp(bufferText, "I @m @wesome #(U$93") == 0);
	// copy empty string
	mystrcpy(bufferEmpty, "");
	assert(strcmp(bufferEmpty, "") == 0);

	// copy with escape character
	mystrcpy(bufferEscape, "cmpt300\ncmpt371");
	assert(strcmp(bufferEscape, "cmpt300\ncmpt371") == 0);

	// copy mulitple escape characters with text
	mystrcpy(bufferEscape2, "\a\b\f\n\r\tasdf\v\\\'\"\?");
	assert(strcmp(bufferEscape2, "\a\b\f\n\r\tasdf\v\\\'\"\?") == 0);

	// /0 escape character
	mystrcpy(bufferEscape3, "\0");
	assert(strcmp(bufferEscape3, "\0") == 0);

	// /0 in the middle
	mystrcpy(bufferEscape4, "cmpt300\0cmpt371");
	strcpy(testbuffer, "cmpt300\0cmpt371");
	assert(strcmp(bufferEscape4, testbuffer) == 0);

	// copy tabs and spaces
	mystrcpy(bufferSpace, "    Wow very 		 		cool");
	assert(strcmp(bufferSpace, "    Wow very 		 		cool") == 0);

	mystrcpy(bufferSpace2, " 	 	");
	assert(strcmp(bufferSpace2, " 	 	") == 0);

	mystrcpy(bufferSpace3, "			");
	assert(strcmp(bufferSpace3, "			") == 0);

	mystrcpy(bufferSpace4, "   ");
	assert(strcmp(bufferSpace4, "   ") == 0);

	// multiple slashes with escape characters
	mystrcpy(bufferSlash, "\\0");
	assert(strcmp(bufferSlash, "\\0") == 0);

	mystrcpy(bufferSlash2, "\\t");
	assert(strcmp(bufferSlash2, "\\t") == 0);

	mystrcpy(bufferSlash3, "\\t\\n\\a\\b");
	assert(strcmp(bufferSlash3, "\\t\\n\\a\\b") == 0);

	// multiple slashes
	mystrcpy(bufferMultiSlash, "./hello/\\\\\\");
	assert(strcmp(bufferMultiSlash, "./hello/\\\\\\") == 0);

	mystrcpy(bufferMultiSlash2, "\\");
	assert(strcmp(bufferMultiSlash2, "\\") == 0);

	printf("\nPassed mystrcpy tests.\n");

	// mystrcmp testing
	//same string
	assert(mystrcmp ("I love coding", "I love coding") == 0);
	assert(mystrcmp("$#@","$#@") == 0);
	//empty string
	assert(mystrcmp("","") == 0);
	// /0 string
	assert(mystrcmp("\0","\0") == 0);
	assert(mystrcmp(" "," \0") == strcmp(" ", " \0")); // 0
	// /0 compared to char
	assert(mystrcmp("cmpt300\0weeeeeeeeeeeeeeeeee","wow\0dlfkas;ldg") == -1);
	// comparing escape characters
	assert(mystrcmp("\a\b\"", "\a\b\f\n\r\t\v") == strcmp("\a\b\"", "\a\b\f\n\r\t\v")); //1
	assert(mystrcmp("\a\b\f\t","\a\b\f\t") == strcmp("\a\b\f\t", "\a\b\f\t")); // 0
	assert(mystrcmp("\a\a\t\t\a\r\t", "\a\b\t\f\n") == strcmp("\a\a\t\t\a\r\t", "\a\b\t\f\n")); // -1
	assert(mystrcmp("\n\f","\n\f") == strcmp("\n\f","\n\f")); // 0
	// comparing space and tab
	assert(mystrcmp(" ","	") == strcmp(" ","	")); // 1
	assert(mystrcmp("		","	") == strcmp("		","	")); // 1
	assert(mystrcmp("  ","  ") == strcmp("  ", "  ")); // 0
	assert(mystrcmp("     ","			\0") == strcmp("     ","			\0")); // 1
	assert(mystrcmp(" 	 		 "," 	 		 ") == strcmp(" 	 		 "," 	 		 ")); // 0
	assert(mystrcmp(" ", "") == strcmp(" ","")); // 1
	// comparing /0 to escape char
	assert(mystrcmp("test\0", "test\f") == strcmp("test\0", "test\f")); // -1
	assert(mystrcmp("\0","\a") == strcmp("\0","\a")); // -1
	// comparing same length but different characters
	assert(mystrcmp("Same Length", "Different !") == strcmp("Same Length", "Different !")); // 1
	assert(mystrcmp("111","000") == strcmp("111","000")); // 1

	//printf("%d", strcmp("\n\f","\n\f"));
	printf("\nPassed mystrcmp tests.\n");


	// mystrdup testing
	char *dupStr = mystrdup(buffer);
	assert (!strcmp(buffer, dupStr));
	assert (buffer != dupStr);

	if (dupStr != NULL)
		free (dupStr);

	char *dupStrText = mystrdup(bufferText);
	assert (!strcmp(bufferText, dupStrText));
	assert (bufferText != dupStrText);

	if (dupStrText != NULL)
		free (dupStrText);

	char *dupStrEmpty = mystrdup(bufferEmpty);
	assert (!strcmp(bufferEmpty, dupStrEmpty));
	assert (bufferEmpty != dupStrEmpty);

	if (dupStrEmpty != NULL)
		free (dupStrEmpty);

	char *dupStrEscape = mystrdup(bufferEscape);
	assert (!strcmp(bufferEscape, dupStrEscape));
	assert (bufferEscape != dupStrEscape);

	if (dupStrEscape != NULL)
		free (dupStrEscape);

	char *dupStrEscape2 = mystrdup(bufferEscape2);
	assert (!strcmp(bufferEscape2, dupStrEscape2));
	assert (bufferEscape2 != dupStrEscape2);

	if (dupStrEscape2 != NULL)
		free (dupStrEscape2);

	char *dupStrEscape3 = mystrdup(bufferEscape3);
	assert (!strcmp(bufferEscape3, dupStrEscape3));
	assert (bufferEscape3 != dupStrEscape3);

	if (dupStrEscape3 != NULL)
		free (dupStrEscape3);

	char *dupStrEscape4 = mystrdup(bufferEscape4);
	assert (!strcmp(bufferEscape4, dupStrEscape4));
	assert (bufferEscape4 != dupStrEscape4);

	if (dupStrEscape4 != NULL)
		free (dupStrEscape4);

	char *dupStrSpace = mystrdup(bufferSpace);
	assert (!strcmp(bufferSpace, dupStrSpace));
	assert (bufferSpace != dupStrSpace);

	if (dupStrSpace != NULL)
		free (dupStrSpace);

	char *dupStrSpace2 = mystrdup(bufferSpace2);
	assert (!strcmp(bufferSpace2, dupStrSpace2));
	assert (bufferSpace2 != dupStrSpace2);

	if (dupStrSpace2 != NULL)
		free (dupStrSpace2);

	char *dupStrSpace3 = mystrdup(bufferSpace3);
	assert (!strcmp(bufferSpace3, dupStrSpace3));
	assert (bufferSpace3 != dupStrSpace3);

	if (dupStrSpace3 != NULL)
		free (dupStrSpace3);

	char *dupStrSpace4 = mystrdup(bufferSpace4);
	assert (!strcmp(bufferSpace4, dupStrSpace4));
	assert (bufferSpace4 != dupStrSpace4);

	if (dupStrSpace4 != NULL)
		free (dupStrSpace4);

	char *dupStrSlash = mystrdup(bufferSlash);
	assert (!strcmp(bufferSlash, dupStrSlash));
	assert (bufferSlash != dupStrSlash);

	if (dupStrSlash != NULL)
		free (dupStrSlash);

	char *dupStrSlash2 = mystrdup(bufferSlash2);
	assert (!strcmp(bufferSlash2, dupStrSlash2));
	assert (bufferSlash2 != dupStrSlash2);

	if (dupStrSlash2 != NULL)
		free (dupStrSlash2);

	char *dupStrSlash3 = mystrdup(bufferSlash3);
	assert (!strcmp(bufferSlash3, dupStrSlash3));
	assert (bufferSlash3 != dupStrSlash3);

	if (dupStrSlash3 != NULL)
		free (dupStrSlash3);

	char *dupStrMultiSlash = mystrdup(bufferMultiSlash);
	assert (!strcmp(bufferMultiSlash, dupStrMultiSlash));
	assert (bufferMultiSlash != dupStrMultiSlash);

	if (dupStrMultiSlash != NULL)
		free (dupStrMultiSlash);

	char *dupStrMultiSlash2 = mystrdup(bufferMultiSlash2);
	assert (!strcmp(bufferMultiSlash2, dupStrMultiSlash2));
	assert (bufferMultiSlash2 != dupStrMultiSlash2);

	if (dupStrMultiSlash2 != NULL)
		free (dupStrMultiSlash2);	

	printf("\nPassed mystrdup tests\n");

	printf ("\nPassed VERY simple tests, remember to develop more tests.\n");

	return 0;
}