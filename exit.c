/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:19:40 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 15:37:57 by msalembe         ###   ########.fr       */
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

static int	ft_exit_utils(char *str, int sig)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && sig)
		{
			printf("bash: exit: %s: numeric argument required\n", str);
			return (0);
		}
		str++;
	}
	return (1);
}

// static int	verify_args(char *filename, char **commands, int sig)
// {
// 	int		fd;
// 	char	*str;

// 	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
// 			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
// 	if (commands[1] && sig)
// 	{
// 		str = commands[1];
// 		if (!ft_exit_utils(str, commands, sig))
// 			return (0);
// 		if (fd == -1 && sig)
// 		{
// 			perror("Erro ao abrir o arquivo");
// 			exit(EXIT_FAILURE);
// 		}
// 		write(fd, str, ft_strlen(str));
// 		close(fd);
// 	}
// 	else
// 	{
// 		write(fd, "0", 1);
// 		close(fd);
// 		exit(0);
// 	}
// 	return (1);
// }

int	ft_exit(t_general *general, int sig, char **commands)
{
	int	i;

	i = -1;
	//printf("%s\n", commands[1]);
	if (commands[1] && ft_exit_utils(commands[1], sig) && sig)
		write_in_file(ft_atoi(commands[1]));
	else if (commands[1] && !ft_exit_utils(commands[i], sig) && sig)
	{
		printf("bash: exit: %s: numeric argument required\n", commands[1]);
		return (1);
	}
	else
		write_in_file(0);
	if (general->initial_command)
		free(general->initial_command);
	if (general->commands)
	{
		while (general->commands[++i])
			free(general->commands[i]);
		free(general->commands);
	}
	auxiliary(general);
	if (sig)
		printf("exit\n");
	exit(0);
}

int	ft_any_command(char *str)
{
	printf("bash: %s: command not found\n", str);
	return (1);
}
