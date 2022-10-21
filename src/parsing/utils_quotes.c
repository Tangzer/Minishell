/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:10:43 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 23:10:46 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	get_value_of_quote(char quote, char *line, int i)
{
	if (quote == 39)
	{
		if (line[i] == 39)
			quote = 0;
	}
	else if (quote == 34)
	{
		if (line[i] == 34)
			quote = 0;
	}
	else
	{
		if (line[i] == 34 || line[i] == 39)
			quote = line[i];
	}
	return (quote);
}

int	skip_single_quotes(char *line, int i)
{
	if (line[i] == 39)
	{
		i++;
		while (line[i] != 39 && line[i])
			i++;
	}
	return (i);
}

int	skip_double_quotes(char *line, int i)
{
	if (line[i] == 34)
	{
		i++;
		while (line[i] != 34 && line[i])
			i++;
	}
	return (i);
}

void	skip_spaces(char **lineptr)
{
	while (*(*lineptr) == ' ' || *(*lineptr) == '\t')
		(*lineptr)++;
}
