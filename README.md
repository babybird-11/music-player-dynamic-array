# Music Player with a Custom Dynamic Array

A coursework-based command-line music player built with C++ and SplashKit.
The project extends an earlier music player by using a custom generic
dynamic array to store song records and search results.

## Features

- Add songs with a name and local audio file path
- Generate a unique ID for each song
- Search for songs by matching text in their names
- Play, pause, and resume music
- Rename songs and toggle their loved status
- Reset play counts and delete songs
- Display totals for stored songs, songs played, and loved songs

## Technical Highlights

The `dynamic_array<T>` implementation includes:

- An initial capacity of 10 elements
- Capacity doubling when the array becomes full
- Indexed access with bounds checks
- Element removal by shifting later elements
- Memory cleanup through a destructor
- Disabled copying and copy assignment to prevent shallow copies

The player uses `dynamic_array<song_data>` for song records and
`dynamic_array<int>` for matching search indices.

## Tech Stack

- C++
- SplashKit
- Custom template-based dynamic array

## Project Structure

```text
.
├── music_player.cpp    # Menus, song management, search, and playback
├── dynamic_array.hpp   # Generic dynamic array implementation
├── utilities.cpp       # Console input helpers
├── utilities.h         # Input helper declarations
├── .gitignore
└── README.md
```

## Build and Run

Requirements:

- A C++ compiler
- SplashKit and SplashKit Manager (`skm`)
- A local environment with audio output for playback

From the repository root:

```bash
mkdir -p build
skm clang++ music_player.cpp utilities.cpp -o build/music-player
./build/music-player
```

These build instructions have not yet been independently verified
for this repository.

## Usage

1. Select `1. Add a new song`.
2. Enter a song name and a valid local audio file path.
3. Choose whether to mark the song as loved.
4. Select `3. Play a song`, search by name, and select a match.
5. Use the other menu options to update songs, control playback,
   or view player statistics.
6. Select `6. Quit` to exit.

Audio files are not included. Use your own audio or appropriately
licensed sample files.

For an audible demonstration, run the application locally.
A browser-based Codespaces terminal alone does not provide local
speaker playback.

## Validation Status

Source code has been reviewed for project documentation.
Compilation, playback, and automated tests have not yet been verified.

Suggested manual checks:

- Add and search for a song
- Add more than 10 songs to exercise array growth
- Rename a song and toggle its loved status
- Play, pause, and resume a valid audio file
- Reset a play count
- Delete a song and check the remaining records
- Search for a song that does not exist

## Current Limitations

- Song records are stored in memory and are not saved after exit.
- There is no graphical interface.
- Audio loading errors need more robust handling.
- The play count increases before successful playback is confirmed.
- Pause and resume handling needs validation when no track is loaded.
- The dynamic array does not support copying.

## Project Background and Acknowledgements

Developed for FIT1045 D2 (Dynamic Array), extending the P8 music player.

This is a coursework-based learning project, not a production application.
Course guidance and SplashKit supported its development.

As recorded in the coursework portfolio, ChatGPT was used to explain
dynamic memory concepts and assist with adapting the earlier player
to use a custom dynamic array.
