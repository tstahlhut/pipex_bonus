/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 11:00:53 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/09/27 14:00:09 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

char	*read_and_stash(int fd, char *stash)
{
	int		r;
	char	*buf;

	r = 1;
	while (check_line(stash) == 0 && r > 0)
	{
		buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
		{
			ft_free_str(&stash);
			return (NULL);
		}
		r = read(fd, buf, BUFFER_SIZE);
		if ((stash == NULL && r == 0) || r == -1)
		{
			ft_free_str(&buf);
			return (NULL);
		}
		buf[r] = '\0';
		stash = ft_strjoin_gnl(stash, buf);
		ft_free_str(&buf);
	}
	return (stash);
}

char	*ft_save_stash(char *str, int start)
{
	int		i;
	char	*dst;

	if (start == 0 || str[start] == '\0')
	{
		ft_free_str(&str);
		return (NULL);
	}
	i = strlen_gnl(str + start);
	dst = malloc(sizeof(char) * (i + 1));
	if (!dst)
	{
		ft_free_str(&str);
		return (NULL);
	}
	i = 0;
	while (str[start + i] != '\0')
	{
		dst[i] = str[start + i];
		i++;
	}
	dst[i] = '\0';
	ft_free_str(&str);
	return (dst);
}

char	*ft_copy_line(char *str, int i)
{
	char	*dst;

	if (!str || str == NULL || *str == '\0')
		return (NULL);
	dst = malloc(sizeof(char) *(i + 1));
	if (!dst)
		return (NULL);
	dst[i] = '\0';
	while (i > 0)
	{
		i--;
		dst[i] = str[i];
	}
	return (dst);
}

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			len;

	line = NULL;
	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &line, 0) < 0)
	{
		ft_free_str(&stash);
		return (NULL);
	}
	stash = read_and_stash(fd, stash);
	len = ft_strlen_nl(stash);
	line = ft_copy_line(stash, len);
	if (line == NULL)
	{
		ft_free_str(&stash);
		return (NULL);
	}
	stash = ft_save_stash(stash, len);
	return (line);
}
