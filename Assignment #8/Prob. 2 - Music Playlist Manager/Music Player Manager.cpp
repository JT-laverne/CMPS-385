#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

struct Song {
    int id;
    string title;
    string artist;
    float duration;
    Song* prev;
    Song* next;
};

Song* head = nullptr;
Song* tail = nullptr;
Song* current = nullptr;

// Function declarations
void loadPlaylist();
void savePlaylist();
void addSong();
void displayPlaylist();
void playNext();
void playPrevious();
void removeSong();

// MAIN
int main() {

    loadPlaylist();

    int choice;
    do {
        cout << "\n****** Welcome to Music Playlist Manager ******\n";
        cout << "1. Add Song to Playlist\n2. Display Playlist\n3. Play Next Song\n4. Play Previous Song\n5. Remove Song\n6. Save and Exit\n→ ";
        cin >> choice;

        switch (choice) {
        case 1: addSong(); break;
        case 2: displayPlaylist(); break;
        case 3: playNext(); break;
        case 4: playPrevious(); break;
        case 5: removeSong(); break;
        case 6:
            savePlaylist();
            cout << "Playlist saved. See you next jam!" << endl;
            break;
        default:
            cout << "Invalid option. Try again.\n";
        }

    } while (choice != 6);

    return 0;
}

// Add a Song
void addSong() {
    Song* newSong = new Song();

    cout << "Enter Song ID: ";
    cin >> newSong->id;
    cin.ignore();

    cout << "Enter Title: ";
    getline(cin, newSong->title);

    cout << "Enter Artist: ";
    getline(cin, newSong->artist);

    cout << "Enter Duration (in minutes): ";
    cin >> newSong->duration;

    newSong->next = nullptr;
    newSong->prev = nullptr;

    if (head == nullptr) {
        head = tail = current = newSong;
    }
    else {
        tail->next = newSong;
        newSong->prev = tail;
        tail = newSong;
    }

    cout << "Song added to playlist!\n";
}

// Display Playlist
void displayPlaylist() {
    if (head == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    cout << "\n========== CURRENT PLAYLIST ==========\n";
    cout << left << setw(10) << "ID"
        << setw(25) << "Title"
        << setw(20) << "Artist"
        << setw(10) << "Duration" << endl;

    cout << "---------------------------------------------------------------\n";

    Song* temp = head;

    while (temp != nullptr) {
        cout << left << setw(10) << temp->id
            << setw(25) << temp->title
            << setw(20) << temp->artist
            << setw(10) << temp->duration << endl;

        temp = temp->next;
    }
}

// Play Next Song
void playNext() {
    if (current == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    if (current->next == nullptr) {
        cout << "You are at the last song.\n";
        return;
    }

    current = current->next;
    cout << "Now playing: " << current->title << " by "
        << current->artist << " (" << current->duration << " min)\n";
}

// Play Previous Song
void playPrevious() {
    if (current == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    if (current->prev == nullptr) {
        cout << "You are at the first song.\n";
        return;
    }

    current = current->prev;
    cout << "Now playing: " << current->title << " by "
        << current->artist << " (" << current->duration << " min)\n";
}

// Remove a Song
void removeSong() {
    if (head == nullptr) {
        cout << "Playlist is empty.\n";
        return;
    }

    int removeID;
    cout << "Enter Song ID to remove: ";
    cin >> removeID;

    Song* temp = head;

    while (temp != nullptr && temp->id != removeID) {
        temp = temp->next;
    }

    if (temp == nullptr) {
        cout << "Song not found.\n";
        return;
    }

    if (temp == head) {
        head = head->next;
        if (head) head->prev = nullptr;
    }

    if (temp == tail) {
        tail = tail->prev;
        if (tail) tail->next = nullptr;
    }

    if (temp->prev != nullptr)
        temp->prev->next = temp->next;
    if (temp->next != nullptr)
        temp->next->prev = temp->prev;

    if (current == temp) {
        if (temp->next != nullptr)
            current = temp->next;
        else
            current = temp->prev;
    }

    cout << "Song '" << temp->title << "' removed from playlist.\n";
    delete temp;
}
 