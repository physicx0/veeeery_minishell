#ifndef MINISHELL_H
#define MINISHELL_H
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <readline/readline.h>
#include <readline/history.h>

typedef enum s_tokenizer 
{
	PIPE,				//0
	APP_REDIRECTION,	//1
	OW_REDIRECTION,		//2
	IN_OPERATOR,		//3
	HEREDOC,			//4
	DQ_STRING,			//5
	SQ_STRING,			//6
	STRING,				//7
	AND,				//8
	OR					//9
} 	t_tokenizer;

typedef struct s_token 
{
    t_tokenizer		word_token;
    char			*word;
    struct s_token	*next;
} 	t_token;

typedef struct s_tree
{
	t_tokenizer		word_token;
	char			*word;
	struct s_tree	*left;
	struct s_tree	*right;
}	t_tree;

t_tree		*parse(t_token *tokens);
t_tree		*create_tree_node(t_token *token);
t_tree		*create_redirection_node(t_token *token);
t_token		*split_token(t_token *tokens, t_token *operator_token);
t_tree		*create_command_subtree(t_token *tokens);
t_tree		*create_redirection_node(t_token *token);
t_tree		*create_operator_node(t_token *token);
t_token		*split_tokens(t_token *tokens, t_token *operator_token);
char		**env_dup(char **env);
void		link_command_node(t_tree *root, t_tree *new_node);
void		link_redirection_to_tree(t_tree *command, t_tree *redirection);
void		print_tree(t_tree *node, int state);
void		ft_free(char **substring, size_t i);
t_tokenizer	identifier(const char *word);
t_token 	*token_initializer(t_tokenizer word_token, const char *word);
t_token		*lexer(char **organized_input);
char		*operation_returner(char *word, int i_word);
int			word_count(char **string);
char		**appender(char **string, int delimiter, int i_word);
char    	**input_organizer(char *parse_string);
void    	parsing_entry(char *parse_string, char **env);
int			ft_strlen(const char *string);
int     	syntax_checker(char *parse_string);
int     	quotes_red_checker(char *string);
int     	left_redirection_checker(char *string, int *i, int closed);
int     	right_redirection_checker(char *string, int *i, int closed);
int     	pipe_checker(char *string, int *i, int closed);
int			ampersand_checker(char *string, int *i, int closed);
char		*ft_substr(char const *s, unsigned int start, size_t len);
char		**commands_spliter(char const *s, char c);
int			ft_strcmp(const char *str1, const char *str2);
char		*ft_strdup(const char *str);

void		exec(t_tree *root, char **env);
#endif