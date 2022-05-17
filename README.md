# DPEdit 1.1.0
DPEdit is a simple command line utility to accurately set the relative position of displays in a dual- or multi-monitor setup.

## Usage

Basic command syntax is as follows:
```
dpedit.exe <displayNum> <xPos> <yPos> [<displayNum2> <xPos2> <yPos2>] ...
```
`<displayNum>` is the index of the display to position (can be listed using `dpedit.exe /L`)

`<xPos>` is the X, or horizontal, position, in pixels, of the top-left corner of display `<displayNum>`.

`<yPos>` is the Y, or vertical, position, in pixels, of the top-left corner of display `<displayNum>`.

NOTE: Display #1 remains at position {0, 0} at all times. Specifying its location at all is entirely optional.
If its location is set (E.G. on a single-monitor system), the wallpaper will be offset accordingly. However, it will still be at position {0, 0}.

## Examples

> Command Line:
> ```
> dpedit.exe 1 0 0 2 -1920 21
> ```
> Powershell (Windows Terminal):
> ```
> ./dpedit.exe 1 0 0 2 -1920 21
> ```

Moves Display #1 to coords {0, 0} and positions Display #2 to the left of
and 21 pixels lower than Display #1 (coords {-1920, 21}).
This example assumes Display #2 to be 1080p.


Results in the following monitor configuration:

![Example 1](https://user-images.githubusercontent.com/43104632/122635504-585a4880-d0b2-11eb-8242-18adf913d570.jpg)

---
> Command Line:
> ```
> dpedit.exe 2 0 1080
> ```
> Powershell (Windows Terminal):
> ```
> ./dpedit.exe 2 0 1080
> ```

Assuming Display #1 is at coords {0, 0}, positions Display #2 below Display #1 (coords {0, 1080}).
This example assumes Display #1 to be 1080p.


Results in the following monitor configuration:

![Example 2](https://user-images.githubusercontent.com/43104632/122635610-ecc4ab00-d0b2-11eb-9b39-dbfc91be58bc.jpg)

## Disclaimer
THIS UTILITY CAUSES CHANGES TO THE REGISTRY.
THE AUTHOR OF THIS UTILITY IS NOT RESPONSIBLE FOR ANY DAMAGE THAT THIS UTILITY MAY CAUSE TO YOUR DEVICE.
USE AT YOUR OWN RISK.
