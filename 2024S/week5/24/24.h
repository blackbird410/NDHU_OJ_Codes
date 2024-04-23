#ifndef CUSTOMER_SUPPORT_h
#define CUSTOMER_SUPPORT_h

class Topic 
{
private:
  int id;
  int nRequests;
  int elapsedTime; // Can be 0
  int serviceTime;
  int delayTime;
  int totalTime;
public:
  Topic() {};
  Topic(int _id, int _nRequests, int _elapsedTime, int _serviceTime, int _delayTime) 
    : id( _id > 0 
         ? _id 
         : throw std::invalid_argument("Invalid identifier.")), 
    nRequests( _nRequests > 0 
              ? _nRequests 
              : throw std::invalid_argument("Invalid number of requests.")), 
    elapsedTime( _elapsedTime >= 0 
                ? _elapsedTime 
                : throw std::invalid_argument("Invalid value for elapsed time for request reception.")), 
    serviceTime( _serviceTime > 0 
                ? _serviceTime 
                : throw std::invalid_argument("Invalid service time value.")), 
    delayTime( _delayTime > 0 
              ? _delayTime 
              : throw std::invalid_argument("Invalid time value between successive requests.")), 
    totalTime( elapsedTime + serviceTime + delayTime ) 
  {};

  ~Topic() {}

  int getId() { return id; };
  int getNrequest() { return nRequests; };
  int getElapsedTime() { return elapsedTime; };
  int getServiceTime() { return serviceTime; };
  int getDelayTime() { return delayTime; };
  int getTotalTime() { return totalTime; };

  void setNrequests(int n) { nRequests = n; };

  friend std::istream &operator>>( std::istream &input, Topic& t )
  {
    int temp[5], i = -1;
    while (++i < 5)
      input >> temp[i];
    t = Topic(temp[0], temp[1], temp[2], temp[3], temp[4]);
    return input;
  }

  friend std::ostream &operator<<( std::ostream &out, const Topic& t )
  {
    out << t.id << " " << t.nRequests << " " << t.elapsedTime << " " << t.serviceTime << " " << t.delayTime << " ";
    return out;
  }

};

class Personel 
{
private:
  int id;
  int nTopics;
  int *topics;
  // int lastRequestTime;
  int delay; // The difference between the time taken to complete a request by this person and the first person in the list of personel
public:
  Personel() {};
  Personel(int _id, int _nTopics) 
    : id(_id > 0 
         ? _id : throw std::invalid_argument("Invalid personel identifier.")), 
    nTopics(_nTopics > 0 
            ? _nTopics : throw std::invalid_argument("Invalid number of topics.")), 
    topics( new int[nTopics]), 
    delay(0) 
  {};

  ~Personel() 
  {
    delete[] topics; 
  }

  void setId( int _id ) 
  { 
    id = _id > 0 
      ? _id : throw std::invalid_argument("Invalid personel identifier.");
  };

  void setNtopics( int _nTopics )
  {
    nTopics = _nTopics > 0 
      ? _nTopics : throw std::invalid_argument("Invalid number of topics.");
  };

  void setDelay(int d) { delay = d; };

  int getId() { return id; };
  int getNtopics() { return nTopics; };

  friend std::istream &operator>>( std::istream &input, Personel& p )
  {
    input >> p.id >> p.nTopics;
    p.topics = new int[p.nTopics];
    for (size_t i = 0; i < p.nTopics; ++i )
      input >> p.topics[i];

    return input;
  };

  friend std::ostream &operator<<( std::ostream &out, const Personel& p )
  {
    out << p.id <<  " " << p.nTopics << " ";
    for ( size_t i = 0; i < p.nTopics; ++i)
      out << p.topics[i] << " ";

    return out;
  }

};

#endif // !CUSTOMER_SUPPORT_h
