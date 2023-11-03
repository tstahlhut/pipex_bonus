/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:38:55 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/25 15:48:26 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* close_all_fd: This function closes all file descriptors of the pipes (fd) and
	the infiel (f1) and outfile (f2). */

void	close_all_fd(t_data *data)
{
	int	i;

	i = -1;
	if (data->fd != NULL)
	{
		while (++i < data->num_processes - 1)
		{
			if (data->fd[i])
			{
				error_check(close(data->fd[i][0]), "close failed", data);
				error_check(close(data->fd[i][1]), "close failed", data);
			}
		}
	}
	if (data->f1 && data->f1 != -1)
		error_check(close(data->f1), "close failed", data);
	if (data->f2 && data->f2 != -1)
		error_check(close(data->f2), "close failed", data);
}

/* ft_free_int: This function frees an array of pointers to int. */

void	ft_free_int(t_data *data)
{
	int	i;

	i = -1;
	if (data->fd)
	{
		while (++i < data->num_processes - 1)
			free(data->fd[i]);
		free(data->fd);
		data->fd = NULL;
	}
}

/* ft_free: This function frees an array of pointers to strings. */

void	ft_free(char **str)
{
	int	i;

	if (str)
	{
		i = 0;
		while (str[i])
		{
			free(str[i]);
			str[i] = NULL;
			i++;
		}
		free(str);
		str = NULL;
	}
}

/* ft_exit: This function garantuees a clean exit of the program in case
	of error and success. All allocated memory is freed, all file descriptors
	closed, all pointers set to NULL and if a "here_doc" file was created, it
	will be unlinked. */

void	ft_exit(t_data *data)
{
	int	i;

	i = -1;
	if (data->cmd)
	{
		while (++i < data->num_processes)
			ft_free(data->cmd[i]);
		free(data->cmd);
	}
	if (data->fd)
		ft_free_int(data);
	if (data->path)
		free(data->path);
	if (data->temp)
		ft_free(data->temp);
	if (data->dir)
		ft_free(data->dir);
	if (data->pid)
		free(data->pid);
	if (data->child_status)
		free(data->child_status);
	init_zero(data);
	if (data->here_doc)
		unlink(".here_doc");
	return ;
}
