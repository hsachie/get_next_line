/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:11:58 by hsachie           #+#    #+#             */
/*   Updated: 2026/07/07 21:56:44 by hsachie          ###   ########.fr       */
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
#  define EOF (-1)
# endif

# ifndef GNL_ERR
#  define GNL_ERR (-2)
# endif

typedef struct s_string
{
	unsigned char	*str;
	size_t			len;
	size_t			capa;
}	t_string;

char	*get_next_line(int fd);
int		ft_getc(int fd);
int		ft_putc(t_string *str, unsigned char c);
void	*ft_memcpy(void *dst, const void *src, size_t n);

#endif