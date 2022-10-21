/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tok_cmd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 13:51:25 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 06:35:50 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*add_space(char *tmp, char *new_line)
{
	tmp = ft_strjoin(new_line, " ");
	free(new_line);
	return (tmp);
}

static char	**malloc_and_free(char *line)
{
	char	**array;

	array = ft_split_pipe(line, ' ');
	protect_malloc(array);
	free(line);
	return (array);
}

static char	*return_properly(char **split_space, char *line)
{
	ft_free_split(split_space);
	return (line);
}

static char	*join_properly(char *tmp, char *line_split)
{
	char	*new_line;

	new_line = ft_strjoin(tmp, line_split);
	free(tmp);
	return (new_line);
}

char	*remove_multi_space(char *line)
{
	char	**split_space;
	int		i;
	char	*new_line;
	char	*tmp;

	split_space = malloc_and_free(line);
	i = 1;
	new_line = ft_strdup(split_space[0]);
	tmp = NULL;
	if (split_space[i])
		tmp = add_space(tmp, new_line);
	else
		return (return_properly(split_space, new_line));
	while (split_space[i])
	{
		new_line = join_properly(tmp, split_space[i]);
		if (split_space[i + 1])
			tmp = add_space(tmp, new_line);
		else
			return (return_properly(split_space, new_line));
		i++;
	}
	free(new_line);
	ft_free_split(split_space);
	return (tmp);
}
