#pragma once

namespace TomasMo
{
    class ColorPrinter
    {
    public:
        enum Color
        {
            White = 0,
            Red,
            Green,
            Blue,
        };

        static void Print(ColorPrinter::Color color, const char* format, ...);
    };
}
