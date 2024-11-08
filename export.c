/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:18:49 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 13:17:55 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_valid_key(const char *key)
{
	int	i;

	i = -1;
	if (!key || !*key)
		return (0);
	if (!ft_isalpha(key[0]) && key[0] != '_')
		return (0);
	while (key[++i])
		if (!ft_isalnum(key[i]) && key[i] != '_')
			return (0);
	return (1);
}

static int	process_export(char *input, int sig)
{
	char	*key;

	key = find_key(input);
	if (key && sig)
	{
		if (!is_valid_key(key) && sig)
		{
			printf("bash: export: '%s' not a valid identifier\n", key);
			free(key);
			return (0);
		}
		free(key);
	}
	else
	{
		if (sig)
		{
			printf("bash: export: Error Key\n");
			return (0);
		}
	}
	return (1);
}

char	**add_var_env(char ***envs, char **commands)
{
	int		len;
	char	**new_mat;
	int		i;
	int		x;

	len = matlen(*envs);
	new_mat = malloc(sizeof(char *) * (len + matlen(commands) + 1));
	if (!new_mat)
		return (NULL);
	i = -1;
	while ((*envs)[++i])
	{
		new_mat[i] = ft_strdup((*envs)[i]);
		i++;
	}
	x = -1;
	while (commands[++x])
	{
		new_mat[i] = ft_strdup(commands[x]);
		i++;
	}
	new_mat[i] = NULL;
	free_mat(*envs);
	*envs = new_mat;
	return (new_mat);
}

int	ft_export(char **commands, t_general *general, int sig)
{
	char	**input;
	int		i;

	input = commands;
	i = 0;
	if (!input[1] && sig)
		show_vars(general->var, 0);
	else
	{
		i = 1;
		while (input[i])
		{
			if (!process_export(input[i], sig))
				return (1);
			i++;
		}
		i = 0;
		while (input[++i])
			add_new_var(general->var, find_key(input[i]), find_value(input[i]));
		*general->var = *general->var;
	}
	return (0);
}
