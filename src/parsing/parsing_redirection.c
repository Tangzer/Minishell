/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_redirection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 12:44:29 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/30 12:44:31 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static void	manage_special_case(char **line_split, int i, int len, int nb)
{
	if (nb == 1)
	{
		if (line_split[i + 2] || i > 1)
			erase_line(line_split, i + 1);
	}
	else
	{
		if (line_split[i + 2] || (!line_split[i + 2] && (len - nb) % 2 == 1))
			erase_line(line_split, i + 1);
	}
}

static char	*manage_badfiles(char **line_split, int i)
{
	char	*line;
	char	*tmp;

	if (!ft_strcmp(line_split[0], "cat"))
	{
		line = ft_strjoin(line_split[0], " ");
		tmp = ft_strjoin(line, line_split[i + 1]);
		free(line);
		return (tmp);
	}
	return (NULL);
}

void	manage_dless(char **line_split, int i, int len, int nb)
{
	erase_line(line_split, i);
	if (line_split[i + 1])
		manage_special_case(line_split, i, len, nb);
}

char	*manage_redir(char **line_split, int i, int len, int nb)
{
	char	*line;

	while (line_split[i])
	{
		if (!ft_strcmp(line_split[i], DLESS))
			manage_dless(line_split, i, len, nb);
		if (!ft_strcmp(line_split[i], LESS))
		{
			erase_line(line_split, i);
			if (line_split[i + 1])
			{
				if (access(line_split[i + 1], F_OK) == 0)
					manage_special_case(line_split, i, len, nb);
				else
				{
					line = manage_badfiles(line_split, i);
					if (line)
						return (line);
				}
			}
		}
		i++;
	}
	line = reverse_split(line_split, " ");
	return (line);
}

char	*parsing_redirstdin(char *line)
{
	char	**line_split;
	char	*new_line;
	int		i;
	int		nb;
	int		len;

	i = 0;
	line_split = ft_split_pipe(line, ' ');
	line_split = check_dless(line_split, i);
	nb = nb_of_redir(line_split, i);
	if (nb == 0)
	{
		ft_free_split(line_split);
		return (line);
	}
	len = len_split(line_split) - 2;
	if (!ft_strcmp(line_split[0], "cat") && line_split[1][0] == '-')
		len--;
	if (!ft_strcmp(line_split[0], "grep"))
		len--;
	new_line = manage_redir(line_split, i, len, nb);
	ft_free_split(line_split);
	return (new_line);
}
