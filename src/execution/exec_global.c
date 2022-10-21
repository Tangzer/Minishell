/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_global.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 20:40:15 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/27 14:00:44 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	protected_execve(char *path, char **cmd_arg, char **envp)
{
	int	check;

	check = execve(path, cmd_arg, envp);
	if (check == -1)
	{
		ft_error(msg(cmd_arg[0], NULL, "Command not found", 0), 127);
		ft_free_split(cmd_arg);
		exit(CMD_ERROR);
	}
}

void	close_fd(int fdin, int fdout)
{
	if (fdout != 1)
		close(fdout);
	if (fdin != 0)
		close(fdin);
}

void	execute(t_struct *data, char *cmd)
{
	char	**paths;
	char	*path;
	char	**cmd_arg;

	cmd_arg = ft_split_pipe(cmd, ' ');
	if (!cmd_arg)
		ft_error(msg(NULL, NULL, "error malloc", 1), MALLOC);
	if (!ft_strncmp(cmd, "./", 2))
		protected_execve(cmd_arg[0], cmd_arg, data->envp);
	if (!ft_strncmp(cmd, "/", 1))
		protected_execve(cmd_arg[0], cmd_arg, data->envp);
	else
	{
		paths = path_list(data->envp);
		path = get_cmd_path(paths, cmd_arg[0]);
		protected_execve(path, cmd_arg, data->envp);
	}
}

void	call_exec(t_struct *data, char **tok, int fdin, int fdout)
{
	pid_t	child;

	g_error_code = 0;
	if (data->type == BU_CD)
		cd_builtin(data, tok);
	if (data->type == BAD_BINARY)
		run_bad_binary(data, tok[1]);
	if (data->type == BU_EXIT)
		exit_builtins(tok[1]);
	if (data->type == BU_EXPORT)
		export_env(data, tok[1]);
	child = fork();
	if (child == -1)
	{
		ft_error(msg(NULL, NULL, "", 1), errno);
		return ;
	}
	if (data->pipe == 0)
		run_without_pipe(data, tok);
	if (child == 0)
		run_child(data, tok, fdin, fdout);
	waitpid(child, NULL, 0);
	if (access(HERE_DOC, F_OK) == 0)
		unlink(HERE_DOC);
}

void	run_program(t_struct *data, char **tok, char *line)
{
	if (!is_pipe(line))
	{
		data->pipe = 0;
		tok = tokenisation(line, tok, data);
		if (tok)
			call_exec(data, tok, ft_atoi(tok[0]), ft_atoi(tok[2]));
	}
	else
	{
		data->pipe = 1;
		pipe_exec(data, tok, line);
	}
}
