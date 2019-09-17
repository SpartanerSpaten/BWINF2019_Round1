
#ifndef BWINF19_CONTAINER_H
#define BWINF19_CONTAINER_H

#include <vector>
#include <ostream>

class Collumn{
public:
    Collumn(unsigned int);
    ~Collumn();
    
    unsigned int getn(){
        return n;
    }
    
    void add(unsigned int an){
        n += an;
    }
    
    void sub(unsigned int dn){
        n -= dn;
    }

    Collumn& operator=(const Collumn&);
    
protected:

    unsigned int n;
};



class Container{
public:
    Container();
    Container(unsigned int);
    Container(std::vector<unsigned int>);
    ~Container();
    
    void put_init(std::vector<unsigned int>);
    
    int calculate_lll();

    friend std::ostream& operator<<(std::ostream&, const Container&);

private:
    
    std::vector<Collumn*> collumns;
    
    int teleport(unsigned int, unsigned int);
    
    
};

#endif 
