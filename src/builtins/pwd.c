/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:08:46 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/22 16:08:19 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	pwd_builtin(t_struct *data)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 200);
	if (!pwd)
		pwd = ft_strdup(data->pwd[0]);
	printf("%s\n", pwd);
	free(pwd);
	pwd = 0x0;
	exit(EXIT_SUCCESS);
}
