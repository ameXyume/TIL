# 関数のオーバーロード
C++では名前が同じでもパラメータが異なるとその関数の宣言は正しいと認められ、それを関数のオーバーロード(多重定義)と呼ぶ。\
オーバーロードされた関数の呼び出すときには、パラメータの数が同じで、関数の定義が最も近い関数が呼び出される。\
ここで、関数の定義が最も近い関数とは以下の例のようなものである。
```cpp
#include <iostream>

using std::cout;
using std::endl;

int print(int a);

int main(){
    double a = 3.14
    cout << print(a) << endl;
}

int print(int a){
    a = a << 2;
    return a;
}
```
ソースコードを見ると、int型のパラメータを要求するprint関数にmain関数はint型ではなく、double型のパラメータを送っている。\
この場合、データ型が違うためエラーを起こすと思われるかも知れないが、実際はdoubleをint型に変えることが出来るため、定義が最も近い関数のint型のprint関数を呼び出すことになる。

# 実験
パラメータとしてint, intを要求する関数と、double, doubleを要求する関数をオーバーロードして、intとdoubleをパラメータとして持つ関数と呼び出すとどうなるのだろうか。\
個人的な仮説は直截な関係はないが、&&文のように前の条件を先に比較した後に後ろの条件を比較する。つまり、評価順序は前から行われるはずだと考えた。
```cpp
#main.cpp

#include <iostream>
#include "print.h"

using std::cout;
using std::endl;

int main(){
    cout << "(3) : " << print(3) << endl;
    cout << "(3.14) : " << print(3.14) << endl;
    cout << "(3, 3.14) : " << print(3, 3.14) << endl;
    cout << "(3.14, 3) : " << print(3.14, 3) << endl;
}

```
```cpp
#print.h

#ifdef PRINT_H
#define PRINT_H

#include <string>
using std::string;

string print(int const a);
string print(double const a);
string print(int const a, int const b);
string print(double const a, double const b);

#endif
```

```cpp
#print.cpp

#include <iosream>
#include <string>

using namespace std;

string print(int const a){
    return __PRETTY_FUNCTION__;
}
string print(double const a){
    return __PRETTY_FUNCTION__;
}
string print(int const a, int const b){
    return __PRETTY_FUNCTION__;
}
string print(double const a, double const b){
    return __PRETTY_FUNCTION__;
}
```
# 結果
print(3)とprint(3.14)は予想通りそれぞれstd::string print(int)とstd::String print(double)を返したが\
print(3, 3.14)とprint(3.14, 3)は仮説とは違う結果を見せてくれた。
```
main.cpp:10:40: error: call of overloaded 'print(int, double)' is ambiguous
    10 |    cout << "(3, 3.14) : " << print(3, 3.14) << endl;
       |
print.h:9:8: note: candidate: 'std::string print(int, int)' 
     9 | string print(int const a, int const b);
       |
print.h:10:8: note: candidate: 'std::string print(double, double)' 
    10 | string print(double const a, double const b);
       |
main.cpp:11:40: error: call of overloaded 'print(double, int)' is ambiguous
    11 |    cout << "(3.14, 3) : " << print(3.14, 3) << endl;
       |
print.h:9:8: note: candidate: 'std::string print(int, int)' 
     9 | string print(int const a, int const b);
       |
print.h:10:8: note: candidate: 'std::string print(double, double)' 
    10 | string print(double const a, double const b);
       |
```
実行結果、print(3, 3.14)とprint(3.14, 3)は呼び出す関数が曖昧であるとエラーを起こしてしまった。\
この実験の結果からオーバーロードされた関数を呼び出す時には、十分注意し、オーバーロードした関数のパラメータが似ている場合には、なるべくオーバーロードせず、関数名を分けた方が安全性の側面では有利だと思われる。