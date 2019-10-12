import types
print(type(123))
def fn():
    pass
print(type(fn) == types.FunctionType)
print(isinstance(123,int))
'''
总是优先使用isinstance()判断类型，可以将指定类型及其子类“一网打尽
'''

print(dir("acx"))

print("acx".__len__())

'''
如果要获得一个对象的所有属性和方法，可以使用dir()函数，
它返回一个包含字符串的list，比如，获得一个str对象的所有属性和方法

类似__xxx__的属性和方法在Python中都是有特殊用途的，比如__len__方法返回长度。
在Python中，如果你调用len()函数试图获取一个对象的长度，
实际上，在len()函数内部，它自动去调用该对象的__len__()方法
'''

class MyObject(object):
    def __init__(self):
        self.x = 9
    def power(self):
        return self.x * self.x 
obj = MyObject()
print(hasattr(obj ,'y',))
setattr(obj,'y',19)
print(getattr(obj,'z',404))
'''
配合getattr()、setattr()以及hasattr()，我们可以直接操作一个对象的状态
获取属性'z'，如果不存在，返回默认值404
'''
def readImage(fp):
    if hasattr(fp, 'read'):
        return readData(fp)
    return None
'''
假设我们希望从文件流fp中读取图像，我们首先要判断该fp对象是否存在read方法，
如果存在，则该对象是一个流，如果不存在，则无法读取。
'''