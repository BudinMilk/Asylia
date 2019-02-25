/*
 * =====================================================================================
 *
 *       Filename:  TilemapLoader.cpp
 *
 *    Description:
 *
 *        Created:  25/02/2019 23:13:11
 *
 *         Author:  Quentin Bazin, <quent42340@gmail.com>
 *
 * =====================================================================================
 */
#include <gk/core/XMLFile.hpp>
#include <gk/graphics/Tilemap.hpp>
#include <gk/resource/ResourceHandler.hpp>

#include "TilemapLoader.hpp"

void TilemapLoader::load(const char *xmlFilename, gk::ResourceHandler &handler) {
	gk::XMLFile doc(xmlFilename);

	tinyxml2::XMLElement *tilemapElement = doc.FirstChildElement("tilemaps").FirstChildElement("tilemap").ToElement();
	while (tilemapElement) {
		std::string name = tilemapElement->Attribute("name");
		std::string tileset = tilemapElement->Attribute("tileset");
		// std::string battleback = tilemapElement->Attribute("battleback");

		loadMap(name, tileset, handler);

		tilemapElement = tilemapElement->NextSiblingElement("tilemap");
	}
}

void TilemapLoader::loadMap(const std::string &name, const std::string &tilesetName, gk::ResourceHandler &handler) {
	gk::XMLFile doc("resources/maps/" + name + ".tmx");

	tinyxml2::XMLElement *mapElement = doc.FirstChildElement("map").ToElement();

	u16 width = mapElement->IntAttribute("width");
	u16 height = mapElement->IntAttribute("height");

	std::vector<std::vector<u16>> data;
	tinyxml2::XMLElement *layerElement = mapElement->FirstChildElement("layer");
	while (layerElement) {
		tinyxml2::XMLElement *tileElement = layerElement->FirstChildElement("data")->FirstChildElement("tile");

		std::vector<u16> layer;
		while(tileElement) {
			u16 tileID = tileElement->IntAttribute("gid", 0);

			layer.emplace_back(tileID);

			tileElement = tileElement->NextSiblingElement("tile");
		}

		data.emplace_back(std::move(layer));

		layerElement = layerElement->NextSiblingElement("layer");
	}

	gk::Tileset &tileset = handler.get<gk::Tileset>(tilesetName);
	gk::Tilemap &map = handler.add<gk::Tilemap>(name, width, height, tileset, data);
	map.setTilesetOffset(1);
	map.updateTiles();
}

