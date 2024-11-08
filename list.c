/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:57:50 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 09:08:49 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	verify_if_exists(t_var **env, char *key, char *value)
{
	t_var	*temp;

	temp = *env;
	while (temp)
	{
		if (ft_strcmp(temp->key, key) == 0)
		{
			free(temp->value);
			temp->value = ft_strdup(value);
			return (1);
		}
		temp = temp->next;
	}
	return (0);
}

void	add_new_var(t_var **var, char *key, char *value)
{
	t_var	*new;

	if (verify_if_exists(var, key, value))
		return ;
	new = (t_var *)malloc(sizeof(t_var));
	if (!new)
		printf("error allocating memmory");
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = *var;
	*var = new;
}

static void	ft_auxiliary_remove(t_var *temp, char *key, t_var *prev)
{
	while (temp != NULL)
	{
		if (ft_strcmp(key, temp->key) == 0)
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

void	ft_remove_var(char *key, t_var **env)
{
	t_var	*temp;
	t_var	*prev;

	temp = *env;
	prev = NULL;
	if (temp == NULL)
		return ;
	if (ft_strcmp(key, temp->key) == 0)
	{
		*env = temp->next;
		free(temp->key);
		free(temp->value);
		free(temp);
		return ;
	}
	ft_auxiliary_remove(temp, key, prev);
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
