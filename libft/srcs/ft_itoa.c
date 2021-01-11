/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: exam <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 18:51:56 by exam              #+#    #+#             */
/*   Updated: 2019/10/08 15:16:52 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

static int	ft_nb_chars(int nbr)
{
	long	mult;
	int		nb_chars;

	mult = 10;
	nb_chars = 0;
	while (nbr % mult != nbr)
	{
		mult *= 10;
		nb_chars++;
	}
	nb_chars++;
	return (nbr < 0 ? nb_chars + 1 : nb_chars);
}

static void	ft_putnbr_rec(char *str, unsigned int nbr)
{
	int		i;

	i = 0;
	if (nbr < 10)
	{
		while (str[i])
			i++;
		str[i] = nbr + '0';
	}
	else
	{
		ft_putnbr_rec(str, nbr / 10);
		ft_putnbr_rec(str, nbr % 10);
	}
}

char		*ft_itoa(int nbr)
{
	char			*str;
	unsigned int	nb;
	int				nb_chars;

	nb_chars = ft_nb_chars(nbr);
	str = (char *)ft_calloc(nb_chars + 1, sizeof(char));
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		*str = '-';
		nb = -nbr;
		ft_putnbr_rec(str + 1, nb);
	}
	else
	{
		nb = nbr;
		ft_putnbr_rec(str, nb);
	}
	return (str);
}
