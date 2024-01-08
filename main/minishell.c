/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/01/08 17:35:45 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	set_exit_code(int i, int flag)
{
	static int	code;

	if (flag)
		code = i;
	return (code);
}

void	init_data(t_data *sh, char **env)
{
	set_exit_code(0, 1);
	sh->env = NULL;
	get_env(env, &sh->env);
	sh->status = 1;
	sh->flag_pipe = 0;
}

int	handle_input(char *l)
{
	if (!l)
	{
		free(l);
		rl_on_new_line();
		ft_putendl_fd("exit", 1);
		return (0);
	}
	return (1);
}

void	parse_comands(char *line, t_data sh)
{
	char	**first_split;

	add_history(line);
	if (check_syntax(line, 0))
	{
		first_split = ft_split(line, 2);
		free(line);
		sh.cmds = parsing(first_split, sh);
		free_split(first_split);
		if (number_comands(sh.cmds) > 1)
			sh.flag_pipe = 1;
		executor(sh);
		free_comand(&sh.cmds);
		sh.flag_pipe = 0;
	}
	else
		free(line);
}

int	main(int ac, char **av, char **env)
{
	char	*line;
	t_data	sh;

	if (ac != 1)
		return (0);
	(void) av;
	init_data(&sh, env);
	while (1)
	{
		set_signals();
		line = readline("\e[1;36mminishell$ \e[0m");
		if (!handle_input(line))
			break ;
		else if (line[0])
			parse_comands(line, sh);
		else
			free(line);
	}
	free_env(&sh.env);
	unlink("heredoc");
	return (set_exit_code(0, 0));
}
