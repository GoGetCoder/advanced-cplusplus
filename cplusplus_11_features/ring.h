#ifndef _RING_H_
#define _RING_H_

#include<iostream>
using namespace std;

template<class T>
class ring{
private:
    int m_pos;
    int m_size;
    T* m_ring;

public:
    class iterator;

public:
    ring(int size) : m_pos(0), m_size(size), m_ring(NULL){
        m_ring = new T[m_size];
    }

    ~ring(){
        delete [] m_ring;
    }

    void add(T value ){
        m_ring[m_pos++] = value;
        if(m_pos == m_size){
            m_pos = 0;
        }
    }

    int size(){
        return m_size;
    }

    T& get(int pos){
        return m_ring[pos];
    }

    iterator begin(){
        return iterator(0, *this);
    }

    iterator end(){
        return iterator(m_size, *this);
    }
};

template<class T>
class ring<T>::iterator{
private:
    int m_pos;
    ring& m_ringref;
public:
    iterator(int pos, ring& ringref) : m_pos(pos), m_ringref(ringref){
        
    }

    iterator& operator++(int a){
        m_pos++;
        return *this;
    }

    iterator& operator++(){
        m_pos++;
        return *this;
    }

    T& operator*(){
        return m_ringref.get(m_pos);
    }

    bool operator!=(const iterator& other) const{
        return m_pos != other.m_pos;
    }
};

#endif