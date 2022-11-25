# Linux-Shell-in-C

We had to write a C Program whose output works in similar way as a shell.

Standard C libraries, including Linux system calls such as fork, exec family system call, and wait
family system calls have been used in this assignment.

instruction to run shell:
open your terminal and run gcc shell.c -o shell
use ./shell.out to run the the executable


The functions available in the given shell are 

	Builtins
		cd - to change the present working directory.
		eg - cd lab/ to move to lab directory contained in documents directory
		or, cd /document/lab to move from home to lab directly.
		options for this include-
			cd .. - this command is used to move to the parent directory of current directory, or the directory one level up from the current directory.
			cd / - this command is used to change directory to the root directory.
			
		pwd - shows present working directory.
		
		echo - Displays whatever is specified in arguments.
		
		exit - to exit from the shell
		
		help - Shows info about builtin functions in shell.
	Externals
		ls - lists the current directory contents.
		options for this include-
			ls -l makes a column list of content
			ls -a does not ignore entries starting with .
		cat command allows us to create single or multiple files, view content of a file, concatenate filesand redirect output in terminal or files.
		options for this include-
			cat >filename – creates new file; Awaits input from the user, type desired text, and press CTRL+D to exit.
			With the -n option you could see the line numbers of a file.
		mkdir - makes directory 
		rm - removes file and directory
		date - show date and time.
