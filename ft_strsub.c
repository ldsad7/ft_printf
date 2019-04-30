/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/25 22:09:48 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 02:22:32 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*ft_strsub(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*str;

	if (len > (size_t)(-1) - start || len == (size_t)(-1))
		return (NULL);
	if (s)
	{
		str = (char *)malloc(sizeof(*str) * (len + 1));
		if (!str)
			return (NULL);
		i = start;
		while (s[i] && i - start < len)
		{
			str[i - start] = s[i];
			i++;
		}
		str[i - start] = '\0';
		return (str);
	}
	return ((char *)s);
}
