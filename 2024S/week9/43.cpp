#include <iostream>
using namespace std;

class Gate
{
    public :
        Gate *input[2] ;
        virtual bool output() = 0 ;
	virtual void setValue(Gate *, int) = 0 ;
        virtual void setValue(bool, int) = 0 ;
} ;

class TRUE : public Gate
{
    public :
        bool output() { return 1 ; }
        virtual void setValue(Gate *, int) {}
        virtual void setValue(bool, int) {}
} ;

class FALSE : public Gate
{
    public :
        bool output() { return 0 ; }
        virtual void setValue(Gate *, int) {}
        virtual void setValue(bool, int) {}
} ;

TRUE t ;
FALSE f ;

class NOT : public Gate
{
    public :
        bool output() { return !(this -> input[0] -> output()) ; }
        virtual void setValue(bool val, int pin = 0)
        {
			if(val) 
				this -> input[0] = &t ;
			else 
				this -> input[0] = &f ;
        }
        virtual void setValue(Gate* gate, int pin = 0) { this -> input[0] = gate ; }
} ;

class NAND : public Gate
{
public :
  bool output() { return !(this -> input[0] -> output()) || !(this -> input[1] -> output()) ; }
  virtual void setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }
  virtual void setValue(bool val, int pin)
  {
      if(val) setValue(&t, pin) ;
      else setValue(&f, pin) ;
  }
} ;

class NOR : public Gate
{
    public :
        bool output() { return !(this -> input[0] -> output()) && !(this -> input[1] -> output()) ; }
        virtual void setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }
        virtual void setValue(bool val, int pin)
        {
            if(val) setValue(&t, pin) ;
            else setValue(&f, pin) ;
        }
} ;

class AND : public Gate
{
public:
    AND() : Gate()
    {
        component[0] = new NAND;
        component[1] = new NOT;
		component[1]->setValue(component[0], 0);
    }
    virtual bool output()
    {
        component[0]->input[0] = this->input[0];
        component[0]->input[1] = this->input[1];

        return component[1]->output();
    }

  virtual void setValue(Gate *gate, int pin) { 
	this->component[0]->input[pin] = gate;
  }
  virtual void setValue(bool val, int pin)
  {
      if(val) setValue(&t, pin) ;
      else setValue(&f, pin) ;
  }
private :
  Gate *component[2] ;
} ;

class OR : public Gate
{
public:
  OR() : Gate()
  {
      component[0] = new NOT;
      component[1] = new NOR;
      component[0]->setValue(component[1], 0);
  }
  virtual bool output()
  {
      component[1]->input[0] = this->input[0];
      component[1]->input[1] = this->input[1];
      return component[0]->output();
  }

  virtual void setValue(Gate *gate, int pin = 0) { this -> input[pin] = gate ; }
  virtual void setValue(bool val, int pin = 0)
  {
      if(val) setValue(&t, pin) ;
      else setValue(&f, pin) ;
  }

private :
  Gate *component[2] ;
} ;

class XOR : public Gate
{
public :
  XOR() : Gate() {}
  virtual bool output()
  {
      return ((this->input[0]->output() && !this->input[1]->output()) || (!this->input[0]->output() && this->input[1]->output()));
  }
  virtual void setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }
  virtual void setValue(bool val, int pin)
  {
      if(val) setValue(&t, pin) ;
      else setValue(&f, pin) ;
  }
private :
    Gate *component[5] ;
} ;

class Decoder
{
    public :
        virtual void setValue(bool, int) = 0 ;
        virtual void setValue(Gate *, int) = 0 ;
        virtual void setEnable(bool) = 0 ;
        virtual void setEnable(Gate *) = 0 ;
        virtual int output() = 0 ;
        virtual Gate *operator[](int) = 0 ;
    protected :
        Gate *enable ;
} ;

class Decoder2_4 : public Decoder
{
    public :
        Decoder2_4() : Decoder2_4(0) {} // Calls another constructor to initialize the object but, not enabled
        Decoder2_4(bool val)
        {
            if(val) this -> enable = &t ;
            else this -> enable = &f ;

			// Initialize the object with 2 NOT component for having all the combination of signal input such as
			//  1 1 , 1 0, 0 1 and 0 0
            for(int i = 0 ; i < 2 ; i++)
                component[i] = new NOT ;

			// Initialize 4 AND components because every output gate will be enabled only if it receive 1 and 1 after the input
			// signals have been converted by the NOT gates if necessary
            for(int i = 2 ; i < 6 ; i++)
                component[i] = new AND ;

			// 4 AND gates to decide which output gate will be enabled	
			// Only 1 can be enabled at a time in a dec4_16
            for(int i = 0 ; i < 4 ; i++)
                enables[i] = new AND ; 
			// All output gate are not enabled when initialized, 
			// they will be linked later with this decoder enabled status 
			// and will be enabled automatically when the decoder is enabled
        }
        virtual void setEnable(bool val)
        {
			// Uses the TRUE and FALSE gates to set the enabled state of a dec2_4
			// We cannot add a boolean as value for a gate input 
			// But in the following dec4_16	we can, because when sending the boolean parameter, under the hood a gate will be assigned instead
            if(val) this -> enable = &t ;
            else this -> enable = &f ;
        }
        virtual void setEnable(Gate *gate) { this -> enable = gate ; }
        virtual void setValue(Gate *gate, int i) { component[i % 2] -> input[0] = gate ; }
        virtual void setValue(bool val, int i)
        {
            if(val) component[i % 2] -> input[0] = &t ;
            else component[i % 2] -> input[0] = &f ;
        }
        virtual Gate *operator[](int n)
        {
            _out() ;
            switch(n)
            {
                case 0 : return enables[0] ;
                case 1 : return enables[1] ;
                case 2 : return enables[2] ;
                case 3 : return enables[3] ;
                default : return nullptr ;
            }
			// Could have we just done the following instead ?
			// return (n < 0 || n > 3) ? nullptr : enables[n];
        }
        friend ostream &operator<<(ostream &out, Decoder2_4 dec)
        {
			// Displays from the last gate to the first its enabled status
            for(int i = 3 ; i >= 0 ; i--)
                out << dec[i] -> output() << " " ;
            return out ;
        }
        virtual int output()
        {
			// What does this one do ? 
			// It returns the index of the current enabled output gate
            for(int i = 0 ; i < 4 ; i++)
                if(enables[i] -> output()) return i ;
			return -1;
        }
    private :
        Gate *component[6] ;
        Gate *enables[4] ;

        void _out()
        {
			// How about this one ?
			// Because we need different combination of the signal for each output gate,
			// therefore using the NOT gates here we will initialize the combination of signal 
			// for each component to be enabled

			// Here 0 0 => 1 1 => activated
            component[2] -> input[0] = component[0] ;
            component[2] -> input[1] = component[1] ;

			// Here 1 0 => 1 1 => activated
            component[3] -> input[0] = component[0] -> input[0] ;
            component[3] -> input[1] = component[1] ;

			// Here 0 1 => 1 1 => activated
            component[4] -> input[0] = component[0] ;
            component[4] -> input[1] = component[1] -> input[0] ;

			// Here 1 1 => 1 1 => activated because here we do not use any output of the NOT gates to convert the input signal
            component[5] -> input[0] = component[0] -> input[0] ;
            component[5] -> input[1] = component[1] -> input[0] ;

            for(int i = 0 ; i < 4 ; i++)
            {
				// What are we doing here ?
				// For each output gate, we set the input as the enabled status of the dec2_4
				// Why ???
				// Because if this dec2_4 is enabled, all of its output gates needs to be enabled also ??
				// But after doing this, how would we know which output gate is correct for an specific input signal ??
				// Is it like we activate each output gate and when the output is needed it can work ?
				// So, automatically when the decoder is enabled, all of its output gates will be enabled simultaneously
                enables[i] -> input[0] = this -> enable ;

				// Here we set the second input as the different combination for the input signal
				// This part up there make sense because we use AND gates for all the output gates,
				// meaning that an output gates will be enabled when it receives the corresponding input signal for 
				// its activation and when the decoder is enabled 
				// Therefore when the decoder is activated, 
				// the only condition that is left for an output to be activated is its own input signal
                enables[i] -> input[1] = component[i + 2] ;
            }
        }
} ;

class Decoder4_16 : public Decoder
{
public :
  Decoder4_16() : Decoder4_16(0) {
	  // We alse use another constructor to initialize the decoder state
	  // But it is not enabled by default 
  }
  Decoder4_16(bool val) {
    // Initialize it with 5 dec2_4
	// The last one will be the main decoder which used to know which sub decoder to enable based of i3 and i4
	size_t i = 0;
    for(i = 0; i < 5; ++i) 
      dec2_4[i] = new Decoder2_4;

	// As we did previously in the implementation of the Decoder2_4, we need all the sub decoder to be 
	// half activated when initialized, so we will linked all of them to the enabled status of the main decoder
	// But this dec4_16 is also a Decoder, it has it own enable gate, but using the last decoder as the main decoder, 
	// should we not link them together ??
	// Meaning that the enabled status of the main decoder will also be the enabled status of this dec4_16
	// Yes, but how do we do that ?
	dec2_4[4]->setEnable(this->enable);
	// Now because when initializing a Decoder2_4, all of its output gates are linked to its own enabled status 
	// The only thing left to do is to link all the sub decoder's enabled state to the main decoder
	// so that when it is enabled, all of them will be half enabled
	// And a sub decoder will be enabled if it corresponds to the output signal of the main decoder 
	// How do we do that ? Do what ?
	// Use the output of the main decoder to enable the right sub decoder 
	// You will need to assign as we did previously, the right activation  combination for each decoder
	// Really ? Isn't there a better way ? Seems like you are repeating yourself 
	// Let's see, the main decoder based on the input signal it receives will have a specific output gate enabled right ?
	// So we could map this specific output index to a sub decoder 
	// For example when it receive a signal of 0 0, the first output gate will be enabled, 
	// in this case we can just activate the first sub decoder 
	// 0 0 enables decoder 0
	// 1 0 enables decoder 1 
	// 0 1 enables decoder 2
	// 1 1 enables decoder 3
	// So we could do it like this :
	// 1) Get the output of the main decoder
	// 2) Activate the sub decoder corresponding to the output index 
  }
  virtual void setEnable(bool val) { 
    if (val)  this->enable = &t;
    else this->enable = &f;
    // this->enable = (val) ? &t : &f; Why can't we use this ??? 
  }
  virtual void setEnable(Gate *gate) { this->enable = gate; }
  virtual void setValue(bool val, int pin) {
    // dec2_4[4] is the main Decoder2_4
	// i3 and i4 goes to the main dec2_4
	// i0 and i1 => all the sub dec2_4
	
    if (pin > 1) {
      dec2_4[4]->setValue(val, pin - 2);
      // Based on the output of the main dec2_4, we enable the correct output and disable all the others
	  size_t decToEnable = dec2_4[4]->output();
	  for (size_t i = 0; i < 4; ++i) { 
		  if (i == decToEnable) dec2_4[i]->setEnable(true);
		  else dec2_4[i]->setEnable(false);
	  } 
    } else {
      for(size_t i = 0; i < 4; ++i)
        dec2_4[i]->setValue(val, pin);
    }

  }
  virtual void setValue(Gate *gate, int pin) {
	  if (pin > 1) {
		  dec2_4[4]->setValue(gate, pin % 2);
		  size_t decToEnable = dec2_4[4]->output();
		  for (size_t i = 0; i < 4; ++i) { 
			  if (i == decToEnable) dec2_4[i]->setEnable(true);
			  else dec2_4[i]->setEnable(false);
		  } 
	  } else {
		  for (size_t i = 0; i < 4; ++i) {
			  dec2_4[i]->setValue(gate, pin);
		  }
	  }
  }
  virtual Gate *operator[](int n) {
    // Returns the wanted output gate according to n 

	  if (n < 0 || n > 3) return nullptr;
	  
	  _out();
	  if (dec2_4[4]->output() == n) return &t;
	  else return &f;
  }

  friend ostream &operator<<(ostream &out, Decoder4_16 dec) {
    // Returns the value of all the dec2_4
    for (size_t i = 0; i < 4; ++i) {
      Decoder2_4* d = dec.dec2_4[i];
      out << *d << std::endl;
    }
    return out;
  }
  int output() {
    // Returns the corresponding value of the output gate between 0~15
    
    // Find which dec2_4 is enabled
    size_t i = dec2_4[4]->output();
    return (3 - i) * 4 + i;
  }
private :
  Decoder2_4 *dec2_4[5] ;

  void _out() {
	  // Here we will link the output gates of the main decoder to the sub decoders enabled status 
	  // Which means that when the output signal of the main decoder is for example 0
	  // Then the decoder 0 will be activated automatically
	  
	  int decoderToEnable = dec2_4[4]->output();
	  for (size_t i = 0; i < 4; ++i) {
		  // Activate the decoder corresponding to the output of the main decoder and disable the others
		  if (i == decoderToEnable) dec2_4[i]->setEnable(true);
		  else dec2_4[i]->setEnable(false);
	  }
  }
} ;

void test(int whichDecoder = 0) {
	if (whichDecoder) {
	  Decoder4_16 d;
	  d.setEnable(true);

	  d.setValue(true, 0);
	  d.setValue(true, 1);
	  d.setValue(false, 2);
	  d.setValue(false, 4);

	  std::cout << d << std::endl;
	  // std::cout << d.output() << std::endl;
	} else {
		Decoder2_4 d;
		d.setEnable(true);

		d.setValue(false, 0);
		d.setValue(false, 1);
		std::cout << d << std::endl;
		std::cout << "Output gate: " << d.output() << std::endl;

		d.setValue(true, 0);
		d.setValue(false, 1);
		std::cout << d << std::endl;
		std::cout << "Output gate: " << d.output() << std::endl;

		d.setValue(false, 0);
		d.setValue(true, 1);
		std::cout << d << std::endl;
		std::cout << "Output gate: " << d.output() << std::endl;

		d.setValue(true, 0);
		d.setValue(true, 1);
		std::cout << d << std::endl;
		std::cout << "Output gate: " << d.output() << std::endl;
	}
}

int main() {
	int choice = 0;
	std::cout << "Choose: " << std::endl;
	std::cin >> choice; 
	test(choice);
}
