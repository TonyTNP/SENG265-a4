# Assignment 4 – SVG Art Generator 

This project was completed for **SENG 265 – Software Development Methods** at the University of Victoria (Spring 2025).  
It demonstrates clean Python design, object-oriented programming, file output, and SVG/HTML generation.

## Project Overview

This assignment is split into 3 parts, each building on the last to progressively generate static and randomized visual art using HTML and SVG.


---

## Part 1: Static HTML-SVG Art (`a41/`)

- Generates `a41.html`
- Contains two rows of colored circles:
  - Top row: red
  - Bottom row: blue
- Created using object-oriented Python and basic SVG rendering

Run:
```bash
python3 a41.py

----------------------------------------------------------------------------------------

## Part 2: Random Shape Data Table (`a42/`)

This script generates a table of 10 randomly generated shapes and prints it to the terminal in a formatted, right-aligned layout.

Each shape includes:
- Shape type (currently always `circle`)
- Center position (`cx`, `cy`)
- Radius
- Width & height (for future extensibility)
- RGB color values
- Opacity (float between 0.1 and 1.0)

📄 A screenshot of the output table is saved as `a42.jpg` (as required by the assignment).

---

### How to Run

```bash
python3 a42.py

-----------------------------------------------------------------------------------------------------

## Part 3: Randomized HTML-SVG Art Generator (`a43/`)

This final part combines the structure from Part 1 with the randomness from Part 2 to generate 3 unique HTML art pages using SVG and custom style configurations.

Each page contains:
- A 500 × 300 SVG canvas
- 10 randomly generated `circle` shapes
- Unique positioning, color, size, and opacity per style

Three visual styles are generated and saved as:
- `a431.html` – muted colors, medium size, mostly opaque
- `a432.html` – bright colors, small size, more transparent
- `a433.html` – mixed colors, large size, medium opacity

---

### How to Run

```bash
python3 a43.py

To open in browser, use the following OS specific commands:
    start a43/a431.html   # Windows
    xdg-open a43/a431.html  # Linux
    open a43/a431.html     # macOS

