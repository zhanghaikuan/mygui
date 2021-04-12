#include "myLabel.h"
#include <QtGui/QPen>
#include<QtGui/QPainter>

myLabel::myLabel()
{
	this->lineStartPoint = QPoint(0, 0);
	this->lineEndPoint = QPoint(0, 0);
	this->lineColor = QColor(Qt::red);
	this->lineSize = 3;
}

//绘制线条
void myLabel::paintEvent(QPaintEvent *event)
{
	QLabel::paintEvent(event);//必须有，才能让背景图片显示出来
	QPainter painter(this);
	QPen pen;
	pen.setColor(lineColor);
	pen.setWidth(lineSize);
	painter.setPen(pen);
	painter.drawLine(lineStartPoint, lineEndPoint);
	// 画十字线
	painter.drawLine(QPoint(width()/2,0), QPoint(width() / 2, height()));
	painter.drawLine(QPoint(0, height()/2), QPoint(width() , height()/2));
	//画方框
	// point1    width()/2 - (width*800/2592)     height()/2 - height*800/1944     width()/2 - (width*800/2592)   height()/2 + height*800/1944
	painter.drawLine(QPoint(width() / 2 - (width() * 400 / 2592), height() / 2 - height() * 400 / 1944), QPoint(width() / 2 - (width() * 400 / 2592), height() / 2 + height() * 400 / 1944));
	painter.drawLine(QPoint(width() / 2+ (width() * 400 / 2592), height() / 2 - height() * 400 / 1944), QPoint(width() / 2 + (width() * 400 / 2592), height() / 2 + height() * 400 / 1944));
	painter.drawLine(QPoint(width() / 2 - (width() * 400 / 2592), height() / 2 - height() * 400 / 1944), QPoint(width() / 2 + (width() * 400 / 2592), height() / 2 - height() * 400 / 1944));
	painter.drawLine(QPoint(width() / 2 - (width() * 400 / 2592), height() / 2+ height() * 400 / 1944), QPoint(width() / 2 + (width() * 400 / 2592), height() / 2 + height() * 400 / 1944));
	
}

//鼠标按下
void myLabel::mousePressEvent(QMouseEvent *e)
{
	lineStartPoint = e->pos();
	lineEndPoint = e->pos();
	//在图片上绘制
	isPressed = true;
}

//鼠标移动
void myLabel::mouseMoveEvent(QMouseEvent *e)
{
	if (isPressed)
	{
		lineEndPoint = e->pos();
		update();
	}
}

//鼠标抬起
void myLabel::mouseReleaseEvent(QMouseEvent *e)
{
	isPressed = false;
	update();
}

void myLabel::setLineColor(const QColor lineColor)
{
	this->lineColor = lineColor;
}

void myLabel::setLineSize(const int lineSize)
{
	this->lineSize = lineSize;
}

QPoint myLabel::getStartPoint()
{
	return lineStartPoint;
}

QPoint myLabel::getEndPoint()
{
	return lineEndPoint;
}

void myLabel::clear()
{
	lineStartPoint = QPoint(0, 0);
	lineEndPoint = QPoint(0, 0);
	update();
}