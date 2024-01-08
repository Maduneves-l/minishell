/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 11:50:42 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 18:39:25 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_var(char *cmd, t_env *env)
{
	char	*name;
	char	*content;
	int		size;
	int		len;

	if (ft_strchr(cmd, '=') == NULL)
		return ;
	size = g_size(cmd, '=');
	name = ft_substr(cmd, 0, size);
	len = ft_strlen(cmd);
	content = ft_substr(cmd, size + 1, len - size);
	while (env)
	{
		if (!ft_strcmp(env->name, name))
			env->content = content;
		env = env->next;
	}
	free(name);
}

int	check_repeat(char *cmd, t_env *env)
{
	t_env	*tmp;

	tmp = env;
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, cmd, ft_strlen(tmp->name)))
			return (0);
		tmp = tmp->next;
	}
	return (1);
}

void	set_variable(t_env *env, char *cmd)
{
	int		size;
	int		len;
	char	*name;

	if (ft_strchr(cmd, '=') == NULL)
	{
		check_name(cmd);
		ev_lstadd_back(&env, ev_lstnew(ft_strdup(cmd), NULL));
	}
	else
	{
		size = g_size(cmd, '=');
		name = ft_substr(name, 0, size);
		check_name(name);
		free(name);
		len = ft_strlen(cmd);
		ev_lstadd_back(&env, ev_lstnew(ft_substr(cmd, 0, size), \
			ft_substr(cmd, size + 1, len - size)));
	}
}

void	print_export(t_env *env, t_data *data, t_cmd *cmd)
{
	t_env	*tmp;

	(void) *data;
	tmp = env;
	if (data->status == 1)
	{
		data->status = 0;
		bubble_sort(env);
	}
	while (tmp)
	{
		ft_putstr_fd("declare -x: ", cmd->fd_out);
		if (tmp->content)
		{
			ft_putstr_fd(tmp->name, cmd->fd_out);
			ft_putstr_fd("=\"", cmd->fd_out);
			ft_putstr_fd(tmp->content, cmd->fd_out);
			ft_putendl_fd("\"", cmd->fd_out);
		}
		else
			ft_putendl_fd(tmp->name, cmd->fd_out);
		tmp = tmp->next;
	}
}

void	bubble_sort(t_env *env)
{
	int		size;
	int		i;
	t_env	*tmp;
	t_env	*head;

	i = 0;
	size = ev_lstsize(env);
	head = env;
	while (i < size)
	{
		tmp = head;
		while (tmp && tmp->next != NULL)
		{
			if (ft_strcmp(tmp->name, tmp->next->name) > 0)
				do_swap(tmp);
			tmp = tmp->next;
		}
		i++;
	}
}
