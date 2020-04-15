/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putu.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 14:50:46 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/20 15:46:52 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_unbrlen(unsigned int nb)
{
	int				i;

	i = 0;
	if (nb == 0)
		return (1);
	while (nb > 0)
	{
		nb /= 10;
		i++;
	}
	return (i);
}

int		ft_printu(unsigned int nb, int len)
{
	char			c;

	if (nb >= 10)
	{
		len = ft_printu(nb / 10, len + 1);
		ft_printu(nb % 10, len);
	}
	else if (nb < 10)
	{
		c = nb + '0';
		write(1, &c, 1);
		return (len + 1);
	}
	return (len);
}

int		ft_putu(t_flags *flags, va_list parameters)
{
	int					i;
	unsigned int		nb;
	int					len;

	i = 0;
	nb = (unsigned int)va_arg(parameters, unsigned int);
	len = flags->precision > ft_unbrlen(nb) ? flags->precision : ft_unbrlen(nb);
	if (flags->precision == 0 && nb == 0)
	{
		i += ft_putnstr(' ', flags->padding);
		return (i);
	}
	if (flags->left == 0 && (flags->zero == 0 || flags->precision != -1))
		i += ft_putnstr(' ', flags->padding - len);
	if (flags->zero == 1 && flags->precision == -1)
		i += ft_putnstr('0', flags->padding - len);
	if (flags->precision > ft_nbrlen(nb))
		i += ft_putnstr('0', flags->precision - ft_unbrlen(nb));
	i += ft_printu(nb, 0);
	if (flags->left == 1)
		i += ft_putnstr(' ', flags->padding - len);
	return (i);
}
