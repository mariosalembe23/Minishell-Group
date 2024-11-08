/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 15:29:50 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/07 16:31:25 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_quote_2(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] != '\"' && str[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i] != '\"')
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

char	*extract_quote_1(char *str)
{
	int		i;
	char	*new;

	i = 0;
	while (str[i] != '\'' && str[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	i = -1;
	while (str[++i] != '\'')
		new[i] = str[i];
	new[i] = '\0';
	return (new);
}

char	*extract_quote_0(char *str)
{
	int		i;
	char	*new;
	int		j;

	i = 0;
	while (str[i] != '\'' && str[i] != '\"' && str[i])
		i++;
	new = malloc(sizeof(char) * (i + 1));
	if (!new)
		return (NULL);
	j = -1;
	while (++j < i)
		new[j] = str[j];
	new[i] = '\0';
	return (new);
}

void	alloc_filter_3(t_filter **head, t_filter **past, char *str, int *i)
{
	t_filter	*new;

	new = malloc(sizeof(t_filter));
	new->filtered = extract_quote_0(&str[(*i)]);
	new->quote = 0;
	new->next = NULL;
	if (*past == NULL)
		*head = new;
	else
		(*past)->next = new;
	*past = new;
	while (str[*i] != '\'' && str[*i] != '\"' && str[*i])
		(*i)++;
}

void	create_filter(char *str, t_filter **head)
{
	int			i;
	t_filter	*past;

	i = 0;
	past = NULL;
	while (str[i])
	{
		if (str[i] == '\'')
			alloc_filter_1(head, &past, str, &i);
		else if (str[i] == '\"')
			alloc_filter_2(head, &past, str, &i);
		else if (str[i] != '\'' && str[i] != '\"')
			alloc_filter_3(head, &past, str, &i);
	}
}
