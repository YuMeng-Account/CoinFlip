#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class myCoin : public QPushButton
{
    Q_OBJECT
private:

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void turn();
    QTimer *timer;
    int frameIndex;
public:
    // explicit myCoin(QWidget *parent = nullptr);
    int data_; //1为正面，0为背面
    myCoin* up;
    myCoin* down;
    myCoin* left;
    myCoin* right;
    myCoin(int data=0);

signals:
    void checkCoinMap();

};

#endif // MYCOIN_H
