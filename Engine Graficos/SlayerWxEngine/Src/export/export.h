#ifndef EXPORTS_H
#define EXPORTS_H

#ifdef SlayerWxEngine_Exports
#define SlayerWxEngine_API __declspec(dllimport) //Specify class for export
#else
#define SlayerWxEngine_API __declspec(dllexport) //Specify class for export
#endif

#endif