/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/12/30 17:04:51 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var_name(char *str, int *i)
{
	char	*name;
	int		len;

	len = 0;
	name = NULL;
	while (str[*i + len + 1])
	{
		if (str[*i + len + 1] == '"' || str[*i + len + 1] == '\'' \
			|| str[*i + len + 1] == ' ' \
			|| str[*i + len + 1] == '$' || str[*i + len + 1] == '\n')
			break ;
		len++;
	}
	if (len)
	{
		name = ft_substr(str, *i + 1, len);
		*i = *i + len + 1;
	}
	return (name);
}

char	*get_var_value(char *str, int *i, t_data sh)
{
	char	*value;
	t_env	*ev;

	ev = sh.env;
	if (str[*i + 1] != '?')
		value = get_env_value(str, i, ev);
	else
	{
		value = ft_itoa(set_exit_code(0, 0));
		*i = *i + 2;
	}
	return (value);
}

void	expand_loop(char *str, char *final, int *j, t_data sh)
{
	int		i;
	int		count_double;
	char	*var;

	i = 0;
	count_double = 0;
	var = NULL;
	while (str[i])
	{
		if (str[i] == '"')
			count_double++;
		if (str[i] == '\'' && !(count_double % 2))
			copy_quotes(str, &i, final, j);
		if (str[i] != '$' || ((str[i] == '$' && (str[i + 1] == ' ' || \
			str[i + 1] == '\0' || (str[i + 1] == '"' && count_double % 2)))))
			final[(*j)++] = str[i++];
		else if (str[i] == '$' && (str[i + 1] == '"' || str[i + 1] == '\''))
			i++;
		else
		{
			var = get_var_value(str, &i, sh);
			copy_var_value(final, j, var);
		}
	}
}

char	*expander(char *str, t_data sh)
{
	char	*final;
	int		j;

	final = malloc(2048);
	if (!final)
		return (NULL);
	j = 0;
	expand_loop(str, final, &j, sh);
	final[j] = 0;
	free(str);
	delete_quotes(final);
	return (final);
}

void	expand_comands(t_cmd **list, t_data sh)
{
	t_cmd	*aux;
	int		i;

	aux = *list;
	while (*list && aux)
	{
		i = 0;
		while (aux->comand[i])
		{
			aux->comand[i] = expander(aux->comand[i], sh);
			i++;
		}
		aux = aux->next;
	}
}
