/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnjoin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hvernhes <hvernhes@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/01 01:24:26 by hvernhes          #+#    #+#             */
/*   Updated: 2021/02/01 01:24:30 by hvernhes         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "../include/libft.h"

char	*ft_strnjoin(char const *s1, char const *s2, int len)
{
	char	*str;

	if (!(str = (char *)malloc(sizeof(char) * (ft_strlen((char *)s1)
		+ len) + 1)))
		return (NULL);
	ft_strcpy(str, s1);
	ft_strncat(str, s2, len);
	return (str);
}
