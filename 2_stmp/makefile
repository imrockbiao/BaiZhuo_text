obj=main.o deal.o check.o base.o
tar=main

$(tar) : $(obj)
	gcc $(obj) -o $(tar)

%.o : %.c
	gcc -c $< -o $@

.PHONY: clean
clean:
	-rm $(obj) -f

# 同样声明debuginfo为伪目标
.PHONY: debuginfo
debuginfo:
	gcc *.c -D DEBUG -g -o $(tar)






# 在目标和依赖中：
# $.o 规则匹配， 当前文件下的所有  .o  文件
# $.c 规则匹配， 当前文件下的所有  .c  文件

# makefile中的自动变量， 规则不同， 那么makefile的自动变量也有不一样的值
# $< 匹配规则中的第一个依赖，gcc mai.o， gcc deal.o，gcc check.o，gcc base.o
# $@ 匹配规则中的目标 main.o
# $^ 规则中的所有依赖，只能在规则中的命令中使用

# 声明伪目标， 防止伪目标clean与当前目录下的文件名为clean的文件发生冲突
# 声明为伪目标以后就不会与当前文件夹下的文件去进行时间比对了
# 忽略命令 - 忽略不能执行的命令， 如： -rm *.o，当当前目录下没有.o文件时会自动向下执行， 不会卡在此处
# .PHONY: clean
# clean:
# 	-rm $(obj) -f