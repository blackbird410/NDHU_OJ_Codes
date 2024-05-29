#include <iostream>

class Gate
{
    public :
        Gate *input[2] ;
        virtual bool output() = 0 ;
  		void setValue(Gate *, int) ;
        void setValue(bool, int) ;
} ;

class TRUE : public Gate
{
    public :
        virtual bool output() { return 1 ; }
        void setValue(Gate *, int) {}
        void setValue(bool, int) {}
} ;

class FALSE : public Gate
{
    public :
        virtual bool output() { return 0 ; }
        void setValue(Gate *, int) {}
        void setValue(bool, int) {}
} ;

TRUE t ;
FALSE f ;

void Gate::setValue(bool val, int pin)
{
    if(val) this -> input[pin] = &t ;
    else this -> input[pin] = &f ;
}

void Gate::setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }

class NOT : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) ; }
        void setValue(bool val, int pin = 0)
        {
        	if(val) this -> input[0] = &t ;
            else this -> input[0] = &f ;
        }
        void setValue(Gate* gate, int pin = 0) { this -> input[0] = gate ; }
} ;

class NAND : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) || !(this -> input[1] -> output()) ; }
} ;

class NOR : public Gate
{
    public :
        virtual bool output() { return !(this -> input[0] -> output()) && !(this -> input[1] -> output()) ; }
} ;

class AND : public Gate
{
public :
  AND() : Gate() {
    component[0] = new NAND;
    component[1] = new NOT;
  }
  virtual bool output() {
    component[0] -> input[0] = this -> input[0];
    component[0] -> input[1] = this -> input[1];
    component[1] -> input[0] = component[0];

    return component[1]->output();
  }

private :
    Gate *component[2] ;
} ;

class OR : public Gate
{
public :
  OR() : Gate() {
    component[0] = new NOT;
    component[1] = new NOR;
  }
  virtual bool output() {
      component[1] -> input[0] = this -> input[0] ;
      component[1] -> input[1] = this -> input[1] ;
      component[0] -> input[0] = component[1] ;
      return component[0] -> output() ;
  }
private :
  Gate *component[2];
} ;

class XOR : public Gate
{
public :
  XOR() : Gate() {}
  virtual bool output() { return ((this->input[0]->output() && !this->input[1]->output()) 
                                  || ( !this->input[0]->output() && this->input[1]->output())); }
private :
    Gate *component[5] ;
} ;
/* Reference example
class XNOR : public Gate
{
    public :
        XNOR() : Gate()
        {
            component[0] = new NOT ;
            component[1] = new XOR ;
        }
        virtual bool output()
        {
            component[1] -> input[0] = this -> input[0] ;
            component[1] -> input[1] = this -> input[1] ;
            component[0] -> input[0] = component[1] ;
            return component[0] -> output() ;
        }
    private :
        Gate *component[2] ;
} ;
*/
