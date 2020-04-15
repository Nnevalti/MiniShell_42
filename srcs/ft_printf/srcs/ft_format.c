/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_format.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:37:36 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/20 15:49:17 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_print_arg(const char *format, t_flags *flags, va_list parameters)
{
	int		i;

	i = 0;
	if (*format == 'c')
		i += ft_putc('c', flags, parameters);
	else if (*format == 's')
		i += ft_puts(flags, parameters);
	else if (*format == 'p')
		i += ft_putp(flags, parameters, "0123456789abcdef");
	else if (*format == 'd' || *format == 'i')
		i += ft_putn(flags, parameters);
	else if (*format == 'u')
		i += ft_putu(flags, parameters);
	else if (*format == 'x')
		i += ft_putx(flags, parameters, "0123456789abcdef");
	else if (*format == 'X')
		i += ft_putx(flags, parameters, "0123456789ABCDEF");
	else if (*format == '%')
		i += ft_putc('%', flags, parameters);
	return (i);
}
