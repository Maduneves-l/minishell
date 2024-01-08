/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 14:06:56 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 17:23:43 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_unset(t_cmd *cmd, t_env **env)
{
	int	i;

	i = 0;
	if (!cmd->comand[1])
		return ;
	while (cmd->comand[i])
	{
		unset_utils(cmd->comand[i], env);
		i++;
	}
	set_exit_code(0, 1);
}

void	do_echo(t_cmd *cmd)
{
	int	flag;
	int	j;

	j = 0;
	flag = 0;
	if (cmd->comand[1] && cmd->comand[1][0] && cmd->comand[1][0] == '-')
	{
		while (cmd->comand[1][++j] && cmd->comand[1][j] == 'n')
			flag = 1;
		if (cmd->comand[1][j] != 'n' && cmd->comand[1][j])
			flag = 0;
	}
	echo_util(cmd, flag);
	set_exit_code(0, 1);
}

void	print_env(t_env **stack, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = *stack;
	while (tmp)
	{
		if (tmp->content)
		{
			ft_putstr_fd(tmp->name, cmd->fd_out);
			ft_putstr_fd("=", cmd->fd_out);
			ft_putendl_fd(tmp->content, cmd->fd_out);
		}
		tmp = tmp->next;
	}
	set_exit_code(0, 1);
}

void	do_pwd(t_env **stack, t_cmd *cmd)
{
	t_env	*tmp;

	tmp = *stack;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, "PWD", 4))
			ft_putendl_fd(tmp->content, cmd->fd_out);
		tmp = tmp->next;
	}
	set_exit_code(0, 1);
}

void	do_export(t_env *env, t_cmd *cmd, t_data *data)
{
	int	i;

	i = 1;
	if (!cmd->comand[1])
		print_export(env, data, cmd);
	else
	{
		while (cmd->comand[i])
		{
			if (ft_isalpha(cmd->comand[i][0]) || cmd->comand[i][0] == '_')
			{
				if (check_repeat(cmd->comand[i], env))
					set_variable(env, cmd->comand[i]);
				else
					check_var(cmd->comand[i], env);
			}
			else
				error_export(cmd->comand[i]);
			i++;
		}
	}
}
