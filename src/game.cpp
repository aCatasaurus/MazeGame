#include "game.h"


Game::Game(int rows, int cols) : map(rows, cols), keys({}), over(false), facing(0)
{
    width = cols * 2 + 1;
    height = rows * 2 + 1;

    player = Point(0, 0);
    exit = Point(rows - 1, cols - 1);
    map.at(player).set(PLAYER, PLAYER);
    map.at(exit).set(EXIT, EXIT);

    this->Construct(width * 8, height * 8, 2, 2);
}

Game::Game(int rows, int cols, Point start, Point end, Points keys)
    : map(rows, cols), exit(end), player(start), keys(keys), over(false), facing(0)
{
    width = cols * 2 + 1;
    height = rows * 2 + 1;

    map.at(player).set(PLAYER, PLAYER);
    map.at(exit).set(EXIT, EXIT);
    for ( const Point& key : keys )
        map.at(key).set(KEY, KEY);

    this->Construct(width * 8, height * 8, 2, 2);
}

Game::~Game() {}

void Game::draw() {
    const char * const * data = map.get();
    Clear(olc::BLACK);
    for ( int y = 0; y < height; ++y ) {
        for ( int x = 0; x < width; ++x ) {
            switch (data[y][x]) {
                case CHAR:
                    DrawSprite(olc::vi2d(x, y) * 8, &charSpr);
                    break;
                case WALL:
                    DrawSprite(olc::vi2d(x, y) * 8, &wallSpr);
                    break;
                case DOOR:
                    DrawSprite(olc::vi2d(x, y) * 8, &doorSpr);
                    break;
                case ITEM:
                    DrawSprite(olc::vi2d(x, y) * 8, &itemSpr);
                    break;
            }
        }
    }
}

bool Game::move( byte direction ) // Updates player position and facing direction
{
    byte state = map.at(player).get();
    bool valid = !(state & direction);
    if ( valid ) {
        map.at(player).set(0, PLAYER);
        if ( player == exit )
            map.at(exit).set(EXIT, EXIT);

        switch ( direction )
        {
        case NORTH : { player.r -= 1; facing = UP   ; break; }
        case EAST  : { player.c += 1; facing = RIGHT; break; }
        case SOUTH : { player.r += 1; facing = DOWN ; break; }
        case WEST  : { player.c -= 1; facing = LEFT ; break; }
        default: break;
        }
        map.at(player).set(PLAYER, PLAYER);
    }

    return valid;
}


bool Game::OnUserCreate() {
    charSpr.LoadFromFile("./assets/sprites/character.png");
    wallSpr.LoadFromFile("./assets/sprites/wall.png");
    doorSpr.LoadFromFile("./assets/sprites/door.png");
    itemSpr.LoadFromFile("./assets/sprites/key.png");
    SetPixelMode(olc::Pixel::MASK);

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    // static unsigned long long frame = 0;
    static float t_since_update = 0.0;
    static byte direction = ALL;
    static short input_delay = 0;

    t_since_update += fElapsedTime;

    if ( t_since_update > FRAME_TIME ) {
        t_since_update -= FRAME_TIME;
        // printf("Frame: %llu\n", frame++);

        if ( --input_delay <= 0 && direction == ALL ) {
                 if (GetKey(olc::Key::W).bHeld) direction = NORTH;
            else if (GetKey(olc::Key::D).bHeld) direction = EAST;
            else if (GetKey(olc::Key::S).bHeld) direction = SOUTH;
            else if (GetKey(olc::Key::A).bHeld) direction = WEST;
            if ( direction != ALL )
                input_delay = 10;
        }

        bool moved = move(direction);
        direction = ALL;

        if ( moved ) {

            if ( keys.contains(player) )
                keys.remove(player);

            if ( player == exit ) {
                if ( keys.size() == 0 )
                    over = true;
                else
                    printf("You cannot unlock the door.\n");
            }

            if ( over ) {
                printf("You cleared the maze!\n");
                return false;
            }
        }

        draw();
    }

    return true;
}

void Game::run()
{
    Start();
}
