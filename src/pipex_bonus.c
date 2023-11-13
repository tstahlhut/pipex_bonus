/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:47:06 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/25 15:52:25 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	exit_status(int child_status, t_data *data)
{
	if (WIFEXITED(child_status))
	{
		data->exit_status = WEXITSTATUS(child_status);
	}
	else
		data->exit_status = 1;
}

void	creat_pipes(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->num_processes - 1)
		error_check(pipe(data->fd[i]), "pipe", data);
}

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
