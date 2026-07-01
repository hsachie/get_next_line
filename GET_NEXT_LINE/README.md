*This project has been created as part of the 42 curriculum by hasachie*

# get_next_line

static変数を使ったバッファリングにより、ファイルディスクリプタから1行ずつ読み込むC言語の関数です。

***

## 概要

`get_next_line` は呼び出すたびに、ファイルディスクリプタから改行文字を含む1行を返します。K&Rの `getchar` 実装を参考にした内部バッファリングにより、`read` システムコールの呼び出し回数を最小限に抑えています。

## 関数プロトタイプ

```c
char *get_next_line(int fd);
```

**戻り値：** 次の1行を含むnull終端文字列。EOFまたはエラー時は `NULL`。返された文字列は呼び出し側で `free` する必要があります。

***

## ファイル構成

```
get_next_line.h              ← 通常版ヘッダー
get_next_line.c              ← ft_getc / ft_putc / get_next_line
get_next_line_utils.c        ← ft_memcpy

get_next_line_bonus.h        ← ボーナス版ヘッダー（t_buf構造体を追加）
get_next_line_bonus.c        ← ft_getc（複数fd対応版）/ ft_putc / get_next_line
get_next_line_utils_bonus.c  ← ft_memcpy（通常版と同じ内容）
```

***

## 実装設計

複雑な分岐を避けるため、2つの小さな関数を組み合わせる設計にしています。

### ft_getc — バッファリング付き1文字読み込み

staticバッファが空になったときだけ `read` を呼び出し、最大 `BUFFER_SIZE` バイトを一度に取得します。これによりシステムコールのオーバーヘッドを削減しつつ、ロジックをシンプルに保ちます。

```c
int ft_getc(int fd);  // 次の1文字を返す。終端・エラーならEOF
```

### ft_putc — 動的文字列ビルダー

`t_string` 構造体に1文字ずつ追記します。バッファが足りなくなったらcapaを2倍にして再確保するため、長さNの行に対して再確保はO(log2(N))回で済みます。

```c
typedef struct s_string {
    unsigned char   *str;   // 文字列
    size_t          len;    // 文字列の長さ
    size_t          capa;   // 確保済み領域のサイズ
}   t_string;

***

## 使い方

### 通常版

```c
#include "get_next_line.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd;
    char    *line;

    fd = open("file.txt", O_RDONLY);
    while (1)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break ;
        printf("%s", line);
        free(line);
    }
    close(fd);
    return (0);
}
```

### ボーナス版（複数fd同時読み込み）

```c
#include "get_next_line_bonus.h"
#include <fcntl.h>
#include <stdio.h>

int main(void)
{
    int     fd1;
    int     fd2;
    char    *line;

    fd1 = open("test1.txt", O_RDONLY);
    fd2 = open("test2.txt", O_RDONLY);

    line = get_next_line(fd1); printf("fd1: %s", line); free(line);
    line = get_next_line(fd2); printf("fd2: %s", line); free(line);
    line = get_next_line(fd1); printf("fd1: %s", line); free(line);
    line = get_next_line(fd2); printf("fd2: %s", line); free(line);

    close(fd1);
    close(fd2);
    return (0);
}
```

***

## コンパイル

### 通常版

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl && ./gnl
```

### ボーナス版

```bash
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus && ./gnl_bonus
```

***

## 設計上の判断

| 判断ポイント | 選択 | 理由 |
|---|---|---|
| readバッファの置き場所 | スタック領域（`buf[BUFFER_SIZE]`） | readバッファにmallocは不要 |
| 行データの置き場所 | ヒープ領域（動的 `t_string`） | 行の長さはコンパイル時に不明 |
| capa増加方式 | オーバー時に2倍 | 再確保がO(log2(N))回 |
| メモリ vs 速度 | 速度優先（返却前に縮小しない） | 余分なmalloc/memcpyを避ける |

***

## 注意事項

- 機械採点対策として `sizeof(buf)` ではなく `BUFFER_SIZE` を `read` の引数に使うこと
- static変数はC言語仕様により0またはNULLに自動初期化される（ISO/IEC 9899 §6.7.8）
- エラー発生時は途中まで構築した `ret.str` を必ず `free` してメモリリークを防ぐこと
- ボーナス版のファイル名は必ず `_bonus` サフィックスをつけること（42の採点ルール）

***

## バッファサイズについて

`read` 時のバッファリングは **4096バイト以上に上げてもパフォーマンス向上はほぼない**とされています（『Linuxプログラミングインターフェース』表13-1より）。また逆に巨大すぎるバッファサイズはCPUキャッシュが効かなくなり、速度が落ちる場合もあります。

***

### 参考文献

-
- 42 Tokyo ft_printf subject
- B.W.カーニハン / D.M.リッチー, 『プログラミング言語C 第2版』, p.209–210

### AI の使用について

AI（Perplexity）をデバッグ・概念理解・コードレビュー・Makefile 作成の補助として使用しました。構文エラーの特定や `va_list` の使い方の確認などに活用しました。
