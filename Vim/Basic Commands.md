# 概要
Vimとは等作成予定

# レベル別おすすめコマンド
例外はいくらでもあるが、基本的に最初は大文字は小文字の機能をより強化していると考えれば楽。\
[1] いくつのコマンドは前に数字を入れることで、その命令を数字回繰り返すことが出来る。
## Level 0
### カーソル移動
|コマンド|機能|
|-------|----|
|h|左に移動|
|j|下に移動|
|k|上に移動|
|l|右に移動|
|w|次の単語の先頭に移動|
|e|次の(若しくは今の)単語の末尾に移動|
|b|前の(若しくは今の)単語の先頭に移動|

### 入力モード (Insert Mode)
|コマンド|機能|
|-------|----|
|i|カーソルの左から入力|
|I|行頭から入力|
|a|カーソルの右から入力|
|A|行末から入力|
|o|改行して入力|
|O|改行を行って、その上の行で入力|

### コマンドモード
|コマンド|機能|
|-------|----|
|ESC|コマンドモードに戻る|

### ファイル保存、終了 (CLIじゃなければやらなくてもok)
|コマンド|機能|
|-------|----|
|:w|ファイルを保存|
|:q|変更されていないファイルを閉じる|
|:wq|ファイルを保存してから閉じる|
|:w!|ファイルを強制的に保存|
|:q!|変更されているファイルでも保存せず強制的に閉じる|

このコマンドはCLIでコーディングしている訳でない以上そこまで重要ではないが、慣れておくと便利ではある。

## Level 1
### カーソル移動
|コマンド|機能|
|-------|----|
|$|行末に移動(キーボードのEndのような機能)|
|^, 0|行頭に移動(キーボードのHomeのような機能)|

### 選択モード (Visual Mode)
|コマンド|機能|
|-------|----|
|v|選択モード(文字単位)|
|V|選択モード(行単位)|
|y|選択されたものをコピー|
|x|選択されたものを切り取る|
|d|選択されたものを消す|
|p|コピー、切り取りしたものをカーソルの後にペスト|
|P|コピー、切り取りしたものをカーソルの前にペスト|

選択モードじゃないときxを押すとカーソルが位置した1文字を切り取ることが出来る。\
コピー、切り取りしたのが行単位である場合、カーソルの下(p)か上(P)にペストされる。\
選択モードじゃないとき、[dd]を押すとその行を全部削除、[yy]を押すとその行を全部コピーする。
<details>
<summary>クリックすると例文が表示されます。</summary>

``` java
(例)
SL.add(new Student("鈴木", 170, 52))

カーソルを位置して、yy5pを押すと以下のようになる。

SL.add(new Student("鈴木", 170, 52))
SL.add(new Student("鈴木", 170, 52))
SL.add(new Student("鈴木", 170, 52))
SL.add(new Student("鈴木", 170, 52))
SL.add(new Student("鈴木", 170, 52))
SL.add(new Student("鈴木", 170, 52))
```
<details>
<summary>なぜ5もペストされたのか</summary>
[1] いくつのコマンドは前に数字を入れることで、その命令を数字回繰り返すことが出来る。<br>
pはこもコマンドに該当する。
</details>
</details>

## Level2
### 移動
|コマンド|機能|
|-------|----|
|Ctrl + d|画面を半分分下に移動|
|Ctrl + u|画面を半分分上に移動|
|<<|選択されたか、カーソルが位置している行をShiftwidth(Tabキー)1個分右にずらす|
|>>|選択されたか、カーソルが位置している行をShiftwidth(Tabキー)1個分左にずらす|

[Ctrl + d]、[Ctrl + u]は100行以上の十分に長い試すことをおすすめする。\

### dの活用
|コマンド|機能|
|-------|----|
|D|カーソルから行末まで削除|
|d[カーソル移動命令]|カーソルから移動した位置まで削除|
|diw|カーソルが位置している単語を削除|
|di(, di)|カーソルが位置した括弧内をすべて削除|
|da(, da)|カーソルが位置した括弧を含めて括弧内をすべて削除|

(や、)の代わりに{, ', ". [などを利用することを有効である。
<details>
<summary>クリックすると例文が表示されます。</summary>

``` java
SL.add(new Student("鈴木", 170, 52))
カーソルがStudentのuにあるとして、diw
SL.add(new ("鈴木", 170, 52))

SL.add(new Student("鈴木", 170, 52))
カーソルがStudentのuにあるとして、di(
SL.add()

SL.add(new Student("鈴木", 170, 52))
カーソルが鈴木の鈴にあるとして、da)
SL.add(new Student)

SL.add(new Student("鈴木", 170, 52))
//カーソルが鈴木の鈴にあるとして、di"
SL.add(new Student("", 170, 52))
```
</details>

<details>
<summary>クリックするとd[カーソル移動命令]の例が表示されます。</summary>

いくつか例外はあるが、多くのd[カーソル移動命令]では、<sup>[1]</sup>コマンドの前に数字を入力して数字回繰り返すことが有効である。\
ここでnが数字として、順番は[n]d[移動]でも、d[n][移動]でも構わない。
|コマンド|機能|
|-------|----|
|dw|カーソルから次の単語の先頭まで削除(先頭含まず)|
|de|カーソルから次の(若しくは今の)単語の末尾まで削除|
|db|カーソルから前の(若しくは今の)単語の先頭まで削除(カーソル含まず)|
|dj|カーソルが位置した行から下の行まで削除(下の行含む)|
|dk|カーソルが位置した行から上の行まで削除(上の行含む)|
|d$|カーソルから行末まで削除|
|d0, d^|カーソルから行頭まで削除|

```
(例)
modify the phase variance
カーソルが行頭にあるとして、2dw
phase variance

modify the phase variance
カーソルが行頭にあるとして、d2e
 phase variance (theとphaseの間のスペースが残っている)

modify the phase variance
カーソルがphaseのsにあるとして、db
modify the se variance

modify the phase variance
food for thought
black sheep well
there is no cow level
カーソルがfood for thoguhtの真ん中にあるとしてd2j
modify the phase variance
```
</details>

### その他
|コマンド|機能|
|-------|----|
|/[文字列]|ファイル内で文字列を検索|
|s|選択されたか、カーソルが位置した文字を消して、入力モード|
|r[文字]|選択されたか、カーソルが位置した文字を入力した文字に変更|


## 応用文法
普通のコマンドも一部該当されるが\
Visual Studio CodeのVimなど本物のVimではなく\
**Vimの機能を一部具現しただけの拡張機能では**特にこの応用文法の一部が具現されていなく、**使えない場合が多い。**

### 文字列修正
2022/10/06基準 Visual Studio対応
|コマンド|機能|
|-------|----|
|:%s/[修正前の文字列]/[修正後の文字列]/g|ファイル内にあるすべての[修正前の文字列]を[修正後の文字列]に書き換える|

``` java
(例)
List<String> list1 = new ArrayList<>();
list1.add("赤");
list1.add("青");
list1.add("黄");

:%s/list1/color/g

List<String> color = new ArrayList<>();
color.add("赤");
color.add("青");
color.add("黄");
```
詳しい説明や、オプションをここで説明するには、量が多すぎるため<a href = "https://github.com/ameXyume/TIL/blob/main/Vim/The%20Replacement%20of%20Character.md">以前作成した文書 </a> を参考\
クリックで入れなかった場合、ページの上端左にある<> Codeを押して、Vim → The Replacement of Character.md順で入れば良い。

### 文字列を含めた行削除
2022/10/06基準 Visual Studio非対応
|コマンド|機能|
|-------|----|
|:%g/[文字列]/d|文字列を含む行をすべて削除|

``` java
(例)
List<String> list1 = new ArrayList<>();
list1.add("赤");
list1.add("青");
List<String> list2 = new ArrayList<>();
list2.add("青");

:%g/list1/d

List<String> list2 = new ArrayList<>();
list2.add("青");


//Idを出力する。
System.out.println(Id);
//PWを出力する
System.out.println(PW);

:%g/\/\//g

System.out.println(Id);
System.out.println(PW);
```
詳しい説明や、オプションをここで説明するには、量が多すぎるため<a href = "https://github.com/ameXyume/TIL/blob/main/Vim/Clear%20Line.md">以前作成した文書 </a> を参考\
クリックで入れなかった場合、ページの上端左にある<> Codeを押して、Vim →  Clear Line.md順で入れば良い。

### 選択した行を修正
2022/10/06基準 Visual Studio非対応
|コマンド|機能|
|-------|----|
|:norm [命令]|選択された行に命令を行う|

まだ詳しく調べてはないが、恐らく$等の正規表現を支援すると予想している。

``` java
(例)
List<String> list1 = new ArrayList<>();
list1.add("赤");
list1.add("青");
List<String> list2 = new ArrayList<>();
list2.add("青");

List<String> list1から list1.add("青");まで選択し、:norm wi//

//List<String> list1 = new ArrayList<>();
//list1.add("赤");
//list1.add("青");
List<String> list2 = new ArrayList<>();
list2.add("青");

この状態で同じ部分を選択し、:norm w2x

List<String> list1 = new ArrayList<>();
list1.add("赤");
list1.add("青");
List<String> list2 = new ArrayList<>();
list2.add("青");
```
使っているだけで、まだ勉強していないため、詳しい説明は出来ない。