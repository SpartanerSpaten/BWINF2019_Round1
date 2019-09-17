#include "./container.h"

Collumn::Collumn(unsigned int in ){
    n = in;
};

Collumn::~Collumn(){};

Collumn& Collumn::operator=(const Collumn & other){
  n = other.n;
  return *this;
}

Container::Container(){}

Container::Container(unsigned int size){
    for (int i = 0; i < size; i++){
        collumns.push_back(new Collumn(0));
    }
}

Container::Container(std::vector<unsigned int> init_d){
    put_init(init_d);
}

Container::~Container(){
    for (int i = 0;i < collumns.size();i++){
        delete collumns[i];
    }
}

void Container::put_init(std::vector<unsigned int> init_d){
    for (int i = 0;i < init_d.size();i++){
        if (i < collumns.size()){
           collumns[i] = new Collumn(init_d[i]);
        }
        else{
            collumns.push_back(new Collumn(init_d[i]));
        }
    }
}

int Container::teleport(unsigned int obj1, unsigned int obj2){
    
    int tocopy = collumns[obj2]->getn();
    
    if (tocopy > collumns[obj1]->getn()){
        return 1;
    }
    
    collumns[obj1]->add(tocopy);
    collumns[obj2]->sub(tocopy);
    
    return 0;
}

std::ostream& operator<<(std::ostream& os, const Container& obj){
    for (int i = 0; i < obj.collumns.size();i++){
      os << "Collum:" << i << " has " << obj.collumns[i]->getn() << " entities\n";
    }
    return os;
}
