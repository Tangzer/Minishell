/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:19:00 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:19:05 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	unset_env(t_struct *data, char *cmd)
{
	int		i;
	char	**full_cmd;

	i = 1;
	full_cmd = ft_split(cmd, ' ');
	while (full_cmd[i])
	{
		data = unset_global(data, full_cmd[i]);
		i++;
	}
	ft_free_split(full_cmd);
}

t_struct	*unset_global(t_struct *data, char *unset)
{
	int	i;

	i = 0;
	while (data->envp[i])
	{
		if (!ft_strncmp(data->envp[i], unset, ft_strlen(unset)))
		{
			while (i + 1 < len_split(data->envp) - 1)
			{
				free(data->envp[i]);
				data->envp[i] = 0x0;
				data->envp[i] = ft_strdup(data->envp[i + 1]);
				i++;
			}
			free(data->envp[i]);
			data->envp[i] = 0x0;
			return (data);
		}
		i++;
	}
	return (data);
}
