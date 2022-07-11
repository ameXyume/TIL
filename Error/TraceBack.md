# Tracebackエラー 
#### Traceback (most recent call last):
#### File "C:\Pr_py\main.py", line 5, in <module>
    import vlc
#### File "C:\Users\KRKM\AppData\Local\Programs\Python\Python310\lib\site-packages\vlc.py", line 220, in <module>
    dll, plugin_path  = find_lib()
#### File "C:\Users\KRKM\AppData\Local\Programs\Python\Python310\lib\site-packages\vlc.py", line 180, in find_lib
    dll = ctypes.CDLL('.\\' + libname)
#### File "C:\Users\KRKM\AppData\Local\Programs\Python\Python310\lib\ctypes\__init__.py", line 374, in __init__
    self._handle = _dlopen(self._name, mode)
FileNotFoundError: Could not find module 'C:\Pr_py\libvlc.dll' (or one of its dependencies). Try using the full path with constructor syntax.

ファイルの重さによりpygameからvlcに乗り換えを行った時に生じたエラーで、関数の呼び出しを逆参照したものである。
その下にエラーを起こしたコードが順に並べてくる。今回Tracebackが起きた原因は最後の文章よりlibvlc.dllを見つけられなかったことにあると思われる。

Python3.8ではWindowsでctypeでロードされたDLLの従属性がより安全になり、PATHやCWDはもうdllに影響を行わないようになっている。そのため、dllを追加するには、DLLやPYDファイルを含めたディレクトリーをadd_dll_directory()を用いて追加する必要がある。

#### つまり、PATHやCWDはadd_dll_directoryで明示的にそのディレクトリーを追加しなければいけない。検索経路にcwdを追加するのは
    import os
    os.add_dll_directory(os.getcwd())
で追加できる。

これでエラーの原因は把握が出来たので、エラーの解決に取り組もう。先ずはlibvlc.dllをインストールする必要がある。そのため、libvlc.dllの入手する方法を探って見たが、VLCのプログラムをインストールするだけで、libvlc.dllはいじらなくても使えるようである。
https://get.videolan.org/vlc/3.0.11/win64/vlc-3.0.11-win64.exe

上のリンクからVLCをインストールし、Tracebackが起きたファイルを実行してみた結果、エラーは解決され正常に動いた。
