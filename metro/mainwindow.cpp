#include "mainwindow.h"
#include <QCursor>
#include <QMouseEvent>
#include "ui_mainwindow.h"
//хуйня (конструктор класса) ниже создает то что в ней написано при старте приложения
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int px = event->pos().x(), py = event->pos().y();
    qDebug() << "Real pos=" << event->pos();
    ui->label->setText(QString("x = %1").arg(px));
    ui->label_2->setText(QString("y = %1").arg(py));
}

void MainWindow::Click(int x, int y)
{
    QPainter painter;
    painter.begin(this);
    painter.drawEllipse(x, y, 10, 10);

    painter.end();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);
    //линия
    painter.drawEllipse(10, 10, 10, 10);
    //круг

    //отвечает за контур(арбис)
    QPen pen;
    // делаем контур красным
    pen.setColor(Qt::red);
    //меняем стиль линии
    pen.setStyle(Qt::SolidLine);

    //заливка
    QBrush brush;
    brush.setColor(Qt::green);
    brush.setStyle(Qt::SolidPattern);

    //чтобы к нашему painter'у применилась что-нибудь
    painter.setPen(pen);
    painter.setBrush(brush);

    // типо соединенные точки
    QPolygon pol;
    pol << QPoint(50, 50) << QPoint(100, 100) << QPoint(100, 50);
    QWidget::update();
    painter.end();
}
MainWindow::~MainWindow(){
    delete ui;
}
