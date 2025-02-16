# copied over solution from C to this file here
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
    

class Rectangle:
    def __init__(self, upper_left=Point, lower_right=Point):
        self.upper_left=upper_left
        self.lower_right=lower_right
    
    def __repr__(self):
        return "Rectangle(%r, %r)" % (self.upper_left, self.lower_right)
    def area(self):
        return abs(self.lower_right.x -self.upper_left.x)*abs(self.lower_right.y-self.upper_left.y)
    def perimeter(self):
        return 2*(abs(self.lower_right.x-self.upper_left.x)+abs(self.upper_left.y-self.lower_right.y))
    def translate(self, dx, dy):
        return Rectangle(self.upper_left.translate(dx, dy), self.lower_right.translate(dx, dy))
