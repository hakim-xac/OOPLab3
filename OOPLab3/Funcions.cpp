#include "Funcions.h"

namespace KHAS {
    namespace Functions {
        COLORREF rgbToCOLORREF(int r, int g, int b)
        {
            return (r | (g << 8) | (b << 16));
        }
    }
}
