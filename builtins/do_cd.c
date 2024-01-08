/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:05:26 by mneves-l          #+#    #+#             */
/*   Updated: 2023/12/29 12:08:39 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_cd(t_env *env, t_cmd *cmd)
{
	char	*dir;
	char	*pwd;

	dir = 0;
	if (matrixlen(cmd->comand) > 2)
	{
		ft_putendl_fd("cd: too many arguments", 2);
		set_exit_code(1, 1);
	}
	else 
		dir = get_path(env, cmd);
	if (dir && chdir(dir) == -1)
		print_cd_error(cmd->comand[1]);
	else if (dir)
	{
		pwd = getcwd(NULL, 0);
		update_dirs(pwd, env);
		free(pwd);
	}
	free(dir);
}

void	*get_path(t_env *env, t_cmd *cmd)
{
	char	*dir;

	if (matrixlen(cmd->comand) == 1 || (matrixlen(cmd->comand) == 2 \
		&& !ft_strcmp(cmd->comand[1], "~")))
		dir = get_env_content("HOME", env);
	else if (matrixlen(cmd->comand) == 2 && !ft_strcmp(cmd->comand[1], "-"))
	{
		dir = get_env_content("OLDPWD", env);
		ft_putendl_fd(dir, cmd->fd_out);
	}
	else
		dir = ft_strdup(cmd->comand[1]);
	return (dir);
}

void	update_dirs(char *newdir, t_env *env)
{
	char	*temp;

	temp = get_env_content("PWD", env);
	free(get_env_node("PWD", env)->content);
	get_env_node("PWD", env)->content = ft_strdup(newdir);
	free(get_env_node("OLDPWD", env)->content);
	get_env_node("OLDPWD", env)->content = ft_strdup(temp);
	free(temp);
	set_exit_code(0, 1);
}

char	*get_env_content(char *name, t_env *env)
{
	t_env	*aux;
	char	*content;

	aux = env;
	content = NULL;
	while (aux->next)
	{
		if (ft_strcmp(name, aux->name) == 0)
		{
			content = ft_strdup(aux->content);
			break ;
		}
		aux = aux->next;
	}
	return (content);
}

t_env	*get_env_node(char *name, t_env *env)
{
	t_env	*aux;

	aux = env;
	while (aux->next)
	{
		if (ft_strcmp(name, aux->name) == 0)
			break ;
		aux = aux->next;
	}
	return (aux);
}
