/*
    Copyright (c) 2014, Gunnar Sletta
    All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this
      list of conditions and the following disclaimer.

    * Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.

    THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
    AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
    IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
    DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
    FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
    DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
    SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
    CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
    OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
    OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef FILETRACKER_H
#define FILETRACKER_H

#include <QtCore>

#include "global.h"

class FileTracker : public QObject
{
    Q_OBJECT
public:

    struct Entry {
        QString path;
        QHash<QString, quint64> content;
    };

    explicit FileTracker(QObject *parent = 0);

    QHash<QString, Entry> trackingSet() const;

    bool track(const QString &id, const QString &path);
    bool untrack(const QString &id);

signals:
    void fileChanged(const QString &id, const QString &filePath);
    void fileAdded(const QString &id, const QString &filePath);
    void fileRemoved(const QString &id, const QString &filePath);

private slots:
    void onDirChange(const QString &);

private:
    Entry createEntry(const QFileInfo &info);
    QString idFromPath(const QString &path) const;

    QHash<QString, Entry> m_set;
    QSet<QString> m_suffixes;

    QFileSystemWatcher m_watcher;
};

#endif // FILETRACKER_H
