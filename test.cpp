#include "test.h"
#include <QPainter>
#include <QMouseEvent>

Test::Test(QWidget *parent) : QWidget(nullptr), Pm(CARD_WIDTH,CARD_HEIGHT)
{

    Hld = new PlayerCardHolder(parent, &maker);
    EnHld = new EnemyCardHolder(CardOrientation::HOR, parent);
    Odis = new OpenDequeDisplayer(nullptr,&maker);
//    QPixmap* pix_cov = new QPixmap("src\\cover.png");
//    dis->SetCover(pix_cov);

    dis = new DequeDisplayer();
    SuitCouter = CardSuit::HEARTS;
    ValueCounter = CardValue::ACE;
    Pm = *maker.GetCard(CardSuit::HEARTS, CardValue::ACE);
Card *c = new Card;
    c->Suit = SuitCouter;
    c->Value = ValueCounter;
    this->setFixedSize(110,170);
    Hld->AddCard(c);
//    Hld->AddCard(c);
//    Hld->AddCard(c);
//    Hld->AddCard(c);
    Hld->UpdateDequeSuit(CardSuit::TILES);
    Hld->show();
    EnHld->show();
    dis->show();
    dis->move(300,300);
    Odis->show();
    Odis->move(600,300);
}

void Test::paintEvent(QPaintEvent *e)
{
    QPainter paint(this);
    paint.drawPixmap(0,0,110,170,Pm);
    paint.end();

}
#include <QDebug>
#include <QThread>
void MoveAnim(QWidget* wgt, int destX, int destY)
{
    float dist;
    float offset=1;
    int cur_X;
    int cur_Y;
    do
    {
//        dist = sqrt(pow(destX-wgt->pos().x(),2)+ pow(destY-wgt->pos().y(),2));
//        cos = (destX-wgt->pos().x())/dist;
//        sin = (destY-wgt->pos().y())/dist;
//        wgt->move(roundf(cos*offset),roundf(sin*offset));
        cur_X = wgt->pos().x();
        cur_Y = wgt->pos().y();
        if(destX > cur_X)
        {
            wgt->move(cur_X+1,cur_Y);
        }
        else if(destX < wgt->pos().x())
        {
            wgt->move(cur_X-1,cur_Y);
        }
        if(destY > cur_Y)
        {
            wgt->move(cur_X,cur_Y+1);
        }
        else if(destY < cur_Y)
        {
            wgt->move(cur_X,cur_Y-1);
        }
        wgt->updateGeometry();
        wgt->update();
        wgt->repaint();
        qDebug() << "aaa";
        QThread::msleep(100);
        //QThread::yieldCurrentThread();

    }while(destX != wgt->pos().x()&&destY != wgt->pos().y());
}

void Test::mousePressEvent(QMouseEvent *e)
{

    if(e->button() == Qt::MouseButton::LeftButton )
    {
        ValueCounter = CardValue(((int)ValueCounter+1)%9);
        Pm = *maker.GetCard(SuitCouter,ValueCounter);
        qDebug() << "Left mouse button was pressed on a card";
        this->update();
    }
    else if(e->button() == Qt::MouseButton::RightButton )
    {
        SuitCouter = CardSuit(((int)SuitCouter+1)%4);
        Pm = *maker.GetCard(SuitCouter,ValueCounter);
        this->update();
    }
    else if(e->button() == Qt::MouseButton::MiddleButton)
    {
        //MoveAnim(this, this->pos().x()+30,this->pos().y()+20);
    }
}

void Test::keyPressEvent(QKeyEvent *e)
{
    qDebug() << "Key pressed";
    if(e->key() == Qt::Key::Key_A)
    {
        Card *c = new Card;
        c->Suit = SuitCouter;
        c->Value = ValueCounter;
        Hld->AddCard(c);
        EnHld->AddCard();
        dis->AddCard();
        Odis->PrintCardOver(*c);
    }
    else if(e->key() == Qt::Key::Key_D)
    {
        Hld->ExtractCards();
        EnHld->ExtractCard();
        dis->ExtractCard();
        Odis->ClearDeque();
    }
}

