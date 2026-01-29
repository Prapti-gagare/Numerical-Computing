class complex 
{
public:
    float real,imag;
    complex();
    complex(float r,float i);
    complex add(complex c);
    complex subtract(complex c);
    complex multiply(complex c);
    complex divide(complex c);
    complex conjugate();
    float norm();
    void display();
};

