/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 05:44:10 by amaaouni          #+#    #+#             */
/*   Updated: 2024/09/27 06:16:08 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../includes/minishell.h"
# include <fcntl.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_path
{
	char	*path;
	char	*pathname;
	char	**env_paths;
	char	**env_to_free;
}			t_path;

void		simple_cmd(t_tree *root, char **env);
char		**ft_split(char const *s, char c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		ft_putstr_fd(char *s, int fd);
char		*exec_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
void		execute(char **arg, char **env);
char		*check_path(char *cmd, char *ev[]);
int			free_split(char **arr);
int			is_redirction(char *arg);
char		**filter_arg(char **arg);
char		**generate_arg(t_tree *root, char **env);
void		redirect(char *filename, int mode);
void		redirect_io(char **arg);

#endif
