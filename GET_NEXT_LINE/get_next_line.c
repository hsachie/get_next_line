/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:11:54 by hsachie           #+#    #+#             */
/*   Updated: 2026/06/24 12:42:49 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	getchar(void)
{
	static char buf[BUFFER_SIZE]; //読み取った文字を溜めておく配列
	static	char *bufp;      // 今どこまで読んだかを示すポインタ
	static	int n = 0;      // バッファに残っている文字数

	if (n == 0)
	{
		n = read(0, buf, sizeof buf);
		bufp = buf;
	}
	return (--n >= 0) ? (unsigned char) *bufp++ : EOF;
}



#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int	main(void)
{
	int	fd;
	int	c;

	fd = open("test.txt", O_RDONLY);
	while(1)
	{
		c = ft_getc(fd);
		if (c == EOF)
			break;
		printf("%c", c);
	}
	close(fd);
	return (0);
}
