/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   do_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cjoao-me <cjoao-me@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/21 13:05:26 by mneves-l          #+#    #+#             */
/*   Updated: 2023/12/29 11:20:47 by cjoao-me         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	do_exit(t_cmd *cmd)
{
	ft_putendl_fd("exit", 1);
	if (!cmd->comand[1])
		exit(set_exit_code(0, 0));
	else if (!check_exit_arg(cmd->comand[1]))
	{
		ft_putstr_fd("exit: ", 2);
		ft_putstr_fd(cmd->comand[1], 2);
		ft_putendl_fd(": numeric argument required", 2);
		exit(set_exit_code(2, 1));
	}
	else if (cmd->comand[2])
	{
		ft_putendl_fd("exit: too many arguments", 2);
		set_exit_code(1, 1);
	}
	else 
		exit(set_exit_code(get_code(cmd->comand[1]), 1));
}

int	check_exit_arg(char *str)
{
	long long int	n;
	int				i;

	i = 0;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while (ft_isdigit(str[i]))
		i++;
	if (str[i])
		return (0);
	n = ft_atoi(str);
	if ((ft_strlen(str) > 19 && n > 0) || (ft_strlen(str) > 20 \
		&& n < 0) || n > LLONG_MAX || n < LLONG_MIN)
		return (0);
	else
		return (1);
}

int	get_code(char *str)
{
	long long int	n;

	n = ft_atoi(str) % 256;
	if (n > 0)
		n = n + 256;
	return (n);
}
