/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tfevrier <tfevrier@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 11:34:09 by tfevrier          #+#    #+#             */
/*   Updated: 2019/10/07 12:14:33 by tfevrier         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int		ft_isprint(char c)
{
	return (c >= 32 && c < 127);
}
