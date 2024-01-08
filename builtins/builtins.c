/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:05:26 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 17:23:27 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	choose_builtin(t_data *data, t_cmd *cmd, int is_parent)
{
	int	builtin;

	if (!cmd->comand[0])
		return ;
	builtin = is_builtin(cmd);
	if (builtin)
		prep_builtin(cmd, is_parent);
	if (!ft_strncmp(cmd->comand[0], "env", 4))
		print_env(&data->env, cmd);
	else if (!ft_strncmp(cmd->comand[0], "pwd", 4))
		do_pwd(&data->env, cmd);
	else if (!ft_strncmp(cmd->comand[0], "echo", 5))
		do_echo(cmd);
	else if (!ft_strncmp(cmd->comand[0], "export", 7))
		do_export(data->env, cmd, data);
	else if (!ft_strncmp(cmd->comand[0], "unset", 6))
		do_unset(cmd, &data->env);
	else if (!ft_strncmp(cmd->comand[0], "cd", 3))
		do_cd(data->env, cmd);
	else if (!ft_strncmp(cmd->comand[0], "exit", 5))
		do_exit(cmd);
	else
		do_execve(data, cmd);
	help_builtin(is_parent, cmd->fd_in, cmd->fd_out, builtin);
}

void	help_builtin(int is_parent, int fd_in, int fd_out, int builtin)
{
	if (!builtin)
		return ;
	if (!is_parent)
	{
		close(0);
		close(1);
		exit(set_exit_code(0, 0));
	}
	else
	{
		if (fd_in > 2)
			close(fd_in);
		if (fd_out > 2)
			close(fd_out);
	}
}

int	is_builtin(t_cmd *cmd)
{
	if (!cmd->comand[0])
		return (0);
	if (!ft_strncmp(cmd->comand[0], "env", 4))
		return (1);
	else if (!ft_strncmp(cmd->comand[0], "pwd", 4))
		return (1);
	else if (!ft_strncmp(cmd->comand[0], "echo", 5))
		return (1);
	else if (!ft_strncmp(cmd->comand[0], "export", 7))
		return (1);
	else if (!ft_strncmp(cmd->comand[0], "unset", 6))
		return (1);
	else if (!ft_strncmp(cmd->comand[0], "cd", 3))
		return (1);
	else if (!ft_strncmp(cmd->comand[0], "exit", 5))
		return (1);
	return (0);
}

void	prep_builtin(t_cmd *cmd, int is_parent)
{
	if (is_parent)
		return ;
	cmd->fd_in = 0;
	cmd->fd_in = 1;
}
