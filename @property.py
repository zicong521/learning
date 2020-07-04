'''
@property装饰器就是负责把一个方法变成属性调用的
'''
class Student(object):
    def get_score(self):
        return self._score
    def set_score(self,score):
        if not isinstance(score,int):
            raise ValueError("wrong!")
        if score <0 or score > 100:
            raise ValueError('wrong!!')
        self._score = score
