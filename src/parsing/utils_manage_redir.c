/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_manage_redir.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 17:41:45 by pamartin          #+#    #+#             */
/*   Updated: 2022/10/03 17:41:51 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	**check_dless(char **line_split, int i)
{
	while (line_split[i])
	{
		if (!ft_strcmp(line_split[i], DLESS))
		{
			free(line_split[i + 1]);
			line_split[i + 1] = ft_strdup("here_doc");
			i++;
		}
		i++;
	}
	return (line_split);
}

int	nb_of_redir(char **line_split, int i)
{
	int	nb;

	nb = 0;
	while (line_split[i])
	{
		if (is_less_redirection(line_split, i))
			nb++;
		i++;
	}
	return (nb);
}

void	erase_line(char **line_split, int i)
{
	free(line_split[i]);
	line_split[i] = ft_strdup(" ");
}
