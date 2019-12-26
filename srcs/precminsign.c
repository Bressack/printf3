/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   precminsign.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 11:54:57 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/15 12:15:56 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int		precminsign_a(t_conv *cn, char output[OTP], int pos)
{
	if (cn->f_zero)
	{
		cn->f_prec = 1;
		cn->prec_v = cn->min_v;
		cn->min_v = 0;
		cn->f_zero = 0;
		cn->sign == SIGN_MINUS ? cn->prec_v-- : 0;
	}
	if (cn->f_hash && cn->sign == SIGN_OCT && OTP - pos >= cn->prec_v)
		cn->prec_v = OTP - pos + 1;
	while (cn->prec_v > OTP - pos)
		output[--pos] = '0';
	cn->sign == SIGN_MINUS ? output[--pos] = '-' : 0;
	cn->f_plus && cn->sign != SIGN_MINUS ? output[--pos] = '+' : 0;
	cn->f_space && cn->sign != SIGN_MINUS ? output[--pos] = ' ' : 0;
	return (pos);
}

int		precminsign(t_conv *cn, char output[OTP], int pos)
{
	pos = precminsign_a(cn, output, pos);
	if (cn->f_hash)
	{
		if (cn->sign == SIGN_BIN)
		{
			output[--pos] = 'b';
			output[--pos] = '0';
		}
		else if (cn->sign == SIGN_HEX_LO)
		{
			output[--pos] = 'x';
			output[--pos] = '0';
		}
		else if (cn->sign == SIGN_HEX_UP)
		{
			output[--pos] = 'X';
			output[--pos] = '0';
		}
	}
	output[--pos] = 0;
	return (pos);
}
