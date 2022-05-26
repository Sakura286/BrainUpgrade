
# 一对破问题

rpm --showrc | less

基于上几次内容打包

git format-patch HEAD^  有几个^就会打几个patch，从最近一次打起

git format-patch HEAD^^ 最近的二个patch内容

以下代码作用同上
git format-patch -1
git format-patch -2

## 问题：

"/lib/cpp" fails sanity check

网上都说装gcc-c++什么的，结果我这边装了kernel-header好了

osc build --no-verify

osc meta prj -e
#节省worker资源
#在末尾</project>之前插入
  <build>
    <disable/>
  </build>
#以禁止整个项目的在线构建

echo ".osc/" >> .git/info/exclude

