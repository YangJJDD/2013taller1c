#include <view/MapView.h>

#define TilesScale     		1
#define TilesVisibleMargin	3

using namespace std;

MapView::MapView(MapData* inputData, SDL_Surface* inputScreen, EntityViewMap* map) {
	screen = inputScreen;
	data = inputData;
	viewMap = map;
	Position* cameraPos = new Position(screen->w / 2, screen->h / 2);
	camera = new MapCameraView( cameraPos, screen , data->GetNRows() , data->GetNCols());
	entitiesView = NULL;
	personaje = NULL;

	textureHolder = NULL;
	timer.start();
}

MapView::~MapView() {
}

void MapView::SetUpPersonajes() {
	// Setea la posicion por unica vez de los personajes (y en un futuro posiblemente
	// lo representable) en el mapa.
	SDL_Rect posTile;

	for (int col = 0; col < data->GetNCols(); col++) {
		for (int row = 0; row < data->GetNRows(); row++) {

			Player* personaje = data->GetPersonaje(row, col);
			if (personaje != NULL) {

				posTile = Tile::computePosition(row, col, true);
				personaje->setPos((float) posTile.x, (float) posTile.y);
			}
		}
	}
}

//TODO - este metodo iria en cfg reader
void MapView::SetUpEntity(EntityView* entityView,Coordinates coor)
{
	this->viewMap->positionEntityView(entityView,coor);
}


void MapView::movePlayer(int x, int y) {

	//dami comenta: la vista del mapa mueve al personaje???
	// Selecciona la casilla mas o menos bien, idealizandola como un cuadrado.
	// TODO: Que seleccione la casilla bien!

	Position* cameraPos = this->camera->getPosition();

	Coordinates* coor = Tile::getTileCoordinates(	x - cameraPos->getX(),
													y - cameraPos->getY());

	if( !(coor->getCol() <= 0 || coor->getRow() < 0) &&
		!(coor->getCol() > data->GetNCols() || coor->getRow() > data->GetNRows())) {
		SDL_Rect firstTile = Tile::computePosition(0, 0);
		firstTile.x = cameraPos->getX() + firstTile.x;
		firstTile.y = cameraPos->getY() + firstTile.y;

		if (personaje != NULL) {
			// TODO: esto no pierde memoria a lo loco?
			 Tile* toTile = new Tile(new Coordinates(coor->getRow(), coor->getCol()));
			 data->movePersonaje(personaje, toTile);
		}
	}

	delete coor;
	delete cameraPos;
}

void MapView::AssignPersonaje(Player* _personaje) {
	personaje = _personaje;
}

void MapView::Update() {

}

MapCameraView* MapView::getCamera(){
	return camera;
}

SDL_Surface* MapView::getDrawingSurface() {
	return screen;
}

map<string, int> MapView::getVisibleTilesLimit(Position* cam) {
// TODO: Esto en vez de devolver un diccionario capas q estaria bueno q devuelva una clase, q dicen?

	// Obtiene las casillas de los extremos de la pantalla
	Coordinates *supLeft = Tile::getTileCoordinates( -cam->getX(), -cam->getY());
	Coordinates *supRight = Tile::getTileCoordinates( screen->w - cam->getX(), - cam->getY());
	Coordinates *infLeft = Tile::getTileCoordinates( -cam->getX(), screen->h - cam->getY());
	Coordinates *infRight = Tile::getTileCoordinates( screen->w - cam->getX(), screen->h - cam->getY());


	if (supLeft->getCol() < 0) supLeft->setCol(0);
	if (supRight->getRow() < 0) supRight->setRow(0);
	if (infLeft->getRow() > data->GetNRows()) infLeft->setRow(data->GetNRows());
	if (infRight->getCol() > data->GetNCols()) infRight->setCol(data->GetNCols());

	// Se agregan los tiles de margen
	if (supLeft->getCol() <= TilesVisibleMargin)
		supLeft->setCol( 0 );
	else
		supLeft->setCol(supLeft->getCol() - TilesVisibleMargin);

	if (supRight->getRow() <= TilesVisibleMargin)
		supRight->setRow( 0 );
	else
		supRight->setRow(supRight->getRow() - TilesVisibleMargin);


	if (infRight->getCol() >= data->GetNCols() - TilesVisibleMargin)
		infRight->setCol( data->GetNCols() );
	else
		infRight->setCol(infRight->getCol() + TilesVisibleMargin);

	if (infLeft->getRow() >= data->GetNRows() - TilesVisibleMargin)
		infLeft->setRow( data->GetNRows() );
	else
		infLeft->setRow(infLeft->getRow() + TilesVisibleMargin);


	std::map<std::string, int> mapVisibleLimits;
	mapVisibleLimits["StartCol"] = supLeft->getCol();
	mapVisibleLimits["EndCol"] = infRight->getCol();
	mapVisibleLimits["StartRow"] = supRight->getRow();
	mapVisibleLimits["EndRow"] = infLeft->getRow();

	return mapVisibleLimits;
}

void MapView::draw(Position* cam) {
	//Personaje* personajes = NULL;
	SDL_Rect posTile;


	/*
	 * Dibujamos los tiles
	 * TODO: agregar un metodo getEntities(row,col) a entityviewmap para dibujar toodo en el mismo for!
	 */

	map<string, int> mapVisibleLimits = getVisibleTilesLimit(cam);

	for (int col = mapVisibleLimits["StartCol"]; col < mapVisibleLimits["EndCol"]; col++) {

		for (int row = mapVisibleLimits["StartRow"]; row < mapVisibleLimits["EndRow"]; row++) {

			posTile = Tile::computePosition(row, col);
			Position* cameraPos = this->camera->getPosition();
			posTile.x = cameraPos->getX() + posTile.x;
			posTile.y = cameraPos->getY() + posTile.y;
			delete cameraPos;

			std::string textureId = data->GetTileType(row, col);
			SDL_Surface* textureImage = textureHolder->getTexture(textureId);

			SDL_BlitSurface(textureImage, NULL, screen, &posTile);

		}

	}

	viewMap->drawViews(screen,cam);
	if (timer.getTimeSinceLastAnimation()>= 2*timer.getDelay()) timer.start();
	// Luego se blitean todos los personajes despues de haber bliteado el piso
	// para que el piso no tape a los flacos.
	/*  if (personajes != NULL){
	 PersonajeVista* personajeVista =
	 new PersonajeVista(personajes, "resources/foo.png", screen);

	 personajeVista->UpdateCameraPos(cameraX, cameraY);
	 personajeVista->Mostrar();
	 }*/
}

TextureHolder* MapView::getTextureHolder() {
	return this->textureHolder;
}

void MapView::setTextureHolder(TextureHolder* textureHolder) {
	this->textureHolder = textureHolder;
}

