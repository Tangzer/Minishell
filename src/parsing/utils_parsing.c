/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                      :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:32:31 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_metachar(char c)
{
	return (c == '|');
}

int	is_end_of_dollar(char c)
{
	if (!ft_isalnum(c))
		return (1);
	return (0);
}

int	update_i(char *line_pars, int i)
{
	while (!is_end_of_dollar(line_pars[i]) && line_pars[i])
		i++;
	return (i);
}

char	*str_dup_parts(char *src, int end, int start)
{
	char	*duplicate;
	int		i;

	if ((end - start) <= 0)
		return (ft_strdup(""));
	duplicate = malloc(sizeof(char) * (end - start) + 1);
	protect_malloc(duplicate);
	i = 0;
	while (src[i] && start - 1 < end)
	{
		duplicate[i] = src[start];
		i++;
		start++;
	}
	duplicate[i] = '\0';
	return (duplicate);
}

int	is_error_code(char *line, int i)
{
	if (line[i] == '$' && line[i + 1] == '?')
		return (1);
	return (0);
}
