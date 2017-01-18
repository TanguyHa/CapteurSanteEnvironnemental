#include "my_scene.h"
#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <vector>
#include <iostream>
#include <math.h>

void My_Scene::update_scene(){
    this->clear();
    for(unsigned i(0);i<rectangles.size();i++){
        this->addRect(*rectangles[i]);
    }
}
void My_Scene::change_rect(int height){
    int h=height;
    rectangles.push_back(new QRect(this->index,0,1,-1*h));
    valeurs.push_back(h);
    this->index++;

    update_scene();
}

My_Scene::My_Scene():QGraphicsScene() {
    rectangles.push_back(new QRect(1,0,1,0));

    update_scene();
}
My_Scene::~My_Scene(){
    for(unsigned i(0);i<rectangles.size();i++){
        delete rectangles[i];
    }

}
