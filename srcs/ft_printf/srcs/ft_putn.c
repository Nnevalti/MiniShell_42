/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putn.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:50:46 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/20 15:46:00 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_nbrlen(int nbr)
{
	int				i;
	unsigned int	nb;

	i = 0;
	if (nbr < 0)
	{
		nb = -nbr;
	}
	else
		nb = nbr;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int		ft_printn(long nb, int *i)
{
	char			c;

	if (nb < 0)
		nb = -nb;
	if (nb >= 10)
	{
		ft_printn(nb / 10, i);
		ft_printn(nb % 10, i);
	}
	else
	{
		c = nb + '0';
		write(1, &c, 1);
		(*i)++;
	}
	return (*i);
}

int		ft_printminus(int nb)
{
	if (nb < 0)
	{
		write(1, "-", 1);
		return (1);
	}
	return (0);
}

int		ft_putn(t_flags *flags, va_list parameters)
{
	int		i;
	int		nb;
	int		len;

	i = 0;
	nb = (int)va_arg(parameters, int);
	if (nb < 0)
		flags->padding--;
	len = flags->precision > ft_nbrlen(nb) ? flags->precision : ft_nbrlen(nb);
	if (flags->precision == 0 && nb == 0)
	{
		i += ft_putnstr(' ', flags->padding);
		return (i);
	}
	if (flags->left == 0 && (flags->zero == 0 || flags->precision != -1))
		i += ft_putnstr(' ', flags->padding - len);
	i += ft_printminus(nb);
	if (flags->zero == 1 && flags->precision == -1)
		i += ft_putnstr('0', flags->padding - len);
	if (flags->precision > ft_nbrlen(nb) && flags->precision != -1)
		i += ft_putnstr('0', flags->precision - ft_nbrlen(nb));
	ft_printn(nb, &i);
	if (flags->left == 1)
		i += ft_putnstr(' ', flags->padding - len);
	return (i);
}
