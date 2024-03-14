#include "Entity.h"

Entity::Entity()
{
    direction = AIMLESS;
    position.x = 0;
    position.y = 0;

    inventory.object = '?';
    inventory.position.x = 0;
    inventory.position.y = 0;
    inventory.total = 0;

    food = '?';
    enemy = '?';
}

void Entity::UpdatePosition(int x, int y)
{
	position.x = x;
	position.y = y;
}

Entity::Sight Entity::LookDirection(Direction direction, PositionCoords position, vector<vector<char>> board)
{
    Sight sight;
    sight.direction = direction;
    sight.distance = 0;
    sight.object = '?';
    switch (direction)
    {
    case Entity::AIMLESS:
        break;

    case Entity::NORTH:
        for (int i = position.x - 1; i >= 0; i--)
        {
            sight.distance++;
            if (IsImportantObject(board[i][position.y]))
            {
                sight.object = board[i][position.y];
                sight.position.x = i;
                sight.position.y = position.y;
                break;
            }
        }
        break;

    case Entity::SOUTH:
        for (int i = position.x + 1; i < board.size(); i++)
        {
            sight.distance++;
            if (IsImportantObject(board[i][position.y]))
            {
                sight.object = board[i][position.y];
                sight.position.x = i;
                sight.position.y = position.y;
                break;
            }
        }
        break;

    case Entity::EAST:
        for (int i = position.y + 1; i < board.size(); i++)
        {
            sight.distance++;
            
            if (IsImportantObject(board[position.x][i]))
            {
                sight.object = board[position.x][i];
                sight.position.x = position.x;
                sight.position.y = i;
                break;
            }
        }
        break;

    case Entity::WEST:
        for (int i = position.y - 1; i >= 0; i--)
        {
            sight.distance++;
            if (IsImportantObject(board[position.x][i]))
            {
                sight.object = board[position.x][i];
                sight.position.x = position.x;
                sight.position.y = i;
                break;
            }
        }
        break;

    default:
        break;
    }
    
    string dir = TranslateDirection(direction);
    return sight;
}

bool Entity::IsImportantObject(char object)
{
    if (object == WALL)
    {
        return true;
    }
    if (object == '0')
    {
        return true;
    }
    if (object == 'C')
    {
        return true;
    }
    if (object == 'M')
    {
        return true;
    }
    return false;
}

vector<vector<char>> Entity::MoveEntity(vector<vector<char>> board)
{
    for (int i : {-1, 0, 1})
    {
        for (int j : {-1, 0, 1})
        {
            //keeps movement in cardinal direction
            if (abs(j) != abs(i))
            {
                if (board[position.x + i][position.y + j] == '_' || board[position.x + i][position.y + j] == food)
                {

                    //try to move
                    switch (direction)
                    {
                    case Entity::NORTH:
                        if (i == -1 && j == 0)
                        {
                            board = MovementBoardSwap(board, i, j);
                        }
                        break;
                    case Entity::SOUTH:
                        if (i == 1 && j == 0)
                        {
                            board = MovementBoardSwap(board, i, j);
                        }
                        break;
                    case Entity::EAST:
                        if (i == 0 && j == 1)
                        {   
                            board = MovementBoardSwap(board, i, j);
                        }
                        break;
                    case Entity::WEST:
                        if (i == 0 && j == -1)
                        {
                            board = MovementBoardSwap(board, i, j);
                        }
                        break;
                    }
                }
            }
        }
    }
    return board;
}

vector<vector<char>> Entity::MovementBoardSwap(vector<vector<char>> board, int x, int y)
{
    if (board[position.x + x][position.y + y] == food)
    {
        cout << "and devoured " << ENTITY_LOOKUP.at(food) << "\n";
        board[position.x + x][position.y + y] = '_';
    }
    swap(board[position.x + x][position.y + y], board[position.x][position.y]);
    UpdatePosition(position.x + x, position.y + y);
    return board;
}

void Entity::RenewMovementOptions()
{
    movement_ops = { NORTH, SOUTH, EAST, WEST };
}

Entity::Direction Entity::RandomDirection()
{
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::vector<Direction> buffer_deck{ std::begin(movement_ops), std::end(movement_ops) };
    shuffle(buffer_deck.begin(), buffer_deck.end(), std::default_random_engine(seed));
    Direction random_dir;

    if (buffer_deck.size() >= 1)
    {
        if (direction == AIMLESS)
        {
            random_dir = buffer_deck.front();
            return random_dir;
        }
        random_dir = buffer_deck.front();
    }
    else
        random_dir = AIMLESS;

    cout << TranslateDirection(random_dir) << "\n";
    
    return random_dir;
}

string Entity::TranslateDirection(Direction dir)
{
    string conv;
    switch (dir)
    {
    case Entity::AIMLESS:
        conv = "???";
        break;
    case Entity::NORTH:
        conv = "North";
        break;
    case Entity::SOUTH:
        conv = "South";
        break;
    case Entity::EAST:
        conv = "East";
        break;
    case Entity::WEST:
        conv = "West";
        break;
    default:
        break;
    }
    return conv;
}

//blocks a direction based off of what is sighted
//or the reverse of the current direction if no sight is given.
void Entity::BlockDirection(Sight sight)
{
    if (sight.direction == AIMLESS && sight.distance == 0 && sight.object == ' ')
    {
        Direction opposite = (Direction)-direction;
        movement_ops.remove(opposite);
        return;
    }

    movement_ops.remove(sight.direction);
}