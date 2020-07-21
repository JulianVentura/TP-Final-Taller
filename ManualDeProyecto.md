# Manual de Proyecto

### Autores: Ventura Julian, Barreneche Franco, More Agustín

## Resumen de Enunciado

Se desea implementar un juego de rol multijugador masivo online. El mismo debe
contar con clases, razas, armamento dinámico y enemigos. Se debe incorporar un
sistema básico de economía con tiendas y banqueros, asi como un sistema de
drops. A nivel visual se deben mostrar los elementos equipados, rasgos distintivos
de cada raza y clase y un renderizado de mapa en perspectiva de vista de ágila.

## Division de Tareas

Durante  el transcurso del proyecto se mantuvo un constante intercambio de ideas y
opiniones respecto al modelo de cada sistema. Tampoco faltaron las ocasiones en 
las que un integrante auxiliaba a otro en el desarrollo de un aspecto crítico.
La siguiente división de tareas es , por lo tanto, tentativa y puede desmerecer
el esfuerzo de determinados miembros del grupo en algún punto.

Renderizado de personajes y animaciones - More Agustín
Renderizado de efectos - More Agustín
Renderizado de mapa - More Agustín
Representaciónde texto - Barreneche Franco, More Agustín
Reproducción de música y sonidos - Barreneche Franco
Interfaz gráfica - Barreneche Franco
Mini Chat - Barreneche Franco
Pantalla de login - Barreneche Franco
Carga/descarga de entidades y colisiones - Julian Ventura
Lógica de las ciudades y “fair play” - Julian Ventura
Compra, venta y otros comandos - Julian Ventura
Ataque,defensa y drops - Julian Ventura
Configuración - Julian Ventura
Persistencia - Barreneche Franco
Persistencia periódica - Julian Ventura
Herramientas de depuración intermedias - More Agustín
Comunicación y protocolo - Ventura Julian, Barreneche Franco, More Agustín
Pruebas, balance y mejoras de estabilidad - Ventura Julian, Barreneche Franco, More Agustín

## Cronograma

#### Servidor

El desarrollo del mapa y la lógica de comunicación llevo mucho más de lo esperado.
Hasta la semana 3 no fue posible conectar cliente y servidor exitosamente. No obstante
el trabajo previo sentó una base fuerte, sobre la que ráìdamente se construyó la lógica
de ataque, enemigos, drops y restricciones de "fair play" durante la semana 4 y 5.
La sexta semana se reservó para afinar la persistencia y salvar problemas emergentes
de gran importancia.

#### Cliente

A diferencia del servidor, durante las primeras 3 semanas se pudo cumplir con el
cronograma propuesto, es decir, pudo formularse velozmente la estructura general
del cliente. El tiempo restante se invirtió en adaptar dicha estructura a la
información que efectivamente se obtenía desde el servidor y resolver condiciones
de carrera. También se debió reservar parte del cronograma a la adquicision de recursos
audiovisuales compatibles con la estética y la atmósfera esperada.