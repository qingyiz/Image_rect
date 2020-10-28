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

    /*窗口大小800*600*/
    resize(820,600);
    QFont font("LiHei Pro Medium ", 13, 100, true);
    QPalette palette;
    ui->label->setFont(font);
    ui->label_2->setFont(font);

    palette.setColor(QPalette::WindowText,Qt::white);
    ui->label->setPalette(palette); //这里设置控件字体颜色
    ui->label_2->setPalette(palette); //这里设置控件字体颜色

    /*去掉标题栏*/
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setAttribute(Qt::WA_TranslucentBackground);



}

Widget::~Widget()
{
    delete ui;
}

/*判断鼠标是否在矩形内*/
bool Widget::judgeMouseInRect(QMouseEvent *event)
{
    int x = rect_x;
    int y = rect_y;
    int w = rect_x + rect_w;
    int h = rect_x + rect_h;
    QPoint mousePoint = event->pos();
    /*鼠标在矩形内*/
    if((mousePoint.x() > x && mousePoint.x() < w) &&
            (mousePoint.y() > y && mousePoint.y() < h) ){
        return true;
    }
    return false;
}



/*绘画，每次update的时候执行*/
void Widget::paintEvent(QPaintEvent *)
{
    /*当没有选择图片时，不能画矩形*/
    if(filename.isEmpty()){
        return;
    }
    QPainter painter(this);
    QPen pen;
    pen.setWidth(5);
    pen.setColor(QColor(0, 255, 0));/*绿色*/
    painter.setPen(pen);
    rect_x = lastPoint.x();
    rect_y = lastPoint.y();
    rect_w = endPoint.x() - rect_x;
    rect_h = endPoint.y() - rect_y;

    QString str1,str2;
    str1 = QString("(%1,%2)").arg(rect_x).arg(rect_y);
    str2 = QString("(%1,%2)").arg(rect_w + rect_x).arg(rect_h + rect_y);
    /*显示坐标*/
    ui->label->setText(str1);  /*左上角*/
    ui->label_2->setText(str2);/*右下角*/
    painter.drawRect(rect_x, rect_y, rect_w, rect_h);

}

/*鼠标左键按下，开始记录坐标*/
void Widget::mousePressEvent(QMouseEvent *event)
{

    if(event->button() == Qt::LeftButton){
        /*鼠标在矩形内*/
        if(judgeMouseInRect(event) ){
            movePoint = event->globalPos();
            return;
        }
        lastPoint = event->pos();
    }
}

/*鼠标移动事件*/

void Widget::mouseMoveEvent(QMouseEvent *event)
{

    if(event->buttons() & Qt::LeftButton){
        int dx = event->globalX() - movePoint.x();
        int dy = event->globalY() - movePoint.y();
        movePoint = event->globalPos();
        /*鼠标在矩形内,移动矩形框*/
        if(judgeMouseInRect(event)){
            lastPoint.setX(lastPoint.x() + dx);
            lastPoint.setY(lastPoint.y() + dy);
            endPoint.setX(endPoint.x() + dx);
            endPoint.setY(endPoint.y() + dy);
            update();/*执行paintEvent函数进行重绘*/
            return;
        }
        endPoint = event->pos();
        update();/*执行paintEvent函数进行重绘*/
    }

}

/*鼠标松开，停止记录*/
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
    /*选择图片*/
    QString temp_filename = QFileDialog::getOpenFileName(this,tr("Open Image"), " ", tr("Image Files (*.png *.jpg *.bmp)"));
    /*防止第二次选择图片时，出现bug*/
    if(!temp_filename.isEmpty()){
        filename = temp_filename;
    }


    /*绘制选择的图片，我这里直接设置为背景，也就是整个界面*/
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


