#!/usr/bin/env python
"""Assignment 4 Part 1 Version 3 template"""
print(__doc__)

from typing import IO

class HtmlComponent:
    """HtmlComponent superclass"""
    def __init__(self, indent: int = 0) -> None:
        self.indent = indent

    def tab(self) -> str:
        return "   " * self.indent


class CircleShape(HtmlComponent):
    """CircleShape class"""
    def __init__(self, cx: int, cy: int, r: int, color: tuple[int, int, int], opacity: float, indent: int = 0) -> None:
        super().__init__(indent)
        self.cx = cx
        self.cy = cy
        self.r = r
        self.red, self.green, self.blue = color
        self.opacity = opacity

    def as_svg(self) -> str:
        return (f'{self.tab()}<circle cx="{self.cx}" cy="{self.cy}" r="{self.r}" '
                f'fill="rgb({self.red}, {self.green}, {self.blue})" fill-opacity="{self.opacity}"></circle>')


class SvgCanvas(HtmlComponent):
    """SvgCanvas class"""
    def __init__(self, width: int, height: int, indent: int = 0) -> None:
        super().__init__(indent)
        self.width = width
        self.height = height
        self.shapes: list[CircleShape] = []

    def add_shape(self, shape: CircleShape) -> None:
        self.shapes.append(shape)

    def gen_art(self) -> None:
        # Top red row
        for x in range(50, 501, 100):
            self.add_shape(CircleShape(x, 50, 50, (255, 0, 0), 1.0, self.indent + 1))
        # Bottom blue row
        for x in range(50, 501, 100):
            self.add_shape(CircleShape(x, 250, 50, (0, 0, 255), 1.0, self.indent + 1))

    def render(self) -> list[str]:
        lines = [f'{self.tab()}<!--Define SVG drawing box-->']
        lines.append(f'{self.tab()}<svg width="{self.width}" height="{self.height}">')
        lines += [shape.as_svg() for shape in self.shapes]
        lines.append(f'{self.tab()}</svg>')
        return lines


class HtmlDocument(HtmlComponent):
    """HtmlDocument class"""
    def __init__(self, title: str, indent: int = 0) -> None:
        super().__init__(indent)
        self.title = title
        self.canvas = SvgCanvas(500, 300, self.indent + 1)

    def build(self) -> list[str]:
        lines = ["<html>", "<head>", f"   <title>{self.title}</title>", "</head>", "<body>"]
        self.canvas.gen_art()
        lines += self.canvas.render()
        lines.append("</body>")
        lines.append("</html>")
        return lines

    def save(self, filename: str) -> None:
        with open(filename, "w") as f:
            for line in self.build():
                f.write(line + "\n")


def main() -> None:
    """main function"""
    doc = HtmlDocument("My Art")
    doc.save("a41.html")


if __name__ == "__main__":
    main()
