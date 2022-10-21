/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_errors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:11:04 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/27 17:01:28 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	is_only_spaces(char *line)
{
	size_t	i;

	i = 0;
	while (line[i] == ' ' || line[i] == '\t' || line[i] == '\n'
		|| line[i] == '\v' || line[i] == '\f' || line[i] == '\r')
		i++;
	if (i == ft_strlen(line))
		return (1);
	return (0);
}

static int	open_quotes(char *line, int i)
{
	int	count_quotes;

	count_quotes = 0;
	while (line[i])
	{
		if (line[i] == 39)
		{
			count_quotes++;
			i = skip_single_quotes(line, i);
			if (line[i] == 39)
				count_quotes++;
		}
		else if (line[i] == 34)
		{
			count_quotes++;
			i = skip_double_quotes(line, i);
			if (line[i] == 34)
				count_quotes++;
		}
		i++;
	}
	if (count_quotes % 2 != 0)
		return (1);
	return (0);
}

int	check_doublepipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		i = skip_double_quotes(line, i);
		i = skip_single_quotes(line, i);
		if (line[i] == '|')
		{
			i++;
			if (line[i] && line[i] == '|')
				return (1);
		}
		else
			i++;
	}
	return (0);
}

int	syntax_errors(char *line)
{
	int	i;

	i = 0;
	if (is_empty_line(line))
		return (error_msg(NULL, 0));
	if (is_only_spaces(line))
		return (error_msg(NULL, 0));
	if (open_quotes(line, i))
		return (error_msg(MSG_OPEN_QUOTES, 1));
	if (check_doublepipe(line))
		return (error_msg(MSG_DOUBLE_PIPE, PIPE_ERROR));
	if (is_metachar(line[0]))
		return (error_msg(MSG_PIPE_ERROR, PIPE_ERROR));
	if (check_redirections(line))
		return (error_msg(MSG_STDOUT, 258));
	return (0);
}
