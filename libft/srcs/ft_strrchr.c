/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:42:50 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/09 14:40:14 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strrchr(const char *str, int c)
{
	int		len;

	len = ft_strlen((char *)str) - 1;
	if (c == '\0')
		len++;
	while (len >= 0 && (str[len] || c == '\0'))
	{
		if (str[len] == c)
			return ((char *)&(str[len]));
		len--;
	}
	return (0);
}
