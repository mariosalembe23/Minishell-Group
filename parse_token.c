/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:38:31 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 15:00:05 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	get_type_fd(const char *operator)
{
	if (strcmp(operator, "|") == 0)
		return (1);
	else if (strcmp(operator, ">>") == 0)
		return (2);
	else if (strcmp(operator, "<<") == 0)
		return (3);
	else if (strcmp(operator, ">") == 0)
		return (4);
	return (0);
}

char	*filter_token(char *token)
{
	int		i;
	char	*token_f;
	char	*filtred_token;

	i = -1;
	while (token[++i])
	{
		if (token[i] == '<')
		{
			token_f = ft_strdup(ft_strrchr(&token[i], ' '));
			if (token[i - 1] == 32)
			{
				filtred_token = ft_strjoin(ft_strndup(token, i - 1), token_f);
				free(token);
				token = filtred_token;
			}
			else
			{
				token[i] = 32;
				filtred_token = ft_strjoin(ft_strndup(token, i), token_f);
			}
			return (filtred_token);
		}
	}
	return (token);
}

static void	ft_increment(int found, int *i)
{
	if (!found)
		(*i)++;
}

static void	tokenize_utils(char *str, int *start, t_token **head, int *i)
{
	int			found;
	int			j;
	int			len;
	const char	*oprs[] = {"|", ">>", "<<", ">", NULL};

	while (str[*i] != '\0')
	{
		found = 0;
		j = -1;
		while (oprs[++j] != NULL)
		{
			len = strlen(oprs[j]);
			if (strncmp(&str[*i], oprs[j], len) == 0)
			{
				if (*i > *start)
					append_node(head, ft_strndup(&str[*start], *i - *start),
						get_type_fd(oprs[j]));
				*i += len;
				*start = *i;
				found = 1;
				break ;
			}
		}
		ft_increment(found, i);
	}
}

void	tokenize(char *str, t_token **head)
{
	int	i;
	int	start;

	i = 0;
	start = 0;
	tokenize_utils(str, &start, head, &i);
	if (i > start)
		append_node(head, ft_strndup(&str[start], i - start), 0);
}
