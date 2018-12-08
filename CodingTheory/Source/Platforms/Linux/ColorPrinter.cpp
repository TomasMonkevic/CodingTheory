#include "../../../Include/ColorPrinter.h"
#include <cstdio>
#include <string.h>
#include <cstdarg>

namespace TomasMo
{
    void ColorPrinter::Print(ColorPrinter::Color color, const char* format, ...)
    {
        va_list vaArgs;
		va_start(vaArgs, format);
        char* colorFormat = new char[strlen(format)+32];
        switch(color)
        {
            case ColorPrinter::White:
                strcat(colorFormat, "\033[37m");
                break;
            case ColorPrinter::Red:
                strcat(colorFormat, "\033[31m");
                break;            
            case ColorPrinter::Green:
                strcat(colorFormat, "\033[32m");
                break;            
            case ColorPrinter::Blue:
                strcat(colorFormat, "\033[34m");
                break;            
            default:
                strcat(colorFormat, "\033[0m");
                break;
        }
        strcat(colorFormat, format);
        strcat(colorFormat, "\033[0m");
		int result = vprintf(colorFormat, vaArgs);
		va_end(vaArgs);
        delete[] colorFormat;
    }
}