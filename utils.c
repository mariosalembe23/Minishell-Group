/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:35:32 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 13:16:46 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_value(const char *str)
{
	char	*equal_sign;

	if (!str)
		return (NULL);
	equal_sign = ft_strchr(str, '=');
	if (!equal_sign)
		return (NULL);
	return (equal_sign + 1);
}

char	*find_key(const char *str)
{
	char	*equal_sign;
	size_t	key_length;
	char	*key;

	if (!str)
		return (NULL);
	equal_sign = strchr(str, '=');
	if (equal_sign)
		key_length = equal_sign - str;
	else
		key_length = strlen(str);
	key = (char *)malloc(key_length + 1);
	ft_strncpy(key, str, key_length);
	key[key_length] = '\0';
	return (key);
}

void	ft_copy_vars(t_general *general, char **ev)
{
	int	i;
	int	count;

	i = -1;
	count = -1;
	while (ev[++count])
		;
	general->envs = malloc(sizeof(char *) * (count + 1));
	while (ev[++i])
		general->envs[i] = ft_strdup(ev[i]);
	general->envs[i] = NULL;
}

void	show_vars(t_var **env, int sig)
{
	t_var	*tmp;

	(void)sig;
	tmp = *env;
	if (tmp == NULL)
		printf("No variables\n");
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
			printf("declare -x %s=\"%s\"\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	show_vars_env(t_var **env, int sig)
{
	t_var	*tmp;

	tmp = *env;
	(void)sig;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		if (tmp->value != NULL)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
