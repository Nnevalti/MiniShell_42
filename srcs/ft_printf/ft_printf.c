/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/12 11:23:24 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/20 16:12:36 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int		ft_write(char c)
{
	write(1, &c, 1);
	return (1);
}

int		ft_printf(const char *format, ...)
{
	va_list			parameters;
	unsigned int	nbchars;
	int				i;
	t_flags			*flags;

	i = 0;
	nbchars = 0;
	flags = malloc(sizeof(t_flags));
	va_start(parameters, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			i += ft_set_flags(flags, &(format[i]), parameters);
			nbchars += ft_print_arg(&(format[i]), flags, parameters);
		}
		else
			nbchars += ft_write(format[i]);
		i++;
	}
	free(flags);
	va_end(parameters);
	return (nbchars);
}
