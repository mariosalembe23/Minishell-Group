/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:19:29 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/05 19:19:36 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **commands)
{
	char *home;
	char *path;

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
	return (1);
}
