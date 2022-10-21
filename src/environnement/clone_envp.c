/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clone_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/05 18:38:59 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/05 18:39:00 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	init_pwd_user(t_struct *data)
{
	char	*pwd_tmp;
	char	*tmp;
	int		i;

	pwd_tmp = NULL;
	pwd_tmp = getcwd(pwd_tmp, 200);
	protect_malloc(pwd_tmp);
	data->pwd = malloc(sizeof(char *) * 3 + 1);
	protect_malloc(data->pwd);
	data->pwd[0] = ft_strdup(pwd_tmp);
	protect_malloc(data->pwd[0]);
	data->pwd[1] = ft_strdup(pwd_tmp);
	protect_malloc(data->pwd[1]);
	data->pwd[2] = 0;
	tmp = var_exist(data, "USER");
	i = ft_strqstr(tmp, "USER=") + 1;
	data->user = ft_strdup (tmp + i);
	protect_malloc(data->user);
	free(pwd_tmp);
}

static void	call_warning(int new_lvl)
{
	char	*tmp;
	char	*msg;

	tmp = ft_strjoin("minishell: warning: shell level (", ft_itoa(new_lvl));
	msg = ft_strjoin(tmp, ") too high, resseting to 1\n");
	printf("%s", msg);
	free(tmp);
	free(msg);
}

t_struct	*update_lvl(t_struct *data, char *lvl)
{
	char	*tmp;
	int		new_lvl;

	lvl = ft_strchr(lvl, 61);
	if (is_numeric(lvl + 1))
	{
		new_lvl = ft_atoi(lvl + 1) + 1;
		if (new_lvl > 1000)
		{
			call_warning(new_lvl);
			new_lvl = 1;
		}
		tmp = ft_itoa(new_lvl);
		lvl = ft_strjoin("SHLVL=", tmp);
		if (new_lvl == 1000)
			data = export_global(data, "SHLVL=");
		else
			data = export_global(data, lvl);
		free(lvl);
		free(tmp);
	}
	else
		data = export_global(data, "SHLVL=1");
	return (data);
}

t_struct	*clone_env(char **env, t_struct *data)
{
	int		i;
	char	*lvl;

	data->envp = malloc(sizeof(char *) * len_split(env) + 1);
	protect_malloc(data->envp);
	i = 0;
	while (env[i])
	{
		data->envp[i] = malloc(sizeof(char) * ft_strlen(env[i]) + 1);
		protect_malloc(data->envp[i]);
		data->envp[i] = ft_strlcpy(data->envp[i], env[i],
				ft_strlen(env[i]) + 1);
		i++;
	}
	data->envp[i] = 0;
	lvl = var_exist(data, "SHLVL");
	if (lvl)
		data = update_lvl(data, lvl);
	else
		data = export_global(data, "SHLVL=1");
	init_pwd_user(data);
	return (data);
}
