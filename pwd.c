/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:17:53 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 11:14:12 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_pwd(char **commands, int sig)
{
	char buff[1024];
	char *path;

	if (!check_pwd_options(commands) || sig == 0)
		return (1);
	if (getcwd(buff, sizeof(buff)) != NULL)
	{
		path = ft_strdup(buff);
		if (!path)
		{
			perror("malloc error");
			exit(1);
		}
		write_in_file(0);
		printf("%s\n", path);
		free(path);
	}
	else
	{
		printf("getcwd() error: %s\n", strerror(errno));
		return (1);
	}
	return (0);
}
