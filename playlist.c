#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SONGS 100

// Structure to store song information
struct Song {
    char name[100];
    char artist[100];
};

// Global array to store the playlist
struct Song playlist[MAX_SONGS];
int songCount = 0;

// Function to add a song to the playlist
void addSong(const char *name, const char *artist) {
    if (songCount < MAX_SONGS) {
        strcpy(playlist[songCount].name, name);
        strcpy(playlist[songCount].artist, artist);
        songCount++;
    }
}

// Function to get the playlist as JSON
void getPlaylistJSON() {
    printf("Content-Type: application/json\r\n\r\n");
    printf("[");
    for (int i = 0; i < songCount; i++) {
        printf("{\"name\":\"%s\",\"artist\":\"%s\"}", playlist[i].name, playlist[i].artist);
        if (i < songCount - 1) {
            printf(",");
        }
    }
    printf("]");
}

int main(void) {
    char *data;
    char *name, *artist;

    // Read input data
    data = getenv("QUERY_STRING");

    // Parse the input data
    if (data) {
        name = strtok(data, "&");
        artist = strtok(NULL, "&");
        if (name && artist) {
            name = strchr(name, '=') + 1;
            artist = strchr(artist, '=') + 1;
            addSong(name, artist);
        }
    }

    // Output the playlist as JSON
    getPlaylistJSON();

    return 0;
}