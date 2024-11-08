/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:41:18 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 15:24:10 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	execute_command(char **commands, t_general *general, int sig)
{
	if (ft_strcmp(commands[0], "echo") == 0)
		return (execute_echo(commands, sig));
	else if (ft_strcmp(commands[0], "pwd") == 0)
		return (execute_pwd(commands, sig));
	else if (ft_strcmp(commands[0], "cd") == 0)
		return (execute_cd(commands, sig));
	else if (ft_strcmp(commands[0], "env") == 0)
		return (execute_env(commands, general, sig));
	else if (ft_strcmp(commands[0], "export") == 0)
		return (execute_export(commands, general, sig));
	else if (ft_strcmp(commands[0], "unset") == 0)
		return (execute_unset(commands, general, sig));
	else if (ft_strcmp(commands[0], "exit") == 0)
		return (execute_exit(general, sig, commands));
	return (0);
}

int	execute_built(char *str, t_general *general, int sig)
{
	char	**commands;

	commands = ft_split(str, ' ');
	if (commands[0] == NULL)
		return (1);
	return (execute_command(commands, general, sig));
}

static void	exec_son_pid(t_token *temp, int *pipefd, t_general *general)
{
	char	*filtred;

	if (temp->type_fd == 2)
		case_type_2(temp);
	else if (temp->type_fd == 3)
		case_type_3(temp, pipefd);
	else if (temp->type_fd == 4)
		case_type_4(temp);
	filtred = filter_token(temp->content);
	if (execute_built(filtred, general, 1) == 1)
		return ;
	else if (filtred != temp->content)
		execute_filtred(temp, filtred, general);
	else
		execute_not_filtred(temp, general);
}

static void	exec_father(int *prev_fd, t_token *temp, int *pipefd, pid_t pid,
		t_general *general)
{
	int		status;
	char	*filtred;

	waitpid(pid, &status, 0);
	filtred = filter_token(temp->content);
	execute_built(filtred, general, 0);
	if (*prev_fd > 0)
		close(*prev_fd);
	if (temp->next != NULL)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
	write_in_file(status);
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
	extract_tokens(&temp, general);
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
			exec_father(&prev_fd, temp, pipefd, pid, general);
		if (check_seg(temp))
			continue ;
		temp = temp->next;
	}
}
