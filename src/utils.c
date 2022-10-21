/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 18:44:52 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 18:44:54 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	protect_malloc(void *element)
{
	if (!element)
	{
		g_error_code = MALLOC;
		exit(g_error_code);
	}
}

char	*msg(char *cmd, char *element, char *msg, int code)
{
	char	*tmp;
	char	*message;

	if (code == 1)
	{
		message = ft_strdup(msg);
		return (message);
	}
	tmp = ft_strjoin("minishell: ", cmd);
	message = ft_strjoin(tmp, ": ");
	free(tmp);
	if (element)
	{
		tmp = ft_strjoin(message, element);
		free(message);
		message = ft_strjoin(tmp, ": ");
		free(tmp);
	}
	tmp = ft_strjoin(message, msg);
	free(message);
	return (tmp);
}

int	find_real_redir( char *haystack, char *needle)
{
	int	i;
	int	y;

	i = 0;
	if (needle[i] == '\0')
		return (-1);
	while (haystack[i])
	{
		y = 0;
		i = skip_double_quotes(haystack, i);
		i = skip_single_quotes(haystack, i);
		while (haystack[i + y] == needle[y])
		{
			if (needle[y + 1] == '\0')
				return (i - y);
			y++;
		}
		i++;
	}
	return (-1);
}

char	*reverse_split(char **line_split, char *add)
{
	char	*tmp;
	char	*line;
	int		i;

	i = 1;
	line = ft_strdup(line_split[0]);
	tmp = ft_strjoin(line, add);
	while (line_split[i])
	{
		free(line);
		line = ft_strjoin(tmp, line_split[i]);
		free(tmp);
		tmp = ft_strjoin(line, add);
		i++;
	}
	free(line);
	return (tmp);
}
