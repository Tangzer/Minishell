/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_builtins.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:10:37 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/22 15:59:41 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	update_pwd(t_struct *data, int status)
{
	char	*update_pwd;

	update_pwd = NULL;
	update_pwd = getcwd(update_pwd, 200);
	if (update_pwd)
	{
		free(data->pwd[status]);
		data->pwd[status] = ft_strdup(update_pwd);
		free(update_pwd);
	}
}

t_struct	*update_var(t_struct *data, char *export, int i)
{
	if (ft_strncmp(data->envp[i], export, ft_strlen(export))
		|| ft_strlen(export) < ft_strlen(data->envp[i]))
	{
		free(data->envp[i]);
		data->envp[i] = malloc(sizeof(char) * ft_strlen(export) + 1);
		protect_malloc(data->envp[i]);
		ft_strcpy(data->envp[i], export);
	}
	return (data);
}

t_struct	*update_envp(t_struct *data, char *type)
{
	int		i;
	char	*export;
	char	*update_pwd;

	update_pwd = NULL;
	update_pwd = getcwd(update_pwd, 200);
	if (update_pwd)
	{
		export = ft_strjoin(type, update_pwd);
		i = 0;
		while (data->envp[i])
		{
			if (is_env_var(data, export, i))
				data = update_var(data, export, i);
			i++;
		}
		free(update_pwd);
		free(export);
	}
	return (data);
}

int	find_env_path(t_struct *data)
{
	char	*path;

	path = var_exist(data, "PATH");
	if (!path)
		return (0);
	if (ft_strnstr(path, "/usr/bin", ft_strlen(path)))
		return (1);
	return (0);
}
