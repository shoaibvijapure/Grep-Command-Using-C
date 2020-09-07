#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <error.h>
#include "grep.h"

void setflag(data var) { 
	var.iflag = 0;
	var.oflag = 0;
	var.nflag = 0;
	var.normalflag = 0;
	var.vflag = 0;
	var.bflag = 0;
	var.fflag = 0;
	var.wflag = 0;
	var.cflag = 0;
	var.qflag = 0;
	var.hflag = 0;
	var.Hflag = 0;
	var.mflag = 0;
	var.rflag = 0;
}

void printline(char *line, char *pattern, data var, data outputvar , char *argv[], int argc, int argm) {
	int line_len = strlen(line);
	char temp_len[line_len];
	strcpy(temp_len, line);
	char *n_line = (char *)malloc(line_len); 
	char *b_line = (char *)malloc(line_len);
	char *v_line = (char *)malloc(line_len);
	char *f_line = (char *)malloc(line_len);
	char *m_line = (char *)malloc(line_len);
	char *w_line = (char *)malloc(line_len);
	char *o_line = (char *)malloc(line_len);
	char *normal_line = (char *)malloc(line_len);
	if(var.vflag == 1 && var.oflag == 1 ) 
		return;

// grep default handling
	if(var.iflag != 1 && var.vflag != 1) {
		normal_line = grep_match(line, pattern);
		if(normal_line != NULL) {
			//do nothing...
		}
	}

// i_grep and v_grep handling
	if(var.iflag == 1 &&  var.vflag != 1 && var.oflag != 1 && var.fflag != 1 && var.nflag != 1 && var.bflag != 1 && var.wflag != 1) {
		char *i_line = (char *)malloc(line_len);
		i_line = i_grep(line, pattern);
		if(i_line != NULL && var.qflag != 1) {
			if(var.Hflag == 1)  
				printf(G_MAGENTA "%s" G_CYAN ":"G_RESET, argv[count]);
			printf("%s", i_line); 
		}
		return;
	}

/*vflag*/
	if(var.vflag == 1) 
		v_line = v_grep(line, pattern);

/*b_grep*/
	if(var.bflag == 1 &&  var.vflag != 1 && var.fflag != 1 && var.nflag != 1  && var.wflag != 1 && var.oflag != 1) {
		b_line = b_grep(line, pattern);
		if(b_line != NULL && var.qflag != 1)
			printf(G_YELLOW"%d :"G_RESET" %s", (bcount - line_len ), b_line); 
		 return;
	} 
	if(var.bflag == 1 ) 
		b_line = b_grep(line, pattern);
	 
/*wflag*/
	if(var.wflag == 1) 
		w_line = w_grep(line, pattern);
	
/*mflag*/
	if(var.mflag == 1 &&  var.vflag != 1 && var.fflag != 1 && var.nflag != 1 ){
		if((m_line = m_grep(line, argm, pattern)) != NULL) {
			//do nothing...
		}
		if(m_line != NULL && var.qflag != 1) {
			if(var.Hflag == 1)  
				printf(G_MAGENTA " %s" G_CYAN ":"G_RESET, argv[count]);
			printf(" %s", m_line);
		}
		return;
	}
	
	if(var.mflag == 1 ) {
		if((m_line = m_grep(line, argm, pattern)) != NULL) {
			// do nothing...
		}
	}

/*fflag_alone*/ 
	if(var.fflag == 1  && var.vflag != 1 && var.oflag != 1  && var.nflag != 1 && var.iflag != 1  && var.bflag != 1 && var.wflag != 1) {
		if((f_line = f_grep(line, pattern)) != NULL) {
			// do nothing...
		}
		if(f_line != NULL) {
			if(var.Hflag == 1 && var.cflag != 1)  
				printf(G_MAGENTA " %s" G_CYAN ":"G_RESET, argv[count]);
			if(var.cflag != 1) 
				printf("%s", f_line);
			if(var.cflag == 1) 
				ccount++;
		}
		return;
	}

/*fflag*/
	if(var.fflag == 1) {
		if((f_line = f_grep(line, pattern)) != NULL) {
			// do nothing...
		}
	}	

/*nflag*/
	if(var.nflag == 1) {
		if(line != NULL) 
			n_line = n_grep(line, pattern);
	}

/*oflag*/ 
	if(var.oflag == 1) {
		if((o_line = o_grep(line, pattern)) != NULL) 
			ocount = 0;
	}

	if(var.Hflag == 1 && var.cflag != 1 && normal_line != NULL && v_line != NULL && n_line != NULL && f_line != NULL && m_line != NULL && w_line != NULL && o_line != NULL && var.qflag != 1) 
			printf(G_MAGENTA"%s"G_CYAN":"G_RESET, argv[count]);
	if(var.nflag == 1 && var.cflag != 1 && normal_line != NULL  && n_line != NULL && m_line != NULL && f_line != NULL && o_line != NULL  && w_line != NULL && v_line != NULL && var.qflag != 1) 
		printf(G_GREEN"%d" G_CYAN":"G_RESET, ncount);
	if(var.bflag == 1 && var.cflag != 1 && normal_line != NULL  && n_line != NULL && f_line != NULL && m_line != NULL && w_line != NULL && v_line != NULL && o_line != NULL && var.qflag != 1) 
			printf(G_GREEN"%d:"G_RESET, bcount - line_len);
	if(n_line != NULL  && normal_line != NULL && f_line != NULL && m_line != NULL && w_line != NULL && o_line != NULL && v_line != NULL ) {
		if(var.oflag == 1 && var.qflag != 1) {
			printf("%s\n", o_line);
			return;
		}
		if(var.vflag == 1 && var.qflag != 1) {
			if(v_line != NULL) {
				ccount ++;
				if(var.cflag != 1) 
					printf("%s", v_line);
			}
		}
		else {
			ccount ++;
			if(var.cflag != 1 && var.qflag != 1) 
				printf("%s", line);
		}
	}
}

// grep default prints matching lines ... 
char *grep_match(char *line, char *pattern) { /*returns 0 if pattern found in line else return -1*/
	int line_len = strlen(line);
	int pattern_len = strlen(pattern);
	char *newline = (char *)malloc(line_len + 1);
	char *newpattern = (char *)malloc(pattern_len + 1);	
	strcpy(newline, line);
	strcpy(newpattern, pattern);
	if(var.iflag == 1) {
		strcpy(newline, lower(newline));
		strcpy(newpattern, lower(newpattern));
	}
	if(line == NULL) 
		return NULL;
	if(strstr(newline, newpattern) == NULL ) 
		return NULL;
	else 
		return line;
}

// i_grep 
char *i_grep(char *line, char *pattern) { 
	int line_len = strlen(line);
	int pattern_len = strlen(pattern);
	int i;
	char *newline = (char *)malloc(line_len + 1);
	char *newpattern = (char *)malloc(pattern_len + 1);
	strcpy(newline, line);
	strcpy(newpattern, pattern);
	if(line == NULL) 
		return NULL;
	for (i = 0; newpattern[i]!='\0'; i++) {
		if(newpattern[i] >= 'A' && newpattern[i] <= 'Z') 
			newpattern[i] = newpattern[i] + 32;
	}
	for (i = 0; newline[i]!='\0'; i++) {
		if(newline[i] >= 'A' && newline[i] <= 'Z')  
			newline[i] = newline[i] + 32;
	}
	if(strstr(newline, newpattern) == NULL ) 
		return NULL;
	else 
		return line;
}

// v_grep print lines which do not match...
char *v_grep(char *line, char *pattern) {
	if(line == NULL) 
		return NULL;
	if(grep_match(line, pattern) != NULL )  
		return NULL;
	else 
		return line;
}
/*w_grep
* Select  only  those  lines  containing  matches  that form whole words.  The test is that the matching substring must
	either be at the beginning of the line, or preceded by a non-word  constituent  character.   Similarly,  it  must  be
	either  at  the  end  of  the  line or followed by a non-word constituent character.  Word-constituent characters are
	letters, digits, and the underscore.
*/
char *w_grep(char *line, char *pattern) {
	if(line == NULL) {
		return NULL;
	}
	int line_len = strlen(line);
	int pattern_len = strlen(pattern);
	int set = -1;
	int i = 0, j = 0, k = 0;
	char *newline = (char *)malloc(line_len + 1);
	char *newpattern = (char *)malloc(pattern_len + 1);
	char *temp = (char *)malloc(line_len + 1);
	strcpy(newline, line);
	strcat(temp, " ");
	strcat(temp, newline);
	strcat(temp, " ");
	strcpy(newpattern, pattern);
	if(var.iflag == 1) {
		strcpy(newline, lower(newline));
		strcpy(newpattern, lower(newpattern));
		strcpy(temp, lower(temp));
	}
	if(strstr(newline, newpattern) == NULL) {
		return NULL;
	}
	for(i = 0; temp[i] != '\0'; i++) {
			if(temp[i] == newpattern[0] && temp[i - 1] != '_'&& isalpha(temp[i - 1]) == 0 &&  isdigit(temp[i - 1]) == 0 &&  isdigit(temp[i + pattern_len]) == 0 && isalpha(temp[i + pattern_len]) == 0 && temp[i + pattern_len] != '_') {
				for(j = i, k = 0; j < i + pattern_len; j++, k++ ) {
					if(temp[j] == pattern[k]) {
						 set = 1;
					}	
					else {
						set = 0;
					}
				}
			}
	}
	if(set == 1) {
		return line;
	}
	else {
		return NULL;
	}
	
}
/*f_grep : 
*opens a file to read pattern 
*match pattern from pattern file to other files also works on multiple files
*print line only ones if pattern is found
*eg : if pattern file contains "ronak " , "coep" and serch file conations line "ronak dislikes coep canteen food " 
	output will display this line only ones not twice;
*/
char *f_grep(char *line, char *filename) {
	FILE *fp;
	fp = fopen(filename, "r"); 
	int line_len = strlen(line);
	int set = 0;	
	char *token;
	char newline[line_len];
	char str2[line_len];
	strcpy(newline, line);
	if(fp == NULL && var.qflag != 1) {
		printf(G_CYAN" %s "G_GREEN": No such file or directory\n" G_RESET, filename);
		goto rewind;
	}
	while(fgets(str2, line_len, fp)) {
		if(strlen(str2) == 0) {
			return NULL;
		}
		token = strtok(str2, "\n");
		while(token != NULL) {
			if(var.iflag == 1) {
				strcpy(newline, lower(newline));
				strcpy(token, lower(token));
			}
			if(strstr(newline, token) != NULL) {
				set = set + 1;
			}		
			token = strtok(NULL, "\n");	
		}
	}
	if(set > 0) {
		rewind(fp);
		return line;
	}
	
	rewind : 
	rewind(fp);
	return NULL;
}
// m_grep match til given number times eg : -m 2 means it will print first 2 matching lines... 
char *m_grep(char *line, int itration, char *pattern) {
	char *set;
	int line_len = strlen(line);	
	int pattern_len = strlen(pattern);
	char *newline = (char *)malloc(line_len + 1);	
	char *newpattern = (char *)malloc(pattern_len + 1);	
	strcpy(newline, line);
	strcpy(newpattern, pattern);
	if(var.iflag == 1) {
		strcpy(newline, lower(newline));
		strcpy(newpattern, lower(newpattern));
	}
	if(line == NULL) {
		return NULL;
	}
	if(itration == mcount) {
		return NULL;	
	} 
	set = grep_match(newline, newpattern);
	if(set != NULL) {
		mcount = mcount + 1;
		return line;
	}
	return NULL;
}
// o_grep print matched pattern only
char *o_grep(char *line, char *pattern) {
	int line_len = strlen(line);
	int pattern_len = strlen(pattern);
	char newline[line_len];	
	char newpattern[pattern_len];	
	char *token;
	static int o_send = 0;
	strcpy(newline, line);
	strcpy(newpattern, pattern);
	if(line == NULL) 
		return NULL;
	if(var.iflag == 1) {
		strcpy(newline, lower(newline));
		strcpy(newpattern, lower(newpattern));
	}
	o_send = 0;
	token = strtok(newline, " \n\0");
	while(token != NULL) {
		if(strstr(token, newpattern) != NULL) {
				ocount = ocount + 1;
				o_send = 1;
		}
		token = strtok(NULL, " \n\0");	
	}
	if(o_send == 1) {
		return  pattern;
	}
	else {
		return NULL;
	} 
}
//n_grep print line number before lines...
char *n_grep(char *line, char *pattern) { 
	int line_len = strlen(line);
	int pattern_len = strlen(pattern);
	char *newline = (char *)malloc(line_len + 1);	
	char *newpattern = (char *)malloc(pattern_len + 1);	
	strcpy(newline, line);
	strcpy(newpattern, pattern);
	if(var.iflag == 1) {
		strcpy(newline, lower(newline));
		strcpy(newpattern, lower(newpattern));
	}
	if(strstr(newline, newpattern) == NULL ) {
		ncount = ncount + 1;
		free(newline);
		free(newpattern);
		if(var.vflag == 1) 
			return line;
		return NULL;
	}
	else {
		ncount = ncount + 1;
		free(newline);
		free(newpattern);
		if( var.vflag == 1) {
			return NULL;
		}
		return line;
	}
}
// b_grep print first byte number of line...

char *b_grep(char *line, char *pattern) {
	int line_len = strlen(line);
	int pattern_len = strlen(pattern);
	int y;
	char *newline = (char *)malloc(line_len + 1);	
	char *newpattern = (char *)malloc(pattern_len + 1);	
	strcpy(newline, line);
	strcpy(newpattern, pattern);
	y = strlen(line);
	if(var.iflag == 1) {
		strcpy(newline, lower(newline));
		strcpy(newpattern, lower(newpattern));
	}
	if(line == NULL) {
		free(newline);
		free(newpattern);
		return NULL;
	}
	if(strstr(newline, newpattern) == NULL ) {
		bcount = bcount + y;
		free(newline);
		free(newpattern);
		return NULL;	
	}
	else {
		bcount = bcount + y;
		free(newline);
		free(newpattern);
		return line;
	}
}

/*lowercase*/
char *lower(char *str) {
	int i;
	for(i = 0; str[i]; i++) {
		str[i] = tolower(str[i]);
	}
	return str;
}
