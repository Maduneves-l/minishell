/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/12/29 12:25:24 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	copy_var_value(char *s1, int *j, char *s2)
{
	int	i;

	i = 0;
	if (s2)
	{
		while (s2[i])
			s1[(*j)++] = s2[i++];
		free(s2);
	}
}

char	*get_env_value(char *str, int *i, t_env *ev)
{
	char	*name;
	char	*value;

	name = get_var_name(str, i);
	value = NULL;
	if (name)
	{
		while (ev)
		{
			if (!ft_strcmp(name, ev->name))
			{
				value = ft_strdup(ev->content);
				break ;
			}
			ev = ev->next;
		}
		free(name);
	}
	return (value);
}
