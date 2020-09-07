#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <ctype.h>
#include <error.h>
#include "grep.h"
int main (int argc, char *argv[]) {
	int c, argm, size = 100000;
	char *line, *pattern;
	FILE *fp;
	line = (char *)malloc(size);
	void setflag(data var);
	void setflag(data outvar);
	if(argc < 3) 
		printf(G_GREEN" invalid arguments \n Usage: grep [OPTION]... PATTERN [FILE]...\n" G_RESET);
	while ((c = getopt (argc, argv, "wcvqhHiobm:rfn")) != -1) {
		switch (c) {
			case 'c':
				var.cflag = 1;
		   		break;
			case 'v':
				var.vflag = 1;
				break;
			case 'w':
				var.wflag = 1;
				break;
			case 'o':
				var.oflag = 1;
				break;		
			case 'q':
				var.qflag = 1;
				break;
			case 'h':
				var.hflag = 1;
				break;
			case 'i':
				var.iflag = 1;
				break;
			case 'H':
				var.Hflag = 1;
				break;
			case 'b':
				var.bflag = 1;
				break;
			case 'm':
				var.mflag = 1;
				argm = atoi(optarg);
				break;
			case 'r':
				var.rflag = 1;
				break;
			case 'f':
				var.fflag = 1;
				break;	
			case 'n':
				var.nflag = 1;
				break;
			default:
				if (var.qflag != 1) 
					printf("Usage: grep [OPTION]... PATTERN [FILE]...\n");
		}
	}
	count = optind;
	pattern = argv[count++];
	while(count != argc){
		fp = fopen(argv[count], "r");
		if(fp == NULL ) {
			if(var.qflag != 1) 
				printf(G_RED"grep:"G_CYAN" %s "G_GREEN": No such file or directory\n" G_RESET, argv[count]);
			goto nextfile;
		}
		while(fgets(line, size, fp)) { 
			printline(line, pattern, var, outvar, argv, argc, argm); 
			free(line);
			line = (char *)malloc(size);
		} 
		if(var.cflag == 1 && var.qflag != 1) {
			if(var.Hflag == 1 ) 
				printf(G_MAGENTA"%s:"G_RESET, argv[count]);
			printf("%d\n", ccount);
			ccount = 0;
		}
		fclose(fp);
		nextfile:
		count++;
		bcount = 0;
		mcount = 0;
		ncount = 0;
	}
	return 0;
}

