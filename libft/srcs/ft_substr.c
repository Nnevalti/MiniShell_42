/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 14:21:29 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/15 15:57:31 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include <stdlib.h>
#include "../include/libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char			*str;
	unsigned int	size;
	unsigned int	i;

	if (start >= ft_strlen(s))
		return ((char *)ft_calloc(1, sizeof(char)));
	size = (start + len > ft_strlen(s)) ?
			ft_strlen(s) - start : len;
	if (!(str = (char *)malloc((size + 1) * sizeof(char))))
		return (0);
	i = 0;
	while (i < size)
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
