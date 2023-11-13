/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:52:27 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/27 14:52:30 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

char	*get_path_line(char **envp)
{
	int	i;

	i = 0;
	while (strncmp(envp[i], "PATH", 4) && envp[i])
		i++;
	if (envp[i] == NULL)
		ft_printf("No path found in environment variable.");
	return (envp[i]);
}

void	find_path(char **envp, char *cmd, t_data *data)
{
	int		x;
	int		i;
	char	*test_path;

	if (!data->dir)
		data->dir = ft_split(get_path_line(envp) + 5, ':');
	i = 0;
	x = 1;
	while (data->dir[i] && x)
	{
		data->path = ft_strjoin(data->dir[i], "/");
		test_path = ft_strjoin(data->path, cmd);
		if (access(test_path, F_OK) == 0)
			x = 0;
		else
		{
			free(data->path);
			data->path = NULL;
			i++;
		}
		free(test_path);
		test_path = NULL;
	}
	if (x == 1)
		ft_printf("pipex: %s: command not found\n", cmd);
}

char	**format_commands(char *cmd, char **envp, t_data *data)
{
	char	**arr;
	char	*temp_cmd;

	data->temp = ft_split(cmd, ' ');
	temp_cmd = ft_strdup(data->temp[0]);
	ft_free(data->temp);
	data->temp = NULL;
	if (access(temp_cmd, F_OK) != 0)
	{
		find_path(envp, temp_cmd, data);
		free(temp_cmd);
		if (data->path == NULL)
			return (NULL);
		temp_cmd = ft_strjoin(data->path, cmd);
		free(data->path);
		data->path = NULL;
		arr = ft_split(temp_cmd, ' ');
	}
	else
		arr = ft_split(cmd, ' ');
	free(temp_cmd);
	temp_cmd = NULL;
	return (arr);
}
