/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:44:49 by hsachie           #+#    #+#             */
/*   Updated: 2026/07/13 19:00:00 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char		*d;
	const unsigned char	*s;
	size_t				i;

	if (!dest && !src)
		return (NULL);
	d = (unsigned char *)dest;
	s = (const unsigned char *)src;
	i = 0;
	while (i < n)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}

int	ft_putc(t_string *str, unsigned char c)
{
	size_t			new_capa;
	unsigned char	*new_str;

	if (str->len + 1 >= str->capa)
	{
		if (str->capa == 0)
			new_capa = 42;
		else
			new_capa = str->capa * 2;
		new_str = malloc(new_capa);
		if (new_str == NULL)
			return (free(str->str), -1);
		if (str->len > 0)
			ft_memcpy(new_str, str->str, str->len);
		free(str->str);
		str->str = new_str;
		str->capa = new_capa;
	}
	str->str[str->len++] = c;
	return (0);
}
