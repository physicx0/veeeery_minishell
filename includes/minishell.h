/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:12:34 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/10/17 04:56:52 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

extern int			g_var;

typedef enum s_tokenizer
{
	PIPE,
	APP_REDIRECTION,
	OW_REDIRECTION,
	IN_OPERATOR,
	HEREDOC,
	DQ_STRING,
	SQ_STRING,
	STRING,
	EMPTY,
}					t_tokenizer;

typedef struct s_env
{
	char			*env_line;
	struct s_env	*next;
}					t_env;

typedef struct s_glob
{
	t_env			**env;
	int				exit_status;
}					t_glob;

typedef struct s_append
{
	int				i;
	char			**orgnized_one;
	int				size;
	int				y;
}					t_append;

typedef struct s_token
{
	t_tokenizer		word_token;
	char			*word;
	struct s_token	*next;
}					t_token;

typedef struct s_trim
{
	t_token			*current;
	int				i;
	int				y;
	char			*trimed;
	int				closed;
}					t_trim;

typedef struct s_expan
{
	char			*search;
	char			*first_part;
	char			*second_part;
	char			*var;
}					t_expan;

typedef struct s_splvar
{
	size_t			words;
	size_t			i;
	int				y;
	int				closed;
	char			quote;
}					t_splvar;

typedef struct s_tokvar
{
	int				i;
	t_token			*head;
	t_token			*current;
	t_token			*new_token;
	t_tokenizer		word_token;
}					t_tokvar;

typedef struct s_orgvar
{
	int				i;
	int				y;
	char			quote;
	int				closed;
	char			**splited_command;
}					t_orgvar;

typedef struct s_tree
{
	t_tokenizer		word_token;
	char			*word;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

typedef struct s_parse
{
	t_tree			*root;
	t_tree			*operator_node;
	t_token			*pipe_operator;
	t_token			*current_token;
}					t_parse;

typedef struct s_fla
{
	t_token			*current;
	int				i;
	char			quote;
	int				closed;
	char			*exported;
	int				flager;
}					t_fla;

typedef struct s_entry
{
	t_token			*new;
	t_token			*head;
	t_token			*prev;
	t_tree			*root;
	char			**organized_input;
}					t_entry;

typedef struct s_herh
{
	char	*file;
	t_token	*looper;
	t_token	*looper1;
	t_token	*looper2;
	int		c;
}					t_herh;

void				entry_helper(t_entry *var_ent, t_glob *glob,
						char *parse_string);
void				free_tree(t_tree *node);
t_tree				*parse(t_token *tokens, int flager);
t_tree				*create_tree_node(t_token *token);
t_token				*split_token(t_token *tokens, t_token *operator_token);
t_tree				*create_command_subtree(t_token *tokens, int flager);
t_tree				*create_operator_node(t_token *token);
t_token				*split_tokens(t_token *tokens, t_token *operator_token);
t_env				*new_link(char *string);
t_token				*dup_head(t_token *head);
t_token				*dup_linker(t_token *head);
void				fla_helper_1(t_token *head, t_env *env, t_fla *var_f);
int					fla_helper(t_token *head, t_env *env, t_fla *var_f,
						t_glob *glob);
char				*expan_helper_1(char *env_var, t_glob *glob, int i,
						t_expan *v_exp);
char				*expan_helper_2(char *env_var, t_glob *glob, int i,
						t_expan *v_exp);
char				*ft_strjoin(char *s1, char *s2);
void				expand_flager(t_token *head, t_env *env, t_glob *glob);
int					expand_triger(char *line);
char				*heredoc_expand(char *string, t_env *env, t_glob *glob);
char				*expand(char *env_var, t_env *env, int i, t_glob *glob);
int					env_length(char *env);
void				trim_whiler(t_trim *trim, char *c);
char				*value_returner(char *search, t_env *env, t_glob *glob);
char				*exporter(char *search, char *env_line);
void				content_trima(t_token *head);
int					trim_flager(char *string);
int					left_red_helper(char *string, int y, int *i);
void				count_helper(t_splvar *sv, char const *s, char delimiter);
void				fill_helper(t_splvar *sv, int delimiter, char **substring,
						const char *s);
void				append_alloc_cp(t_append *ap, char **string, int delimiter,
						int i_word);
void				init_orgvar(t_orgvar *ov, char *parse_string);
void				close_open(t_orgvar *ov);
int					closer(t_orgvar *ov);
int					string_checker(t_orgvar *ov);
int					append_caller(t_orgvar *ov);
int					caller(char *string, int y, int *i);
void				link_free(t_token *head);
t_env				*env_dup(char **env);
void				link_command_node(t_tree *root, t_tree *new_node);
void				link_redirection_to_tree(t_tree *command,
						t_tree *redirection);
void				print_tree(t_tree *node, int state);
void				ft_free(char **substring, size_t i);
t_tokenizer			identifier(char *word);
t_token				*token_initializer(t_tokenizer word_token, char *word);
t_token				*lexer(char **organized_input);
char				*operation_returner(char *word, int i_word);
int					word_count(char **string);
char				**appender(char **string, int delimiter, int i_word);
char				**input_organizer(char *parse_string);
t_tree				*parsing_entry(char *parse_string, t_glob *glob);
int					ft_strlen(const char *string);
int					syntax_checker(char *parse_string);
int					check_help(char *string, int i, int closed);
int					red_helper(char *string, int y);
int					quotes_red_checker(char *string);
int					left_redirection_checker(char *string, int *i, int closed);
int					right_redirection_checker(char *string, int *i, int closed);
int					pipe_checker(char *string, int *i, int closed);
int					ampersand_checker(char *string, int *i, int closed);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**commands_spliter(char const *s, char c);
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strdup(const char *str);
char				*ft_itoa(int n);
void				exec(t_tree *root, t_glob *glob);
void				here_doc(t_entry *var_ent, t_glob *glob);
void				setup_main_signals(void);
void				main_sigquit(int sigquit);
void				main_sigint(int sigint);
void				reset_signals(void);
void				hdoc_signals(void);
void				rl_replace_line(const char *string, int clear_undo);
char				*add_char(char *line, char c);
#endif
