/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_doxibu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 17:08:31 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/15 11:58:50 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static int		convert_toa(
	unsigned long long n, char *base_to, unsigned long long bs, char *buf)
{
	int	i;

	i = 0;
	if (n > bs - 1)
	{
		i = convert_toa(n / bs, base_to, bs, buf - 1);
		return (convert_toa(n % bs, base_to, bs, buf) + i);
	}
	else
		*buf = *(base_to + (n % bs));
	return (1);
}

static void		ft_vtoa_u_b(t_conv *cn, int *i, int *j, char output[OTP])
{
	output[(*i) - 1] = 0;
	cn->nmin ? output[OTP - 1]++ : 0;
	(*i) = precminsign(cn, output, OTP - (*i));
	(*j) = (*i);
	while (!cn->f_minus && cn->min_v > OTP - (*j) - 1)
	{
		output[(*i)] = cn->f_zero ? '0' : ' ';
		(*i)--;
		(*j)--;
	}
	write_buf(cn, output + (*i) + 1, OTP - (*i) - 1);
	while (cn->f_minus && cn->min_v > OTP - (*j) - 1)
	{
		write_buf(cn, " ", 1);
		(*j)--;
	}
}

static void		ft_vtoa_u(unsigned long long n, t_conv *cn)
{
	char	output[OTP];
	int		i;
	int		j;

	i = 1;
	!n && !cn->isp ? cn->f_hash = 0 : 0;
	if (!(!n && cn->f_prec && !cn->prec_v))
	{
		if (cn->base == BASE_BIN)
			i = convert_toa(n, BIN_STR, BIN_SIZE, &output[OTP - 1]);
		else if (cn->base == BASE_OCT)
			i = convert_toa(n, OCT_STR, OCT_SIZE, &output[OTP - 1]);
		else if (cn->base == BASE_DEC)
			i = convert_toa(n, DEC_STR, DEC_SIZE, &output[OTP - 1]);
		else if (cn->base == BASE_HEX_LO)
			i = convert_toa(n, HEX_LO_STR, HEX_LO_SIZE, &output[OTP - 1]);
		else if (cn->base == BASE_HEX_UP)
			i = convert_toa(n, HEX_UP_STR, HEX_UP_SIZE, &output[OTP - 1]);
	}
	else
		i = 0;
	ft_vtoa_u_b(cn, &i, &j, output);
}

static void		ft_vtoa(long long n, t_conv *cn)
{
	cn->sign = n < 0 ? SIGN_MINUS : SIGN_NONE;
	cn->sign == SIGN_PLUS && cn->f_space ? n = SIGN_SPACE : 0;
	if (n == LLONG_MIN)
	{
		cn->nmin = 1;
		n = -(n + 1);
	}
	n = n < 0 ? -n : n;
	ft_vtoa_u((unsigned long long)n, cn);
}

void			conv_doibux(t_conv *cn, int cast, int issigned)
{
	cn->f_prec ? cn->f_zero = 0 : 0;
	if (cast == sizeof(char) && issigned == UNSIGNED)
		ft_vtoa_u((unsigned char)va_arg(cn->ap, int), cn);
	else if (cast == sizeof(char) && issigned == SIGNED)
		ft_vtoa((char)va_arg(cn->ap, int), cn);
	else if (cast == sizeof(short) && issigned == UNSIGNED)
		ft_vtoa_u((unsigned short)va_arg(cn->ap, int), cn);
	else if (cast == sizeof(short) && issigned == SIGNED)
		ft_vtoa((short)va_arg(cn->ap, int), cn);
	else if (cast == sizeof(int) && issigned == UNSIGNED)
		ft_vtoa_u((unsigned int)va_arg(cn->ap, int), cn);
	else if (cast == sizeof(int) && issigned == SIGNED)
		ft_vtoa((int)va_arg(cn->ap, int), cn);
	else if (cast == sizeof(long) && issigned == UNSIGNED)
		ft_vtoa_u((unsigned long)va_arg(cn->ap, long), cn);
	else if (cast == sizeof(long) && issigned == SIGNED)
		ft_vtoa((long)va_arg(cn->ap, long), cn);
	else if (cast == sizeof(long long) && issigned == UNSIGNED)
		ft_vtoa_u((unsigned long long)va_arg(cn->ap, long long), cn);
	else if (cast == sizeof(long long) && issigned == SIGNED)
		ft_vtoa((long long)va_arg(cn->ap, long long), cn);
}
