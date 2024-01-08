/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/12/29 12:12:21 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	skip_quotes(char *line, int *i, char c)
{
	(*i)++;
	while (line[*i] && line[*i] != c)
		(*i)++;
	if (line[*i] == c)
		(*i)++;
}

void	delete_char(char *line, int i)
{
	while (line[i + 1])
	{
		line[i] = line[i + 1];
		i++;
	}
	line[i] = 0;
}

void	delete_quotes(char *line)
{
	char	c;
	int		i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'' )
		{
			c = line[i];
			delete_char(line, i);
			while (line[i] && line[i] != c)
				i++;
			delete_char(line, i);
		}
		else
			i++;
	}
}

void	copy_quotes(char *line, int *i, char *newline, int *j)
{
	char	c;

	c = line[*i];
	if (c == '"' || c == '\'')
	{
		newline[(*j)++] = line[(*i)++];
		while (line[*i] && line[*i] != c)
			newline[(*j)++] = line[(*i)++];
	}
}
