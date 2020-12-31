#ifndef DATEFORMATDELEGATE_H
#define DATEFORMATDELEGATE_H

#include <QStyledItemDelegate>


class DateTimeFormatDelegate : public QStyledItemDelegate
{
    Q_OBJECT

public:
    DateTimeFormatDelegate();
    ~DateTimeFormatDelegate();
    QString displayText(const QVariant &value,
                        const QLocale &locale) const override;
};

#endif // DATEFORMATDELEGATE_H
