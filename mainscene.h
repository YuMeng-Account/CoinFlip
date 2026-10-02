#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QMainWindow>
#include "chooselevelscene.h"
QT_BEGIN_NAMESPACE
namespace Ui {
class mainScene;
}
QT_END_NAMESPACE

class mainScene : public QMainWindow
{
    Q_OBJECT

public:
    mainScene(QWidget *parent = nullptr);
    ~mainScene();
    void paintEvent(QPaintEvent* event);

private:
    Ui::mainScene *ui;
    chooseLevelScene * levelScene;
};
#endif // MAINSCENE_H
