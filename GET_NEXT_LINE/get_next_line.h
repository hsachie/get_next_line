/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:11:58 by hsachie           #+#    #+#             */
/*   Updated: 2026/06/29 23:04:27 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h> // malloc, free
# include <unistd.h> // read, close

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef EOF    // もし EOF がまだ定義されていなければ
#  define EOF -1 // EOF = -1 という「名前」を定義する
# endif

typedef struct s_buf
{
    char    buf[BUFFER_SIZE];
    char    *bufp;
    int     n;
}   t_buf;

typedef struct s_string
{
	unsigned char	*str; //「1文字を文字列に追加する」 関数。足りなければメモリを増やす。
	size_t			len; // 今何文字入ってるか
	size_t			capa; //何文字分の箱があるか 
}					t_string;
//str  → [a][a][a][ ][ ][ ][ ][ ]
        //↑文字が入ってる    ↑空き
//len  = 3   （今3文字入ってる）
//capa = 8   （箱は8個ある）

void	*ft_memcpy(void *dest, const void *src, size_t n);
int					getchar(void);
int	ft_putc(t_string *str, unsigned char c);
char *get_next_line(int fd);

#endif
