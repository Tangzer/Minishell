/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:10:43 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 23:10:46 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*remove_quotes(char *line)
{
	char	*new_line;
	int		i;
	int		j;
	char	quote;

	i = 0;
	j = 0;
	quote = 0;
	new_line = ft_strdup(line);
	while (line[i])
	{
		if (line[i] == quote)
			quote = 0;
		else if (!quote && (line[i] == 39 || line[i] == 34))
			quote = line[i];
		else
		{
			new_line[j] = line[i];
			j++;
		}
		i++;
	}
	new_line[j] = 0;
	free(line);
	return (new_line);
}
