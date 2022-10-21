/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:12:38 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 06:37:18 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*parsing(char *line, t_struct *data)
{
	int		i;
	char	quote;

	line = remove_multi_space(line);
	quote = 0;
	i = 0;
	while (line[i])
	{
		quote = get_value_of_quote(quote, line, i);
		if (line[i] == '$' && (quote == 0 || quote == 34))
		{
			line = parsing_dollar(data, line, i);
			i = 0;
			quote = 0;
			continue ;
		}
		i++;
	}
	line = remove_quotes(line);
	line = parsing_redirstdin(line);
	return (line);
}
