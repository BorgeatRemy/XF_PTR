#include "config/trace-config.h"

#if (USE_PLATFORM_QT_TRACE != 0)

#include <QDebug>
#include "trace/trace.h"

#include <QTime>

#define ADD_CRLF_SEQU 	0

//static
void Trace::initialize()
{

}

void Trace::out(string str)
{
    qDebug() << QDateTime::currentDateTime().toString("[hh:mm:ss,zzz]") << str.data();
}

void Trace::out(const char * format, ...)
{
    char str[255];

    va_list args;

    va_start(args, format);
    vsprintf(str, format, args);
    va_end(args);

    qDebug() << QDateTime::currentDateTime().toString("[hh:mm:ss,zzz]") << str;
}

#endif // USE_PLATFORM_QT_TRACE
