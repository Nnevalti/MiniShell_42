/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puts.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 17:12:49 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/20 15:50:22 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int		ft_strlen(char *str)
{
	int		i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_prints(char *str, t_flags *flags, int len)
{
	int		i;

	i = 0;
	if (flags->precision == 0)
	{
		i += ft_putnstr(' ', len);
		return (i);
	}
	else if (flags->precision > 0)
	{
		while (i < flags->precision && str[i])
		{
			write(1, &(str[i]), 1);
			i++;
		}
		return (i);
	}
	while (str[i])
	{
		write(1, &(str[i]), 1);
		i++;
	}
	return (i);
}

int		ft_puts(t_flags *flags, va_list parameters)
{
	int		i;
	char	*va_arg;
	int		len;

	i = 0;
	va_arg = (char *)va_arg(parameters, char *);
	if (va_arg == NULL)
		va_arg = "(null)";
	len = ft_strlen(va_arg);
	if (flags->precision >= 0 && flags->precision < len)
		len = flags->precision;
	if (flags->left == 1)
	{
		i += ft_prints(va_arg, flags, len);
		i += ft_putnstr(' ', flags->padding - len);
	}
	else if (flags->left == 0)
	{
		if (flags->zero == 1)
			i += ft_putnstr('0', flags->padding - len);
		else
			i += ft_putnstr(' ', flags->padding - len);
		i += ft_prints(va_arg, flags, len);
	}
	return (i);
}
