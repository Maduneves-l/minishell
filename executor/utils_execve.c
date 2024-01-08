/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_execve.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/27 11:03:47 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 17:34:51 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*to_path(char *cmd, char **envp)
{
	int		i;
	char	*paths;
	char	**path;

	i = 0;
	while (ft_strncmp(envp[i], "PATH=", 5))
		i++;
	paths = ft_substr(envp[i], 5, ft_strlen(envp[i]));
	path = ft_split(paths, ':');
	free(paths);
	if (!path || !*path)
		return (NULL);
	return (path_to_cmd(cmd, path));
}

char	*path_to_cmd(char *cmd, char **path)
{
	int		i;
	char	*tmp;
	char	*final;

	i = 0;
	while (path[i])
	{
		tmp = ft_strjoin(path[i], "/");
		final = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(final, F_OK & X_OK) != -1)
		{
			free_split(path);
			return (final);
		}
		free(final);
		i++;
	}
	free_split(path);
	return (cmd);
}

void	execute_cmd(char **cmd, char **envp)
{
	char	*path;
	int		flag;
	int		i;

	i = 0;
	flag = 0;
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
			flag = 1;
		i++;
	}
	if (flag == 1)
		path = to_path(cmd[0], envp);
	if (execve(path, cmd, envp) == -1 || flag == 0)
	{
		ft_putstr_fd(cmd[0], 2);
		ft_putendl_fd(" :command not found", 2);
		free_split(envp);
		free(path);
		exit (set_exit_code(127, 1));
	}
	free(path);
}

char	**env_to_matrix(t_env *env)
{
	char	**matriz;
	t_env	*tmp;
	int		i;
	char	*name;
	char	*content;

	tmp = env;
	matriz = (char **)malloc((ev_lstsize(env) + 1) * sizeof(char *));
	i = 0;
	while (tmp)
	{
		name = ft_strjoin(tmp->name, "=");
		content = ft_strjoin(name, tmp->content);
		free(name);
		matriz[i] = ft_strdup(content);
		free(content);
		i++;
		tmp = tmp->next;
	}
	matriz[i] = NULL;
	return (matriz);
}
