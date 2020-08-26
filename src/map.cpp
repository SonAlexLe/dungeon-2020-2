//map generation
//todo: version of generateMap() which returns a single square room
#include "map.hpp"


Map::Map(int difficulty, Player* p) : difficulty_(difficulty), p_(p) {
    // rooms_.push_back(new Room);
    map_init();
}

Room* Map::GetStartingRoom() {
    return rooms_.front();
}

//Runs when a map is constructed
void Map::map_init() {

    //Some preliminary parameters for how many rooms are generated
    int nofRooms = 5 + difficulty_;

    //Init layout and starting room
    Room* map[5][5] = { {nullptr} };
    Room* start = new Room();
    double size = start->GetHeight();
    map[2][2] = start;
    rooms_.push_back(start);

    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (map[i][j] == nullptr) { std::cout << "#"; } else { std::cout << "X"; } 
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;

    //Create a random seed
    srand(time(nullptr));

    while (nofRooms > 0) {

        //Pick a random cell in array
        int x = rand() % 5;
        int y = rand() % 5;

        // std::cout << "Accessing " << x << " " << y << std::endl;

        if(map[x][y] == nullptr) {
 
            // std::cout << "Found nullptr" << std::endl;

            //Where 1 is north, 2 is east, 3 is south, 4 is west
            std::list<int>neighbors;

            //Count how many neighbors the cell has
            if ( (x != 4) && map[x + 1][y] != nullptr) { neighbors.push_back(3);} // Check South
            if ( (x != 0) && map[x - 1][y] != nullptr) { neighbors.push_back(1);} // Check North

            if ( (y != 4) && map[x][y + 1] != nullptr) { neighbors.push_back(2);} // Check East
            if ( (y != 0) && map[x][y - 1] != nullptr) { neighbors.push_back(4);} // Check West

            /*std::cout << "Cell has: " << neighbors.size() << " neighbros ";
            if (!neighbors.empty()) {
                std::cout << "And they are: ";
                for (auto i : neighbors) {
                    std::cout << i << " ";
            }
            }
            std::cout << std::endl;
            */
            

            //The maximum amount of neighbors can be tweaked to change the layout of the maps
            if(neighbors.size() >= 1 && neighbors.size() < 3) {

                //All conditions are met, create a room
                Room* room = room_init();

                // Room* room = new Room;
                map[x][y] = room;
                rooms_.push_back(room);

                std::cout << "Room created @ " << x << " " << y  << std::endl;



                /*Generate item room when there are X rooms to generate
                if (nofRooms == 6) {
                    $$Item generator goes here$$
                    Item* item = Item::generate;
                    room->AddItem(item);
                    nofRooms--;
                    
                } */

                /* Last will be a boss room
                if (nofRooms == 1) {
                    Monster* boss = new Boss(50.0, 50.0);
                    room->AddEnemy(Boss);
                    nofRooms--;
                }

                */
                nofRooms--;
                std::cout << nofRooms << std::endl;

                //Setup connections to neighboring rooms
                for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
                    if (*it == 1 ) {
                            std::cout << "Creating north connections"  << std::endl;
                            Connection* c1 = new Connection(size / 2, 0.0, "north", p_);
                            Connection* c2 = new Connection(size / 2, size, "south", p_);

                            Room* neighbor = map[x - 1][y];

                            room->AddConnection(c1);
                            room->SetNConn(neighbor);

                            neighbor->AddConnection(c2);
                            neighbor->SetSConn(room);

                        }
                    if (*it == 2) {
                            std::cout << "Creating east connections"  << std::endl;
                            Connection* c1 = new Connection(size, size / 2, "east", p_);
                            Connection* c2 = new Connection(0.0, size / 2, "west", p_);

                            Room* neighbor = map[x][y + 1];

                            room->AddConnection(c1);
                            room->SetNConn(neighbor);

                            neighbor->AddConnection(c2);
                            neighbor->SetSConn(room);
                        }
                    if (*it == 3) {
                            std::cout << "Creating south connections"  << std::endl;
                            Connection* c1 = new Connection(size / 2, size, "south", p_);
                            Connection* c2 = new Connection(size / 2, 0.0, "north", p_);

                            Room* neighbor = map[x + 1][y];

                            room->AddConnection(c1);
                            room->SetNConn(neighbor);

                            neighbor->AddConnection(c2);
                            neighbor->SetSConn(room);
                        }
                    if (*it == 4) {
                        {
                            std::cout << "Creating west connections"  << std::endl;
                            Connection* c1 = new Connection(0.0, size / 2, "west", p_);
                            Connection* c2 = new Connection(size, size / 2, "east", p_);

                            Room* neighbor = map[x][y - 1];

                            room->AddConnection(c1);
                            room->SetNConn(neighbor);

                            neighbor->AddConnection(c2);
                            neighbor->SetSConn(room);
                        }
                    }
                }
                neighbors.clear();
                for (int i = 0; i < 5; i++) {
                    for (int j = 0; j < 5; j++) {
                        if (map[i][j] == nullptr) { std::cout << "#"; } else { std::cout << "X"; } 
                    }
                    std::cout << std::endl;
                }
            }
            else { neighbors.clear(); }
        }
    }
    std::cout << std::endl << "Connections in each room:" << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (map[i][j] != nullptr) { 
                std::cout << map[i][j]->GetConnections().size();
            }
            else { std::cout << "#"; } 
        }
        std::cout << std::endl;
    }
    std::cout << "Enemies in each room:" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (map[i][j] != nullptr) { 
                std::cout << map[i][j]->GetEnemies().size();
            }
            else { std::cout << "#"; } 
        }
        std::cout << std::endl;
    }
}
//Fills room with monsters
Room* Map::room_init() {

    int size = rooms_.front()->GetWidth();
    srand(time(nullptr));

    Room* room = new Room;

    //Pick a monster randomly from monsters
    //Expand as more monsters are added

    char monsters[2] = { 'O', 'G' };


    //Coords for the placements of monsters, (4 monsters in corners)
    /*
    std::list<sf::Vector2f> coords = { sf::Vector2f(10.0, 10.0), sf::Vector2f(90.0, 10.0), sf::Vector2f(10.0, 90.0), sf::Vector2f(90.0, 90.0) };


    for (auto c : coords) {

        int idx = rand() % 2;

        switch (monsters[idx]) {

            case 'O': {
                Orc* orc = new Orc(c.x, c.y, p); 
               room->AddEnemy(orc);
            }

            case 'G': {
                Orge* orge = new Orge(c.x, c.y, p);
                room->AddEnemy(orge);
            }

        }
    }*/
    //Alternatively if monsters are just placed willy nilly

    int nofMonsters = 3 + difficulty_;

    for (int i = 0; i < nofMonsters; i++) {

        sf::Vector2f pos = sf::Vector2f(rand() % size, rand() % size);

        switch (monsters[rand() % 2]) {

            case 'O': {
                Orc* orc = new Orc(pos.x, pos.y, p_); 
               room->AddEnemy(orc);
            }

            case 'G': {
                Orge* orge = new Orge(pos.x, pos.y, p_);
                room->AddEnemy(orge);
            }

        }       
    }
    return room;
}
