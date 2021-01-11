/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:49:40 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/09 11:22:14 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>
#include "../include/libft.h"

void	*ft_memmove(void *d, const void *s, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*src;

	if (s < d && s + n >= d)
	{
		i = n;
		dest = d;
		src = s;
		while (i > 0)
		{
			dest[i - 1] = src[i - 1];
			i--;
		}
	}
	else
		ft_memcpy(d, s, n);
	return (d);
}
