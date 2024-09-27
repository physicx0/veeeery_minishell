/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbelarra42 <bbelarra@student.1337.ma>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/27 10:12:34 by bbelarra42        #+#    #+#             */
/*   Updated: 2024/09/27 12:09:29 by bbelarra42       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

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

typedef struct s_token
{
	t_tokenizer		word_token;
	char			*word;
	struct s_token	*next;
}					t_token;

typedef struct s_tokvar
{
	int				i;
	t_token			*head;
	t_token			*current;
	t_token			*new_token;
	t_tokenizer		word_token;
}					t_tokvar;

typedef struct s_tree
{
	t_tokenizer		word_token;
	char			*word;
	struct s_tree	*left;
	struct s_tree	*right;
}					t_tree;

t_tree				*parse(t_token *tokens);
t_tree				*create_tree_node(t_token *token);
t_tree				*create_redirection_node(t_token *token);
t_token				*split_token(t_token *tokens, t_token *operator_token);
t_tree				*create_command_subtree(t_token *tokens);
t_tree				*create_redirection_node(t_token *token);
t_tree				*create_operator_node(t_token *token);
t_token				*split_tokens(t_token *tokens, t_token *operator_token);

char				*ft_strjoin(char *s1, char *s2);
void				expand_flager(t_token *head, char **env);
char				*expand(char *env_var, char **env, int i);
int					env_length(char *env);
char				*value_returner(char *search, char **env);
char				*exporter(char *search, char *env_line);
char				*ft_strtrim(char *s1, char *set);
void				content_trimer(t_token *head);
char				*trimed_returner(char *string);

void				link_free(t_token *head);
char				**env_dup(char **env);
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
void				parsing_entry(char *parse_string, char **env);
int					ft_strlen(const char *string);
int					syntax_checker(char *parse_string);
int					quotes_red_checker(char *string);
int					left_redirection_checker(char *string, int *i, int closed);
int					right_redirection_checker(char *string, int *i, int closed);
int					pipe_checker(char *string, int *i, int closed);
int					ampersand_checker(char *string, int *i, int closed);
char				*ft_substr(char const *s, unsigned int start, size_t len);
char				**commands_spliter(char const *s, char c);
int					ft_strcmp(const char *str1, const char *str2);
char				*ft_strdup(const char *str);

void				exec(t_tree *root, char **env);
#endif