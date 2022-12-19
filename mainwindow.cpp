#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("./testDB.db");

    if (db.open()){
        qDebug("open");
    }
    else {
        qDebug("no open");

    }

    query = new QSqlQuery(db);
    query->exec("CREATE TABLE DataBase(Firstname TEXT, Height DOUBLE)");
    model = new QSqlTableModel(this, db);
    model->setTable("DataBase");
    model->select();
    ui->tableView->setModel(model);
    QWidget::setFixedSize(800, 650);

    QPixmap pixmap;
    pixmap.load(":/img/fon");
    pixmap = pixmap.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, pixmap);
    this->setPalette(palette);
    ui->pushButton_3->setStyleSheet("background-color: rgb(237, 41, 57)");
    ui->pushButton->setStyleSheet("background-color: rgb(0, 200, 0)");
    ui->pushButton_2->setStyleSheet("background: rgb(56, 176, 222)");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    model->insertRow(model->rowCount());
}

void MainWindow::on_pushButton_2_clicked()
{
    model->removeRow(row);
}

void MainWindow::on_tableView_clicked(const QModelIndex &index)
{
    row = index.row();
    qDebug()<<row<<index.data();
    update();
}

void MainWindow::on_pushButton_3_clicked()
{
    QApplication::quit();
}

void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter;
    painter.begin(this);

    QPen pen;
    pen.setWidth(5);
    pen.setColor(Qt::darkBlue);

    QBrush brush;
    brush.setColor(Qt::darkBlue);
    brush.setStyle(Qt::SolidPattern);

    painter.setPen(pen);
    painter.setBrush(brush);
    painter.drawLine(700, 50, 700, 550);
    painter.drawLine(680, 550, 720, 550);
    painter.drawLine(680, 50, 720, 50);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Comic Sans MS", 10));
    painter.drawText(720, 45, "175");
    painter.drawText(720, 570, "100");

    int height = model->data(model->index(row, 1)).toInt();
    if(height==0)
    {
    }
    else if (height<150)
    {
        painter.setPen(Qt::red);
        painter.drawLine(680, 450, 720, 450);
        painter.drawText(720, 450, QString::number(height));
    }
    else if(height>150)
    {
        painter.setPen(Qt::red);
        painter.drawLine(680, 150, 720, 150);
        painter.drawText(720, 150, QString::number(height));
    }
    else if(height==150)
    {
        painter.setPen(Qt::red);
        painter.drawLine(680, 300, 720, 300);
        painter.drawText(720, 300, QString::number(height));
    }
    painter.end();
}
