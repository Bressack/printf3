/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/30 23:18:31 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/15 13:37:04 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int			isconv(char c)
{
	int		i;

	i = -1;
	while (CONV[++i])
		if (CONV[i] == c)
			return (i);
	return (-1);
}

int			isvalid(char c)
{
	int		i;

	i = -1;
	while (VALID_CHAR[++i])
		if (VALID_CHAR[i] == c)
			return (i);
	return (-1);
}

void		reset_cn(t_conv *cn, int lev)
{
	if (lev)
	{
		cn->fmt = 0;
		cn->i = 0;
		cn->j = 0;
		cn->ret = 0;
	}
	cn->hash_start = 0;
	cn->f_prec = 0;
	cn->f_minus = 0;
	cn->f_zero = 0;
	cn->f_plus = 0;
	cn->f_space = 0;
	cn->f_hash = 0;
	cn->mod_h = 0;
	cn->mod_l = 0;
	cn->mod_j = 0;
	cn->min_v = 0;
	cn->prec_v = 0;
	cn->sign = 0;
	cn->nmin = 0;
	cn->isp = 0;
}

int			get_cast(int size, t_conv *cn)
{
	if (cn->mod_h == 2)
		return (size / 4);
	else if (cn->mod_h == 1)
		return (size / 2);
	else if (cn->mod_l == 1)
		return (size * 2);
	else if (cn->mod_l == 2)
		return (size * 2);
	return (size);
}

void		overwrites_handle(t_conv *cn)
{
	cn->mod_h > 2 ? cn->mod_h -= 2 : 0;
	cn->mod_l > 2 ? cn->mod_l -= 2 : 0;
	cn->f_plus ? cn->f_space = 0 : 0;
	cn->f_minus ? cn->f_zero = 0 : 0;
	cn->min_v < 0 ? cn->f_minus = 1 : 0;
	cn->min_v < 0 ? cn->min_v = -cn->min_v : 0;
	cn->min_v >= OTP || cn->min_v >= BUFF_SIZE ? cn->min_v = OTP / 2 : 0;
	cn->min_v * -1 >= OTP ||
		cn->min_v >= BUFF_SIZE ? cn->min_v = -(OTP / 2) : 0;
	cn->prec_v >= OTP || cn->prec_v >= BUFF_SIZE ? cn->prec_v = OTP / 2 : 0;
	cn->prec_v * -1 >= OTP ||
		cn->prec_v >= BUFF_SIZE ? cn->prec_v = -(OTP / 2) : 0;
}

void		conv_char_4(t_conv *cn)
{
	if (FMT_AC_ == 'o' || FMT_AC_ == 'O')
		cn->sign = SIGN_OCT;
	else if (FMT_AC_ == 'b' || FMT_AC_ == 'B')
		cn->sign = SIGN_BIN;
	else if (FMT_AC_ == 'x' || FMT_AC_ == 'p')
		cn->sign = SIGN_HEX_LO;
	else if (FMT_AC_ == 'X')
		cn->sign = SIGN_HEX_UP;
	if (FMT_AC_ == 'd' || FMT_AC_ == 'd' ||
		FMT_AC_ == 'i' || FMT_AC_ == 'I')
		conv_doibux(cn, get_cast(sizeof(int), cn), SIGNED);
	else if (FMT_AC_ == 'o' || FMT_AC_ == 'O' || FMT_AC_ == 'u' ||
		FMT_AC_ == 'U' || FMT_AC_ == 'x' || FMT_AC_ == 'X' ||
		FMT_AC_ == 'p' || FMT_AC_ == 'b' || FMT_AC_ == 'B')
		conv_doibux(cn, get_cast(sizeof(int), cn), UNSIGNED);
	else if (FMT_AC_ == 'c')
		conv_c((char)va_arg(cn->ap, int), cn);
	else if (FMT_AC_ == 's')
		conv_s(va_arg(cn->ap, char *), cn);
	if (FMT_AC_ == '%')
		conv_c('%', cn);
	if (FMT_AC_ == 'n' || FMT_AC_ == 'N')
		conv_n(cn);
}

void		conv_char_3(t_conv *cn)
{
	cn->hash_start = 0;
	if (FMT_AC_ == 'd' || FMT_AC_ == 'I' || FMT_AC_ == 'O' ||
		FMT_AC_ == 'U' || FMT_AC_ == 'B' || FMT_AC_ == 'p')
		cn->mod_l++;
	if (FMT_AC_ == 'p')
	{
		cn->f_hash = 1;
		cn->isp = 1;
	}
	if (FMT_AC_ == 'd' || FMT_AC_ == 'd' || FMT_AC_ == 'i' ||
		FMT_AC_ == 'I' || FMT_AC_ == 'u' || FMT_AC_ == 'U')
		cn->base = BASE_DEC;
	else if (FMT_AC_ == 'o' || FMT_AC_ == 'O')
		cn->base = BASE_OCT;
	else if (FMT_AC_ == 'b' || FMT_AC_ == 'B')
		cn->base = BASE_BIN;
	else if (FMT_AC_ == 'x' || FMT_AC_ == 'p')
		cn->base = BASE_HEX_LO;
	else if (FMT_AC_ == 'X')
		cn->base = BASE_HEX_UP;
	conv_char_4(cn);
}

void		conv_char_2(t_conv *cn)
{
	if (FMT_AC_ == '*' && FMT_PC_ == F_PREC_CHAR)
		cn->prec_v = va_arg(cn->ap, int);
	else if (FMT_AC_ == 'h')
		cn->mod_h++;
	else if (FMT_AC_ == 'l')
		cn->mod_l++;
	else if (FMT_AC_ == 'j')
		cn->mod_j++;
	if (isconv(FMT_AC_) != -1)
	{
		conv_char_3(cn);
		reset_cn(cn, 0);
	}
	else if (isvalid(FMT_AC_) == -1)
	{
		cn->hash_start = 0;
		conv_c(FMT_AC_, cn);
	}
}

int		conv_char_1(t_conv *cn)
{
	if (isdigit(FMT_AC_) && FMT_PC_ != F_PREC_CHAR)
	{
		while (isdigit(FMT_AC_))
		{
			cn->min_v = cn->min_v * 10 + FMT_AC_ - '0';
			(cn->i)++;
		}
		return (1);
	}
	else if (FMT_AC_ == '*' && FMT_PC_ != F_PREC_CHAR)
		cn->min_v = va_arg(cn->ap, int);
	else if (isdigit(FMT_AC_) && FMT_PC_ == F_PREC_CHAR)
	{
		while (isdigit(FMT_AC_))
		{
			cn->prec_v = cn->prec_v * 10 + FMT_AC_ - '0';
			(cn->i)++;
		}
		return (1);
	}
	else
		conv_char_2(cn);
	return (0);
}

int			ft_vprintf(const char *fmt, va_list ap)
{
	t_conv	cn;

	reset_cn(&cn, 1);
	cn.fmt = (char *)fmt;
	va_copy(cn.ap, ap);
	while (FMT_AC)
	{
		if (FMT_AC == '%' && !cn.hash_start)
			cn.hash_start = 1;
		else if (cn.hash_start == 1)
		{
			if (FMT_AC == F_PREC_CHAR)
				cn.f_prec  = 1;
			else if (FMT_AC == F_MINUS_FLAG)
				cn.f_minus = 1;
			else if (FMT_AC == F_ZERO_FLAG && !isdigit(FMT_PC))
				cn.f_zero  = 1;
			else if (FMT_AC == F_PLUS_FLAG)
				cn.f_plus  = 1;
			else if (FMT_AC == F_SPACE_FLAG)
				cn.f_space = 1;
			else if (FMT_AC == F_HASH_FLAG)
				cn.f_hash  = 1;
			else if (conv_char_1(&cn))
				continue ;
			overwrites_handle(&cn);
		}
		else
		{
			write_buf(&cn, &FMT_AC, 1);
		}
		cn.i++;
	}
	write_buf(&cn, NULL, BUFF_SIZE);
	va_end(cn.ap);
	return (cn.ret);
}

int			ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, fmt);
	ret = ft_vprintf(fmt, ap);
	va_end(ap);
	return (ret);
}
