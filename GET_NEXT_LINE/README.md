*This project has been created as part of the 42 curriculum by hasachie*

# get_next_line

## 概要

`get_next_line` は、与えられたファイルディスクリプタから改行 (`\n`) までの
1文字ずつを読み込み、1行分の文字列として返す関数です。
繰り返し呼び出すことで、ファイルの内容を先頭から1行ずつ順番に取得できます。


| 戻り値 | 条件 |
|---|---|
| 読み込んだ1行（改行文字 `\n` を含む） | 正常時 |
| NULL | 読み込むものがない・ファイル終端・read()エラー時 |

## ディレクトリ構成

```
GET_NEXT_LINE/
├── get_next_line.c              # 必須課題本体
├── get_next_line.h
├── get_next_line_utils.c        # ft_memcpyなどのユーティリティ
├── get_next_line_bonus.c        # ボーナス課題（複数fd対応版）
├── get_next_line_bonus.h
├── get_next_line_utils_bonus.c
├── main.c                       # 動作確認用
└── test.txt                     # テスト用サンプルファイル
```

## 実装のポイント

この関数は、1文字ずつファイルから取得する `ft_getc` と、
取得した文字を1文字ずつ格納していく `ft_putc` の2つの関数を組み合わせて
1行分の文字列を組み立てています。

`get_next_line` はこの2つの関数を交互に呼び出し、改行 (`\n`) が出てくるまで
「1文字取得 → 格納」を繰り返し、最終的に1行分の文字列を完成させます。

### ft_getc（1文字を取得する関数）

ファイルから1文字ずつ返す関数です。ただし、1文字ごとに毎回 `read()` を
呼ぶと処理が遅くなるため、`BUFFER_SIZE` 個分をまとめて先読みしておき、
そこから1文字ずつ取り出す仕組みになっています。

- `buf` : 先読みした文字を一時的に保持する配列（バッファ）
- `n` : バッファ内にまだ取り出していない文字が何個残っているか
- `idx` : バッファ内で次に取り出すべき文字の位置

バッファの中身を使い切ったら（`n` が0になったら）、再度 `read()` で
次の `BUFFER_SIZE` 個分を読み込みます。

具体例（BUFFER_SIZE = 4、ファイルの中身が "abcdefg\n" の場合）：

\`\`\`
1回目のread()  → buf = [a][b][c][d] を読み込み
呼び出し1回目 → 'a' を返す
呼び出し2回目 → 'b' を返す
呼び出し3回目 → 'c' を返す
呼び出し4回目 → 'd' を返す（ここでbufを使い切る）

2回目のread() → buf = [e][f][g][\n] を読み込み
呼び出し5回目 → 'e' を返す
...
\`\`\`

### ft_putc（1文字を格納する関数）

`ft_getc` が取得した文字を、`t_string` 構造体に1文字ずつ格納していく関数です。

`t_string` の容量（`capa`）が不足した場合、`malloc` で現在の2倍の
サイズを再確保し、既存のデータをコピーしてから新しい文字を追加します。
これにより、行の長さが事前に分からなくても対応できます。

\`\`\`
初期容量: 42バイト
容量が不足 → 84バイトに再確保
さらに不足 → 168バイトに再確保（以降も倍々に拡張）
\`\`\`

### get_next_line（処理全体の流れ）

`ft_getc` と `ft_putc` を交互に呼び出しながら、以下の手順で
1行分の文字列を組み立てます。

1. `ft_getc` で1文字取得する
2. 取得した文字を `ft_putc` で `t_string` に格納する
3. 取得した文字が `\n` の場合、1行分の読み込みが完了したためループを終了する
4. ファイルの終端に達した場合、またはエラーが発生した場合もループを終了する

### エラーと終端の区別

読み込みが終了する理由には「ファイルの終端に達した（正常）」場合と
「read() が失敗した（異常）」場合の2種類があるため、それぞれ別の値で
区別しています。

| 値 | 名前 | 意味 |
|---|---|---|
| -1 | `EOF` | ファイルの終端に達した（正常終了） |
| -2 | `GNL_ERR` | read() が失敗した（異常終了） |

## t_string構造体

\`\`\`c
typedef struct s_string
{
    unsigned char *str;   // 文字列本体
    size_t        len;    // 現在格納されている文字数
    size_t        capa;   // 確保されている容量
}   t_string;
\`\`\`

`len`（現在の文字数）が `capa`（確保済み容量）に達するたびに、
容量を2倍にして再確保する可変長バッファです。初期容量は42バイトで、
必要に応じて84バイト、168バイトと自動的に拡張されます。
## 必須課題とボーナス課題の違い

| 項目 | 必須課題 | ボーナス課題 |
|---|---|---|
| 対応fd数 | 1つのみ | 複数（`OPEN_MAX`まで） |
| static変数 | `buf`, `n`, `idx` を単体で保持 | `t_buf bufs[OPEN_MAX]` の配列（staticは1個） |
| バッファの持ち方 | `buf` を固定長配列で保持 | `buf` はポインタで保持し、実体は`malloc`で確保 |
| ヘッダー | get_next_line.h | get_next_line_bonus.h |
| 追加定義 | なし | `OPEN_MAX` (1024) |

ボーナス版では `t_buf` 構造体（`buf`, `idx`, `n`）をfdの数だけ配列として持つことで、
異なるfdを交互に読み込んでも、それぞれの読み込み位置が独立して保持されます。

#### バッファをmallocで持つ理由

ボーナス版で気をつけたのは、各fdの読み込みバッファ `buf` を
**固定長配列ではなくポインタにして、必要になったときだけ `malloc` する**点です。

仮に `unsigned char buf[BUFFER_SIZE]` を構造体に直接埋め込むと、
それを `OPEN_MAX`（1024）個ぶん配列で持つことになります。
このとき `BUFFER_SIZE` が非常に大きい値（例：10,000,000）だと、
`10,000,000 × 1024 ≒ 約10GB` を一度に確保しようとして
プログラムが強制終了（Killed）されてしまいます。

そこで、`buf` はポインタとして宣言し、そのfdを最初に読み込むタイミングで
`malloc(BUFFER_SIZE)` し、読み終わり（EOF）やエラー発生時に `free` して
`NULL` に戻すようにしました。これにより、実際に確保されるメモリは
**「同時に開いているfdの数 × BUFFER_SIZE」** だけで済み、
`BUFFER_SIZE` がどれだけ大きくてもメモリを使いすぎず正しく動作します。

```c
typedef struct s_buf
{
    unsigned char *buf;   // 読み込みバッファ（実体はmallocで確保）
    int           idx;    // 次に取り出す位置
    int           n;      // バッファ内の残り文字数
}   t_buf;

static t_buf bufs[OPEN_MAX];  // staticはこの1個だけ
```

## コンパイル方法

\`\`\`bash
# 必須課題
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line.c get_next_line_utils.c main.c -o gnl

# ボーナス課題
cc -Wall -Wextra -Werror -D BUFFER_SIZE=42 get_next_line_bonus.c get_next_line_utils_bonus.c main.c -o gnl_bonus
\`\`\`

`BUFFER_SIZE` はコンパイル時に自由に指定可能で、値の大小に関わらず
正しく1行ずつ読み込めることが本課題の評価ポイントです。


### 参考文献

- 1時間で書くGet Next Line(GNL)(https://zenn.dev/grigri_grin/articles/bf45a9fa50f25f)
- 42 Tokyo get_next_line subject

### AI の使用について

AIをデバッグ・概念理解・コードレビューの補助として使用しました。

