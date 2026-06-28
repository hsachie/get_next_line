/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:11:58 by hsachie           #+#    #+#             */
/*   Updated: 2026/06/28 18:12:52 by hsachie          ###   ########.fr       */
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

typedef struct s_string
{
	unsigned char	*str;
	size_t			len;
	size_t			capa;
}					t_string;

void	*ft_memcpy(void *dest, const void *src, size_t n);
int					getchar(void);

#endif
