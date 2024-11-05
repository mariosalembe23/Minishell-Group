/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dgermano <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:33:21 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/01 16:04:49 by dgermano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_tokens(t_token *head)
{
	t_token	*temp;

	while (head != NULL)
	{
		temp = head;
		head = head->next;
		free(temp->content);
		free(temp);
	}
}

int	matlen(char **mat)
{
	int	len;

	len = 0;
	while (mat[len] != NULL)
	{
		len++;
	}
	return (len);
}

void	free_mat(char **mat)
{
	int	i;

	i = 0;
	if (mat == NULL)
		return ;
	while (mat[i] != NULL)
	{
		free(mat[i]);
		i++;
	}
	free(mat);
}

void	ft_reader(t_words **words, char *stop_str)
{
	char	*temp;

	while (1)
	{
		temp = readline("> ");
		if (temp == NULL || strcmp(temp, stop_str) == 0)
		{
			free(temp);
			break ;
		}
		add_word(words, temp);
		free(temp);
	}
}

void	reader(char *stop_str, int type, int fd)
{
	t_words	*words;
	t_words	*cur;
	t_words	*next;

	words = NULL;
	ft_reader(&words, stop_str);
	if (type)
	{
		cur = words;
		while (cur)
		{
			ft_putstr_fd(cur->word, fd);
			ft_putchar_fd('\n', fd);
			cur = cur->next;
		}
	}
	while (words)
	{
		next = words->next;
		free(words->word);
		free(words);
		words = next;
	}
}
