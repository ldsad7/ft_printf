/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_f.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sdurgan <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/02 11:54:19 by sdurgan           #+#    #+#             */
/*   Updated: 2019/02/02 14:57:48 by sdurgan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

char	*nan_inf(double num, char up)
{
	if (num != num)
		return (up == 'g' || up == 'f' || up == 'e' ?
			("nan") : ("NAN"));
	else if (num == 1.0 / 0.0)
		return (up == 'g' || up == 'f' || up == 'e' ?
			("inf") : ("INF"));
	else if (num == -1.0 / 0.0)
		return (up == 'g' || up == 'f' || up == 'e' ?
			("-inf") : ("-INF"));
	else
		return (NULL);
}

int		round_f(char **head, char **tail, int l, int i)
{
	if ((*tail)[l - 1] == '9' && (*tail)[l - 2] == '9')
	{
		while (l && (*tail)[l] == '9')
		{
			(*tail)[l] = '0';
			if ((*tail)[l - 1] != '9')
			{
				(*tail)[l - 1] += 1;
				return (0);
			}
			l--;
		}
		if (l == 0)
		{
			if (((*tail)[l] = '0') && !ft_strcmp(*head, "9"))
				*head = ft_strdup("10");
			else
				(*head)[ft_strlen(*head) - 1] += 1;
			return (0);
		}
	}
	else
		(*tail)[i - 2] = ((*tail)[i - 1] > '4' && (*tail)[i - 2] != '9') ?
			(*tail)[i - 2] + 1 : (*tail)[i - 2];
	return (0);
}

int		round_g(char **head, char **tail, int i, char up)
{
	(*tail)[i - 2] = ((*tail)[i - 1] > '4' && (*tail)[i - 2] != '9') ?
		(*tail)[i - 2] + 1 : (*tail)[i - 2];
	if (up != 'e' && up != 'E')
	{
		while (--i != -1)
		{
			if ((*tail)[i] == '0' || ((*tail)[i - 1] != '9' &&
						(*tail)[i] != '9'))
				return (0);
			if (((*tail)[i] = '0') && i != 0 && (*tail)[i - 1] == '8')
				return (((*tail)[i - 1] += 1));
			if (i != 0 && (*tail)[i - 1] < '8')
				(*tail)[i - 1] += 1;
		}
		(*head)[ft_strlen(*head) - 1] += (*head)[ft_strlen(*head) - 1]
			== '9' ? 0 : 1;
		ft_strdel(tail);
		(*tail) = ft_strdup("0");
	}
	return (0);
}

int		float_rigth_nuls_spaces(double num, char *fr, int nul, int flags[11])
{
	int		ret;
	int		l;

	ret = flags[0] && num >= 0 && ((flags[7] && flags[2]) ||
			!flags[7]) ? write(1, " ", 1) : 0;
	if (!flags[7] || flags[2])
	{
		ret += flags[1] && num >= 0 ? write(1, "+", 1) : 0;
		ret += num < 0 ? write(1, "-", 1) : 0;
		return (ret);
	}
	flags[7] -= num < 0 || flags[1] || ret ? 1 + flags[5] : flags[5];
	flags[7] -= !nul && !ft_strcmp(fr, "0") ? 7 : 0;
	flags[7] -= !nul && ft_strcmp(fr, "0") ? (int)ft_strlen(fr) *
		!(flags[10] && !flags[8]) : 0;
	if (nul && (l = ft_strlen(fr) - 1))
	{
		while (fr[l - 1] == '0')
			l--;
		flags[7] -= 1 + l;
	}
	ret += put_spaces(num, flags);
	return (ret);
}

int		print_float(double num, int n_l[2], char up, int f[11])
{
	char	*head;
	int		r;
	char	*fr;
	double	t;

	head = ft_itoa_unsigned_long((unsigned long long)double_abs(num));
	t = double_abs(num) - (unsigned long long)double_abs(num);
	fr = ft_itoa_unsigned_long((unsigned long long)(t * power(10, n_l[1] + 1)));
	ft_round(&head, &fr, n_l, up);
	f[5] = ft_strlen(head) + (up == 'e' || up == 'E') * 4;
	r = float_rigth_nuls_spaces(num, fr, n_l[0], f);
	r += write(1, head, ft_strlen(head));
	r += !n_l[0] && !ft_strcmp(fr, "0") ? write(1, ".000000", 7) : 0;
	r += !n_l[0] && ft_strcmp(fr, "0") ? write(1, ".", !(f[10] && !f[8] &&
	!f[3])) + put_lost_nul(n_l[1], fr) + write(1, fr, ft_strlen(fr) - 1) : 0;
	if (n_l[0] && (n_l[1] = ft_strlen(fr) - 1))
	{
		while (fr[n_l[1] - 1] == '0')
			n_l[1]--;
		r += write(1, ".", 1) + put_lost_nul(n_l[1], fr) + write(1, fr, n_l[1]);
	}
	ft_strdel(&head);
	ft_strdel(&fr);
	return (r);
}
