/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:44:00 by hsachie           #+#    #+#             */
/*   Updated: 2026/07/07 22:40:00 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_getc(int fd)
{
	static t_buf	bufs[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX)
		return (EOF);
	if (bufs[fd].n <= 0)
	{
		bufs[fd].n = read(fd, bufs[fd].buf, BUFFER_SIZE);
		bufs[fd].idx = 0;
		if (bufs[fd].n < 0)
		{
			bufs[fd].n = 0;
			return (GNL_ERR);
		}
		if (bufs[fd].n == 0)
			return (EOF);
	}
	bufs[fd].n--;
	return ((unsigned char)bufs[fd].buf[bufs[fd].idx++]);
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

char	*get_next_line(int fd)
{
	t_string	ret;
	int			c;

	if (fd < 0 || fd >= OPEN_MAX || BUFFER_SIZE <= 0)
		return (NULL);
	ret.str = NULL;
	ret.len = 0;
	ret.capa = 0;
	c = ft_getc(fd);
	while (c != EOF && c != GNL_ERR)
	{
		if (ft_putc(&ret, (unsigned char)c) == -1)
			return (NULL);
		if (c == '\n')
			break ;
		c = ft_getc(fd);
	}
	if (c == GNL_ERR)
		return (free(ret.str), NULL);
	if (ret.len == 0)
		return (free(ret.str), NULL);
	if (ft_putc(&ret, '\0') == -1)
		return (NULL);
	return ((char *)ret.str);
}
