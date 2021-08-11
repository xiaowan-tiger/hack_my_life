# Notes

## `find -size c` 根据大小查找 xxc  —> xx字节

## `find -user admin -group super` 根据用户名，根据组名查找

## `cat ./-` 查看以 “-” 开头的内容

## sort、uniq

![image-20210808212411324](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/bandit/img/img:image-20210808212411324.png)

先排序、再查找唯一性

## base64 decode

![image-20210808213052480](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/bandit/img/img:image-20210808213052480.png)

## level 24:

1. 在bash中生成连续的数字

   `#!/bin/bash`

   `for i in {000..9999}`

   `do`

   `.... $i`    <---- 0001, 0456 增加前导零

   `done`

2. 向本地端口发送 信息

   `cat readme | nc localhost 8080`

