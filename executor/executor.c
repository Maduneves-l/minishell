/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 10:55:55 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 17:29:50 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	executor(t_data sh)
{
	sh.cmds->n_cmds = number_comands(sh.cmds);
	sh.cmds->fd_in = sh.cmds->redir[0];
	sh.cmds->fd_out = sh.cmds->redir[1];
	if (sh.flag_pipe == 0 && is_builtin(sh.cmds) && sh.cmds->redir[0] != -1)
		choose_builtin(&sh, sh.cmds, 1);
	else if (sh.cmds->redir[0] != -1)
	{
		create_pipe(sh, sh.cmds, -1);
	}
}

void	create_pipe(t_data sh, t_cmd *cmd, int i)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (++i < cmd->n_cmds && tmp)
	{
		tmp->pid = -1;
		if (pipe(tmp->pip_fd) == 1)
			error("error:");
		tmp->pid = process_child(sh, tmp);
		tmp = tmp->next;
	}
	ft_wait(sh);
}

pid_t	process_child(t_data sh, t_cmd *cmd)
{
	pid_t	pid;

	child_signal();
	if (cmd->next)
		cmd->fd_out = cmd->pip_fd[1];
	if (cmd->prev)
		cmd->fd_in = cmd->prev->pip_fd[0];
	if (cmd->redir[0] > 2)
		cmd->fd_in = cmd->redir[0];
	if (cmd->redir[1] > 2)
		cmd->fd_out = cmd->redir[1];
	pid = fork();
	if (pid < 0)
		error("Error: ");
	if (pid == 0)
		child(sh, cmd);
	else
		help_process_child(cmd);
	return (pid);
}

void	help_process_child(t_cmd *cmd)
{
	if (cmd->redir[0] > 2)
		close(cmd->redir[0]);
	if (cmd->redir[1] > 2)
		close(cmd->redir[1]);
	close(cmd->pip_fd[1]);
	if (!cmd->next)
		close(cmd->pip_fd[0]);
	if (cmd->prev)
		close(cmd->prev->pip_fd[0]);
}

void	child(t_data sh, t_cmd *cmd)
{
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, STDIN_FILENO);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, STDOUT_FILENO);
	close(cmd->pip_fd[0]);
	close(cmd->pip_fd[1]);
	if (cmd->prev)
		close(cmd->prev->pip_fd[0]);
	if (cmd->redir[0] > 2)
		close(cmd->redir[0]);
	if (cmd->redir[1] > 2)
		close(cmd->redir[1]);
	choose_builtin(&sh, cmd, 0);
}
