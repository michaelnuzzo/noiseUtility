<div  align="center">

# Reverser

</div>

## Overview

noiseUtility is a simple audio plugin that adds series noise into the signal path. It can be useful for testing other plugins in a DAW environment. 

<div  align="center">

</div>



## Install

The plugin itself can be downloaded from the [Releases page](https://github.com/michaelnuzzo/noiseUtility/releases) in this repository. Once downloaded, the plugin can be installed by simply dragging the file into your plugins folder. 

```
VST3:
Macintosh HD/Library/Audio/Plug-Ins/VST3
AU (Component):
Macintosh HD/Library/Audio/Plug-Ins/Components
```
The .app can be run as a standalone without a DAW or further installation.

## Build

At present, the available binaries are AU, VST, and a macOS app. If you would like to generate your own binary for another file format or platform, you can compile your own plugin.

First, install [JUCE](https://juce.com/get-juce/download).

Then clone this repository to your local machine.

```
git clone https://github.com/michaelnuzzo/CompressOScope.git
```

Import into your JUCE project, then tweak your build settings as needed.
