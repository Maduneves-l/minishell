/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   comand_list_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/01/08 15:39:10 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_cmd	*new_comand(void)
{
	t_cmd	*cmd;

	cmd = malloc(sizeof(t_cmd));
	if (!cmd)
		return (NULL);
	cmd->pid = -1;
	cmd->redir[0] = 0;
	cmd->redir[1] = 1;
	cmd->fd_in = STDIN_FILENO;
	cmd->fd_out = STDOUT_FILENO;
	cmd->pip_fd[0] = -1;
	cmd->pip_fd[1] = -1;
	cmd->hd_error = 0;
	cmd->next = NULL;
	cmd->prev = NULL;
	return (cmd);
}

t_cmd	*last_comand(t_cmd *c)
{
	if (!c)
		return (0);
	while (c->next)
		c = c->next;
	return (c);
}

void	add_comand(t_cmd **lst, t_cmd *new)
{
	if (lst)
	{
		if (*lst)
		{
			new->prev = last_comand(*lst);
			last_comand(*lst)->next = new;
		}
		else
			*lst = new;
	}
}

int	number_comands(t_cmd *lst)
{
	int	i;

	i = 0;
	while (lst != NULL)
	{
		i++;
		lst = lst->next;
	}
	return (i);
}
