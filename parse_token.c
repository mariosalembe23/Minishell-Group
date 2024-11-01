/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_token.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:38:31 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/01 09:50:03 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char			*oprs[] = {"|", ">>", "<<", ">", NULL};

char	*ft_strndup(const char *str, size_t n)
{
	char	*new_str;
	size_t	i;

	if (str == NULL)
		return (NULL);
	new_str = (char *)malloc(n + 1);
	if (new_str == NULL)
		return (NULL);
	for (i = 0; i < n && str[i] != '\0'; i++)
	{
		new_str[i] = str[i];
	}
	new_str[i] = '\0';
	return (new_str);
}

int	get_type_fd(const char *operator)
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

void	tokenize_utils(char *str, int *start, t_token **head, int *i)
{
	int	found;
	int	j;
	int	len;

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
		if (!found)
			(*i)++;
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
