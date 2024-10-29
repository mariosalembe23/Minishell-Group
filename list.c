/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:57:50 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/25 17:23:49 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	verify_if_exists(t_env **env, char *name, char *value)
{
	t_env	*temp;

	temp = *env;
	while (temp != NULL)
	{
		if (ft_strcmp(name, temp->key) == 0)
		{
			if (ft_strcmp(value, "") == 0 || ft_strlen(value) == 0)
				return (1);
			free(temp->value);
			temp->value = ft_strdup(value);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	add_new_var(t_env **env, char *key, char *value)
{
	t_env	*new;

	if (verify_if_exists(env, key, value))
		return ;
	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		printf("error allocating memmory");
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *env;
	*env = new;
}

static void	ft_auxiliary_remove(t_env *temp, char *input, t_env *prev)
{
	while (temp != NULL)
	{
		if (ft_strcmp(input, temp->key) == 0)
		{
			prev->next = temp->next;
			free(temp->key);
			free(temp->value);
			free(temp);
			return ;
		}
		prev = temp;
		temp = temp->next;
	}
}

void	ft_remove_var(char *input, t_env **env)
{
	t_env	*temp;
	t_env	*prev;

	temp = *env;
	prev = NULL;
	if (temp == NULL)
		return ;
	if (ft_strcmp(input, temp->key) == 0)
	{
		*env = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return ;
	}
	ft_auxiliary_remove(temp, input, prev);
}

void	show_unique_var(char *key, t_env **env, char **input, int i)
{
	t_env	*temp;

	temp = *env;
	while (temp != NULL)
	{
		if (ft_strcmp(key, temp->key) == 0)
		{
			if (ft_strcmp(temp->value, "") != 0 && input[i + 1])
				printf("%s ", temp->value);
			else if (ft_strcmp(temp->value, "") != 0 && !input[i + 1])
				printf("%s\n", temp->value);
			else if (ft_strcmp(temp->value, "") == 0 && !input[i + 1])
				printf("%s\n", temp->value);
		}
		temp = temp->next;
	}
}
