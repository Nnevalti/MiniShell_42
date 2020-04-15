/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:16:50 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/20 15:42:34 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_putc(char c, t_flags *flags, va_list parameters)
{
	int		i;
	char	va_arg;

	i = 1;
	if (c == 'c')
		va_arg = (char)va_arg(parameters, int);
	else
		va_arg = c;
	if (flags->left == 1)
	{
		write(1, &va_arg, 1);
		i += ft_putnstr(' ', flags->padding - 1);
	}
	else if (flags->left == 0)
	{
		if (flags->zero == 1)
			i += ft_putnstr('0', flags->padding - 1);
		else
			i += ft_putnstr(' ', flags->padding - 1);
		write(1, &va_arg, 1);
	}
	return (i);
}
