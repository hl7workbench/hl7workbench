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

#include "Hl7MessageEditorWidget.h"

Hl7MessageEditorTabWidget::Hl7MessageEditorTabWidget(QWidget *parent) :
    QTabWidget(parent),
    m_untitledDocumentIds()
{
    connect(this, &QTabWidget::tabCloseRequested,
            this, qOverload<int>(&Hl7MessageEditorTabWidget::closeTab));

    setTabsClosable(true);

    // TODO: add logic for opening last opened files
    // otherwise
    {
        newFile();
    }
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

void Hl7MessageEditorTabWidget::fileNameChangedInEditor(QString newFileName)
{
    int index = indexOf(qobject_cast<Hl7MessageEditorWidget*>(sender()));
    if (index != -1)
    {
        setTabText(index, newFileName);
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

    connect(w, &Hl7MessageEditorWidget::fileNameChanged,
            this, &Hl7MessageEditorTabWidget::fileNameChangedInEditor);
    connect(w, &Hl7MessageEditorWidget::removeUntitledDocumentId,
            this, &Hl7MessageEditorTabWidget::removeUntitledDoucmentId);

    addTab(w, w->fileName());
    setCurrentWidget(w);
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
