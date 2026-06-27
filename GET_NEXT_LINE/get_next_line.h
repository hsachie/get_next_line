/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:11:58 by hsachie           #+#    #+#             */
/*   Updated: 2026/06/24 12:52:08 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>  // read, close
# include <stdlib.h>  // malloc, free

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 42
# endif

# ifndef EOF         // もし EOF がまだ定義されていなければ
#  define EOF -1     // EOF = -1 という「名前」を定義する
# endif

int	getchar(void);

#endif
