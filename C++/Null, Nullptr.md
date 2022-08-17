# ポインタの初期化
C++ではポインタを初期化するとき、nullではなく、nullptrを使うことが指向されている。\
ならnullとnullptrはどう違うのだろうか。\
先ずは次のコードの結果を見てみよう。

``` cpp
#include <iostream>

using std::cout;
using std::endl;

void po(void* a) {
	cout << __FUNCSIG__ << endl;
	//cout << __PRETTY_FUNCTION__ << endl; //g++では__FUNCSIG__を使えない。
}

void po(int a) {
	cout << __FUNCSIG__ << endl;
	//cout << __PRETTY_FUNCTION__ << endl; //g++では__FUNCSIG__を使えない。
}

int main() {
	cout << "po(0) : ";
	po(0);
	cout << "po(NULL) : ";
	po(NULL);
	cout << "po(nullptr) : ";
	po(nullptr);

	return 0;
}
```
上記のソースコードは関数poを呼び出した引数がポインタかint型かによって出力される内容が変わるコードである。\
もしNULLがポインタであるのであれば、po(NULL)はpo(void *)を出力しなければならない。

### Visual Studio 2022での結果
``` 
po(0) : void __cdecl po(int)
po(NULL) : void __cdecl po(int)
po(nullptr) : void __cdecl po(void *)
```

### g++での結果
```
nullptr_test01.cpp:18:11: error: call of overloaded 'po(NULL)' is ambiguous
	18 | 		po(NULL);
	   |
nullptr_test01.cpp:6:6: note: candidate: 'void po(void*)'
	 6 | void po(void* p){
	   |
nullptr_test01.cpp:10:6: note: candidate: 'void po(int)'
	10 | void po(int p){
	   |
```
しかしながら、結果の通りVisual Studio 2022で使われているコンパイラーではNULLをint型として扱い、g++では関数を呼び出すには生煮えだとエラーを発生させている。\
それに比べてnullptrはVisual Studio 2022でも、g++でもエラーを発生させずpo(void *)でポイントであることを確かにしている。\
このことを整理すると、基本的にNULLは整数の0として扱われてあり、生煮えなタイプで状況によってはエラーを発生させることがあるため、ポインタを初期化する際には、nullptrを用いることが安全性的な側面でも有効