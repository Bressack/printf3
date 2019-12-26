/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:07:24 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/15 13:29:35 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H
# include <stdarg.h>
# include <stdio.h>
# include <unistd.h>
# include <limits.h>
# include <strings.h>
# include <ctype.h>
# include <libc.h>
# define NULL_STR		"(null)"
# define NULL_STR_LEN	6
# define BUFF_SIZE		320000
# define OTP			320000
# define SIGNED			0
# define UNSIGNED		1
# define CONV			"dDiIoOuUxXbBcspnN%"
# define VALID_CHAR		"dDiIoOuUxXbBcspnN%0123456789-+ #.*lhj"

/*
** BASE STR + SIZE
*/
# define BIN_STR		"01"
# define BIN_SIZE		2
# define OCT_STR		"01234567"
# define OCT_SIZE		8
# define DEC_STR		"0123456789"
# define DEC_SIZE		10
# define HEX_LO_STR		"0123456789abcdef"
# define HEX_LO_SIZE	16
# define HEX_UP_STR		"0123456789ABCDEF"
# define HEX_UP_SIZE	16

/*
** FLAGS
*/
# define F_ZERO_FLAG	'0'
# define F_MINUS_FLAG	'-'
# define F_PLUS_FLAG	'+'
# define F_SPACE_FLAG	' '
# define F_HASH_FLAG	'#'
# define F_PREC_CHAR	'.'
# define F_STAR_CHAR	'*'

/*
** FMT IDX
*/
# define FMT_PC			cn.fmt[cn.i - 1]
# define FMT_AC			cn.fmt[cn.i]
# define FMT_NC			cn.fmt[cn.i + 1]
# define FMT_PC_		cn->fmt[cn->i - 1]
# define FMT_AC_		cn->fmt[cn->i]
# define FMT_NC_		cn->fmt[cn->i + 1]

/*
** BASE
*/
# define BASE_BIN		0
# define BASE_OCT		1
# define BASE_DEC		2
# define BASE_HEX_LO	3
# define BASE_HEX_UP	4

/*
** SIGN
*/
# define SIGN_NONE		0
# define SIGN_MINUS		1
# define SIGN_PLUS		2
# define SIGN_SPACE		3
# define SIGN_BIN		4
# define SIGN_OCT		5
# define SIGN_HEX_LO	6
# define SIGN_HEX_UP	7

typedef struct			s_conv
{
	char				buf[BUFF_SIZE + 1];
	char				*fmt;
	va_list				ap;
	int					ret;
	char				*tmps;
	int					min_v;
	int					prec_v;
	int					sign;
	int					base;
	int					i;
	int					j;
	char				hash_start;
	char				f_minus;
	char				f_zero;
	char				f_plus;
	char				f_space;
	char				f_hash;
	char				f_prec;
	char				mod_h;
	char				mod_l;
	char				mod_j;
	char				nmin;
	char				isp;
}						t_conv;
void					conv_doibux(t_conv *cn, int cast, int issigned);
void					conv_c(char c, t_conv *cn);
void					conv_s(char *s, t_conv *cn);
int						ft_printf(const char *fmt, ...);
void					write_buf(t_conv *cn, char *s, size_t n);
void					conv_n(t_conv *cn);
int						precminsign_a(t_conv *cn, char output[OTP], int pos);
int						precminsign(t_conv *cn, char output[OTP], int pos);
#endif
