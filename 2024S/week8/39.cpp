#include <algorithm>
#include <cstddef>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

class Train {
	public:
		class Node {
			public:
				Node () : data(0), next(nullptr) {};
				Node(int d) : data(d), next(nullptr) {};
				Node(Node* n) : data(n->getData()), next(n->getNext()) {};
				Node(int d, Node* _next) : data(d), next(_next) {};
				int getData() const { return data; };
				Node *getNext() const { return next; };
				void setNext(Node* n) { next = n; }
				int data;
				Node* next;

				friend std::ostream& operator<<( std::ostream& out, Node* l) {
					out << l->getData();
					return out;
				};
		};

		Train() : head(nullptr) {};
		~Train() {
			Node *temp = getHead();
			while (temp) {
				head = temp->getNext();
				delete temp;
				temp = head;
			}
		};

		Node* getHead() const { return head; };
		void setHead( Node* n ) { head = n; }
		size_t getSize() const {
			size_t s = 0;
			Node *temp = getHead();
			while (temp != nullptr) {
				++s;
				temp = temp->getNext();
			}
			return s;
		};

		Node* getTail() const {
			if (!getSize()) return nullptr;

			Node *temp = getHead();
			while (temp->getNext() != nullptr) {
				temp = temp->getNext();
			}
			return temp;
		};

		bool addFromHead(int d) {
			if (head == nullptr) setHead(new Node(d));
			
			// Add in weight priority order
			if (d <= head->getData()) return false;

			Node* newNode = new Node(d, head);
			setHead(newNode);

			return true;
		};

		bool addFromTail(int d) {
			if (head == nullptr) setHead(new Node(d));
			if (d >= head->getData()) return false;

			Node* newNode = new Node(d);
			Node* temp = getHead();
			while (temp->getNext() != nullptr && temp->getData() > d) {
				temp = temp->getNext();
			}

			if (temp->getData() <= d) {
				delete newNode;
				return false;
			}

			temp->setNext(newNode);
			return true;
		};

		bool addCar(int weight) {
			if (!head || head->getData() < weight) return addFromHead(weight);
			else return addFromTail(weight);
		}

		friend std::ostream& operator<<(std::ostream& out, Train* l) {
            if (!l->getHead()) return out;
            Node* temp = l->getHead();
            while (temp != nullptr) {
                out << temp << (temp->getNext() ? " => " : "");
                temp = temp->getNext();
            }
            return out;
        }
	private:
			Node *head;
};

class TrainManager {
	private:
		std::vector<Train*> trains;
		std::vector<int> carWeights;
	public:
		TrainManager() {};
		~TrainManager() {
			for ( auto* t: trains) {
				delete t;
			}
		};

		std::vector<Train*> getTrains() { return trains; };

		void add(Train* t) {
			trains.push_back(t);
		};

		void inputCarWeights(int nTrain) {
			int carWeight = 0;
			do {
				std::cin >> carWeight;
				carWeights.push_back(carWeight);
			} while (--nTrain > 0);
		};

		void buildPossibleTrains() {
			// Build the first train and keep of record of the cars you did not add 
			// Build each train starting at a different car position
			//std::vector<int> unaddedCars;
			Train* possibleTrain;
			for ( const int& car: carWeights ) {
				possibleTrain = new Train;
				for( const int& c: carWeights) {
					possibleTrain->addCar(c);
				}
				this->add(possibleTrain);
			};
		};

		Train* getLongestTrain() {
			buildPossibleTrains();
			
			if (trains.empty()) return nullptr;
			return *std::max_element(trains.begin(), trains.end(), [](Train* a, Train* b) {
					return a->getSize() < b->getSize();
					});
		};

		void cleanStation() {
            for (Train* t : trains) {
                delete t;
            }
            trains.clear();
            carWeights.clear();
        }
		friend std::ostream& operator<<( std::ostream& out, const TrainManager manager) {
			for( const auto& t: manager.trains) {
				out << t << std::endl;
			}
			return out;
		}
};

void test() {
	std::srand( std::time(0) );
	TrainManager erin;
	Train *t; 

	for( size_t i = 0; i < 10; ++i) {
		t = new Train();
		for (size_t j = 0; j < 2000; ++j) {
			t->addCar(rand() % 10000);
		}
		erin.add(t);
	}
	std::cout << erin.getLongestTrain() << std::endl;
}

int main() {
	//test();
	int testCases = 0;
	int nCars = 0;
	TrainManager erin;
	
	std::cin >> testCases;
	while (testCases > 0) {
		std::cin >> nCars;
		erin.inputCarWeights(nCars);
		std::cout << erin.getLongestTrain()->getSize() << std::endl;
		erin.cleanStation();
		testCases--;
	}

	return 0;
}
