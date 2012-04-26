#include "Map.h"

Map Map::Instance;

Map::Map() {}

void Map::Init() {

    Surface = SDL_CreateRGBSurface(SDL_HWSURFACE, MAP_WIDTH*BLOCK_SIZE, MAP_HEIGHT*BLOCK_SIZE, 32, 0, 0, 0, 0);

    Tiles.resize(MAP_WIDTH);
    for (int i = 0; i < MAP_WIDTH; i++) {
        Tiles[i].resize(MAP_HEIGHT);
    }

    for (int i = 0; i < MAP_WIDTH; i++) {
        for(int j = 0; j < MAP_HEIGHT; j++) {
            Tiles[i][j] = NULL;

            // Borders
            if (i == 0 || j == 0 || j == MAP_HEIGHT-1 || i == MAP_WIDTH-1) {
                Tiles[i][j] = new Tile(TILE_TYPE_WALL);
                continue;
            }

            // Pillars
            if (i%2 == 0 && j%2 == 0) {
                Tiles[i][j] = new Tile(TILE_TYPE_WALL);
                continue;
            }

            //Random bricks
            if (rand()%10 == 1) {
                Tiles[i][j] = new Tile(TILE_TYPE_BRICK);
            }
        }
    }

    Tiles[1][1] = NULL;
}

bool Map::Load(const char* File) {

    SDL_Surface* TileMap = NULL;

    if ((TileMap = Sprite::Load(File)) == NULL) {
        return false;
    }

    Sprite::Transparent(TileMap, 255, 0, 255);

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (Tiles[i][j] != NULL) {
                Sprite::Draw(Surface, TileMap, i*BLOCK_SIZE, j*BLOCK_SIZE, Tiles[i][j]->Type*BLOCK_SIZE, 0, BLOCK_SIZE, BLOCK_SIZE);
            }
        }
    }

    SDL_FreeSurface(TileMap);

    return true;
}

void Map::Render(SDL_Surface* Screen, int OffsetX, int OffsetY) {
    if (Surface == NULL || Screen == NULL) return;
    Sprite::Draw(Screen, Surface, OffsetX, OffsetY);
}

void Map::Cleanup() {
    SDL_FreeSurface(Surface);
}

void Map::GetFreeSpace(float* X, float* Y) {

    std::vector< std::vector<int> > Coords;

    for (int i = 0; i < MAP_WIDTH; i++) {
        for (int j = 0; j < MAP_HEIGHT; j++) {
            if (Tiles[i][j] == NULL) {
                std::vector<int> xy;
                xy.push_back(i);
                xy.push_back(j);
                Coords.push_back(xy);
            }
        }
    }

    int random = rand()%Coords.size();
    *X = Coords[random][0];
    *Y = Coords[random][1];
}
