#include "mypushbutton.h"
#include <QPixmap>
#include <QPropertyAnimation>
#include <QPainter>
// myPushButton::myPushButton(QWidget *parent)
//     : QWidget{parent}
// {}
myPushButton::myPushButton(QString normalImg,QString pressImg){
    normalImgPath=normalImg;
    pressImgPath=pressImg;
    QPixmap pm;
    if(!pm.load(normalImg)){
        qDebug()<<"文件加载失败!";
        return ;
    }

    setIcon(QIcon(normalImgPath));
    resize(pm.width(),pm.height());
    setStyleSheet("QPushButton{border:none;background: red;}");
    // setIconSize(QSize(this->width(),this->height()));
}

void myPushButton::zoom1(){
    if (isAnimating) return ;
    isAnimating=true;
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()+10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce);
    connect(animation,&QPropertyAnimation::finished,[=](){
        isAnimating=false;
        zoom2();
    });
    animation->start();


}
void myPushButton::zoom2(){
    if (isAnimating) return ;
    isAnimating=true;
    QPropertyAnimation*animation=new QPropertyAnimation(this,"geometry");
    animation->setDuration(200);
    animation->setStartValue(QRect(this->x(),this->y(),this->width(),this->height()));
    animation->setEndValue(QRect(this->x(),this->y()-10,this->width(),this->height()));
    animation->setEasingCurve(QEasingCurve::InExpo);
    connect(animation,&QPropertyAnimation::finished,[=](){
        isAnimating=false;
    });
    animation->start();
}

// void myPushButton::mousePressEvent(QMouseEvent *event){
//     move(x(),y()+10);
// }
// void myPushButton::mouseReleaseEvent(QMouseEvent *event){
//     move(x(),y()-10);

// }
void myPushButton::paintEvent(QPaintEvent *event){
    // Q_UNUSED(event);
    // QPushButton::paintEvent(event);
    QPainter painter(this);
    QPixmap pm;
    // 鼠标按下时显示按下图片，否则显示正常图片
    if(this->isDown() && !pressImgPath.isEmpty()){
        pm.load(pressImgPath);
    } else {
        pm.load(normalImgPath);
    }
    // drawPixmap 的第3、4个参数 = 按钮宽高，图片拉伸填满

    painter.drawPixmap(0, 0, this->width(), this->height(), pm);

}
// bool myPushButton::hitButton(const QPoint &pos) const{
//     // 圆心 = 按钮中心
//     int cx = this->width() / 2;
//     int cy = this->height() / 2;
//     // 半径 = 按钮宽高较小值的一半（假设圆形居中且填满）
//     int r = qMin(this->width(), this->height()) / 2.4;

//     // 点到圆心的距离平方 <= 半径平方 → 在圆内
//     int dx = pos.x() - cx;
//     int dy = pos.y() - cy;
//     return (dx*dx + dy*dy) <= r*r;
// }


