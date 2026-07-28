#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include <windows.h>
#include <mmsystem.h>
#include <dirent.h>
#include <string.h>

#pragma comment(lib, "winmm.lib")


typedef struct {
    char song[50];
    char artist[50];
    char filePath[100];
    unsigned int views;
} Song;

typedef struct Node Node;

struct Node{
    Song* song;
    Node* next;
    Node* prev;
    
};

typedef struct {
    Node* head;
    Node* end;
    int size;

} LinkedList;



void insertNode(LinkedList* list, int index, Song* song){

    if(list->head == NULL){
        Node* newNode = calloc(1, sizeof(Node));
        newNode->song = song;
        list->head = newNode;
        list->size++;
    }else{
        printf("list->size: %d %s\n", list->size, song->song);
        Node* curr = list->head;
        int currInd = 0;

        if(curr == NULL){
            printf("THE HEAD IS NULL\n");
        }
        while(curr->next != NULL && currInd < index){
            curr = curr->next;
            currInd++;
        }
        Node* temp = curr->next;
        Node* newNode = calloc(1, sizeof(Node));
        newNode->song = song;
        newNode->next = temp;
        newNode->prev = curr;
        curr->next = newNode;
        if(temp){
            temp->prev = newNode;
        }else{
            list->end = newNode;
        }
        list->size++;
    }
}

void appendNode(LinkedList* list, Song* song){
    insertNode(list, list->size - 1, song);
}


void printSong(Song *song){
    printf("Song Name: %s\n", song->song);
    printf("Artist: %s\n", song->artist);
    printf("Number of Views: %d\n", song->views);
}


void printSongs(LinkedList *list){
    
    Node* curr = list->head;

    while(curr != NULL){
        printSong(curr->song);
        printf("\n");
        curr = curr->next;
    }
}

void freeLinkedList(LinkedList *list){

    Node *curr = list->head;

    while (curr != NULL) {
        Node *temp = curr->next;
        free(curr->song);
        free(curr);
        curr = temp;
    }

    list->head = NULL;
    list->size = 0;
}


static LinkedList list;




bool containsSubString(char mainString[], char subString[]){
    int subLength = strlen(subString);
    int i = 0;
    while(mainString[i] != '\0'){
        int matchCounter = 0;
        for(int j = i; j < i + subLength; j++){
            if(mainString[j] == '\0'){
                return false;
            }else if(mainString[j] == subString[j - i]){
                matchCounter++;
            }
        }

        if(matchCounter == subLength){
            return true;
        }
        i++;
    }

    return false;
   

    
    
}



void scanForSongs(char directory[], LinkedList* list){

    struct dirent *de;  // Pointer for directory entry

    // opendir() returns a pointer of DIR type. 
    
    DIR *dr = opendir(directory);

    if (dr == NULL)  // opendir returns NULL if couldn't open directory
    {
        printf("Could not open current directory" );
        return;
    }



    while ((de = readdir(dr)) != NULL)

            if(containsSubString(de->d_name, "wav")){
                Song* song = calloc(1, sizeof(Song));
                strcpy(song->artist, "Unknown");
                strcpy(song->song, de->d_name);
                song->views = 6767;
                char totalPath[150];
                strcpy(totalPath, directory);
                strcat(totalPath, "/");
                strcpy(song->filePath, strcat(totalPath, de->d_name));

                appendNode(list, song);
            }

    closedir(dr);  
}


Node* gotoNextSong(Node* currNode, LinkedList *list){
    if(currNode->next != NULL){
        return currNode->next;
    }else{
        return list->head;
    }
}

Node* gotoPrevSong(Node* currNode, LinkedList *list){
    if(currNode->prev == NULL){
        return list->end;
    }else{
        return currNode->prev;
    }
}


int main(int argc, char *argv[]) {

    char directory[100];

    if(argc == 1){
        strcpy(directory, ".");
    }else{
        printf("GOT MULTIPLE COMMANDS\n");
        if(!containsSubString(argv[1], "C:")){
            char d[100] = "./";
            strcpy(directory, strcat(d, argv[1]));
        }else{
            strcpy(directory, argv[1]);
        }
        
    }

    list.head = NULL;
    list.size = 0;

    

    // 


    printf("FINAL DIRECTORY %s\n", directory);
    scanForSongs(directory, &list);
    printSongs(&list);

    Node* currSongNode = list.head;

    if(currSongNode == NULL){
        printf("THERE ARE NO SONGS IN THIS DIRECTORY!\n");
        return 0;
    }

  

    char command[20];
    scanf("%20s", command);
   
  
    while(list.size != 0 && strcmp(command, "quit") != 0){
        printf("NOW PLAYING: \n");
        printSong(currSongNode->song);
        PlaySound(currSongNode->song->filePath, NULL, SND_FILENAME | SND_ASYNC);
        scanf("%s", command);

        if(strcmp(command, "next") == 0){
            PlaySound(NULL, NULL, 0);
            currSongNode = gotoNextSong(currSongNode, &list);
        }else if(strcmp(command, "prev") == 0){
            PlaySound(NULL, NULL, 0);
            currSongNode = gotoPrevSong(currSongNode, &list);
        }

        //else will replay song


    }
    

    freeLinkedList(&list);
    
    return 0;
}