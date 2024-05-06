class PokerCard
{
public:
  PokerCard(std::string s, int f)
  {
    suit = s;
    face = f;
  }

  int getFace() { return face; };
  std::string getSuit() { return suit; }

  friend std::ostream &operator<<(std::ostream &out, const PokerCard &p)
  {
    out<<"["<<p.face<<" of "<<p.suit<<"]";
    return out;
  }

  //Please finish the comparison operator override
  //compare face first, if the same then compare suit 
  //請完成比較運算子多載
  //先比較 face ， face 一樣再比較 suit
  //1 > 13 > 12 > 11 > 10 > 9 > 8 > 7 > 6 > 5 > 4 > 3 > 2
  //spade > heart > diamond > club
  bool operator>(PokerCard &b)
  {
    if (b.getFace() != getFace() )
    {
      if (getFace() == 1 )
        return true;
      else if (b.getFace() == 1)
        return false;
      
      return getFace() > b.getFace();
    }
    else 
    {
      // Compare suit
      return getSuit()[0] > b.getSuit()[0];
    }
  }
  bool operator<(PokerCard &b)
  {
    if ( *this == b )
      return false;
    else 
      return ! ( *this > b );
  }
  bool operator==(PokerCard &b)
  {
    return ( getFace() == b.getFace() && getSuit() == b.getSuit() );
  }

private:
    std::string suit;
    int face;
};