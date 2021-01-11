/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:49:40 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/09 11:04:48 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stddef.h>

void	*ft_memcpy(void *d, const void *s, size_t n)
{
	size_t		i;
	char		*dest;
	const char	*src;

	i = 0;
	dest = d;
	src = s;
	while (i < n)
	{
		dest[i] = src[i];
		i++;
	}
	return (dest);
}
