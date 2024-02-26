/*
 - Bridge design pattern is a structural design pattern, that separates the abstraction from its implementation.
 - This is useful when we want to avoid permanently binding abstraction & implementation.
 - This gives us the flexibility to change abstraction and/or implementation independently.
*/
#include <iostream>
using namespace std;

// Abstraction
class Shape{
public:
    virtual void draw() = 0;
};

// Implementations: Render (VectorRender & RasterRender)
class Renderer{
public:
    virtual void render() = 0;
};
class VectorRenderer : public Renderer{
public:
    void render() override{
        cout << "Rendering as a vector" << endl;
    }
};
class RasterRenderer : public Renderer{
public:
    void render() override{
        cout << "Rendering as a raster" << endl;
    }
};

// Refined Abstractions
class Circle : public Shape{
public:
    Circle(Renderer& rend) : m_render(rend){

    }
    void draw() override{
        cout << "Drawing a Circle" << endl;
        m_render.render();
    }
private:
    Renderer& m_render;
};
class Square : public Shape{
public:
    Square(Renderer& rend) : m_render(rend){

    }
    void draw() override{
        cout << "Drawing a Square" << endl;
        m_render.render();
    }
private:
    Renderer& m_render;
};

int main(){
    VectorRenderer vr;
    RasterRenderer rr;
    Circle c(vr);
    Square s(rr);

    c.draw();
    s.draw();
    
    return 0;
}