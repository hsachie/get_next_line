/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:44:33 by hsachie           #+#    #+#             */
/*   Updated: 2026/07/13 19:05:00 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef EOF
#  define EOF -1
# endif

# ifndef GNL_ERR
#  define GNL_ERR -2
# endif

# ifndef OPEN_MAX
#  define OPEN_MAX 1024
# endif

typedef struct s_buf
{
	unsigned char	*buf;
	int				idx;
	int				n;
}	t_buf;

typedef struct s_string
{
	unsigned char	*str;
	size_t			len;
	size_t			capa;
}	t_string;

void	*ft_memcpy(void *dest, const void *src, size_t n);
int		ft_putc(t_string *str, unsigned char c);
int		ft_getc(int fd);
char	*get_next_line(int fd);

#endif
