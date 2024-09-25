// SPDX-License-Identifier: GPL-3.0-or-later

#ifndef OPTION_H
#define OPTION_H

#include <QVariant>

#include <functional>
#include <memory>

class QObject;

class OptionValueConverter {
public:
    virtual QVariant read(const QVariant &value) const = 0;
    virtual QVariant save(const QVariant &value) const = 0;
};

using OptionValueConverterPtr = std::shared_ptr<OptionValueConverter>;

/**
 * Configuration option.
 */
class Option final {
public:
    Option();

    /**
     * Create option with a default value.
     * Current value is taken from object's property.
     */
    explicit Option(
        const QVariant &default_value,
        const char *property_name,
        QObject *obj,
        OptionValueConverterPtr &&converter = nullptr
        );

    explicit Option(
        const QVariant &default_value,
        const char *description = nullptr
        );

    /** Return current value. */
    QVariant value() const;

    /** Set current value. */
    bool setValue(const QVariant &value);

    /** Reset option to default value. */
    void reset();

    /**
     * Tooltip for option.
     * This text is taken from toolTip property of a QObject which was passed
     * to constructor.
     */
    QString tooltip() const;

private:
    QVariant m_default_value;
    QVariant m_value;
    const char *m_property_name = nullptr;
    const char *m_description = nullptr;
    QObject *m_obj = nullptr;
    OptionValueConverterPtr m_converter = nullptr;
};

#endif // OPTION_H
