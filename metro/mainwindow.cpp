#include "mainwindow.h"
#include <QApplication>
#include <QCursor>
#include <QLineF>
#include <QVector>
#include <math.h>
//
#include <QMouseEvent>
#include "ui_mainwindow.h"
//
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    branches["Red"] = QVector<QPoint>(); // Инициализация красной ветки

    connect(ui->EditButton, &QPushButton::clicked, this, &MainWindow::on_EditButton_clicked);
    connect(ui->addStationButton,
            &QPushButton::clicked,
            this,
            &MainWindow::on_addStationButton_clicked);
    connect(ui->EditButton_3, &QPushButton::clicked, this, [this]() { switchActiveBranch("Red"); });
}

void MainWindow::createBranchButton(const QString &branchName)
{
    QPushButton *branchBtn = new QPushButton(branchName, this);
    branchBtn->setGeometry(730, 10 + (branches.size() * 40), 160, 30);
    branchBtn->setStyleSheet(
        "QPushButton{"
        "background-color: #80000;"                        /* Красный фон */
        "color: white;"                                    /* Белый текст */
        "border: 2px solid #800000;"                       /* Темно красная рамка */
        "border-radius: 10px;"                             /* Скругленные углы */
        "font-size: 12px;"                                 /* Размер шрифта */
        "padding: 5px 10px;}"                              /* Отступы */
        "QPushButton:pressed {background-color: #0000FF;}" /* Фон при нажатии (синий) */
    );
    connect(branchBtn, &QPushButton::clicked, this, [this, branchName]() {
        switchActiveBranch(branchName);
    });
    branchBtn->show();
}
void MainWindow::switchActiveBranch(const QString &branchName)
{
    activeBranch = branchName;
    repaint();
}
void MainWindow::on_addStationButton_clicked()
{
    QString newBranchName = QString("Branch %1").arg(stationCounter++);
    branches[newBranchName] = QVector<QPoint>();
    createBranchButton(newBranchName);
}
void MainWindow::on_EditButton_clicked()
{
    qDebug() << "Button has been pressed!!!!!!!!!!!";
    isEdit = !isEdit;
}

QPoint TempPoint;
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    int px = event->pos().x();
    int py = event->pos().y();
    QVector<QPoint> &stations = branches[activeBranch];

    if (!isEdit && stations.size() >= 4) {
        bool canAddStation = true; // Флаг для проверки возможности добавления станции

        for (int i = 1; i < stations.size(); i += 1) {
            QPointF p1(stations.last());
            QPointF q1(px, py);
            QPointF p2(stations[i - 1]);
            QPointF q2(stations[i]);

            if (areLinesIntersecting(p1, q1)) {
                canAddStation = false; // Если пересекается, устанавливаем флаг в false
                ui->label_3->setText(
                    QString("Paths cross! Please place the station in a different location!"));
                break; // Выходим из цикла, так как уже нашли пересечение
            }
        }

        // Если не было пересечений, добавляем новую станцию
        if (canAddStation) {
            repaint();
        }

    } else if (!isEdit && stations.size() < 4) {
        TempPoint.setX(px);
        TempPoint.setY(py);
        ui->label_3->setText(QString("The station was successfully placed!"));
        repaint();
    } else {
        closestIndex = -1;
        minDistance = 100;
        qDebug() << "Dis point:";
        for (int i = 0; i < stations.size(); i += 1) {
            float distance_to_click = sqrt(pow(px - stations[i].x(), 2)
                                           + pow(py - stations[i].y(), 2));
            qDebug() << "Distance to point:" << distance_to_click;

            if (distance_to_click < minDistance) {
                minDistance = distance_to_click;
                closestIndex = i;
            }
        }
    }
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    int px = event->pos().x();
    int py = event->pos().y();
    QVector<QPoint> &stations = branches[activeBranch];
    if (isEdit && closestIndex != -1) {
        bool canAddStation = true; // Флаг для проверки возможности добавления станции
        for (int i = 0; i < stations.size() - 2; i += 1) {
            QPointF p1(stations.last() + QPoint(10, 10));
            QPointF q1(px + 10, py + 10);
            QPointF p2(stations[i] + QPoint(10, 10));
            QPointF q2(stations[i + 1] + QPoint(10, 10));

            if (areLinesIntersecting(p1, q1)) {
                canAddStation = false; // Если пересекается, устанавливаем флаг в false
                ui->label_3->setText(
                    QString("Paths cross! Please place the station in a different location!"));
                break; // Выходим из цикла, так как уже нашли пересечение
            }
        }

        // Если не было пересечений, добавляем новую станцию
        if (canAddStation) {
            stations[closestIndex].setX(px);
            stations[closestIndex].setY(py);
            ui->label_3->setText(QString("The station was successfully placed!"));
            repaint();
        }
    } else if (!isEdit) {
        TempPoint.setX(px);
        TempPoint.setY(py);
        ui->label_3->setText(QString("The station was successfully placed!"));
        repaint();
    }
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    int px = event->pos().x();
    int py = event->pos().y();
    QVector<QPoint> &stations = branches[activeBranch];
    if (!isEdit && stations.size() >= 2) {
        bool canAddStation = true; // Флаг для проверки возможности добавления станции

        for (int i = 0; i < stations.size() - 2; i += 1) {
            QPointF q1(px, py);

            if (areLinesIntersecting(stations.last(), q1)) {
                canAddStation = false; // Если пересекается, устанавливаем флаг в false
                ui->label_3->setText(QString("Pathscation!"));
                break; // Выходим из цикла, так как уже нашли пересечение
            }
        }

        // Если не было пересечений, добавляем новую станцию
        if (canAddStation) {
            stations.push_back(QPoint(px, py));
            ui->label_3->setText(QString("The station was successfully placed!"));
            repaint();
        }

    } else if (!isEdit && stations.size() < 3) {
        stations.push_back(QPoint(px, py));

        ui->label_3->setText(QString("The station was successfully placed!"));
        ui->label_3->setText(QString("The station was successfully placed!"));
        repaint();
    }
}

bool MainWindow::areLinesIntersecting(QPointF p1, QPointF q1)
{
    QMapIterator<QString, QVector<QPoint>> it(branches);
    while (it.hasNext()) {
        it.next();
        const QVector<QPoint> &stations = it.value(); // Список станций в ветке

        // Перебираем все линии в текущей ветке
        for (int i = 1; i < stations.size() - 1; ++i) {
            QPointF p2(stations[i - 1]); // Начало линии
            QPointF q2(stations[i]);     // Конец линии

            // Проверяем пересечение новой линии (p1, q1) с текущей линией (p2, q2)
            QLineF line1(p1, q1);
            QLineF line2(p2, q2);

            if (line1.intersects(line2, nullptr) == QLineF::BoundedIntersection) {
                qDebug() << "Intersection found between lines:"
                         << "(" << p1.x() << "," << p1.y() << ")-(" << q1.x() << "," << q1.y()
                         << ")"
                         << "and"
                         << "(" << p2.x() << "," << p2.y() << ")-(" << q2.x() << "," << q2.y()
                         << ")";
                return true; // Найдено пересечение
            }
        }
    }

    return false; // Пересечений не найдено
}
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);

    // Перебираем все ветки
    QMapIterator<QString, QVector<QPoint>> it(branches);
    while (it.hasNext()) {
        it.next();
        const QVector<QPoint> &stations = it.value();
        bool isActiveBranch = (it.key() == activeBranch);

        // Настройка цвета для ветки
        QColor branchColor = isActiveBranch
                                 ? QColor(255, 0, 25)
                                 : QColor(0, 0, 255); // Активная — красная, остальные — синие

        // Отрисовка станций и линий
        painter.setPen(QPen(branchColor, 1, Qt::SolidLine));
        painter.setBrush(branchColor);

        for (int i = 0; i < stations.size(); ++i) {
            painter.drawEllipse(stations[i].x(), stations[i].y(), 20, 20);
            if (i > 0) {
                painter.setPen(QPen(branchColor, 5, Qt::SolidLine));
                painter.drawLine(stations[i - 1].x() + 10,
                                 stations[i - 1].y() + 10,
                                 stations[i].x() + 10,
                                 stations[i].y() + 10);
            }
        }

        // Отрисовка временной линии для активной ветки
        if (isActiveBranch && !isEdit && stations.size() >= 1) {
            painter.setPen(QPen(branchColor, 2, Qt::DashLine));
            painter.drawLine(stations.last().x() + 10,
                             stations.last().y() + 10,
                             TempPoint.x() + 10,
                             TempPoint.y() + 10);
        }
    }
}
MainWindow::~MainWindow()
{
    delete ui;
}
