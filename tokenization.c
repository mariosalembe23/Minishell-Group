/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:41:18 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/01 12:16:18 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	case_type_4(t_token *temp)
{
	int		fd;
	char	*file;

	file = temp->next->content;
	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, FILE_MODE);
	if (fd < 0)
	{
		perror("open");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

void	exec_son_pid(t_token *temp, int *pipefd)
{
	char	*filtred;

	if (temp->type_fd == 2)
		case_type_2(temp);
	else if (temp->type_fd == 3)
		case_type_3(temp, pipefd);
	else if (temp->type_fd == 4)
		case_type_4(temp);
	filtred = filter_token(temp->content);
	if (filtred != temp->content)
	{
		temp->command = ft_split(filtred, ' ');
		free(filtred);
		filtred = ft_strjoin("/bin/", temp->command[0]);
		execve(filtred, temp->command, NULL);
		perror("execve");
		exit(EXIT_FAILURE);
	}
	else
	{
		temp->command = ft_split(temp->content, ' ');
		free(temp->content);
		temp->content = ft_strjoin("/bin/", temp->command[0]);
		execve(temp->content, temp->command, NULL);
	}
}

void	exec_father(int *prev_fd, t_token *temp, int *pipefd, pid_t pid)
{
	if (*prev_fd > 0)
		close(*prev_fd);
	if (temp->next != NULL)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
	waitpid(pid, NULL, 0);
	unlink("/tmp/minishel_trash.tmp");
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

void	exec_command(t_token **head)
{
	t_token	*temp;
	int		pipefd[2];
	pid_t	pid;
	int		prev_fd;

	prev_fd = 0;
	temp = *head;
	while (temp != NULL)
	{
		if (temp->next != NULL)
			pipe(pipefd);
		pid = fork();
		if (pid == 0)
		{
			initial_case(prev_fd, temp, pipefd);
			exec_son_pid(temp, pipefd);
			exit(1);
		}
		else
			exec_father(&prev_fd, temp, pipefd, pid);
		if (check_seg(temp))
			continue ;
		temp = temp->next;
	}
}
