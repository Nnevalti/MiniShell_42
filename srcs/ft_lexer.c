#include "../include/minishell.h"

int		ft_isblank(char c)
{
	return (c == ' ' || c == '\t');
}

int		ft_search(char c, char *str)
{
	int i;

	i = 0;
	while(str[i])
	{
		if (str[i] == c)
			return(1);
		i++;
	}
	return(0);
}

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
		else if (ft_search(cmd[i],"\"\'"))
			i = skip_quotes(cmd,i);
		else if (cmd[i] == ';')
		{
			nb_cmd++;
			i++;
		}
		else
			i++;
	}
	return(nb_cmd);
}

int		find_start(char *cmd, int i, char *sep)
{
	while (ft_search(cmd[i], sep))
		i++;
	while(cmd && ft_isblank(cmd[i]))
		i++;
	return (i);
}

int		find_end(char *cmd, int i, char *sep)
{
	int		j;

	j = 0;
	if (ft_search(cmd[i], sep) || cmd[i] == '\0')
		j++;
	while(cmd && ft_isblank(cmd[i - j]))
		j++;
	return ((i - j) + 1);
}

char	**split_command(char *cmd, int nb_cmd)
{
	int i;
	int j;
	int start;
	int end;
	char **cmds;

	if(!(cmds = malloc(sizeof(char *) * nb_cmd + 1)))
		return(NULL);
	i = 0;
	j = 0;
	start = find_start(cmd, i, ";");
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i],"\"\'"))
			i = skip_quotes(cmd,i);
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
	end = find_end(cmd, i, ";");
	cmds[j] = ft_substr(cmd, start, end - start);
	j++;
	cmds[j] = NULL;
	return(cmds);
}

int		count_tokens(char *cmd)// count sep | < > >>
{
	int	i;
	int nb_tokens;

	i = 0;

	i = 0;
	nb_tokens = 1;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i],"\"\'"))
			i = skip_quotes(cmd,i);
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
	return(nb_tokens);
}

char	**fill_tokens(char *cmd, int nb_tokens)// split sep | < > >>
{
	int i;
	int j;
	int start;
	int end;
	char **tokens;

	if (!(tokens = malloc(sizeof(char *) * nb_tokens + 1)))
		return (NULL);
	i = 0;
	j = 0;
	start = 0;
	while (cmd && cmd[i])
	{
		if (cmd[i] == '\\')
			i += 2;
		else if (ft_search(cmd[i],"\"\'"))
			i = skip_quotes(cmd,i);
		else if (ft_search(cmd[i], "|<>"))
		{
			end = find_end(cmd, i, "|<>");
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
	return(tokens);
}

char		***split_tokens(char **cmds, int nb_cmds)
{
	int		i;
	int		nb_tokens;
	char	***tokens;

	i = 0;
	if (!(tokens = malloc(sizeof(char **) * nb_cmds + 1)))
		return (NULL);
	while (cmds && cmds[i])
	{
		nb_tokens = count_tokens(cmds[i]);
		tokens[i] = fill_tokens(cmds[i], nb_tokens);
		i++;
	}
	tokens[i] = NULL;
	return(tokens);
}

char		***ft_lexer(t_data *data)
{
	printf("IN LEXER : %s\n", data->command);

	int		nb_cmds;
	char	**cmds;
	char	***tokens;

	nb_cmds = count_command(data->command);
	cmds = split_command(data->command, nb_cmds);
	tokens = split_tokens(cmds, nb_cmds);
	free_tab_str(cmds);
	return (tokens);
}
