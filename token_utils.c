/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:35:46 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 15:03:18 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initial_case(int prev_fd, t_token *temp, int pipefd[2])
{
	if (prev_fd > 0)
	{
		dup2(prev_fd, STDIN_FILENO);
		close(prev_fd);
	}
	if (temp->type_fd == 1 && temp->next != NULL)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(pipefd[1]);
	}
}

void	case_type_2(t_token *temp)
{
	char	*file;
	int		fd;

	file = temp->next->content;
	fd = open(file, O_CREAT | O_WRONLY | O_APPEND, FILE_MODE);
	if (fd < 0)
	{
		perror("Erro ao abrir o arquivo");
		exit(EXIT_FAILURE);
	}
	dup2(fd, STDOUT_FILENO);
	close(fd);
}

static void	clean_node(t_token *temp)
{
	t_token	*trash;

	trash = temp->next;
	if (trash != NULL)
	{
		if (trash->next != NULL)
			trash->next->prev = temp;
		temp->next = trash->next;
		free(trash->content);
		free_mat(trash->command);
		free(trash);
	}
}

static void	case_type_3_utils(t_token *temp, char **temp_mat, int t_fd)
{
	char	*trash_content;

	if (matlen(temp_mat) > 1)
	{
		reader(temp_mat[0], 0, t_fd);
		trash_content = ft_strdup(temp->content);
		free(temp->content);
		temp->content = ft_strjoin(trash_content, temp_mat[matlen(temp_mat)
				- 1]);
		free(trash_content);
	}
	else
	{
		trash_content = ft_strdup(temp->content);
		free(temp->content);
		temp->content = ft_strjoin(trash_content, t_file);
		free(trash_content);
		reader(temp_mat[0], 1, t_fd);
		free_mat(temp_mat);
	}
}

void	case_type_3(t_token *temp, int pipefd[2])
{
	char **temp_mat;
	int t_fd;
	int type_fd;

	temp_mat = ft_split(temp->next->content, ' ');
	type_fd = temp->next->type_fd;
	t_fd = open(t_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	temp->seg = 1;
	case_type_3_utils(temp, temp_mat, t_fd);
	if (type_fd == 1)
	{
		dup2(pipefd[1], STDOUT_FILENO);
		close(t_fd);
	}
	clean_node(temp);
}
