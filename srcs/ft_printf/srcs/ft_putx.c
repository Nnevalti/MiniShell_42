/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putx.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:11:58 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/20 16:11:45 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_hexlen(long nb)
{
	int		i;

	i = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
		nb = -nb;
	while (nb > 0)
	{
		i++;
		nb /= 16;
	}
	return (i);
}

void	ft_putnbrbase(unsigned int nb, char *base, int *i)
{
	if (nb < 0)
		nb = nb * -1;
	if (nb % 16 != nb)
	{
		ft_putnbrbase(nb / 16, base, i);
	}
	ft_write(base[nb % 16]);
	(*i)++;
}

int		ft_putx(t_flags *flags, va_list parameters, char *base)
{
	int				i;
	unsigned int	nb;
	int				hexlen;

	i = 0;
	nb = (unsigned int)va_arg(parameters, unsigned int);
	hexlen = flags->precision > ft_hexlen(nb)
			? flags->precision : ft_hexlen(nb);
	if (nb == 0 && flags->precision == 0)
	{
		i += ft_putnstr(' ', flags->padding);
		return (i);
	}
	if (flags->left == 0 && (flags->zero == 0 || flags->precision != -1))
		i += ft_putnstr(' ', flags->padding - hexlen);
	if (flags->zero == 1 && flags->precision == -1)
		i += ft_putnstr('0', flags->padding - hexlen);
	if (flags->precision > ft_hexlen(nb))
		i += ft_putnstr('0', flags->precision - ft_hexlen(nb));
	ft_putnbrbase(nb, base, &i);
	if (flags->left == 1)
		i += ft_putnstr(' ', flags->padding - hexlen);
	return (i);
}
