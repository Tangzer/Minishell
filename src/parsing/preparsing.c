/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   preparsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 17:58:23 by algaspar          #+#    #+#             */
/*   Updated: 2022/09/21 19:07:46 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	ignore_quote(char **lineptr, char **bufptr, char c)
{
	*(*bufptr)++ = *(*lineptr)++;
	while (*(*lineptr) && *(*lineptr) != c)
		*(*bufptr)++ = *(*lineptr)++;
	if (*(*lineptr) == c)
		*(*bufptr)++ = *(*lineptr)++;
}

static void	check_chevron(char **lineptr, char **bufptr, char c, char *buffer)
{
	if (*bufptr != buffer && *(*(bufptr) - 1) != ' ')
		*(*bufptr)++ = ' ';
	*(*bufptr)++ = *(*lineptr)++;
	if (*(*lineptr) == c)
	{
		*(*bufptr)++ = *(*lineptr)++;
		if (*(*lineptr) && *(*lineptr) != ' ')
			*(*bufptr)++ = ' ';
	}
	else if (*(*lineptr) && *(*lineptr) != ' ')
		*(*bufptr)++ = ' ';
}

static void	check_pipe(char **lineptr, char **bufptr, char *buffer)
{
	if (*bufptr != buffer && *(*(bufptr) - 1) != ' ')
		*(*bufptr)++ = ' ';
	*(*bufptr)++ = *(*lineptr)++;
	if (*(*lineptr) && *(*lineptr) != ' ')
		*(*bufptr)++ = ' ';
}

static void	check_space(char **lineptr, char **bufptr)
{
	*(*bufptr)++ = *(*lineptr)++;
	while (*(*lineptr) == ' ')
		(*lineptr)++;
}

char	*preparsing(char *line)
{
	char	buffer[ARG_MAX];
	char	*bufptr;
	char	*new_line;
	char	*lineptr;

	ft_memset(buffer, 0, sizeof(buffer));
	bufptr = buffer;
	lineptr = line;
	skip_spaces(&lineptr);
	while (*lineptr)
	{
		if (*lineptr == 34 || *lineptr == 39)
			ignore_quote(&lineptr, &bufptr, *lineptr);
		else if (*lineptr == '<' || *lineptr == '>')
			check_chevron(&lineptr, &bufptr, *lineptr, buffer);
		else if (*lineptr == '|')
			check_pipe(&lineptr, &bufptr, buffer);
		else if (*lineptr == ' ')
			check_space(&lineptr, &bufptr);
		else
			*bufptr++ = *lineptr++;
	}
	new_line = ft_strdup(buffer);
	free(line);
	return (new_line);
}
