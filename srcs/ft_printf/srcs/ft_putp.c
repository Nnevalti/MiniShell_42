/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putp.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 14:11:58 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/21 10:54:58 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_putpbase(long nb, char *base, int *i)
{
	if (nb < 0)
		nb = nb * -1;
	if (nb % 16 != nb)
		ft_putpbase(nb / 16, base, i);
	ft_write(base[nb % 16]);
	(*i)++;
}

int		ft_osef(t_flags *flags, int i)
{
	i += flags->left == 0 ? ft_putnstr(' ', flags->padding) : 2;
	write(1, "0x", 2);
	i += flags->left == 1 ? ft_putnstr(' ', flags->padding) : 2;
	return (i);
}

int		ft_putp(t_flags *flags, va_list parameters, char *base)
{
	int		i;
	long	nb;
	int		hexlen;

	i = 0;
	nb = (long)va_arg(parameters, long);
	flags->padding -= 2;
	hexlen = flags->precision > ft_hexlen(nb)
			? flags->precision : ft_hexlen(nb);
	if (nb == 0 && flags->precision == 0)
		return (ft_osef(flags, i));
	if (flags->left == 0 && (flags->zero == 0 || flags->precision != -1))
		i += ft_putnstr(' ', flags->padding - hexlen);
	write(1, "0x", 2);
	i += 2;
	if (flags->zero == 1 && flags->precision == -1)
		i += ft_putnstr('0', flags->padding - hexlen);
	if (flags->precision > ft_hexlen(nb))
		i += ft_putnstr('0', flags->precision - ft_hexlen(nb));
	ft_putpbase(nb, base, &i);
	if (flags->left == 1)
		i += ft_putnstr(' ', flags->padding - hexlen);
	return (i);
}
