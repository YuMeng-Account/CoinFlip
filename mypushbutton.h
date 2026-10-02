#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QPushButton>


class myPushButton : public QPushButton
{
    Q_OBJECT
public:
    // explicit myPushButton(QWidget *parent = nullptr);

    myPushButton(QString normalImg,QString pressImg="");
    // void mousePressEvent(QMouseEvent *event);
    // void mouseReleaseEvent(QMouseEvent *event);

    void zoom1();
    void zoom2();

private:
    QString normalImgPath;
    QString pressImgPath;
    bool isAnimating = false;
protected:
    void paintEvent(QPaintEvent *event) override;   // 自己绘制按钮
    // bool hitButton(const QPoint &pos) const override;


signals:
};

#endif // MYPUSHBUTTON_H
