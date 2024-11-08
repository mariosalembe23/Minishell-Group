/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:19:29 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 15:05:27 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd(char **commands, int sig)
{
	char	*home;
	char	*path;

	path = commands[1];
	home = getenv("HOME");
	if (path == NULL || ft_strcmp(path, "") == 0 || ft_strcmp(path, "~") == 0
		|| ft_strcmp(path, " ") == 0)
	{
		if (chdir(home) != 0 && sig)
		{
			return (1);
			printf("cd: %s\n", strerror(errno));
		}
		return (0);
	}
	if (chdir(path) != 0 && sig)
	{
		return (1);
		printf("cd: %s\n", strerror(errno));
	}
	return (0);
}

char	*ft_strndup(const char *str, size_t n)
{
	char	*new_str;
	size_t	i;

	if (str == NULL)
		return (NULL);
	new_str = (char *)malloc(n + 1);
	if (new_str == NULL)
		return (NULL);
	for (i = 0; i < n && str[i] != '\0'; i++)
	{
		new_str[i] = str[i];
	}
	new_str[i] = '\0';
	return (new_str);
}

char	*first_word(char *str, char delim)
{
	int		i;
	char	*word;

	i = 0;
	while (str[i] && str[i] != delim)
		i++;
	word = ft_strndup(str, i);
	return (word);
}
