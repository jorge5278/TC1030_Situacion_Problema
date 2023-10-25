// Roberto Vázquez Betancourt A00837351
// Jorge Alberto Garcia Jardon A00837558

// En este programa se modelará un servicio de streaming en el que se
// desplegarán los datos de las series y peliculas junto con sus calificaciones

// Declaramos librerias
#include <iostream>
using namespace std;

// Declaramos las clases

// Declaramos clase padre video
class Video {

protected:
  int id;
  float duracion, calificacion;
  string nombre, categoria;

public:
  Video();
  Video(int, float, float, string);
  virtual void muestraDatos();
  float getCalificacion() { return calificacion; }
  int getId() { return id; }
  Video operator*(Video);
};

// Declaramos clase hija pelicula
class Pelicula : public Video {
private:
  string categoria;

public:
  Pelicula();
  Pelicula(int, float, float, string, string);
  void muestraDatos();
  void calificar(float valor) { calificacion = valor; }
  string Categoria() const { return categoria; }
};

// Declaramos clase hija serie
class Serie : public Video {
private:
  int capitulos;
  string categoria;

public:
  Serie();
  Serie(int, float, float, string, string, int);
  void muestraDatos();
  void calificar(float valor) { calificacion = valor; }
  string Categoria() const { return categoria; }
};
// Definimos métodos de video

Video::Video() {
  id = 00;
  duracion = 00;
  calificacion = 00;
  nombre = "Sin nombre";
}

Video::Video(int _id, float _duracion, float _calificacion, string _nombre) {
  id = _id;
  duracion = _duracion;
  calificacion = _calificacion;
  nombre = _nombre;
}

void Video::muestraDatos() {
  cout << endl << "Datos de la Pelicula: " << endl;
  cout << "Nombre: " << nombre << endl
       << "ID: " << id << endl
       << "Duracion: " << duracion << endl
       << "Calificacion: " << calificacion << endl;
}
Video Video::operator*(Video otroVideo) {
  Video resultado;
  resultado.calificacion = this->calificacion * otroVideo.calificacion;

  return resultado;
}
// Definimos métodos de pelicula
Pelicula::Pelicula() : Video() { categoria = "No encontrada"; }
Pelicula::Pelicula(int _id, float _duracion, float _calificacion,
                   string _nombre, string _categoria)
    : Video(_id, _duracion, _calificacion, _nombre) {
  categoria = _categoria;
}

void Pelicula::muestraDatos() {
  cout << endl << "Datos de la Pelicula: " << endl;
  cout << "Nombre: " << nombre << endl
       << "ID: " << id << endl
       << "Duracion: " << duracion << endl
       << "Calificacion: " << getCalificacion() << endl
       << "Categoría: " << categoria << endl;
}
// Definimos métodos de serie
Serie::Serie() : Video() { categoria = "No tiene categoria", capitulos = 0; }

Serie::Serie(int _id, float _duracion, float _calificacion, string _nombre,
             string _categoria, int _capitulos)
    : Video(_id, _duracion, _calificacion, _nombre) {
  categoria = _categoria;
  capitulos = _capitulos;
}

void Serie::muestraDatos() {
  cout << endl << "Datos de la serie: " << endl;
  cout << "Nombre: " << nombre << endl
       << "ID: " << id << endl
       << "Duracion: " << duracion << endl
       << "Calificacion: " << calificacion << endl
       << "Categoría: " << categoria << endl
       << "Capitulos: " << capitulos << endl;
}
// Para la mayoria de las funciones se necesito el uso de arreglos y
// apuntadores, por lo que los estoy declarando, todos con un tamaño maximo de
// 100 porque no creo que sea necesario mas de eso
Pelicula *peliculas[100]; // Tamaño máximo de 100 peliculas

// Variable para realizar un seguimiento de peliculas almacenadas
int numPelicula = 0;

// Función para mostrar todas las peliculas guardados
void mostrarPeliculas() {
  if (numPelicula == 0) {
    cout << "No hay peliculas guardadas." << endl;
    return;
  }
  // El caso de mostrar peliculas es distinto pues necesitamos primero evaluar
  // la calificacion minima con la que se desea que se muestren las peliculas, y
  // en base a eso se muestran todas las peliculas con esa calificacion y mayor
  float calificacionMinima;
  cout << "Ingrese la calificación mínima: ";
  cin >> calificacionMinima;

  cout << "Peliculas con calificación igual o mayor a " << calificacionMinima
       << ":" << endl;
  for (int i = 0; i < numPelicula; i++) {
    // Evalua la condicion de calificacion minima agarrando cada valor de
    // calificacion en el arreglo de pelicula, lo compara con la calificacion
    // del usuario y si se cumple impre sus datos
    if (peliculas[i]->getCalificacion() >= calificacionMinima) {
      peliculas[i]->muestraDatos();
    }
  }
}

Serie *serie1[100]; // Tamaño máximo de 100 series

// Variable para realizar un seguimiento del número de series almacenados
int numSerie = 0;
// Función para mostrar todos las series guardadas
void mostrarEpisodiosSerie() {
  if (numSerie == 0) {
    cout << "No hay series guardadas." << endl;
    return;
  }

  cout << "Series guardadas:" << endl;
  for (int i = 0; i < numSerie; i++) {
    serie1[i]->muestraDatos();
  }
}
// Aqui se puede volver a calificar las peliculas y series
void calificarVideo() {
  int opcion;
  // Primero se pregunta al usuario si desea cambiar la calificacion de una
  // pelicula o serie
  cout << "Ingrese el tipo de video (1: Película, 2: Serie): ";
  cin >> opcion;
  // Declaro las variables donde guardare la seleccion del usuario
  int id;
  float calificacion;

  cout << "Ingrese el ID del video: ";
  cin >> id;

  cin.ignore(1000, '\n'); // limpio caractereses adicionales de bufer de entrada
                          // porque me esta dando problemas con el menu

  cout << "Ingrese la nueva calificación: ";
  cin >> calificacion;

  // Con el uso de un if, dependiendo de si es pelicula o serie, busco en todo
  // el arreglo de peliculas la id que el usuario me proporciono, cuando la
  // encuntro uso la funcion de calificar y le doy la calificacion que me dio el
  // usuario y por ultimo declaro mi booleano como verdadero para imprimir el
  // mensaje de que se actualizo la calificacion
  if (opcion == 1) {
    // Buscar la película por su ID
    bool encontrada = false;
    for (int i = 0; i < numPelicula; i++) {
      if (peliculas[i]->getId() == id) {
        peliculas[i]->calificar(calificacion);
        encontrada = true;
        break;
      }
    }

    if (encontrada) {
      cout << "La calificación se ha actualizado correctamente." << endl;
    } else {
      cout << "No se encontró ninguna película con el ID proporcionado."
           << endl;
    }
  } else if (opcion == 2) {
    // Buscar la serie por su ID
    bool encontrada = false;
    for (int i = 0; i < numSerie; i++) {
      if (serie1[i]->getId() == id) {
        serie1[i]->calificar(calificacion);
        encontrada = true;
        break;
      }
    }

    if (encontrada) {
      cout << "La calificación se ha actualizado correctamente." << endl;
    } else {
      cout << "No se encontró ninguna serie con el ID proporcionado." << endl;
    }
  } else {
    cout << "Opción inválida. Intente nuevamente." << endl;
  }
}
// Aqui se muestran los videos por calificacion y las series por genero
void mostrarVideos() {
  string filtro;
  float calificacionMinima;
  // Se pide al usuario los datos de calificacion minima y genero
  cout << "Ingrese el género o dejelo en blanco para mostrar todos: ";
  getline(cin, filtro);

  cout << "Ingrese la calificación mínima: ";
  cin >> calificacionMinima;

  cin.ignore(1000, '\n');
  // Se imprimen las peliculas que cumplan con los requisitos y tambien se da la
  // opcion de dejar el genero en blanco para mostrarlo todo, basicamente se
  // leen todos los datos del arreglo de peliculas y serie, despues se verifica
  // si se dejo en filtro en blanco y se pasa a comparar la calificacion o si si
  // hay categoria se busca los arreglos que cumplan con esa categoria para
  // despues imprimirlo
  cout << "Peliculas y series con calificación igual o mayor a "
       << calificacionMinima << " y género " << filtro << ":" << endl;

  // Mostrar películas que cumplan con los criterios de género y calificación
  for (int i = 0; i < numPelicula; i++) {
    if ((filtro == "" || peliculas[i]->Categoria() == filtro) &&
        peliculas[i]->getCalificacion() >= calificacionMinima) {
      peliculas[i]->muestraDatos();
    }
  }

  // Mostrar series que cumplan con los criterios de género y calificación
  for (int i = 0; i < numSerie; i++) {
    if ((filtro == "" || serie1[i]->Categoria() == filtro) &&
        serie1[i]->getCalificacion() >= calificacionMinima) {
      serie1[i]->muestraDatos();
    }
  }
}

void cargarArchivoDatos() {
  // Aqui se cargan los archivos, se pregunta el tipo de archivo de video, sus
  // datos y dependiendo de la opcion se guardan en el apuntador, guardo esos
  // datos en el arreglo y sumo 1 al contador de cantidad de pelicula, serie o
  // video
  int opcion;
  cout << "Ingrese el tipo de video (1: Película, 2: Serie): ";
  cin >> opcion;

  int id;
  float duracion, calificacion;
  string nombre, categoria;

  cout << "Ingrese el ID: ";
  cin >> id;

  cout << "Ingrese la duración: ";
  cin >> duracion;

  cout << "Ingrese la calificación: ";
  cin >> calificacion;

  cin.ignore(1000, '\n'); // Sin esta linea no me deja ingresar el nombre pues
                          // se da un enter automatico por el cin.

  cout << "Ingrese el nombre: ";
  getline(cin, nombre);

  if (opcion == 1) {
    cout << "Ingrese la categoría: ";
    getline(cin, categoria);
    Pelicula *pelicula =
        new Pelicula(id, duracion, calificacion, nombre, categoria);
    peliculas[numPelicula] = pelicula;
    numPelicula++;
  } else if (opcion == 2) {
    cout << "Ingrese la categoría: ";
    getline(cin, categoria);
    int capitulos;
    cout << "Ingrese el número de capítulos: ";
    cin >> capitulos;

    Serie *serie =
        new Serie(id, duracion, calificacion, nombre, categoria, capitulos);
    serie1[numSerie] = serie;
    numSerie++;
  }
}

// Instanciamos los objetos y los manipulamos en el main
int main() {
  // Declaro mi variable de opcion
  int opcion = -1;
  // Un while donde repito que se imprima el menu mientras que el usuario
  // ingrese un numero distinto a 0, al colocar 0 se cierra y sale del menu
  while (opcion != 0) {
    cout << "===== MENÚ =====" << endl;
    cout << "1. Cargar archivo de datos" << endl;
    cout << "2. Mostrar videos" << endl;
    cout << "3. Mostrar episodios de una serie" << endl;
    cout << "4. Mostrar películas" << endl;
    cout << "5. Calificar un video" << endl;
    cout << "0. Salir" << endl;
    cout << "================" << endl;

    cout << "Ingrese una opción: ";
    cin >> opcion;

    // Valido la opcion del usuario para ver que sea valido y pasamos al switch
    // case
    while (cin.fail() || opcion < 0 || opcion > 5) {
      // Agregue esta parte de cin porque estaba teniendo varios problemas con
      // el menu que presionaba doble enter y encontre esta solucion en internet
      // donde ignora valores inesperados como un enter.
      cin.clear();
      cin.ignore(1000, '\n');
      cin >> opcion;
    }

    cin.ignore(1000, '\n');

    // Switch con nuestro menu de opciones donde se mandan a llamar nuestras
    // funciones
    switch (opcion) {
    case 1:
      cargarArchivoDatos();
      break;
    case 2:
      mostrarVideos();
      break;
    case 3:
      mostrarEpisodiosSerie();
      break;
    case 4:
      mostrarPeliculas();
      break;
    case 5:
      calificarVideo();
      break;
    case 0:
      cout << "Saliendo del programa..." << endl;
      break;
    default:
      cout << "Opción inválida. Intente nuevamente." << endl;
      break;
    }

    cout << endl;
  }

  return 0;
}
