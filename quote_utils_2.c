/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils_2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:31:29 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/07 16:22:51 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	alloc_filter_1(t_filter **head, t_filter **past, char *str, int *i)
{
	t_filter	*new;

	new = malloc(sizeof(t_filter));
	new->filtered = extract_quote_1(&str[*i + 1]);
	new->quote = 1;
	new->next = NULL;
	if (*past == NULL)
		*head = new;
	else
		(*past)->next = new;
	*past = new;
	(*i)++;
	while (str[*i] != '\'' && str[*i])
		(*i)++;
	(*i)++;
}

void	alloc_filter_2(t_filter **head, t_filter **past, char *str, int *i)
{
	t_filter	*new;

	new = malloc(sizeof(t_filter));
	new->filtered = extract_quote_2(&str[*i + 1]);
	new->quote = 2;
	new->next = NULL;
	if (*past == NULL)
		*head = new;
	else
		(*past)->next = new;
	*past = new;
	(*i)++;
	while (str[*i] != '\"' && str[*i])
		(*i)++;
	(*i)++;
}
