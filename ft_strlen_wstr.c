/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen_wstr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 12:28:38 by sdurgan           #+#    #+#             */
/*   Updated: 2019/02/02 12:30:44 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

size_t	ft_strlen_wstr(wchar_t *wstr, int flags[11])
{
	size_t	num;
	size_t	i;

	i = 0;
	num = 0;
	while (wstr[i])
	{
		if (flags[10])
			if (num + (size_t)num_of_bytes(wstr[i]) <= (size_t)flags[8])
				num += num_of_bytes(wstr[i]);
			else
				break ;
		else
			num += num_of_bytes(wstr[i]);
		i++;
	}
	return (num);
}
