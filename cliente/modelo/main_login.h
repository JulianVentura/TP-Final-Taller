#ifndef __MAIN_LOGIN_H__
#define __MAIN_LOGIN_H__

#include "../modelo/BucleLogin.h"
#include "../vista/GUI_Login.h"
#include "../vista/EntornoGrafico.h"
#include "../vista/EntornoMusical.h"
#include "../vista/Ventana.h"
#include "../vista/Colores.h"

int main_login(EntornoGrafico& entorno, Ventana& ventana,
 ServidorProxy& servidor, Colores& paleta);

#endif /*__MAIN_LOGIN_H__*/