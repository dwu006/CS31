// bees.cpp

// Portions you are to complete are marked with a TODO: comment.
// We've provided some incorrect return statements (so indicated) just
// to allow this skeleton program to compile and run, albeit incorrectly.
// The first thing you probably want to do is implement the trivial
// functions (marked TRIVIAL).  Then get Room::display going.  That gives
// you more flexibility in the order you tackle the rest of the functionality.
// As you finish implementing each TODO: item, remove its TODO: comment.

#include <iostream>
#include <string>
#include <random>
#include <utility>
#include <cstdlib>
using namespace std;

///////////////////////////////////////////////////////////////////////////
// Manifest constants
///////////////////////////////////////////////////////////////////////////

const int MAXROWS = 20;             // max number of rows in the room
const int MAXCOLS = 25;             // max number of columns in the room
const int MAXBEES = 150;            // max number of bees allowed
const int INITIAL_BEE_HEALTH = 2;

const int UP      = 0;
const int DOWN    = 1;
const int LEFT    = 2;
const int RIGHT   = 3;
const int NUMDIRS = 4;

///////////////////////////////////////////////////////////////////////////
// Type definitions
///////////////////////////////////////////////////////////////////////////

class Room;  // This is needed to let the compiler know that Room is a
             // type name, since it's mentioned in the Bee declaration.

class Bee
{
  public:
        // Constructor
    Bee(Room* rp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;

        // Mutators
    void move();
    bool getSwatted(int dir);

  private:
    Room* m_room;
    int   m_row;
    int   m_col;
    int   m_health;
      // TODO: You'll probably find that a bee object needs an additional
      // data member to support your implementation of the behavior affected
      // by being swatted.
};

class Player
{
  public:
        // Constructor
    Player(Room *rp, int r, int c);

        // Accessors
    int  row() const;
    int  col() const;
    int  age() const;
    bool isDead() const;

        // Mutators
    void   stand();
    void   moveOrSwat(int dir);
    void   setDead();

  private:
    Room* m_room;
    int   m_row;
    int   m_col;
    int   m_age;
    bool  m_dead;
};

class Room
{
  public:
        // Constructor/destructor
    Room(int nRows, int nCols);
    ~Room();

        // Accessors
    int     rows() const;
    int     cols() const;
    Player* player() const;
    int     beeCount() const;

    int     numBeesAt(int r, int c) const;
    bool    determineNewPosition(int& r, int& c, int dir) const;
    void    display() const;

        // Mutators
    bool   addBee(int r, int c);
    bool   addPlayer(int r, int c);
    bool   swatBeeAt(int r, int c, int dir);
    bool   moveBees();

        private:
    int     m_rows;
    int     m_cols;
    Player* m_player;
    Bee*    m_bees[MAXBEES];
    int     m_nBees;
};

class Game
{
  public:
        // Constructor/destructor
    Game(int rows, int cols, int nBees);
    ~Game();

        // Mutators
    void play();

  private:
    Room* m_room;
};

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function declarations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir);
int randInt(int min, int max);
void clearScreen();

///////////////////////////////////////////////////////////////////////////
//  Bee implementation
///////////////////////////////////////////////////////////////////////////

Bee::Bee(Room* rp, int r, int c)
{
    if (rp == nullptr)
    {
        cout << "***** A bee must be created in some Room!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > rp->rows()  ||  c < 1  ||  c > rp->cols())
    {
        cout << "***** Bee created with invalid coordinates (" << r << ","
             << c << ")!" << endl;
        exit(1);
    }
    m_room = rp;
    m_row = r;
    m_col = c;
    m_health = INITIAL_BEE_HEALTH;
}

int Bee::row() const
{
    return m_row;
}

int Bee::col() const
{
    return m_col;
}

void Bee::move()
{
    // Attempt to move in a random direction; if bee can't move, don't move
    int dir = randInt(0, NUMDIRS-1);  // dir is now UP, DOWN, LEFT, or RIGHT
    if(dir == 0 && m_row > 1){m_row--;}
    else if(dir == 1 && m_row < m_room->rows()){m_row++;}
    else if(dir == 2 && m_col > 1){m_col--;}
    else if(dir == 3 && m_col < m_room->cols()){m_col++;}
}

bool Bee::getSwatted(int dir)  
{
    if(m_health == INITIAL_BEE_HEALTH-1){return true;}

    m_health--;

    if (m_health <= 0) {return true;}

    if (m_room->determineNewPosition(m_row, m_col, dir)) {return false;}
    m_health = 0;
    return true;  
}


///////////////////////////////////////////////////////////////////////////
//  Player implementations
///////////////////////////////////////////////////////////////////////////

Player::Player(Room* rp, int r, int c)
{
    if (rp == nullptr)
    {
        cout << "***** The player must be created in some Room!" << endl;
        exit(1);
    }
    if (r < 1  ||  r > rp->rows()  ||  c < 1  ||  c > rp->cols())
    {
        cout << "**** Player created with invalid coordinates (" << r
             << "," << c << ")!" << endl;
        exit(1);
    }
    m_room = rp;
    m_row = r;
    m_col = c;
    m_age = 0;
    m_dead = false;
}

int Player::row() const
{
    return m_row;
}

int Player::col() const
{
    return m_col;
}

int Player::age() const
{
    return m_age;  
}

void Player::stand()
{
    m_age++;
}

void Player::moveOrSwat(int dir)
{
    m_age++;
    int row = m_row;
    int col = m_col;
            // If there's a bee at the current position (before moving), swat it.
    if(m_room->determineNewPosition(row, col, dir)){
        if (m_room->numBeesAt(row, col) > 0) {
            m_room->swatBeeAt(row, col, dir);
        } else {m_room->determineNewPosition(m_row, m_col, dir);}
    }
    // Check if the move is valid (determining the new position).
    // If the move is invalid (out of bounds), do nothing.
}

bool Player::isDead() const
{
      // Return whether the player is dead.
    return m_dead;  // This implementation compiles, but is incorrect.
}

void Player::setDead()
{  
    m_dead = true;
}

///////////////////////////////////////////////////////////////////////////
//  Room implementations
///////////////////////////////////////////////////////////////////////////

Room::Room(int nRows, int nCols)
{
    if (nRows <= 0  ||  nCols <= 0  ||  nRows > MAXROWS  ||  nCols > MAXCOLS)
    {
        cout << "***** Room created with invalid size " << nRows << " by "
             << nCols << "!" << endl;
        exit(1);
    }
    m_rows = nRows;
    m_cols = nCols;
    m_player = nullptr;
    m_nBees = 0;
}

Room::~Room()
{
    delete m_player;
    for (int i = 0; i < m_nBees; i++)
        delete m_bees[i];
}

int Room::rows() const
{
    return m_rows;
}

int Room::cols() const
{
    return m_cols;  
}

Player* Room::player() const
{
    return m_player;
}

int Room::beeCount() const
{
    return m_nBees;
}

int Room::numBeesAt(int r, int c) const
{
    // TODO:  Return the number of bees at row r, column c. v
    int count = 0;
    for(int i = 0; i < m_nBees; i++)
    {
        if(m_bees[i]->row() == r && m_bees[i]->col() == c){count++;}
    }
    return count;
}

bool Room::determineNewPosition(int& r, int& c, int dir) const
{
      // TODO:  If a move from row r, column c, one step in direction dir
      // would go out of the room, leave r and c unchanged and return false.
      // Otherwise, set r or c so that row r, column c, is now the new
      // position resulting from the proposed move, and return true.
    switch (dir)
    {
      case UP:
        if(r <= 1){return false;}
        r--;
        break;
      case DOWN:
        if(r >= m_rows){return false;}
        r++;
        break;
      case LEFT:
        if(c <= 1){return false;}
        c--;
        break;
      case RIGHT:  
        if(c >= m_cols){return false;}
        c++;
        break;
      default:
        return false;
    }
    return true;
}

void Room::display() const
{
      // Position (row,col) in the room coordinate system is represented in
      // the array element grid[row-1][col-1]
    char grid[MAXROWS][MAXCOLS];
    int r, c;
    
      // Fill the grid with dots


      // Indicate each bee's position
      // If one bee is at some grid point, set the char to 'B'.
      //        If it's 2 though 8, set it to '2' through '8'.
      //        For 9 or more, set it to '9'.
    for (r = 1; r <= rows(); r++)
        for (c = 1; c <= cols(); c++)
            if(numBeesAt(r,c) == 1){grid[r][c] = 'B';}
            else if(numBeesAt(r,c) >= 9){grid[r][c] = '9';}
            else if(numBeesAt(r,c) > 1){grid[r][c] = '0' + numBeesAt(r,c);}
            else{grid[r][c] = '.';}

      // Indicate player's position
    if (m_player != nullptr)
    {
          // Set the char to '@', unless there's also a bee there,
          // in which case set it to '*'.
        char& gridChar = grid[m_player->row()][m_player->col()];
        if (gridChar == '.')
            gridChar = '@';
        else if(isdigit(gridChar) || gridChar =='B')
            gridChar = '*';
    }

        // Draw the grid
    clearScreen();
    for (r = 1; r <= rows(); r++)
    {
        for (c = 1; c <= cols(); c++)
            cout << grid[r][c];
        cout << endl;
    }
    cout << endl;

        // Write message, bee, and player info
    cout << endl;
    cout << "There are " << beeCount() << " bees remaining." << endl;
    if (m_player == nullptr)
        cout << "There is no player." << endl;
    else
    {
        if (m_player->age() > 0)
            cout << "The player has lasted " << m_player->age() << " steps." << endl;
        if (m_player->isDead())
            cout << "The player is dead." << endl;
    }
}

bool Room::addBee(int r, int c)
{
      // If there are MAXBEES bees, return false.  Otherwise,
      // dynamically allocate a new Bee at coordinates (r,c).  Save the
      // pointer to the newly allocated Bee and return true.
    if(m_nBees >= MAXBEES){return false;}
    m_bees[m_nBees] = new Bee(this, r, c); 
    m_nBees++;

      // Your function must work as specified in the preceding paragraph even
      // in this scenario (which won't occur in this game):  MAXBEES
      // are added, then some are destroyed, then more are added.

    return true;  // This implementation compiles, but is incorrect.
}

bool Room::addPlayer(int r, int c)
{
      // Don't add a player if one already exists
    if (m_player != nullptr)
        return false;

      // Dynamically allocate a new Player and add it to the room
    m_player = new Player(this, r, c);
    return true;
}

bool Room::swatBeeAt(int r, int c, int dir)
{
      // TODO:  Swat one bee at row r, column c if at least one is at
      // that position.  If the bee does not survive the swat, destroy the
      // bee object, removing it from the room, and return true.  Otherwise,
      // return false (no bee at (r,c), or bee didn't die).
    if(numBeesAt(r,c) == 0){return false;}
    for(int i = 0; i < m_nBees; i++)
    {
        if(m_bees[i]->row() == r && m_bees[i]->col() == c)
        {
            if(m_bees[i]->getSwatted(dir))
            {
                delete m_bees[i];
                m_bees[i] = nullptr;
                if (i != m_nBees - 1){m_bees[i] = m_bees[m_nBees - 1]; m_bees[m_nBees - 1] = nullptr;}
                m_nBees--;
                return true;
            }
            return false;
        }
    }
    // swat 
    return false;  // This implementation compiles, but is incorrect.
}

bool Room::moveBees()
{
    for (int k = 0; k < m_nBees; k++)
    {
      // TODO:  Have the k-th bee in the room make one move.
      //        If that move results in that bee being in the same
      //        position as the player, the player dies.
      m_bees[k]->move();
      if(m_player->row() == m_bees[k]->row() && m_player->col() == m_bees[k]->col()){m_player->setDead();}
    }
      // return true if the player is still alive, false otherwise
    return ! m_player->isDead();
}

///////////////////////////////////////////////////////////////////////////
//  Game implementations
///////////////////////////////////////////////////////////////////////////

Game::Game(int rows, int cols, int nBees)
{
    if (nBees < 0)
    {
        cout << "***** Cannot create Game with negative number of bees!" << endl;
        exit(1);
    }
    if (nBees > MAXBEES)
    {
        cout << "***** Trying to create Game with " << nBees
             << " bees; only " << MAXBEES << " are allowed!" << endl;
        exit(1);
    }
    if (rows == 1  &&  cols == 1  &&  nBees > 0)
    {
        cout << "***** Cannot create Game with nowhere to place the bees!" << endl;
        exit(1);
    }

        // Create room
    m_room = new Room(rows, cols);

        // Add player
    int rPlayer = randInt(1, rows);
    int cPlayer = randInt(1, cols);
    m_room->addPlayer(rPlayer, cPlayer);
      // Populate with bees
    while (nBees > 0)
    {
        int r = randInt(1, rows);
        int c = randInt(1, cols);  
          // Don't put a bee where the player is
        if (r == rPlayer  &&  c == cPlayer)
            continue;
        m_room->addBee(r, c);
        nBees--;
    }
}

Game::~Game()
{
    delete m_room;
}

void Game::play()
{
    m_room->display();
    Player* player = m_room->player();
    if (player == nullptr)
        return;
    while ( ! player->isDead()  &&  m_room->beeCount() > 0)
    {
        cout << endl;
        cout << "Move (u/d/l/r/q or nothing): ";
        string action;
        getline(cin,action);
        if (action.size() == 0)  // player stands
            player->stand();
        else
        {
            switch (action[0])
            {
              default:   // if bad move, nobody moves
                cout << '\a' << endl;  // beep
                continue;
              case 'q':
                return;
              case 'u':
              case 'd':
              case 'l':
              case 'r':
                player->moveOrSwat(decodeDirection(action[0]));
                break;
            }
        }
        m_room->moveBees();
        m_room->display();
    }
}

///////////////////////////////////////////////////////////////////////////
//  Auxiliary function implementations
///////////////////////////////////////////////////////////////////////////

int decodeDirection(char dir)
{
    switch (dir)
    {
      case 'u':  return UP;
      case 'd':  return DOWN;
      case 'l':  return LEFT;
      case 'r':  return RIGHT;
    }
    return -1;  // bad argument passed in!
}

  // Return a uniformly distributed random int from min to max, inclusive
int randInt(int min, int max)
{
    if (max < min)
        swap(max, min);
    static random_device rnd;
    static default_random_engine generator(rnd());
    uniform_int_distribution<> distro(min, max);
    return distro(generator);
}

///////////////////////////////////////////////////////////////////////////
//  main()
///////////////////////////////////////////////////////////////////////////
#include <type_traits>
#include <cassert>

#define CHECKTYPE(c, f, r, a)  \
    static_assert(std::is_same<decltype(&c::f), r (c::*)a>::value, \
       "FAILED: You changed the type of " #c "::" #f);  \
    { [[gnu::unused]] auto p = static_cast<r(c::*)a>(&c::f); }

void thisFunctionWillNeverBeCalled()
{
      // If the student deleted or changed the interfaces to the public
      // functions, this won't compile.  (This uses magic beyond the scope
      // of CS 31.)

    Bee(static_cast<Room*>(0), 1, 1);
    CHECKTYPE(Bee, row, int, () const);
    CHECKTYPE(Bee, col, int, () const);
    CHECKTYPE(Bee, move, void, ());
    CHECKTYPE(Bee, getSwatted, bool, (int));

    Player(static_cast<Room*>(0), 1, 1);
    CHECKTYPE(Player, row, int, () const);
    CHECKTYPE(Player, col, int, () const);
    CHECKTYPE(Player, age, int, () const);
    CHECKTYPE(Player, isDead, bool, () const);
    CHECKTYPE(Player, stand, void, ());
    CHECKTYPE(Player, moveOrSwat, void, (int));
    CHECKTYPE(Player, setDead, void, ());

    Room(1, 1);
    CHECKTYPE(Room, rows, int, () const);
    CHECKTYPE(Room, cols, int, () const);
    CHECKTYPE(Room, player, Player*, () const);
    CHECKTYPE(Room, beeCount, int, () const);
    CHECKTYPE(Room, numBeesAt, int, (int, int) const);
    CHECKTYPE(Room, determineNewPosition, bool, (int&, int&, int) const);
    CHECKTYPE(Room, display, void, () const);
    CHECKTYPE(Room, addBee, bool, (int, int));
    CHECKTYPE(Room, addPlayer, bool, (int, int));
    CHECKTYPE(Room, swatBeeAt, bool, (int, int, int));
    CHECKTYPE(Room, moveBees, bool, ());

    Game(1, 1, 1);
    CHECKTYPE(Game, play, void, ());
}

void doBasicTests()
{
    {
        Room mate(10, 20);
        assert(mate.addPlayer(2, 6));
        Player* pp = mate.player();
        assert(pp->row() == 2  &&  pp->col() == 6  && ! pp->isDead());
        pp->moveOrSwat(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->moveOrSwat(UP);
        assert(pp->row() == 1  &&  pp->col() == 6  && ! pp->isDead());
        pp->setDead();
        assert(pp->row() == 1  &&  pp->col() == 6  && pp->isDead());
    }
    {
        Room service(2, 2);
        assert(service.addPlayer(1, 1));
        assert(service.addBee(2, 2));
        Player* pp = service.player();
        assert(service.moveBees());
        assert( ! pp->isDead());
        for (int k = 0; k < 1000  &&  ! pp->isDead()  &&  service.moveBees(); k++)
            assert(service.numBeesAt(1, 1) == 0);
        assert(pp->isDead()  &&  service.numBeesAt(1, 1) == 1);
    }
    {
        Room andBoard(2, 6);
        assert(andBoard.addPlayer(2, 1));
        assert(andBoard.addBee(2, 3));
        assert(andBoard.addBee(1, 1));
        assert(andBoard.addBee(1, 6));
        Player* pp = andBoard.player();
        pp->moveOrSwat(RIGHT);
        assert(andBoard.beeCount() == 3  &&  andBoard.numBeesAt(2, 3) == 1);
        pp->moveOrSwat(RIGHT);
        assert(andBoard.beeCount() == 3  &&  andBoard.numBeesAt(2, 4) == 1);
        pp->moveOrSwat(RIGHT);
        assert(andBoard.beeCount() == 3  &&  andBoard.numBeesAt(2, 4) == 1);
        pp->moveOrSwat(RIGHT);
        assert(andBoard.beeCount() == 2  &&  andBoard.numBeesAt(2, 4) == 0   &&  andBoard.numBeesAt(2, 5) == 0);
        andBoard.addBee(1, 3);
        assert(andBoard.beeCount() == 3  &&  andBoard.numBeesAt(1, 3) == 1);
        pp->moveOrSwat(UP);
        assert(andBoard.beeCount() == 2  &&  andBoard.numBeesAt(1, 3) == 0);
          // If the program crashes after leaving this compound statement, you
          // are probably messing something up when you delete a dead Bee
          // (or you have mis-coded the destructor).
          //
          // Draw a picture of your m_bees array before attcking
          // and also note the values of m_nBees or any other variables you
          // might have that are involved with the number of Bees.  Trace
          // through your code step by step as the Bees die and are
          // removed, updating the picture according to what the code says, not
          // what you want it to do.  If you don't see a problem then, try
          // tracing through the destruction of the room.
          //
          // If you execute the code, use the debugger to check on the values
          // of key variables at various points.  If you didn't try to learn
          // to use the debugger, insert statements that write the values of
          // key variables to cerr so you can trace the execution of your code
          // and see the first place where something has gone amiss.  (Comment
          // out the call to clearScreen in Room::display so that your output
          // doesn't disappear.)
    }
    cout << "Passed all basic tests" << endl;
}

int main()
{   
    doBasicTests(); // Remove this line after completing test.
    return 0; 
      // Create a game
      // Use this instead to create a mini-game:   
    //Game g(3, 4, 4);
    Game g(7, 8, 25);

      // Play the game
    g.play();
}

///////////////////////////////////////////////////////////////////////////
//  clearScreen implementation
///////////////////////////////////////////////////////////////////////////

// DO NOT MODIFY OR REMOVE ANYTHING BETWEEN HERE AND THE END OF THE FILE!!!
// THE CODE IS SUITABLE FOR VISUAL C++, XCODE, AND g++/g31 UNDER LINUX.

// Note to Xcode users:  clearScreen() will just write a newline instead
// of clearing the window if you launch your program from within Xcode.
// That's acceptable.  (The Xcode output window doesn't have the capability
// of being cleared.)

#ifdef _WIN32

#pragma warning(disable : 4005)
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
// #define byte win_byte
// #include <windows.h>
// #undef byte 

void clearScreen()
{
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(hConsole, &csbi);
    DWORD dwConSize = csbi.dwSize.X * csbi.dwSize.Y;
    COORD upperLeft = { 0, 0 };
    DWORD dwCharsWritten;
    FillConsoleOutputCharacter(hConsole, TCHAR(' '), dwConSize, upperLeft,
                                                        &dwCharsWritten);
    SetConsoleCursorPosition(hConsole, upperLeft);
}

#else  // not _WIN32

#include <iostream>
#include <cstring>
#include <cstdlib>

void clearScreen()  // will just write a newline in an Xcode output window
{
    static const char* term = getenv("TERM");
    if (term == nullptr  ||  strcmp(term, "dumb") == 0)
        cout << endl;
    else
    {
        static const char* ESC_SEQ = "\x1B[";  // ANSI Terminal esc seq:  ESC [
        cout << ESC_SEQ << "2J" << ESC_SEQ << "H" << flush;
    }
}

#endif

