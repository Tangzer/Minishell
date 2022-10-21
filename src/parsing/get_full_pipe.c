/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_full_pipe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/19 18:06:00 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 18:06:05 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

char	*get_full_pipe(char *line)
{
	char	*tmp;
	char	*tmp2;

	if (!line)
		return (NULL);
	tmp = get_next_line(0, MSG_PIPE);
	tmp2 = ft_strjoin(line, " ");
	free(line);
	while (!ft_strcmp(tmp, "\n"))
		tmp = get_next_line(0, MSG_PIPE);
	if (tmp2 && tmp)
	{
		line = ft_strjoin(tmp2, tmp);
		line[ft_strlen(line) - 1] = '\0';
		free(tmp);
		free(tmp2);
		add_history(line);
	}
	else
		return (NULL);
	if (line && is_metachar(line[ft_strlen(line) - 1]))
		line = get_full_pipe(line);
	return (line);
}
