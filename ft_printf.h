/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsimonis <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 14:19:49 by tsimonis          #+#    #+#             */
/*   Updated: 2019/02/02 16:18:49 by tsimonis         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <math.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <locale.h>

int					ft_putchar_unicode(unsigned long long a);
char				*change_base(char *from, int base_from,
									int base_to, int fl);
int					ft_printf(const char *str, ...);
int					print_char(va_list ap, char ls[3], int flags[11]);
int					print_double_hex(va_list ap, char ls[3], int flags[11]);
int					print_int(va_list ap, char ls[3], int flags[11]);
int					print_int_hex(va_list ap, char ls[3], int flags[11]);
void				print_n(va_list ap, char ls[3],
							unsigned long long printed);
int					print_octal(va_list ap, char ls[3], int flags[11]);
int					print_pointer(va_list ap, int flags[11]);
int					print_str(va_list ap, char ls[3], int flags[11]);
int					print_unsigned(va_list ap, char ls[3], int flags[11]);
int					print(va_list ap, char **str, int ret);
void				ft_bzero(void *s, size_t n);
int					print_double(va_list ap, char ls[3], int flags[11]);
char				*ft_itoa_unsigned_long(unsigned long long n);
char				*ft_itoa_long(long long n);
char				*ft_strchr(const char *s, int c);
void				ft_strdel(char **as);
int					ft_strcmp(const char *s1, const char *s2);
size_t				ft_strlen(const char *s);
char				*ft_strdup(const char *s1);
void				*ft_memset(void *b, int c, size_t len);
int					print_percent(int flags[11], char c);
void				int_bzero(int (*flags)[11], int *dots,
								int *nul, char (*ls)[3]);
int					print_arg(va_list ap, char ls[3],
								int flags[11], int print_);
int					flags_filling(int (*flags)[11], char **str,
									int *dots, int *nul);
int					num_of_bytes(unsigned long long a);
char				*ft_strsub(char const *s, unsigned int start, size_t len);
void				local_vars_init(int flags[11], int (*local_vars)[3],
									char (*all)[16], int vars[9]);
char				*double_to_str(double c, char ls[3]);
int					ft_max(int a, int b);
void				all_filling_hex(char (*all)[16], int fl);
int					ft_round_hex(double a);
void				to_filling(int j, char **to, int vars[9], char **main_str);
char				*double_to_hex(double a, int vars[9],
									int flags[11], char **main_str);
int					print_end(char sign, int num, char *tmp, int flags[11]);
int					add_0x(int flags[11], char ls[3], char *res);
int					free_double_str(char *double_str);
double				double_abs(double num);
unsigned long long	power(unsigned long long num, int power);
int					ft_round(char **head, char **tail, int nul_l[2], char up);
int					convert_e(char up, int i, int nul_l[2], int flags[11]);
char				*nan_inf(double num, char up);
int					round_f(char **head, char **tail, int l, int i);
int					round_g(char **head, char **tail, int i, char up);
int					float_rigth_nuls_spaces(double num, char *fr, int nul,
		int flags[11]);
int					print_float(double num, int n_l[2], char up, int f[11]);
int					ft_min(int a, int b);
int					put_lost_nul(int length, char *tail);
int					put_spaces(double num, int flags[11]);
size_t				ft_strlen_wstr(wchar_t *wstr, int flags[11]);
int					ft_abs(int a);

#endif
