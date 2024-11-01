/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_1.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:20:13 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/31 14:46:09 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_key_word(char *key, char **input, int break_type, int i)
{
	char	c;
	int		fd;

	key = ft_strchr(input[i], '$');
	if (key)
	{
		key++;
		if (*key == '?')
		{
			if (!access(".data", F_OK) == 0)
				printf("%d ", 0);
			else
			{
				fd = open(".data", O_RDONLY);
				while (read(fd, &c, 1) == 1)
					printf("%c", c);
				close(fd);
				key++;
				if (break_type && input[i + 1] == NULL)
					printf("%s\n", key);
				else
					printf("%s ", key);
			}
		}
	}
}

void	execute_with_flag(char **input, char *key, t_env **env)
{
	int	i;
	int	break_type;

	i = 2;
	break_type = 0;
	while (input[i])
	{
		if (input[i][0] == '$' && input[i][1] && input[i][1] != '?')
		{
			key = ft_strchr(input[i], '$');
			if (key)
			{
				key++;
				show_unique_var(key, env, input, i);
			}
		}
		else if (input[i][0] == '$' && input[i][1] == '?')
			print_key_word(key, input, break_type, i);
		else if (input[i + 1] != NULL)
			printf("%s ", input[i]);
		else
			printf("%s", input[i]);
		i++;
	}
}

void	execute_without_flag(char **input, char *key, t_env **env)
{
	int	i;
	int	break_type;

	break_type = 1;
	i = 1;
	while (input[i])
	{
		if (input[i][0] == '$' && input[i][1] && input[i][1] != '?')
		{
			key = ft_strchr(input[i], '$');
			if (key)
			{
				key++;
				show_unique_var(key, env, input, i);
			}
		}
		else if (input[i][0] == '$' && input[i][1] == '?')
			print_key_word(key, input, break_type, i);
		else if (input[i + 1] != NULL)
			printf("%s ", input[i]);
		else
			printf("%s\n", input[i]);
		i++;
	}
}

int	ft_env(char **commands, char **envs, t_env **env)
{
	int	i;

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

int	ft_unset(char **commands, t_env **env, char **envs)
{
	int	i;
	int	result;

	i = 1;
	result = 0;
	while (commands[i])
	{
		if (verify_key(commands[i], envs))
			result = 1;
		if (result != 1)
			ft_remove_var(commands[i], env);
		i++;
	}
	return (1);
}
