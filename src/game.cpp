#include "game.h"


Game::Game(int rows, int cols)
    : Game(rows, cols, Point(0, 0), Point(cols - 1, rows - 1), Points()) {};

Game::Game(int rows, int cols, Point start, Point end, Points keys)
    : exit(end), entrance(start), keys(keys), over(false), facing(0)
{
    srand((unsigned)time(NULL));

    map_init(rows, cols);
    explored = alloc2D(map->width(), map->height(), false);
    update_fog();

    tile_seed = alloc2D(map->width(), map->height());
    for ( int x = 0; x < map->width(); ++x )
        for ( int y = 0; y < map->height(); ++y )
            tile_seed[x][y] = (byte)rand();

    Construct(
        (map->width() + 2) * TILE_SIZE, (map->height() + 2) * TILE_SIZE,
        PXL_SIZE, PXL_SIZE
    );
}

Game::~Game()
{
    free2D(explored);
    free2D(tile_seed);
    delete map;
    delete barrierSprs;
    delete charSprs;
    delete floorSprs;
    delete wallSprs;
    for ( int i = 0; i < FOG_N; ++i )
        delete fogSprs[i];
}

void Game::draw() {
    Clear(olc::BLACK);

    // draw border
    for ( int r = 0, c = map->width() + 1; r < map->height() + 2; ++r ) {
        DrawSprite(olc::vi2d(0, r) * TILE_SIZE, barrierSprs->rand(r));
        DrawSprite(olc::vi2d(c, r) * TILE_SIZE, barrierSprs->rand(r * c));
    }
    for ( int c = 0, r = map->height() + 1; c < map->width() + 2; ++c ) {
        DrawSprite(olc::vi2d(c, 0) * TILE_SIZE, barrierSprs->rand(c));
        DrawSprite(olc::vi2d(c, r) * TILE_SIZE, barrierSprs->rand(r * c));
    }

    // draw floor
    for ( int r = 1; r < map->height() + 1; ++r )
        for ( int c = 1; c < map->width() + 1; ++c )
            DrawSprite(olc::vi2d(c, r) * TILE_SIZE,
                       floorSprs->rand(tile_seed[c - 1][r - map->height()]));

    // draw objects with transparency
    SetPixelMode(olc::Pixel::MASK);
    for ( int y = 0; y < map->height(); ++y ) {
        for ( int x = 0; x < map->width(); ++x ) {
            int r = 1 + map->height() - y - 1;
            int c = 1 + x;
            byte seed = tile_seed[x][y];
            byte exploration = explored[x][y];

            if ( exploration > 0 ) {
                switch ( (Tile)map->get(x, y) ) {
                    case Tile::CHAR:
                        if ( player == exit )
                            DrawSprite(olc::vi2d(c, r) * TILE_SIZE, &doorSpr);
                        else if ( player == entrance )
                            DrawSprite(olc::vi2d(c, r) * TILE_SIZE, &ladderSpr);
                        DrawSprite(olc::vi2d(c, r) * TILE_SIZE, charSprs->at(facing));
                        break;
                    case Tile::WALL:
                        DrawSprite(olc::vi2d(c, r) * TILE_SIZE, wallSprs->rand(seed));
                        break;
                    case Tile::EXIT:
                        DrawSprite(olc::vi2d(c, r) * TILE_SIZE, &doorSpr);
                        break;
                    case Tile::KEY:
                        DrawSprite(olc::vi2d(c, r) * TILE_SIZE, &keySpr);
                        break;
                    case Tile::LADDER:
                        DrawSprite(olc::vi2d(c, r) * TILE_SIZE, &ladderSpr);
                        break;
                }
            }

            if ( exploration < FOG_N ) {
                srand((unsigned)time(NULL) * (y * map->width() + x));
                DrawSprite(olc::vi2d(c, r) * TILE_SIZE, fogSprs[exploration]->rand());
            }
        }
    }
    SetPixelMode(olc::Pixel::NORMAL);
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

    // add space for walls between positions
    Point one(1, 1);
    int width  = cols     * 2 + 1;
    int height = rows     * 2 + 1;
    entrance   = entrance * 2 + one;
    exit       = exit     * 2 + one;
    player     = entrance;
    for ( Point& key : keys )
        key = key * 2 + one;

    // alloc and generate map
    map = new Map(width, height);
    map->generate(random_walk);

    // place objects
    for ( auto key : keys )
        map->at(key.x, key.y) = (byte)Tile::KEY;

    map->at(player.x, player.y) = (byte)Tile::CHAR;
    map->at(exit.x, exit.y) = (byte)Tile::EXIT;
}

bool Game::move( byte direction ) // Updates player position and facing direction
{
    bool valid = false;
    int x = player.x, y = player.y;

    switch ( (Direction)direction )
    {
    case Direction::NORTH : { valid = map->get(x, ++y) != (byte)Tile::WALL; if (valid) facing = UP   ; break; }
    case Direction::EAST  : { valid = map->get(++x, y) != (byte)Tile::WALL; if (valid) facing = RIGHT; break; }
    case Direction::SOUTH : { valid = map->get(x, --y) != (byte)Tile::WALL; if (valid) facing = DOWN ; break; }
    case Direction::WEST  : { valid = map->get(--x, y) != (byte)Tile::WALL; if (valid) facing = LEFT ; break; }
    default: break;
    }

    if ( valid ) {
        auto replacement = player == exit ? Tile::EXIT : player == entrance ? Tile::LADDER : Tile::OPEN;
        map->at(player.x, player.y) = (byte)replacement;

        map->at(x, y) = (byte)Tile::CHAR;

        player = Point(x, y);
    }

    return valid;
}

bool Game::OnUserCreate() { // init
    // allocate sprites here (not in cosntructor!) for Windows compatability
    doorSpr  .LoadFromFile("./assets/sprites/door.png");
    ladderSpr.LoadFromFile("./assets/sprites/ladder.png");
    keySpr   .LoadFromFile("./assets/sprites/key.png");
    charSprs    = new Sprites(CHAR_SPRS);
    barrierSprs = new Sprites(BARRIER_SPRS);
    floorSprs   = new Sprites(FLOOR_SPRS);
    wallSprs    = new Sprites(WALLS_SPRS);
    fogSprs[3]  = new Sprites(FOG_W_SPRS);
    fogSprs[2]  = new Sprites(FOG_L_SPRS);
    fogSprs[1]  = new Sprites(FOG_SPRS);
    fogSprs[0]  = new Sprites(FOG_H_SPRS);

    return true;
}

bool Game::OnUserUpdate(float fElapsedTime) { // frame update
    // static unsigned long long frame = 0;
    static float t_since_update = 0.0;
    static Direction direction = Direction::NONE;
    static short input_delay = 0;

    t_since_update += fElapsedTime;

    if ( t_since_update > FRAME_TIME ) {
        t_since_update -= FRAME_TIME;
        // printf("Frame: %llu\n", frame++);

        if ( --input_delay <= 0 && direction == Direction::NONE ) {
                 if (GetKey(olc::Key::W).bHeld) direction = Direction::NORTH;
            else if (GetKey(olc::Key::D).bHeld) direction = Direction::EAST;
            else if (GetKey(olc::Key::S).bHeld) direction = Direction::SOUTH;
            else if (GetKey(olc::Key::A).bHeld) direction = Direction::WEST;
            if ( direction != Direction::NONE )
                input_delay = 6;
        }

        bool moved = move((byte)direction);
        direction = Direction::NONE;

        if ( moved ) {
            update_fog();

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

void Game::update_fog() {
    // immediate area check
    explored[player.x][player.y] = FOG_N;
    for ( int x = player.x - 1; x <= player.x + 1; x += 2 )
        for ( int y = player.y - 1; y <= player.y + 1; y += 2 )
            explored[x][y] = std::min(explored[x][y] + 1, FOG_N);

    // line of sight checks
    int x, y;
    x = player.x, y = player.y;
    for ( int s = FOG_N; s > 0 && map->at(x, y) != (byte)Tile::WALL; --s, ++x )
        explored[x + 1][y] = std::min(explored[x + 1][y] + s, FOG_N);

    x = player.x, y = player.y;
    for ( int s = FOG_N; s > 0 && map->at(x, y) != (byte)Tile::WALL; --s, --x )
        explored[x - 1][y] = std::min(explored[x - 1][y] + s, FOG_N);

    x = player.x, y = player.y;
    for ( int s = FOG_N; s > 0 && map->at(x, y) != (byte)Tile::WALL; --s, ++y )
        explored[x][y + 1] = std::min(explored[x][y + 1] + s, FOG_N);

    x = player.x, y = player.y;
    for ( int s = FOG_N; s > 0 && map->at(x, y) != (byte)Tile::WALL; --s, --y )
        explored[x][y - 1] = std::min(explored[x][y - 1] + s, FOG_N);
}
