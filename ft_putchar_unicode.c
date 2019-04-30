/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putchar_.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/25 14:02:42 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:21:39 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int				num_of_bytes(unsigned long long a)
{
	if (a <= 0x7F)
		return (1);
	else if (a <= 0x7FF)
		return (2);
	else if (a <= 0xFFFF)
		return (3);
	else
		return (4);
}

static void		char_bzero(char (*bytes)[6], unsigned long long a)
{
	int		num;

	(*bytes)[0] = a;
	num = 0;
	while (++num < 6)
		(*bytes)[num] = 0;
}

int				ft_putchar_unicode(unsigned long long a)
{
	char	bytes[6];
	int		num;

	char_bzero(&bytes, a);
	num = num_of_bytes(a);
	if (num == 2)
	{
		bytes[1] = 128 | (a & 63);
		bytes[0] = 192 | (a >> 6);
	}
	else if (num == 3)
	{
		bytes[2] = 128 | (a & 63);
		bytes[1] = 128 | ((a >> 6) & 63);
		bytes[0] = 224 | (a >> 12);
	}
	else if (num == 4)
	{
		bytes[3] = 128 | (a & 63);
		bytes[2] = 128 | ((a >> 6) & 63);
		bytes[1] = 128 | ((a >> 12) & 63);
		bytes[0] = 240 | (a >> 18);
	}
	write(1, bytes, num);
	return (num);
}
