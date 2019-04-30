/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_unsigned_long.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:12:53 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:20:45 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_write(char **str, unsigned long long n, int len)
{
	int		i;

	i = len - 1;
	if (n == 0)
		(*str)[i--] = '0';
	while (n)
	{
		(*str)[i--] = '0' + n % 10;
		n /= 10;
	}
}

char			*ft_itoa_unsigned_long(unsigned long long n)
{
	unsigned long long	tmp;
	int					len;
	char				*str;

	len = 1;
	tmp = n;
	while (tmp /= 10)
		len++;
	if (!(str = (char *)malloc(sizeof(*str) * (len + 1))))
		return (NULL);
	ft_write(&str, n, len);
	str[len] = '\0';
	return (str);
}
