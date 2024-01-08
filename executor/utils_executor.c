/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_executor.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/05 12:53:38 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 17:32:50 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	error(char *s)
{
	perror(s);
	exit(EXIT_FAILURE);
}

void	do_execve(t_data *data, t_cmd *cmd)
{
	char	**our_env;

	our_env = env_to_matrix(data->env);
	execute_cmd(cmd->comand, our_env);
}

void	ft_wait(t_data sh)
{
	int		buffer;
	int		i;
	t_cmd	*tmp;

	i = -1;
	tmp = sh.cmds;
	while (tmp)
	{
		if (tmp->pid != -1)
			waitpid(tmp->pid, &buffer, 0);
		tmp = tmp->next;
	}
	if (WIFSIGNALED(buffer))
		set_exit_code(128 + WTERMSIG(buffer), 1);
	else if (WIFEXITED(buffer))
		set_exit_code(WEXITSTATUS(buffer), 1);
}
