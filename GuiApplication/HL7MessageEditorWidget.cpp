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

#include "HL7MessageEditorWidget.h"

HL7MessageEditorWidget::HL7MessageEditorWidget(int untitledDocumentId,
                                               QWidget *parent) :
    QTextEdit(parent),
    m_filename(QString("Untitled %1.hl7").arg(untitledDocumentId)),
    m_untitledDocumentId(untitledDocumentId)
{
    QFont f = currentFont();

    setFont(QFont("Ubuntu Mono", f.pointSize()));
}

HL7MessageEditorWidget::HL7MessageEditorWidget(const QString &filename,
                                               QWidget *parent) :
    QTextEdit(parent),
    m_filename(filename),
    m_untitledDocumentId(-1)
{
}

const QString &HL7MessageEditorWidget::filename() const
{
    return m_filename;
}

int HL7MessageEditorWidget::untitledDocumentId() const
{
    return m_untitledDocumentId;
}
