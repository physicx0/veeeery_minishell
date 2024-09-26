#include "../includes/minishell.h"

int env_length(char *env)
{
    int i;
    i = 0;
    while (env[i] && env[i] != 32 && env[i] != '$' 
        && env[i] != 34 && env[i] != 39 && env[i] != '=')
        i++;
    return i;
}
char    *exporter(char *search, char *env_line)
{
    int i;
    i = 0;
    while (search[i] == env_line[i])
        i++;
    if (!search[i] && env_line[i] == '=')
        return (ft_substr(env_line, i + 1, ft_strlen(env_line)));
    return (NULL);
}

char    *value_returner(char *search, char **env)
{
    char    *exported;
    int     i;
    exported = NULL;

    i = 0;
    while (env[i])
    {
        exported = exporter(search, env[i]);
        if (exported)
            break;
        i++;
    }
    free(search);
    return (exported);
}

char    *expand(char *env_var, char **env, int i)
{
    char *search;
    char *first_part;
    char *second_part;
    char *test;

    search = ft_substr(env_var, i + 1, env_length(&env_var[i + 1]));
    
    test = ft_strdup(search);

    if (!env_var[i + ft_strlen(search) + 1] && i != 0)
    {
        first_part = ft_substr(env_var, 0, i);
        search = value_returner(search, env);
        if (search)
            return ft_strjoin(first_part, search);
        return (first_part);
    }
    else if (env_var[i + ft_strlen(search) + 1] && i != 0)
    {
        first_part = ft_substr(env_var, 0, i);
        search = value_returner(search, env);
        if (search)
        {
            second_part = ft_substr(env_var, ft_strlen(first_part) + ft_strlen(test) + 1, ft_strlen(env_var)); 
            return ft_strjoin(ft_strjoin(first_part, search), second_part);
        }
        second_part = ft_substr(env_var, ft_strlen(first_part), ft_strlen(env_var));
        return ft_strjoin(first_part, second_part);
    }
    else
    {
        search = value_returner(search, env);
        if (search)
            return search;
    }
    return (NULL);
}

void    expand_flager(t_token *head, char **env)
{
    t_token *current;
    int     i;
    char quote;
    int closed;
    int expandable;
    char *exported;
    
    expandable = 1;
    closed = 1;
    quote = 0;
    current = head;

    while (current)
    {
        i = 0;
        while (current->word[i])
        {
            if ((closed == 1 || expandable == 1) && current->word[i] == '$' && current->word[i - 1] != '\\' 
                && current->word[i + 1] != '$')
            {
                exported = expand(current->word, env, i); 
                if (!exported)
                {
                    if (i == 0)
                    {
                        i += env_length(&current->word[i + 1]);
                        if (!current->word[i])
                        {
                            current->word = ft_strdup("");
                            current->word_token = EMPTY;
                            break;
                        }
                    }
                }
                current->word = exported;
                current = head;
                break;
            }
            if ((current->word[i] == 39 || current->word[i] == 34) && closed == 1)
            {
                quote = current->word[i];
                if (i == 0 || current->word[i - 1] != '\\')
                {
                    if (quote == 39)
                        expandable = 0;
                    else if (quote == 34)
                        expandable = 1;
                    closed = 0;
                }
            }
            else
            {
                if (current->word[i] == quote && current->word[i - 1] != '\\')
                    closed = 1;
            }
            i++;
        }
        current = current->next;
    }
}