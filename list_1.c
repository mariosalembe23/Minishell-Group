/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/28 12:38:12 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/28 12:38:29 by msalembe         ###   ########.fr       */
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
	new_node->type_fd = type_fd;
	return (new_node);
}

void	append_node(t_token **head, t_token **tail, char *content, int type_fd)
{
	t_token	*new_node;

	new_node = create_node(content, type_fd);
	if (*head == NULL)
	{
		*head = new_node;
		*tail = new_node;
	}
	else
	{
		(*tail)->next = new_node;
		new_node->prev = *tail;
		*tail = new_node;
	}
}
