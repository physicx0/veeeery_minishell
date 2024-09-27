#include "../includes/minishell.h"

// void    link_free(t_token *head)
// {
//     t_token *holder;
//     while (head)
//     {
//         free(head->word);
//         holder = head;
//         head = head->next;
//         free(holder);
//     }
// }

// void    ft_free_env(char **env)
// {
//     int i = 0;
//     while (env[i])
//     {
//         free(env[i]);
//         i++;
//     }
//     free(env[i]);
//     free(env);
// }

int main(int ac, char *av[], char *env[])
{
    char **our_env;

    our_env = env_dup(env);
    while (1)
        parsing_entry(readline("0xhb_shell$ "), our_env);
}

void    parsing_entry(char *parse_string, char **env)
{
    t_token *head;
    t_tree  *root;
    char **organized_input;

    if (!parse_string)
        exit(1);
    else if (syntax_checker(parse_string))
    {
        printf("syntax error\n");
        free(parse_string);
        return;
    }
    organized_input = input_organizer(parse_string);
    head = lexer(organized_input);
    expand_flager(head, env);
    root = parse(head);
    exec(root, env);
}

char    *trimted_returner(char *string)
{
    printf("(%s)\n", string);
    return NULL;
}

void    content_trimer(t_token *head)
{
    t_token *current;
    current = head;
    int i;

    while (current)
    {
        i = 0;
        while(current->word[i])
        {
            if ((current->word[i] == 34 || current->word[i] == 39) && i != 0 && current->word[i - 1] != '\\')
            {
                current->word = trimted_returner(current->word);
                trimted_returner(current->word);
                break;
            }
            i++;
        }
        current = current->next;
    }
}

t_token	*lexer(char **organized_input)
{
	int i;
	t_token *head;
	t_token	*current;
	t_token *new_token;
    t_tokenizer word_token;

	i = 0;
	head = NULL;

	while(organized_input[i])
	{
		word_token = identifier(organized_input[i]);
        new_token = token_initializer(word_token, organized_input[i]);
	    if (!head)
        {
            head = new_token;
            current = new_token;
        }
        else
        {
            current->next = new_token;
            current = new_token;
        }
        free(organized_input[i]);
        i++;
	}
    free(organized_input[i]);
    free(organized_input);
    return(head);
}

char    **input_organizer(char *parse_string)
{
    char **splited_command;
    int i;
    int y;
    char quote;
    int closed;

    closed = 1;
    quote = 0;
    y = 0;
    splited_command = commands_spliter(parse_string, ' ');
    i = 0;
    while(splited_command[i])
    {
        y = 0;
        if (identifier(splited_command[i]) == STRING || identifier(splited_command[i]) == SQ_STRING 
            || identifier(splited_command[i]) == DQ_STRING)
        {
            while(splited_command[i][y])
            {
                if ((splited_command[i][y] == 39 || splited_command[i][y] == 34) && closed == 1)
                {
                    closed = 0;
                    quote = splited_command[i][y];
                }
                else
                {
                    if (splited_command[i][y] == quote)
                        closed = 1;
                }
                if ((splited_command[i][y] == '|' && splited_command[i][y - 1] != '\\' && closed == 1)
                    || (splited_command[i][y] == '>' && splited_command[i][y - 1] != '\\' && closed == 1)
                    || (splited_command[i][y] == '<' && splited_command[i][y - 1] != '\\' && closed == 1))
                {
                    splited_command = appender(splited_command, i, y);
                    i = 0;
                    break;
                }
                y++;
            }
        }
        i++;
    }
    return (splited_command);
}
