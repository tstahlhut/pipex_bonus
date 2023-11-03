# Pipex
A school project of 42 coding school
To learn about handling pipes, redirections and processes.



## Description
 Pipex, together with its bonus part, mimicks the behaviour of pipes and redirections in a shell (bash).

### Usage
Its usage differs a little to the usage in bash but the behaviour should be the same:

    shell: "< infile command1 argument1 argument2 | command2 | ... | commandn > outifle"
				pipex: "./pipex infile "command1 argument1 argument 2" command2 outfile"
    
				shell: "command1 << LIMITER | command2 >> outfile"
				pipex: "./pipex here_doc LIMITER command1 command2 outfile"

### Rules:

 * user input format: ./pipex file1 cmd1 cmd2 file2
     or:              ./pipex here_doc LIMITER cmd1 cmd2 file
 * allowed functions: open, close, perror, exit, read, write, dup, dup2, execve, fork, pipe, wait, waitpid, malloc, free, strerror, access, unlink
