Git的报错
在使用Git的过程中有时会出现一些问题，那么在解决了每个问题的时候，都需要去总结记录下来，下次不再犯。

一、fatal: refusing to merge unrelated histories
今天在使用Git创建项目的时候，在两个分支合并的时候，出现了下面的这个错误。

~/SpringSpace/newframe on  master ⌚ 11:35:56
$ git merge origin/druid
fatal: refusing to merge unrelated histories
1
2
3
这里的问题的关键在于：fatal: refusing to merge unrelated histories
你可能会在git pull或者git push中都有可能会遇到，这是因为两个分支没有取得关系。那么怎么解决呢？

二、解决方案
在你操作命令后面加--allow-unrelated-histories
例如：
git merge master --allow-unrelated-histories

~/SpringSpace/newframe on  druid ⌚ 11:36:49
$ git merge master --allow-unrelated-histories
Auto-merging .gitignore
CONFLICT (add/add): Merge conflict in .gitignore
Automatic merge failed; fix conflicts and then commit the result.
1
2
3
4
5
如果你是git pull或者git push报fatal: refusing to merge unrelated histories
同理：
git pull origin master --allow-unrelated-histories
等等，就是这样完美的解决咯！
————————————————
版权声明：本文为CSDN博主「向小凯同学学习」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
原文链接：https://blog.csdn.net/wd2014610/article/details/80854807