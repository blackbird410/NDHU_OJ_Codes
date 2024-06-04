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

class Mux
{
    public :
        virtual void setData(bool, int) = 0 ;
        virtual void setData(Gate *, int) = 0 ;
        virtual void setSelect(bool, int) = 0 ;
        virtual void setSelect(Gate *, int) = 0 ;
        virtual void setEnable(bool) = 0 ;
        virtual void setEnable(Gate *) = 0 ;
        virtual Gate *output() = 0 ;
    protected :
        Gate *enable ;
} ;

class Mux2_1 : public Mux
{
    public :
        Mux2_1() : Mux2_1(0) {}
        Mux2_1(bool val)
        {
            if(val) this -> enable = &t ;
            else this -> enable = &f ;
            component[0] = new AND ;
            component[1] = new AND ;
            component[2] = new NOT ;
            component[3] = new OR ;
            component[4] = new AND ;
        }
        virtual void setData(bool val, int pin)
        {
            switch(pin)
            {
                case 0 : component[0] -> setValue(val, 0) ; break ;
                case 1 : component[1] -> setValue(val, 0) ; break ;
                default : ;
            }
        }
        virtual void setData(Gate *gate, int pin)
        {
            switch(pin)
            {
                case 0 : component[0] -> setValue(gate, 0) ; break ;
                case 1 : component[1] -> setValue(gate, 0) ; break ;
                default : ;
            }
        }
        virtual void setEnable(bool val)
        {
            if(val) this -> enable = &t ;
            else this -> enable = &f ;
        }
        virtual void setEnable(Gate *gate)
        {
            this -> enable = gate ;
        }
        virtual void setSelect(bool val, int pin = 0)
        {
            component[1] -> setValue(val, 1) ;
            component[2] -> setValue(val, 0) ;
            component[0] -> input[1] = component[2] ;
        }
        virtual void setSelect(Gate *gate, int pin = 0)
        {
            component[1] -> setValue(gate, 1) ;
            component[2] -> setValue(gate, 0) ;
            component[0] -> input[1] = component[2] ;
        }
        virtual Gate *output()
        {
            component[3] -> setValue(component[0], 0) ;
            component[3] -> setValue(component[1], 1) ;
            component[4] -> setValue(this -> enable, 0) ;
            component[4] -> setValue(component[3], 1) ;
            return component[4] ;
        }
    private :
        Gate *component[5] ;
} ;

class Mux4_1 : public Mux
{
public :
    Mux4_1() : Mux4_1(0) {}
    Mux4_1(bool val) {
        setEnable(val);

        mux2_1[0] = new Mux2_1;
        mux2_1[1] = new Mux2_1;

        component[0] = new NOT;
        component[1] = new AND;

        mux2_1[0]->setEnable(this->enable);
        mux2_1[1]->setEnable(this->enable);
    }
    virtual void setData(bool val, int pin) override {
        mux2_1[(pin / 2) % 2]->setData(val, pin % 2);
    }
    virtual void setData(Gate *gate, int pin) override {
        mux2_1[(pin / 2) % 2]->setData(gate, pin % 2);
    }
    virtual void setSelect(bool val, int pin) override {
        // S0 => mux2_1 && S1 => which output 
        if (!pin) {
            mux2_1[0]->setSelect(val, 0);
            mux2_1[1]->setSelect(val, 0);
        }
        else 
            component[0]->setValue(val, 0);
    }
    virtual void setSelect(Gate *gate, int pin) override {
        if (!pin) {
            mux2_1[0]->setSelect(gate, 0);
            mux2_1[1]->setSelect(gate, 0);
        }
        else 
            component[0]->setValue(gate, 0);
    }
    virtual void setEnable(bool val) override {
        if (val) this->enable = &t;
        else this->enable = &f;
    }
    virtual void setEnable(Gate *gate) override { this->enable = gate; }
    virtual Gate *output() override {
        component[1]->setValue(this->enable, 0);
        if (component[0]->output()) {
            component[1]->setValue(mux2_1[0]->output(), 1);
        } else {
            component[1]->setValue(mux2_1[1]->output(), 1);
        }
        return component[1];
    }
private :
    Mux *mux2_1[2] ;
    Gate *component[3] ;
} ;

class XOR_dev {
public:
    XOR_dev() : XOR_dev(0) {};
    XOR_dev(bool val) {
        if(val) this->enable = &t;
        else this->enable = &f;
        m = new Mux4_1(val);

        // Setting the inputs as constant
        m->setData(false, 0);
        m->setData(true, 1);
        m->setData(true, 2);
        m->setData(false, 3);
    };

    virtual void setData(bool val, int pin) { m->setSelect(val, pin % 2); };
    virtual void setData(Gate * gate, int pin) { m->setSelect(gate, pin % 2); };
    virtual void setEnable(bool val) { 
        if(val) this->enable = &t;
        else this->enable = &f;
        m->setEnable(this->enable);
    };
    virtual void setEnable(Gate *gate) { 
        this->enable = gate;
        m->setEnable(this->enable); 
    };
    virtual Gate *output() {
        return m->output();
    }

    friend std::ostream& operator<<(std::ostream& out, XOR_dev x) {
        out << x.output()->output();
        return out;
    }
private:
    Mux4_1 *m;
    Gate* enable;
};

int main() {
    XOR_dev x(true);
    bool a, b;
    std::cin >> a >> b;

    x.setData(a, 0);
    x.setData(b, 1);

    std::cout << x << std::endl;

    return 0;
}
