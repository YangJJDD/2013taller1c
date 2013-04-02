#ifndef MAPDATA_H
#define	MAPDATA_H

#include <stdio.h>
#include <stdlib.h>
#include <model/entities/Entity.h>
#include <model/entities/personaje/Personaje.h>
#include <model/map/Tile.h>
#include <list>


#define MAX_TILE_CONTENT	5

using namespace std;

struct TileData{
	//Lucas: TODO : ESTO NO ES OO AMIGO!!
	int tileType;
	Personaje* personaje;
	Entity *content[MAX_TILE_CONTENT];
	int contentAmount;
};

class MapData {
public:
	//Lucas: TODO : por que no defines?
    static const int NEUTRAL = 0;
    static const int SOIL = 1;
    static const int WATER = 2;
    static const int TREE = 3;
    static const int AMOUNT_TYPES = 4;  // Igual al mayor +1 index de consts

    MapData(int _nrows, int _ncols);
    virtual ~MapData();
    
    void addRepresentable(int row, int col, Entity *object);
    void SetTileType(int tileType, int row, int col);
    int GetTileType(int row, int col);
    int GetNRows();
    int GetNCols();
    TileData * GetTileData(int row, int col);
    void addPersonaje(int row, int col, Personaje* personaje);
    Personaje* GetPersonaje(int row, int col);
	list<Tile *> *GetPath(Tile* from, Tile* to);
private:
    TileData *data;
    int nrows;
    int ncols;

    void InitializeData();
    void CheckRowColsValue(int row, int col);
};

#endif	/* MAPDATA_H */
