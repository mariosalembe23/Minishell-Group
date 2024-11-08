/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:16:59 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 11:08:13 by msalembe         ###   ########.fr       */
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

static void	ft_echo_utils(int has_flag, char **input, t_env **env)
{
	char	*key;

	key = NULL;
	if (!has_flag)
		execute_with_flag(input, key, env);
	else
		execute_without_flag(input, key, env);
	write_in_file(0);
}

int	ft_echo(char **commands, t_env **env, int sig)
{
	int		has_flag;
	char	**input;
	int		i;
	int		x;

	has_flag = 0;
	input = commands;
	i = 1;
	if (sig == 0)
		return (0);
	if (!input[i])
		return (printf("\n"));
	if (input[i][0] == '-')
	{
		x = 1;
		while (input[i][x])
		{
			if (input[i][x] != 'n')
				has_flag = 1;
			x++;
		}
	}
	else
		has_flag = 1;
	ft_echo_utils(has_flag, input, env);
	return (0);
}
