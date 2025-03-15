#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <QMap>
#include <QPainter>
#include <QVBoxLayout>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QMap<QString, QVector<QPoint>> branches; // Хранилище веток
    QString activeBranch = "Red";            // Текущая активная ветка
    bool isEdit = false;
    int stationCounter = 1;
    float minDistance = INFINITY;
    int closestIndex = -1;

    void createBranchButton(const QString &branchName);
    void switchActiveBranch(const QString &branchName);

protected:
    void paintEvent(QPaintEvent *) override;
    void mouseReleaseEvent(QMouseEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    bool areLinesIntersecting(QPointF p1, QPointF q1);

    void on_EditButton_clicked();
    void on_addStationButton_clicked();
};

#endif // MAINWINDOW_H
