#include "mainwindow.h"

#include <QFileDialog>
#include <QTableView>

MainWindow::MainWindow()
{
    table = new TableView;
    setWindowTitle(tr("Password Manager"));
    setCentralWidget(table);
    createMenus();
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    toolsMenu = menuBar()->addMenu(tr("&Tools"));
    loadAct = new QAction(tr("Open Password File..."), this);
    fileMenu->addAction(loadAct);
    connect(loadAct, SIGNAL(triggered()), this, SLOT(loadFile()));
    saveAct = new QAction(tr("Save Passwords to file"), this);
    fileMenu->addAction(saveAct);
    connect(saveAct, SIGNAL(triggered()), this, SLOT(saveFile()));
    exit = new QAction(tr("Exit"), this);
    fileMenu->addAction(exit);
    connect(exit, SIGNAL(triggered()), this, SLOT(close()));

    addAct = new QAction(tr("Add password"), this);
    toolsMenu->addAction(addAct);
    connect(addAct, SIGNAL(triggered()), table, SLOT(addAction()));
    modAct = new QAction(tr("Modify password"), this);
    toolsMenu->addAction(modAct);
    connect(modAct, SIGNAL(triggered()), table, SLOT(modAction()));
    delAct = new QAction(tr("Delete password"), this);
    toolsMenu->addAction(delAct);
    connect(delAct, SIGNAL(triggered()), table, SLOT(delAction()));
}

void MainWindow::loadFile()
{
    QString filename = QFileDialog::getOpenFileName(this);
    if (!filename.isEmpty())
        table->readFromFile(filename);
}

void MainWindow::saveFile()
{
    QString filename = QFileDialog::getSaveFileName(this);
    if (!filename.isEmpty())
        table->saveToFile(filename);
}
