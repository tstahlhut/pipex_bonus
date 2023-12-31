/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:48:18 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/27 14:48:20 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* close_fd: This function closes all file descriptors that are not used. */

void	close_fd(int x, t_data *data)
{
	int	i;

	i = 0;
	while (i < x - 1)
	{
		error_check(close(data->fd[i][0]), "close failed", data);
		error_check(close(data->fd[i][1]), "close failed", data);
		i++;
	}
	i++;
	if (i == x && x <= data->num_processes - 1)
	{
		if (x > 0)
			error_check(close(data->fd[i - 1][1]), "close failed", data);
		if (x != data->num_processes - 1)
			error_check(close(data->fd[i][0]), "close failed", data);
		i++;
	}
	while (i < data->num_processes - 1)
	{
		error_check(close(data->fd[i][0]), "close failed", data);
		error_check(close(data->fd[i][1]), "close failed", data);
		i++;
	}
}

/* child_process: The command is executed in the child process.
	First, the ends of the pipes (fd_in & fd_out) are put to the right
	file descriptors. If it is the first command it gets its input from 
	the infile (data->f1), else from the command before (n - 1). And the last
	command writes its output to the outfile (data->f2). 
	All other file descriptors are closed in close_fd().
	The input and output is redirected with the help of dup2() and 
	the duplicated file descriptors closed. 
	With the help of execve the command is executed. If it is executed success-
	fully, the child process will not return and execute the lines afterwards.
	In case of an error, however, the output is again set to stdout, the fd closed
	and the error function with errno called. */

void	child_process(t_data *data, int n)
{
	int	fd_in;
	int	fd_out;
	int	stdout_cpy;

	if (n == 0)
		fd_in = data->f1;
	else
		fd_in = data->fd[n - 1][0];
	if (n == data->num_processes - 1)
		fd_out = data->f2;
	else
		fd_out = data->fd[n][1];
	close_fd(n, data);
	stdout_cpy = dup(1);
	dup2(fd_in, 0);
	dup2(fd_out, 1);
	close(fd_in);
	close(fd_out);
	execve(data->cmd[n][0], data->cmd[n], NULL);
	dup2(stdout_cpy, 1);
	close(fd_out);
	ft_error(data->cmd[n][0], strerror(errno), data);
}
