/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:20:25 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 11:18:56 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_key(char *key, char **envs)
{
	int		i;
	char	*original_key;

	i = 0;
	while (envs[i])
	{
		original_key = find_key(envs[i]);
		if (ft_strcmp(key, original_key) == 0)
		{
			free(envs[i]);
			while (envs[i + 1])
			{
				envs[i] = envs[i + 1];
				i++;
			}
			envs[i] = NULL;
			return (1);
		}
		i++;
	}
	return (0);
}

int	ft_unset(char **commands, t_var **var)
{
	int	i;

	i = 1;
	while (commands[i])
	{
		char *key = find_key(commands[i]);
		ft_remove_var(key, var);
		i++;
	}
	return (0);
}
