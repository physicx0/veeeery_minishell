/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amaaouni <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 18:57:15 by amaaouni          #+#    #+#             */
/*   Updated: 2024/10/13 18:20:17 by amaaouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

# include "../includes/minishell.h"
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_cmd
{
	char	**arg;
	char	**fltr_arg;
	char	*path;
	int		pid;
	int		wstatus;
}			t_cmd;

typedef struct s_path
{
	char	cwd[PATH_MAX];
	char	*path;
	char	*pathname;
	char	**env_paths;
	char	**env_to_free;
}			t_path;

typedef struct s_pipe
{
	int		fd[2];
	int		pid;
	int		prv_fd;
	int		wstatus;
	t_tree	*node;
	t_env	**env_s;
}			t_pipe;

void		simple_cmd(t_tree *root, t_glob *glob);
char		**ft_split(char const *s, char c);
char		*ft_strnstr(const char *haystack, const char *needle, size_t len);
void		ft_putstr_fd(char *s, int fd);
char		*exec_strjoin(char const *s1, char const *s2);
char		*ft_strchr(const char *s, int c);
void		execute(char **arg, char **env);
char		*check_path(char *cmd, t_glob *glob);
int			free_split(char **arr);
int			is_redirction(char *arg);
char		**filter_arg(char **arg);
char		**generate_arg(t_tree *root);
int			redirect(char *filename, int mode);
int			redirect_io(char **arg);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
int			ft_echo(char **arg);
int			ft_cd(char **arg, t_env **env);
int			ft_pwd(void);
int			ft_exit(char **arg, int status);
int			env_size(t_env *lst);
void		env_add_back(t_env **lst, t_env *new_node);
t_env		*env_last(t_env *lst);
t_env		*env_new(char *content);
char		**env_to_arr(t_env *env);
int			ft_export(char **arg, t_env **env);
int			ft_env(t_env *env);
int			ft_unset(char **args, t_env **env);
char		*std_strjoin(char const *s1, char const *s2);
int			ft_isalpha(int c);
void		built_cmd(char **arg, char **farg, t_glob *glob);
int			is_builtin(char *cmd);
int			ft_pipe(int fd[]);
int			ft_fork(void);
int			ft_execve(char *path, char **arg, char **env);
void		child_redirect(t_pipe *strc);
void		parent_redirect(t_pipe *strc);
int			left_cmd(t_tree *root, t_glob *glob, t_pipe *strc);
int			right_cmd(t_tree *root, t_glob *glob, t_pipe *strc);
void		pipe_cmd(t_tree *root, t_glob *glob);
void		exit_status(int wstatus, t_glob *glob);
char		*find_path(t_env *env_list);
int			no_prms(char *cmd, t_glob *glob);
int			no_path(char *cmd, t_glob *glob);
int			no_cmd(char *cmd, t_glob *glob);
int			is_dir(char *cmd, t_glob *glob);
int			check_var(char *arg);
int			strict_strncmp(char *s1, char *s2);
void		ft_tolower(char *c);
int			ft_isnum(int c);
int			ft_isdigit(int c);
void		ft_putstr_fd(char *s, int fd);

#endif