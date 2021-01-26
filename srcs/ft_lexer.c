#include "../include/minishell.h"

int		skip_quotes(char const *str, int i)
{
	if (str[i] == '\"')
	{
		i++;
		while (str[i] && str[i] != '\"')
		{
			if (str[i] == '\\' && (str[i + 1] == '\"' || str[i + 1] == '\\'))
				i += 2;
			else
				i++;
		}
	}
	else
	{
		i++;
		while (str[i] && str[i] != '\'')
			i++;
	}
	return (i + 1);
}

int		count_command(char *cmd)
{
	int i;
	int nb_cmd;

	i = 0;
	nb_cmd = 1;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i], "\"\'"))
			i = skip_quotes(cmd, i);
		else if (cmd[i] == ';')
		{
			while (ft_isblank(cmd[i]) || cmd[i] == ';')
				i++;
			if (cmd[i])
				nb_cmd++;
		}
		else
			i++;
	}
	return (nb_cmd);
}

int		find_start(char *cmd, int i, char *sep)
{
	while (cmd && (ft_search(cmd[i], sep)))
		i++;
	while (cmd && ft_isblank(cmd[i]))
		i++;
	return (i);
}

int		find_end(char *cmd, int i, char *sep)
{
	int		j;

	j = 0;
	if (ft_search(cmd[i], sep) || cmd[i] == '\0')
		j++;
	while (cmd && ft_isblank(cmd[i - j]))
		j++;
	return ((i - j) + 1);
}

char	**split_command(char *cmd, int nb_cmd)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	**cmds;

	if (!(cmds = malloc(sizeof(char *) * (nb_cmd + 1))))
		return (NULL);
	i = 0;
	j = 0;
	start = find_start(cmd, i, ";");
	while (cmd && cmd[i] && j < nb_cmd)
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i], "\"\'"))
			i = skip_quotes(cmd, i);
		else if (cmd[i] == ';')
		{
			end = find_end(cmd, i, ";");
			cmds[j] = ft_substr(cmd, start, end - start);
			j++;
			start = find_start(cmd, i, ";");
			i++;
		}
		else
			i++;
	}
	if (j < nb_cmd)
	{
		end = find_end(cmd, i, ";");
		cmds[j] = ft_substr(cmd, start, end - start);
		j++;
	}
	cmds[j] = '\0';
	return (cmds);
}

int		count_tokens(char *cmd)
{
	int	i;
	int nb_tokens;

	i = 0;
	nb_tokens = 1;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i], "\"\'"))
			i = skip_quotes(cmd, i);
		else if (ft_search(cmd[i], "|<>"))
		{
			nb_tokens++;
			if (!ft_strncmp(&cmd[i], ">>", 2))
				i += 2;
			else
				i++;
		}
		else
			i++;
	}
	return (nb_tokens);
}

char	**fill_tokens(char *cmd, int nb_tokens)
{
	int		i;
	int		j;
	int		start;
	int		end;
	char	**tokens;

	if (!(tokens = malloc(sizeof(char *) * (nb_tokens + 1))))
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i], "\"\'"))
			i = skip_quotes(cmd, i);
		else if (cmd[i] == '>')
		{
			if (!(ft_strncmp(&cmd[i], ">>", 2)))
			{
				end = find_end(cmd, i, ">");
				tokens[j] = ft_substr(cmd, start, end - start);
				j++;
				start = i;
				i += 2;
			}
			else
			{
				end = find_end(cmd, i, ">");
				tokens[j] = ft_substr(cmd, start, end - start);
				j++;
				start = i;
				i++;
			}
		}
		else if (ft_search(cmd[i], "|<"))
		{
			end = find_end(cmd, i, "|<");
			tokens[j] = ft_substr(cmd, start, end - start);
			j++;
			start = i;
			i++;
		}
		else
			i++;
	}
	end = find_end(cmd, i, "|<>");
	tokens[j] = ft_substr(cmd, start, end - start);
	j++;
	tokens[j] = NULL;
	return (tokens);
}

char	***split_tokens(char **cmds, int nb_cmds)
{
	int		i;
	int		nb_tokens;
	char	***tokens;

	i = 0;
	if (!(tokens = malloc(sizeof(char **) * (nb_cmds + 1))))
		return (NULL);
	while (cmds && cmds[i] && i < nb_cmds)
	{
		nb_tokens = count_tokens(cmds[i]);
		tokens[i] = fill_tokens(cmds[i], nb_tokens);
		i++;
	}
	tokens[i] = NULL;
	return (tokens);
}

char	***ft_lexer(t_data *data)
{
	char	**cmds;
	char	***tokens;

	printf("\nIN LEXER\n");
	data->nb_cmds = count_command(data->command);
	cmds = split_command(data->command, data->nb_cmds);
	tokens = split_tokens(cmds, data->nb_cmds);
	free_tab_str(cmds);
	return (tokens);
}
