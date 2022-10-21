/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_redirections.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 18:50:26 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 18:50:28 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	is_any_redirection(char **line_split, int i)
{
	if (!ft_strcmp(line_split[i], GREAT) || !ft_strcmp(line_split[i], DGREAT)
		|| !ft_strcmp(line_split[i], LESS)
		|| !ft_strcmp(line_split[i], DLESS))
		return (1);
	else
		return (0);
}

int	is_less_redirection(char **line_split, int i)
{
	if (!ft_strcmp(line_split[i], DLESS) || !ft_strcmp(line_split[i], LESS))
		return (1);
	else
		return (0);
}

int	there_is_a_less_redirection(char **line_split, int i)
{
	while (line_split[i])
	{
		if (!ft_strcmp(line_split[i], DLESS) || !ft_strcmp(line_split[i], LESS))
			return (1);
		i++;
	}
	return (0);
}

int	is_a_less_redir(char *line_split, int i)
{
	if (line_split[i] == '<'
		|| (line_split[i] == '<' && line_split[i + 1] == '<'))
		return (1);
	else
		return (0);
}
