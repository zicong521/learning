#由于类可以起到模板的作用，因此，可以在创建实例的时候，
# 把一些我们认为必须绑定的属性强制填写进去。
# 通过定义一个特殊的__init__方法，在创建实例的时候，就把name，score等属性绑上去
class Student(object):
    def __init__(self ,name ,score):
        self.name = name
        self.score = score
    def print_score(self): #封装数据的函数是和Student类本身是关联起来的 称之为类的方法
        print("%s %s"%(self.name ,self.score))
Bart= Student("bart",32)
Bart.print_score()



