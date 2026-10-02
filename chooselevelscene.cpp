#include "chooselevelscene.h"
#include <QMenuBar>
#include <QPainter>
#include "mypushbutton.h"
#include <QLabel>
#include <QSoundEffect>
chooseLevelScene::chooseLevelScene(QWidget *parent)
    : QMainWindow{parent}
{
    this->setFixedSize(640,1176);
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    this->setWindowTitle("翻金币");
    QMenuBar* menu =menuBar();
    menu->setAutoFillBackground(true);
    menu->setStyleSheet(R"(QMenuBar::item{padding:2px 20px;})");
    QMenu *start=menu->addMenu("开始");
    QAction *exit=start->addAction("退出");
    this->setMenuBar(menu);
    connect(exit,&QAction::triggered,[=](){
        this->close();
    });

    //返回按钮音效
    QSoundEffect*soundBack= new QSoundEffect(this);
    soundBack->setSource(QUrl("qrc:/res/BackButtonSound.wav"));
    //返回按钮
    myPushButton *backbtn = new myPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->resize(backbtn->width()*2, backbtn->height()*2);
    backbtn->move(this->width()-backbtn->width(), this->height()-backbtn->height());
    connect(backbtn,&QPushButton::clicked,[=](){
        qDebug("点击back");
        soundBack->play();
        emit this->chooseBack();
    });


    //选择关卡音效
    QSoundEffect *soundChooseLevel=new QSoundEffect(this);
    soundChooseLevel->setSource(QUrl("qrc:/res/TapButtonSound.wav"));

    //关卡选择按钮
    for(int i = 0 ; i <20;i++){
        myPushButton* levelBtn =new myPushButton(":/res/LevelIcon.png");
        levelBtn->setParent(this);
        levelBtn->move(60+i%4*125,270+i/4*125);
        levelBtn->resize(levelBtn->width()*2,levelBtn->height()*2);

        QLabel * numberLabel =new QLabel(this);
        numberLabel->setFixedSize(levelBtn->width(),levelBtn->height());
        numberLabel->setText(QString::number(i+1));
        QFont font=numberLabel->font();
        font.setPointSize(30);
        numberLabel->setFont(font);
        numberLabel->setAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
        numberLabel->move(60+i%4*125,270+i/4*125);
        numberLabel->setAttribute(Qt::WA_TransparentForMouseEvents);

        connect(levelBtn,&QPushButton::clicked,[=](){
            play=new playScene(i+1);
            this->hide();
            play->setGeometry(this->geometry());
            play->show();
            soundChooseLevel->play();
            connect(play,&playScene::chooseBack,[=](){
                this->setGeometry(play->geometry());
                delete play;
                this->show();
                play=NULL;
                soundBack->play();
            });

        });

    }





}
void chooseLevelScene::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPixmap pm;
    pm.load(":/res/OtherSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pm);

    pm.load(":/res/Title.png");
    pm=pm.scaled(pm.width()*2,pm.height()*2);
    painter.drawPixmap(20,50,pm);


}
