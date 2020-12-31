#include <QDateTime>

#include "datetimeformatdelegate.h"


DateTimeFormatDelegate::DateTimeFormatDelegate()
{}

DateTimeFormatDelegate::~DateTimeFormatDelegate()
{}

QString DateTimeFormatDelegate::displayText(const QVariant &value,
                                            const QLocale &locale) const
{
    Q_UNUSED(locale)

    QDateTime timestamp = QDateTime::fromSecsSinceEpoch(value.toLongLong());
    return timestamp.toString("hh:mm:ss ddd, d MMM yyyy");
}
