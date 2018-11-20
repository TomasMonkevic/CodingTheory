#pragma once

namespace TomasMo
{
    class ColorPrinter
    {
    public:
        enum Color
        {
            Red = 1,
            Green = 2,
            Blue = 4
        };

        static void Print(ColorPrinter::Color color, const char* format, ...);
    };
}
