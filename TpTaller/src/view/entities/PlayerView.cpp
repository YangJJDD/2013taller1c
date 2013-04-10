/* 
 * File:   PersonajeVista.cpp
 * Author: damian
 * 
 * Created on 23 de marzo de 2013, 12:25
 */

#include <view/entities/PlayerView.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_rotozoom.h>

#include <cmath>
#include <string>

//Posicion de los pies del personaje respecto de la base de la imagen
#define OFFSET_Y	15

#define RUTA_IMAGEN "resources/soldierSheet.png"
#define ANIMATION_CHANGE_DELAY 1

#define STANDING_ANIMATION_LOCATION_IN_IMAGE_FILE 16

//#define SCALE				0.2

void PlayerView::showFrame(SDL_Surface* source, SDL_Surface* screen,
		SDL_Rect* clip) {
	SDL_Rect offset;

	Vector2* position = miPersonaje->GetCurrentPos();
	float x = position->GetX();
	float y = position->GetY();
	offset.x = (int) x + cameraX - clip->w / 2;
	offset.y = (int) y + cameraY - clip->h + OFFSET_Y;
	offset.w = clip->w;
	offset.h = clip->h;

	SDL_BlitSurface(source, clip, screen, &offset);
}

void PlayerView::draw(SDL_Surface* screen, Position* cam) {
	UpdateCameraPos(cam->getX(), cam->getY());
	Mostrar(screen);
}

void PlayerView::UpdateCameraPos(int x, int y) {
	cameraX = x;
	cameraY = y;
}

PlayerView::PlayerView()
//Llamamos al constructor de la superclase
:
		EntityView() {
	cameraX = cameraY = 0;
	miPersonaje = NULL;
	marco = 0;
	animationChangeRate = 0;
	personajeImagen = NULL;
	imageHeight = 0;
	imageWidth = 0;
	numberOfClips = 0;
	movable = true;
	direction = STANDING;
	wasStanding = true;
	// try
	//{
	//this->fondo = fondo;
	/* }catch(ERROR e)
	 {
	 //TODO:cargo una imagen alternativa.
	 }*/
}

void PlayerView::setPersonaje(Player* personaje) {
	this->miPersonaje = personaje;
	Vector2* anchorPixel = new Vector2(clip.w / 2, OFFSET_Y);
	miPersonaje->getBase()->setAnchorPixel(anchorPixel);
}

Player* PlayerView::getPersonaje() {
	return this->miPersonaje;
}

void PlayerView::cargarImagen(std::string img) {
	//Load the sprite sheet
	if (img.compare("")) {
		//  throw new FaltaParametroException();
	}

	SDL_Surface* miPersonajeImagen = load_image(img);

	//If there was a problem in loading the sprite
	if (!miPersonajeImagen) {
		printf("NO SE HA ENCONTRADO LA IMAGEN DEL PERSONAJE\n");
		//return false;
		//TODO: cargo una alternativa
		miPersonajeImagen = load_image(RUTA_IMAGEN);
	}

	marco = 0;
	personajeImagen = miPersonajeImagen;
}

Player* PlayerView::getEntity() {
	return miPersonaje;
}

void PlayerView::setEntity(Entity* entity) {
	//TODO: Error check (si no es un personaje)
	Player* aux = (Player*) entity;
	miPersonaje = aux;
}

void PlayerView::showStandingAnimation(float direction,SDL_Surface* fondo){

	SDL_Rect clipToDraw;
	clipToDraw.x = imageWidth*currentClip*scaleWidth;;
	clipToDraw.y = imageHeight*STANDING_ANIMATION_LOCATION_IN_IMAGE_FILE;
	clipToDraw.w = imageWidth*scaleWidth;;
	clipToDraw.h = imageHeight*scaleHeight;


	showFrame(this->personajeImagen, fondo, &clipToDraw);

	timeSinceLastAnimation = timer.getTimeSinceLastAnimation();
	//TODO - deberia ser numberOfClips-1 pero parece q esta mal la imagen ?¿

	//Apply delay
	if (currentClip < (numberOfClips-2) && timeSinceLastAnimation >= delay * 1000) {
		//Apply FPS cap
		if (animationRateTimer.getTimeSinceLastAnimation() >= 1000 / fps) {
			currentClip++;
			animationRateTimer.start();
		}

	} else {
		if (timeSinceLastAnimation >= delay * 1000)
			timer.start();
		currentClip = 0;
	}


}

void PlayerView::Mostrar(SDL_Surface* fondo) {
	Vector2* movementDirection = this->miPersonaje->GetMovementDirection();
	float direction = movementDirection->GetAngle();

	const float step = M_PI * 1 / 8;

	if (step * 15 < direction || direction < step)			direction = RIGHT;
	else if (step < direction && direction < step * 3)		direction = DOWN_RIGHT;
	else if (step * 3 < direction && direction < step * 5)	direction = DOWN;
	else if (step * 5 < direction && direction < step * 7)	direction = DOWN_LEFT;
	else if (step * 7 < direction && direction < step * 9)	direction = LEFT;
	else if (step * 9 < direction && direction < step * 11)	direction = UP_LEFT;
	else if (step * 11 < direction && direction < step * 13)direction = UP;
	else if (step * 13 < direction && direction < step * 15)direction = UP_RIGHT;

	if (miPersonaje->isRunning()){
		if (direction == RIGHT) 	direction = RIGHT_RUN;
		if (direction == DOWN_RIGHT)direction = DOWN_RIGHT_RUN;
		if (direction == DOWN) 		direction = DOWN_RUN;
		if (direction == DOWN_LEFT) direction = DOWN_LEFT_RUN;
		if (direction == LEFT) 		direction = LEFT_RUN;
		if (direction == UP_LEFT) 	direction = UP_LEFT_RUN;
		if (direction == UP) 		direction = UP_RUN;
		if (direction == UP_RIGHT) 	direction = UP_RIGHT_RUN;
	}

	if (animationChangeRate == ANIMATION_CHANGE_DELAY) {
		this->marco++;
		animationChangeRate = 0;// Move to the next marco in the animation
	} else {
		animationChangeRate++;
	}

	if (!miPersonaje->IsMoving()){
		if (!wasStanding){
			timer.start();
			wasStanding = true;
		}
		showStandingAnimation(direction,fondo);
		return;
	}

	wasStanding = false;
	if (marco >= numberOfClips) marco = 0;    // Loop the animation

	SDL_Rect clipToDraw;
	clipToDraw.x = imageWidth*marco*scaleWidth;
	clipToDraw.y = imageHeight*direction;
	clipToDraw.w = imageWidth*scaleWidth;
	clipToDraw.h = imageHeight*scaleHeight;

	showFrame(this->personajeImagen, fondo, &clipToDraw);
}


PlayerView::~PlayerView() {
	//libera la memoria que pide para La imagen
	SDL_FreeSurface(this->personajeImagen);

	//Quita SDL
	SDL_Quit();
}

int PlayerView::getImageHeight() {
	return this->imageHeight;
}

void PlayerView::setImageHeight(int height) {
	this->imageHeight = height;
}

int PlayerView::getImageWidth() {
	return this->imageWidth;
}

void PlayerView::setImageWidth(int width) {
	this->imageWidth = width;
}

int PlayerView::getNClips() {
	return this->numberOfClips;
}

void PlayerView::setNClips(int clips) {
	this->numberOfClips = clips;
}
