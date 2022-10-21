/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_envp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:38:40 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:38:44 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*var_exist(t_struct *data, char *variable)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(variable, "=");
	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], tmp, ft_strlen(tmp)))
		{
			free(tmp);
			return (data->envp[i]);
		}
		i++;
	}
	free(tmp);
	return (NULL);
}

int	is_numeric(char *value)
{
	int	i;

	i = 0;
	if (value[i] == '+' || value[i] == '-')
		i++;
	while (value[i])
	{
		if (!ft_isdigit((int)value[i]))
			return (0);
		i++;
	}
	return (1);
}

int	len_split(char **split)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	return (i + 1);
}

int	is_env_var(t_struct *data, char *export, int i)
{
	int	is_egual;

	is_egual = ft_strfchr(export, '=');
	if (is_egual < 1)
		return (0);
	if (!ft_strncmp(data->envp[i], export, ft_strfchr(export, '=')))
		return (1);
	return (0);
}
