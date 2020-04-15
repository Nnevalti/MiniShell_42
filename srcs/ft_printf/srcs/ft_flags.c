/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_flags.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 12:41:46 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/21 13:05:53 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void	ft_reset(t_flags *flags)
{
	flags->zero = 0;
	flags->left = 0;
	flags->precision = -1;
	flags->padding = 0;
}

int		ft_precision(t_flags *flags, const char *format, va_list parameters)
{
	int i;
	int va_arg;

	i = 1;
	va_arg = 0;
	if (ft_isdigit(format[i]))
	{
		flags->precision = ft_atoi(&(format[i]));
		if (flags->precision < 0)
			flags->precision = -1;
	}
	else if (format[i] == '*')
	{
		va_arg = (int)va_arg(parameters, int);
		if (va_arg < 0)
			flags->precision = -1;
		else
			flags->precision = va_arg;
		return (i + 1);
	}
	else
		flags->precision = 0;
	while (ft_isdigit(format[i]))
		i++;
	return (i);
}

int		ft_width(t_flags *flags, const char *format, va_list parameters)
{
	int i;
	int va_arg;

	i = 0;
	va_arg = 0;
	if (ft_isdigit(format[i]))
		flags->padding = ft_atoi(&(format[i]));
	else if (format[i] == '*')
	{
		va_arg = (int)va_arg(parameters, int);
		if (va_arg < 0)
		{
			flags->padding = -va_arg;
			flags->left = 1;
			flags->zero = 0;
		}
		else
			flags->padding = va_arg;
		return (1);
	}
	while (ft_isdigit(format[i]))
		i++;
	return (i);
}

int		ft_set_flags(t_flags *flags, const char *format, va_list parameters)
{
	int		i;

	i = 1;
	ft_reset(flags);
	while (ft_strchr("0123456789-*.", format[i]))
	{
		if (format[i] == '0' && !flags->left)
		{
			flags->zero = 1;
			i++;
		}
		else if (format[i] == '-')
		{
			flags->zero = 0;
			flags->left = 1;
			i++;
		}
		else if (ft_isdigit(format[i]) || format[i] == '*')
			i += ft_width(flags, &(format[i]), parameters);
		else if (format[i] == '.')
			i += ft_precision(flags, &(format[i]), parameters);
	}
	return (i);
}
