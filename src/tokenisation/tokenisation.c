/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenisation.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:49:46 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/26 18:15:55 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	**tok_initialization(t_struct *data, char *line)
{
	char	**line_split;

	data->i_redir = 0;
	data->cmd = -1;
	line_split = ft_split_pipe(line, ' ');
	return (line_split);
}

static int	tok_0(t_struct *data, char **tok, char **line_split, int i)
{
	i = tok_fd_in(data, tok, line_split, i);
	while (data->i_redir != -1)
	{
		free(tok[0]);
		i = tok_fd_in(data, tok, line_split, i);
	}
	return (i);
}

static int	tok_2(t_struct *data, char **tok, char **line_split, int i)
{
	i = tok_fd_out(data, tok, line_split, i);
	while (data->i_redir != -1)
	{
		free(tok[2]);
		i = tok_fd_out(data, tok, line_split, i);
	}
	return (i);
}

char	**tokenisation(char *line, char **tok, t_struct *data)
{
	char	**line_split;
	int		i;

	line_split = tok_initialization(data, line);
	i = 0;
	i = tok_0(data, tok, line_split, i);
	if (i == len_split(line_split) || i < 0 || !tok[0])
		return (ft_free_split(line_split));
	i = tok_1(tok, line_split, i, line);
	if (i < 0)
		return (ft_free_split(line_split));
	i = tok_2(data, tok, line_split, i);
	tok[1] = parsing(tok[1], data);
	tok[3] = 0;
	data->type = check_type(tok, data);
	ft_free_split(line_split);
	return (tok);
}
