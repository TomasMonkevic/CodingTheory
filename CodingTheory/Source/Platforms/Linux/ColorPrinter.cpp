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
#ifdef _WIN32
		//int result = vsscanf_s(buffer, format, vaArgs);
#else
		int result = vprintf(format, vaArgs);
#endif
		va_end(vaArgs);
    }
}