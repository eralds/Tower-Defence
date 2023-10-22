#include "map.hpp"

Map::Map(std::string _path) {

    std::ifstream data(_path);

    int tileId;
    std::string line;

    for (int i = 0; i < MAPDIM; i++)
    {
        getline(data, line);
        for (int j = 0; j < MAPDIM; j++)
        {
            tileId = int(line.at(j*2) - '0'); // turn char into int
            if(tileId == 2){
                startPos = std::make_pair(i,j);
            } 
            tiles[i][j] = new Tile("assets/imgs/tiles/tile_" + std::string(1, line.at(j*2)) + ".png", static_cast<float>(HEIGHT/MAPDIM * j), static_cast<float>(HEIGHT/MAPDIM *i), (tileId >=1 && tileId <= 3)  ? true : false, (tileId == 3) ? true : false, (tileId == 4) ? true : false);
        }
    }
    data.close();
    std::cout << "Map generated" << std::endl;
    this->CreatePath();
}


void Map::Render(RenderWindow *window) {
    for (int i = 0; i < MAPDIM; i++)
    {
        for (int j = 0; j < MAPDIM; j++)
        {
            window->draw((*tiles[i][j]).GetSprite());
        }
    }
}


void Map::CreatePath() {
    std::vector<std::pair<int, int>> posLeft;
    posLeft.push_back(startPos);
    std::pair<int, int> curPos;
    bool seen[MAPDIM][MAPDIM] = {false}; 
    seen[startPos.first][startPos.second] = true;
    while(!posLeft.empty()) {
        // std::cout << "y: " << std::to_string(curPos.first) << " x: " << std::to_string(curPos.second)<< std::endl;
        curPos = posLeft.back();
        posLeft.pop_back();
        std::vector<std::pair<std::pair<int, int>,DIRECTION>> neighbours = Neighbours(curPos);
        if ((*GetTile(curPos)).IsEnd()) {
            pathMap[curPos.first*MAPDIM + curPos.second].push_back(std::make_pair(curPos.first*MAPDIM + curPos.second, UP));
        }
        for (auto i = neighbours.begin(); i!=neighbours.end(); i++) {
            int x = (*i).first.first;
            int y = (*i).first.second;
     
            if (!seen[x][y]) {
                // get the last neighbour that is not the same as the previous one
                // in case of branched path would need to use a map
                pathMap[curPos.first*MAPDIM + curPos.second].push_back(std::make_pair(x*MAPDIM+y, (*i).second));
                posLeft.push_back(std::make_pair(x,y));
                seen[x][y] = true;
                // curPos = (*i).first;
            }
        }
    }
    std::cout << "Path generated" << std::endl;
    // path.push_back(std::make_pair(curPos, UP));
}

Tile* Map::GetTile(std::pair<int, int> co) {
    return tiles[co.first][co.second];
}


std::vector<std::pair<std::pair<int, int>,DIRECTION>> Map::Neighbours(std::pair<int, int> co) {
    std::vector<std::pair<std::pair<int, int>,DIRECTION>> neighbours;
    if (co.first > 0) {
        if ((*GetTile(std::make_pair(co.first-1, co.second))).IsPath()) {
            neighbours.push_back(std::make_pair(std::make_pair(co.first-1, co.second), UP));
        }
    }
    if (co.second > 0) {
        if ((*GetTile(std::make_pair(co.first, co.second-1))).IsPath()) {
            neighbours.push_back(std::make_pair(std::make_pair(co.first, co.second-1), LEFT));
        }
    }
    if (co.first < MAPDIM - 1) {
        if ((*GetTile(std::make_pair(co.first+1, co.second))).IsPath()) {
            neighbours.push_back(std::make_pair(std::make_pair(co.first+1, co.second), DOWN));
        }
    }
    if (co.second < MAPDIM - 1) {
        if ((*GetTile(std::make_pair(co.first, co.second+1))).IsPath()) {
            neighbours.push_back(std::make_pair(std::make_pair(co.first, co.second+1),RIGHT));
        }
    }
    
    return neighbours;
}

void Map::Update() {

}
std::map<int ,std::vector<std::pair<int,DIRECTION>>>* Map::GetPath() {
    return &pathMap;
}

std::pair<int, int> Map::GetStartPos() {
    return startPos;
}
