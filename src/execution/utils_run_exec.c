/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_run_exec.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:59:44 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/30 13:39:43 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	run_bad_binary(t_struct *data, char *cmd)
{
	char	**cmd_arg;

	cmd_arg = ft_split_pipe(cmd, ' ');
	if (!cmd_arg)
		ft_error(msg(NULL, NULL, "error malloc", 1), MALLOC);
	else if (!cmd_arg[0])
		ft_error(msg(cmd, NULL, "Command not found", 0), CMD_ERROR);
	else if (!var_exist(data, "PATH"))
		ft_error(msg(cmd_arg[0], NULL, MSG_NO_SUCH_FILE, 0), CMD_ERROR);
	else if (!ft_strncmp(cmd, "./", 2))
		ft_error(msg(cmd_arg[0] + 2, NULL, MSG_NO_SUCH_FILE, 0), CMD_ERROR);
	else if (!ft_strncmp(cmd, "/", 1))
		ft_error(msg(cmd_arg[0], NULL, MSG_NO_SUCH_FILE, 0), CMD_ERROR);
	else
		ft_error(msg(cmd_arg[0], NULL, "Command not found", 0), CMD_ERROR);
	ft_free_split(cmd_arg);
}

void	run_exec(t_struct *data, char **tok)
{
	if (data->type == BINARY)
		execute(data, tok[1]);
	else if (data->type == BU_ECHO)
		echo(tok);
	else if (data->type == BU_PWD)
		pwd_builtin(data);
	else if (data->type == BU_ENV)
		env_builtin(data);
	else if (data->type == BU_EXPORT_EMPTY)
		export_empty(data);
	else
		exit(EXIT_SUCCESS);
}

void	run_without_pipe(t_struct *data, char **tok)
{
	if (data->type == BU_EXIT)
		exit_builtins(tok[1]);
	else if (data->type == BU_UNSET)
		unset_env(data, tok[1]);
}

void	run_child(t_struct *data, char **tok, int fdin, int fdout)
{
	data->check = dup2(fdin, 0);
	protect_dup(data->check);
	data->check = dup2(fdout, 1);
	protect_dup(data->check);
	close_fd(fdin, fdout);
	run_exec(data, tok);
}

void	protect_dup(int check)
{
	if (check == -1)
	{
		ft_error_exit(msg(NULL, NULL, "", 1), errno);
	}
}
