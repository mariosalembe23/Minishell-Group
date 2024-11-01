/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:41:18 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/01 15:16:09 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

void	execute_filtred(t_token *temp, char *filtred)
{
	temp->command = ft_split(filtred, ' ');
	free(filtred);
	filtred = ft_strjoin("/bin/", temp->command[0]);
	execve(filtred, temp->command, NULL);
	exit(EXIT_FAILURE);
}

void	execute_not_filtred(t_token *temp)
{
	temp->command = ft_split(temp->content, ' ');
	free(temp->content);
	temp->content = ft_strjoin("/bin/", temp->command[0]);
	execve(temp->content, temp->command, NULL);
	exit(EXIT_FAILURE);
}

int	exec_op(char *str, t_general *general)
{
	char	**commands;

	commands = ft_split(str, ' ');
	if (commands[0] == NULL)
		return (1);
	else if (ft_strcmp(commands[0], "echo") == 0)
		return (ft_echo(commands, &general->env));
	else if (ft_strcmp(commands[0], "pwd") == 0)
		return (ft_pwd(commands));
	else if (ft_strcmp(commands[0], "cd") == 0)
		return (ft_cd(commands));
	else if (ft_strcmp(commands[0], "env") == 0)
		return (ft_env(commands, general->envs, &general->env));
	else if (ft_strcmp(commands[0], "export") == 0)
		return (ft_export(commands, general->envs, &general->env));
	else if (ft_strcmp(commands[0], "unset") == 0)
		return (ft_unset(general->commands, &general->env, general->envs));
	else if (ft_strcmp(commands[0], "exit") == 0)
		return (ft_exit(general));
	return (0);
}

void	exec_son_pid(t_token *temp, int *pipefd, t_general *general)
{
	char	*filtred;

	if (temp->type_fd == 2)
		case_type_2(temp);
	else if (temp->type_fd == 3)
		case_type_3(temp, pipefd);
	else if (temp->type_fd == 4)
		case_type_4(temp);
	filtred = filter_token(temp->content);
	if (exec_op(filtred, general) == 1)
		return ;
	if (filtred != temp->content)
		execute_filtred(temp, filtred);
	else
		execute_not_filtred(temp);
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



void	exec_command(t_token **head, t_general *general)
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
			exec_son_pid(temp, pipefd, general);
			exit(1);
		}
		else
			exec_father(&prev_fd, temp, pipefd, pid);
		if (check_seg(temp))
			continue ;
		temp = temp->next;
	}
}
