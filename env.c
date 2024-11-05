/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:18:24 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/05 19:18:43 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **commands, char **envs, t_env **env)
{
	int i;

	if (commands[1])
	{
		printf("Too arguments for env\n");
		return (1);
	}
	i = -1;
	while (envs[++i])
		printf("%s\n", envs[i]);
	show_vars_env(env, 1);
	return (1);
}