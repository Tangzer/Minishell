/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: algaspar <algaspar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/18 13:32:28 by pamartin          #+#    #+#             */
/*   Updated: 2022/09/27 16:59:16 by algaspar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	show_ghost(void)
{
	printf(G " /▔▔▔▔▔▔▔▔\\  ╭━━━━╮\n" R);
	printf(G "| ╭--╮╭--╮ | |BOO…|\n" R);
	printf(G "| |╭-╯╰-╮| | ╰━┳━━╯\n" R);
	printf(G "| ╰╯ ╭╮ ╰╯ |━━━╯ \n" R);
	printf(G "|    ╰╯    | \n" R);
	printf(G "|/\\_/\\/\\_/\\| \n" R);
}

static char	*prompt(void)
{
	char	*str;

	run_signals(1);
	show_ghost();
	str = readline("MINISHELL~> ");
	if (!str)
		ft_error_exit(msg(NULL, NULL, "exit", 1), 1);
	add_history(str);
	return (str);
}

static void	free_that_shit(char *line, char **tok)
{
	free(line);
	ft_free_split(tok);
}

int	main(int argc, char **argv, char **envp)
{
	t_struct	*data;
	char		*line;
	char		**tok;

	data = initializer(envp, argc, argv);
	while (!0)
	{
		tok = ft_calloc(sizeof(char *), 4);
		protect_malloc(tok);
		line = prompt();
		if (syntax_errors(line))
		{
			free_that_shit(line, tok);
			continue ;
		}
		line = preparsing(line);
		line = remove_multi_space(line);
		if (is_metachar(line[ft_strlen(line) - 1]))
			line = get_full_pipe(line);
		if (line)
		{
			run_program(data, tok, line);
			free_that_shit(line, tok);
		}
	}
}
