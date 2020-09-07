#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <error.h>

/*colors*/
#define G_RED     "\x1b[31m"
#define G_GREEN   "\x1b[32m"
#define G_YELLOW  "\x1b[33m"
#define G_BLUE    "\x1b[34m"
#define G_MAGENTA "\x1b[35m"
#define G_CYAN    "\x1b[36m"
#define G_RESET   "\x1b[0m"

typedef struct data {
	int iflag, oflag, nflag, normalflag, vflag, bflag, fflag, wflag, cflag, qflag, hflag, Hflag, mflag, rflag;
} data;

/*globals*/
static int bcount = 0, mcount = 0, count = 1 , ncount = 0, ocount = 0, ccount = 0;
static data var, outvar;

/*function declaration*/
char *lower(char *str);
void setflag(data var);
void printline(char *line, char *pattern, data var, data outvar , char *argv[], int argc, int argm);
char *o_grep(char *line, char *pattern);
char *n_grep(char *line, char *pattern);
char *f_grep(char *line, char *filename);
char *i_grep(char *line, char *pattern);
char *v_grep(char *line, char *pattern);
char *w_grep(char *line, char *pattern);
char *grep_match(char *line, char *pattern);
char *b_grep(char *line, char *pattern);
char *m_grep(char *line, int itr, char *pattern);

