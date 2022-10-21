/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initializer.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/13 23:29:57 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/13 23:30:01 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

t_struct	*initializer(char **envp, int argc, char **argv)
{
	t_struct	*data;

	if (!envp[0])
		ft_error_exit((msg(NULL, NULL, MSG_NO_ENV, 1)), 1);
	run_signals(1);
	if (argc != 1)
		ft_error_exit((msg(NULL, NULL, "Number of arguments != 1", 1)), ERROR);
	if (ft_strcmp(argv[0], "./minishell"))
		ft_error_exit((msg(NULL, NULL, "Bad program name", 1)), ERROR);
	welcome();
	g_error_code = 0;
	data = malloc(sizeof(t_struct));
	protect_malloc(data);
	data = clone_env(envp, data);
	data->i_redir = 0;
	data->tmp_1 = NULL;
	data->tmp_2 = NULL;
	data->tmp_3 = NULL;
	return (data);
}

void	ft_free_tmp(t_struct *data)
{
	if (data->tmp_1)
		free(data->tmp_1);
	if (data->tmp_2)
		free(data->tmp_2);
	if (data->tmp_3)
		free(data->tmp_3);
}
