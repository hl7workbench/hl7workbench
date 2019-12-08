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

    connect(ui->actionNewFile, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::newFile);
    connect(ui->actionCloseCurrentFile, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::closeCurrentTab);
    connect(ui->actionCloseAllFiles, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::closeAllTabs);
    connect(ui->actionCloseAllExceptCurrentFile, &QAction::triggered,
            ui->messageEditorTabWidget, &Hl7MessageEditorTabWidget::closeAllExceptCurrentTab);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionExit_triggered()
{
    close();
}
