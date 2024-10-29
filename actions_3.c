/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:17:29 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/29 08:44:23 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	auxiliary(t_general *general)
{
	int		i;
	t_env	*tmp;

	i = -1;
	if (general->envs)
	{
		while (general->envs[++i])
			free(general->envs[i]);
		free(general->envs);
	}
	if (general->env)
	{
		while (general->env)
		{
			tmp = general->env;
			general->env = general->env->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
		}
	}
}

int	ft_exit(t_general *general)
{
	int	i;

	i = -1;
	if (general->initial_command)
		free(general->initial_command);
	if (general->commands)
	{
		while (general->commands[++i])
			free(general->commands[i]);
		free(general->commands);
	}
	auxiliary(general);
	// if (general->token)
	// {
	// 	free(general->token->content);
	// 	i = -1;
	// 	while (general->token->command[++i])
	// 		free(general->token->command[i]);
	// 	free(general->token->command);
	// 	free(general->token);
	// }
	printf("exit\n");
	exit(0);
}

int	ft_any_command(void)
{
	printf("bash: command not found\n");
	return (1);
}
