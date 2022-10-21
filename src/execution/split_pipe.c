/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/15 13:59:44 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/26 18:09:36 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	manage_special_char(char *str, int i)
{
	if (str[i] == 34 && str[i + 1])
	{
		i++;
		while (str[i] != 34 && str[i + 1])
			i++;
	}
	if (str[i] == 39 && str[i + 1])
	{
		i++;
		while (str[i] != 39 && str[i + 1])
			i++;
	}
	return (i);
}

static char	**ft_count_words(char *str, char c)
{
	int		count;
	int		i;
	char	**split;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] != c)
		{
			count++;
			while (str[i])
			{
				i = manage_special_char(str, i);
				if (str[i] != c)
					i++;
				if (str[i] == c)
					break ;
			}
		}
		else
			i++;
	}
	split = (char **)malloc(sizeof(char *) * (count + 1));
	return (split);
}

static int	ft_lenword(const char *str, char c, int i)
{
	int	y;
	int	z;

	y = i;
	while (str[i])
	{
		if (str[i] == 34 && str[i + 1])
		{
			i++;
			while (str[i] != 34 && str[i + 1])
				i++;
		}
		if (str[i] == 39 && str[i + 1])
		{
			i++;
			while (str[i] != 39 && str[i + 1])
				i++;
		}
		if (str[i] != c && str[i])
			i++;
		else
			break ;
	}
	z = i - y;
	return (z);
}

static int	ft_copy(char *dest, char *str, char c, int i)
{
	int	j;

	j = 0;
	while (str[i])
	{
		if (str[i] == 34 || str[i] == 39)
		{
			dest = cpy_dest(i, j, str, dest);
			j = increment_j(i, j, str);
			i = increment_i(i, str);
		}
		if (str[i] != c)
		{
			dest[j] = str[i];
			j++;
			i++;
		}
		else
			break ;
	}
	dest[j] = '\0';
	return (i);
}

char	**ft_split_pipe(char *s, char c)
{
	char	**split;
	int		words;
	int		i;

	if (!s)
		return (NULL);
	split = ft_count_words(s, c);
	if (!split)
		return (0);
	i = 0;
	words = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			split[words] = malloc(sizeof(char) * ft_lenword(s, c, i) + 1);
			if (!split[words])
				return (ft_free_split(split));
			i = ft_copy(split[words++], s, c, i);
		}
	}
	split[words] = 0;
	return (split);
}
