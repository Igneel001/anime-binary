#include <iostream>
#include <fstream>
#include <cstring>
#include <sstream>

using namespace std;


// Function Declaration

int add_anime(), update_anime(), display_anime(), delete_anime(), search_display_anime();
int add_manga(), update_manga(), display_manga(), delete_manga(), search_display_manga();
int add_watchlist_anime(), add_readlist_manga(), update_watchlist_anime(), update_readlist_manga(), display_watchlist_anime(), display_readlist_manga();

void success(string success), error(string error);
char* strip(char *name);
int anime_check(char *Aname), manga_check(char *Mname), watchlist_anime_check(char *WAname), watchlist_manga_check(char *WMname);


// Structure Definition 

struct Anime_list{
    char anime_name[100];
    char completed;
    int season;
    int recent_ep_watched;
}al;

struct Manga_list{
    char manga_name[100];
    char finished;
    int recent_chap_read;
}ml;

struct Watch_list{
    char anime_to_watch[100];
    char manga_to_read[100];
}wl;


// Global variables

ifstream fi;  
ofstream fo; 
int flag = 0;


// Main function

int main(){

    char to_be_updated[100], updated_manga_status, del, existing_name[100], name_to_check[100], search_anime[100], search_manga[100], watchlist_anime[100], updated_watchlist_anime[100], watchlist_manga[100], updated_watchlist_manga[100]; 
    int ch, updated_manga_chap, AnimeOrManga, watch_list, read_list;
    do{
        cout<<"\n1. Anime \n2. Manga \n3. Watch List \n4. Exit \nEnter your choice: ";
        cin>>AnimeOrManga;
        switch(AnimeOrManga){

            // Anime commands
            
                case 1: 
                        do{
                            cout<<"\n1. Add \n2. Modify \n3. Display \n4. Delete \n5. Search \n6. Exit \nEnter your choice: ";
                            cin>>ch;
                            cin.clear();
                            cin.sync();
                            switch(ch){
                                case 1: // Add anime
                                        cout<<"\n<----Add---->";
                                        fo.open("anime.dat", ios::out | ios::binary | ios::app);
 
                                        if(add_anime() == 1){
                                            fo.close();
                                            break;
                                        }  
                                        else{
                                            cout<<"\n Writing into binary file\n";
                                            fo.write((char*)&al, sizeof(Anime_list));
                                            fo.close();
                                        }

                                        if(!fo.good()){
                                            error("Error occured at the time of writing");
                                            return 1;
                                        }
                                        else if(fo.good()){
                                            success("Data entry successful");
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;

                                case 2: // Update specific anime
                                        flag = 0;
                                        char mod;
                                        fi.open("anime.dat", ios::in | ios::binary);
                                        
                                        if(!fi){
                                            error("Error occured while opening the file / File does not exist");
                                            break;
                                        }
                                        cout<<"\n<----Modify---->";
                                        cout<<"\nAre you sure you want to update an anime from the list (y/n): ";
                                        cin>>mod;
                                        cin.clear();
                                        cin.sync();

                                        if(mod == 'y' || mod == 'Y'){
                                            cout<<"\nEnter the name of the anime to be modified: ";
                                            #ifndef _WIN32
                                                cin.ignore();
                                            #endif
                                            cin.getline(to_be_updated, 100);

                                                while(fi.read((char*)&al, sizeof(Anime_list))){
                                                    strcpy(existing_name, al.anime_name);
                                                    strcpy(name_to_check, to_be_updated);
                                                    #ifdef _WIN32
                                                        if(strcmpi(strip(existing_name), strip(name_to_check)) == 0){
                                                            flag = 1;
                                                            
                                                            update_anime();

                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                            fo.write((char*)&al, sizeof(Anime_list));
                                                            fo.close();
                                                        }
                                                    #else
                                                        if(strcasecmp(strip(existing_name), strip(name_to_check)) == 0){
                                                            flag = 1;
                                                            
                                                            update_anime();

                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                            fo.write((char*)&al, sizeof(Anime_list));
                                                            fo.close();
                                                        }
                                                    #endif
                                                        else{
                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                            fo.write((char*)&al, sizeof(Anime_list));
                                                            fo.close();
                                                        }
                                                }
                                                if(!fo.good()){
                                                    error("Error occured at the time of writing");
                                                }
                                                else if(fo.good()){
                                                    if(flag == 0){
                                                        error("Record not found");
                                                        remove("update.dat");
                                                        fi.close();
                                                        break;
                                                    }
                                                    else
                                                        success("Data updation successful");
                                                }

                                            fi.close();
                                            remove("anime.dat");
                                            rename("update.dat", "anime.dat");
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;

                                case 3: // Display all anime
                                        fi.open("anime.dat", ios::in | ios::binary);
                                        
                                        if(!fi){
                                            error("Error occured while opening the file / File does not exist");
                                            break;
                                        }
                                        cout<<"\n<----Display---->";

                                        display_anime();
                                        
                                        fi.close();
                                        cout<<"\n<----Exit---->";
                                        break;

                                case 4: // Delete specific anime
                                        cout<<"\n<----Delete---->";
                                        cout<<"\nAre you sure you want to delete an anime from the list (y/n): ";
                                        cin>>del;
                                        cin.clear();
                                        cin.sync();
                                       
                                        if(del == 'y' || del == 'Y'){
                                            fi.open("anime.dat", ios::in | ios::binary);
                                            
                                            if(!fi){
                                                error("Error occured while opening the file / File does not exist");
                                                break;
                                            } 

                                            delete_anime();

                                            if(!flag){
                                                error("Record not found");
                                                remove("delete.dat");
                                                fi.close();
                                                break;
                                            }
                                            else{
                                                success("Anime removed from the list");
                                            }
                                            fi.close();
                                            remove("anime.dat");
                                            rename("delete.dat", "anime.dat");
                                        }
                                        cout<<"\n<----Exit---->";                
                                        break;
                                
                                case 5: // Display specific anime
                                        cout<<"\n<----Search---->";
                                        fi.open("anime.dat", ios::in | ios::binary);

                                        cout<<"\n Enter the name of the anime: ";
                                        #ifndef _WIN32
                                            cin.ignore();
                                        #endif
                                        cin.getline(search_anime, 100);

                                        while(fi.read((char*)&al, sizeof(Anime_list))){
                                            strcpy(existing_name, al.anime_name);
                                            strcpy(name_to_check, search_anime);
                                            
                                            #ifdef _WIN32
                                                if(strcmpi(strip(existing_name), strip(name_to_check)) == 0){
                                                    flag = 1;

                                                    search_display_anime();
                                                }
                                            #else
                                                if(strcasecmp(strip(existing_name), strip(name_to_check)) == 0){
                                                    flag = 1;
                                                    
                                                    search_display_anime();
                                                }
                                            #endif
                                        }
                                        if(flag == 0){
                                            error("Record not found");
                                            fi.close();
                                            break;
                                        }
                                        fi.close();
                                        cout<<"\n<----Exit---->";    
                                        break;            

                                case 6: // Exit program
                                        cout<<".\n.\nExiting program\n\n";
                                        return 1; 

                                default: 
                                        error("Invalid command");
                                        break;
                                        
                            }
                        }while(ch != 7);
                        break;

            // Manga commands
                
                case 2:
                        do{
                            cout<<"\n1. Add \n2. Update \n3. Display \n4. Delete \n5. Search \n6. Exit \nEnter your choice: ";
                            cin>>ch;
                            cin.clear();
                            cin.sync();
                            switch(ch){
                                case 1: // Add manga
                                        cout<<"\n<----Add---->";
                                        fo.open("manga.dat", ios::out | ios::binary | ios::app);

                                        if(add_manga() == 1){
                                            fo.close();
                                            break;
                                        }
                                        else{
                                            cout<<"\n Writing into binary file\n";
                                            fo.write((char*)&ml, sizeof(Manga_list));
                                            fo.close();
                                        }
                                        
                                        
                                        if(!fo.good()){
                                            error("Error occured at the time of writing");
                                            return 1;
                                        }
                                        else if(fo.good()){
                                            success("Data entry sucessful");
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;
                                
                                case 2: // Update specific manga
                                        flag = 0;
                                        char mod;
                                        fi.open("manga.dat", ios::in | ios::binary);
                                        
                                        if(!fi){
                                            error("Error occured while opening the file / File does not exist");                                            
                                            return 1;
                                        }
                                        cout<<"\n<----Modify---->";
                                        cout<<"\nAre you sure you want to update a manga in the list (y/n): ";
                                        cin>>mod;
                                        cin.clear();
                                        cin.sync();

                                        if(mod == 'y' || mod == 'Y'){
                                            cout<<"\nEnter the name of the manga to be modified: ";
                                            #ifndef _WIN32
                                                cin.ignore();
                                            #endif
                                            cin.getline(to_be_updated, 100);

                                                while(fi.read((char*)&ml, sizeof(Manga_list))){
                                                
                                                    strcpy(existing_name, ml.manga_name);
                                                    strcpy(name_to_check, to_be_updated);
                                                    #ifdef _WIN32
                                                        if(strcmpi(strip(existing_name), strip(name_to_check)) == 0){
                                                            flag = 1;
                                                            
                                                            update_manga();

                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                            fo.write((char*)&ml, sizeof(Manga_list));
                                                            fo.close();
                                                        }
                                                    #else
                                                        if(strcasecmp(strip(existing_name), strip(name_to_check)) == 0){
                                                            flag = 1;
                                                            
                                                            update_manga();

                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                            fo.write((char*)&ml, sizeof(Manga_list));
                                                            fo.close();
                                                        }
                                                    #endif
                                                        else{
                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                            fo.write((char*)&ml, sizeof(Manga_list));
                                                            fo.close();
                                                        }
                                                }
                                                if(!fo.good()){
                                                    error("Error occured at the time of writing");
                                                    return 1;
                                                }
                                                else if(fo.good()){
                                                    if(!flag){
                                                        error("Record not found");
                                                        remove("update.dat");
                                                        fi.close();
                                                        break;
                                                    }
                                                    else
                                                        success("Data updation successful");
                                                }
                                                
                                            fi.close();
                                            remove("manga.dat");
                                            rename("update.dat", "manga.dat");
                                        }
                                        cout<<"\n<----Exit---->";
                                        break;
                                
                                case 3: // Display all manga
                                        fi.open("manga.dat", ios::in | ios::binary);
                                        
                                        if(!fi){
                                            error("Error occured while opening the file / File does not exist");
                                            break;
                                        }
                                        cout<<"\n<----Display---->";

                                        display_manga();
                                        
                                        cout<<"\n<----Exit---->";
                                        fi.close();
                                        break;
                                
                                case 4: // Delete specific manga
                                        cout<<"\n<----Delete---->";
                                        cout<<"\nAre you sure you want to delete a manga from the list (y/n): ";
                                        cin>>del;
                                        cin.clear();
                                        cin.sync();
                                        
                                        if(del == 'y' || del == 'Y'){
                                            fi.open("manga.dat", ios::in | ios::binary);
                                            if(!fi){
                                                error("Error occured while opening the file / File does not exist");
                                                break;
                                            } 

                                            delete_manga();

                                            if(!flag){
                                                error("Record not found");
                                                remove("delete.dat");
                                                fi.close();
                                                break;
                                            }
                                            else{
                                                success("Manga removed from the list");
                                            }
                                            fi.close();
                                            remove("manga.dat");
                                            rename("delete.dat", "manga.dat");
                                        }
                                        cout<<"\n<----Exit---->";                
                                        break;
                               
                                case 5: // Display specific manga
                                        cout<<"\n<----Search---->";
                                        fi.open("manga.dat", ios::in | ios::binary);

                                        cout<<"\n Enter the name of the manga: ";
                                        #ifndef _WIN32
                                            cin.ignore();
                                        #endif
                                        cin.getline(search_manga, 100);

                                        while(fi.read((char*)&ml, sizeof(Manga_list))){
                                            strcpy(existing_name, ml.manga_name);
                                            strcpy(name_to_check, search_manga);
                                            
                                            #ifdef _WIN32
                                                if(strcmpi(strip(existing_name), strip(name_to_check)) == 0){
                                                    flag = 1;

                                                    search_display_manga();
                                                }
                                            #else
                                                if(strcasecmp(strip(existing_name), strip(name_to_check)) == 0){
                                                    flag = 1;
                                                    
                                                    search_display_manga();
                                                }
                                            #endif
                                        }
                                        if(flag == 0){
                                            error("Record not found");
                                            fi.close();
                                            break;
                                        }
                                        fi.close();
                                        cout<<"\n<----Exit---->";    
                                        break;

                                case 6: // Exit program
                                        cout<<".\n.\nExiting program\n\n";
                                        return 1;
                                
                                default:
                                        error("Invalid Command");
                                        break;      
                            }
                        }while(ch != 7);
                        break;
                
                // watch list 

                case 3: 
                        do{
                            cout<<"\n1. Anime \n2. Manga \nEnter your choice: ";
                            cin>>ch;
                            cin.clear();
                            cin.sync();

                            switch(ch){
                                case 1: 
                                        do{
                                            cout<<"\n1. Add \n2. Update \n3. Display \n4. Mark as Completed \n5. Exit \nEnter your choice: ";
                                            cin>>watch_list;
                                            cin.clear();
                                            cin.sync();

                                            switch(watch_list){
                                                case 1: // Add anime name to watchlist
                                                        cout<<"\n<----Add---->";
                                                        fo.open("anime_watchlist.dat", ios::out | ios::binary | ios::app);
                                                        
                                                        if(add_watchlist_anime() == 1){
                                                            fo.close();
                                                            break;
                                                        }
                                                        else{
                                                            cout<<"\n Writing into binary file\n";
                                                            fo.write((char*)&wl, sizeof(Watch_list));
                                                            fo.close();
                                                        }
                                                                                                            
                                                        if(!fo.good()){
                                                            error("Error occured at the time of writing");
                                                            return 1;
                                                        }
                                                        else if(fo.good()){
                                                            success("Data entry successful");
                                                        }
                                                        cout<<"\n<----Exit---->";
                                                        break;

                                                case 2: // Update anime name
                                                        char mod;
                                                        fi.open("anime_watchlist.dat", ios::in | ios::binary);
                                                        
                                                        if(!fi){
                                                            error("Error occured while opening the file / File does not exist");
                                                            break;
                                                        }
                                                        cout<<"\n<----Update---->";
                                                        cout<<"\nAre you sure you want to update an anime from the list (y/n): ";
                                                        cin>>mod;
                                                        cin.clear();
                                                        cin.sync();

                                                        if(mod == 'y' || mod == 'Y'){
                                                            cout<<"\nEnter the name of the anime to be modified: ";
                                                            #ifndef _WIN32
                                                                cin.ignore();
                                                            #endif
                                                            cin.getline(to_be_updated, 100);

                                                                while(fi.read((char*)&wl, sizeof(Watch_list))){
                                                                    strcpy(existing_name, wl.anime_to_watch);
                                                                    strcpy(name_to_check, to_be_updated);
                                                                    #ifdef _WIN32
                                                                        if(strcmpi(strip(existing_name), strip(name_to_check)) == 0){
                                                                            flag = 1;
                                                                            
                                                                            update_watchlist_anime();

                                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                                            fo.write((char*)&wl, sizeof(Watch_list));
                                                                            fo.close();
                                                                        }
                                                                    #else
                                                                        if(strcasecmp(strip(existing_name), strip(name_to_check)) == 0){
                                                                            flag = 1;

                                                                            update_watchlist_anime();
                                                                
                                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                                            fo.write((char*)&wl, sizeof(Watch_list));
                                                                            fo.close();
                                                                        }
                                                                    #endif
                                                                        else{
                                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                                            fo.write((char*)&wl, sizeof(Watch_list));
                                                                            fo.close();
                                                                        }
                                                                }
                                                                if(!fo.good()){
                                                                    error("Error occured at the time of writing");
                                                                }
                                                                else if(fo.good()){
                                                                    if(flag == 0){
                                                                        error("Record not found");
                                                                        remove("update.dat");
                                                                        fi.close();
                                                                        break;
                                                                    }
                                                                    else
                                                                        success("Data updation successful");
                                                                }

                                                            fi.close();
                                                            remove("anime_watchlist.dat");
                                                            rename("update.dat", "anime_watchlist.dat");
                                                        }
                                                        cout<<"\n<----Exit---->";
                                                        break;

                                                case 3: // Display all watchlist names
                                                        fi.open("anime_watchlist.dat", ios::in | ios::binary);
                                                        
                                                        if(!fi){
                                                            error("Error occured while opening the file / File does not exist");
                                                            break;
                                                        }
                                                        cout<<"\n<----Display---->";

                                                        display_watchlist_anime();
                                                        
                                                        fi.close();
                                                        cout<<"\n<----Exit---->";
                                                        break;

                                                case 4: // Delete an anime from the watchlist
                                                        cout<<"\n<----Delete---->";
                                                        cout<<"\nAre you sure you want to Mark an anime as Completed from the list (y/n): ";
                                                        cin>>del;
                                                        cin.clear();
                                                        cin.sync();
                                                    
                                                        if(del == 'y' || del == 'Y'){
                                                            fi.open("anime_watchlist.dat", ios::in | ios::binary);
                                                            
                                                            if(!fi){
                                                                error("Error occured while opening the file / File does not exist");
                                                                break;
                                                            } 

                                                            char to_be_deleted[100], original[100];
                                                            flag = 0;

                                                            cout<<"\n Enter the name of the anime to be Marked as Completed: ";
                                                            #ifndef _WIN32
                                                                cin.ignore();
                                                            #endif
                                                            cin.getline(to_be_deleted, 100);
                                                            while(fi.read((char*)&wl, sizeof(Watch_list))){
                
                                                                strcpy(original, wl.anime_to_watch);
                                                                #ifdef _WIN32
                                                                    if(strcmpi(strip(original), strip(to_be_deleted)) == 0){
                                                                        flag = 1;
                                                                    }
                                                                #else
                                                                    if(strcasecmp(strip(original), strip(to_be_deleted)) == 0){
                                                                        flag = 1;
                                                                    }
                                                                #endif
                                                                    else{ 
                                                                        fo.open("delete.dat", ios::out | ios::binary | ios::app);
                                                                        fo.write((char*)&wl, sizeof(Watch_list));
                                                                        fo.close();
                                                                }
                                                            }

                                                            if(!flag){
                                                                error("Record not found");
                                                                remove("delete.dat");
                                                                fi.close();
                                                                break;
                                                            }
                                                            else{
                                                                success("Anime marked as completed");
                                                            }
                                                            fi.close();
                                                            remove("anime_watchlist.dat");
                                                            rename("delete.dat", "anime_watchlist.dat");
                                                        }
                                                        cout<<"\n<----Exit---->";                
                                                        break;                                                        
                                                
                                                case 5: // Exit program
                                                        cout<<".\n.\nExiting program\n\n";
                                                        return 1;

                                                default: 
                                                        error("Invalid command");
                                                        break;
                                            }
                                        }while(watch_list != 6); 
                                        break;
                                
                                case 2: 
                                        do{
                                            cout<<"\n1. Add \n2. Update \n3. Display \n4. Mark as Read \n5. Exit \nEnter your choice: ";
                                            cin>>read_list;
                                            cin.clear();
                                            cin.sync();

                                            switch(read_list){
                                                case 1: // Add manga name to watchlist
                                                        cout<<"\n<----Add---->";
                                                        fo.open("manga_watchlist.dat", ios::out | ios::binary | ios::app);
                                                        
                                                        if(add_readlist_manga() == 1){
                                                            fo.close();
                                                            break;
                                                        }
                                                        else{
                                                            cout<<"\n Writing into binary file\n";
                                                            fo.write((char*)&wl, sizeof(Watch_list));
                                                            fo.close();
                                                        }
                                                                                                            
                                                        if(!fo.good()){
                                                            error("Error occured at the time of writing");
                                                            return 1;
                                                        }
                                                        else if(fo.good()){
                                                            success("Data entry successful");
                                                        }
                                                        cout<<"\n<----Exit---->";
                                                        break;

                                                case 2: // Update manga name
                                                        char mod;
                                                        fi.open("manga_watchlist.dat", ios::in | ios::binary);
                                                        
                                                        if(!fi){
                                                            error("Error occured while opening the file / File does not exist");
                                                            break;
                                                        }
                                                        cout<<"\n<----Update---->";
                                                        cout<<"\nAre you sure you want to update a manga from the list (y/n): ";
                                                        cin>>mod;
                                                        cin.clear();
                                                        cin.sync();

                                                        if(mod == 'y' || mod == 'Y'){
                                                            cout<<"\nEnter the name of the manga to be modified: ";
                                                            #ifndef _WIN32
                                                                cin.ignore();
                                                            #endif
                                                            cin.getline(to_be_updated, 100);

                                                                while(fi.read((char*)&wl, sizeof(Watch_list))){
                                                                    strcpy(existing_name, wl.manga_to_read);
                                                                    strcpy(name_to_check, to_be_updated);
                                                                    #ifdef _WIN32
                                                                        if(strcmpi(strip(existing_name), strip(name_to_check)) == 0){
                                                                            flag = 1;
                                                                            
                                                                            update_readlist_manga();

                                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                                            fo.write((char*)&wl, sizeof(Watch_list));
                                                                            fo.close();
                                                                        }
                                                                    #else
                                                                        if(strcasecmp(strip(existing_name), strip(name_to_check)) == 0){
                                                                            flag = 1;

                                                                            update_readlist_manga();
                                                                
                                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                                            fo.write((char*)&wl, sizeof(Watch_list));
                                                                            fo.close();
                                                                        }
                                                                    #endif
                                                                        else{
                                                                            fo.open("update.dat", ios::out | ios::binary | ios::app);
                                                                            fo.write((char*)&wl, sizeof(Watch_list));
                                                                            fo.close();
                                                                        }
                                                                }
                                                                if(!fo.good()){
                                                                    error("Error occured at the time of writing");
                                                                }
                                                                else if(fo.good()){
                                                                    if(flag == 0){
                                                                        error("Record not found");
                                                                        remove("update.dat");
                                                                        fi.close();
                                                                        break;
                                                                    }
                                                                    else
                                                                        success("Data updation successful");
                                                                }

                                                            fi.close();
                                                            remove("manga_watchlist.dat");
                                                            rename("update.dat", "manga_watchlist.dat");
                                                        }
                                                        cout<<"\n<----Exit---->";
                                                        break;

                                                case 3: // Display all watchlist names
                                                        fi.open("manga_watchlist.dat", ios::in | ios::binary);
                                                        
                                                        if(!fi){
                                                            error("Error occured while opening the file / File does not exist");
                                                            break;
                                                        }
                                                        cout<<"\n<----Display---->";

                                                        display_readlist_manga();
                                                        
                                                        fi.close();
                                                        cout<<"\n<----Exit---->";
                                                        break;

                                                case 4: // Delete a manga from the list
                                                        cout<<"\n<----Delete---->";
                                                        cout<<"\nAre you sure you want to Mark an manga as Completed from the list (y/n): ";
                                                        cin>>del;
                                                        cin.clear();
                                                        cin.sync();
                                                    
                                                        if(del == 'y' || del == 'Y'){
                                                            fi.open("manga_watchlist.dat", ios::in | ios::binary);
                                                            
                                                            if(!fi){
                                                                error("Error occured while opening the file / File does not exist");
                                                                break;
                                                            } 

                                                            char to_be_deleted[100], original[100];
                                                            flag = 0;

                                                            cout<<"\n Enter the name of the manga to be Marked as Read: ";
                                                            #ifndef _WIN32
                                                                cin.ignore();
                                                            #endif
                                                            cin.getline(to_be_deleted, 100);
                                                            while(fi.read((char*)&wl, sizeof(Watch_list))){
                
                                                                strcpy(original, wl.manga_to_read);
                                                                #ifdef _WIN32
                                                                    if(strcmpi(strip(original), strip(to_be_deleted)) == 0){
                                                                        flag = 1;
                                                                    }
                                                                #else
                                                                    if(strcasecmp(strip(original), strip(to_be_deleted)) == 0){
                                                                        flag = 1;
                                                                    }
                                                                #endif
                                                                    else{ 
                                                                        fo.open("delete.dat", ios::out | ios::binary | ios::app);
                                                                        fo.write((char*)&wl, sizeof(Watch_list));
                                                                        fo.close();
                                                                }
                                                            }

                                                            if(!flag){
                                                                error("Record not found");
                                                                remove("delete.dat");
                                                                fi.close();
                                                                break;
                                                            }
                                                            else{
                                                                success("Anime marked as completed");
                                                            }
                                                            fi.close();
                                                            remove("manga_watchlist.dat");
                                                            rename("delete.dat", "manga_watchlist.dat");
                                                        }
                                                        cout<<"\n<----Exit---->";                
                                                        break;                                                        
                                                
                                                case 5: // Exit program
                                                        cout<<".\n.\nExiting program\n\n";
                                                        return 1;

                                                default: 
                                                        error("Invalid command");
                                                        break;
                                            }
                                        }while(read_list != 6); 
                                        break;

                            }
                        }while(ch != 4);
                        break;
                
                case 4: return 1;
                
                default: 
                        error("Invalid Command");
                        break;
        }
    }while(AnimeOrManga != 5);
return 0;
}

// anime user defined functions

int add_anime(){
    char name[100], anime_completed;
    int anime_season, ep;

    cout<<"\n Anime name: ";
    #ifndef _WIN32
        cin.ignore();
    #endif
    cin.getline(name, 100);

    if(anime_check(name) == 1)
        return 1;
    
    strcpy(al.anime_name, name);
    
    cout<<"\n Have you completed the anime (y/n): ";
    cin>>anime_completed;
    anime_completed = tolower(anime_completed);
    al.completed = anime_completed;
                    
    switch(anime_completed){
        case 'n':   cout<<" Enter the season: ";
                    cin>>anime_season;
                    al.season = anime_season;
                    
                    cout<<" Enter the recent episode watched: ";
                    cin>>ep;
                    al.recent_ep_watched = ep;
                    break;
        case 'y':   cout<<"\n";
                    break;
        default:    error("Enter valid input");
                    return 1;
    }
return 0;
}

int update_anime(){
    int choice, updated_episode, updated_anime_season;
    char anime_completed, y_n, updated_anime_name[100];
    
    do{
        cout<<"\nWhat is to be updated? \n1. Anime name \n2. Episodes \n3. Exit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        cin.clear();
        cin.sync();
        switch(choice){
            case 1: 
                    cout<<" Enter new anime name: ";
                    #ifndef _WIN32
                        cin.ignore();
                    #endif
                    cin.getline(updated_anime_name, 100);
                    strcpy(al.anime_name, updated_anime_name);
                    break;
            case 2: 
                    if(al.completed == 'n'){
                        cout<<" Have you finished watching the anime (y/n): ";
                        cin>>anime_completed;
                        anime_completed = tolower(anime_completed);
                        al.completed = anime_completed;
                        
                        if(al.completed == 'n'){
                            cout<<" Enter the season: ";
                            cin>>updated_anime_season;
                            al.season = updated_anime_season;
                            
                            cout<<" Enter recent episode watched: ";
                            cin>>updated_episode;
                            al.recent_ep_watched = updated_episode;
                        }
                    }
                    else if(al.completed == 'y'){
                        cout<<" You have already completed watching the anime, continuing will set anime completed to 'no'";
                        cout<<"\n Do you want to continue? (y/n): ";
                        cin>>y_n;
                        if(y_n == 'y' || y_n == 'Y'){
                            al.completed = 'n';
                            cout<<"\n Anime completed status set to 'no'";
                            
                            cout<<"\n Enter the season: ";
                            cin>>updated_anime_season;
                            al.season = updated_anime_season;
                            
                            cout<<" Enter recent episode watched: ";
                            cin>>updated_episode;
                            al.recent_ep_watched = updated_episode;
                        }
                    }
                    break;   
            }
    }while(choice != 3);
return 0;
}

int display_anime(){
    
    while(fi.read((char*)&al, sizeof(Anime_list))){
        cout<<"\n------------------------------------------------------------------\n\n";
        cout<<"\tAnime name ................. "<<al.anime_name<<endl;
        cout<<"\tAnime completed ............ "<<al.completed<<endl;
        if(al.completed == 'n'){
            cout<<"\tSeason ..................... "<<al.season<<endl;
            cout<<"\tRecent episode watched ..... "<<al.recent_ep_watched<<endl;
        }
    }
return 0;
}

int delete_anime(){
    char to_be_deleted[100], original[100];
    flag = 0;

    cout<<"\n Enter the name of the anime to be deleted: ";
    #ifndef _WIN32
        cin.ignore();
    #endif
    cin.getline(to_be_deleted, 100);

        while(fi.read((char*)&al, sizeof(Anime_list))){
            
            strcpy(original, al.anime_name);
            #ifdef _WIN32
                if(strcmpi(strip(original), strip(to_be_deleted)) == 0){
                    flag = 1;
                }
            #else
                if(strcasecmp(strip(original), strip(to_be_deleted)) == 0){
                    flag = 1;
                }
            #endif
                else{ 
                    fo.open("delete.dat", ios::out | ios::binary | ios::app);
                    fo.write((char*)&al, sizeof(Anime_list));
                    fo.close();
                }
        }
return 0;
}

int search_display_anime(){
    cout<<"\n------------------------------------------------------------------\n\n";
    cout<<"\tAnime name ................. "<<al.anime_name<<endl;
    cout<<"\tAnime completed ............ "<<al.completed<<endl;
    if(al.completed == 'n'){
        cout<<"\tSeason ..................... "<<al.season<<endl;
        cout<<"\tRecent episode watched ..... "<<al.recent_ep_watched<<endl;
    }
return 0;
}

// manga user defined functions

int add_manga(){
    char mng[100], fin;
    int mng_chap;

    cout<<"\n Enter the manga name: ";
    #ifndef _WIN32
        cin.ignore();
    #endif
    cin.getline(mng, 100);

    if(manga_check(mng) == 1)
        return 1;
    
    strcpy(ml.manga_name, mng);
    
    cout<<"\n Have you completed reading the manga (y/n): ";
    cin>>fin;
    fin = tolower(fin);
    ml.finished = fin;

    switch(fin){
        case 'n':   cout<<" Enter recent manga chapter read: ";
                    cin>>mng_chap;
                    ml.recent_chap_read = mng_chap;
                    break;
        case 'y':   cout<<"\n";
                    break;
        default:    error("Enter valid input");
                    return 1;
    }
return 0;
}

int update_manga(){
    char manga_finished, y_n, updated_manga_name[100];
    int choice, updated_chap;
    
    do{
        cout<<"\nWhat is to be updated? \n1. Manga name \n2. Episodes \n3. Exit\nEnter your choice: ";
        cin>>choice;
        cin.clear();
        cin.sync();
        switch(choice){
            case 1:
                    cout<<" Enter new manga name: ";
                    #ifndef _WIN32
                        cin.ignore();
                    #endif
                    cin.getline(updated_manga_name, 100);
                    strcpy(ml.manga_name, updated_manga_name);
                    break;
            case 2: 
                    if(ml.finished == 'n'){
                        cout<<" Have you completed the manga (y/n): ";
                        cin>>manga_finished;
                        manga_finished = tolower(manga_finished);
                        ml.finished = manga_finished;
                        
                        if(ml.finished == 'n'){
                            cout<<" Enter the recent chapter read: ";
                            cin>>updated_chap;
                            ml.recent_chap_read = updated_chap;
                        }
                    }
                    else if(ml.finished == 'y'){
                        cout<<" You have already completed reading the manga, continuing will set manga completed to 'no'";
                        cout<<"\n Do you want to continue? (y/n): ";
                        cin>>y_n;
                        
                        if(y_n == 'y' || y_n == 'Y'){
                            ml.finished = 'n';
                            cout<<"\n Manga completed status set to 'no'";
                            
                            cout<<"\n Enter the recent chapter read: ";
                            cin>>updated_chap;
                            ml.recent_chap_read = updated_chap;
                        }
                    }
                    break;
        }
    }while(choice != 3);
return 0;
}

int display_manga(){

    while(fi.read((char*)&ml, sizeof(Manga_list))){
        cout<<"\n------------------------------------------------------------------\n\n";
        cout<<"\tManga name ................. "<<ml.manga_name<<endl;
        cout<<"\tManga completed: ........... "<<ml.finished<<endl;
        if(ml.finished == 'n')
            cout<<"\tRecent manga chapter read .. "<<ml.recent_chap_read<<endl;
    }
return 0;
}

int delete_manga(){
    char to_be_deleted[100], temp[100];
    flag = 0;

    cout<<"\n Enter the name of the manga to be deleted: ";
    #ifndef _WIN32
        cin.ignore();
    #endif
    cin.getline(to_be_deleted, 100);

        while(fi.read((char*)&ml, sizeof(Manga_list))){
            
            strcpy(temp, ml.manga_name);
            #ifdef _WIN32
                if(strcmpi(strip(temp), strip(to_be_deleted)) == 0){
                    flag = 1;
                }
            #else
                if(strcasecmp(strip(temp), strip(to_be_deleted)) == 0){
                    flag = 1;
                }
            #endif
                else{ 
                    fo.open("delete.dat", ios::out | ios::binary | ios::app);
                    fo.write((char*)&ml, sizeof(Manga_list));
                    fo.close();
                }
        }
return 0;
}

int search_display_manga(){
    cout<<"\n------------------------------------------------------------------\n\n";
    cout<<"\tManga name ................. "<<ml.manga_name<<endl;
    cout<<"\tManga completed: ........... "<<ml.finished<<endl;
    if(ml.finished == 'n')
        cout<<"\tRecent manga chapter read .. "<<ml.recent_chap_read<<endl;
return 0;
}

// watch list user defined functions

int add_watchlist_anime(){
    char watchlist_anime[100];

    cout<<"\n Anime name: ";
    #ifndef _WIN32
        cin.ignore();
    #endif
    cin.getline(watchlist_anime, 100);
    
    if(watchlist_anime_check(watchlist_anime) == 1)
        return 1;

    strcpy(wl.anime_to_watch, watchlist_anime);
return 0;
}

int add_readlist_manga(){
    char watchlist_manga[100];

    cout<<"\n Manga name: ";
    #ifndef _WIN32
        cin.ignore();
    #endif
    cin.getline(watchlist_manga, 100);
    
    if(watchlist_manga_check(watchlist_manga) == 1)
        return 1;

    strcpy(wl.manga_to_read, watchlist_manga);
return 0;
}

int update_watchlist_anime(){
        char updated_watchlist_anime[100];

        cout<<" Enter new anime name: ";
        #ifndef _WIN32
            cin.ignore();
        #endif                                                                            
        cin.getline(updated_watchlist_anime, 100);
        strcpy(wl.anime_to_watch, updated_watchlist_anime);

return 0;
}

int update_readlist_manga(){
    char updated_readlist_manga[100];

    cout<<" Enter new manga name: ";
    #ifndef _WIN32
        cin.ignore();
    #endif
    cin.getline(updated_readlist_manga, 100);
    strcpy(wl.manga_to_read, updated_readlist_manga);
return 0;
}


int display_watchlist_anime(){
    int i = 1;
    cout<<"\n------------------------------------------------------------------\n\n";
    while(fi.read((char*)&wl, sizeof(Watch_list))){
        cout<<"\t"<<i<<") "<<wl.anime_to_watch<<endl;
        i += 1;
    }
return 0;
}

int display_readlist_manga(){
    int i = 1;
    cout<<"\n------------------------------------------------------------------\n\n";
    while(fi.read((char*)&wl, sizeof(Watch_list))){
        cout<<"\t"<<i<<") "<<wl.manga_to_read<<endl;
        i += 1;
    }
return 0;
}


// miscellaneous functions

// error text
void error(string error){
    cout<<"\n==> ERROR: " + error<<endl;
}

// success text
void success(string success){
    cout<<"\n==> SUCCESS: " + success<<endl;
}

// removes all the spaces in a sentence
char* strip(char *name){
    int i=0, chk, j;
    
    while(name[i]!='\0'){
        chk=0;
        if(name[i]==' '){
            for(j=i; name[j-1]!='\0'; j++)
                name[j] = name[j+1];
            chk = 1;
        }
        if(chk==0)
            i++;
    }
return name;
}

// checks if the anime passed in the argument and the matching original anime is the same case insensitively
int anime_check(char *Aname){
    cout<<"\n Checking database for duplicates...";
    char temp1[100], temp2[100];
    
    fi.open("anime.dat", ios::in | ios::binary);
    while(fi.read((char*)&al, sizeof(Anime_list))){

        strcpy(temp1, al.anime_name);
        strcpy(temp2, Aname);
        #ifdef _WIN32
            if(strcmpi(strip(temp1), strip(temp2)) == 0){
                cout<<endl;
                error("Anime already exists");
                fi.close();
                return 1;
            }
        #else
            if(strcasecmp(strip(temp1), strip(temp2)) == 0){
                cout<<endl;
                error("Anime already exists");
                fi.close();
                return 1;
            }
        #endif
    }
    cout<<"\n No duplicates found\n";
    fi.close();
return 0;
}

// checks if the manga passed in the argument and the matching original manga is the same case insensitively
int manga_check(char *Mname){
    cout<<"\n Checking database for duplicates...";
    char temp1[100], temp2[100];
    
    fi.open("manga.dat", ios::in | ios::binary);
    while(fi.read((char*)&ml, sizeof(Manga_list))){

        strcpy(temp1, ml.manga_name);
        strcpy(temp2, Mname);
        #ifdef _WIN32
            if(strcmpi(strip(temp1), strip(temp2)) == 0){
                cout<<endl;
                error("Manga already exists");
                fi.close();
                return 1;
            }
        #else
            if(strcasecmp(strip(temp1), strip(temp2)) == 0){
                cout<<endl;
                error("Manga already exists");
                fi.close();
                return 1;
            }
        #endif
    }
    cout<<"\n No duplicates found\n";
    fi.close();
return 0;
}

// checks if the anime passed in the argument and the matching original anime is the same case insensitively
int watchlist_anime_check(char *WAname){
    cout<<"\n Checking database for duplicates...";
    char temp1[100], temp2[100];
    
    fi.open("anime_watchlist.dat", ios::in | ios::binary);
    while(fi.read((char*)&wl, sizeof(Watch_list))){

        strcpy(temp1, wl.anime_to_watch);
        strcpy(temp2, WAname);
        #ifdef _WIN32
            if(strcmpi(strip(temp1), strip(temp2)) == 0){
                cout<<endl;
                error("Anime already exists");
                fi.close();
                return 1;
            }
        #else
            if(strcasecmp(strip(temp1), strip(temp2)) == 0){
                cout<<endl;
                error("Anime already exists");
                fi.close();
                return 1;
            }
        #endif
    }
    cout<<"\n No duplicates found\n";
    fi.close();
return 0;
}

// checks if the manga passed in the argument and the matching original manga is the same case insensitively
int watchlist_manga_check(char *WMname){
    cout<<"\n Checking database for duplicates...";
    char temp1[100], temp2[100];
    
    fi.open("manga_watchlist.dat", ios::in | ios::binary);
    while(fi.read((char*)&wl, sizeof(Watch_list))){

        strcpy(temp1, wl.manga_to_read);
        strcpy(temp2, WMname);
        #ifdef _WIN32
            if(strcmpi(strip(temp1), strip(temp2)) == 0){
                cout<<endl;
                error("Manga already exists");
                fi.close();
                return 1;
            }
        #else
            if(strcasecmp(strip(temp1), strip(temp2)) == 0){
                cout<<endl;
                error("Manga already exists");
                fi.close();
                return 1;
            }
        #endif
    }
    cout<<"\n No duplicates found\n";
    fi.close();
return 0;
}