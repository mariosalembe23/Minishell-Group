/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenization.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:41:18 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/05 14:18:41 by dgermano         ###   ########.fr       */
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
	fd = open(file, O_CREAT | O_RDONLY | O_WRONLY | O_TRUNC , FILE_MODE);
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
		execute_filtred(temp, filtred, general);
	else
		execute_not_filtred(temp, general);
}

void	exec_father(int *prev_fd, t_token *temp, int *pipefd, pid_t pid)
{
	int		status;
	char	*number;
	int		fd;

	if (*prev_fd > 0)
		close(*prev_fd);
	if (temp->next != NULL)
		close(pipefd[1]);
	*prev_fd = pipefd[0];
	waitpid(pid, &status, 0);
	number = ft_itoa(status);
	fd = open(".data", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
	write(fd, number, 1);
	close(fd);
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

void	extract_pid(char **str)
{
	char	*value;
	char	*temp;
	char	*temp2;
	int		i;

	value = ft_itoa(getpid());
	temp = first_word(*str, '$');
	i = 0;
	while ((*str)[i] && (*str)[i] != '$')
		i++;
	while ((*str)[i] && (*str)[i] != ' ')
		i++;
	temp2 = ft_strjoin(temp, value);
	free(temp);
	temp = ft_strjoin(temp2, &((*str)[i]));
	free(temp2);
	free(*str);
	*str = temp;
}
void	extract_case(char **str)
{
	int		fd;
	char	*f_value;
	char	*value;
	char	*temp;
	char	*temp2;
	int		i;

	f_value = (char *)malloc(sizeof(char) * 4);
	f_value[3] = '\0';
	if (access(".data", F_OK) == -1)
	{
		fd = open(".data", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
		write(fd, "0", 1);
		close(fd);
	}
	else
	{
		fd = open(".data", O_RDONLY);
		read(fd, f_value, 4);
		close(fd);
	}
	value = f_value;
	temp = first_word(*str, '$');
	i = 0;
	while ((*str)[i] && (*str)[i] != '$')
		i++;
	while ((*str)[i] && (*str)[i] != ' ')
		i++;
	temp2 = ft_strjoin(temp, value);
	free(temp);
	temp = ft_strjoin(temp2, &((*str)[i]));
	free(temp2);
	free(*str);
	*str = temp;
	close(fd);
}
void	extract_value(char **str, char *env)
{
	char	*value;
	char	*temp;
	char	*temp2;
	int		i;

	value = find_value(env);
	temp = first_word(*str, '$');
	i = 0;
	while ((*str)[i] && (*str)[i] != '$')
		i++;
	while ((*str)[i] && (*str)[i] != ' ')
		i++;
	temp2 = ft_strjoin(temp, value);
	free(temp);
	temp = ft_strjoin(temp2, &((*str)[i]));
	free(temp2);
	free(*str);
	*str = temp;
}

char	*apply_var_value(char *str, char *pos, t_general *general)
{
	char	*arg;
	int		i;
	char	*key;

	arg = first_word(pos + 1, ' ');
	i = 0;
	while (general->envs[i])
	{
		key = find_key(general->envs[i]);
		if (pos[1] == '$')
		{
			extract_pid(&str);
			return (str);
			break ;
		}
		else if (pos[1] == '?')
		{
			extract_case(&str);
			return (str);
			break ;
		}
		else if (ft_strcmp(key, arg) == 0)
		{
			extract_value(&str, general->envs[i]);
			return (ft_strdup(str));
			break ;
		}
		free(key);
		i++;
	}
	free(arg);
	return (str);
}

void	extract_tokens(t_token **head, t_general *general)
{
	t_token	*temp;
	char	*str;
	int		i;
	char	*new_content;

	temp = *head;
	i = 0;
	while (temp != NULL)
	{
		str = temp->content;
		i = -1;
		while (str[++i])
		{
			if (str[i] == '$')
			{
				new_content = apply_var_value(temp->content, &str[i], general);
				if (new_content != temp->content)
				{
					temp->content = new_content;
					str = temp->content;
					i = -1;
				}
			}
		}
		temp = temp->next;
	}
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
			exec_father(&prev_fd, temp, pipefd, pid);
		if (check_seg(temp))
			continue ;
		temp = temp->next;
	}
}
