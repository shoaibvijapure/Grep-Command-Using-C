# Grep-Command-Using-C

### SYNOPSIS FOR DSA PROJECT ###

Project Title : grep command.

MIS : 141808009	

### INTRODUCTION  ###

‘grep’ searches input files for lines containing a match to a given pattern list.  When it finds a match in a line, it copies the line to standard output (by default), or produces whatever other sort of output you have requested with options.

Though ‘grep’ expects to do the matching on text, it has no limits on input line length and it can match arbitrary characters within a line. 

### SYNTAX OF GREP ###
The general synopsis of the ‘grep’ command line is

    grep [OPTIONS] PATTERN [FILE...]

### COMMAND LINE OPTIONS DESCRIPTION ###

I will be implementing  i, w, q, n, f, o, m, b, c, v, H, h options. 

1) -i : Ignores case for matching.(i.e lower or upper both displays even we specify it with lower or viceversa)
2) -w : Matches the whole word.(Case sensitive)
3) -q : Quiet; do not write anything to standard output. Exit immediately with zero status if any match is found, even if an error was detected. 
4) -n : Display matched lines with their line numbers.
5) -f file : Takes pattern from file, one per line.
6) -o : only matching (prints only matched parts of matching line and displaying each part on seperate line).
7) -m : Stops the searching of files after num no. of lines are searched.
8) -b : Displays the byte offset of matched pattern in each line.
9) -c : count the no. of matching lines.
10) -v : displays all non-matching lines.
11) -H : prints filename for each matched lines containing pattern.
12) -h : Display matched lines, but don't display filenames.

### EXECUTING THE PROJECT ###

1. Run the Makefile by just typing make in terminal/shell.
2. Usage: ./mygrep [PATTERN]... [FILES]...
