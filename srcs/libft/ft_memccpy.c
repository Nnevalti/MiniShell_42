/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:49:40 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/07 12:21:46 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memccpy(void *d, const void *s, int c, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*src;

	i = 0;
	dest = d;
	src = s;
	while (i < n)
	{
		dest[i] = (unsigned char)src[i];
		if ((unsigned char)dest[i] == (unsigned char)c)
			return (&(dest[i + 1]));
		i++;
	}
	return (0);
}
