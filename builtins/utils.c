/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/30 17:33:05 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 17:04:04 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	echo_util(t_cmd *cmd, int flag)
{
	int	j;

	j = 1;
	while (cmd->comand && cmd->comand[j])
	{
		if (flag == 1 && cmd->comand[2])
		{
			if (!ft_strncmp(cmd->comand[j], "-n", 2))
				j++;
			ft_putstr_fd(cmd->comand[j], cmd->fd_out);
			if (cmd->comand[j + 1])
				ft_putstr_fd(" ", cmd->fd_out);
		}
		else if (flag == 0)
		{
			ft_putstr_fd(cmd->comand[j], cmd->fd_out);
			if (cmd->comand[j + 1])
				ft_putstr_fd(" ", cmd->fd_out);
			else
				ft_putstr_fd("\n", cmd->fd_out);
		}
		j++;
	}
}

void	do_swap(t_env *env)
{
	char	*name;
	char	*content;

	name = env->name;
	content = env->content;
	env->name = env->next->name;
	env->content = env->next->content;
	env->next->name = name;
	env->next->content = content;
}

void	unset_utils(char *s, t_env **head)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = (*head);
	if (tmp && !ft_strcmp(tmp->name, s))
	{
		*head = tmp->next;
		help_unset(tmp->name, tmp->content, tmp);
		return ;
	}
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, s))
		{
			if (tmp->next)
				prev->next = tmp->next;
			else
				prev->next = NULL;
			help_unset(tmp->name, tmp->content, tmp);
			break ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}

void	help_unset(char *name, char *content, t_env *env)
{
	free(name);
	free(content);
	free(env);
}

void	print_cd_error(char *s)
{
	char	*temp;

	temp = ft_strjoin("cd: ", s);
	perror(temp);
	free(temp);
	set_exit_code(1, 1);
}
