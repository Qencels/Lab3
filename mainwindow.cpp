#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::DataDraw(int mode) {
    ui->StatusLabel->setText("");

    auto tmpT = dynamic_cast<UnorderedABTable<int, Polynomial<int>>*>(table.container[0]);
    ui->treeWidget->resize(0, 0);
    ui->tableWidget->resize(611, 441);

    table.rows = tmpT->Size();

    switch (mode) {
    case 0:
        ui->tableWidget->clear();
        UABTDraw();
        break;
    case 1:
        ui->tableWidget->clear();
        ULBTDraw();
        break;
    case 2:
        ui->tableWidget->clear();
        LBTDraw();
        break;
    case 3:
        ui->tableWidget->clear();
        HTDraw();
        break;
    case 4:
        ui->treeWidget->clear();
        TDraw();
        break;
    default:
        ui->StatusLabel->setText("Bad exception!");
        break;
    }
}

void MainWindow::on_TableSelector_currentIndexChanged(int index)
{
    DataDraw(index);
}

void MainWindow::UABTDraw() {
    auto ABtable = dynamic_cast<UnorderedABTable<int, Polynomial<int>>*>(table.container[0]);
    auto tw = ui->tableWidget;
    tw->setRowCount(table.rows);
    tw->setColumnCount(3);

    int tableCellSize = tw->width()/10;

    tw->setColumnWidth(0, tableCellSize);
    tw->setColumnWidth(1, tableCellSize);
    tw->setColumnWidth(2, tableCellSize * 8);

    tw->setHorizontalHeaderLabels({"Индекс", "Ключ", "Значение"});

    if (ABtable->Size() == 0) return;

    auto values = ABtable->GetRecords();

    QTableWidgetItem* tmp = new QTableWidgetItem();

    for (int i = 0; i < tw->rowCount(); i++) {
        tmp->setText(QString::number(i));
        tw->setItem(i, 0, tmp->clone());
    }
    for (int i = 0; i < tw->rowCount(); i++) {
        tmp->setText(QString::number(values[i].key));
        tw->setItem(i, 1, tmp->clone());
    }
    for (int i = 0; i < tw->rowCount(); i++) {
        tmp->setText(QString::fromStdString(values[i].val.GetPolynomial()));
        tw->setItem(i, 2, tmp->clone());
    }
    delete tmp;
}

void MainWindow::ULBTDraw() {
    auto tw = ui->tableWidget;
    auto LBtable = dynamic_cast<UnorderedLBTable<int, Polynomial<int>>*>(table.container[1]);
    tw->setRowCount(table.rows);
    tw->setColumnCount(2);

    int tableCellSize = tw->width()/10;

    tw->setColumnWidth(0, tableCellSize*2);
    tw->setColumnWidth(1, tableCellSize*8);

    tw->setHorizontalHeaderLabels({"Ключ", "Значение"});

    auto recs = LBtable->GetRecords();

    QTableWidgetItem* fTmp = new QTableWidgetItem();
    QTableWidgetItem* sTmp = new QTableWidgetItem();
    int i = 0;
    for (auto it = recs.Begin(); it != recs.End(); it++) {
        fTmp->setText(QString::number(it.target->value.key));
        sTmp->setText(QString::fromStdString(it.target->value.val.GetPolynomial()));
        tw->setItem(i, 0, fTmp->clone());
        tw->setItem(i, 1, sTmp->clone());
        i++;
    }
    delete fTmp;
    delete sTmp;
}

void MainWindow::LBTDraw() {
    auto tw = ui->tableWidget;
    auto Ltable = dynamic_cast<OrderedListTable<int, Polynomial<int>>*>(table.container[2]);
    tw->setRowCount(table.rows);
    tw->setColumnCount(2);

    int tableCellSize = tw->width()/10;

    tw->setColumnWidth(0, tableCellSize*2);
    tw->setColumnWidth(1, tableCellSize*8);

    tw->setHorizontalHeaderLabels({"Ключ", "Значение"});

    auto recs = Ltable->GetRecords();

    QTableWidgetItem* fTmp = new QTableWidgetItem();
    QTableWidgetItem* sTmp = new QTableWidgetItem();
    int i = 0;
    for (auto it = recs.Begin(); it != recs.End(); it++) {
        fTmp->setText(QString::number(it.target->value.key));
        sTmp->setText(QString::fromStdString(it.target->value.val.GetPolynomial()));
        tw->setItem(i, 0, fTmp->clone());
        tw->setItem(i, 1, sTmp->clone());
        i++;
    }
    delete fTmp;
    delete sTmp;
}

void MainWindow::HTDraw() {
    auto tw = ui->tableWidget;
    auto Htable = dynamic_cast<ChainedHashTable<int, Polynomial<int>>*>(table.container[3]);
    tw->setRowCount(table.rows);
    tw->setColumnCount(3);

    int tableCellSize = tw->width()/10;

    tw->setColumnWidth(0, tableCellSize);
    tw->setColumnWidth(1, tableCellSize);
    tw->setColumnWidth(2, tableCellSize*8);

    tw->setHorizontalHeaderLabels({"Хэш", "Ключ", "Значение"});

    auto recs = Htable->GetRecords();

    QTableWidgetItem* fTmp = new QTableWidgetItem();

    int cRow = 0;
    for (int curListIndex = 0; curListIndex < BUCKETS; curListIndex++) {
        auto curList = recs[curListIndex];
        if(curList.IsEmpty()) continue;
        fTmp->setText(QString::number(curListIndex));
        tw->setItem(cRow, 0, fTmp->clone());

        for (auto it = curList.Begin(); it != curList.End(); it++) {
            fTmp->setText(QString::number(it.target->value.key));
            tw->setItem(cRow, 1, fTmp->clone());
            fTmp->setText(QString::fromStdString(it.target->value.val.GetPolynomial()));
            tw->setItem(cRow, 2, fTmp->clone());
            cRow++;
        }
    }

    delete fTmp;

}

QTreeWidgetItem* MainWindow::TreeCross(QTreeWidgetItem* item, const Node<int, Polynomial<int>>* node) {
    if (node) {
        item->setText(0, QString::number(node->key));
        item->setText(1, QString::fromStdString(node->value.GetPolynomial()));

        if (node->pLeft) {
            QTreeWidgetItem* ch1 = new QTreeWidgetItem();
            auto ch1Node = node->pLeft;

            TreeCross(ch1, ch1Node);
            item->addChild(ch1->clone());

            delete ch1;
        }

        if (node->pRight) {
            QTreeWidgetItem* ch2 = new QTreeWidgetItem();
            auto ch2Node = node->pRight;

            TreeCross(ch2, ch2Node);
            item->addChild(ch2->clone());

            delete ch2;
        }
    }
    return item;
}

void MainWindow::TDraw() {
    auto tw = ui->treeWidget;
    auto tree = dynamic_cast<AVLTree<int, Polynomial<int>>*>(table.container[4]);
    if (!tree->GetRoot()) return;

    tw->resize(611, 441);
    ui->tableWidget->resize(0,0);
    tw->setColumnCount(2);

    int tableCellSize = tw->width()/10;

    tw->setColumnWidth(0, tableCellSize*4);
    tw->setColumnWidth(1, tableCellSize*6);
    tw->setHeaderLabels({"Ключ", "Значение"});

    auto rootNode = tree->GetRoot();
    QTreeWidgetItem* item = new QTreeWidgetItem();

    tw->addTopLevelItem(TreeCross(item->clone(), rootNode));

    delete item;
}


void MainWindow::on_PushButton_clicked()
{
    QString key = ui->KeyInputField->text();
    QString value = ui->ValueInputField->text();
    if (key.isEmpty() || value.isEmpty()) {
        ui->StatusLabel->setText("Одно из полей неверно заполнено!");
        return;
    }

    try {
        auto polynomialData = std::istringstream(value.toStdString());
        Polynomial<int> pol;
        polynomialData >> pol;
        table.Insert(key.toInt(), pol);
    } catch (...) {
        ui->StatusLabel->setText("Одно из полей неверно заполнено!");
        return;
    }
    DataDraw(ui->TableSelector->currentIndex());
}


void MainWindow::on_RemoveButton_clicked() {
    QString key = ui->KeyInputField->text();
    if (key.isEmpty()) {
        ui->StatusLabel->setText("Одно из полей неверно заполнено!");
        return;
    }

    try {
        table.Remove(ui->TableSelector->currentIndex(), key.toInt());
    } catch (...) {
        ui->StatusLabel->setText("Одно из полей неверно заполнено!");
        return;
    }
    DataDraw(ui->TableSelector->currentIndex());
}

void MainWindow::TSearchHighlight(int key, int columnKeyId) {
    for (int i = 0; i < ui->tableWidget->rowCount(); i++) {
        if (ui->tableWidget->item(i, columnKeyId)->text().toInt() == key) {
            ui->tableWidget->scrollToItem(ui->tableWidget->item(i, columnKeyId));

            for (int j = 0; j < ui->tableWidget->columnCount(); j++) {
                ui->tableWidget->item(i, j)->setBackground(QBrush(QColorConstants::Svg::lightgrey));
            }
            return;
        }
    }

    ui->StatusLabel->setText("Элемент не существует!");
}

void MainWindow::LSearchHighlight(int key, int columnKeyId) {

    auto mtc = ui->treeWidget->findItems(QString::number(key), Qt::MatchFixedString | Qt::MatchRecursive, columnKeyId);
    if (mtc.empty()) {
        ui->StatusLabel->setText("Элемент не существует!");
        return;
    }

    ui->treeWidget->setCurrentItem(*mtc.begin());
}

void MainWindow::on_SearchButton_clicked() {
    QString key = ui->KeyInputField->text();
    if (key.isEmpty()) {
        ui->StatusLabel->setText("Одно из полей неверно заполнено!");
        return;
    }

    try {
        switch (ui->TableSelector->currentIndex()) {
        case 0:
            TSearchHighlight(key.toInt(), 1);
            break;
        case 1:
            TSearchHighlight(key.toInt(), 0);
            break;
        case 2:
            TSearchHighlight(key.toInt(), 0);
            break;
        case 3:
            TSearchHighlight(key.toInt(), 1);
            break;
        case 4:
            LSearchHighlight(key.toInt(), 0);
            break;
        default:
            ui->StatusLabel->setText("Одно из полей неверно заполнено!");
            return;
        }
    } catch (...) {
        ui->StatusLabel->setText("Одно из полей неверно заполнено!");
        return;
    }
}


