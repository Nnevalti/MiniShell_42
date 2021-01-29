/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 17:52:10 by vdescham          #+#    #+#             */
/*   Updated: 2019/10/29 15:56:28 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/get_next_line.h"

int		ft_return(char **str, char **line)
{
	int		i;
	char	*tmp;

	i = 0;
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	*line = ft_substr(*str, 0, i);
	if ((*str)[i] == '\n') // && (*str)[i + 1] != '\0')
		tmp = ft_strdup(&(*str)[i + 1]);
	else
		tmp = NULL;
	free(*str);
	*str = tmp;
	if (!*str)
		return (0);
	return (1);
}

int		readline(int fd, char **str, char **buff)
{
	int		res;
	char	*tmp;

	while ((res = read(fd, *buff, BUFFER_SIZE)) > 0)
	{
		(*buff)[res] = '\0';
		if (!*str || !**str)
			*str = ft_strdup(*buff);
		else
		{
			tmp = ft_strjoin(*str, *buff);
			free(*str);
			*str = tmp;
		}
		if (ft_strchr(*str, '\n'))
		{
			break ;
		}
	}
	return (res);
}

int		get_next_line(int fd, char **line)
{
	int				res;
	static char		*str;
	char			*buff;

	if (!(buff = (char *)malloc(BUFFER_SIZE + 1 * sizeof(char))))
		return (-1);
	if (fd < 0 || !line || read(fd, buff, 0) < 0 || BUFFER_SIZE < 1)
		return (-1);
	res = readline(fd, &str, &buff);
	if (res < 0)
		return (-1);
	if (!str)
	{
		*line = ft_strdup("");
		return (0);
	}
	free(buff);
	return (ft_return(&str, line));
}
