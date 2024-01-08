/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/12/29 12:45:25 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_pipe(char *line, int *i)
{
	if (line[*i] == '|')
	{
		line[*i] = 2;
		(*i)++;
		if (line[*i] == '|' || line[*i] == '\0')
		{
			print_syntax_error('|');
			return (0);
		}
		else
			skip_spaces(line, i);
		if (line[*i] == '|' || line[*i] == '\0')
		{
			print_syntax_error('|');
			return (0);
		}
	}
	return (1);
}

int	check_redir(char *line, int *i)
{
	char	c;

	if (line[*i] == '>' || line[*i] == '<')
	{
		c = line[*i];
		(*i)++;
		if (check_mixed_redir(line, c, i))
			return (0);
		skip_spaces(line, i);
		if (line[*i] == '>' || line[*i] == '<' || \
				line[*i] == '|' || line[*i] == '\0')
		{
			if (line [*i] == '\0')
				print_syntax_error('\n');
			else
				print_syntax_error(line[*i]);
			return (0);
		}
	}
	return (1);
}

int	check_quotes(char *line, int *i)
{
	char	c;

	if (line[*i] == '"' || line[*i] == '\'' )
	{
		c = line[*i];
		(*i)++;
		while (line[*i] && line[*i] != c)
			(*i)++;
		if (line[*i] == '\0')
		{
			ft_putendl_fd("Syntax error: unclosed quotes", 2);
			return (0);
		}
	}
	return (1);
}

int	check_syntax(char *line, int i)
{
	skip_spaces(line, &i);
	if (line [i] == '|')
	{
		print_syntax_error('|');
		return (0);
	}
	while (line [i])
	{
		if (line [i] == '&' || line [i] == '\\' || line [i] == ';')
		{
			print_syntax_error(line [i]);
			return (0);
		}
		else if (!check_pipe(line, &i))
			return (0);
		else if (!check_redir(line, &i))
			return (0);
		else if (!check_quotes(line, &i))
			return (0);
		i++;
	}
	return (1);
}
