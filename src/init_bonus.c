/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:47:18 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/24 15:16:29 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

/* input_check: The user input is checked.
	In this case, it is sufficient to only check the number of arguments,
	which should be at least 4: infile, cmd1, cmd2, outfile.
	I set the max. amount of commands to an arbitrary 20. This may be changed.*/

void	input_check(int argc)
{
	if (argc < 5)
	{
		ft_printf("Error: at least 4 arguments required:\n");
		ft_printf(" ./pipex infile cmd1 cmd2 ... cmdn outfile.\n");
		exit(EXIT_FAILURE);
	}
	if (argc > 23)
	{
		ft_printf("The max number of commands has been set to 20\n");
		exit(EXIT_FAILURE);
	}
	return ;
}

/* init_zero: All variables are set to 0 or NULL. */

void	init_zero(t_data *data)
{
	data->f1 = 0;
	data->f2 = 0;
	data->cmd = NULL;
	data->path = NULL;
	data->temp = NULL;
	data->dir = NULL;
	data->num_processes = 0;
	data->fd = NULL;
	data->pid = NULL;
	data->child_status = NULL;
	return ;
}

/* ft_init: For the variables in the data struct the necessary memory is allocated
 	and variables are set. 
 	The number of processes equals argc - 3 (program name, infile, outfile)
 	or one less (here_doc). The same is the case for the number of file
 	descriptors,the number of process IDs and of exit statuses for the 
 	child processes (child_status). */

void	ft_init(t_data *data, int argc)
{
	int	i;

	data->num_processes = (argc - 3);
	if (data->here_doc == 1)
		data->num_processes -= 1;
	data->fd = (int **)malloc(sizeof(int *) * (argc - 3));
	if (!data->fd)
		ft_error("malloc", "failed", data);
	i = -1;
	while (++i < data->num_processes - 1)
	{
		data->fd[i] = (int *)malloc(sizeof(int) * 2);
		if (!data->fd[i])
			ft_error("malloc", "failed", data);
	}
	data->pid = (int *)malloc(sizeof(int) * data->num_processes);
	if (!data->pid)
		ft_error("malloc", "failed", data);
	data->child_status = (int *)malloc(sizeof(int) * data->num_processes);
	if (!data->child_status)
		ft_error("malloc", "failed", data);
}
