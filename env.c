/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:18:24 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 11:17:31 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **commands, t_var **var, int sig)
{
	if (sig == 0)
		return (0);
	if (commands[1])
	{
		printf("Too arguments for env\n");
		return (1);
	}
	show_vars_env(var, sig);
	return (0);
}
