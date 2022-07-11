# Pushする時、Github内のディレクトリーを設定する方法
TILを作成した後、種類別に集めるためGithub内にディレクトリーを作成したが、PushをしてもディフォルトのmainにPushされてしまった。もちろん、Githubから手作業で直接ディレクトリーを変更することもできるが、そうするとコミットメッセージが変更されてしまう問題があった。

この状況を解決するために
```
git push <リモートリポジトリ> <ブランチ>

git push origin/Error
git push main/Error
git push origin main/Error
git push origin Master/Error
```
のコードを試して見たが、git pushの書き方のようにpushはremote repoとbranchだけを入れて、ディレクトリー名を入れてはいけない。

やり方としては、リモートリポジトリと繋がっているローカルリポジトリにディレクトリーを追加してから
```
git add .
git commit -m "コミットメッセージ"
git push origin
```
を行えば良い。

#### この時、git.をローカルリポジトリから新しく作ったディレクトリーに追加してはいけない。
恐らく、他の操作を行おうとしていたネット上の情報をみて、git.を移していたが、このことが原因で解決するのにかなり時間を消耗してしまった。