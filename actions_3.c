/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions_3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 09:17:29 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/29 12:44:58 by msalembe         ###   ########.fr       */
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

static int	ft_exit_utils(char *str, t_general *general)
{
	while (*str)
	{
		if (!ft_isdigit(*str))
		{
			printf("bash: exit: %s: numeric argument required\n",
				general->commands[1]);
			return (0);
		}
		str++;
	}
	return (1);
}

static int	verify_args(char *filename, t_general *general)
{
	int		fd;
	char	*str;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC,
			S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH);
	if (general->commands[1])
	{
		str = general->commands[1];
		if (!ft_exit_utils(str, general))
			return (0);
		if (fd == -1)
		{
			perror("Erro ao abrir o arquivo");
			exit(EXIT_FAILURE);
		}
		write(fd, str, ft_strlen(str));
		close(fd);
	}
	else
	{
		write(fd, "0", 1);
		close(fd);
		exit(0);
	}
	return (1);
}

int	ft_exit(t_general *general)
{
	int		i;
	char	*filename;

	i = -1;
	filename = ".data";
	if (!verify_args(filename, general))
		return (1);
	if (general->initial_command)
		free(general->initial_command);
	if (general->commands)
	{
		while (general->commands[++i])
			free(general->commands[i]);
		free(general->commands);
	}
	auxiliary(general);
	printf("exit\n");
	exit(0);
}

int	ft_any_command(void)
{
	printf("bash: command not found\n");
	return (1);
}
