/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conv_n.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/05 16:50:13 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/06 11:44:57 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void		conv_n(t_conv *cn)
{
	int			*n;
	long		*ln;
	long long	*lln;

	cn->fmt[cn->i] == 'N' ? cn->mod_l++ : 0;
	cn->mod_l > 2 ? cn->mod_l -= 2 : 0;
	if (cn->mod_l == 0)
	{
		n = (int *)va_arg(cn->ap, int *);
		*n = cn->j;
	}
	else if (cn->mod_l == 1)
	{
		ln = (long *)va_arg(cn->ap, long *);
		*ln = cn->j;
	}
	else if (cn->mod_l == 2)
	{
		lln = (long long *)va_arg(cn->ap, long long *);
		*lln = cn->j;
	}
}
