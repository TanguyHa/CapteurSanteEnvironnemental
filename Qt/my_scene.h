#ifndef MY_SCENE
#define MY_SCENE

#include <QGraphicsScene>
#include <QVBoxLayout>
#include <QGraphicsView>
#include <vector>

/*Class pour l'affichage des grpahique*/
class My_Scene: public QGraphicsScene{
public:
    My_Scene();
    ~My_Scene();
    void change_rect(int height);           //Fonction pour ajouter des points sur le graphique

private:
    void update_scene();

protected:
    std::vector <QRect*> rectangles;
    std::vector <int> valeurs;
    int index=0;

};





#endif
