/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:50:40 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/26 18:25:28 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*get_cmd(char *str, int i)
{
	int		y;
	char	*line;

	y = 0;
	if (!str)
		return (NULL);
	line = malloc(sizeof(char) * i + 1);
	protect_malloc(line);
	while (y < i)
	{
		line[y] = str[y];
		y++;
	}
	line[y] = '\0';
	return (line);
}

static int	manage_redirection_with_quotes(char **line_split, int i)
{
	while (line_split[i])
	{	
		if (line_split[i][0] == 39)
			i++;
		else if (line_split[i][0] == 34)
			i++;
		else if (line_split[i] && is_a_greater_redirection(line_split, i))
			return (i);
		else
			i++;
	}
	return (i);
}

int	tok_1(char **tok, char **line_split, int i, char *line)
{
	t_var	var;

	var.end = NULL;
	if (!line_split[i])
		return (-1);
	if (!ft_strcmp(line_split[i], DGREAT) || !ft_strcmp(line_split[i], GREAT))
	{
		tok[1] = ft_strdup("echo -n");
		return (i);
	}
	var.start = ft_strdup(line_split[i]);
	var.tmp = ft_strstr(line, var.start);
	free(var.start);
	i = manage_redirection_with_quotes(line_split, i);
	if (line_split[i])
		var.end = ft_strdup(line_split[i]);
	if (var.end && i != 0)
	{
		var.i_end = find_real_redir(var.tmp, var.end);
		free(var.end);
	}
	else
		var.i_end = ft_strlen(line);
	tok[1] = get_cmd(var.tmp, var.i_end);
	return (i);
}
