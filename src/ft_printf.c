/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 16:49:11 by eniini            #+#    #+#             */
/*   Updated: 2021/04/04 17:34:45 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
**	ANSI C-compliant printf implementation mainly in style of glibc.
**	Supports writing to file descriptors via ft_fprintf(2).
**	Has additional locale-agnostic support for wide characters (UTF-8).
*/

#include "ft_printf.h"

/*
**	Catches unsupported inputs after the control character.
*/

static void		ftprintf_typecheck(t_printf *f, const char *s)
{
	if (*s == 's')
		ftprintf_str(f);
	else if (*s == 'c')
		ftprintf_c(f);
	else if (*s == 'd' || *s == 'i')
		ftprintf_convert_i(f);
	else if (*s == 'u' || *s == 'o' || *s == 'x' || *s == 'X')
		ftprintf_convert_ui(f, s);
	else if (*s == 'f')
		ftprintf_convert_f(f);
	else if (*s == 'p')
		ftprintf_convert_p(f, s);
	else if (*s == '%')
	{
		ft_putchar_fd('%', f->fd);
		f->writecount++;
	}
	else
		ft_getout(CONVERR);
}

static void		printf_reset(t_printf *f)
{
	f->data.s = NULL;
	f->data.ws = NULL;
	f->conversion = NULL;
	f->info = (t_info){0, 0, 0, 0, 0, 0,
	0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
}

static t_printf	*printf_init(const int fd)
{
	t_printf	*f;

	if (!(f = (t_printf*)malloc(sizeof(t_printf))))
		ft_getout(MEMERR);
	f->writecount = 0;
	f->fd = fd;
	return (f);
}

/*
**	Writes results to stdout.
*/

int				ft_printf(const char *s, ...)
{
	t_printf	*f;
	int			ret_count;

	f = printf_init(1);
	va_start(f->args, s);
	while (*s && *s != '\0')
	{
		if (*s == '%')
		{
			s++;
			printf_reset(f);
			s = ftprintf_read_args(s, f);
			ftprintf_typecheck(f, s);
			s++;
		}
		else
			f->writecount += write(1, s++, 1);
	}
	va_end(f->args);
	ret_count = (int)f->writecount;
	free(f);
	return (ret_count);
}

/*
**	Writes results to file descriptor [fd].
*/

int				ft_fprintf(const int fd, const char *s, ...)
{
	t_printf	*f;
	int			ret_count;

	f = printf_init(fd);
	va_start(f->args, s);
	while (*s && *s != '\0')
	{
		if (*s == '%')
		{
			s++;
			printf_reset(f);
			s = ftprintf_read_args(s, f);
			ftprintf_typecheck(f, s);
			s++;
		}
		else
			f->writecount += write(f->fd, s++, 1);
	}
	va_end(f->args);
	ret_count = (int)f->writecount;
	free(f);
	return (ret_count);
}
