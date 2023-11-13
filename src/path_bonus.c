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

/* get_path_line: This function searches in the environment variable
for the PATH variable and returns its contents. If the PATH variable
is empty, it returns NULL and a Warning message is printed. */

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

/* find_path: This functions aims at finding the right absolute path 
	for a command given. 
	First, all possible paths provided in the PATH variable (envp) are stored
	in data.dir. Next, all paths are tested with the help of the access function.
	As soon as the access function returns 0, i.e. a valid path was found,
	the loop is exited. The right path is stored in data.path. If no path at all
	is found to match the command, an error message is printed. */

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

/* format_commands: This function formats the commands and its
	possible arguments to fit the requirements of execve (array of
	pointers, array[0]= path/command, array[n] = argument(n)).
	First the string containing the command and arguments (0 to n)
	is split up and the command without its arguments is stored in
	temp_cmd. With the help of the access function it is checked if
	the command is exists. Either the user already provided the right
	absolute path or it is checked if the right path can be found in the 
	PATH variable (env). If no path is found the function returns NULL, 
	else it returns an array of pointers containing the command 
	(with its absolute path) and its arguments. In both cases,
	the program keeps on executing (same behaviour as bash).*/

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
