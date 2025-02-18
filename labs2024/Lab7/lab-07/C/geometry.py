import math
class Point:

    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __repr__(self):
        return "Point(%r, %r)" % (self.x, self.y)

    def delta_x(self, dx):
        return Point(self.x+dx, self.y)
    def delta_y(self, dy):
        return Point(self.x, self.y+dy)
    def translate(self, dx, dy):
        return Point(self.x+dx, self.y+dy)# copied over the solution from part B into this file.
    
class Circle:
    def __init__(self, center=Point(), radius=0):
        self.r = radius
        self.c = center
        
    def __repr__(self):
        return "Circle(%r, %r)" % (self.c, self.r)
    
    def area(self):
        return math.pi*self.r**2
    
    def perimeter(self):
        return math.pi*2*self.r
    
    def translate(self, dx, dy):
        return Circle(self.c.translate(dx, dy), self.r)
    
