#include "mycoin.h"
#include <QPixmap>
#include <QPainter>
#include <QTimer>
#include <QSoundEffect>
// myCoin::myCoin(QWidget *parent)
//     : QWidget{parent}
// {}
//定义一个类似于链表的结构体，存储上下左右的金币，再定义一个二维数组
myCoin::myCoin(int data):data_(data),up(nullptr),down(nullptr),left(nullptr),right(nullptr){
    if(data==1){frameIndex=1;}
    else{frameIndex=8;}
    timer = new QTimer(this);

    connect(timer, &QTimer::timeout, this, [this](){
        if(data_==1){
            frameIndex--;
            if(frameIndex <=1)
            {
                frameIndex=1;
                timer->stop();
            }
        }
        else {
            frameIndex++;
            if(frameIndex >=8)
            {
                frameIndex=8;
                timer->stop();
            }


        }
        this->update();
    });

};
void myCoin::paintEvent(QPaintEvent *event){
    QPainter painter(this);
    QPixmap pm;
    pm.load(QString(":/res/Coin000%1.png").arg(frameIndex));
    painter.drawPixmap(5, 5, this->width()-10, this->height()-10, pm);
}
void myCoin::turn(){
    if(timer->isActive()) return;
    data_ =!data_;
    timer->start(50);
}

void myCoin::mousePressEvent(QMouseEvent *event){



    turn();
    if(up){up->turn();};
    if(down){down->turn();}
    if(left){left->turn();}
    if(right){right->turn();}
    QTimer::singleShot(400, this, [=](){
        emit checkCoinMap();
    });
    QPushButton::mousePressEvent(event);


}
