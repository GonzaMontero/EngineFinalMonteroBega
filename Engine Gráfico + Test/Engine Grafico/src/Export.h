#ifndef EXPORT_H

#ifdef ENGINE_EXPORT
#define ENGINE_API __declspec(dllimport) //clase para exportacion
#else
#define ENGINE_API  __declspec(dllexport)  // especifica clase para importacion
#endif // ENGINE_EXPORT

#endif // !EXPORT_H