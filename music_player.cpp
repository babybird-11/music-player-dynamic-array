#include "splashkit.h"
#include "dynamic_array.hpp"
#include "utilities.h"
#include <string>

//Main menu option
enum menu_option
{
    ADD_SONG = 1,
    UPDATE_SONG,
    PLAY_SONG,
    PAUSE_RESUME,
    PRINT_STATUS,
    QUIT
};

//Update_song's option
enum menu_update_song
{
    UPDATE_A_SONG = 1,
    UPDATE_LOVED,
    RESET_TIMES_PLAYED,
    DELETE,
    QUIT_UPDATE
};

//Structure of Storing a song
struct song_data
{
    string name;
    string unique_id;
    string path;
    bool loved;
    int times;
};

//Structure to store all data for the music player
struct music_player_data
{
    dynamic_array<song_data> songs;//Dynamic array of songs
    int next_id;
    
};

//print a song
void print_song(const song_data &song)
{
    write_line("Song:" + song.name);
    write_line("ID:" + song.unique_id);
    write_line("Path:" + song.path);
    write_line("Loved:" + string(song.loved ? "Yes" : "No"));
    write_line("Times played:" + to_string(song.times));
    write_line();
}
//read the input of the user and create a new song（make a song）
song_data read_song(int next_id)
{
    song_data result;

    result.name = read_string("Enter song name: ");//input a name
    while (result.name == "")//Keep asking when user enter a empty name
    {
        write_line("You should put a song here!");
        result.name = read_string("Enter song name:");
    }
    result.path = read_string("Enter file path:");

    result.loved = read_boolean("Do you love this song? (y/n): ");

    result.unique_id = "song-" + to_string(next_id);//song-1....
    result.times = 0;//New song starts with 0 play count
    return result;
};

//Add a new song into the song list
void add_song(music_player_data &player)
{
    song_data song = read_song(player.next_id);
    player.songs.add(song);// adding one whole song_data object into the dynamic array
    player.next_id++;

    write_line("Song" + song.name + "added with ID" + song.unique_id);
    write_line("Loading music:" + song.path + " (ID:)" + song.unique_id + ")");
}
//print all songs stored in the player
void list_song(const music_player_data &player)
{
    int song_count = player.songs.length();

    if (song_count == 0)//no songs here
    {
        write_line("You should put a song here!");
        return;
    }
    //Loop through all songs and print all songs 
    for (int i = 0; i < song_count; i++)
    {
        string song_num = to_string(i + 1);
        write("Song" + song_num + ": \n");
        print_song(player.songs[i]);
    }
    write_line("Total songs: " + to_string(song_count));
    write_line();
}
//search the name for one song
int find_song(const music_player_data &player)//reference
{
    if (player.songs.length() == 0)
    {
        write_line("No songs added yet.");
        return -1;
    }
    string search_text = read_string("Enter text to search for: ");
    dynamic_array<int> matching_indices; //create a dynamic_array stores integer that are the indexes of songs that match the search text.
    //Check which songs contain the search text
    for (int i = 0; i < player.songs.length(); i++)
    {
        if (contains(player.songs[i].name, search_text))//if the song name contains the search text
        {
            matching_indices.add(i);
            write_line(to_string(matching_indices.length()) + ". " + player.songs[i].name);
        }
    }
    //no matching
    if (matching_indices.length() == 0)
    {
        write_line("No matching songs.");
        return -1;
    }

    int index = read_integer("Select a song:", 1, matching_indices.length()) - 1;
    return matching_indices[index];
}

//Play the song selected by the user
void play_song(music_player_data &player)
{
    int index = find_song(player);// find the songs user's choice
    if (index == -1)
        return;

    player.songs[index].times++; // Increase play count

    if (music_playing())
    {
        stop_music();
    }
    //play selected song
    music m = load_music(player.songs[index].unique_id, player.songs[index].path);
    play_music(m);
    write_line("Playing " + player.songs[index].name);
    write_line("Times played: " + to_string(player.songs[index].times));
}

//Pause or resume the current song
void pause_resume(music_player_data &player)
{
    if (music_playing())
    {
        pause_music();
        write_line("Music paused.");
    }
    else
    {
        resume_music();
        write_line("Music resumed.");
    }
}

//Delete a song from the list
void delete_song(music_player_data &player, int index)
{
    string name = player.songs[index].name;
    stop_music();
    player.songs.remove(index);
    write_line("Deleted " + name + ".");
}
//Print status information about the player
void print_status(const music_player_data &player)
{
    int total_songs = player.songs.length();
    int total_played = 0;
    int total_loved = 0;
    // Count how many songs were played and how many are loved
    for (int i = 0; i < total_songs; i++)
    {
        if (player.songs[i].times > 0)
        {
            total_played++;
        }
        if (player.songs[i].loved)
        {
            total_loved++;
        }
    }
    write_line("MUsic Player Status.");
    write_line("Total songs:" + to_string(total_songs));
    write_line("Songs played:" + to_string(total_played));
    write_line("Loved songs:" + to_string(total_loved));
}
//print the main menu
void print_main_menu()
{
    write_line("Main Menu");
    write_line("1. Add a new song");
    write_line("2. Update a song");
    write_line("3. Play a song");
    write_line("4. Pause / Resume");
    write_line("5. Print status");
    write_line("6. Quit");
}
//updeate the main menu
void print_update_menu()
{
    write_line("Update Menu");
    write_line("1. Update name");
    write_line("2. Toggle loved status");
    write_line("3. Reset times played");
    write_line("4. Delete song");
    write_line("5. Quit update");
}
//Update the details of a selected song
void update_song(music_player_data &player)
{
    int index = find_song(player);
    if (index == -1)
        return;
    menu_update_song option;
    do
    {
        write_line("Current details:");
        print_song(player.songs[index]);
        write_line("");
        print_update_menu();

        option = (menu_update_song)read_integer("Enter an option: ", UPDATE_A_SONG, QUIT_UPDATE);

        switch (option)
        {
        case UPDATE_A_SONG:
            player.songs[index].name = read_string("Enter new name: ");
            write_line("Updated name.");
            break;

        case UPDATE_LOVED:
            player.songs[index].loved = !player.songs[index].loved;
            write_line("Loved status toggled to: " + string(player.songs[index].loved ? "Yes" : "No"));
            break;

        case RESET_TIMES_PLAYED:
            player.songs[index].times = 0;
            write_line("Times played reset to 0.");
            break;

        case DELETE:
            delete_song(player, index);
            write_line("Song deleted. Returning to main menu...");
            option = QUIT_UPDATE; 
            break;


        case QUIT_UPDATE:
            write_line("Returning to main menu...");
            break;
        }
    } while (option != QUIT_UPDATE);
}

int main()
{
    music_player_data player = {};// Create and initialize player data, so the object name called player
    player.next_id = 1;
    
    
    write_line("Welcome to the Music Player!");

    menu_option option;
    do
    {
        print_main_menu();
        option = (menu_option)read_integer("Please choose an option: ", ADD_SONG, QUIT);// only input form ADD_SONG to QUIT

        switch (option)
        {
        case ADD_SONG:
            add_song(player);
            break;

        case UPDATE_SONG:
            update_song(player);
            break;

        case PLAY_SONG:
            play_song(player);
            break;

        case PAUSE_RESUME:
            pause_resume(player);
            break;

        case PRINT_STATUS:
            print_status(player);
            break;

        case QUIT:
            break;
        }
    } while (option != QUIT);

    write_line("Thank you for using the Music Player!");
    return 0;
}
