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

#include "Hl7MessageEditorTabWidget.h"

#include "Hl7GuiCommon.h"
#include "Hl7MessageEditorWidget.h"

#include <QAction>
#include <QFileDialog>
#include <QStandardPaths>
#include <QTextStream>

Hl7MessageEditorTabWidget::Hl7MessageEditorTabWidget(QWidget *parent) :
    QTabWidget(parent),
    m_untitledDocumentIds()
{
    connect(this, &QTabWidget::tabCloseRequested,
            this, qOverload<int>(&Hl7MessageEditorTabWidget::closeTab));

    setTabsClosable(true);

    connect(this, &QTabWidget::currentChanged,
            this, &Hl7MessageEditorTabWidget::currentTabChanged);
}

void Hl7MessageEditorTabWidget::closeTab(int index, bool openNewWhenLast)
{
    if (Hl7MessageEditorWidget *w =
        qobject_cast<Hl7MessageEditorWidget*>(widget(index)))
    {
        removeUntitledDoucmentId(w->untitledDocumentId());
    }

    removeTab(index);

    if (openNewWhenLast && 0 == count())
    {
        newFile();
    }
}

void Hl7MessageEditorTabWidget::closeAllExceptCurrentTab()
{
    QWidget *cw = currentWidget();

    while (count() > 1)
    {
        int i = indexOf(cw);
        closeTab((i == 0) ? 1 : 0);
    }
}

void Hl7MessageEditorTabWidget::closeAllTabs()
{
    while (count() > 0)
    {
        closeTab(0, false);
    }

    newFile();
}

void Hl7MessageEditorTabWidget::closeCurrentTab()
{
    closeTab(currentIndex());
}

void Hl7MessageEditorTabWidget::closeTab(int index)
{
    closeTab(index, true);
}

void Hl7MessageEditorTabWidget::currentTabChanged(int index)
{
    if (Hl7MessageEditorWidget *w =
            qobject_cast<Hl7MessageEditorWidget*>(widget(index)))
    {
        emit viewedFileNameChanged(w->fileName());
    }
}

void Hl7MessageEditorTabWidget::fileNameChangedInEditor(QString newFileName)
{
    int index = indexOf(qobject_cast<Hl7MessageEditorWidget*>(sender()));
    if (index != -1)
    {
        setTabText(index, newFileName);

        if (index == currentIndex())
        {
            emit viewedFileNameChanged(newFileName);
        }
    }
}

void Hl7MessageEditorTabWidget::filePathChangedInEditor(QString newFilePath)
{
    int index = indexOf(qobject_cast<Hl7MessageEditorWidget*>(sender()));
    if (index != -1)
    {
        setTabToolTip(index, newFilePath);
    }
}

void Hl7MessageEditorTabWidget::newFile()
{
    int i = 0;
    for (; i < m_untitledDocumentIds.size(); i++)
    {
        if (m_untitledDocumentIds[i] != i + 1)
            break;
    }

    i++;
    m_untitledDocumentIds.insert(i-1, i);

    Hl7MessageEditorWidget *w = new Hl7MessageEditorWidget(i, this);
    newTab(w);
}

void Hl7MessageEditorTabWidget::newTab(Hl7MessageEditorWidget *widget)
{
    connect(widget, &Hl7MessageEditorWidget::fileNameChanged,
            this, &Hl7MessageEditorTabWidget::fileNameChangedInEditor);
    connect(widget, &Hl7MessageEditorWidget::filePathChanged,
            this, &Hl7MessageEditorTabWidget::filePathChangedInEditor);
    connect(widget, &Hl7MessageEditorWidget::removeUntitledDocumentId,
            this, &Hl7MessageEditorTabWidget::removeUntitledDoucmentId);

    QString fileName = widget->fileName();
    int index = addTab(widget, fileName);
    setTabToolTip(index, fileName);
    setCurrentWidget(widget);
    emit viewedFileNameChanged(fileName);
}

void Hl7MessageEditorTabWidget::openFile()
{
    QString folder;
    if (Hl7MessageEditorWidget *w = qobject_cast<Hl7MessageEditorWidget*>(currentWidget()))
    {
        if (w->untitledDocumentId() == -1)
        {
            folder = QFileInfo(w->filePath()).absolutePath();
        }
        else
        {
            QStringList documentLocations =
                    QStandardPaths::standardLocations(QStandardPaths::DocumentsLocation);

            if (documentLocations.count() > 0)
            {
                folder = documentLocations[0];
            }
            else
            {
                folder = QDir::currentPath();
            }
        }
    }

    QFileDialog openDialog(this,
                           "Open File",
                           folder,
                           HL7_FILE_FILTER);
    openDialog.setAcceptMode(QFileDialog::AcceptOpen);

    if (QDialog::Accepted == openDialog.exec() &&
            1 == openDialog.selectedFiles().count())
    {
        openFile(QDir(folder).absoluteFilePath(openDialog.selectedFiles()[0]));
    }
}

void Hl7MessageEditorTabWidget::openRecentFile()
{
    if (QAction *action = qobject_cast<QAction*>(sender()))
    {
        openFile(action->property("filePath").toString());
    }
}

void Hl7MessageEditorTabWidget::removeUntitledDoucmentId(int id)
{
    m_untitledDocumentIds.removeAll(id);
}

void Hl7MessageEditorTabWidget::saveFile()
{
    if (Hl7MessageEditorWidget *w =
            qobject_cast<Hl7MessageEditorWidget*>(currentWidget()))
    {
        w->saveFile();
    }
}

void Hl7MessageEditorTabWidget::saveFileAs()
{
    if (Hl7MessageEditorWidget *w =
            qobject_cast<Hl7MessageEditorWidget*>(currentWidget()))
    {
        w->saveFileAs();
    }
}

void Hl7MessageEditorTabWidget::saveAllFiles()
{
    for (int i = 0; i < count(); i++)
    {
        if (Hl7MessageEditorWidget *w =
                qobject_cast<Hl7MessageEditorWidget*>(widget(i)))
        {
            w->saveFileAs();
        }
    }
}

void Hl7MessageEditorTabWidget::showEvent(QShowEvent *e)
{
    QTabWidget::showEvent(e);

    if (count() == 0)
    {
        newFile();
    }
}

void Hl7MessageEditorTabWidget::openFile(const QString &filePath)
{
    QFile file(filePath);

    if (file.open(QFile::ReadOnly | QFile::Text))
    {
        QTextStream stream(&file);

        QString plainText = stream.readAll();

        file.close();

        Hl7MessageEditorWidget *w = new Hl7MessageEditorWidget(plainText,
                                                               QFileInfo(file),
                                                               this);
        newTab(w);
    }
}
