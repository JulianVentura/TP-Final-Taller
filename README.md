# TP-Final-Taller

# Requisitos

- Mapa que permita detectar colisiones jugador-jugador, jugador-fantasma, jugador-npc, jugador-edificacion.
- El jugador podra jugar con distintas razas, al morir se transforma en un fantasma.
- Sistema de vida: Vida maxima, regeneracion de vida, al llegar a 0 vida se transforma en fantasma.
- Sistema de mana: Mana maximo, regeneracion de mana por meditar o por el paso del tiempo.
- Sistema monetario: El oro sirve para comerciar en el juego, se lo obtiene matando npcs u otros jugadores.
- Inventario: 
    * Podra almacenar N objetos, algunos de los cuales pueden ser equipados.
    * Se podran recolectar objetos del suelo utilizando `/tomar`, que seran almacenados en el inventario.
    * Se podran tirar al suelo objetos almacenados en el inventario seleccionandolos y escribiendo `/tirar`.
- Objetos equipables:
    * Se podran equipar varios objetos equipables al mismo tiempo, siempre que sean de distinto tipo.
    * Los objetos equipables modifican algun parametro, por ej: espada aumenta danio de ataque.
    * Algunos objetos equipables al ser equipados son consumidos *consumibles*.
- Puntos de experiencia:
    * Se debera llegar a un limite de experiencia para subir un nivel.
    * Se obtiene experiencia por cada ataque realizado.
    * Se obtiene un plus de experiencia por matar a un npc o jugador.
    * Al morir se pierde experiencia NO ESTA ACLARADO EN EL ENUNCIADO, PREGUNTAR.
- Ataque:
    * Existe cierta probabilidad de realizar un ataque critico, que causa el doble de danio y no puede esquivarse.
    * Si el arma equipada es un arma a distancia se podran realizar ataques haciendo click sobre el objetivo.
    * Si el arma no es a distancia solo sera posible atacar si el objetivo esta al lado del jugador.
- Defensa:
    * Existe la probabilidad de que un ataque sea esquivado, causando danio cero.
    * La defensa del jugador disminuye el danio efectivo de un ataque no esquivado.

- Atributos: Todo personaje tendra atributos que modificaran las ecuaciones del juego.
    * Fuerza: Aumenta el danio de ataque.
    * Agilidad: Aumenta la evasion.
    * Inteligencia: Aumenta el mana maximo y su regeneracion.
  
- Razas y clases:
    * Cada raza iniciara con ciertos atributos unicos no mejorables.
    * Ciertas razas tendran capacidades unicas, o incapacidades (war no puede tener mana).
- Muerte:
    * Al morir todos los objetos del inventario caen al piso.
    * Al morir se puede perder oro y/o experiencia.
    * Al morir el jugador se transforma en fantasma.
    * Un fantasma no puede interaccionar con nada (puede colisionar?)
    * Un fantasma puede resucitar con un sanador.
    * Un fantasma puede resucitar utilizando el comando `/resucitar`, que lo teletransportara con el sanador mas cercano y se le cobrara con una penalidad de tiempo.
- Fair play:
    * Un jugador nivel 12 o menor no puede atacar ni ser atacado por otros jugadores.
    * Un jugador no podra atacar ni ser atacado por otro jugador si la diferencia de nivel es superior a 10.
- Ciudades y pueblos:
    * En el juego habra distintas ciudades, cada una de ellas tendra un Sacerdote, un Banquero y un Comerciante.
    * El Sacerdote puede resucitar a un personaje, curarlo y venderle hechizos y pociones.
    * El comerciante puede comprar y vender casi todo.
    * El banquero permite depositar y retirar elementos, que se colocaran en un almacen. Los depositos pueden ser accedidos desde cualquier banquero del juego.
    * Las ciudades son zonas seguras, los NPCs no pueden entrar y los jugadores no pueden atacarse.
- Items: No vale la pena, esta bien resumido en el enunciado
- Criaturas:
    * Cada cierto tiempo un grupo de criaturas sera spawneado hasta que la poblacion de estas llegue a un limite.
    * Las criaturas se acercaran y atacaran al jugador mas cercando cuando este entre en un radio de cobertura.
    * Todas las criaturas tienen un ataque cuerpo a cuerpo.
    * Las criaturas deberan spawnear segun el mapa (NO ESTA EN EL ENUNCIADO, PERO LO DIJO MARTIN).
    * Con la muerte de cada criatura existe la probabilidad de que dropee algun objeto u oro.
    * Las criaturas que existen son: Goblin, Esqueleto, Zombie y Araña.
- Interfaz de usuario:
    * El juego muestra al personaje desde una vista de aguila con el personaje en el centro de la pantalla.
    * El jugador puede moverse usando el teclado y puede atacar haciendo click sobre otro jugador o NPC.
    * Se deben mostrar el inventario, que objeto esta equipado, cantidad de vida, mana, oro, experiencia y nivel.
- Mini-chat:
    * Se deberan mostrar los mensajes importantes, como el daño provocado, daño recibido, ataques evadidos por el jugador o su contricante y mensajes enviados por otros jugadores hacia el.
    * Debera permitir escribir una serie de comandos, entre ellos permitir enviar un mensaje a un jugador.
- Vestimenta:
    * La vestimenta debera mostrarse visualmente segun la pieza que se equipe, contando armas.
    * Si alguna pieza no esta equipada se debera mostrar una vestimenta comun para esa zona.
- Persistencia:
    * Debera realizarse periodicamente.
    * No se puede cargar todo el archivo en memoria
    * Se recomienda utilizar dos archivos.
    * Los archivos seran binarios
    * No se requiere borrado de usuarios.
    * No se pueden implementar algoritmos de persistencia propios, deberan utilizarse bibliotecas externas.
- Configuracion:
    * Cada ecuacion debe estar implementada en su propio metodo o funcion.
    * Todas las ecuaciones deben pertenecer a una misma clase o modulo.
    * Todos los valores numericos deberan ser cargados desde un archivo de configuracion de texto.
- Sonidos y musica:
    * Se debera reproducir una musica de fondo
    * Se deberan reproducir sonidos ante explosiones o ataques.


# Responsabilidades

## Cliente

- Interfaz grafica:
    * Pantalla de login, permitiendole al usuario definir el servidor a conectarse.
    * Mostrar inventario, barra de estado, mini-chat, mapa, NPCs, jugadores y al personaje en el centro.
- Controles:
    * Tomar los inputs de teclado y mouse, codificarlos y enviarlos al servidor mediante protocolo.
- Comandos:
    * Tomar los comandos del mini-chat, codificarlos y enviarlos al servidor mediante protocolo
- Mini-chat:
    * Mostrar los mensajes del mini-chat recibidos desde el servidor.
- Acciones:
    * Cada nueva accion debera ser reportada al servidor y esperar la respuesta antes de actualizar la interfaz:
        1. Movimiento del personaje.
        2. Ataque del personaje.
        3. Seleccion de elementos, jugadores o NPCs. (incluido elementos del inventario).


## Servidor


- Razas y Clases:
    * Debera llevar la logica de la interaccion de las distintas razas y clases.
- Items:
    * Debera llevar la logica de los efectos de los distintos items del juego.
- Creacion de pj y logueo:
    * Debera permitir la creacion de un nuevo personaje, respetando su raza y nombre.
    * Los personajes creados deberan ser almacenados en un fichero (persistir)
    * Debera llevar la logica de logueo de un personaje ya creado, buscando en los ficheros.
- Movimiento:
    * Debera llevar la logica del movimiento del jugador y NPCs, las cuales reportara al mapa.
- Ataque:
    * Permitir realizar un ataque jugador-jugador o jugador-NPC, ambos dentro del mismo mapa.
    * Llevar la logica de los distintos ataques posibles, a distancia y cuerpo a cuerpo.
    * Llevar la logica del daño del ataque y la defensa al mismo.
    * Llevar la logica de "fair-play".
    * Llevar la logica de zonas no ofensivas.
- Drop y experiencia:
    * Llevar la logica de el drop de items u oro.
    * Llevar la logica del drop de experiencia.
- Mapa:
    * Debera soportar la carga de todas las entidades dibujables, permitiendo cierta logica de seleccion y colision.
    * Debera actualizarse constantemente con el movimiento de NPCs y jugadores. Estos ultimos reportaran su movimiento por conexion TCP.
    * Un mapa puede o no ser una ciudad, debera permitir diferenciar.
- Ciudades:
    * Las ciudades seran zonas no ofensivas.
    * Debera manejarse la logica de los NPCs de las ciudades.




# Modelo del mapa

## Primer modelo

### Servidor

- Cada mapa consistira en una matriz de N*M donde cada posicion sera un puntero a un objeto `Posicionable`. Las posiciones vacias son representadas por `0` y las invalidas con un `-1`.
- Cada objeto `Posicionable` almacenara su posicion en coordenadas.
- El servidor cargara una matriz en memoria por cada mapa del juego al mismo tiempo.
- Los Clientes se encargaran de reportar al servidor la nueva posicion que desean adquirir, el servidor se encargara de chequear que esa posicion sea valida y que no haya colision con NPCs u otros jugadores.
- Ante un movimiento valido el servidor mueve el puntero al objeto `Posicionable` a su nueva posicion y responde al Cliente con las coordenadas correspondientes.
- Ante un cambio de mapa el servidor le indicara al Cliente la nueva posicion en coordenadas junto al id del archivo a cargar.

### Cliente

- El cliente cargara en memoria unicamente el mapa sobre el cual se encuentra el personaje.
- El mapa consistira de:
    1. Una imagen preprocesada que sera mostrada estaticamente en el fondo del canvas.
    2. Un Quad-tree que permitira hacer chequeo de colisiones estaticas de forma mas eficiente.
    3. Un hash que guardara la posicion de los objetos dinamicos utilizando sus `id` como clave.
- El hash almacenara en cada posicion un objeto que contendra la informacion necesaria para dibujar a ese objeto por pantalla. El `id` podra ser una concatenacion del tipo de clase y numero de instancia o nombre de jugador. (Hay que prohibir ciertos nombres de jugador que nos pueden romper el parseo). 
- El cliente tomara el input del usuario, realizara por si mismo un chequeo de colisiones con las barreras estaticas del juego (borde del mapa, un arbol, una casa, etc) y solo enviara una peticion al servidor si no hay colision.
- El serivdor respondera con la nueva posicion de todos los objetos dinamicos constantemente, por lo tanto es importante ser eficientes al actualizar el hash.
- La seleccion de un objeto del mapa con el mouse implicara buscar el `id` de dicho objeto dentro del hash para poder enviar una peticion al servidor. Esta busqueda debera realizarse linealmente ya que el hash tiene acceso directo por `id` y no por `posicion`. (pensar optimizacion).
