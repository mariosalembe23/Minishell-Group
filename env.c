/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:18:24 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 15:06:54 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(char **commands, t_var **var, int sig)
{
	if (sig == 0)
		return (0);
	if (commands[1])
	{
		printf("Too arguments for env\n");
		return (1);
	}
	show_vars_env(var, sig);
	return (0);
}

void	write_in_file(int status)
{
	char *number;
	int fd;

	number = ft_itoa(status);
	fd = open(".data", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	write(fd, number, ft_strlen(number));
	close(fd);
}

int	check_seg(t_token *temp)
{
	if (temp->seg == 1)
	{
		temp = temp->next;
		if (temp == NULL)
			return (1);
	}
	return (0);
}
