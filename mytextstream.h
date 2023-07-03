#ifndef MYTEXTSTREAM_H
#define MYTEXTSTREAM_H

#include <QString>
#include <QStringBuilder>
#include <QTextStream>

class MyTextStream : public QTextStream
{
    public:
        MyTextStream(QString* str) : QTextStream(str) {}

        MyTextStream& operator>>(QString& str)
        {
            QChar ch;

            while (!atEnd())
            {
                QTextStream::operator>>(ch);

                if (ch == '\t' || ch == ' ')
                    break;

                str = str % ch;
            }

            return *this;
        }
};

#endif // MYTEXTSTREAM_H
