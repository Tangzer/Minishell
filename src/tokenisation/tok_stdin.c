/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_stdin.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:50:26 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 18:50:28 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*create_heredoc(char *delimiter)
{
	char	*line;
	char	*info;
	int		here_doc;
	int		fd;

	if (!delimiter)
		return (NULL);
	here_doc = open("here_doc", O_CREAT | O_TRUNC | O_RDWR, 0644);
	if (here_doc < 0)
		protect();
	line = get_next_line(0, MSG_HERE);
	while (line && (ft_strncmp(line, delimiter, ft_strlen(delimiter))
			|| ft_strlen(delimiter) + 1 != ft_strlen(line)))
	{
		write(here_doc, line, ft_strlen(line));
		line = get_next_line(0, MSG_HERE);
	}
	free(line);
	fd = open("here_doc", O_RDONLY);
	if (fd < 0)
		protect();
	info = ft_itoa(fd);
	return (info);
}

static char	*manage_info_stdin(char *info, char **line_split, int i)
{
	if (!ft_strcmp(line_split[i], LESS))
		info = get_fd(line_split[i + 1], REDIR_STDIN, NULL);
	else if (!ft_strcmp(line_split[i], DLESS))
	{
		info = create_heredoc(line_split[i + 1]);
		if (!line_split[i + 1])
			unlink(HERE_DOC);
	}
	else
		info = get_fd(NULL, REDIR_STDIN, NULL);
	return (info);
}

static int	manage_incre(char **line_split, t_struct *data, int i, int type)
{
	if (is_less_redirection(line_split, i))
		i += 2;
	else if (is_a_greater_redirection(line_split, i))
		i += 0;
	else
	{
		if (type == POST)
			i += 1;
	}
	if (type == PRE)
	{
		if (there_is_a_less_redirection(line_split, i) && i > 0)
			data->i_redir = i + 1;
		else
			data->i_redir = -1;
		if (data->i_redir != -1 && data->cmd < 0)
			data->cmd = i;
	}
	return (i);
}

void	redir_after_executable(char **line_split, t_struct *data, int i)
{
	char	*info;
	int		y;

	y = i + 1;
	while (line_split[y] && !is_a_greater_redirection(line_split, y))
	{
		info = manage_info_stdin(info, line_split, y);
		if (info)
			free(info);
		y = manage_incre(line_split, data, y, POST);
	}
	data->i_redir = -1;
}

int	tok_fd_in(t_struct *data, char **tok, char **line_split, int i)
{
	char	*info;
	int		i_manage;

	info = NULL;
	if (data->i_redir == 1)
		i = data->i_redir;
	else if (data->i_redir > 1)
		i = data->i_redir - 1;
	i_manage = i;
	i = manage_incre(line_split, data, i, PRE);
	if ((data->i_redir != -1 && !is_any_redirection(line_split, i))
		|| (there_is_a_less_redirection(line_split, i) && i == 0))
		redir_after_executable(line_split, data, i);
	info = manage_info_stdin(info, line_split, i_manage);
	if (!info)
		return (-1);
	tok[0] = ft_strdup(info);
	free(info);
	if (data->cmd == 0)
		return (data->cmd);
	return (i);
}
