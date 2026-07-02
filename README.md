# Fractol

A real-time fractal explorer written in C, rendering the Mandelbrot, Julia and Burning Ship sets with interactive zoom, panning and coloring using the MiniLibX graphics library.

![C](https://img.shields.io/badge/C-00599C?logo=c&logoColor=white)
![MiniLibX](https://img.shields.io/badge/MiniLibX-X11-1f6feb)
![42 Barcelona](https://img.shields.io/badge/42-Barcelona-000000?logo=42&logoColor=white)

## About

`fractol` is a 42 Common Core graphics project that visualizes escape-time fractals by mapping each pixel to a point in the complex plane and iterating a recurrence until it escapes a bounded region. It demonstrates complex-number arithmetic, coordinate scaling, direct pixel-buffer manipulation and event-driven programming with the MiniLibX (X11) library. The image is redrawn on every user interaction, giving smooth exploration of the fractal boundary.

## Features

- Three fractal types: **Mandelbrot**, **Julia** (with custom seed parameters) and **Burning Ship**.
- Interactive **mouse-wheel zoom** centered on the current view.
- **Arrow-key panning** across the complex plane.
- Adjustable **iteration depth** with `+` / `-` to trade detail against speed.
- Live **Julia seed tracking** from mouse movement for animated exploration.
- Rendering to an off-screen image buffer via `mlx_get_data_addr` for fast per-pixel drawing.
- Clean resource teardown and exit on `ESC` or window close.

## Build & run

Built with `make`, which compiles the sources and links against the bundled MiniLibX and X11 (`-lX11 -lXext -lm`).

```bash
# Build the executable (NAME = fractol)
make

# Rebuild from scratch
make re

# Run
./fractol mandelbrot
./fractol julia -0.8 0.156
./fractol burning_ship
```

Controls: arrow keys to move, mouse wheel to zoom, `+` / `-` to change iteration detail, `ESC` to quit.

Requires a Linux environment with the X11 development libraries (`libx11-dev`, `libxext-dev`) available.

## Concepts

- C (C99), memory management and manual resource cleanup
- MiniLibX / X11 graphics and event hooks (keyboard, mouse, close)
- Complex-number math and escape-time algorithms
- Coordinate mapping and image buffer rendering
- Makefile build system

_42 Barcelona · Common Core project._
