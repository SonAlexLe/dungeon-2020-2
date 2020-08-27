//map generation
#include "map.hpp"


Map::Map(int difficulty, std::shared_ptr<Player> p) : difficulty_(difficulty), p_(p) {
    // rooms_.push_back(new Room);
    map_init();
}

std::shared_ptr<Room> Map::GetStartingRoom() {
    return rooms_.front();
}

//Runs when a map is constructed
void Map::map_init() {

    //Some preliminary parameters for how many rooms are generated
    int nofRooms = 5 + difficulty_;

    //Init helper layout and starting room
    std::shared_ptr<Room> map[5][5] = { {nullptr} };
    std::shared_ptr<Room> start = std::make_shared<Room>();
    double size = start->GetHeight();
    map[2][2] = start;
    rooms_.push_back(start);

    //Create a random seed
    srand(time(nullptr));

    while (nofRooms > 0) {

        //Pick a random cell in array
        int x = rand() % 5;
        int y = rand() % 5;

        if(map[x][y] == nullptr) {
 
            //Where 1 is north, 2 is east, 3 is south, 4 is west
            std::list<int>neighbors;

            //Count how many neighbors the cell has
            if ( (x != 4) && map[x + 1][y] != nullptr) { neighbors.push_back(3);} // Check South
            if ( (x != 0) && map[x - 1][y] != nullptr) { neighbors.push_back(1);} // Check North

            if ( (y != 4) && map[x][y + 1] != nullptr) { neighbors.push_back(2);} // Check East
            if ( (y != 0) && map[x][y - 1] != nullptr) { neighbors.push_back(4);} // Check West


            //The maximum amount of neighbors can be tweaked to change the layout of the maps
            if(neighbors.size() >= 1 && neighbors.size() < 3) {

                std::shared_ptr<Room> room = std::make_shared<Room>();

                if (nofRooms == 3) {

                    //Generate two random pieces of equipment and a consumable in the item room
                    std::shared_ptr<itemGenerator> gen = std::make_shared<itemGenerator>();
                    std::shared_ptr<Item> item1 = gen->createEquipment(150.f, 200.f, p_);
                    //std::shared_ptr<Item> item2 = gen->createEquipment(150.f, 100.f, p_);
                    //std::shared_ptr<Item> cons = gen->createConsumable(200.f, 150.f, p_);

                    room->SetType("Item");
                    room->AddItem(item1);

                }

                else if (nofRooms == 1) {

                    //Set the room type to Boss (could be useful for win condition logic)
                    room->SetType("Boss");

                    //For now init an ogre in the middle of the room, can be replaced by a boss
                    std::shared_ptr<Orge> boss = std::make_shared<Orge>(150.f, 150.f, p_);

                    room->AddEnemy(boss);

                }

                //All conditions are met, create a room               
                else { room = room_init(); }

                map[x][y] = room;
                rooms_.push_back(room); 

                std::cout << "Room created @ " << x << " " << y  << std::endl;

                nofRooms--;
                std::cout << nofRooms << std::endl;

                //Setup connections to neighboring rooms
                for (auto it = neighbors.begin(); it != neighbors.end(); it++) {
                    if (*it == 1 ) {
                            std::cout << "Creating north connections"  << std::endl;
                            std::shared_ptr<Connection> c1 = std::make_shared<Connection>(size / 2, 0.0, "north", p_);
                            std::shared_ptr<Connection> c2 = std::make_shared<Connection>(size / 2, size, "south", p_);

                            std::shared_ptr<Room> neighbor = map[x - 1][y];

                            room->AddConnection(c1);
                            room->SetNConn(neighbor);

                            neighbor->AddConnection(c2);
                            neighbor->SetSConn(room);

                        }
                    if (*it == 2) {
                            std::cout << "Creating east connections"  << std::endl;
                            std::shared_ptr<Connection> c1 = std::make_shared<Connection>(size, size / 2, "east", p_);
                            std::shared_ptr<Connection> c2 = std::make_shared<Connection>(0.0, size / 2, "west", p_);

                            std::shared_ptr<Room> neighbor = map[x][y + 1];

                            room->AddConnection(c1);
                            room->SetEConn(neighbor);

                            neighbor->AddConnection(c2);
                            neighbor->SetWConn(room);
                        }
                    if (*it == 3) {
                            std::cout << "Creating south connections"  << std::endl;
                            std::shared_ptr<Connection> c1 = std::make_shared<Connection>(size / 2, size, "south", p_);
                            std::shared_ptr<Connection> c2 = std::make_shared<Connection>(size / 2, 0.0, "north", p_);

                            std::shared_ptr<Room> neighbor = map[x + 1][y];

                            room->AddConnection(c1);
                            room->SetSConn(neighbor);

                            neighbor->AddConnection(c2);
                            neighbor->SetNConn(room);
                        }
                    if (*it == 4) {
                        {
                            std::cout << "Creating west connections"  << std::endl;
                            std::shared_ptr<Connection> c1 = std::make_shared<Connection>(0.0, size / 2, "west", p_);
                            std::shared_ptr<Connection> c2 = std::make_shared<Connection>(size, size / 2, "east", p_);

                            std::shared_ptr<Room> neighbor = map[x][y - 1];

                            room->AddConnection(c1);
                            room->SetWConn(neighbor);

                            neighbor->AddConnection(c2);
                            neighbor->SetEConn(room);
                        }
                    }
                }
                neighbors.clear();
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
    std::cout << "Special rooms:" << std::endl;
    std::cout << std::endl;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (map[i][j] != nullptr) { 
                std::string tmp = map[i][j]->GetType();
                if (tmp == "Boss") {std::cout << "B";} else if (tmp == "Item") { std::cout << "I"; } else { std::cout << "X"; }
            }
            else { std::cout << "#"; } 
        }
        std::cout << std::endl;
    }

}
//Fills room with monsters
std::shared_ptr<Room> Map::room_init() {

    int size = rooms_.front()->GetWidth();
    srand(time(nullptr));

    std::shared_ptr<Room> room = std::make_shared<Room>();

    //Pick a monster randomly from monsters

    //O for Orc and G for Ogre :^) <- spelled orge
    char monsters[2] = { 'O', 'G' };

    int nofMonsters = 1 + difficulty_;

    for (int i = 0; i < nofMonsters; i++) {

        sf::Vector2f pos = sf::Vector2f(rand() % size, rand() % size);

        switch (monsters[rand() % 2]) {

            case 'O': {
                std::shared_ptr<Orc> orc = std::make_shared<Orc>(pos.x, pos.y, p_); 
               room->AddEnemy(orc);
            }

            case 'G': {
                std::shared_ptr<Orge> orge = std::make_shared<Orge>(pos.x, pos.y, p_);
                room->AddEnemy(orge);
            }

        }       
    }
    return room;
}
