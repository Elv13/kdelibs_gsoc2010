/*  This file is part of the KDE libraries
 *  Copyright (C) 1999 Waldo Bastian <bastian@kde.org>
 *                2000, 2007 David Faure   <faure@kde.org>
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Library General Public
 *  License version 2 as published by the Free Software Foundation;
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Library General Public License for more details.
 *
 *  You should have received a copy of the GNU Library General Public License
 *  along with this library; see the file COPYING.LIB.  If not, write to
 *  the Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,
 *  Boston, MA 02110-1301, USA.
 **/

#ifndef KFOLDERMIMETYPE_H
#define KFOLDERMIMETYPE_H

#include "kmimetype.h"

class KFolderMimeTypePrivate;

/**
 * @internal  - this header is not installed
 *
 * Folder mime type. Handles the .directory file inside a folder, which modifies
 * the comment and icon for this folder.
 * @short Mimetype for a folder (inode/directory)
 */
class KDECORE_EXPORT KFolderMimeType : public KMimeType
{
    Q_DECLARE_PRIVATE( KFolderMimeType )

public:
    /** \internal */
    KFolderMimeType( const QString& fullpath, const QString& name, const QString& comment );

    /** \internal */
    KFolderMimeType( QDataStream& str, int offset );

    /** Destructor. */
    ~KFolderMimeType();
};

#endif
