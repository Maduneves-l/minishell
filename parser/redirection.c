/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/06 15:11:40 by cjoao-me          #+#    #+#             */
/*   Updated: 2024/01/08 16:02:57 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	redir_type(char *str)
{
	if (str[0] == '>' && !str[1])
		return (1);
	else if (str[0] == '>')
		return (2);
	else if (str[0] == '<' && !str[1])
		return (3);
	else
		return (4);
}

void	infile_error(char **line, int *i)
{
	if (access(line[(*i) + 1], F_OK))
	{
		set_exit_code(1, 1);
		ft_putstr_fd(line[(*i) + 1], 1);
		ft_putendl_fd(": No such file or directory", 1);
	}
	else if (access(line[(*i) + 1], R_OK))
	{
		set_exit_code(126, 1);
		ft_putstr_fd(line[(*i) + 1], 1);
		ft_putendl_fd(": Permission denied", 1);
	}
}

void	manage_outfile(int option, char **line, int *i, t_cmd *cm)
{
	if (cm->redir[1] > 2 && (option == 1 || option == 2))
		close(cm->redir[1]);
	if (option == 2)
		cm->redir[1] = open(line[(*i) + 1], \
				O_WRONLY | O_APPEND | O_CREAT, 0644);
	else if (option == 1)
		cm->redir[1] = open(line[(*i) + 1], \
				O_WRONLY | O_TRUNC | O_CREAT, 0644);
}

void	manage_infile(t_cmd *cm, char **line, int *i, t_data sh)
{
	int	hd;
	int	option;

	option = redir_type(line[*i]);
	if (option == 4)
		hd = ft_here_doc(line[(*i) + 1], sh);
	if (cm->redir[0] != -1)
	{
		if (cm->redir[0] > 2 && (option == 3 || option == 4))
			close(cm->redir[0]);
		if (option == 3)
			cm->redir[0] = open(line[(*i) + 1], O_RDONLY, 0644);
		else if (option == 4)
		{
			cm->redir[0] = hd;
			if (hd == -1)
				cm->hd_error = 1;
		}
		if (cm->redir[0] < 0 && option == 3)
			infile_error(line, i);
	}
}

void	manage_redirections(char **line, int *i, t_cmd *cm, t_data sh)
{
	int	option;

	option = redir_type(line[*i]);
	if (!cm->hd_error)
	{
		manage_infile(cm, line, i, sh);
		if (cm->redir[0] != -1)
			manage_outfile(option, line, i, cm);
	}
	(*i)++;
}
