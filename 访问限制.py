#由于类可以起到模板的作用，因此，可以在创建实例的时候，
# 把一些我们认为必须绑定的属性强制填写进去。
# 通过定义一个特殊的__init__方法，在创建实例的时候，就把name，score等属性绑上去
class Student(object):
    def __init__(self ,name ,score):
        self.name = name
        self.score = score
        self.__privatename = name 
    def print_score(self): #封装数据的函数是和Student类本身是关联起来的 称之为类的方法
        print("%s %s"%(self.name ,self.score))
Bart= Student("bart",32)
Bart.print_score()
'''
实例的变量名如果以__开头，就变成了一个
私有变量（private），只有内部可以访问，外部不能访问

以双下划线开头，并且以双下划线结尾的，是特殊变量，特殊变量是可以直接访问的

不能直接访问__name是因为Python解释器对外把__name变量改成了_Student__name，
所以，仍然可以通过_Student__name来访问__name变量
'''
Bart.__privatename = 'ha'
Bart.print_score()
'''
表面上看，外部代码“成功”地设置了__name变量，但实际上这个__name变量和
class内部的__name变量不是一个变量！内部的__name变量已经被
Python解释器自动改成了_Student__name，而外部代码给bart新增了一个__name变量
'''
