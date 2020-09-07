grepmain.o: grepfun.o grep.h
	cc grep.h grepfun.c grepmain.c -Wall -o mygrep
	



