/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:37 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:10:40 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_struct	*change_directory(t_struct *data, char *directory)
{
	int	check;

	update_pwd(data, 1);
	data = update_envp(data, "OLDPWD=");
	check = chdir(directory);
	if (check < 0)
		ft_error(msg("cd", directory, "No such file or directory", 0), 1);
	update_pwd(data, 0);
	data = update_envp(data, "PWD=");
	return (data);
}

char	*cd_tilde(t_struct *data, char **full_cmd)
{
	char	*tmp;
	char	*line;

	tmp = ft_strjoin("/Users/", data->user);
	line = NULL;
	if (!full_cmd[1] || !ft_strcmp(full_cmd[1], "~"))
		return (tmp);
	else
	{
		if (full_cmd[1])
		{
			line = ft_strjoin(tmp, full_cmd[1] + 1);
			free(tmp);
		}
	}
	return (line);
}

void	cd_solo(t_struct *data, char **tok, char **full_cmd)
{
	int		check;
	char	*tmp;

	check = access(full_cmd[1], F_OK);
	if (check == 0)
		data = change_directory(data, full_cmd[1]);
	else if (!full_cmd[1] || !ft_strncmp(full_cmd[1], "~", 1))
	{
		tmp = cd_tilde(data, full_cmd);
		data = change_directory(data, tmp);
		free(tmp);
	}
	else if (!ft_strcmp(full_cmd[1], "-"))
	{
		tmp = ft_strdup(data->pwd[1]);
		data = change_directory(data, tmp);
		free(tmp);
		ft_putstr_fd(data->pwd[0], ft_atoi(tok[2]));
		ft_putchar_fd('\n', ft_atoi(tok[2]));
	}
	else if (ft_strlen(full_cmd[1]) <= 255)
		ft_error(msg("cd", full_cmd[1], "No such file or directory", 0), 1);
	else
		ft_error(msg("cd", full_cmd[1], "File name too long", 0), 1);

}

void	cd_builtin(t_struct *data, char **tok)
{
	char	**full_cmd;

	full_cmd = ft_split(tok[1], ' ');
	if (data->pipe == 0)
		cd_solo(data, tok, full_cmd);
	else
	{
		if (!ft_strcmp(full_cmd[1], "-"))
		{
			ft_putstr_fd(data->pwd[1], ft_atoi(tok[2]));
			ft_putchar_fd('\n', ft_atoi(tok[2]));
		}
	}
	ft_free_split(full_cmd);
}
