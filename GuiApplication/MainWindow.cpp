/*
 * This file is part of the HL7 Workbench project.
 *
 * Copyright (C) 2019  Individual HL7 Workbench contributors.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include "Hl7MessageEditorTabWidget.h"

#include "MessageLogModel.h"

namespace HL7WB
{

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->actionFile_New, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::newFile);

    connect(ui->actionFile_Open, &QAction::triggered,
            ui->messageEditorTabWidget, qOverload<>(&Hl7MessageEditorTabWidget::openFile));

    connect(ui->actionFile_Save, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::saveFile);
    connect(ui->actionFile_SaveAs, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::saveFileAs);
    connect(ui->actionFile_SaveAll, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::saveAllFiles);

    connect(ui->actionFile_Close, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::closeCurrentTab);
    connect(ui->actionFile_CloseAll, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::closeAllTabs);
    connect(ui->actionFile_CloseOthers, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::closeAllExceptCurrentTab);

    connect(ui->actionEdit_Undo, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::undo);
    connect(ui->actionEdit_Redo, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::redo);

    connect(ui->actionEdit_Cut, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::cut);
    connect(ui->actionEdit_Copy, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::copy);
    connect(ui->actionEdit_Paste, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::paste);
    connect(ui->actionEdit_Delete, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::removeSelectedText);

    connect(ui->actionEdit_SelectAll, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::selectAll);

    connect(ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::copyAvailable,
            this, &MainWindow::copyAvailable);
    connect(ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::redoAvailable,
             this, &MainWindow::redoAvailable);
    connect(ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::undoAvailable,
            this, &MainWindow::undoAvailable);
    connect(ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::viewedFileNameChanged,
            this, &MainWindow::viewedFileNameChanged);

    ui->senderMessageLogView->setModel(new MessageLogModel(this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::copyAvailable(bool available)
{
    ui->actionEdit_Copy->setEnabled(available);
    ui->actionEdit_Cut->setEnabled(available);
}

void MainWindow::on_actionFile_Exit_triggered()
{
    close();
}

void MainWindow::redoAvailable(bool available)
{
    ui->actionEdit_Redo->setEnabled(available);
}

void MainWindow::undoAvailable(bool available)
{
    ui->actionEdit_Undo->setEnabled(available);
}

void MainWindow::viewedFileNameChanged(QString fileName)
{
    setWindowTitle(QString("HL7 Workbench [%1]").arg(fileName));
}

}
