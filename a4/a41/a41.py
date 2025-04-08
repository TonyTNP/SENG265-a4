#!/usr/bin/env python3
"""Assignment 4 Part 1: Static HTML-SVG Art Generator

This script creates a simple HTML document that displays SVG art.
Two rows of colored circles (red and blue) are rendered in a 500×300 canvas.
"""

from typing import IO


class HtmlComponent:
    """
    Base class for HTML/SVG components with indentation support.

    Attributes:
        indent (int): Indentation level (each level = 3 spaces).
    """
    def __init__(self, indent: int = 0) -> None:
        self.indent = indent

    def tab(self) -> str:
        """Returns indentation as a string of spaces."""
        return "   " * self.indent


class CircleShape(HtmlComponent):
    """
    Represents an SVG <circle> shape.

    Attributes:
        cx, cy (int): Center coordinates of the circle.
        r (int): Radius of the circle.
        color (tuple[int, int, int]): RGB color.
        opacity (float): Fill opacity (0.0–1.0).
    """
    def __init__(self, cx: int, cy: int, r: int, color: tuple[int, int, int], opacity: float, indent: int = 0) -> None:
        super().__init__(indent)
        self.cx = cx
        self.cy = cy
        self.r = r
        self.red, self.green, self.blue = color
        self.opacity = opacity

    def as_svg(self) -> str:
        """
        Returns the SVG markup string for the circle.
        """
        return (f'{self.tab()}<circle cx="{self.cx}" cy="{self.cy}" r="{self.r}" '
                f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.opacity}"></circle>')


class SvgCanvas(HtmlComponent):
    """
    Represents an SVG canvas containing shapes.

    Attributes:
        width, height (int): Canvas dimensions.
        shapes (list[CircleShape]): List of CircleShape objects.
    """
    def __init__(self, width: int, height: int, indent: int = 0) -> None:
        super().__init__(indent)
        self.width = width
        self.height = height
        self.shapes: list[CircleShape] = []

    def add_shape(self, shape: CircleShape) -> None:
        """Adds a shape to the canvas."""
        self.shapes.append(shape)

    def gen_art(self) -> None:
        """
        Generates a simple design: red circles on the top row and blue circles on the bottom row.
        """
        # Top red row
        for x in range(50, 501, 100):
            self.add_shape(CircleShape(x, 50, 50, (255, 0, 0), 1.0, self.indent + 1))

        # Bottom blue row
        for x in range(50, 501, 100):
            self.add_shape(CircleShape(x, 250, 50, (0, 0, 255), 1.0, self.indent + 1))

    def render(self) -> list[str]:
        """
        Returns a list of SVG lines for the canvas and its shapes.
        """
        lines = [f'{self.tab()}<!--Define SVG drawing box-->']
        lines.append(f'{self.tab()}<svg width="{self.width}" height="{self.height}">')
        lines += [shape.as_svg() for shape in self.shapes]
        lines.append(f'{self.tab()}</svg>')
        return lines


class HtmlDocument(HtmlComponent):
    """
    Represents an HTML document embedding the SVG canvas.

    Attributes:
        title (str): The title of the document.
        canvas (SvgCanvas): The embedded canvas.
    """
    def __init__(self, title: str, indent: int = 0) -> None:
        super().__init__(indent)
        self.title = title
        self.canvas = SvgCanvas(500, 300, self.indent + 1)

    def build(self) -> list[str]:
        """
        Assembles and returns the HTML content as a list of lines.
        """
        lines = ["<html>", "<head>", f"   <title>{self.title}</title>", "</head>", "<body>"]
        self.canvas.gen_art()
        lines += self.canvas.render()
        lines.append("</body>")
        lines.append("</html>")
        return lines

    def save(self, filename: str) -> None:
        """
        Saves the HTML document to a file.

        Args:
            filename (str): Output file path.
        """
        with open(filename, "w") as f:
            for line in self.build():
                f.write(line + "\n")


def main() -> None:
    """
    Main function: generates and saves the static HTML art file.
    """
    doc = HtmlDocument("My Art")
    doc.save("a41.html")


if __name__ == "__main__":
    main()
