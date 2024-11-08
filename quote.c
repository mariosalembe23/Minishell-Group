/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 08:47:34 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:11:03 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static bool	has_unclosed_quotes(const char *str)
{
	bool	in_single_quote;
	bool	in_double_quote;
	int		i;

	in_single_quote = false;
	in_double_quote = false;
	i = 0;
	while (str[i])
	{
		if (str[i] == '\'' && !in_double_quote)
			in_single_quote = !in_single_quote;
		else if (str[i] == '\"' && !in_single_quote)
			in_double_quote = !in_double_quote;
		i++;
	}
	return (in_single_quote || in_double_quote);
}

int	process_command(t_token **head)
{
	t_token	*temp;

	temp = *head;
	while (temp)
	{
		if (has_unclosed_quotes(temp->content))
		{
			write_in_file(2);
			printf("minishell: syntax error: unclosed quotes\n");
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

char	*join_struct(t_filter **head)
{
	t_filter	*tmp;
	char		*str;
	char		*new_str;

	tmp = *head;
	str = ft_strdup("");
	while (tmp)
	{
		new_str = ft_strjoin(str, tmp->filtered);
		free(str);
		str = new_str;
		tmp = tmp->next;
	}
	return (str);
}

void	print_filter(t_filter *head)
{
	t_filter	*tmp;

	tmp = head;
	while (tmp)
	{
		printf("%s QUOTE: %d\n", tmp->filtered, tmp->quote);
		tmp = tmp->next;
	}
}
