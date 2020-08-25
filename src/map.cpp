//map generation
//todo: version of generateMap() which returns a single square room

#include "map.hpp"


Map::Map(int difficulty) : difficulty_(difficulty) {
    rooms_.push_back(new Room); 

    // map_init();

}

Map::~Map() {
    for (Room* r : rooms_) {
        delete r;
    }
}

Room* Map::GetStartingRoom() {
    return rooms_.front();
}

//Runs when a map is constructed
void Map::map_init() {

    //Some preliminary parameters for how many rooms are generated
    int nofRooms = 10 + difficulty_;

    //Init layout and starting room
    Room* map[9][9] = { {nullptr} };
    Room* start = new Room();
    map[5][5] = start;
    rooms_.push_back(start);

    //Create a random seed
    srand(time(nullptr));

    while (nofRooms > 0) {

        //Pick a random cell in array
        int x = rand() % 9;
        int y = rand() % 9;

        if(map[x][y] == nullptr) {

            //Where 1 is north, 2 is east, 3 is south, 4 is west
            std::list<int>neighbors;

            //Count how many neighbors the cell has
            if ( (x != 8) && map[x + 1][y] != nullptr) { neighbors.push_back(2);}
            if ( (x != 0) && map[x - 1][y] != nullptr) { neighbors.push_back(4);}
            if ( (y != 8) && map[x][y + 1] != nullptr) { neighbors.push_back(1);}
            if ( (y != 0) && map[x][y - 1] != nullptr) { neighbors.push_back(3);}

            //The maximum amount of neighbors can be tweaked to change the layout of the maps
            if(neighbors.size() > 1 && neighbors.size() < 3) {

                //All conditions are met, create a room #####UNCOMMENT THIS TO TEST ROOM_INIT####
                // Room* room = Map::room_init();

                Room* room = new Room;
                map[x][y] = room;

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

                //Setup connections for the new room
                for (int dir : neighbors) {
                    switch (dir) {

                        //For a northern connection c1 is on the northern wall and c2 on the southern wall (Coordinates are placeholder)
                        case 1: {
                            Connection* c1 = new Connection(50.0, 0.0);
                            Connection* c2 = new Connection(50.0, 100.0);

                            room->AddConnection(c1);
                            room->SetNConn(map[x][y + 1]);

                            map[x][y + 1]->AddConnection(c2);
                            map[x][y + 1]->SetSConn(room);

                        }
                        //For an eastern connection c1 is east and c2 west
                        case 2: {
                            Connection* c1 = new Connection(100.0, 50.0);
                            Connection* c2 = new Connection(0.0, 50.0);

                            room->AddConnection(c1);
                            room->SetEConn(map[x - 1][y]);

                            map[x - 1][y]->AddConnection(c2);
                            map[x - 1][y]->SetWConn(room);
                        }
                        //For a southern connection c1 is south and c2 north
                        case 3: {
                            Connection* c1 = new Connection(50.0, 100.0);
                            Connection* c2 = new Connection(50.0, 0.0);

                            room->AddConnection(c1);
                            room->SetSConn(map[x][y - 1]);

                            map[x][y - 1]->AddConnection(c2);
                            map[x][y - 1]->SetNConn(room);
                        }
                        //For a western connection c1 is west and c2 east
                        case 4: {
                            Connection* c1 = new Connection(0.0, 50.0);
                            Connection* c2 = new Connection(100.0, 50.0);

                            room->AddConnection(c1);
                            room->SetWConn(map[x + 1][y]);

                            map[x + 1][y]->AddConnection(c2);
                            map[x + 1][y]->SetEConn(room);
                        }
                    }
                }
            }

        }
    }
}
//Fills room with monsters
Room* Map::room_init() {

    Room* room = new Room;


    //Pick a monster randomly from monsters
    //Expand as more monsters are added
    char monsters[1] = { 'O' };
    srand(time(nullptr));
    Player* p = rooms_.front()->GetPlayer();

    //Coords for the placements of monsters, (4 monsters in corners)
    std::list<sf::Vector2f> coords = { sf::Vector2f(10.0, 10.0), sf::Vector2f(90.0, 10.0), sf::Vector2f(10.0, 90.0), sf::Vector2f(90.0, 90.0) };


    for (auto c : coords) {

        int idx = rand() % 1;

        switch (monsters[idx]) {

            case 'O': {
                Orc* orc = new Orc(c.x, c.y, p); 
               room->AddEnemy(orc);
            }

        }

    }
    return room;
}
