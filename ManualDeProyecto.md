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

### Inconvenientes encontrados

#### Servidor

Las parte mas desafiante del servidor fue sin lugar a dudas, el diseño del mismo, tarea que llevo varios días de análisis en la primer semana de desarrollo. Se puede mencionar también a la relación entre las entidades y el diseño del mapa como dos problemas importantes atravesar a lo largo del desarrollo.

Llegados a la primera entrega fue muy evidente la necesidad de una refactorización de las relaciones de las entidades y del mapa, ya que el programa entregado no era escalable. Se considera que tras la refactorización el código resulto ser mucho mas amigable, prolijo y extensible.

Debido a los problemas antes mencionados el tiempo comenzó a jugar en contra, y sumado a la cantidad de errores surgidos al intentar unir los trabajos realizados en el cliente y servidor, fue imposible llegar a la primera fecha de entrega con un trabajo solido que demuestre realmente el esfuerzo invertido.

Dicho esto, se cree que el trabajo mejoro notablemente una vez superados estos problemas, ya que la base de desarrollo comenzó a ser bastante mas clara.

#### Cliente

Se encontraron numerosos desafíos a la hora de diseñar e implementar el modelo del cliente, sin embargo solo uno de ellos destaca por encima de los otros. En el modelo concebido el cliente envía operaciones y recibe datos de actualización, pero no puede correlacionar los efectos con sus causas. En el caso del funcionamiento ligado al servidor este no es un inconveniente, pues la lógica la resuelve él mismo. La adición de efectos de sonido y animaciones adicionales en cambio, requirió un balance de supuestos y de suma de características a la comunicación cliente-servidor. 



### Análisis de puntos pendientes

El modelo presentado permite bastante escalabilidad en cuanto a mapas, criaturas, entidades e items se refiere, el hecho de haber logrado ciertas generalizaciones en las clases del servidor permite que incluso se puedan agregar nuevos elementos al modelo únicamente modificando el archivo de configuraciones, obviamente será necesario indicar sprites de dibujo del lado del cliente.

Dentro de los puntos pendientes del trabajo podemos mencionar:

* Creación de más mapas, en los cuales se pueda definir el spawn de distintas criaturas relacionadas al medio ambiente que habitan.

* Creación de más criaturas, para tener una jugabilidad mas lineal y que el jugador se sienta siempre desafiado al jugar sin importar su nivel. Creación de mini jefes en mapas especiales, estilo catacumbas, que dropeen items únicos.

* Distintos tipos de armas que permitan implementar distintas ecuaciones de daño según los atributos del personaje, con el objetivo de impulsar al jugador a elegir una clase y raza y llevar el rol de la misma en todo aspecto del juego. Penalizaciones o ventajas en distintas piezas del equipo en base a los atributos del personaje, como puede ser la defensa de las armaduras en función de la fuerza del personaje.

* Refactorización del GUI_Login, al igual que se separo en vista y controlador a GUI_Principal.

* Mejorar el sprite de los arcos.

* Cambiar la filosofia de desconexion polite del lado del servidor por una violenta. Al principio pareció una buena idea seguir esta filosofia ya que fue la implementada en el TP3 y sobre la cual mas conocimiento se tenia, sin embargo en los últimos momentos del trabajo se hizo notar el principal error de la, que obviamente, el servidor no tiene control sobre la desconexión de un cliente, por lo tanto un cliente que no se desconecte puede dejar esperando al servidor ante un necesario apagado. La única solución en ese caso seria cancelar la ejecución del servidor violentamente.

* Confección de un instalador propiamente dicho, más amigable a usuarios generales.

  


### Herramientas

Para la elaboración del trabajo se utilizaron las siguientes herramientas:

* valgrind: Para resolver problemas de memoria y garantizar una correcta administración de los recursos de la computadora.
* gdb: Para resolver bugs pequeños tanto del servidor como del cliente.
* Visual Studio Code: Como editor de codigo fuente y solucion de bugs importantes, utilizando su herramienta de debugger.
* Tiled: Para la elaboracion de los mapas.
* Plant UML: Para la creacion de los diagramas que figuran en los informes.
* Github: Para llevar a cabo la organizacion del trabajo y control de versiones.
* Trello: Para organizar tareas, notificar de bugs y llevar una lista organizada de tareas a cumplir.
* Discord: Para comunicacion entre los integrantes del grupo.

Además hay que mencionar la utilización de internet para buscar documentación de las bibliotecas utilizadas, tanto nativas como externas.

### Conclusiones

Dentro de las conclusiones del proyecto podemos mencionar:

* Haber aprendido a organizar y llevar a cabo un trabajo de complejidad media, implicando la correcta comunicación entre los integrantes, división de tareas y cumplimiento de metas.
* Haber puesto en practica la programación orientada a eventos.
* Haber puesto en practica la utilización de herramientas de GUI, tales como SDL.
* Revalorizar los consejos obtenidos a lo largo de la carrera en cuanto a buenas practicas de desarrollo de software se refiere.
* Haber aprendido a reconocer los momentos en los cuales era necesario realizar una refactorización del modelo.
