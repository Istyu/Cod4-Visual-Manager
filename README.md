# Cod4-Visual-Manager
This manager can be change game visual options.

![](https://github.com/Istyu/Cod4-Visual-Manager/blob/main/iw3_visual.gif)

This project is a C++ DLL created for Call of Duty 4. The DLL can be injected into the game's process and is capable of controlling various visual settings such as FOV adjustment, film effects toggling, as well as FPS limit and counter control.

## Features

Users can control the following settings by pressing different keys:

- **FOV (Field of View) Scale**: Four available values (1.0, 1.135, 1.35, 1.45)
- **Filmtweak**: Can be toggled on or off
- **Fullbright Mode**: Can be toggled on or off
- **FPS Limit**: Three available values (125, 250, 333)
- **FPS Counter**: Can be shown or hidden in-game


## Usage

- Just inject the [iw3_visualmanager.dll](https://github.com/Istyu/Cod4-Visual-Manager/releases/download/IW3Visual/iw3_visualmanager.dll) to iw3mp.exe process.
- Now you can change the visual settings.

### Key Bindings

The features are controlled using the following NUMPAD keys:

- **NUMPAD0**: Adjust FOV Scale. Available values: `1.0`, `1.135`, `1.35`, `1.45`
- **NUMPAD1**: Toggle Filmtweak on/off
- **NUMPAD2**: Toggle Fullbright mode on/off
- **NUMPAD3**: Cycle FPS Limit between the values `125`, `250`, `333`
- **NUMPAD4**: Show or hide the FPS counter

## Supported Cod4 client versions
- cod4 1.7
- cod4x
