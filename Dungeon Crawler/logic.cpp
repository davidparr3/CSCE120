#include <iostream>
#include <fstream>
#include <string>
#include "logic.h"

using std::cout, std::endl, std::ifstream, std::string;

/**
 * TODO: Student implement this function
 * Load representation of the dungeon level from file into the 2D map.
 * Calls createMap to allocate the 2D array.
 * @param   fileName    File name of dungeon level.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference to set starting position.
 * @return  pointer to 2D dynamic array representation of dungeon map with player's location., or nullptr if loading fails for any reason
 * @updates  maxRow, maxCol, player
 */
char** loadLevel(const string& fileName, int& maxRow, int& maxCol, Player& player) {
    //open file
    ifstream level(fileName); 
    if(!level.is_open()){
        return nullptr;
    }
    //

    //read rows, cols, and starting position
    if(!(level >> maxRow) || !(level >> maxCol) || !(level >> player.row)
        || !(level >> player.col) || (maxCol <= 0) || (maxRow <= 0) 
        || (maxCol > 999999) || (maxRow > 999999) || (player.row < 0) 
        || (player.col < 0) || (player.row >= maxRow)
        || (player.col >= maxCol) || ((maxCol * maxRow) > 2147483647)){
       return nullptr;
    }
    //create map as 2d array
    char** map = createMap(maxRow, maxCol);
    if (map == nullptr) {
        return nullptr; 
    }
    //read map from file
    for(int y = 0; y < maxRow; y++){
        for(int x = 0; x < maxCol; x++){
            if(!(level >> map[y][x]) || (map[y] == nullptr) || ((map[y][x] != TILE_OPEN) && (map[y][x] != TILE_TREASURE)
                && (map[y][x] != TILE_AMULET) && (map[y][x] != TILE_MONSTER) && (map[y][x] != TILE_PILLAR)
                && (map[y][x] != TILE_DOOR) && (map[y][x] != TILE_EXIT))){
                return nullptr;
            }
        }
    }
    //check end of file
    char over;
    level >> over;
    if(!level.eof()){
        return nullptr;
    }
    //check for door
    bool door = false;
    for(int y = 0; y < maxRow; y++){
        for(int x = 0; x < maxCol; x++){
            if((map[y][x] == TILE_DOOR) || (map[y][x] == TILE_EXIT)){
                door = true;
                break;
            }
        }
    }
    if(door == false){
        return nullptr;
    }
    //validate and appendplayer postition
    if(map[player.row][player.col] != TILE_OPEN){
        return nullptr;
    }
    map[player.row][player.col] = TILE_PLAYER;

    level.close(); 
    return map;
}

/**
 * TODO: Student implement this function
 * Translate the character direction input by the user into row or column change.
 * That is, updates the nextRow or nextCol according to the player's movement direction.
 * @param   input       Character input by the user which translates to a direction.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @updates  nextRow, nextCol
 */
void getDirection(char input, int& nextRow, int& nextCol) {
    //move up
    if(input == 'w'){
        nextRow--;
    }
    //move down
    if(input == 's'){
        nextRow++;
    }
    //move left
    if(input == 'a'){
        nextCol--;
    }
    //move right
    if(input == 'd'){
        nextCol++;
    }
}

/**
 * TODO: [suggested] Student implement this function
 * Allocate the 2D map array.
 * Initialize each cell to TILE_OPEN.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @return  2D map array for the dungeon level, holds char type.
 */
char** createMap(int maxRow, int maxCol) {
    //allocate first dimension
    char** mapArray = new char*[maxRow];
    //allocate second dimension
    for(int y = 0; y < maxRow; y++){
        mapArray[y] = new char[maxCol];
        //set elements to open
        for(int x = 0; x < maxCol; x++){
            mapArray[y][x] = TILE_OPEN;
        }
    }

    return mapArray;
}

/**
 * TODO: Student implement this function
 * Deallocates the 2D map array.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @return None
 * @update map, maxRow
 */
void deleteMap(char**& map, int& maxRow) {
    //check if map null
    if((map != nullptr) && (maxRow != 0)){
        //dealocate memory for rows
        for(int y = 0; y < maxRow; y++){
            if(!(map[y] == nullptr)){
                delete[] map[y];
            }
        }   
    }
    //clear map off heap
    delete[] map;
    map = nullptr;
    maxRow = 0;
}

/**
 * TODO: Student implement this function
 * Resize the 2D map by doubling both dimensions.
 * Copy the current map contents to the right, diagonal down, and below.
 * Do not duplicate the player, and remember to avoid memory leaks!
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height), to be doubled.
 * @param   maxCol      Number of columns in the dungeon table (aka width), to be doubled.
 * @return  pointer to a dynamically-allocated 2D array (map) that has twice as many columns and rows in size.
 * @update maxRow, maxCol
 */
char** resizeMap(char** map, int& maxRow, int& maxCol) {
    if((map == nullptr) || (maxRow == 0) || (maxCol == 0)){
        return nullptr;
    }
    // save originally vals
    int origmaxRow = maxRow;
    int origmaxCol = maxCol;
    //double vals
    maxRow = maxRow * 2;
    maxCol = maxCol * 2;
    //create new map
    char** map2 = createMap(maxRow, maxCol);
    //append old map top left
    for(int y = 0; y < origmaxRow; y++){
        for(int x = 0; x < origmaxCol; x++){
            map2[y][x] = map[y][x];
        }
    }
    //prevent player dup
    for(int y = 0; y < origmaxRow; y++){
        for(int x = 0; x < origmaxCol; x++){
            if(map[y][x] == TILE_PLAYER){
                map[y][x] = TILE_OPEN;
            }
            //append old map top right
            map2[y][x + origmaxCol] = map[y][x];
            //append old map bottom left
            map2[y + origmaxRow][x] = map[y][x];
            //append old map bottom right
            map2[y + origmaxRow][x + origmaxCol] = map[y][x];
        }
    }
    //deallocate memory
    deleteMap(map, origmaxRow);
    return map2;
}

/**
 * TODO: Student implement this function
 * Checks if the player can move in the specified direction and performs the move if so.
 * Cannot move out of bounds or onto TILE_PILLAR or TILE_MONSTER.
 * Cannot move onto TILE_EXIT without at least one treasure. 
 * If TILE_TREASURE, increment treasure by 1.
 * Remember to update the map tile that the player moves onto and return the appropriate status.
 * You can use the STATUS constants defined in logic.h to help!
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object to by reference to see current location.
 * @param   nextRow     Player's next row on the dungeon map (up/down).
 * @param   nextCol     Player's next column on dungeon map (left/right).
 * @return  Player's movement status after updating player's position.
 * @update map contents, player
 */
int doPlayerMove(char** map, int maxRow, int maxCol, Player& player, int nextRow, int nextCol){
    //set bool vals for possibilities
    bool movement = 0, escape = 0, leave = 0, treasure = 0, amulet = 0;
    //checks if move is valid
    if((nextRow < 0) || (nextCol < 0) || (nextRow >= maxRow) || (nextCol >= maxCol) 
    || (map[nextRow][nextCol] == TILE_PILLAR) || (map[nextRow][nextCol] == TILE_MONSTER)){
        return STATUS_STAY;
    }
    //treasure
    if(map[nextRow][nextCol] == TILE_TREASURE){
        player.treasure++;
        movement = true;
        treasure = true;
    }
    //amulet
    if(map[nextRow][nextCol] == TILE_AMULET){
        amulet = true;
        movement = true;
    }
    //leave room
    if(map[nextRow][nextCol] == TILE_DOOR){
        leave = true;
        movement = true;
    }
    //escape
    if(map[nextRow][nextCol] == TILE_EXIT){
        if(player.treasure > 0){
            escape = true;
            movement = true;
        }
        else{
            return STATUS_STAY;
        }
    }
    //normal movement
    if(map[nextRow][nextCol] == TILE_OPEN){
        movement = true;
    }
    //update map for movement
    if(movement){
        map[player.row][player.col] = TILE_OPEN;
        player.row = nextRow;
        player.col = nextCol;
        map[nextRow][nextCol] = TILE_PLAYER;
    }
    //return status
    if(amulet){
        return STATUS_AMULET;
    }
    if(escape){
        return STATUS_ESCAPE;
    }
    if(leave){
        return STATUS_LEAVE;
    }
    if(treasure){
        return STATUS_TREASURE;
    }
    return STATUS_MOVE;
}

/**
 * TODO: Student implement this function
 * Update monster locations:
 * We check up, down, left, right from the current player position.
 * If we see an obstacle, there is no line of sight in that direction, and the monster does not move.
 * If we see a monster before an obstacle, the monster moves one tile toward the player.
 * We should update the map as the monster moves.
 * At the end, we check if a monster has moved onto the player's tile.
 * @param   map         Dungeon map.
 * @param   maxRow      Number of rows in the dungeon table (aka height).
 * @param   maxCol      Number of columns in the dungeon table (aka width).
 * @param   player      Player object by reference for current location.
 * @return  Boolean value indicating player status: true if monster reaches the player, false if not.
 * @update map contents
 */
bool doMonsterAttack(char** map, int maxRow, int maxCol, const Player& player) {
    //define bool vals
    bool dead = 0;
    //create new map for multiple monsters
    char** monsterMap = createMap(maxRow, maxCol);
     for (int y = 0; y < maxRow; ++y) {
        for (int x = 0; x < maxCol; ++x) {
            monsterMap[y][x] = map[y][x];
        }
    }

    //check up
    for(int y = player.row; y >= 0; y--){
        //move monstor up
        if(map[y][player.col] == TILE_MONSTER){
            monsterMap[y][player.col] = TILE_OPEN;
            monsterMap[y + 1][player.col] = TILE_MONSTER;
            
        }
        //check pillar
        if(map[y][player.col] == TILE_PILLAR){
            break;
        }
    }
    //check down
    for(int y = player.row; y < maxRow; y++){
        //move monstor down
        if(map[y][player.col] == TILE_MONSTER){
            monsterMap[y][player.col] = TILE_OPEN;
            monsterMap[y - 1][player.col] = TILE_MONSTER;
            
        }
        //check pillar
        if(map[y][player.col] == TILE_PILLAR){
            break;
        }
    }
    //check left
    for(int x = player.col; x >= 0; x--){
        //move monstor left
        if(map[player.row][x] == TILE_MONSTER){
            monsterMap[player.row][x] = TILE_OPEN;
            monsterMap[player.row][x + 1] = TILE_MONSTER;
            
        }
        //check pillar
        if(map[player.row][x] == TILE_PILLAR){
            break;
        }
    }
    //check right
    for(int x = player.col; x < maxCol; x++){
        //move monstor down
        if(map[player.row][x] == TILE_MONSTER){
            monsterMap[player.row][x] = TILE_OPEN;
            monsterMap[player.row][x - 1] = TILE_MONSTER;
            
        }
        //check pillar
        if(map[player.row][x] == TILE_PILLAR){
            break;
        }
    }
    //update map
    for (int y = 0; y < maxRow; ++y) {
        for (int x = 0; x < maxCol; ++x) {
            map[y][x] = monsterMap[y][x];
        }
    }
    //check if player dead
    if(map[player.row][player.col] == TILE_MONSTER){
        dead = true;
    }
    deleteMap(monsterMap, maxRow);
    return dead;
}
