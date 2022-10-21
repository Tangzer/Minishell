/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dollar.c                                             :+:      :+:    :+: */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 13:32:31 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*replace_error_code(t_struct *data, char *line, int i)
{
	char	*tmp;
	char	*dst;
	int		y;

	data->tmp_1 = str_dup_parts(line, i - 1, 0);
	i++;
	data->tmp_2 = ft_itoa(g_error_code);
	y = i + 1;
	while (line[i])
		i++;
	data->tmp_3 = str_dup_parts(line, i, y);
	tmp = ft_strjoin(data->tmp_1, data->tmp_2);
	dst = ft_strjoin(tmp, data->tmp_3);
	free(tmp);
	free(line);
	return (dst);
}

static char	*join_and_replace(t_struct *data, char *tmp1, char *rpl, char *tmp3)
{
	char	*dst;
	char	*tmp;
	char	*tmp_dollar;
	int		i;

	tmp = NULL;
	tmp_dollar = var_exist(data, rpl);
	if (tmp_dollar)
	{
		i = 0;
		while (tmp_dollar[i] && tmp_dollar[i] != '=')
			i++;
		i++;
		tmp_dollar = str_dup_parts(tmp_dollar, ft_strlen(tmp_dollar), i);
		tmp = ft_strjoin(tmp1, tmp_dollar);
		dst = ft_strjoin(tmp, tmp3);
	}
	else
		dst = ft_strjoin(tmp1, tmp3);
	free(tmp_dollar);
	if (tmp != NULL)
		free(tmp);
	return (dst);
}

static char	*replace_or_erase(char *line, t_struct *data)
{
	char	*tmp;

	tmp = NULL;
	tmp = var_exist(data, data->tmp_2);
	if (tmp)
		line = join_and_replace(data, data->tmp_1, data->tmp_2, data->tmp_3);
	else
		line = ft_strjoin(data->tmp_1, data->tmp_3);
	return (line);
}

char	*replace_dollar(t_struct *data, char *line, int i)
{
	int		y;
	char	*tmp;

	data->tmp_1 = str_dup_parts(line, i - 1, 0);
	i++;
	y = i;
	i = update_i(line, i);
	data->tmp_2 = str_dup_parts(line, i - 1, y);
	y = i;
	while (line[i])
		i++;
	data->tmp_3 = str_dup_parts(line, i, y);
	tmp = replace_or_erase(line, data);
	free(line);
	return (tmp);
}

char	*parsing_dollar(t_struct *data, char *line_to_pars, int i)
{
	if (is_error_code(line_to_pars, i))
		line_to_pars = replace_error_code(data, line_to_pars, i);
	if (line_to_pars[i] == '$')
		line_to_pars = replace_dollar(data, line_to_pars, i);
	ft_free_tmp(data);
	return (line_to_pars);
}
