'''
在OOP程序设计中，当我们定义一个class的时候，可以从某个现有的class继承，
新的class称为子类（Subclass），而被继承的class称为基类、
父类或超类（Base class、Super class）
'''
class Animal(object):
    def run(self):
        print("animal is running")
class Dog(Animal):
    def run(self):
        print("dog is running")
class Cat(Animal):
    def run(self):
        print("cat is running")
dog = Dog()
dog.run()
'''
当子类和父类都存在相同的run()方法时，我们说，
子类的run()覆盖了父类的run()，在代码运行的时候，
总是会调用子类的run()。这样，我们就获得了继承的另一个好处：多态

当我们定义一个class的时候，我们实际上就定义了一种数据类型。
我们定义的数据类型和Python自带的数据类型，比如str、list、dict没什么两样
'''
b = Animal()
print(isinstance(b,Dog))
'''
在继承关系中，如果一个实例的数据类型是某个子类，
那它的数据类型也可以被看做是父类。但是，反过来就不行
'''
def run_twice(Animal):
    Animal.run()
    Animal.run()
run_twice(Cat())
'''
对于一个变量，我们只需要知道它是Animal类型，无需确切地知道它的子类型，
就可以放心地调用run()方法，而具体调用的run()方法是作用在Animal、Dog、Cat
还是Tortoise对象上，由运行时该对象的确切类型决定，这就是多态真正的威力：
调用方只管调用，不管细节，而当我们新增一种Animal的子类时，只要确保run()方法编写正确，
不用管原来的代码是如何调用的。这就是著名的“开闭”原则：

对扩展开放：允许新增Animal子类；
对修改封闭：不需要修改依赖Animal类型的run_twice()等函数。
'''

class People(object):
    def run(self):
        print("I am a duck")
'''
对于静态语言（例如Java）来说，如果需要传入Animal类型，
则传入的对象必须是Animal类型或者它的子类，否则，将无法调用run()方法。
对于Python这样的动态语言来说，则不一定需要传入Animal类型。我们只需要保证传入的对象有一个run()方法就可以了

这就是动态语言的“鸭子类型”，它并不要求严格的继承体系，一个对象只要“看起来像鸭子，走起路来像鸭子”，那它就可以被看做是鸭子
'''
run_twice(People())
