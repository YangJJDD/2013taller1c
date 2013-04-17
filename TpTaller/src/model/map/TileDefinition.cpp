/*
 * TileDefinition.cpp
 *
 *  Created on: Apr 1, 2013
 *      Author: gonchub
 */

#include <model/map/TileDefinition.h>
#include <SDL/SDL.h>
#include <string>
#include <SDL/SDL_image.h>
#include <SDL/SDL_rotozoom.h>

#include <model/Logs/Logs.h>

#define TilesScale  	1

#define DEFAULT_TEXTURE_PATH "resources/texturesTiles/grass.png"

TileDefinition::TileDefinition() {
	this->id = "default";
	this->setDefaultTileImage(DEFAULT_TEXTURE_PATH);
	this->imageSrc = this->defaultImgSrc;
	this->openImage = NULL;
}

TileDefinition::TileDefinition(std::string id, std::string imageSrc) {
	this->id = id;
	this->imageSrc = imageSrc;
	this->setDefaultTileImage(DEFAULT_TEXTURE_PATH);
	this->openImage = NULL;
}

TileDefinition::~TileDefinition() {
	SDL_FreeSurface(openImage);
}

std::string TileDefinition::getTileId() {
	return this->id;
}

void TileDefinition::setTileId(std::string id) {
	this->id = id;
}

std::string TileDefinition::getTileImageSrc() {
	return this->imageSrc;
}

SDL_Surface* TileDefinition::getTileImage() {
	if (this->openImage == NULL) {
		SDL_Surface* loadedImageTmp = IMG_Load(this->imageSrc.c_str());
		if (loadedImageTmp == NULL) {
			Logs::logErrorMessage("Unable to load tile texture: " + string(SDL_GetError()));
			loadedImageTmp = this->getDefaultTileImage();
		}

		SDL_Surface* loadedImageRot = rotozoomSurfaceXY(loadedImageTmp, 0, TilesScale,
				TilesScale, 0);
		SDL_FreeSurface(loadedImageTmp);
		SDL_Surface* loadedImage = SDL_DisplayFormatAlpha(loadedImageRot);
		SDL_FreeSurface(loadedImageRot);
		this->openImage = loadedImage;
	}
	return this->openImage;
}

void TileDefinition::setTileImageSrc(std::string imageSrc) {
	this->imageSrc = imageSrc;
}

SDL_Surface* TileDefinition::prepareImage(SDL_Surface* loadedImage) {
	SDL_Surface* tmp = loadedImage;
	loadedImage = rotozoomSurfaceXY(tmp, 0, TilesScale, TilesScale, 0);
	SDL_FreeSurface(tmp);
	tmp = loadedImage;
	loadedImage = SDL_DisplayFormatAlpha(tmp);
	SDL_FreeSurface(tmp);
	return loadedImage;
}

SDL_Surface * TileDefinition::getDefaultTileImage() {
	SDL_Surface* loadedImage = IMG_Load(this->defaultImgSrc.c_str());
	if (loadedImage == NULL) {
		Logs::logErrorMessage("Unable to load default tile texture: " + string(SDL_GetError()));
		return NULL;
	}
	loadedImage = prepareImage(loadedImage);
	return loadedImage;
}

void TileDefinition::setDefaultTileImage(std::string imageSrc) {
	this->defaultImgSrc = imageSrc;
}
