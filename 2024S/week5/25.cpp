#include <iostream>

class Location 
{
private:
  int street;
  int avenue;
public:
  Location() : street(0), avenue(0) {};
  Location( int _street, int _avenue) 
    :  street(_street), avenue(_avenue) 
  {};

  void setStreet( int _street ) { street = _street; };
  void setAvenue( int _avenue ) { avenue = _avenue; };
  int getStreet() { return street; };
  int getAvenue() { return avenue; };

  int sumStreetAvenue() { return street + avenue; };

  int operator-( const Location& other )
  {
    return abs(street - other.street) + abs( avenue - other.avenue );
  }

  Location &operator=( const Location& other)
  {
    street = other.street;
    avenue = other.avenue;
    return *this;
  }

  friend std::ostream &operator<<( std::ostream &out, const Location& p)
  {
    out << "(Street: " << p.street << ", " 
      << "Avenue: " << p.avenue << ")";
    
    return out;
  };

  friend std::istream &operator>>( std::istream &input, Location& p )
  {
    input >> p.street >> p.avenue;
    return input;
  }
};

class Grid 
{
private:
  int nStreets;
  int nAvenues;
  int nFriends;
  Location *friends;
public:
  Grid() {};
  Grid( int _nStreets, int _nAvenues, int _nFriends ) 
    : nStreets( _nStreets ), 
    nAvenues( _nAvenues ), 
    nFriends( _nFriends ),
    friends( new Location[nFriends] )
  {};
  ~Grid() 
  {
    delete[] friends;
  }

  Location meetingLocation()
  {
    int dim = ( nStreets > nAvenues ) ? nStreets : nAvenues;

    // Draw a grid 
    // Find the distance of every friend to every point on the grid
    // The best location will be the one that gives the minimum distance for every one 
    int *distances = new int[ (dim + 1) * (dim + 1)];
    int minDistance = -1, distance = 0;
    Location bestLocation;
    size_t i = 0, j = 0, k = 0;

    for ( i = 0; i < (dim + 1) * (dim + 1); ++i)
      distances[i] = 0;

    // Compute the distance for each friend to every location on the Grid
    for ( i = 0; i < nFriends; ++i )
      for ( j = 1; j <= dim ; ++j )
        for ( k = 1; k <= dim; ++k )
          distances[ j * dim + k ] += abs(friends[i].getStreet() - j) + abs(friends[i].getAvenue() - k);
    
    // Find the minimum distance
    std::pair<int, int> location;
    for (j = 1; j <= dim; ++j )
    {
      for ( k = 1; k <= dim; ++k )
      {
        if (minDistance == -1 || distances[ j * dim + k ] < minDistance )
        {
          minDistance = distances[ j * dim + k ];
          location = {j, k};
        } else if ( minDistance == distances[ j * dim + k ] && std::make_pair<int, int>(j, k) < location)
          location = {j, k};
      }
    }

    delete[] distances;

    bestLocation = Location(location.first, location.second);

    return bestLocation;
  }

  friend std::istream &operator>>( std::istream &input, Grid& g )
  {
    for ( size_t i = 0; i < g.nFriends; ++i )
      input >> g.friends[i];

    return input;
  }

  friend std::ostream &operator<<( std::ostream &out, const Grid& g)
  {
    for ( size_t i = 0; i < g.nFriends; ++i )
        out << g.friends[i] << std::endl;
    return out;
  }

};

int main()
{
  size_t testCases = 0;
  int nStreets = 0, nAvenues = 0, nFriends = 0;
  Grid *city;

  std::cin >> testCases;
  testCases++;
  
  while (--testCases) 
  {
    std::cin >> nStreets >> nAvenues >> nFriends;
    city = new Grid(nStreets, nAvenues, nFriends);
    std::cin >> *city;
    std::cout << city->meetingLocation() << std::endl;
    delete city;
  }

  return 0;
}
