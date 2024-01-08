/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2023/12/29 19:08:14 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	replace_spaces(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (line[i] == '"' || line[i] == '\'' )
			skip_quotes(line, &i, line[i]);
		if (ft_is_space(line[i]))
			line[i] = 2;
		if (line[i])
			i++;
	}
}

void	treat_great_less(char *line, int *i, char *newline, int *j)
{
	while (line[*i] == '<' || line[*i] == '>')
		newline[(*j)++] = line[(*i)++];
	if (!ft_is_space(line[*i]))
		newline[(*j)++] = 32;
}

char	*prepare_2nd_split(char *line)
{
	int		i;
	int		j;
	char	*newline;

	i = 0;
	j = 0;
	newline = malloc(ft_strlen(line) * 4);
	if (!newline)
		return (NULL);
	while (line[i])
	{
		copy_quotes(line, &i, newline, &j);
		if (line[i] && (line[i] == '<' || line[i] == '>'))
			treat_great_less(line, &i, newline, &j);
		if (line[i])
			newline[j++] = line[i++];
		if (line[i] && (line[i] == '<' || line[i] == '>'))
			newline[j++] = 32;
	}
	newline[j] = '\0';
	replace_spaces(newline);
	return (newline);
}

void	set_comand_list(char **line, t_cmd *cm, t_data sh)
{
	int	i;
	int	j;

	cm->comand = malloc(sizeof(char *) * (matrixlen(line) + 1));
	if (!cm->comand)
		return ;
	i = 0;
	j = 0;
	while (line[i])
	{
		if (line[i][0] == '<' || line[i][0] == '>')
		{
			line[i + 1] = expander(line[i + 1], sh);
			manage_redirections(line, &i, cm, sh);
		}
		else
		{
			cm->comand[j] = ft_strdup(line[i]);
			j++;
		}
		i++;
	}
	cm->comand[j] = 0;
}

t_cmd	*parsing(char **first, t_data sh)
{
	int		i;
	char	**second_split;
	char	*line;
	t_cmd	*cm_list;
	t_cmd	*cm;

	i = 0;
	cm_list = NULL;
	while (first[i] && first[i][0])
	{
		cm = new_comand();
		line = prepare_2nd_split(first[i]);
		second_split = ft_split(line, 2);
		free(line);
		set_comand_list(second_split, cm, sh);
		add_comand(&cm_list, cm);
		free_split(second_split);
		i++;
	}
	expand_comands(&cm_list, sh);
	return (cm_list);
}
