/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/15 12:46:47 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/25 15:47:52 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <string.h>
# include <errno.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "../libft/ft_printf.h"
# include "get_next_line.h"

typedef struct s_data 
{
	int		f1;
	int		f2;
	char	***cmd;
	char	*path;
	char	**temp;
	char	**dir;
	int		num_processes;
	int		**fd;
	int		*pid;
	int		*child_status;
	int		exit_status;
	int		here_doc;
}			t_data;

/* init_bonus.c: */
void	input_check(int argc);
void	init_zero(t_data *data);
void	ft_init(t_data *data, int argc);

/* path_bonus.c: */
char	*get_path_line(char **envp);
void	find_path(char **envp, char *cmd, t_data *data);
char	**format_commands(char *cmd, char **envp, t_data *data);

/* pipex_bonus.c:	*/
void	exit_status(int child_status, t_data *data);
void	creat_pipes(t_data *data);
void	pipex(t_data *data, int i);

/* child_bonus.c: */
void	close_fd(int x, t_data *data);
void	child_process(t_data *data, int n);

/* here_doc_bonus.c */
void	here_doc(t_data *data, char *limiter);

/* error_bonus.c: */
void	ft_error(char *variable, char *message, t_data *data);
void	error_check(int x, char *message, t_data *data);

/* clean_up_bonus.c: */
void	close_all_fd(t_data *data);
void	ft_free_int(t_data *data);
void	ft_free(char **str);
void	ft_exit(t_data *data);

#endif /* PIPEX_BONUS_H */