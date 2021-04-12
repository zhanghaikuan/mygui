#ifndef MYLABEL_H
#define MYLABEL_H
#include <QtWidgets/QLabel>
#include <QtCore/QPoint>
#include <QtGui/QColor>
#include <QtGui/QPaintEvent>
#include <QtGui/QImage>
#include <QtGui/QPixmap>

class myLabel : public QLabel
{
	//Q_OBJECT
public:
	myLabel();
	//~myLabel();
	//��������
	virtual void paintEvent(QPaintEvent *event) override;
	//��갴��
	void mousePressEvent(QMouseEvent *e);
	//����ƶ�
	void mouseMoveEvent(QMouseEvent *e);
	//���̧��
	void mouseReleaseEvent(QMouseEvent *e);

	//����������������
	void setLineColor(const QColor lineColor);
	void setLineSize(const int lineSize);
	//�õ����ߵ������յ�
	QPoint getStartPoint();
	QPoint getEndPoint();

	void clear();

private:
	QPoint lineStartPoint;          //�������
	QPoint lineEndPoint;            //�����յ�
	QColor lineColor;               //������ɫ
	int lineSize;                  //5������
	bool isPressed;
};

#endif // MYLABEL_H
