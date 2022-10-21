/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 14:49:30 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/30 13:38:48 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	run_first(t_struct *data, char **tok, int *pipe_fd)
{
	if (ft_atoi(tok[2]) == 1)
		call_exec(data, tok, ft_atoi(tok[0]), pipe_fd[1]);
	else
		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
	close(pipe_fd[1]);
}

static void	run_last(t_struct *data, char **tok, int *pipe_fd)
{
	if (ft_atoi(tok[0]) == 0)
		call_exec(data, tok, pipe_fd[0], ft_atoi(tok[2]));
	else
		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
}

static void	run_multi_pipe(t_struct *data, char **tok, int *pipe_fd1)
{
	int		pipe_fd2[2];

	data->check = pipe(pipe_fd2);
	if (data->check < 0)
	{
		error_perror();
	}
	if (ft_atoi(tok[0]) == 0 && ft_atoi(tok[2]) == 1)
		call_exec(data, tok, pipe_fd1[0], pipe_fd2[1]);
	else if (ft_atoi(tok[0]) == 0 && ft_atoi(tok[2]) != 1)
		call_exec(data, tok, pipe_fd1[0], ft_atoi(tok[2]));
	else if (ft_atoi(tok[0]) != 0 && ft_atoi(tok[2]) == 1)
		call_exec(data, tok, ft_atoi(tok[0]), pipe_fd2[1]);
	else
		call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
	close(pipe_fd2[1]);
	pipe_fd1[0] = dup2(pipe_fd2[0], pipe_fd1[0]);
	pipe_fd1[1] = dup2(pipe_fd2[1], pipe_fd1[1]);
	close(pipe_fd2[0]);
	close(pipe_fd2[1]);
}

void	pipe_exec(t_struct *data, char **tok, char *line)
{
	char	**split_pipe;
	int		len;
	int		i;
	int		pipe_fd[2];

	split_pipe = ft_split_pipe(line, '|');
	len = len_split(split_pipe);
	i = 0;
	tok = tokenisation(split_pipe[i], tok, data);
	data->check = pipe(pipe_fd);
	if (data->check < 0)
		error_perror();
	run_first(data, tok, pipe_fd);
	ft_clear_split(tok);
	i++;
	while (i < len - 2)
	{
		tok = tokenisation(split_pipe[i], tok, data);
		run_multi_pipe(data, tok, pipe_fd);
		ft_clear_split(tok);
		i++;
	}
	tok = tokenisation(split_pipe[i], tok, data);
	ft_free_split(split_pipe);
	run_last(data, tok, pipe_fd);
}
