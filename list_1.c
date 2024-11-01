/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:38:12 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/01 09:58:11 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_node(char *content, int type_fd)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token));
	if (!new_node)
		return (NULL);
	new_node->content = strdup(content);
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->seg = 0;
	new_node->type_fd = type_fd;
	return (new_node);
}

void	append_node(t_token **head, char *content, int type_fd)
{
	t_token	*new_node;
	t_token	*current;

	new_node = create_node(content, type_fd);
	if (*head == NULL)
		*head = new_node;
	else
	{
		current = *head;
		while (current->next != NULL)
			current = current->next;
		current->next = new_node;
		new_node->prev = current;
	}
}
void	add_word(t_words **wds, char *value)
{
	t_words	*new_word;
	t_words	*cur;

	new_word = (t_words *)malloc(sizeof(t_words));
	new_word->word = ft_strdup(value);
	new_word->next = NULL;
	if (*wds == NULL)
		*wds = new_word;
	else
	{
		cur = *wds;
		while (cur->next)
			cur = cur->next;
		cur->next = new_word;
	}
}
