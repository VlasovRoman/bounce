#include "level.h"
#include <TmxParser/Tmx.h>
#include <tinyxml.h>
#include <Box2D/Box2D.h>

using namespace std;

Level::Level() {
	this->painter = NULL;
}

Level::Level(Painter* painter) {
	this->painter = painter;
    map = NULL;
}

void Level::clear() {
    if(map != NULL) {
        for(int x = 0; x < width; x++){
            for(int y = 0; y < height; y++) {
               map[x][y].environment = TE_NONE;
               map[x][y].object = TO_NONE;
               map[x][y].modification = TM_NONE;
            }
        }
    }
}

bool Level::loadFromFile(std::string _name) {
    if(map != NULL) {
        for(int x = 0; x < width; x++){
            delete [] map[x];
        }
        delete [] map;
    }
    map = NULL;
    TiXmlDocument levelFile(_name.c_str());

    // Загружаем XML-карту
    if(!levelFile.LoadFile())
    {
        std::cout << "Loading level \"" << _name << "\" failed." << std::endl;
        return false;
    }

    // // Работаем с контейнером map
    TiXmlElement *tileMap;
    tileMap = levelFile.FirstChildElement("map");

    // // Пример карты: <map version="1.0" orientation="orthogonal"
    // // width="10" height="10" tilewidth="34" tileheight="34">
    width = atoi(tileMap->Attribute("width"));
    height = atoi(tileMap->Attribute("height"));
    tileWidth = atoi(tileMap->Attribute("tilewidth"));
    tileHeight = atoi(tileMap->Attribute("tileheight"));

    // cout << width << " " << height << endl;


    map = new Tile*[width];
    for(int i = 0; i < width; i++) {
    	map[i] = new Tile[height];
    }

    clear();
    // // Работа со слоями
    TiXmlElement *layerElement;
    layerElement = tileMap->FirstChildElement("layer");
    while(layerElement)
    {

        // Контейнер <data>
        TiXmlElement *layerDataElement;
        string  layerName = layerElement->Attribute("name");
        layerDataElement = layerElement->FirstChildElement("data");

        if(layerDataElement == NULL)
        {
            std::cout << "Bad map. No layer information found." << std::endl;
        }

        // Контейнер <tile> - описание тайлов каждого слоя
        TiXmlElement *tileElement;
        tileElement = layerDataElement->FirstChildElement("tile");

        if(tileElement == NULL)
        {
            std::cout << "Bad map. No tile information found." << std::endl;
            return false;
        }

        int x = 0;
        int y = 0;

        while(tileElement)
        {

            int tileGID = atoi(tileElement->Attribute("gid"));
            // int subRectToUse = tileGID - firstTileID;

            if(layerName == "environment") {
                map[x][y].environment = (TILE_ENVIRONMENT)tileGID;
            }
            if(layerName == "objects") {
                map[x][y].object = (TILE_OBJECT)tileGID;
            }
            if(layerName == "modifications") {
                map[x][y].modification = (TILE_MODIFICATION)tileGID;
            }

            tileElement = tileElement->NextSiblingElement("tile");

            x++;
            if (x >= width)
            {
                x = 0;
                y++;
                if(y >= height)
                    y = 0;
            }
        }

        layerElement = layerElement->NextSiblingElement("layer");
    }

    return true;

}

Tile** Level::getMap() {
    return map;
}

b2Vec2 Level::getMapSize() {
    return b2Vec2(width, height);
}

void Level::draw() {
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++) {
            Tile tile = map[x][y];
            
            if(tile.environment == TE_AIR) {
                painter->drawSpace(x * 32, y * 32);
            }
            if(tile.environment == TE_WATER) {
                painter->drawWater(x * 32, y * 32);
            }

            if(tile.object == TO_WALL_SOLID) {
                painter->drawWall(x * 32, y * 32, 0);
            }
            if(tile.object == TO_WALL_DOWN_RIGHT_EDGE) {
                painter->drawWall(x * 32, y * 32, 2);
            }
            if(tile.object == TO_WALL_DOWN_LEFT_EDGE) {
                painter->drawWall(x * 32, y * 32, 1);
            }
            if(tile.object == TO_WALL_UP_RIGHT_EDGE) {
                painter->drawWall(x * 32, y * 32, 4);
            }
            if(tile.object == TO_WALL_UP_LEFT_EDGE) {
                painter->drawWall(x * 32, y * 32, 3);
            }
            if(tile.object == TO_PUMP_INFLATOR) {
                painter->drawPump(x * 32, y * 32, true, map[x][y].modification);
            }
            if(tile.object == TO_PUMP_OUTPUT) {
                painter->drawPump(x * 32, y * 32, false, map[x][y].modification);
            }
            if(tile.object == TO_SPIKE) {
                painter->drawSpike(x * 32, y * 32, map[x][y].modification);
            }
            if(tile.object == TO_JUMP_WALL) {
                // cout << "rednerer" << endl;
                painter->drawJumpWall(x * 32, y * 32);
            }
            // painter->drawJumpWall(5 * 32, 5 * 32);
        }
    }
}