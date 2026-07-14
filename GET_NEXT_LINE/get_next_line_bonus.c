/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:44:00 by hsachie           #+#    #+#             */
/*   Updated: 2026/07/14 12:23:11 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static void	clear_buf(t_buf *b)
{
	free(b->buf);
	b->buf = NULL;
	b->idx = 0;
	b->n = 0;
}

static int	fill_buf(t_buf *b, int fd)
{
	if (b->buf == NULL)
	{
		b->buf = malloc(BUFFER_SIZE);
		if (b->buf == NULL)
			return (GNL_ERR);
	}
	b->n = read(fd, b->buf, BUFFER_SIZE);
	b->idx = 0;
	if (b->n < 0)
		return (clear_buf(b), GNL_ERR);
	if (b->n == 0)
		return (clear_buf(b), EOF);
	return (0);
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

int	ft_getc(int fd)
{
	static t_buf	bufs[OPEN_MAX];
	int				status;

	if (fd < 0 || fd >= OPEN_MAX)
		return (EOF);
	if (bufs[fd].n <= 0)
	{
		status = fill_buf(&bufs[fd], fd);
		if (status != 0)
			return (status);
	}
	bufs[fd].n--;
	return ((unsigned char)bufs[fd].buf[bufs[fd].idx++]);
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
