#include <iostream>
#include <cstdio>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

#define SIZE 1000
char *convertToDifferentBase(int dec, int base, char *result);
std::vector<string> getBins();

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

class Adder
{
public:
    virtual void setValue(bool, int) = 0;
    virtual void setValue(Gate *, int) = 0;
    virtual Gate *sum() = 0;
    virtual Gate *carryOut() = 0;
};

class OneBitHalfAdder : public Adder
{
public:
    OneBitHalfAdder()
    {
        component[0] = new XOR;
        component[1] = new AND;
    }
    virtual void setValue(bool val, int pin)
    {
        if (val)
        {
            component[0]->setValue(&t, pin);
            component[1]->setValue(&t, pin);
        }
        else
        {
            component[0]->setValue(&f, pin);
            component[1]->setValue(&f, pin);
        }
    }

    virtual void setValue(Gate *gate, int pin)
    {
        component[0]->input[pin] = gate;
        component[1]->input[pin] = gate;
    }

    virtual Gate *sum()
    {
        return component[0];
    }
    virtual Gate *carryOut()
    {
        return component[1];
    }

private:
    Gate *component[2];
};

class OneBitFullAdder : public Adder
{
public:
    OneBitFullAdder()
    {
        a[0] = new OneBitHalfAdder;
        a[1] = new OneBitHalfAdder;
        carry = new OR;
    }

    virtual void setValue(bool val, int pin)
    {
        if (pin < 2)
            a[0]->setValue(val, pin);
        else
            a[1]->setValue(val, 1);

        a[1]->setValue(a[0]->sum(), 0);
        carry->setValue(a[0]->carryOut(), 0);
        carry->setValue(a[1]->carryOut(), 1);
    }

    virtual void setValue(Gate *gate, int pin)
    {
        if (pin < 2)
            a[0]->setValue(gate, pin);
        else
            a[1]->setValue(gate, 1);

        a[1]->setValue(a[0]->sum(), 0);
        carry->setValue(a[0]->carryOut(), 0);
        carry->setValue(a[1]->carryOut(), 1);
    }

    virtual Gate *sum()
    {
        return a[1]->sum();
    }

    virtual Gate *carryOut()
    {
        return carry;
    }

private:
    Adder *a[2];
    Gate *carry;
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
        bool isEnabled() {
            return this->enable->output();
        }
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
        for (size_t i = 0; i < 4; ++i)
            enables[i] = new AND; 
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
    Decoder2_4 *dec2_4[5];
    Gate* enables[4];

    void _out() {
        size_t i = 0;
        int decToEnable = 0;

        dec2_4[4]->setEnable(this->enable);

        for (i = 0; i < 4; ++i) 
            if ((*dec2_4[4])[i]->output()) decToEnable = i;

        for (i = 0; i < 4; ++i) {
            enables[i]->input[0] = this->enable;
            
            if (i == decToEnable) enables[i]->input[1] = &t;
            else enables[i]->input[1] = &f;

            dec2_4[i]->setEnable(enables[i]);
        }
    }
} ;


class FourBitsRippleAdder : public Adder
{
public:
    FourBitsRippleAdder() {
        for (size_t i = 0; i < 4; ++i)
            fullAdder[i] = new OneBitFullAdder;
        setValue(false, 8);
    }

    virtual void setValue(bool val, int pin) {
        // Has 12 pins from top to bottom
        // fullAdder[pin / 3]->setValue(val, pin % 3);

        switch (pin)
        {
            case 0: fullAdder[0]->setValue(val, 0); break;
            case 1: fullAdder[0]->setValue(val, 1); break;
            case 2: fullAdder[1]->setValue(val, 0); break;
            case 3: fullAdder[1]->setValue(val, 1); break;
            case 4: fullAdder[2]->setValue(val, 0); break;
            case 5: fullAdder[2]->setValue(val, 1); break;
            case 6: fullAdder[3]->setValue(val, 0); break;
            case 7: fullAdder[3]->setValue(val, 1); break;
            case 8: fullAdder[3]->setValue(val, 2); break;
            default: break;
        }
    }

    virtual void setValue(Gate* gate, int pin) {
        switch (pin)
        {
            case 0: fullAdder[0]->setValue(gate, 0); break;
            case 1: fullAdder[0]->setValue(gate, 1); break;
            case 2: fullAdder[1]->setValue(gate, 0); break;
            case 3: fullAdder[1]->setValue(gate, 1); break;
            case 4: fullAdder[2]->setValue(gate, 0); break;
            case 5: fullAdder[2]->setValue(gate, 1); break;
            case 6: fullAdder[3]->setValue(gate, 0); break;
            case 7: fullAdder[3]->setValue(gate, 1); break;
            case 8: fullAdder[3]->setValue(gate, 2); break;
            default: break;
        }
    }

    virtual Adder* operator[](int n) {
        _out();
        if (n < 0 || n > 3) return nullptr;
        return fullAdder[n];
    }

    virtual Gate* sum() override {
        return fullAdder[0]->sum();
    };

    virtual Gate* carryOut() override {
        return fullAdder[0]->carryOut();
    };

    friend std::ostream& operator<<(std::ostream& out, FourBitsRippleAdder f) {
        out << f[0]->carryOut()->output() << " ";
        for (size_t i = 0; i < 4; ++i) 
            out << f[i]->sum()->output() << " ";
        return out;
    }

private:
    OneBitFullAdder* fullAdder[4];

    void _out() {
        // The smaller digit's carryOut becomes the larger digit's carryIn
        for (int i = 2; i >= 0; i--) {
            fullAdder[i]->setValue(fullAdder[i+1]->carryOut(), 2);
        }
    }
} ;

class Decoder5_32 : public Decoder {
public:
    Decoder5_32() : Decoder5_32(0) {};
    Decoder5_32(bool val) {
        this->setEnable(val);
        
        dec4_16[0] = new Decoder4_16;
        dec4_16[1] = new Decoder4_16;
        enables[0] = new AND;
        enables[1] =  new AND;
        switchDecoder = new NOT;
    }

    virtual void setEnable(bool val) override {
        if (val) this->enable = &t;
        else this->enable = &f;
    }

    virtual void setEnable(Gate* gate) override { this->enable = gate; }

    virtual void setValue(bool val, int pin) override {
        if (pin < 4) {
            dec4_16[0]->setValue(val, pin);
            dec4_16[1]->setValue(val, pin);
        } else {
            if (val) switchDecoder->input[0] = &t;
            else switchDecoder->input[0] = &f;
        }
    }

    virtual void setValue(Gate* gate, int pin) override {
        if (pin < 4) {
            dec4_16[0]->setValue(gate, pin);
            dec4_16[1]->setValue(gate, pin);
        } else
            switchDecoder->input[0] = gate;
    }

    virtual Gate* operator[](int n) override {
        _out();
        // Access output gates from 0 to 31
        if (n < 0 || n > 31) return nullptr;
        return (*dec4_16[n / 16])[n % 16];
    }

    int output() override {
        _out();
        // Returns which gate is currently activated
        return (dec4_16[0]->isEnabled()) ? dec4_16[0]->output() : dec4_16[1]->output() + 16;
    }

    friend std::ostream& operator<<( std::ostream& out, Decoder5_32 dec) {
        for (int i = 31; i > 0; --i) {
            out << dec[i]->output() << " ";          
        }
        out << dec[0]->output();
        return out;
    }

private:
    Decoder4_16* dec4_16[2];
    Gate* enables[2];
    Gate* switchDecoder;

    void _out() {
        enables[0]->input[0] = this->enable;
        enables[1]->input[0] = this->enable;
        enables[0]->setValue(switchDecoder->output(), 1);
        enables[1]->setValue(switchDecoder->input[0], 1);
        dec4_16[0]->setEnable(enables[0]);
        dec4_16[1]->setEnable(enables[1]);

        (*dec4_16[0])[0];
        (*dec4_16[1])[0];
    }
} ;

void test();

int main() {
    FourBitsRippleAdder f;

    bool a[4], b[4];
    for (size_t i = 0; i < 4; ++i)
        std::cin >> a[i];
    for (size_t i = 0; i < 4; ++i)
        std::cin >> b[i];

    f.setValue(a[0], 0);
    f.setValue(b[0], 1);
    f.setValue(a[1], 2);
    f.setValue(b[1], 3);
    f.setValue(a[2], 4);
    f.setValue(b[2], 5);
    f.setValue(a[3], 6);
    f.setValue(b[3], 7);

    Decoder5_32 dec(true);

    dec.setValue(f[0]->carryOut()->output(), 4);
    dec.setValue(f[0]->sum()->output(), 3);
    dec.setValue(f[1]->sum()->output(), 2);
    dec.setValue(f[2]->sum()->output(), 1);
    dec.setValue(f[3]->sum()->output(), 0);

    std::cout << dec << std::endl;
    std::cout << dec.output() << std::endl;

    // test();

    return 0;
}

void test() {
    FourBitsRippleAdder f;
    Decoder5_32 dec(true);
    std::vector<string> l = getBins();

    for(const string& a: l) {
        for( const string& b: l) {
            std::cout << a << "\n" << b << std::endl;

            f.setValue(bool(char(a[0]) - 48), 0);
            f.setValue(bool(char(b[0]) - 48), 1);
            f.setValue(bool(char(a[1]) - 48), 2);
            f.setValue(bool(char(b[1]) - 48), 3);
            f.setValue(bool(char(a[2]) - 48), 4);
            f.setValue(bool(char(b[2]) - 48), 5);
            f.setValue(bool(char(a[3]) - 48), 6);
            f.setValue(bool(char(b[3]) - 48), 7);

            dec.setValue(f[0]->carryOut()->output(), 4);
            dec.setValue(f[0]->sum()->output(), 3);
            dec.setValue(f[1]->sum()->output(), 2);
            dec.setValue(f[2]->sum()->output(), 1);
            dec.setValue(f[3]->sum()->output(), 0);

            std::cout << dec << std::endl;
            std::cout << dec.output() << std::endl;
        }
    }
}

char *convertToDifferentBase(int dec, int base, char *result) 
{
    if (!(dec / base))
    {
        if (dec < 0)
        {
            result[0] = '-';
            result[1] = (abs(dec % base) > 9) ? abs(dec % base) + '7': abs(dec % base) + '0';
            result[2] = '\0';
        }
        else
        {
            result[0] = (abs(dec % base) > 9) ? abs(dec % base) + '7': abs(dec % base) + '0';
            result[1] = '\0';
        }
        
        return result; 
    }    
    
    convertToDifferentBase(dec / base, base, result);
    int digit = (abs(dec % base) > 9) ? abs(dec % base) + '7': abs(dec % base) + '0';
    int i = 0;
    for (i = 0; result[i] != '\0'; i++);
    result[i] = digit;
    result[i+1] = '\0';
    return result;
}

std::vector<string> getBins() {
    // Generate the 32 4 bits binary numbers
    int i, j;
    char result[5];
    string temp;
    std::vector<string> l;

    for( i = 0; i < 16; ++i)
    {
        temp = "";
        convertToDifferentBase(i, 2, result);
        for( j = 0; j < strlen(result); ++j) {
            temp += result[j];
        }

        while(j < 4) {
            temp = "0" + temp;
            ++j;
        }

        l.push_back(temp);
    }

    // for(i = 0; i < l.size(); ++i) {
    //     std::cout << l[i] << std::endl;
    //     for(j = 0; j < l[i].size(); ++j)
    //         std::cout << bool(char(l[i][j]) - 48) << " ";
    // }
    return l;
}
