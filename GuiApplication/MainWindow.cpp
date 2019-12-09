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

    connect(ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::viewedFileNameChanged,
            this, &MainWindow::viewedFileNameChanged);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::viewedFileNameChanged(QString fileName)
{
    setWindowTitle(QString("HL7 Workbench [%1]").arg(fileName));
}

void MainWindow::on_actionFile_Exit_triggered()
{
    close();
}
