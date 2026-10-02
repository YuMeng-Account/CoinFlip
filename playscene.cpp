#include "playscene.h"
#include <QPainter>
#include <QMenuBar>
#include <QLabel>
#include <QFont>
#include <QPropertyAnimation>
#include <QTimer>
#include <QSoundEffect>
#include "mypushbutton.h"
// playScene::playScene(QWidget *parent)
//     : QMainWindow{parent}
// {}
playScene::playScene(int level):level(level){
    qDebug()<<"进入第"<<level<<"关";
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

    //back按钮
    myPushButton *backbtn = new myPushButton(":/res/BackButton.png", ":/res/BackButtonSelected.png");
    backbtn->setParent(this);
    backbtn->resize(backbtn->width()*2, backbtn->height()*2);
    backbtn->move(this->width()-backbtn->width(), this->height()-backbtn->height());
    connect(backbtn,&QPushButton::clicked,[=](){
        qDebug("点击back");
        emit this->chooseBack();
    });





    //显示当前关卡数
    QLabel *levelText =new QLabel(this);

    levelText->setText(QString("level:%1").arg(level));
    levelText->move(100,this->height()-300);
    QFont font =levelText->font();
    font.setPointSize(60);
    font.setFamily("华文新魏");
    levelText->setFont(font);
    levelText->adjustSize();


    //胜利图标
    QLabel* winLabel=new QLabel(this);
    QPixmap pm ;
    pm.load(":/res/LevelCompletedDialogBg.png");
    pm=pm.scaled(pm.width()*2,pm.height()*2);
    winLabel->setGeometry(0,0,pm.width(),pm.height());
    winLabel->setParent(this);
    winLabel->setPixmap(pm);
    winLabel->move((this->width()-winLabel->width())*0.5,-winLabel->height());
    //准备下移动画
    QPropertyAnimation*animation=new QPropertyAnimation(winLabel,"geometry");
    animation->setDuration(1000);
    animation->setStartValue(QRect(winLabel->x(),winLabel->y(),winLabel->width(),winLabel->height()));
    animation->setEndValue(QRect(winLabel->x(),winLabel->height()*0.5,winLabel->width(),winLabel->height()));
    animation->setEasingCurve(QEasingCurve::OutBounce );


    //翻金币音效
    QSoundEffect *soundFilp =new QSoundEffect(this);
    soundFilp->setSource(QUrl("qrc:/res/ConFlipSound.wav"));
    //胜利音效
    QSoundEffect* soundWin=new QSoundEffect(this);
    soundWin->setSource(QUrl("qrc:/res/LevelWinSound.wav"));
    soundWin->setVolume(0.7f);



    //翻金币背景
    for(int i = 0; i < 4; i++){        // i = 行
        for(int j = 0; j < 4; j++){    // j = 列
            QLabel* backGround = new QLabel(this);
            QPixmap pm(":/res/BoardNode(1).png");
            pm = pm.scaled(pm.width()*2, pm.height()*2);
            backGround->setPixmap(pm);
            backGround->setGeometry(120 + j*100, 360 + i*100, pm.width(), pm.height());
            myCoin *coin = new myCoin(levels[level-1][i][j]);

            coin->resize(backGround->width()-10, backGround->height()-10);
            coin->setParent(this);
            coin->move(120 + j*100 + 5, 360 + i*100 + 5);

            coinMap[i][j] = coin;
            //当一个按键点击时,禁用全部案件，直到动画播放完毕
            connect(coin, &QPushButton::clicked, [=](){
                soundFilp->play();
                for(int n = 0; n < 4; n++)
                    for(int m = 0; m < 4; m++)
                        coinMap[n][m]->setEnabled(false);
            });
        }
    }


    //硬币状态初始化
    for(int i =0 ;i<4;i++){
        for(int j=0;j<4;j++){
            initCoin(coinMap[i][j],i,j);
            //每点击一次鼠标检查一次游戏状态
            connect(coinMap[i][j],&myCoin::checkCoinMap,[=](){
                if(checkWin()){
                    // 胜利图标下移
                    animation->start();
                    soundWin->play();
                    qDebug()<<"胜利";
                    qDebug()<<"----------";
                }
                else{
                    QTimer::singleShot(50,this,[=](){
                        for(int n=0;n<4;n++){
                            for(int m = 0 ; m <4;m++){
                                coinMap[n][m]->setEnabled(true);
                            }}
                    });

                    for(int n=0;n<4;n++){
                        QString str;
                        for(int m = 0 ; m <4;m++){
                            str += QString::number(coinMap[n][m]->data_) + " ";
                        }
                        qDebug()<<str;
                    }
                    qDebug()<<"---------";
                }


            });



        }
    }



}


bool playScene::checkWin(){
    for(int i=0;i<4;i++){
        for(int j =0;j<4;j++){
            if(coinMap[i][j]->data_==1){
                return false;
            }
        }
    }
    return true;

}
void playScene::initCoin(myCoin* coin,int i ,int j){
    if(i == 0)
        coin->up = nullptr;
    else
        coin->up = coinMap[i-1][j];
    if(i == 3)
        coin->down = nullptr;
    else
        coin->down = coinMap[i+1][j];
    if(j == 0)
        coin->left = nullptr;
    else
        coin->left = coinMap[i][j-1];
    if(j == 3)
        coin->right = nullptr;
    else
        coin->right = coinMap[i][j+1];
}
void playScene::paintEvent(QPaintEvent* event){
    QPainter painter(this);
    QPixmap pm;
    pm.load(":/res/PlayLevelSceneBg.png");
    painter.drawPixmap(0,0,this->width(),this->height(),pm);

    pm.load(":/res/Title.png");
    pm=pm.scaled(pm.width()*2,pm.height()*2);
    painter.drawPixmap(20,50,pm);


}
