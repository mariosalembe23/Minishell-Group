/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   extract.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 15:00:52 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:12:47 by msalembe         ###   ########.fr       */
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
void	extract_case(char **str)
{
	int		fd;
	char	*f_value;
	char	*value;
	char	*temp;
	char	*temp2;
	int		i;

	f_value = (char *)malloc(sizeof(char) * 4);
	f_value[3] = '\0';
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
	close(fd);
}
void	extract_value(char **str, char *env)
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
	i = 0;
	while (general->envs[i])
	{
		key = find_key(general->envs[i]);
		if (pos[1] == '$')
		{
			extract_pid(&str);
			return (str);
			break ;
		}
		else if (pos[1] == '?')
		{
			extract_case(&str);
			return (str);
			break ;
		}
		else if (ft_strcmp(key, arg) == 0)
		{
			extract_value(&str, general->envs[i]);
			return (ft_strdup(str));
			break ;
		}
		free(key);
		i++;
	}
	free(arg);
	return (str);
}

void	extract_quote(t_filter **tmp, t_general *general)
{
	t_filter	*cur;
	char		*str;
	char		*new_content;
	int			i;

	cur = *tmp;
	while (cur)
	{
		if (cur->quote == 2 || cur->quote == 0)
		{
			str = cur->filtered;
			i = -1;
			while (str[++i])
			{
				if (str[i] == '$')
				{
					new_content = apply_var_value(cur->filtered, &str[i],
							general);
					if (new_content != cur->filtered)
					{
						cur->filtered = new_content;
						str = cur->filtered;
						i = -1;
					}
				}
			}
		}
		printf("filtered: %s\n", cur->filtered);
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
