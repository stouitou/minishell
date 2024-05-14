/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 11:04:44 by stouitou          #+#    #+#             */
/*   Updated: 2024/04/05 12:06:34 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	gnl_ischarset(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (1);
		i++;
	}
	return (0);
}

static char	*gnl_initstr(char *str)
{
	if (str == NULL)
	{
		str = (char *)malloc(1 * sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
	}
	return (str);
}

static char	*get_line(int fd, char *str, char *buffer)
{
	int		got;
	char	*tmp;

	if (str)
	{
		if (gnl_ischarset(str, '\n'))
			return (str);
	}
	got = 1;
	while (got)
	{
		got = read(fd, buffer, BUFFER_SIZE);
		if (got < 0)
			return (NULL);
		if (got == 0)
			break ;
		buffer[got] = '\0';
		str = gnl_initstr(str);
		tmp = str;
		str = ft_strjoin(tmp, buffer);
		free(tmp);
		if (gnl_ischarset(buffer, '\n'))
			break ;
	}
	return (str);
}

static char	*get_more(char *str)
{
	int		i;
	char	*tmp;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	tmp = ft_substr(str, i + 1, ft_strlen(str) - i);
	if (tmp == NULL)
	{
		free(str);
		exit (1);
	}
	if (tmp[0] == '\0')
	{
		free(tmp);
		return (NULL);
	}
	str[i + 1] = '\0';
	return (tmp);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*stash[1025];
	char		*buffer;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = (char *)malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (buffer == NULL)
		return (NULL);
	line = get_line(fd, stash[fd], buffer);
	free(buffer);
	if (line == NULL)
		return (NULL);
	stash[fd] = get_more(line);
	return (line);
}
