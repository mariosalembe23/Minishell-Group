/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 17:18:09 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/29 08:22:07 by msalembe         ###   ########.fr       */
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

static int	process_export(const char *input)
{
	char	*key;

	key = find_key(input);
	if (key)
	{
		if (!is_valid_key(key))
		{
			printf("bash: export: '%s' not a valid identifier\n", key);
			free(key);
			return (0);
		}
		free(key);
	}
	else
	{
		printf("bash: export: Error Key\n");
		return (0);
	}
	return (1);
}

int	ft_initial_checker(char *input)
{
	if (!process_export((const char *)input))
		return (0);
	return (1);
}

static void	ft_add_varenv(char **commands, t_env **env)
{
	int		i;
	char	*key;
	char	*value;

	i = 1;
	while (commands[i])
	{
		key = find_key(commands[i]);
		value = find_value(commands[i]);
		if (value == NULL)
			value = ft_strdup("");
		add_new_var(env, key, value);
		free(key);
		i++;
	}
}

int	ft_export(char **commands, char **envs, t_env **env)
{
	int		i;
	char	**input;

	input = commands;
	if (!input[1])
	{
		i = -1;
		while (envs[++i])
			printf("declare -x %s\n", envs[i]);
		show_vars(env, 1);
	}
	else
	{
		i = 1;
		while (input[i])
		{
			if (!ft_initial_checker(input[i]))
				return (1);
			i++;
		}
		ft_add_varenv(commands, env);
	}
	return (1);
}
