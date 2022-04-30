
# SPEC学习

## `1%{?dist}`的意思

[Whats the meaing of 1%{?dist} in SPEC file in RPM package - stack overflow](https://stackoverflow.com/questions/25508687/whats-the-meaing-of-1dist-in-spec-file-in-rpm-package)

```bash
$  rpm -E 'foo:%{foo}' -E 'bar:%{?bar}'
foo:%{foo}
bar:

$ rpm -D 'foo foov' -E 'foo:%{foo}' -E 'bar:%{?bar}'
foo:foov
bar:

$ rpm -D'foo foov' -D 'bar barv' -E 'foo:%{foo}' -E 'bar:%{?bar}'
foo:foov
bar:barv
```

如果`%{?bar}`中的`bar`变量有定义，那么会正常输出`bar`中的内容；如果未定义，则不输出
对于`%{foo}`来说，如果`foo`变量有定义，那么正常输出`foo`中内容；如果未定义，则输出变量名`foo`

那么`1`和`dist`呢？

等编译完成后再作检查吧**__MARK__**

注：关于`-E`与`-D`

```bash
$ rpm --help | grep '\-E'
-E, --eval='EXPR'                  print macro expansion of EXPR

$ rpm --help | grep '\-D'
-D, --define='MACRO EXPR'          define MACRO with value EXPR
```
