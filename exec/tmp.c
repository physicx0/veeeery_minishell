void    execute_left(t_tree *root, t_env *env, int fd[])
{
    dup2(fd[1], 1);
    close(fd[0]);
    exec(root, env);
    exit(1);
}

void    execute_right(t_tree *root, t_env *env, int fd[])
{
    dup2(fd[0], 0);
    close(fd[1]);
    exec(root, env);
    exit(1);
}

void    exec(t_tree *root, t_env *env)
{
    static int  exit_status = 0;
    int         fd[2];

    if (root == NULL)
        return ;
    if (root->word_token == PIPE)
    {
        pipe(fd);
        if (fork() == 0)
            execute_left(root->left, env, fd);
        if (fork() == 0)
            execute_right(root->right, env, fd);
        close(fd[0]);
        close(fd[1]);
        wait(&exit_status);
        wait(&exit_status);
    }
    else
    {
        simple_cmd(root, env);
    }
    return ;
}

