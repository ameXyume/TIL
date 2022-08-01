# C++でのクォーテーション
Stringに関する勉強を進んでる途中、Stringの中の空欄を除いたchar型文字をxに置換するのに下のコードでエラーが出てしまった。
```cpp
#include <iostream>
#include <string>

using std::cout;
using std::endl;
using std::cin;
using std::string;

int main() {
	string hello = "Hello World!!!";
	//char x = "x";
	//string x = "x";
	for (auto& c : hello) {
		decltype(c) x = "x";
		if (isgraph(c))
			c = x;
			//c = "x";
	}
	cout << hello << endl;
}
```
String型のHelloに含まれている文字列のすべての文字を一つずつ取り出し、空欄だけ除く作業までは行えたが何故かその文字をxに変えることが出来なかった。

その原因はクォーテーションにあって、簡単に言うと**ダブルクォーテーションは文字列を、シングルクォーテーションは文字を**返却する。
上記のコードでのcはchar型の文字であることが定まれているため文字列を意味するダブルクォーテーションを使ったのが原因となり\
`c = 'x';`\
に書き換えることでこの問題を解決することが出来た。

# シングルクォーテーション

# ダブルクォーテーション
 * " " :
 * " "s :
 * " "sv : 