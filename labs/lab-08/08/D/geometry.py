"""
Ashton Majachani
SENG 265 Lab 8
Due 03.15.2025
"""

import math
import doctest

class Point:
    def __init__(self, x=0, y=0):
        self.x = x
        self.y = y

    def __repr__(self):
        return f"Point({self.x}, {self.y})"

    def delta_x(self, dx):
        """Returns a new Point with x moved by dx."""
        return Point(self.x + dx, self.y)

    def delta_y(self, dy):
        """Returns a new Point with y moved by dy."""
        return Point(self.x, self.y + dy)

    def translate(self, dx, dy):
        """Returns a new Point translated by dx and dy."""
        return Point(self.x + dx, self.y + dy)

class Circle:
    def __init__(self, center, radius):
        self.center = center
        self.radius = radius

    def __repr__(self):
        return f"Circle({repr(self.center)}, {self.radius})"

    def translate(self, dx, dy):
        """Returns a new Circle instance with translated center."""
        new_center = self.center.translate(dx, dy)
        return Circle(new_center, self.radius)

    def perimeter(self):
        """Returns the perimeter of the circle."""
        return 2 * math.pi * self.radius

    def area(self):
        """Returns the area of the circle."""
        return math.pi * (self.radius ** 2)

class Rectangle:
    def __init__(self, upper_left, lower_right):
        self.upper_left = upper_left
        self.lower_right = lower_right

    def __repr__(self):
        return f"Rectangle({repr(self.upper_left)}, {repr(self.lower_right)})"

    def area(self):
        """Returns the area of the rectangle."""
        width = abs(self.lower_right.x - self.upper_left.x)
        height = abs(self.lower_right.y - self.upper_left.y)
        return width * height

    def perimeter(self):
        """Returns the perimeter of the rectangle."""
        width = abs(self.lower_right.x - self.upper_left.x)
        height = abs(self.lower_right.y - self.upper_left.y)
        return 2 * (width + height)

    def translate(self, dx, dy):
        """Returns a new Rectangle instance with translated points."""
        new_ul = self.upper_left.translate(dx, dy)
        new_lr = self.lower_right.translate(dx, dy)
        return Rectangle(new_ul, new_lr)

if __name__ == "__main__":
    doctest.testfile("test_geometry.txt", verbose=True)
