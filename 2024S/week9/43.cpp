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
        	if(val) this -> input[0] = &t ;
            else this -> input[0] = &f ;
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
    }
    virtual bool output()
    {
        component[0]->input[0] = this->input[0];
        component[0]->input[1] = this->input[1];
        component[1]->input[0] = component[0];

        return component[1]->output();
    }
    virtual void setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }
    virtual void setValue(bool val, int pin)
    {
        if(val) setValue(&t, pin) ;
        else setValue(&f, pin) ;
    }

private:
    Gate *component[2];
};

class OR : public Gate
{
public:
    OR() : Gate()
    {
        component[0] = new NOT;
        component[1] = new NOR;
    }
    virtual bool output()
    {
        component[1]->input[0] = this->input[0];
        component[1]->input[1] = this->input[1];
        component[0]->input[0] = component[1];
        return component[0]->output();
    }
    virtual void setValue(Gate *gate, int pin) { this -> input[pin] = gate ; }
    virtual void setValue(bool val, int pin)
    {
        if(val) setValue(&t, pin) ;
        else setValue(&f, pin) ;
    }

private:
    Gate *component[2];
};

class XOR : public Gate
{
public:
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

private:
    Gate *component[5];
};

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
        Decoder2_4() : Decoder2_4(0) {}
        Decoder2_4(bool val)
        {
            if(val) this -> enable = &t ;
            else this -> enable = &f ;
            for(int i = 0 ; i < 2 ; i++)
                component[i] = new NOT ;
            for(int i = 2 ; i < 6 ; i++)
                component[i] = new AND ;
            for(int i = 0 ; i < 4 ; i++)
                enables[i] = new AND ;
        }
        virtual void setEnable(bool val)
        {
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
        }
        friend ostream &operator<<(ostream &out, Decoder2_4 dec)
        {
            for(int i = 3 ; i >= 0 ; i--)
                out << dec[i] -> output() << " " ;
            return out ;
        }
        virtual int output()
        {
            for(int i = 0 ; i < 4 ; i++)
                if(enables[i] -> output()) return i ;
            return -1;
        }
    private :
        Gate *component[6] ;
        Gate *enables[4] ;

        void _out()
        {
            component[2] -> input[0] = component[0] ;
            component[2] -> input[1] = component[1] ;

            component[3] -> input[0] = component[0] -> input[0] ;
            component[3] -> input[1] = component[1] ;

            component[4] -> input[0] = component[0] ;
            component[4] -> input[1] = component[1] -> input[0] ;

            component[5] -> input[0] = component[0] -> input[0] ;
            component[5] -> input[1] = component[1] -> input[0] ;

            for(int i = 0 ; i < 4 ; i++)
            {
                enables[i] -> input[0] = this -> enable ;
                enables[i] -> input[1] = component[i + 2] ;
            }
        }
} ;

class Decoder4_16 : public Decoder
{
public :
    Decoder4_16() : Decoder4_16(0) {}
    Decoder4_16(bool val) {
        this->setEnable(val);

        for (size_t i = 0; i < 5; ++i)
            dec2_4[i] = new Decoder2_4;
        
        dec2_4[4]->setEnable(this->enable);
    }
   
    virtual void setEnable(bool val) {
        if (val) this->enable = &t;
        else this->enable = &f;
    }
    virtual void setEnable(Gate *gate) { this->enable = gate; }
    virtual void setValue(bool val, int pin) {
        if (pin > 1) 
            dec2_4[4]->setValue(val, pin % 2);
        else 
            for (size_t i = 0; i < 4; ++i) 
                dec2_4[i]->setValue(val, pin);
    };

    virtual void setValue(Gate *gate, int pin) {
        if (pin > 1) 
            dec2_4[4]->setValue(gate, pin % 2);
        else 
            for(size_t i = 0; i < 4; ++i) 
                dec2_4[i]->setValue(gate, pin);
    };

    virtual Gate *operator[](int n) override {
        _out();
        if (n < 0 || n > 15) return nullptr;
        return (*dec2_4[n / 4])[n % 4];
    };
    
    friend ostream &operator<<(ostream &out, Decoder4_16 dec) {
        for (int i = 15; i >= 0; --i) {
            out << dec[i]->output() << " ";          
        }
        return out;
    }

    int output() {
        _out();
        int decToEnable = dec2_4[4]->output();
        int decToEnableOutput = dec2_4[decToEnable]->output();

        return decToEnable * 4 + decToEnableOutput;
    }
private :
    Decoder2_4 *dec2_4[5] ;

    void _out() {
        size_t i = 0;
        for (i = 0; i < 5; ++i)
            (*dec2_4[i])[0];

        int decToEnable = dec2_4[4]->output();

        for (i = 0; i < 4; ++i) {
            if (i == decToEnable) dec2_4[i]->setEnable(&t);
            else dec2_4[i]->setEnable(&f);
        }
    }
} ;


int main() {
    Decoder4_16 d(true);
    
    d.setValue(true, 0);
    d.setValue(true, 1);
    d.setValue(false, 2);
    d.setValue(false, 3);

    std::cout << d[15]->output() << std::endl;
    std::cout << d << std::endl;
    std::cout << d.output() << std::endl;

    return 0;
}
