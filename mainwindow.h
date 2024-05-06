#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "include/AVLTree.h"
#include "include/AbstractTable.h"
#include "include/ChainedHashTable.h"
#include "include/OrderedListBasedTable.h"
#include "include/UnorderedArrayBasedTable.h"
#include "include/UnorderedListBasedTable.h"
#include "include/Polynomial.h"
#include "qtreewidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class Tables
{
public:

    Table<int, Polynomial<int>>** container;
    int rows;
    int mode;

    Tables() {
        rows = 0;
        mode = 0;
        container = new Table<int, Polynomial<int>>*[5];
        container[0] = new UnorderedABTable<int, Polynomial<int>>;
        container[1] = new UnorderedLBTable<int, Polynomial<int>>;
        container[2] = new OrderedListTable<int, Polynomial<int>>;
        container[3] = new ChainedHashTable<int, Polynomial<int>>;
        container[4] = new AVLTree<int, Polynomial<int>>;
    }

    void Insert(int key, const Polynomial<int>& value) {
        for (int i = 0; i < 5; i++) {
            container[i]->Insert(key, value);
        }
    }

    void Remove(int id, int key) {
        container[id]->Remove(key);
    }

    ~Tables() {
        for (int i = 0; i < 5; i++) {
            delete container[i];
        }
        delete[] container;
    }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    Tables table;
    ~MainWindow();

    void DataDraw(int mode);

private slots:
    void on_TableSelector_currentIndexChanged(int index);

    void on_PushButton_clicked();

    void on_RemoveButton_clicked();

    void on_SearchButton_clicked();

private:
    Ui::MainWindow *ui;

    void UABTDraw();
    void ULBTDraw();
    void LBTDraw();
    void HTDraw();
    void TDraw();

    void TSearchHighlight(int key, int columnKeyId);
    void LSearchHighlight(int key, int columnKeyId);

    QTreeWidgetItem* TreeCross(QTreeWidgetItem* item, const Node<int, Polynomial<int>>* node);
};
#endif // MAINWINDOW_H
