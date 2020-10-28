#include "widget.h"
#include "ui_widget.h"
#include<QString>
#include<QImage>
#include<QFileDialog>
#include <QMouseEvent>
#include <QPainter>
#include <QtDebug>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);

    /*���ڴ�С800*600*/
    resize(820,600);
    QFont font("LiHei Pro Medium ", 13, 100, true);
    QPalette palette;
    ui->label->setFont(font);
    ui->label_2->setFont(font);

    palette.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(palette); //�������ÿؼ�������ɫ
    ui->label_2->setPalette(palette); //�������ÿؼ�������ɫ

    /*ȥ��������*/
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);



}

Widget::~Widget()
{
    delete ui;
}

/*�ж�����Ƿ��ھ�����*/
bool Widget::judgeMouseInRect(QMouseEvent *event)
{
    int x = rect_x;
    int y = rect_y;
    int w = rect_x + rect_w;
    int h = rect_x + rect_h;
    QPoint mousePoint = event->pos();
    /*����ھ�����*/
    if((mousePoint.x() > x && mousePoint.x() < w) &&
            (mousePoint.y() > y && mousePoint.y() < h) ){
        return true;
    }
    return false;
}



/*�滭��ÿ��update��ʱ��ִ��*/
void Widget::paintEvent(QPaintEvent *)
{
    /*��û��ѡ��ͼƬʱ�����ܻ�����*/
    if(filename.isEmpty()){
        return;
    }
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(QColor(0, 255, 0));/*��ɫ*/
    painter.setPen(pen);
    rect_x = lastPoint.x();
    rect_y = lastPoint.y();
    rect_w = endPoint.x() - rect_x;
    rect_h = endPoint.y() - rect_y;

    QString str1,str2;
    str1 = QString("(%1,%2)").arg(rect_x).arg(rect_y);
    str2 = QString("(%1,%2)").arg(rect_w + rect_x).arg(rect_h + rect_y);
    /*��ʾ����*/
    ui->label->setText(str1);  /*���Ͻ�*/
    ui->label_2->setText(str2);/*���½�*/
    painter.drawRect(rect_x, rect_y, rect_w, rect_h);

}

/*���������£���ʼ��¼����*/
void Widget::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
        /*����ھ�����*/
        if(judgeMouseInRect(event) ){
            movePoint = event->globalPos();
            return;
        }
        lastPoint = event->pos();
    }
}

/*����ƶ��¼�*/

void Widget::mouseMoveEvent(QMouseEvent *event)
{

    if(event->buttons() & Qt::LeftButton){
        int dx = event->globalX() - movePoint.x();
        int dy = event->globalY() - movePoint.y();
        movePoint = event->globalPos();
        /*����ھ�����,�ƶ����ο�*/
        if(judgeMouseInRect(event)){
            lastPoint.setX(lastPoint.x() + dx);
            lastPoint.setY(lastPoint.y() + dy);
            endPoint.setX(endPoint.x() + dx);
            endPoint.setY(endPoint.y() + dy);
            update();/*ִ��paintEvent���������ػ�*/
            return;
        }
        endPoint = event->pos();
        update();/*ִ��paintEvent���������ػ�*/
    }

}

/*����ɿ���ֹͣ��¼*/
void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button()==Qt::LeftButton){
        if(judgeMouseInRect(event)){
            return;
        }
        endPoint = event->pos();
        update();
    }
}

void Widget::on_pushButton_clicked()
{
    /*ѡ��ͼƬ*/
    QString temp_filename = QFileDialog::getOpenFileName(this,tr("Open Image"), " ", tr("Image Files (*.png *.jpg *.bmp)"));
    /*��ֹ�ڶ���ѡ��ͼƬʱ������bug*/
    if(!temp_filename.isEmpty()){
        filename = temp_filename;
    }


    /*����ѡ���ͼƬ��������ֱ������Ϊ������Ҳ������������*/
    QPalette PAllbackground = this->palette();
    QImage ImgAllbackground(filename);
    QImage fitimgpic=ImgAllbackground.scaled(this->width(),this->height(), Qt::IgnoreAspectRatio);
    PAllbackground.setBrush(QPalette::Window, QBrush(fitimgpic));
    this->setPalette(PAllbackground);


}

void Widget::on_closeButton_clicked()
{
    this->close();
}

void Widget::on_minsizeButton_clicked()
{
    this->showMinimized();
}


