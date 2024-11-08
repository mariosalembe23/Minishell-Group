/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:41:18 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:03:46 by msalembe         ###   ########.fr       */
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

int	execute_built(char *str, t_general *general, int sig)
{
	char	**commands;

	commands = ft_split(str, ' ');
	if (commands[0] == NULL)
		return (1);
	else if (ft_strcmp(commands[0], "echo") == 0)
	{
		if (sig)
			exit(ft_echo(commands, &general->env, sig));
		return (ft_echo(commands, &general->env, sig));
	}
	else if (ft_strcmp(commands[0], "pwd") == 0)
	{
		if (sig)
			exit(ft_pwd(commands, sig));
		return (ft_pwd(commands, sig));
	}
	else if (ft_strcmp(commands[0], "cd") == 0)
	{
		if (sig)
			exit(ft_cd(commands, sig));
		return (ft_cd(commands, sig));
	}
	else if (ft_strcmp(commands[0], "env") == 0)
	{
		if (sig)
			exit(ft_env(commands, general->var, sig));
		return (ft_env(commands, general->var, sig));
	}
	else if (ft_strcmp(commands[0], "export") == 0)
	{
		if (sig)
			exit(ft_export(commands, general, sig));
		return (ft_export(commands, general, sig));
	}
	else if (ft_strcmp(commands[0], "unset") == 0)
	{
		if (sig)
			exit(ft_unset(commands, general->var));
		return (ft_unset(commands, general->var));
	}
	else if (ft_strcmp(commands[0], "exit") == 0)
		exit (ft_exit(general, sig, commands));
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
	if (execute_built(filtred, general, 1) == 1)
		return ;
	else if (filtred != temp->content)
		execute_filtred(temp, filtred, general);
	else
		execute_not_filtred(temp, general);
}

void	write_in_file(int status)
{
	char	*number;
	int		fd;

	number = ft_itoa(status);
	fd = open(".data", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	write(fd, number, ft_strlen(number));
	close(fd);
}

void	exec_father(int *prev_fd, t_token *temp, int *pipefd, pid_t pid,
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
