/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:11:34 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:11:36 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int		bad_indentifier(char *export)
{
	int	end;
	int	i;

	i = 1;
	end = ft_strfchr(export, '=');
	while (export[i] && i < end)
	{
		if(!ft_isalnum((int)export[i]) && export[i] != 95)
			return (1);
		i++;
	}
	return(0);
}

void	export_env(t_struct *data, char *cmd)
{
	int		i;
	char	**full_cmd;

	i = 1;
	full_cmd = ft_split(cmd, ' ');
	while (full_cmd[i])
	{
		data = export_global(data, full_cmd[i]);
		i++;
	}
	ft_free_split(full_cmd);
}

char	**add_var(char **matrix, int len_matrix, int len_nline, char *n_line)
{
	char	**new_matrix;
	int		i;

	if (len_matrix == 0)
		len_matrix++;
	new_matrix = malloc(sizeof(char *) * (len_matrix + 1));
	protect_malloc(new_matrix);
	i = 0;
	while (matrix[i] && i <= len_matrix)
	{
		new_matrix[i] = malloc(sizeof(char) * ft_strlen(matrix[i]) + 1);
		protect_malloc(new_matrix[i]);
		ft_strcpy(new_matrix[i], matrix[i]);
		i++;
	}
	new_matrix[i] = malloc(sizeof(char) * len_nline + 1);
	protect_malloc(new_matrix[i]);
	ft_strcpy(new_matrix[i], n_line);
	new_matrix[i + 1] = 0;
	ft_free_split(matrix);
	return (new_matrix);
}

t_struct	*export_global(t_struct *data, char *export)
{
	int	i;

	i = 0;
	while (data->envp[i] && data->pipe == 0)
	{
		if (is_env_var(data, export, i))
		{
			if (ft_strncmp(data->envp[i], export, ft_strlen(data->envp[i])))
			{
				free(data->envp[i]);
				data->envp[i] = malloc(sizeof(char) * ft_strlen(export) + 1);
				protect_malloc(data->envp[i]);
				ft_strcpy(data->envp[i], export);
				return (data);
			}
		}
		i++;
	}
	if (ft_strfchr(export, '=') < 1 || (!ft_isalpha((int)export[0]) && export[0] != 95) || bad_indentifier(export))
		ft_error(msg("export", export, "not a valid identifier", 0), 1);
	if (ft_strfchr(export, '=') >= 1 && data->pipe == 0)
		data->envp = add_var(data->envp, len_split(data->envp),
				ft_strlen(export), export);
	return (data);
}
