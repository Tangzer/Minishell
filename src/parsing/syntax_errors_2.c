/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_syntax_errors.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:11:04 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/27 17:01:28 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_empty_line(char *line)
{
	if (*line == '\0')
		return (1);
	return (0);
}

int	error_msg(char *msg, int code)
{
	ft_error_no_ptr(msg, code);
	return (1);
}

static int	ends_with_redirection(char *line)
{
	int	i;

	if (!line)
		return (0);
	i = ft_strlen(line);
	while ((line[i] == ' ' || line[i] == '\0'))
		i--;
	if (is_a_less_redir(line, i) || is_a_greater_redir(line, i))
		return (1);
	return (0);
}

int	check_redirections(char *line)
{
	int		i;
	char	**array;

	array = ft_split_pipe(line, '|');
	i = 0;
	while (array[i])
	{
		if (ends_with_redirection(array[i]))
		{
			ft_free_split(array);
			return (1);
		}
		i++;
	}
	ft_free_split(array);
	return (0);
}
