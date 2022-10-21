/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/19 15:31:29 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_error_exit(char *message, int code)
{
	g_error_code = code;
	write(2, message, ft_strlen(message));
	write(2, "\n", 1);
	free(message);
	exit(g_error_code);
}

void	error_perror(void)
{
	perror("minishell");
	g_error_code = errno;
	exit(g_error_code);
}

void	ft_error(char *message, int code)
{
	g_error_code = code;
	if (message == NULL)
		return ;
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
	free(message);
}

void	ft_error_no_ptr(char *message, int code)
{
	g_error_code = code;
	if (message == NULL)
		return ;
	ft_putstr_fd(message, 2);
	ft_putchar_fd('\n', 2);
}
