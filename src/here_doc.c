/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <tstahlhu@student.42berlin.d      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 10:25:04 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/27 13:54:03 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex_bonus.h"

void	here_doc(t_data *data, char *limiter)
{
	char	*buf;
	int		heredoc;

	heredoc = open(".here_doc", O_WRONLY | O_CREAT | O_TRUNC, 00664);
	error_check(heredoc, ".here_doc", data);
	while (1)
	{
		ft_printf("heredoc>");
		buf = get_next_line(0);
		if (strncmp(buf, limiter, ft_strlen(limiter)) == 0)
			break ;
		write(heredoc, buf, ft_strlen(buf));
		write(heredoc, "/n", 1);
		free(buf);
	}
	free(buf);
	close(heredoc);
	error_check(data->f1 = open(".here_doc", O_RDONLY), ".here_doc", data);
}
