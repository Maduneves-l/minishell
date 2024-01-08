/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mneves-l <mneves-l@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/08 17:08:28 by mneves-l          #+#    #+#             */
/*   Updated: 2024/01/08 17:23:55 by mneves-l         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	check_name(char *n)
{
	int	i;

	i = 0;
	while (n[i])
	{
		if ((n[i] > 32 && n[i] < 48) || (n[i] > 57 && n[i] < 65) \
			|| (n[i] > 90 && n[i] < 97) || (n[i] > 122 && n[i] < 127))
			error_export(n);
		i++;
	}
}

void	error_export(char *name)
{
	ft_putstr_fd("export: '", 2);
	ft_putstr_fd(name, 2);
	ft_putendl_fd("': not a valid identifier", 2);
	set_exit_code(1, 1);
	return ;
}
