# ビット演算子
 * ビット単位での演算を行うための演算子のこと。
 * 算術・論理演算子に比べ、使う頻度が少なく、忘れやすい。
    * 具体例を入れて、確実に覚える。
 * 種類
    * シフト演算子
    * 論理演算子

# シフト演算子
 * <<と、>>がある。
 * ビット単位で括弧の矢印の方向にシフト
    * ex) <<だったら左にシフト
 * bit単位であるため、*2若しくは/2のn乗で計算できる。
    * ex) <<3で、左に3だけシフトだったら*(2^3)で掛け8
    * ex) >>5で、右に5だけシフトだったら/(2^5)で割り32
 * 残りが生じた場合は切り捨て
```cpp
例題1
#include <iostream>

using namespace std;

int main(){
    unsigned int byte = 4; //2進数だと 0100
    cout << "first byte : " << byte << endl;
    byte <<= 2; // 左に2だけシフト 0001 0000
    cout << "second byte : " << byte << endl;
    byte >>= 5; // 右に5だけシフト 0000 0000
    cout << "third byte : " << byte << endl;
}
```
```
出力例1
first byte : 4
second byte : 16
third byte : 0
```

# 論理演算子
 * ビット演算子でも論理演算子を提供する。
 * andは \&
    * 両方とも1のとき1
 * orは \|
    * 片方でも1であれば1
 * xorは \^
    * 片方だけが1であれば1
    * 両方とも0もしくは、1で同じだったら0
 * notは \~
    * \~変数名だったら0と1が反転
``` cpp
例題2
#include <iostream>

using namespace std;

int main(){
    //0xで始まる整数は16進数での数字を意味する。
    unsigned int i = 0x03; // 0x03は0011
    unsigned int j = 0x05; // 0x05は0101

    cout << "and : " << i&j << endl;    // 0001
    cout << "or : " << i|j << endl;     // 0111
    cout << "xor : " << i^j << endl;    // 0110
    i = ~i; // iは1100
    cout << "not i, and : " << i&j << endl; // 0100
}
```
```
出力例2
and : 1
or : 7
xor : 6
not i, and : 4
```
# 使いどころ
* そのままでの使い方もあるとは思うが、今回はステータスを表示するときを述べる。
* もちろん、ゲームのステータスでも使うことは出来る。
    * 別の文書で作成予定
* 今回はウィンドウを例に述べる。
1. unsigned int window_status = 0で初期化された4byte(32bit)の変数を考える。\
0000 0000 0000 0000 0000 0000 0000 0000で初期化されているはず。
2. 1bit目では閉じるボタンを生成するか否かを決定する。
3. 2bit目では画面の最大化/元に戻すボタンを生成するか否かを決定する。
4. 3bit目では最小化ボタンを生成するか否かを決定する。
5. 4bit目ではウィンドウのサイズ変更を許可するか否かを決定する。
6. 5bit目ではウィンドウの位置を変えられるか否かを決定する。
7. などなどで、ウィンドウのステータスを決めて、許可する場合には1、許可しない場合は0を入力する
```cpp
例題3
#define close   0x01 // 0000 0001
#define max_win 0x02 // 0000 0010
#define min_win 0x04 // 0000 0100
#define con_siz 0x08 // 0000 1000
#define mov_win 0x10 // 0001 0000

int main(){
    unsigned int window_status = 0; // 0000 0000 0000 0000 0000 0000 0000 0000
    /*
    以下、window_statusは1byte(0000 0000)だけ表示させる
    閉じるボタンは無し。
    画面の最大化は許可する。
    画面の最小化は無し。
    ウィンドウのサイズは変更できない
    ウィンドウの位置は変えられる
    との条件んでwindow_statusを変更させるなら
    */
    window_status |= max_win; // 0000 0000 |= 0000 0010 -> 0000 0010
    window_status |= mov_win; // 0000 0001 |= 0001 0000 -> 0001 0010

    /*
    プログラムの途中に
    最大化の設定をoffにして
    最小化の設定をonにしたいとき
    */
    window_status &= ~max_win; //0001 0010 &= 1111 1101 -> 0001 0000
    // window_status ^= max_win;は、もし1、1ではなく0、1だったときに1になってしまう。
    window_status |= min_win; // 0001 0000 |= 0000 0100 -> 0001 0100

    /*
    プログラムの途中に
    ウィンドウの位置を変えようとしたとき
    */
    if(window_status & mov_win){ // 0001 0100 & 0001 0000 -> 0001 0000 != 0 -> true

    }
    /*
    プログラムの途中に
    ウィンドウのサイズを変えようとしたとき
    */
    if(window_status & con_siz){ // 0001 0100 & 0000 1000 -> 0000 0000 == 0 -> false

    }
}
```