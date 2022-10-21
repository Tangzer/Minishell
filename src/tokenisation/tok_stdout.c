/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tok_stdout.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 20:38:42 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/28 20:38:44 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	tok_fd_out(t_struct *data, char **tok, char **line_split, int i)
{
	char	*tmp;

	if (data->i_redir != -1)
		i = data->i_redir;
	if (line_split[i] && !ft_strcmp(line_split[i], GREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, GREAT);
	else if (line_split[i] && !ft_strcmp(line_split[i], DGREAT))
		tmp = get_fd(line_split[i + 1], REDIR_STDOUT, DGREAT);
	else
		tmp = get_fd(NULL, REDIR_STDOUT, NULL);
	if (tmp)
		tok[2] = ft_strdup(tmp);
	free(tmp);
	if (i < len_split(line_split) - 3)
		data->i_redir = i + 2;
	else
		data->i_redir = -1;
	return (i);
}
