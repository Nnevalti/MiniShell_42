/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vdescham <vdescham@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/31 16:19:39 by vdescham          #+#    #+#             */
/*   Updated: 2019/11/21 10:54:51 by vdescham         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <unistd.h>
# include <stdlib.h>
# include <stdarg.h>

typedef struct	s_flags
{
	int			zero;
	int			padding;
	int			left;
	int			precision;

}				t_flags;

int				ft_printf(const char *format, ...);
int				ft_write(char c);
int				ft_set_flags(t_flags *flags, const char *format,
								va_list parameters);
void			ft_reset(t_flags *flags);
int				ft_precision(t_flags *flags, const char *format,
								va_list parameters);
int				ft_width(t_flags *flags, const char *format,
								va_list parameters);
int				ft_print_arg(const char *format, t_flags *flags,
								va_list parameters);
int				ft_atoi(const char *str);
int				ft_isdigit(int c);
int				ft_strchr(char *str, char c);
int				ft_putnstr(char c, int n);
int				ft_putc(char c, t_flags *flags, va_list parameters);
int				ft_puts(t_flags *flags, va_list parameters);
int				ft_strlen(char *str);
int				ft_prints(char *str, t_flags *flags, int len);
int				ft_putn(t_flags *flags, va_list parameters);
int				ft_nbrlen(int nbr);
int				ft_printn(long nb, int *i);
int				ft_printminus(int nb);
int				ft_putu(t_flags *flags, va_list parameters);
int				ft_unbrlen(unsigned int nb);
int				ft_printu(unsigned int nb, int len);
int				ft_putx(t_flags *flags, va_list parameters, char *base);

int				ft_hexlen(long nb);
void			ft_putnbrbase(unsigned int nb, char *base, int *i);

int				ft_putp(t_flags *flags, va_list parameters, char *base);
void			ft_putpbase(long nb, char *base, int *i);

#endif
