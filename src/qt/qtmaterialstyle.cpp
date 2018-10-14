#include "qtmaterialstyle.h"
#include <QFontDatabase>
#include "qtmaterialtheme.h"

/*!
 *  \class QtMaterialStylePrivate
 *  \internal
 */

QtMaterialStylePrivate::QtMaterialStylePrivate(QtMaterialStyle *q)
    : q_ptr(q)
{
}

QtMaterialStylePrivate::~QtMaterialStylePrivate()
{
}

void QtMaterialStylePrivate::init()
{
    Q_Q(QtMaterialStyle);
    q->setTheme(new QtMaterialTheme);
}

/*!
 *  \class QtMaterialStyle
 *  \internal
 */

void QtMaterialStyle::setTheme(QtMaterialTheme *theme)
{
    Q_D(QtMaterialStyle);

    d->theme = theme;
    theme->setParent(this);
}

QColor QtMaterialStyle::themeColor(const QString &key) const
{
    Q_D(const QtMaterialStyle);

    Q_ASSERT(d->theme);

    return d->theme->getColor(key);
}

QtMaterialStyle::QtMaterialStyle()
    : QCommonStyle(),
      d_ptr(new QtMaterialStylePrivate(this))
{
    d_func()->init();
}
