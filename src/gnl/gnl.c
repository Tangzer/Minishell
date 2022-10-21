/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 12:43:50 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/12 12:44:07 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static size_t	is_line(char *str)
{
	size_t	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	return (i);
}

static char	*read_file(char *rest, int fd, char *msg)
{
	char	*reading;
	int		rc;

	reading = malloc(sizeof(char) * BUFFER_SIZE + 1);
	protect_malloc(reading);
	rc = 1;
	while (rc && !ft_strchr(rest, '\n') && g_error_code != 130)
	{
		ft_putstr_fd(msg, 0);
		rc = read(fd, reading, BUFFER_SIZE);
		if (rc < 0)
			return (ft_free(reading));
		reading[rc] = '\0';
		rest = ft_strjoin_gnl(rest, reading);
	}
	ft_free(reading);
	return (rest);
}

static char	*get_line(char *rest, size_t i)
{
	char	*line;
	size_t	y;

	if (!rest[0])
		return (NULL);
	line = malloc(sizeof (char) * i + 1);
	protect_malloc(line);
	i = 0;
	y = 0;
	while (rest[i] && rest[i] != '\n')
		line[y++] = rest[i++];
	if (rest[i] == '\n')
		line[y++] = rest[i];
	line[y] = '\0';
	return (line);
}

static char	*recover_rest(char *rest, size_t i)
{
	char	*save;
	size_t	y;

	if (!rest[0])
		return (ft_free(rest));
	save = malloc(sizeof (char) * ft_strlen(rest) - i + 1);
	protect_malloc(save);
	y = 0;
	while (rest[i])
		save[y++] = rest[i++];
	save[y] = '\0';
	ft_free(rest);
	return (save);
}

char	*get_next_line(int fd, char *msg)
{
	char static	*rest;
	char		*line;

	if (BUFFER_SIZE <= 0 || fd < 0 || fd > OPEN_MAX)
		return (NULL);
	rest = read_file(rest, fd, msg);
	if (!rest)
		return (NULL);
	line = get_line(rest, is_line(rest));
	rest = recover_rest(rest, is_line(rest));
	return (line);
}
