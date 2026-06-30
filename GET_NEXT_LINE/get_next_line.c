/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hsachie <hsachie@student.42.jp>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/06/23 12:11:54 by hsachie           #+#    #+#             */
/*   Updated: 2026/06/30 12:41:53 by hsachie          ###   ########.fr       */
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
		n = read(fd, buf, BUFFER_SIZE); //fdのファイルからBUFFER_SIZE読んで、buf[0]から順番に入れてね
		bufp = buf; //「bufpに0番目のアドレスを入れる」=「0番目を指してね」
		if(n <= 0) // 0（EOF）か マイナス（エラー）だったら
		{
			n = 0; // ← n がマイナスのままだと次回おかしくなるので0にリセット
			return (EOF); 
		}
	}
	return ((--n >= 0) ? (unsigned char)*bufp++ : EOF); //三項演算子　条件 ? trueのとき : falseのとき　YES → 今の文字を返してbufpを進める
}

int	ft_putc(t_string *str, unsigned char c) //「1文字を文字列に追加する」 関数。足りなければメモリを増やす。
{
	size_t			new_capa; // 新しい箱の大きさ（まだ中身なし）
	unsigned char	*new_str; // 新しい箱のポインタ（まだ中身なし）

	if (str->len + 1 >= str->capa) //strっていう箱の中のlenとcapaを見ている、「1文字追加したら箱がいっぱいになる？」
	{
		new_capa = (str->capa == 0) ? 42 : str->capa * 2; //if文に入ったら、capaが０だったら42確保、それ以外はcapaを２倍する
		new_str = malloc(new_capa);
		if (new_str == NULL)
		{
			free(str->str); // 今まで使ってた古い箱をfreeする
			*str = (t_string){NULL, 0, 0}; // 構造体を空にリセット
			return (-1); // 「失敗したよ！」とget_next_lineに伝える		
		}
		if (str->len > 0) //古い中身を新しい箱にコピー（中身があるときだけ！）
			ft_memcpy(new_str, str->str, str->len);
		free(str->str); //古い箱を捨てて、新しい箱に切り替え
		str->str = new_str;
		str->capa = new_capa;
	}
	str->str[str->len++] = c; // 末尾に1文字追加（lenも+1）
	return (0);
}

char *get_next_line(int fd)
{
	t_string ret;
	int	c;

	ret.str = NULL; //retという箱を空っぽの状態にリセット！
	ret.len = 0;
	ret.capa = 0;

	while (1) // 無限ループ（breakするまで続ける）
	{
		c = ft_getc(fd); //ファイルから1文字読む
		if (c == EOF) // ファイルの終わりに達したら
			break;  // ループを抜ける
		if(ft_putc(&ret, c) == -1) // retに1文字追加、失敗したら
			return (NULL); // NULLを返して終了
		if (c == '\n') // 改行が来たら
			break; // ループを抜ける
	}
	if (ret.len > 0)
		ft_putc(&ret, '\0');

	return ((char *)ret.str); 
}
