/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_buf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tharchen <tharchen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/02 16:06:46 by tharchen          #+#    #+#             */
/*   Updated: 2019/11/15 10:57:58 by tharchen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	write_buf(t_conv *cn, char *s, size_t n)
{
	long	x;

	if (s && n >= BUFF_SIZE)
	{
		write(1, cn->buf, cn->j);
		cn->ret += cn->j;
		cn->j = 0;
		write(1, s, n);
		cn->ret += n;
	}
	else
	{
		if (n >= BUFF_SIZE || cn->j + n >= BUFF_SIZE - 20 || !s)
		{
			write(1, cn->buf, cn->j);
			cn->ret += cn->j;
			cn->j = 0;
		}
		x = -1;
		if (s)
			while (++x < (long)n)
				cn->buf[(cn->j)++] = s[x];
	}
}
