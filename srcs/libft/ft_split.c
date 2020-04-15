/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsplit.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/09 18:13:58 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/08 15:06:47 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static char	*ft_getstr(char const *str, char c)
{
	int		nb_chars;
	char	*copy;
	int		i;

	nb_chars = 0;
	while (str[nb_chars] && str[nb_chars] != c)
		nb_chars++;
	copy = (char *)malloc((nb_chars + 1) * sizeof(char));
	i = 0;
	while (i < nb_chars)
	{
		copy[i] = str[i];
		i++;
	}
	copy[nb_chars] = '\0';
	return (copy);
}

static int	ft_get_nb_strings(char const *str, char c)
{
	int		nb_strings;

	nb_strings = 0;
	while (*str)
	{
		while (*str == c)
			str++;
		if (*str != '\0')
			nb_strings++;
		while (*str && *str != c)
			str++;
	}
	return (nb_strings);
}

char		**ft_split(char const *s, char c)
{
	int		nb_strings;
	char	**tab;
	int		i;

	nb_strings = ft_get_nb_strings(s, c);
	if (!(tab = (char **)malloc((nb_strings + 1) * sizeof(char *))))
		return (NULL);
	i = 0;
	while (i < nb_strings)
	{
		while (*s == c)
			s++;
		if (*s != '\0')
			tab[i] = ft_getstr(s, c);
		while (*s && *s != c)
			s++;
		i++;
	}
	tab[nb_strings] = NULL;
	return (tab);
}
