# Pipex
A school project of 42 coding school
To learn about handling pipes, redirections and processes.



## Description
 Pipex, together with its bonus part, mimicks the behaviour of pipes and redirections in a shell (bash).

### Background Information

 #### Pipes |
 In bash the output of a command can be piped to another command: 
 	
  	cmd1 | cmd2
 This means that the result of cmd1 is not displayed in the terminal (i.e. written to STDOUT) but directed to
 cmd2 that takes it as input. 

 #### Redirections < > << >>
 In bash, you can also provide a file as input to a command and/ or put the result of a command (or command chain)
 into a file. You redirect the input and/ or output. By default, the input is STDIN (i.e. what you type into your terminal)
 and the output is STDOUT (i.e. what is displayed on the screen). In your C program you can do this with the help of the
 function dup2(). 

 	< infile command > outfile

### Rules:

 * user input format: ./pipex file1 cmd1 cmd2 file2
     or:              ./pipex here_doc LIMITER cmd1 cmd2 file
 * allowed functions: open, close, perror, exit, read, write, dup, dup2, execve, fork, pipe, wait, waitpid, malloc, free, strerror, access, unlink
   

### Usage
The subject of pipex requires it to take an infile and an outfile and at least two commands.
The syntax of pipex differs a little to the one in bash but the behaviour should be the same:

1. The user can pipe as many commands as they wish. If a command has arguments, the command and its arguments have to be put in double quotes ("..."):
   
	shell (bash):

		< infile command1 argument1 argument2 | command2 | ... | commandn > outifle
  
	pipex:

		./pipex infile "command1 argument1 argument 2" command2 outfile

3. Instead of providing an input file, the user can type the input directly into the terminal by typing "here_doc". As in bash, a limiter word has to be provided. As soon as the user types in the limiter, the program stops to read the input. The result of the piped commands is written to an output file, defined by the user. It is written in APEND mode which means that if the file already exists, the content of the file is not overwritten but appended. Of course, the user may pipe more than two commands. However, I limited the amount of commands to 20.
   
	shell (bash)

		command1 << LIMITER | command2 >> outfile
	pipex:
	
 		./pipex here_doc LIMITER command1 command2 outfile

## End Note
Especially, if you are a 42 student (but not only), please note the following:
- I did not upload the mandatory part because it is included in the bonus part. This would have been redundant.
- I passed the three peer evaluations with each 125%.
- You are welcome to use my code as inspiration for your project, but do not copy. This does not help you with your studies.
- If you have any questions about my implementation, find errors, flaws or have suggestions of how to improve the code, please write me on slack: tstahlhu.
- And last but not least: Yes, its worth doing the bonus part, you will need it in minishell. 
