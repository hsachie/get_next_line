/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/29 12:44:00 by hsachie           #+#    #+#             */
/*   Updated: 2026/06/29 12:49:38 by hsachie          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int     ft_getc(int fd)
{
    static t_buf    bufs[OPEN_MAX]; // ← 配列になった

    if (fd < 0 || fd >= OPEN_MAX)
        return (EOF);
    if (bufs[fd].n == 0) // ← bufs[fd].がついた
    {
        bufs[fd].n = read(fd, bufs[fd].buf, BUFFER_SIZE);
        bufs[fd].bufp = bufs[fd].buf;
        if (bufs[fd].n <= 0)
        {
            bufs[fd].n = 0;
            return (EOF);
        }
    }
    return ((--bufs[fd].n >= 0) ? (unsigned char)*bufs[fd].bufp++ : EOF);
}

int     ft_putc(t_string *str, unsigned char c)
{
    size_t          new_capa;
    unsigned char   *new_str;

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

char    *get_next_line(int fd)
{
    t_string    ret;
    int         c;

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