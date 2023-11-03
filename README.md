# Pipex
42 school's project Pipex (handling pipes)

## To Do/ Status:
 *
 * NOW: in the middle of trying to get the right exit status in case of exeve's failure
 * THEN: running tester again
 *
 * I use /bin/ as path and not envp variable to determine path. Thus, /usr/bin/cat does not work for me
 *  Error handling works BUT if command non-existent, different error message than shell command ("command not found", mine "No such file or directory"). 
 * Examples of pdf work, other examples have not been tested.
 * access, unlink and wait and dup have not been used -> have I missed something?
 * user input might be checked more thoroughly, maybe if its ASCII?



# Description
 Handling pipes. 


 
# Rules:

 * user input format: ./pipex file1 cmd1 cmd2 file2
 * allowed functions: open, close, perror, exit, read, write, dup, dup2, execve, fork, pipe, wait, waitpid, malloc, free, strerror, access, unlink
