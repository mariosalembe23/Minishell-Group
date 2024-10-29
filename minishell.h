/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:08:32 by msalembe          #+#    #+#             */
/*   Updated: 2024/10/29 08:44:32 by msalembe         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <term.h>
# include <termios.h>
# include <unistd.h>
# define FILE_MODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

typedef struct s_general
{
	char			*initial_command;
	char			**commands;
	char			**envs;
	struct s_token	*token;
	struct s_env	*env;
}					t_general;

typedef struct s_token
{
	int				type_fd;
	char			*content;
	char			**command;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

// BUILD-IN FUNCTIONS
int					ft_echo(char **commands, t_env **env);
int					ft_pwd(char **commands);
int					ft_cd(char **commands);
int					ft_env(char **commands, char **envs, t_env **env);
int					ft_export(char **commands, char **envs, t_env **env);
int					ft_unset(char **commands, t_env **env, char **envs);
int					ft_exit(t_general *general);
int					ft_any_command(void);

// AUXILIARY FUNCTIONS
void				execute_with_flag(char **input, char *key, t_env **env);
void				execute_without_flag(char **input, char *key, t_env **env);
char				*find_value(const char *str);
char				*find_key(const char *str);
void				ft_copy_vars(t_general *general, char **ev);
void				show_vars(t_env **env, int sig);
void				add_new_var(t_env **env, char *key, char *value);
void				show_vars_env(t_env **env, int sig);
void				ft_remove_var(char *input, t_env **env);
void				show_unique_var(char *key, t_env **env, char **input,
						int i);
void				ft_verify_signals(char **av, int ac);

#endif