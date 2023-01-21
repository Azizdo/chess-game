#include "board.h"
#include <QtWidgets/QApplication>
#include <QGraphicsView>

Board* board;
int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    board = new Board();                                               
    QGraphicsView* view = new QGraphicsView(board);
    view->setScene(board->getScene());
    view->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    view->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    board->setCentralWidget(view);
    board->show();
     
    return app.exec();
}