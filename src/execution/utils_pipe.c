/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:59:44 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/15 13:59:46 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static char	*copy_src_to_dst_double_quote(char *str, int i, char *dst, int j)
{
	dst[j] = str[i];
	j++;
	i++;
	while (str[i] != 34 && str[i])
	{
		dst[j] = str[i];
		j++;
		i++;
	}
	return (dst);
}

static char	*copy_src_to_dst_single_quote(char *str, int i, char *dst, int j)
{
	dst[j] = str[i];
	j++;
	i++;
	while (str[i] != 39 && str[i])
	{
		dst[j] = str[i];
		j++;
		i++;
	}
	return (dst);
}

char	*cpy_dest(int i, int j, char *str, char *dest)
{
	if (str[i] == 34)
	{
		dest = copy_src_to_dst_double_quote(str, i, dest, j);
	}
	if (str[i] == 39)
	{
		dest = copy_src_to_dst_single_quote(str, i, dest, j);
	}
	return (dest);
}

int	increment_j(int i, int j, char *str)
{
	if (str[i] == 34)
	{
		i++;
		j++;
		while (str[i] != 34 && str[i])
		{
			j++;
			i++;
		}
	}
	if (str[i] == 39)
	{
		i++;
		j++;
		while (str[i] != 39 && str[i])
		{
			j++;
			i++;
		}
	}
	return (j);
}

int	increment_i(int i, char *str)
{
	if (str[i] == 34)
	{
		i++;
		while (str[i] != 34 && str[i])
			i++;
	}
	if (str[i] == 39)
	{
		i++;
		while (str[i] != 39 && str[i])
			i++;
	}
	return (i);
}
