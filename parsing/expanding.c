#include "../includes/minishell.h"

int env_length(char *env)
{
    int i;
    i = 0;
    while (env[i] && env[i] != 32 && env[i] != '$' 
        && env[i] != 34 && env[i] != 39 && env[i] != '=' && env[i] != '\\')
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
    char *var;
    search = ft_substr(env_var, i + 1, env_length(&env_var[i + 1]));
    var = ft_strdup(search);

    if (!env_var[i + ft_strlen(search) + 1] && i != 0)
    {
        first_part = ft_substr(env_var, 0, i);
        search = value_returner(search, env);
        if (search)
            return free(var), free(env_var), ft_strjoin(first_part, search);
        return free(var), free(env_var), (first_part);
    }
    else if (env_var[i + ft_strlen(search) + 1] && i != 0)
    {
        first_part = ft_substr(env_var, 0, i);
        search = value_returner(search, env);
        if (search)
        {
            second_part = ft_substr(env_var, ft_strlen(first_part) + ft_strlen(var) + 1, ft_strlen(env_var)); 
            return free(var), free(env_var), ft_strjoin(ft_strjoin(first_part, search), second_part);
        }
        second_part = ft_substr(env_var, ft_strlen(first_part) + ft_strlen(var) + 1, ft_strlen(env_var));
        return free(var), free(env_var), ft_strjoin(first_part, second_part);
    }
    else if (i == 0 && !env_var[i + ft_strlen(search) + 1])
    {
        search = value_returner(search, env);
        if (search)
            return free(var), free(env_var), (search);
        return free(var), free(env_var), NULL;
    }
    search = value_returner(search, env);
    first_part = ft_substr(env_var, ft_strlen(var) + 1, ft_strlen(env_var));
    if (search)
        return free(var), free(env_var), ft_strjoin(search, first_part);
    return free(var), free(env_var), first_part;
}

void    expand_flager(t_token *head, char **env)
{
    t_token *current;
    int     i;
    char quote;
    int closed;
    int expandable;
    char *exported;
    int flager;

    flager = 0;
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
                    current->word_token = EMPTY;
                    current->word = ft_strdup("");
                    current = head;
                    flager = 1;
                    break;
                }
                current->word = exported;
                current = head;
                flager = 1;
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
        if (flager == 0)
            current = current->next;
        flager = 0;
    }
}