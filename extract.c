/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:00:52 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:52:50 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

static void	extract_quote_utils(int *i, char *str, t_filter *cur,
		t_general *general)
{
	char	*new_content;

	if (str[*i] == '$')
	{
		new_content = apply_var_value(cur->filtered, &str[*i], general);
		if (new_content != cur->filtered)
		{
			cur->filtered = new_content;
			str = cur->filtered;
			*i = -1;
		}
	}
}

static void	extract_quote(t_filter **tmp, t_general *general)
{
	t_filter	*cur;
	char		*str;
	int			i;

	cur = *tmp;
	while (cur)
	{
		if (cur->quote == 2 || cur->quote == 0)
		{
			str = cur->filtered;
			i = -1;
			while (str[++i])
				extract_quote_utils(&i, str, cur, general);
		}
		cur = cur->next;
	}
}

void	extract_tokens(t_token **head, t_general *general)
{
	t_token		*temp;
	t_filter	*tmp;

	tmp = NULL;
	temp = *head;
	while (temp != NULL)
	{
		create_filter(temp->content, &tmp);
		extract_quote(&tmp, general);
		free(temp->content);
		temp->content = join_struct(&tmp);
		temp = temp->next;
	}
}
