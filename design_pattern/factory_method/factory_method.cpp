#include <iostream>

class Product
{
public:
    virtual ~Product() = default;

    virtual void ProductProperties() = 0;
};

class ConcreteProductA : public Product
{
public:

    void ProductProperties() override
    {
        std::cout << "ConcreteProductA's Properties" << std::endl;
    }
};

class ConcreteProductB : public Product
{
public:

    void ProductProperties() override
    {
        std::cout << "ConcreteProductB's Properties" << std::endl;
    }
};

class Factory
{
public:
    virtual ~Factory() = default;
    
    virtual Product* FactoryMethod() = 0;
};

class ConcreteFactoryA : public Factory
{
public:
    Product* FactoryMethod() override
    {
        return new ConcreteProductA();
    }
};

class ConcreteFactoryB : public Factory
{
public:
    Product* FactoryMethod() override
    {
        return new ConcreteProductB();
    }
};

void ClientCode(Factory* factory)
{
    Product* product = factory->FactoryMethod();
    product->ProductProperties();
}

int main(int argc, char *argv[])
{
    Factory* factory = new ConcreteFactoryA();
    ClientCode(factory);

    factory = new ConcreteFactoryB();
    ClientCode(factory);
    return 0;
}