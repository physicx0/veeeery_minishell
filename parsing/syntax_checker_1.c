#include "../includes/minishell.h"

int left_redirection_checker(char *string, int *i, int closed)
{
    int y;

    int reset;

    reset = 0;
    y = 0;
    if ((closed == 1 && string[y] == '<' && string[y - 1] != '\\'))
    {
        y++;
        (*i)++;
        reset++;
        if (string[y] == '<')
        {
            y++;
            (*i)++;
            reset++;
        }
        if (!string[y] || (string[y] == '<' && reset == 2) || string[y] == '>')
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