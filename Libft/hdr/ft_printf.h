/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stouitou <stouitou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/27 09:34:02 by stouitou          #+#    #+#             */
/*   Updated: 2024/03/21 11:16:56 by stouitou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include "./libft.h"
# include <stdarg.h>

typedef struct s_print
{
	va_list	args;
	int		txt;
	int		col;
	int		sp;
	int		wdt;
	int		tl;
}	t_print;

/* PRINTF */
int		ft_printf(const char *format, ...);
int		ft_eval_format(t_print *tab, const char *str, int i);
void	ft_checkcase(t_print *tab, char c);
char	*pf_addprefix(t_print *tab);
void	pf_print_prefix(t_print *tab);
void	pf_putchar(t_print *tab);
void	pf_putstr(t_print *tab, char *str);
void	pf_putptr(t_print *tab);
void	pf_putnbr(t_print *tab);
void	pf_putu_base(t_print *tab, size_t n, char *base);
int		pf_unbrlen_base(size_t n, char *base);

/* FPRINTF */
int		ft_fprintf(int fd, const char *format, ...);
int		fpf_eval_format(int fd, t_print *tab, const char *str, int i);
void	fpf_checkcase(int fd, t_print *tab, char c);
void	fpf_print_prefix(int fd, t_print *tab);
void	fpf_putchar(int fd, t_print *tab);
void	fpf_putstr(int fd, t_print *tab, char *str);
void	fpf_putptr(int fd, t_print *tab);
void	fpf_putnbr(int fd, t_print *tab);
void	fpf_putu_base(int fd, t_print *tab, size_t n, char *base);

#endif
