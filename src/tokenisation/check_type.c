/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_type.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:35:50 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 18:35:52 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	export_type(char *line)
{
	int	type;

	if (!line)
		type = BU_EXPORT_EMPTY;
	else
		type = BU_EXPORT;
	return (type);
}

static int	check_binary(t_struct *data, char **tok, int type)
{
	if (type == BINARY)
	{
		if (!is_good_binary(data, tok[1]))
			type = BAD_BINARY;
	}
	return (type);
}

int	check_type(char **tok, t_struct *data)
{
	char	**full_cmd;
	int		type;

	run_signals(2);
	full_cmd = ft_split(tok[1], ' ');
	if (!ft_strcmp(full_cmd[0], ECHO))
		type = BU_ECHO;
	else if (!ft_strcmp(full_cmd[0], CD))
		type = BU_CD;
	else if (!ft_strcmp(full_cmd[0], PWD))
		type = BU_PWD;
	else if (!ft_strcmp(full_cmd[0], ENV))
		type = BU_ENV;
	else if (!ft_strcmp(full_cmd[0], EXPORT))
		type = export_type(full_cmd[1]);
	else if (!ft_strcmp(full_cmd[0], UNSET))
		type = BU_UNSET;
	else if (!ft_strcmp(full_cmd[0], EXIT))
		type = BU_EXIT;
	else
		type = BINARY;
	if (type == BINARY)
		type = check_binary(data, tok, type);
	ft_free_split(full_cmd);
	return (type);
}
