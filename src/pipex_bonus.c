/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:47:06 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/11/13 13:16:36 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* exit_status: Captures the right exit status of child process.
	Macro WIFEXITED returns true if child terminated normally. 
	If this is the case, WEXITSTATUS is called to capture the exit status
	of the child. Else, the childs exit status is set to 1. */

void	exit_status(int child_status, t_data *data)
{
	if (WIFEXITED(child_status))
	{
		data->exit_status = WEXITSTATUS(child_status);
	}
	else
		data->exit_status = 1;
}

/* create_pipes: This function creates num_processes - 1 pipes so that there
	is a pipe between each command. The file desciptors for the pipes are
	stored in data.fd.*/

void	creat_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_processes - 1)
		error_check(pipe(data->fd[i]), "pipe", data);
}

/* pipex: 
	First, the pipes between the commands are created.
	Then, for each command a child process is created with fork() in a loop.
	All file desciptors open are closed in the parent process and
	the parent process waits for each child process to finish. 
	The exit status of each child process is stored in child_status.
	(Remark: Now the parent is waiting for child process 1, then 2, etc.),
	maybe it would be better to change it -1 so that it waits for
	andy child process and thus finishes earlier, if for example the last
	commands is "ls" which does not wait for input from the pipe.) */

void	pipex(t_data *data, int i)
{
	creat_pipes(data);
	i = -1;
	while (++i < data->num_processes)
	{
		error_check(data->pid[i] = fork(), "fork process", data);
		if (data->pid[i] == 0)
		{
			if (!data->cmd[i] | !data->cmd[i][1])
			{
				close_all_fd(data);
				ft_exit(data);
				exit(127);
			}
			else
				child_process(data, i);
		}
	}
	i = -1;
	close_all_fd(data);
	while (++i < data->num_processes)
	{
		waitpid(data->pid[i], &data->child_status[i], 0);
		exit_status(data->child_status[i], data);
	}
}

/* pipex(bonus): Mimics the behaviour of pipes and redirections in a shell.
				shell: "< infile command1 | command2 > outifle"
				pipex: "./pipex infile "command1" "command2" outfile"
				shell: "command1 << LIMITER | command2 >> outfile"
				pipex: "./pipex here_doc LIMITER "command1" "command2" outfile"
Needs at least 4 arguments. This is checked in input_check.
Next, all variables in data struct are set to 0 or NULL to avoid
bad pointers in case of error. 
In case the user typed "here_doc" here_doc is set to 1 to know for later decisions.
Necessary memory is allocated and variables set (ft_init).
Infile and outfile are opened. In case the user used "here_doc" the user input
is read and stored in data.f1 (infile). Everything is backed by an error_check
function. 
The commands and their arguments are formatted to fit the requirements of the 
execve function and stored in the array data.cmd.
Next, the commands are executed in the pipex function which also handles the pipes
and redirections. After its successful execution all allocated memory is freed and
the program exits with the exit status of the child process which finished last. 
(The exit status almost fits the exit statuses of bash but not always. In this point
the program could be improved.)*/

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	int		i;

	input_check(argc);
	init_zero(&data);
	if (ft_strncmp(argv[1], "here_doc", 8) == 0)
		data.here_doc = 1;
	ft_init(&data, argc);
	if (data.here_doc == 1)
		here_doc(&data, argv[2]);
	else
		error_check(data.f1 = open(argv[1], O_RDONLY), argv[1], &data);
	data.f2 = open(argv[argc - 1], O_CREAT | O_WRONLY | O_TRUNC, 00664);
	error_check(data.f2, argv[argc - 1], &data);
	data.cmd = malloc(sizeof(char **) * (data.num_processes + 1));
	if (!data.cmd)
		ft_error("data.cmd", "malloc failed", &data);
	data.cmd[data.num_processes] = NULL;
	i = -1;
	while (++i < data.num_processes)
		data.cmd[i] = format_commands(argv[i + 2 + data.here_doc], envp, &data);
	pipex(&data, i);
	ft_exit(&data);
	return (data.exit_status);
}
