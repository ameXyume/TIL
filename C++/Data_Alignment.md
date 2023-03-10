# Data Alignment
0~5の整数でゲームの難易度を設定する変数diff_valを考える。\
このdiff_valは3bitでも十分な変数である。\
enumや、フラグなどは考えずに、基本的なデータ型のみを考える。\
3bitで表せるため、4byte(32bit)のintを使う必要もなく、1byte(8bit)のunsigned charでも十分なはず。\
これで、無駄なメモリ空間を最小化して、メモリ不足を防げたと思ったなら、それは誤っている。

## データ構造アライメントとは
* 殆どのCPUは**決められたワード(word)を読み書きするのに最適化**されている。
    * ワードとは、メモリに保存される単位の一つで、CPUが一度に処理できるデータのサイズを表す。
    * 一般的にワードは4byteになっている。
    * 一般的に4byteである理由は、かつて使われてきた殆どのCPUが32bitアーキテクチャを使用していたからだと推測される。\
    このことを前提で考えると、64bitアーキテクチャを使用するCPUが増えた今は8byteのワードサイズを使用するケースもあると思われる。\
    しかし、未だに32bitアーキテクチャを使用するシステムも多いため、4bteワードサイズは相変わらず重要な役割を持っているはずで、そもそも**あくまでも推測**であるため、もう少し**根拠を調べる必要がある。**
* データを保存するとき、決められたサイズのメモリーアドレスに位置させることを称する。
* 決められたサイズのメモリーアドレスとは、一般的にワードの倍数である。
    * ワードが4byteだとすると、以下のようになる。(ただし、paddingは起きている。)
        ``` cpp
        例題1
        #include <iostream>
        using namespace std;

        struct Example{
            char c;
            int i;
            short s;
        };

        int main(){
            Example ex;
            cout << "Size of char : " << sizeof(char) << endl;
            cout << "Size of int : " << sizeof(int) << endl;
            cout << "Size of short : " << sizeof(short) << endl;
            cout << "Size of Example : " << sizeof(Example) << endl;

            cout << "Address of c : " << (void *)&ex.c << endl;
            cout << "Address of i : " << (void *)&ex.i << endl;
            cout << "Address of s : " << (void *)&ex.s << endl;

            return 0;
        }
        ```
        ```
        出力例1
        Size of char : 1
        Size of int : 4
        Size of short : 2
        Size of Example : 12

        Address of c : 0x7ffc6a1bcf00
        Address of c : 0x7ffc6a1bcf04
        Address of c : 0x7ffc6a1bcf08
        ```
    * 4の倍数に合わせるためにcharは1byte、shortは2byteにも関わらずそれぞれ4バイトずつ使われ、アドレスを見るとcharの次に来るintも4の倍数のアドレスで保存されている。
    * なぜこんなことが出来るかは後ほど説明する。
* x86ではCPUの最適化条件であるため、これにより処理速度は上昇される。
* また、同じくx86ではunalignedであっても割ってでも読み取る機能がある
* その時、遅くなるか最悪、意図しなかった結果が出る可能性がある。
* また、atomicさもなくなる問題もある。
* armではunalignedだとexceptionが出てしまう。

## パディング (Padding)
* データ構造アライメントで説明したよう、CPUはワード単位で読み書きするのに最適化されている。
* それのために、変数のサイズをワードのサイズに合わせるパディングを追加することができる。
* 例題1をまた見て見よう。
    * 見ると、charとintの間に3byteが空いている。
    * その空き容量3byteがパディングされている部分である。
    * 同じく、shortは2byteだが、struct Exampleの総サイズは12byteになっている。
    * これもshortの後に2byteがpaddingされているからである。

## C++でもパディング
* C++では、構造体(struct)及び、クラス(class)を用いてデータ型を定義することができる。
* structやclass内部のメンバ変数は連続的にメモリ空間に割り当てられる。
* しかし、structやclassメンバ変数の中にはワードサイズより小さいサイズの変数がある可能性がある。
* このような場合、structやclass内部にパーディングされ、変数のサイズをワードのサイズに合わせてくれる。
* このパディングはstructやclassの宣言順序や変数のサイズによって追加される。
* 最初に戻って、このパディングにより、unsigned intを定義してもunsigned charを定義してもパディングによって4byteとして扱われるのは一緒である。
* unsigned charを4byteの倍数となるように配列を作るのであれば、paddingは起こらず、無駄になるメモリはなくなる。
* 次は、structやclassで変数を宣言する順序によってサイズが変わる例題である。
    ``` cpp
    例題2
    #include <iostream>

    using namespace std;

    struct Example1 {
        char c;
        int i;
        short s;
    };

    struct Example2 {
        char c;
        short s;
        int i;
    };

    int main() {
        cout << "Size of Example1 : " << sizeof(Example1) << endl;
        cout << "Size of Example2 : " << sizeof(Example2) << endl;

        return 0;
    }
    ```
    ```
    出力例2-1
    Size of Example1 : 12
    Size of Example1 : 8
    ```
    * Example1では、1 (char) + 3 (padding) + 4 (int) + 2 (short) + 2 (padding) = 12byte
    * Example2では、1 (char) + 1 (padding) + 2 (short) + 4 (int) = 8byte
    * でサイズが設定されている。
    * もし、パディングが起こらなかったとしたら
    ```
    出力例2-1
    Size of Example1 : 7
    Size of Example1 : 7
    ```
    * Example1では、1 (char) + 4 (int) + 2 (short) = 7
    * Example2では、1 (char) + 2 (short) + 4 (int) = 7
    * になっているはず。