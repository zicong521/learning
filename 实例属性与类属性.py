class Student():
    name_class ='student'
    count =0 
    def __init__(self , name):
        self.name = name
        Student.count +=1 #类属性在内部调用时格式:   类名.属性名
s = Student('x')
p = Student('s')
s.score = 90
print(s.name_class)
print(s.count)
'''
给实例绑定属性的方法是通过实例变量，或者通过self变量

也可以直接在class中定义属性，这种属性是类属性，归Student类所有
这个属性虽然归类所有，但类的所有实例都可以访问到

在编写程序的时候，千万不要对实例属性和类属性使用相同的名字，
因为相同名称的实例属性将屏蔽掉类属性，但是当你删除实例属性后，
再使用相同的名称，访问到的将是类属性
'''
