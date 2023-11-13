/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 14:41:18 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/27 14:41:22 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	ft_error(char *variable, char *message, t_data *data)
{
	ft_printf("pipex: %s: %s\n", variable, message);
	ft_exit(data);
	exit(EXIT_FAILURE);
}

void	error_check(int x, char *message, t_data *data)
{
	if (x == -1)
	{
		ft_printf("pipex: %s: %s\n", message, strerror(errno));
		ft_exit(data);
		exit(EXIT_FAILURE);
	}
	return ;
}
