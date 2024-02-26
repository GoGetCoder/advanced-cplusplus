/*
 - Composite design pattern is a structural design pattern that lets you compose objects into tree structures which
   represent whole-part hierarchies.
 - Composite lets the clients treat individual objects and compositions of objects uniformally.
 - In other words, in most cases we can ignore the differences between composition of objects & individual objects.
*/
#include <iostream>
#include <functional>
#include <vector>
#include <algorithm>
using namespace std;

class Graphic {
public:
    virtual void draw() = 0;
    virtual void add(Graphic* g){};
    virtual ~Graphic(){ };
};

class Line : public Graphic{
public:
  void draw() override{
    cout << "Line Draw()" << endl;
  }
};

class Triangle : public Graphic{
public:
  void draw() override{
    cout << "Rectangle Draw()" << endl;
  }
};

class Picture : public Graphic{
public:
  void draw() override{
    for(auto g : g_list){
      g->draw();
    }
  }
  void add(Graphic* g) override{
    g_list.push_back(g);
  }
private:
  vector<Graphic*> g_list;
};

int main(){
  Line line;
  line.draw();
  Triangle tri;
  tri.draw();

  Picture pict;
  pict.add(&line);
  pict.add(&tri);
  pict.draw();

  return 0;
}