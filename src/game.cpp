#include "game.h"


Game::Game(int rows, int cols)
    : Game(rows, cols, Point(0, 0), Point(cols - 1, rows - 1), Points()) {};

Game::Game(int rows, int cols, Point start, Point end, Points keys)
    : exit(end), player(start), keys(keys), over(false), facing(0)
{
    map_init(rows, cols);

    Construct(map->width() * TILE_SIZE, map->height() * TILE_SIZE, PXL_SIZE, PXL_SIZE);
}

Game::~Game()
{
    delete map;
    delete floorSprs;
    delete wallSprs;
}

void Game::draw() {
    srand(0);
    Clear(olc::BLACK);
    for ( int y = 0; y < map->height(); ++y ) {
        for ( int x = 0; x < map->width(); ++x ) {
            int r = map->height() - y - 1;
            int c = x;

            DrawSprite(olc::vi2d(c, r) * TILE_SIZE, floorSprs->rand());
            switch ( map->at(x, y) ) {
                case CHAR:
                    if ( player == exit )
                        DrawSprite(olc::vi2d(c, r) * TILE_SIZE, &doorSpr);
                    DrawSprite(olc::vi2d(c, r) * TILE_SIZE, charSprs->at(facing));
                    break;
                case WALL:
                    DrawSprite(olc::vi2d(c, r) * TILE_SIZE, wallSprs->rand());
                    break;
                case EXIT:
                    DrawSprite(olc::vi2d(c, r) * TILE_SIZE, &doorSpr);
                    break;
                case KEY:
                    DrawSprite(olc::vi2d(c, r) * TILE_SIZE, &keySpr);
                    break;
            }
        }
    }
}

void Game::map_init(int rows, int cols) {
    {   // error checking
        if ( rows < 2 || cols < 2 )
            throw std::range_error("Dimensions are too small.");

        Points objs(keys);
        objs.push_back(player);
        objs.push_back(exit);
        for ( auto obj : objs ) {
            if ( obj.x < 0 || obj.y < 0 || obj.x >= cols || obj.y >= rows )
                throw std::range_error("Can't initialize: object out of bounds.");
        }
    }

    Point one(1, 1);
    int width  = cols   * 2 + 1;
    int height = rows   * 2 + 1;
    player     = player * 2 + one;
    exit       = exit   * 2 + one;

    for ( Point& key : keys )
        key = key * 2 + one;

    srand(time(NULL));
    map = new Map(width, height);

    map->generate(random_walk);

    for ( auto key : keys )
        map->at(key.x, key.y) = KEY;

    map->at(player.x, player.y) = CHAR;
    map->at(exit.x, exit.y) = EXIT;
}

bool Game::move( byte direction ) // Updates player position and facing direction
{
    bool valid = false;
    int x = player.x, y = player.y;

    switch ( direction )
    {
    case NORTH : { valid = map->get(x, ++y) != WALL; if (valid) facing = UP   ; break; }
    case EAST  : { valid = map->get(++x, y) != WALL; if (valid) facing = RIGHT; break; }
    case SOUTH : { valid = map->get(x, --y) != WALL; if (valid) facing = DOWN ; break; }
    case WEST  : { valid = map->get(--x, y) != WALL; if (valid) facing = LEFT ; break; }
    default: break;
    }

    if ( valid ) {
        auto replacement = player == exit ? EXIT : OPEN;
        map->at(player.x, player.y) = replacement;

        map->at(x, y) = CHAR;

        player = Point(x, y);
    }

    return valid;
}

bool Game::OnUserCreate() {
    // charSpr .LoadFromFile("./assets/sprites/character"".png");
    charSprs = new Sprites(CHAR_SPRS);
    // wallSpr .LoadFromFile("./assets/sprites/wall"     ".png");
    wallSprs = new Sprites(WALLS_SPRS);
    doorSpr .LoadFromFile("./assets/sprites/door"     ".png");
    keySpr  .LoadFromFile("./assets/sprites/key"      ".png");
    // floorSpr.LoadFromFile("./assets/sprites/floor"    ".png");
    floorSprs = new Sprites(FLOOR_SPRS);
    SetPixelMode(olc::Pixel::MASK);

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) {
    // static unsigned long long frame = 0;
    static float t_since_update = 0.0;
    static byte direction = NONE;
    static short input_delay = 0;

    t_since_update += fElapsedTime;

    if ( t_since_update > FRAME_TIME ) {
        t_since_update -= FRAME_TIME;
        // printf("Frame: %llu\n", frame++);

        if ( --input_delay <= 0 && direction == NONE ) {
                 if (GetKey(olc::Key::W).bHeld) direction = NORTH;
            else if (GetKey(olc::Key::D).bHeld) direction = EAST;
            else if (GetKey(olc::Key::S).bHeld) direction = SOUTH;
            else if (GetKey(olc::Key::A).bHeld) direction = WEST;
            if ( direction != NONE )
                input_delay = 6;
        }

        bool moved = move(direction);
        direction = NONE;

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
