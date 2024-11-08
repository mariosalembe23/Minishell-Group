/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msalembe <msalembe@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 19:08:32 by msalembe          #+#    #+#             */
/*   Updated: 2024/11/08 14:02:47 by msalembe         ###   ########.fr       */
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
# include <stdbool.h>
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
# define t_file "/tmp/minishel_trash.tmp"

typedef struct s_general
{
	char			*initial_command;
	char			**commands;
	char			**envs;
	struct s_token	*token;
	struct s_env	*env;
	struct s_var	**var;
	struct s_filter	*filter;
}					t_general;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}					t_env;

typedef struct s_var
{
	char			*key;
	char			*value;
	struct s_var	*next;
}					t_var;

typedef struct s_token
{
	int				seg;
	int				type_fd;
	int				quoted;
	char			*content;
	char			**command;
	struct s_token	*next;
	struct s_token	*prev;
}					t_token;

typedef struct s_words
{
	char			*word;
	struct s_words	*next;
}					t_words;

typedef struct s_filter
{
	char			*filtered;
	int				quote;
	struct s_filter	*next;
}					t_filter;

// BUILD-IN FUNCTIONS
int					ft_echo(char **commands, t_env **env, int sig);
int					ft_pwd(char **commands, int sig);
int					ft_cd(char **commands, int sig);
int					ft_env(char **commands, t_var **var, int sig);
int					ft_export(char **commands, t_general *general, int sig);
int					ft_unset(char **commands, t_var **env);
int					ft_exit(t_general *general, int sig, char **commands);
int					ft_any_command(char *str);

// AUXILIARY FUNCTIONS
void				execute_with_flag(char **input, char *key, t_env **env);
void				execute_without_flag(char **input, char *key, t_env **env);
char				*find_value(const char *str);
char				*find_key(const char *str);
void				ft_copy_vars(t_general *general, char **ev);
void				show_vars(t_var **env, int sig);
void				add_new_var(t_var **env, char *key, char *value);
void				show_vars_env(t_var **env, int sig);
void				ft_remove_var(char *input, t_var **env);
void				show_unique_var(char *key, t_env **env, char **input,
						int i);
void				ft_verify_signals();
void				free_mat(char **mat);
int					matlen(char **mat);
char				*first_word(char *str, char delim);
void				extract_tokens(t_token **head, t_general *general);
int					process_command(t_token **head);
char				*join_struct(t_filter **head);
void				alloc_filter_1(t_filter **head, t_filter **past, char *str,
						int *i);
void				alloc_filter_2(t_filter **head, t_filter **past, char *str,
						int *i);
void				create_filter(char *str, t_filter **head);
char				*extract_quote_2(char *str);
char				*extract_quote_1(char *str);
char				*extract_quote_0(char *str);
void				alloc_filter_3(t_filter **head, t_filter **past, char *str,
						int *i);

// TOKEN FUNCTIONS
char				*ft_strndup(const char *str, size_t n);
int					get_type_fd(const char *operator);
char				*filter_token(char *token);
void				tokenize_utils(char *str, int *start, t_token **head,
						int *i);
void				tokenize(char *str, t_token **head);
void				free_tokens(t_token *head);
int					matlen(char **mat);
void				free_mat(char **mat);
void				ft_reader(t_words **words, char *stop_str);
void				reader(char *stop_str, int type, int fd);
void				initial_case(int prev_fd, t_token *temp, int pipefd[2]);
void				case_type_2(t_token *temp);
void				clean_node(t_token *temp);
void				case_type_3_utils(t_token *temp, char **temp_mat, int t_fd);
void				case_type_3(t_token *temp, int pipefd[2]);
void				case_type_4(t_token *temp);
void				exec_son_pid(t_token *temp, int *pipefd,
						t_general *general);
void				exec_father(int *prev_fd, t_token *temp, int *pipefd,
						pid_t pid, t_general *general);
int					check_seg(t_token *temp);
void				exec_command(t_token **head, t_general *general);
void				add_word(t_words **wds, char *value);
void				append_node(t_token **head, char *content, int type_fd);
void				ft_add_var(t_var **var, char **ev);

void				init_proccess(t_general *general);
void				write_in_file(int status);

#endif