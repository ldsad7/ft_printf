/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa_long.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 20:13:38 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:20:38 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void		ft_write(char **str, long long n, int len, int fl)
{
	int		i;

	i = len + fl - 1;
	if (fl)
		(*str)[0] = '-';
	if (n == 0)
		(*str)[i--] = '0';
	while (n)
	{
		(*str)[i--] = '0' + n % 10;
		n /= 10;
	}
}

char			*ft_itoa_long(long long n)
{
	long long			tmp;
	int					fl;
	int					len;
	char				*str;

	len = 1;
	if ((unsigned long long)n == -9223372036854775808U)
		return (ft_strdup("-9223372036854775808"));
	fl = (n < 0);
	n = n - 2 * n * fl;
	tmp = n;
	while (tmp /= 10)
		len++;
	if (!(str = (char *)malloc(sizeof(*str) * (len + fl + 1))))
		return (NULL);
	ft_write(&str, n, len, fl);
	str[len + fl] = '\0';
	return (str);
}
