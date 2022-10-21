/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_tokenisation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 12:51:00 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/26 18:16:45 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

int	ft_strcmp(char *s1, char *s2)
{
	int	len1;
	int	len2;
	int	i;

	i = 0;
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	if (len1 != len2)
		return (1);
	while (s1[i])
	{
		if (s1[i] != s2[i])
			return (1);
		i++;
	}
	return (0);
}

static int	manage_fdin(char *file)
{
	int	fd;

	fd = 0;
	if (file)
		fd = open(file, O_RDONLY);
	return (fd);
}

char	*get_fd(char *file, int type, char *token)
{
	int		fd;
	char	*fd_tok;

	if (type == REDIR_STDIN)
	{
		fd = manage_fdin(file);
		if (fd == -1)
		{
			ft_error(msg("", file, "No such file or directory", 0), 1);
			return (NULL);
		}
	}
	else
	{
		if (file && !ft_strcmp(token, GREAT))
			fd = open(file, O_CREAT | O_TRUNC | O_RDWR, 0644);
		else if (file && !ft_strcmp(token, DGREAT))
			fd = open(file, O_CREAT | O_APPEND | O_RDWR, 0644);
		else
			fd = 1;
	}
	if (fd < 0)
		return (NULL);
	fd_tok = ft_itoa(fd);
	return (fd_tok);
}

int	is_pipe(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == 34)
		{
			i++;
			while (line[i] != 34)
				i++;
		}
		if (line[i] == 39)
		{
			i++;
			while (line[i] != 39)
				i++;
		}
		if (line[i] == '|')
			return (1);
		i++;
	}
	return (0);
}

void	protect(void)
{
	perror("minishell: ");
	exit(EXIT_FAILURE);
}
