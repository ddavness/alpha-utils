## The purpose of this fork:

- The purpose of this fork is to simply nothing more, nothing less than to provide compiled binaries for Windows.

- The goal is for users to quickly access this tool without having to fiddle with compiling it (and, more importantly, having to compile the libraries it depends on - `libpng`, which on it's hand depends on `zlib`).

## The tool:

This is a small tool to bleed the border colors of an image with transparency through the pixels that
are fully transparent. It's intended to avoid filtering issues in OpenGL applications.

**Usage:**

`alpha-bleeding <input> <output>`

Both `<input>` and `<output>` should be PNG image files.

**Building:**

Just type `make` on the root directory. `libpng` and `libz` are the only required dependencies.

**Example:**

It's hard to see the effect of this tool, given that it only modifies the transparent pixels, so I
added another tool which just changes the alpha channel of every pixel to fully opaque. It can be
used the same way:

`alpha-remove <input> <output>`

Using that helper tool you can clearly see the effect of the alpha bleeding:

Original image:

![original](media/original.png)

Image after `alpha-bleeding` (not much to see):

![alpha-bleeding](media/alpha-bleeding.png)

Original image after `alpha-remove`:

![original-opaque](media/original-opaque.png)

Image after `alpha-bleeding`, then `alpha-remove`:

![alpha-bleeding-opaque](media/alpha-bleeding-opaque.png)
