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

/* ft_error: In case of error, an error message is printed, 
	allocated memory is freed and the program exits. */

void	ft_error(char *variable, char *message, t_data *data)
{
	ft_printf("pipex: %s: %s\n", variable, message);
	ft_exit(data);
	exit(EXIT_FAILURE);
}

/* error_check: This function checks the return value of functions like "open"
	or "pipe". If it is -1 and error message is printed with the helpf of errno, 
	allocated memory is freed and the program exits. */

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
