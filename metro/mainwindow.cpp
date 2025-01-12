#include "mainwindow.h"
#include <QCursor>
#include <QVector>
#include <math.h>

// сделал климентьев олег и Поляк
#include <QMouseEvent>
#include "ui_mainwindow.h"
// (конструктор класса) ниже создает то что в ней написано при старте приложения
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , isEdit(false)
    , permision(true)

{
    ui->setupUi(this);
    connect(ui->EditButton, &QPushButton::clicked, this, &MainWindow::on_EditButton_clicked);
}

QVector<int> Stations;
void MainWindow::on_EditButton_clicked()
{
    qDebug() << "Button has been pressed";
    isEdit = !isEdit; // Переключаем режим редактирования
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int px = event->pos().x();
    int py = event->pos().y();

    if (!isEdit) {
        // Добавляем новую точку только в режиме добавления
        Stations.push_back(px);
        Stations.push_back(py);
        repaint(); // или update()
    } else {
        // В режиме редактирования ищем ближайшую точку
        closestIndex = -1; // Сбрасываем индекс ближайшей точки
        minDistance = 50;  // Сбрасываем минимальное расстояние

        for (int i = 0; i < Stations.size(); i += 2) {
            float distance_to_click = sqrt(pow(px - Stations[i], 2) + pow(py - Stations[i + 1], 2));
            qDebug() << "Distance to point:" << distance_to_click;

            // Проверяем, является ли текущее расстояние минимальным
            if (distance_to_click < minDistance) {
                minDistance = distance_to_click; // Обновляем минимальное расстояние
                closestIndex = i;                // Сохраняем индекс ближайшей точки
            }
        }

        if (closestIndex != -1) {
            qDebug() << "Nearest point:" << Stations[closestIndex] << Stations[closestIndex + 1];
            qDebug() << "min distance:" << minDistance;
        } else {
            qDebug() << "No points in Stations.";
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int px = event->pos().x();
    int py = event->pos().y();
    if (isEdit && closestIndex != -1) {
        // Обновляем координаты ближайшей точки только в режиме редактирования
        Stations[closestIndex] = px;
        Stations[closestIndex + 1] = py;
        repaint(); // или update()
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    if (!isEdit) {
        int px = event->pos().x(), py = event->pos().y();

        ui->label->setText(QString("x = %1").arg(px));
        ui->label_2->setText(QString("y = %1").arg(py));

        // Добавляем новую точку только в режиме добавления

        repaint(); // или update()
    }
}

float dot[2]; // ����� �����������
bool cross(float x1, float y1, float x2, float y2, float x3, float y3, float x4, float y4)
{
    float n;
    if (y2 - y1 != 0) { // a(y)
        float q = (x2 - x1) / (y1 - y2);
        float sn = (x3 - x4) + (y3 - y4) * q;
        if (!sn) {
            return 0;
        }                                     // c(x) + c(y)*q
        float fn = (x3 - x1) + (y3 - y1) * q; // b(x) + b(y)*q
        n = fn / sn;
    } else {
        if (!(y3 - y4)) {
            return 0;
        }                          // b(y)
        n = (y3 - y1) / (y3 - y4); // c(y)/b(y)
    }
    dot[0] = x3 + (x4 - x3) * n; // x3 + (-b(x))*n
    dot[1] = y3 + (y4 - y3) * n; // y3 +(-b(y))*n
    return 1;
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    // Рисуем кружочки и линии между ними
    for (int i = 0; i < Stations.size(); i += 2) {
        painter.setPen(QPen(QColor(79, 106, 25), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
        painter.setBrush(QColor(0, 100, 100));
        painter.drawEllipse(Stations[i], Stations[i + 1], 20, 20);
        if (i >= 2) {
            painter.setPen(QPen(QColor(0, 100, 100), 5, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin));
            painter.drawLine(Stations[i - 2] + 10,  // x 1-ой точки
                             Stations[i - 1] + 10,  // y 1-ой точки
                             Stations[i] + 10,      // x 2-ой точки
                             Stations[i + 1] + 10); // y 2-ой точки
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
