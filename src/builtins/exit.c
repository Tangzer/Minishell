/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pamartin <pamartin@student.s19.be>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 14:43:18 by pamartin          #+#    #+#             */
/*   Updated: 2022/08/18 14:43:47 by pamartin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

static int	ft_norm(char *numbers)
{
	ft_error(msg("exit", numbers, MSG_NUM, 0), 2);
	free(numbers);
	exit(2);
}

static void	get_argument(char *line, int i, int j, char *numbers)
{
	int	space_count;

	space_count = 0;
	while (line[i])
	{
		if (!ft_isdigit(line[i]) && space_count == 0)
		{
			if (line[i] == ' ')
				space_count++;
			i++;
		}
		else if (line[i] && space_count > 0)
		{
			numbers[j] = line[i];
			j++;
			i++;
		}
	}
	numbers[j] = '\0';
}

static int	ft_argument_is_valid(char *numbers)
{
	int	i;

	i = 0;
	while (numbers[i])
	{
		if (ft_isdigit(numbers[i]))
			i++;
		else
			return (0);
	}
	return (1);
}

static int	ft_return_nbr(char *line)
{
	int		i;
	int		j;
	int		tmp;
	char	*numbers;

	i = 0;
	j = 0;
	numbers = malloc(sizeof(char) * ft_strlen(line) + 1);
	get_argument(line, i, j, numbers);
	if (ft_strlen(numbers) > 19
		|| ft_long_atoi(numbers) > 9223372036854775807
		|| !ft_argument_is_valid(numbers))
		return (ft_norm(numbers));
	tmp = ft_long_atoi(numbers);
	free(numbers);
	return (tmp);
}

int	exit_builtins(char *line)
{
	long	exit_value;

	exit_value = ft_return_nbr(line);
	if (exit_value >= LONG_MAX)
	{
		ft_error(msg("exit", (char *)exit_value, MSG_NUM, 0), 2);
		free(line);
		exit(2);
	}
	else
		printf("exit\n");
	free(line);
	exit(exit_value);
}
