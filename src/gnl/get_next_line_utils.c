/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tstahlhu <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/28 12:57:26 by tstahlhu          #+#    #+#             */
/*   Updated: 2023/04/04 14:48:18 by tstahlhu         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

void	ft_free_str(char **str)
{
	if (*str && str)
	{
		free (*str);
		*str = NULL;
	}
}

int	strlen_gnl(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

int	ft_strlen_nl(const char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (0);
	while (str[i] != '\0' && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

int	check_line(char *str)
{
	int	i;

	i = 0;
	if (str == NULL || *str == '\0')
		return (0);
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strjoin_gnl(char *s1, char *s2)
{
	char	*str;
	int		i;
	int		j;

	if ((s1 == NULL || *s1 == '\0') && (s2 == NULL || *s2 == '\0'))
		return (NULL);
	str = (char *)malloc(sizeof(*str) * (strlen_gnl(s1) + strlen_gnl(s2) + 1));
	if (!str)
	{
		ft_free_str(&s1);
		return (NULL);
	}
	i = 0;
	while (s1 != NULL && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2 != NULL && s2[j] != '\0')
		str[i++] = s2[j++];
	str[i] = '\0';
	ft_free_str(&s1);
	return (str);
}
