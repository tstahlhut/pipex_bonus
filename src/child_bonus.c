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
