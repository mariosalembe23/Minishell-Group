/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/08 14:42:00 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:52:30 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	extract_utils(char *f_value)
{
	int	fd;

	if (access(".data", F_OK) == -1)
	{
		fd = open(".data", O_WRONLY | O_CREAT | O_TRUNC, FILE_MODE);
		write(fd, "0", 1);
		close(fd);
	}
	else
	{
		fd = open(".data", O_RDONLY);
		read(fd, f_value, 4);
		close(fd);
	}
}

static char	*extract_case(char **str)
{
	char	*f_value;
	char	*value;
	char	*temp;
	char	*temp2;
	int		i;

	f_value = (char *)malloc(sizeof(char) * 4);
	f_value[3] = '\0';
	extract_utils(f_value);
	value = f_value;
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
	return (*str);
}

static void	extract_value(char **str, char *env)
{
	char	*value;
	char	*temp;
	char	*temp2;
	int		i;

	value = find_value(env);
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

char	*apply_var_value(char *str, char *pos, t_general *general)
{
	char	*arg;
	int		i;
	char	*key;

	arg = first_word(pos + 1, ' ');
	i = -1;
	while (general->envs[++i])
	{
		key = find_key(general->envs[i]);
		if (pos[1] == '$')
		{
			extract_pid(&str);
			return (str);
		}
		else if (pos[1] == '?')
			return (extract_case(&str));
		else if (ft_strcmp(key, arg) == 0)
		{
			extract_value(&str, general->envs[i]);
			return (ft_strdup(str));
		}
		free(key);
	}
	free(arg);
	return (str);
}
