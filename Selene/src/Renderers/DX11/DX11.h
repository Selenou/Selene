#pragma once

#include <d3d11.h>
#include <wrl.h> // ComPtr
#include "Selene/Core/Macro.h"

namespace Selene
{
    inline bool CheckHResult(HRESULT hresult, std::string_view statement, std::string_view file, UINT line)
    {
        if (FAILED(hresult))
        {
            // Check output tab in VS in order to see the actual error
            // The formatted string in errorText is bad here, moreover the log is pretty much useless with the sample below
            // We should use the message in the output tab in our console

            //LPSTR errorText;
            //FormatMessageA(FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_IGNORE_INSERTS, nullptr, hresult, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPSTR)&errorText, 0, nullptr);
            //SLN_ASSERT(false, "DX11 Call Error!");
            // Release memory allocated by FormatMessage()
            //LocalFree(errorText);
            //errorText = NULL;

            SLN_ERROR("%s failed (File : %s(%d))", statement.data(), file.data(), line);

            return false;
        }
        return true;
    }

    #if SLN_DEBUG
        #define THROW_DX11_FAILURE(func)\
        {\
            HRESULT hr = func;\
            CheckHResult((hr), #func, __FILE__, __LINE__ );\
        }
    #else
        #define THROW_DX11_FAILURE(func) (func)
    #endif
}