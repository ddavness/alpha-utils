## The purpose of this fork:

- The purpose of this fork is to simply nothing more, nothing less than to provide compiled binaries for Windows (as most likely the program was written with Linux/macOS in mind).

- The goal is for users to quickly access this tool without having to fiddle with compiling it (and, more importantly, having to compile the libraries it depends on - `libpng`, which on it's hand depends on `zlib`).

## The tool:

This is a small command-line tool to bleed the border colors of an image with transparency through the pixels that
are fully transparent. It's intended to avoid filtering issues in OpenGL applications.

### Installation:

Just download and use. It's that simple!

### Usage:

`alpha-bleeding <input> <output>`

`alpha-remove <input> <output>`

`alpha-set <alpha> <input> <output>`

- Both `<input>` and `<output>` **must be PNG image files.**
- `<alpha>` is an 8-bit unsigned integer (from `0` to `255`)

### Building (You'll need Visual Studio with C++ tools):

> I personally do not recommend this approach unless for some reason the program refuses to work. The libraries were built statically (as `.liB` files) instead of dynamic libraries (as `.dll` files)

1. Grab `libpng` and `zlib` source code, unpack and place both in the same directory;

2. Copy the `vstudio` folder to `<libpng-folder>\projects\vstudio`. Overwrite.

3. Open the `.sln` file. Build!

**Note:** You may encounter some errors. Those are related to programs bundled to test the library; *I, davness, was too lazy to fix them - if you can actually fix, file an issue or PR regarding that.*

## Example

Using this tool you can clearly see the effect of the alpha bleeding:

| Original image | After Bleeding | Alpha Removed | Bleeding + Remove | Alpha = 128 (0 - 255) |
|----------------|----------------|---------------|--------------------------|------------------|
| ![original](media/original.png) | ![alpha-bleeding](media/alpha-bleed.png) | ![original-opaque](media/alpha-remove.png) | ![alpha-bleeding-opaque](media/alpha-bleed-remove.png) | ![alpha-bleeding-opaque](media/alpha-set.png) |
