#include "../include/minishell.h"

t_data      *init_data(char **env)
{
    t_data   *data;

    if (!(data = malloc(sizeof(t_data))))
        return (NULL);
    data->my_env = get_env(env);
    data->prompt = get_env_var(data->my_env, "USER");
    if (!(data->error = malloc(sizeof(t_error))))
        return (NULL);
    return (data);
}
