#ifndef __adaptarSistemasOp_H__
#define __adaptarSistemasOp_H__

#ifdef __linux__
#define LIMPIAR "clear"
define MOVER "mv"
#endif // __linux__
 
#ifdef __MINGW32__
#define LIMPIAR "cls"
#define MOVER "move"
#endif // __MINGW32__
 
#ifdef __APPLE__
#define LIMPIAR "clear"
#define MOVER "mv"
#endif // __APPLE__

#endif // __adaptarSistemasOp_H__