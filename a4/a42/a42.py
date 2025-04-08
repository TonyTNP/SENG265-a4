#!/usr/bin/env python3
"""Assignment 4 Part 2: Random shape data table

This program generates a table of 10 random geometric shapes (circles) using configurable ranges
for position, size, color, and opacity. Output is aligned in columns to match the assignment spec.
"""

import random
from typing import NamedTuple


class PyArtConfig:
    """
    Stores configuration ranges for generating random shapes.
    
    Attributes:
        radius_range: Tuple[int, int] - Min and max radius values.
        width_range: Tuple[int, int] - Width range for use in Part 3.
        height_range: Tuple[int, int] - Height range for use in Part 3.
        color_range: Tuple[int, int] - Min and max values for RGB color components.
        opacity_range: Tuple[float, float] - Min and max values for shape opacity.
    """
    def __init__(self,
                 radius_range=(10, 100),
                 width_range=(10, 100),
                 height_range=(10, 100),
                 color_range=(0, 255),
                 opacity_range=(0.1, 1.0)):
        self.radius_range = radius_range
        self.width_range = width_range
        self.height_range = height_range
        self.color_range = color_range
        self.opacity_range = opacity_range


class RandomShape(NamedTuple):
    """
    Represents a single randomly generated shape with visual attributes.

    Attributes:
        shape_type: The name of the shape (e.g., 'circle').
        cx, cy: The x and y coordinates of the shape's center.
        radius: Radius of the shape (used for circles).
        width, height: Shape dimensions (for future extensibility).
        red, green, blue: RGB color values.
        opacity: Float between 0 and 1.0 representing transparency.
    """

    shape_type: str
    cx: int
    cy: int
    radius: int
    width: int
    height: int
    red: int
    green: int
    blue: int
    opacity: float

    def __str__(self) -> str:
        """Returns a detailed multiline string describing the shape."""
        return (f"Shape: {self.shape_type}\n"
                f"  Center: ({self.cx}, {self.cy})\n"
                f"  Radius: {self.radius}, Width: {self.width}, Height: {self.height}\n"
                f"  Color: RGB({self.red}, {self.green}, {self.blue}), Opacity: {self.opacity}")

    def as_Part2_line(self) -> str:
        """
        Returns a formatted one-line string used in Part 2 table output.
        Fields are right-aligned to match assignment formatting.
        """
        return (f"{self.shape_type:>6} {self.cx:>4} {self.cy:>4} {self.radius:>4} "
                f"{self.width:>4} {self.height:>4}  {self.red:>3} {self.green:>3} {self.blue:>3}  {self.opacity:>4.2f}")


def generate_random_shape(config: PyArtConfig) -> RandomShape:
    """
    Generates a single random shape using the given configuration.

    Args:
        config: An instance of PyArtConfig with all value ranges.

    Returns:
        A populated RandomShape instance with randomized values.
    """
    return RandomShape(
        shape_type="circle",
        cx=random.randint(0, 500),
        cy=random.randint(0, 300),
        radius=random.randint(*config.radius_range),
        width=random.randint(*config.width_range),
        height=random.randint(*config.height_range),
        red=random.randint(*config.color_range),
        green=random.randint(*config.color_range),
        blue=random.randint(*config.color_range),
        opacity=round(random.uniform(*config.opacity_range), 2)
    )


def main() -> None:
    """
    Main entry point. Generates and prints a formatted table of 10 random shapes.
    """
    print("Shape   cx   cy  rad  wid  hgt   red green blue  opac")
    config = PyArtConfig()
    for _ in range(10):
        shape = generate_random_shape(config)
        print(shape.as_Part2_line())


if __name__ == "__main__":
    main()
