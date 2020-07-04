# 可以给实例绑定一个方法
from types import MethodType
class Student(object):
    __slots__= ('name','age')
s=Student()
def set_age(self,age): # 定义实例方法
    self.age = age
s.set_age = MethodType(set_age,s) #给实例绑定方法
s.set_age(12)
print(s.age)
'''
为了达到限制的目的，Python允许在定义class的时候，
定义一个特殊的__slots__变量，来限制该class实例能添加的属性

用__slots__要注意，__slots__定义的属性
仅对当前类实例起作用，对继承的子类是不起作用的
除非在子类中也定义__slots__，这样，
子类实例允许定义的属性就是自身的__slots__加上父类的__slots__
'''