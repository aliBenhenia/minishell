# include <unistd.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdio.h>
# include <signal.h>
# include <fcntl.h>
# include <limits.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

char *get_home(char **env)
{
    int i = 0;
    while (env[i])
    {
        if (!strcmp(env[i++], "name"))
            return (env[i]);
    }
    return (NULL);
}

void    ft_cd(char *path, char **env)
{
    if (!path)
    {
        char *home = get_home(env);
        if (chdir(home) == - 1)
            perror("cd");
    }
    else
    {
        if (chdir(path) == - 1)
            perror("cd");
    }
}