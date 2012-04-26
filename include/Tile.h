#ifndef TILE_H
#define TILE_H

enum {
    TILE_TYPE_WALL = 0,
    TILE_TYPE_BRICK = 1,
    TILE_TYPE_DOOR = 2
};

class Tile {

    public:
        int Type;

    public:
        Tile(int Type);

};

#endif // TILE_H
