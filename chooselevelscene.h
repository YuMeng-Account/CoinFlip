#ifndef CHOOSELEVELSCENE_H
#define CHOOSELEVELSCENE_H
#include "playscene.h"
#include <QMainWindow>

class chooseLevelScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit chooseLevelScene(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent* event);
private:
    playScene* play = NULL;
signals:
    void chooseBack();


signals:
};

#endif // CHOOSELEVELSCENE_H
