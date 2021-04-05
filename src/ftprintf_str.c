/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ftprintf_str.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eniini <eniini@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/22 12:08:25 by eniini            #+#    #+#             */
/*   Updated: 2021/04/04 19:47:50 by eniini           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static size_t	get_size(t_printf *f, size_t strl)
{
	if (f->info.i_prec)
	{
		if (f->info.width > f->info.i_prec)
			return (f->info.width);
		if (f->info.width > strl)
			return (f->info.width);
		if (strl < f->info.i_prec)
			return (strl);
		return (f->info.i_prec);
	}
	if (f->info.width > strl)
		return (f->info.width);
	return (strl);
}

/*
**	If width is larger than strl, we know to that incoming str must be shifted
**	to either side of the output.
**	Precisions smaller than [strl] result in data truncation.
*/

void			ftprintf_print_str(t_printf *f)
{
	size_t	strl;
	size_t	output_size;
	size_t	offset;
	char	*str;
	char	*p;

	strl = ft_strlen(f->conversion);
	output_size = get_size(f, strl);
	if (!(str = ft_strnew(output_size)))
		ft_getout(MEMERR);
	ft_memset(str, ' ', output_size);
	offset = (f->info.i_prec && f->info.i_prec < strl) ? f->info.i_prec : strl;
	if (!f->info.i_prec)
		p = &str[(f->info.width < strl) ? 0 : f->info.width - strl];
	else
		p = &str[(f->info.width < offset) ? 0 : f->info.width - offset];
	ft_memcpy(((f->info.left) ? str : p), f->conversion, offset);
	ft_putstr_fd(str, f->fd);
	f->writecount += ft_strlen(str);
	free(str);
	free(f->conversion);
}

/*
**	User can specify both zero precision and a specific (minimum) width,
**	so that is handled here as well.
*/

static void		print_str_extend(t_printf *f)
{
	char	*s;

	if (f->info.zero_prec)
	{
		if (!(s = ft_strnew(f->info.width + 1)))
			ft_getout(MEMERR);
		ft_memset(s, ' ', f->info.width);
		ft_putstr_fd(s, f->fd);
		f->writecount += f->info.width;
		free(s);
		free(f->conversion);
		return ;
	}
	if (f->data.ws)
	{
		ft_putwstr(f->data.ws, f->fd);
		f->writecount += ft_wstrlen(f->data.ws);
	}
	else
		ftprintf_print_str(f);
}

/*
**	NULL pointers are defined to print out "(null)"
**	in par with Berkeley/Sun implementation.
*/

void			ftprintf_str(t_printf *f)
{
	if (f->info.is_long)
		f->data.ws = va_arg(f->args, wchar_t*);
	else
	{
		f->data.s = va_arg(f->args, char*);
		if (f->data.s == NULL && !f->info.is_long)
			f->conversion = ft_strdup("(null)");
		else if (f->data.s)
			f->conversion = ft_strdup(f->data.s);
		if (!(f->conversion))
			ft_getout(MEMERR);
	}
	if (f->data.ws == NULL && f->info.is_long)
	{
		if (!(f->data.ws = ft_memalloc(sizeof(wchar_t) * 7)))
			ft_getout(MEMERR);
		ft_memcpy((void*)f->data.ws, (void*)L"(null)", sizeof(wchar_t) * 6);
	}
	print_str_extend(f);
}
