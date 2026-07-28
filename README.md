# ConsoleMusicPlayer
Console Music Player (C) Developed an interactive command-line music player in C that scans directories for audio files, maintains a custom doubly linked list playlist, and integrates with the Windows API for audio playback. Implemented playlist navigation, command parsing, and dynamic memory management.


## Windows Setup

### Requirements

Before running the program, make sure you have:

* Windows 10 or Windows 11
* A C compiler (such as GCC through MinGW-w64)
* The Windows Multimedia library (`winmm.lib`), which is included with Windows
* WAV audio files to test playback
* To use as a command, edit your environment variables by adding the directory of the built exe file to the PATH variables

### Building the Project

Compile the source file with GCC:

```bash
gcc main.c -o MusicPlayer -lwinmm
```

If your project is split into multiple source files, compile them together:

```bash
gcc *.c -o MusicPlayer -lwinmm
```

### Running the Program

Open Command Prompt or PowerShell and navigate to the project directory.

To scan the current folder for WAV files:

```bash
MusicPlayer.exe
```

To scan a specific directory:

```bash
MusicPlayer.exe "C:\Users\YourName\Music"
```

The program will automatically search the specified directory for `.wav` files and load them into the playlist.

### Controls

Once the program starts, type one of the following commands:

| Command | Description                        |
| ------- | ---------------------------------- |
| `next`  | Play the next song in the playlist |
| `prev`  | Return to the previous song        |
| `quit`  | Exit the program                   |

Typing any other command will replay the current song.

### Notes

* Only `.wav` audio files are currently supported.
* Songs are loaded from the selected directory when the program starts.
* Playback is handled using the Windows Multimedia API (`PlaySound`).
* If no supported audio files are found, the program will exit with a message indicating that the directory contains no playable songs.

## Future Improvements

Potential features planned for future versions include:

* Shuffle and repeat modes
* Song search by title
* Playlist saving/loading
* Volume controls
* Pause and resume playback
* Metadata support (artist, album, duration)
* Support for additional audio formats such as MP3 or FLAC
* Improved command-line interface with help menus and better error handling
