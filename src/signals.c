/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 17:14:22 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 17:14:24 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	process_ended(int sig)
{
	if (access(HERE_DOC, X_OK) == 0)
	{
		unlink(HERE_DOC);
	}
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	g_error_code = SIGNAL;
	(void)sig;
}

void	restore_prompt(int sig)
{
	rl_on_new_line();
	rl_replace_line("", 0);
	write(1, "\n", 1);
	show_ghost();
	rl_redisplay();
	g_error_code = SIGNAL;
	(void)sig;
}

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, process_ended);
		signal(SIGQUIT, process_ended);
		signal(SIGPIPE, process_ended);
	}
}
