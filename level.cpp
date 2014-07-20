#include "level.h"
#include <TmxParser/Tmx.h>
#include <tinyxml.h>
#include <Box2D/Box2D.h>
#include "ResInit.h"

using namespace std;

Level::Level() {
	this->renderer = NULL;
}

Level::Level(SDL_Renderer* renderer, Camera* camera) {
	this->renderer = renderer;
    this->camera = camera;

    for(int i = 0; i < 5; i++) {
        sprites[i] = Sprite(renderer);
    }

    sprites[0].setTexture(space_tex);
    sprites[1].setTexture(wall_tex);
    sprites[2].setTexture(space_tex);
    sprites[4].setTexture(spike_tex);
}

void Level::clear() {
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++) {
           map[x][y] = 0;
        }   
    }
}

bool Level::loadFromFile(std::string _name) {
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

    cout << width << " " << height << endl;

    map = new int*[width];
    for(int i = 0; i < width; i++) {
    	map[i] = new int[height];
    }
    // // Работа со слоями
    TiXmlElement *layerElement;
    layerElement = tileMap->FirstChildElement("layer");
    while(layerElement)
    {

        // Контейнер <data>
        TiXmlElement *layerDataElement;
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
            switch(tileGID){
                case 4: {
                    map[x][y] = 1;
                } break;
                case 1: {
                    map[x][y] = 2;
                } break;
                case 3: {
                    map[x][y] = 0;
                } break;
                case 2: {
                    map[x][y] = 3;
                } break;
                case 5: {
                    map[x][y] = 4;
                } break;
                case 7: {
                    map[x][y] = 5;
                } break;
                case 9: {
                    map[x][y] = 6;
                }break;
                case 10: {
                    map[x][y] = 7;
                }break;
                case 11: {
                    map[x][y] = 8;
                }break;
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

int** Level::getMap() {
    return map;
}

b2Vec2 Level::getMapSize() {
    return b2Vec2(width, height);
}

void Level::draw() {
    for(int y = 0; y < height; y++){
        for(int x = 0; x < width; x++) {
            int id = map[x][y];

            if(id == 5 || id == 6 || id == 7 || id == 8)
                id = 0;

            if(id == 4)
                sprites[0].draw((x * 32) - camera->x, (y * 32) - camera->y);

            sprites[id].draw((x * 32) - camera->x, (y * 32) - camera->y);
        }
    }
}