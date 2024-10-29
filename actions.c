/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 12:02:53 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/25 17:23:39 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	ft_echo_utils(int has_flag, char **input, t_env **env)
{
	char	*key;

	key = NULL;
	if (!has_flag)
		execute_with_flag(input, key, env);
	else
		execute_without_flag(input, key, env);
}

int	ft_echo(char **commands, t_env **env)
{
	int		has_flag;
	char	**input;
	int		i;
	int		x;

	has_flag = 0;
	input = commands;
	i = 1;
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
	return (1);
}

static int	check_pwd_options(char **commands)
{
	char	*str;

	if (commands[1])
	{
		str = commands[1];
		if (ft_strlen(str) > 2)
		{
			printf("bash: pwd: %s: invalid option\n", str);
			printf("pwd: usage: pwd [-LP]\n");
			return (0);
		}
		else
		{
			if ((str[0] == '-' && str[1] != 'L') && (str[0] == '-'
					&& str[1] != 'P'))
			{
				printf("bash: pwd: %s: invalid option\n", str);
				printf("pwd: usage: pwd [-LP]\n");
				return (0);
			}
		}
	}
	return (1);
}

int	ft_pwd(char **commands)
{
	char	buff[1024];
	char	*path;

	if (!check_pwd_options(commands))
		return (1);
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		path = ft_strdup(buff);
		if (!path)
		{
			perror("malloc error");
			exit(1);
		}
		printf("%s\n", path);
		free(path);
	}
	else
	{
		printf("getcwd() error: %s\n", strerror(errno));
		return (0);
	}
	return (1);
}

int	ft_cd(char **commands)
{
	char	*home;
	char	*path;

	path = commands[1];
	home = getenv("HOME");
	if (path == NULL || ft_strcmp(path, "") == 0 || ft_strcmp(path, "~") == 0
		|| ft_strcmp(path, " ") == 0)
	{
		if (chdir(home) != 0)
			printf("cd: %s\n", strerror(errno));
		return (1);
	}
	if (chdir(path) != 0)
		printf("cd: %s\n", strerror(errno));
	// if (path != NULL)
	// 	printf("%s\n", path);
	return (1);
}
