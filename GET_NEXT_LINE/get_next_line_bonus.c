/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:44:00 by hsachie           #+#    #+#             */
/*   Updated: 2026/07/01 19:20:12 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	ft_getc(int fd)
{
	static char	buf[OPEN_MAX][BUFFER_SIZE];
	static char	*bufp[OPEN_MAX];
	static int	n[OPEN_MAX];

	if (fd < 0 || fd >= OPEN_MAX)
		return (EOF);
	if (n[fd] == 0)
	{
		n[fd] = read(fd, buf[fd].buf, BUFFER_SIZE);
		bufp[fd] = buf[fd];
		if (n[fd] <= 0)
		{
			n[fd] = 0;
			return (EOF);
		}
	}
	if (--n >= 0)
	{
		return ((unsigned char)*bufp++);
	}
	return (EOF);
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
		{
			free(str->str);
			*str = (t_string){NULL, 0, 0};
			return (-1);
		}
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

	ret.str = NULL;
	ret.len = 0;
	ret.capa = 0;
	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break ;
		if (ft_putc(&ret, c) == -1)
			return (NULL);
		if (c == '\n')
			break ;
	}
	if (ret.len > 0)
		ft_putc(&ret, '\0');
	return ((char *)ret.str);
}
