## This is from [urraka/alpha-bleeding](https://github.com/urraka/alpha-bleeding).

- The purpose of this fork is to simply nothing more, nothing less than to provide compiled binaries for Windows (as most likely the program was written with Linux/macOS in mind).

- The binaries work with both 32bit and 64bit versions of Windows - I tested this for a Windows 7 Pro 32bit VM and a Windows 10 Education 64bit installation.

- The goal is for users to quickly access this tool without having to fiddle with compiling it (and, more importantly, having to compile the libraries it depends on - `libpng`, which on it's hand depends on `zlib`).

## The tool:

This is a small command-line tool to bleed the border colors of an image with transparency through the pixels that
are fully transparent. It's intended to avoid filtering issues in OpenGL applications.

### Installation:

Just download from the Releases page and use. It's that simple!

If you have got [scoop](https://scoop.sh), you can also install this tool to your PATH:

`scoop bucket add rbxdev 'https://github.com/ddavness/scoop-RobloxDev.git'`

`scoop install alpha-utils`

### Usage:

`alpha-bleeding <input> <output>`

`alpha-remove <input> <output>`

`alpha-set <alpha> <input> <output>`

- Both `<input>` and `<output>` **must be PNG image files.**
- `<alpha>` is an 8-bit unsigned integer (from `0` to `255`)

### 😱😱 HELP! THE PROGRAM DOESN'T RUN! 😱😱

- Likely you're missing the Visual C++ Redistributable runtimes. Get them [here](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads), and choose the runtime for your architecture - x86 for 32bit, x64 for 64bit.
- The latest version is always recommended (at this moment, from VS 2019), however any runtime package from VS 2015 or more recent will work.

### Building (You'll need Visual Studio with C++ tools):

> I personally do not recommend this approach unless for some reason the program refuses to work and the steps mentioned above do not work. The libraries were built statically (as `.lib` files) instead of dynamic libraries (as `.dll` files)

1. Grab `libpng` and `zlib` source code, unpack and place both in the same directory;

2. Copy the `vstudio` folder to `<libpng-folder>\projects\vstudio`. Overwrite.

3. Open the `.sln` file. Build!

- **Note #1:** You may encounter some errors. Those are related to programs bundled to test the library; *I, davness, was too lazy to fix them - if you can actually fix those, please file an issue or PR regarding that.*

- **Note #2:** For this particular compilation the library versions were `1.6.37` and `1.2.11`, respectively for `libpng` and `zlib`.

## Example

Using this tool you can clearly see the effect of the alpha bleeding:

| Original image | After Bleeding | Alpha Removed | Bleeding + Remove | Alpha = 128 (0 - 255) |
|----------------|----------------|---------------|--------------------------|------------------|
| ![original](media/original.png) | ![alpha-bleeding](media/alpha-bleed.png) | ![original-opaque](media/alpha-remove.png) | ![alpha-bleeding-opaque](media/alpha-bleed-remove.png) | ![alpha-bleeding-opaque](media/alpha-set.png) |
