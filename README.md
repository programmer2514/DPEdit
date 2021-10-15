# DPEdit 1.0.0
DPEdit is a simple command line utility to accurately set the relative position of monitors in a dual- or multi-monitor setup.

## Usage

Basic command syntax is as follows:
```
dpedit.exe <monitorNum> <xPos> <yPos> [<monitorNum2> <xPos2> <yPos2>] ...
```
`<monitorNum>` is the index of the monitor to position, where 1 = Main, 2 = Secondary, etc.

`<xPos>` is the X, or horizontal, position, in pixels, of the top-left corner of monitor `<monitorNum>`.

`<yPos>` is the Y, or vertical, position, in pixels, of the top-left corner of monitor `<monitorNum>`.

NOTE: The main monitor (monitor 1) remains at position {0, 0} at all times. Specifying its location at all is entirely optional.
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

Moves the main monitor to coords {0, 0} and positions the secondary monitor to the left of
and 21 pixels lower than the main monitor (coords {-1920, 21}).
This example assumes the secondary monitor to be 1080p.


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

Assuming the main monitor is at coords {0, 0}, positions the secondary monitor below the main monitor (coords {0, 1080}).
This example assumes the secondary monitor to be 1080p.


Results in the following monitor configuration:

![Example 2](https://user-images.githubusercontent.com/43104632/122635610-ecc4ab00-d0b2-11eb-9b39-dbfc91be58bc.jpg)

## Disclaimer
THIS UTILITY CAUSES CHANGES TO THE REGISTRY.
THE AUTHOR OF THIS UTILITY IS NOT RESPONSIBLE FOR ANY DAMAGE THAT THIS UTILITY MAY CAUSE TO YOUR DEVICE.
USE AT YOUR OWN RISK.
