/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 14:35:32 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/25 16:29:15 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_value(const char *str)
{
	char	*equal_sign;

	if (!str)
		return (NULL);
	equal_sign = strchr(str, '=');
	if (!equal_sign)
		return (NULL);
	if (equal_sign[1] == '\0')
	{
		equal_sign = strdup("\"\"");
		return (equal_sign);
	}
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
		general->envs[i] = strdup(ev[i]);
	general->envs[i] = NULL;
}

void	show_vars(t_env **env, int sig)
{
	t_env	*tmp;

	(void)sig;
	tmp = *env;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->value, ""))
			printf("declare -x %s=%s\n", tmp->key, tmp->value);
		else
			printf("declare -x %s\n", tmp->key);
		tmp = tmp->next;
	}
}

void	show_vars_env(t_env **env, int sig)
{
	t_env	*tmp;

	(void)sig;
	tmp = *env;
	if (tmp == NULL)
		return ;
	while (tmp != NULL)
	{
		if (tmp->value != NULL && ft_strcmp(tmp->value, "\"\"") != 0
			&& ft_strlen(tmp->value) > 0)
			printf("%s=%s\n", tmp->key, tmp->value);
		tmp = tmp->next;
	}
}
