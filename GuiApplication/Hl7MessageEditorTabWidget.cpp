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

#include "HL7MessageEditorWidget.h"

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
    if (HL7MessageEditorWidget *w =
        qobject_cast<HL7MessageEditorWidget*>(widget(index)))
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

    HL7MessageEditorWidget *w = new HL7MessageEditorWidget(i, this);
    addTab(w, w->filename());
    setCurrentWidget(w);
}

void Hl7MessageEditorTabWidget::removeUntitledDoucmentId(int id)
{
    m_untitledDocumentIds.removeAll(id);
}
