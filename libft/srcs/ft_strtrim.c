/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 14:39:27 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/15 17:02:20 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "../include/libft.h"

static int	ft_inset(char c, char const *set)
{
	while (*set)
	{
		if (*set == c)
			return (1);
		set++;
	}
	return (0);
}

static int	ft_nb_chars_start(char const *str, char const *set)
{
	int		nb_chars;
	int		i;

	nb_chars = 0;
	i = 0;
	while (ft_inset(str[i++], set))
		nb_chars++;
	return (nb_chars);
}

static int	ft_nb_chars_end(char const *str, char const *set)
{
	int		nb_chars;
	int		i;

	nb_chars = 0;
	i = ft_strlen((char *)str) - 1;
	while (ft_inset(str[i--], set))
		nb_chars++;
	return (nb_chars);
}

char		*ft_strtrim(char const *s1, char const *set)
{
	char			*str;
	unsigned long	i;
	int				nb_chars_start;
	int				nb_chars_end;

	nb_chars_start = ft_nb_chars_start(s1, set);
	if (nb_chars_start == (int)ft_strlen(s1))
		return (str = (char *)ft_calloc(1, sizeof(char)));
	nb_chars_end = ft_nb_chars_end(s1, set);
	if (!(str = (char *)malloc((ft_strlen((char *)s1)
		- nb_chars_start - nb_chars_end + 1) * sizeof(char))))
		return (NULL);
	i = nb_chars_start;
	while (i < ft_strlen((char *)s1) - nb_chars_end)
	{
		str[i - nb_chars_start] = s1[i];
		i++;
	}
	str[i - nb_chars_start] = '\0';
	return (str);
}
