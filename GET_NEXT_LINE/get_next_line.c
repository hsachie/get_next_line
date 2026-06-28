/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:11:54 by hsachie           #+#    #+#             */
/*   Updated: 2026/06/28 18:47:00 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_getc(int fd)
{
	static char buf[BUFFER_SIZE]; //読み取った文字を溜めておく配列
	static char *bufp;            // 今どこまで読んだかを示すポインタ
	static int n = 0;             // バッファに残っている文字数
	if (n == 0)
	{
		n = read(fd, buf, BUFFER_SIZE);
		bufp = buf;
	}
	return ((--n >= 0) ? (unsigned char)*bufp++ : EOF);
}

int	ft_putc(t_string *str, unsigned char c)
{
	size_t			new_capa;
	unsigned char	*new_str;

	if (str->len + 1 >= str->capa)
	{
		new_capa = (str->capa == 0) ? 42 : str->capa * 2;
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

char *get_next_line(int fd)
{
	t_string ret;
	int	c;

	ret.str = NULL;
	ret.len = 0;
	ret.capa = 0;

	while (1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break;

		ft_putc(&ret, c);

		if (c == '\n')
			break;
	}
	if (ret.len > 0)
		ft_putc(&ret, '\0');

	return ret.str;
}
