/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:11:58 by hsachie           #+#    #+#             */
/*   Updated: 2026/07/01 19:54:38 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef EOF
#  define EOF -1
# endif

typedef struct s_string
{
	unsigned char	*str;
	size_t			len;
	size_t			capa;
}					t_string;

void				*ft_memcpy(void *dest, const void *src, size_t n);
int					getchar(void);
int					ft_putc(t_string *str, unsigned char c);
char				*get_next_line(int fd);

#endif
