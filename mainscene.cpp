#include "mainscene.h"
#include "ui_mainscene.h"
#include "mypushbutton.h"
#include <QPainter>
#include <QMenuBar>
#include <QTimer>
#include <QSoundEffect>
mainScene::mainScene(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::mainScene)
{


    ui->setupUi(this);

    //设置窗口固定大小
    this->setFixedSize(640,1176);
    //设置窗口icon
    this->setWindowIcon(QIcon(":/res/Coin0001.png"));
    //设置窗口标题
    this->setWindowTitle("翻金币");
    //菜单栏优化
    ui->menubar->setAutoFillBackground(true);
    ui->menubar->setStyleSheet("#menubar::item{padding:2px 20px;}");

    //选择关卡场景创建
    levelScene =new chooseLevelScene;

    //退出
    connect(ui->actionQuit,&QAction::triggered,[=](){
        this->close();
    });


    //开始按钮的音效
    QSoundEffect*soundStart= new QSoundEffect(this);
    soundStart->setSource(QUrl("qrc:/res/TapButtonSound.wav"));
    soundStart->setVolume(0.6f);
    //开始按钮
    myPushButton*myButton=new myPushButton(":/res/MenuSceneStartButton.png");
    myButton->setParent(this);
    myButton->resize(myButton->width()*1.5,myButton->height()*1.5);
    myButton->move(this->width()*0.5-myButton->width()*0.5,this->height()*0.7-myButton->height()*0.5);
    //弹跳效果
    connect(myButton,&QPushButton::clicked,[=](){
        qDebug()<<"点击开始按钮";
        soundStart->play();
        myButton->zoom1();
        QTimer::singleShot(500,this,[=](){
            this->hide();
            levelScene->setGeometry(this->geometry());
            levelScene->show();
        });

    });
    connect(levelScene,&chooseLevelScene::chooseBack,[=](){
        QTimer::singleShot(100,this,[=](){
            this->setGeometry(levelScene->geometry());
            levelScene->hide();
            this->show();
        });
    });






}
void mainScene::paintEvent(QPaintEvent* event){
    //背景图绘制
    QPainter painter(this);
    QPixmap pm;
    pm.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pm);

    //背景图标题绘制
    pm.load(":/res/Title.png");
    pm=pm.scaled(pm.width()*2,pm.height()*2);
    painter.drawPixmap(20,50,pm);









}



mainScene::~mainScene()
{
    delete ui;
}
