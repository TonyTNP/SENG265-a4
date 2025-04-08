#!/usr/bin/env python3
"""Assignment 4 Part 3: Randomized HTML-SVG Art Generator

This program generates three randomized SVG art files using HTML and SVG.
It leverages object-oriented design, using configurable parameters for radius,
color, opacity, and shape position.
"""

import random
from typing import NamedTuple, IO


class HtmlComponent:
    """
    Base class for HTML elements with indentation control for pretty-printing.
    
    Attributes:
        indent (int): Number of indentation levels (each level = 3 spaces).
    """
    def __init__(self, indent: int = 0) -> None:
        self.indent = indent

    def tab(self) -> str:
        """Returns the current indentation as spaces."""
        return "   " * self.indent


class PyArtConfig:
    """
    Configuration class for controlling shape attribute ranges.

    Attributes:
        radius_range: Tuple[int, int] for random radius generation.
        width_range: Tuple[int, int] (unused for circle, future use).
        height_range: Tuple[int, int] (unused for circle, future use).
        color_range: Tuple[int, int] for RGB values.
        opacity_range: Tuple[float, float] for transparency.
    """
    def __init__(self,
                 radius_range=(10, 100),
                 width_range=(10, 100),
                 height_range=(10, 100),
                 color_range=(0, 255),
                 opacity_range=(0.1, 1.0)) -> None:
        self.radius_range = radius_range
        self.width_range = width_range
        self.height_range = height_range
        self.color_range = color_range
        self.opacity_range = opacity_range


class RandomShape(NamedTuple):
    """
    Represents a randomly generated SVG circle with visual attributes.

    Attributes:
        shape_type: Name of shape ("circle" only in Part 3).
        cx, cy: Circle center position on the canvas.
        radius: Radius of the circle.
        width, height: For future extensibility (unused for circle).
        red, green, blue: RGB values for fill color.
        opacity: Float between 0.1–1.0 indicating fill transparency.
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

    def as_svg(self, indent: int = 0) -> str:
        """
        Returns a properly formatted SVG <circle> tag string.

        Args:
            indent (int): Indentation level for pretty-printing.

        Returns:
            str: SVG markup for the circle.
        """
        ts = "   " * indent
        return (f'{ts}<circle cx="{self.cx}" cy="{self.cy}" r="{self.radius}" '
                f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.opacity}"></circle>')


class SvgCanvas(HtmlComponent):
    """
    Represents an SVG drawing canvas.

    Attributes:
        width, height: Dimensions of the canvas.
        shapes: List of RandomShape objects to render.
    """
    def __init__(self, width: int, height: int, indent: int = 0):
        super().__init__(indent)
        self.width = width
        self.height = height
        self.shapes: list[RandomShape] = []

    def add_shape(self, shape: RandomShape) -> None:
        """Adds a shape to the canvas."""
        self.shapes.append(shape)

    def generate_shapes(self, count: int, config: PyArtConfig) -> None:
        """
        Generates and adds `count` shapes using the given config.
        """
        for _ in range(count):
            shape = RandomShape(
                shape_type="circle",
                cx=random.randint(0, self.width),
                cy=random.randint(0, self.height),
                radius=random.randint(*config.radius_range),
                width=random.randint(*config.width_range),
                height=random.randint(*config.height_range),
                red=random.randint(*config.color_range),
                green=random.randint(*config.color_range),
                blue=random.randint(*config.color_range),
                opacity=round(random.uniform(*config.opacity_range), 2)
            )
            self.add_shape(shape)

    def render(self) -> list[str]:
        """
        Returns the SVG canvas content as a list of HTML lines.
        """
        lines = [f'{self.tab()}<!--Define SVG drawing box-->']
        lines.append(f'{self.tab()}<svg width="{self.width}" height="{self.height}">')
        lines += [shape.as_svg(self.indent + 1) for shape in self.shapes]
        lines.append(f'{self.tab()}</svg>')
        return lines


class HtmlDocument(HtmlComponent):
    """
    Represents a full HTML document containing an SVG canvas.

    Attributes:
        title: The page title.
        canvas: An instance of SvgCanvas to be embedded in <body>.
    """
    def __init__(self, title: str, canvas: SvgCanvas, indent: int = 0):
        super().__init__(indent)
        self.title = title
        self.canvas = canvas

    def build(self) -> list[str]:
        """
        Constructs the full HTML content as a list of lines.
        """
        lines = ["<html>", "<head>", f"   <title>{self.title}</title>", "</head>", "<body>"]
        lines += self.canvas.render()
        lines.append("</body>")
        lines.append("</html>")
        return lines

    def save(self, filename: str) -> None:
        """
        Saves the HTML content to a file.

        Args:
            filename: Name of the HTML file to save to.
        """
        with open(filename, "w") as f:
            for line in self.build():
                f.write(line + "\n")


def generate_art_page(filename: str, config: PyArtConfig, title: str = "Random Art") -> None:
    """
    Generates and saves an HTML page with random SVG shapes.

    Args:
        filename: Output HTML filename.
        config: Configuration object to control shape generation.
        title: Page title.
    """
    canvas = SvgCanvas(500, 300, indent=1)
    canvas.generate_shapes(10, config)
    doc = HtmlDocument(title, canvas)
    doc.save(filename)


def main() -> None:
    """
    Main function to generate 3 randomized art pages with different styles.
    """
    config1 = PyArtConfig(radius_range=(20, 60), color_range=(0, 128), opacity_range=(0.5, 1.0))
    config2 = PyArtConfig(radius_range=(10, 30), color_range=(128, 255), opacity_range=(0.2, 0.7))
    config3 = PyArtConfig(radius_range=(40, 100), color_range=(0, 255), opacity_range=(0.3, 0.9))

    generate_art_page("a431.html", config1, "Random Art Style 1")
    generate_art_page("a432.html", config2, "Random Art Style 2")
    generate_art_page("a433.html", config3, "Random Art Style 3")


if __name__ == "__main__":
    main()
