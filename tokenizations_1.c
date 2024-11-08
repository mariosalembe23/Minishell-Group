/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizations_1.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 15:07:24 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 15:08:39 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_type_4(t_token *temp)
{
	int		fd;
	char	*file;

	file = temp->next->content;
	if (*file == ' ')
		file++;
	fd = open(file, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC, FILE_MODE);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	execute_filtred(t_token *temp, char *filtred, t_general *general)
{
	temp->command = ft_split(filtred, ' ');
	free(filtred);
	filtred = ft_strjoin("/bin/", temp->command[0]);
	if (access(filtred, F_OK) == -1)
	{
		free(filtred);
		printf("minishell: %s: command not found\n", temp->command[0]);
	}
	else
		execve(filtred, temp->command, general->envs);
	exit(EXIT_FAILURE);
}

void	execute_not_filtred(t_token *temp, t_general *general)
{
	temp->command = ft_split(temp->content, ' ');
	free(temp->content);
	temp->content = ft_strjoin("/bin/", temp->command[0]);
	if (access(temp->content, F_OK) == -1 && temp->type_fd != 0)
	{
		free(temp->content);
		printf("%s command not found\n", temp->command[0]);
	}
	else
		execve(temp->content, temp->command, general->envs);
	exit(EXIT_FAILURE);
}
