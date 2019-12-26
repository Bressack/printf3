/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_cs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:50:44 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/15 11:53:02 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		conv_c(char c, t_conv *cn)
{
	int		i;

	i = -1;
	while (!cn->f_minus && cn->min_v - (1 + (++i)) > 0)
		write_buf(cn, cn->f_zero ? "0" : " ", 1);
	write_buf(cn, &c, 1);
	while (cn->f_minus && cn->min_v - (1 + (++i)) > 0)
		write_buf(cn, " ", 1);
}

void		conv_s(char *s, t_conv *cn)
{
	int		i;
	int		len;

	len = s ? strlen(s) : NULL_STR_LEN;
	cn->f_prec && cn->prec_v < len ? len = cn->prec_v : 0;
	i = -1;
	while (!cn->f_minus && cn->min_v - (len + (++i)) > 0)
		write_buf(cn, " ", 1);
	write_buf(cn, s ? s : NULL_STR, len);
	while (cn->f_minus && cn->min_v - (len + (++i)) > 0)
		write_buf(cn, " ", 1);
}
