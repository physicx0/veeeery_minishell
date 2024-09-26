#include "../includes/minishell.h"

int quotes_red_checker(char *string)
{
    int i;
    char quote;
    int closed;

    i = 0;
    closed = 1;

    while (string[i])
    {
        if (left_redirection_checker(&string[i], &i, closed) || right_redirection_checker(&string[i], &i, closed)
            || pipe_checker(&string[i], &i, closed) || ampersand_checker(&string[i], &i, closed))
            return (0);
        if ((string[i] == 39 || string[i] == 34) && closed == 1)
        {
            if (string[i - 1] != '\\')
                closed = 0;
            quote = string[i];
        }
        else
        {
            if (string[i] == quote && string[i - 1] != '\\')
                closed = 1;
        }
        i++;
    }
    return (closed);
}

int ampersand_checker(char *string, int *i, int closed)
{
    int y;

    y = 0;
    if ((closed == 1 && string[y] == '&' && string[y - 1] != '\\'))
        return (1);
    return (0);
}
int right_redirection_checker(char *string, int *i, int closed)
{
    int y;
    int reset;

    reset = 0;
    y = 0;
    if ((closed == 1 && string[y] == '>' && string[y - 1] != '\\'))
    {
        y++;
        (*i)++;
        reset++;
        if (string[y] == '>')
        {
            y++;
            (*i)++;
            reset++;
        }
        if (string[y] == '\0' || (string[y] == '>' && reset == 2) || string[y] == '<')
            return (1);
        while (string[y] == ' ' || string[y] == '\\' 
            || string[y] == '>' || !string[y] || string[y] == '&'
            || string[y] == '|' || string[y] == '<'
            || !string[y])
        {
            if ((string[y] == '\0') || (string[y] == '<' && string[y - 1] != '\\') 
                || (string[y] == '&' && string[y - 1] != '\\') || (string[y] == '>' && string[y - 1] != '\\')
                ||  (string[y] == '|' && string[y - 1] != '\\'))
                    return (1);
            y++;
            (*i)++;
        }
    }
    return (0);
}

int     pipe_checker(char *string, int *i, int closed)
{
    int y;

    y = 0;
    if ((closed == 1 && string[y] == '|' && string[y - 1] != '\\'))
    {
        y++;
        (*i)++;
        if (string[y] == '\0' || string[y] == '|')
            return (1);
        while (string[y] == ' ' || string[y] == '\\' 
            || string[y] == '|' || !string[y] || string[y] == '&')
        {
            if ((string[y] == '\0') || (string[y] == '|' && string[y - 1] != '\\') 
                || (string[y] == '&' && string[y - 1] != '\\'))
                {
                    printf("salut");
                    return (1);
                }
            y++;
            (*i)++;
        }
    }
    return (0);
}

int syntax_checker(char *parse_string)
{
    if (!quotes_red_checker(parse_string))
        return (1);
    return (0);
}