/*Hoja de Trabajo # 4 – (Ejercicio en Clase)
En la región de la sierra de los Cuchumatanes la compañía Xterminio s.a. , tiene las siguientes tarifas:

________________________________________________
|tipo 	|servicio			|costo por ectaria.	|
|_______|___________________|___________________|
|1		|Mala hierba		|	10				|
|2		|Langostas			|	20				|
|3		|Gusanos			|	30				|	
|4		|Todo lo anterior	|	40				|
|_______|___________________|___________________|

Además del área a fumigar es mayor a 500.00 hectáreas se tiene un descuento del 5%. Adicionalmente,
si el total a pagar por el servicio es mayor a Q1500.00 se tiene un descuento adicional del 10% sobre el
excedente.
La compañía necesita las estadísticas de los servicios que ha ofrecido a un grupo de agricultores durante
un periodo de tiempo. Por cada servicio debe ingresar los datos siguientes: Tipo de Fumigación (1 a 4) y
el número de hectáreas, toda esta información deberá almacenarse en una base de datos (archivo plano).
Se le pide que realice un programa en C++ que solicite el ingreso de la información de cada servicio
realizado a un grupo de agricultores. El programa deberá de leer los datos del archivo que tiene la
información antes almacenada y mostrar la cantidad de servicios de cada tipo de fumigación, determinar
el tipo servicio con mayor demanda y el monto total pagado por los clientes.
*/

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
using namespace std;

struct tipo_fumigacion{
	int tipo;
	string descripcion;
	float costo;
};

struct regar{
	int tipo;
	float tamanio;
	float total;
};

struct contar{
	int tipo;
	int cs;
}cuenta[4];

vector<tipo_fumigacion> tfumigacion;
void menu();
void grabar();
void leer();
void opciones();
int main(){
	menu();
	opciones();
	return 0;
}
void inicio(){
	tfumigacion.push_back({1, "mala hierva ", 10.00});
	tfumigacion.push_back({2, "langostas ", 20.00});
	tfumigacion.push_back({3, "gusanos ", 30.00});
	tfumigacion.push_back({4, "todo lo anterior ", 50.00});
	
	cuenta[0]={1,0};
	cuenta[1]={2,0};
	cuenta[2]={3,0};
	cuenta[3]={4,0};
}

void opciones(){
	cout << "    -------- Xterminaciones, S. A. -------- " << endl;
	cout << "=================================================================="<< endl;
	cout << "	--Tipo--" << "\t \t" << "--Servicio--" << "\t \t" << "--Costo x Hectaria--" << endl;
	cout << "=================================================================="<< endl;
	cout << "	1" <<"\t \t \t"<<"Mala Hierba" << "\t \t \t" << "10.00" << endl;
	cout << "	2" << "\t \t \t" << "Langostas" << "\t \t \t" << "20.00" << endl;
	cout << "	3" << "\t \t \t" << "Gusanos" << "\t \t \t \t" << "30.00" << endl;
	cout << "	4" << "\t \t \t" << "Todo lo anterior" << "\t \t" << "40.00" << endl;
	cout << "=================================================================="<< endl;
}

float calcular(int tipo, float tamanio){
  float cal1, total, precio;
  
  if (tipo==1) {
    precio=tfumigacion[0].costo;
  } else if (tipo==2){
    precio=tfumigacion[1].costo;
  } else if (tipo==3) {
    precio=tfumigacion[2].costo;
  } else if (tipo==4) {
    precio=tfumigacion[3].costo;
  } 
  
  precio=tamanio*precio;

  if (tamanio>500){
    precio=precio-(precio*0.05);
  }

  if (precio>1500) {
    cal1=precio-1500;
    cal1=cal1-(cal1*0.10);
    total=1500+cal1;
  }
  
  else {
    total=precio;
  }
  
  return total;
}

void grabar(){
  opciones(); // Mostramos las opciones de fumigacion

  // declaramos la estructura reg -> registro  la variable x
  regar x;

  cout << "Ingrese el tipo de servicio:" << endl;
  cin >> x.tipo;
  cout << "Ingrese el tamaño a fumigar: " << endl;
  cin >> x.tamanio;
  // llamamos la funcion y le asignamos el resultado
  // de la funcion
  x.total=calcular(x.tipo, x.tamanio);
  // grabamos en el archivo
  ofstream archivo("registro.txt", ios::app);
  archivo << x.tipo << "\t" << x.tamanio <<"\t"<< x.total<<endl;
  // Cerrar el archivo
  archivo.close();  

}

void leer(){
  regar x; // declaramos la estructura reg -> registro  la variable x

  float sumatotal=0; // esta variable sumara el total de los servicios brindados
  
  // generamos el objeto de la clase ofstream, que es archivo
  ifstream archivo;

  // abrimos el archivo.
  archivo.open("registro.txt", ios::in);

  // aca leemos el archivo y lo pasamos a x con estructura de reg.
  while(archivo >> x.tipo >> x.tamanio >> x.total){

    // Al obtener el tipo de servicio según la linea del archivo
    // sumamos al arreglo a cuenta el servicio registrado.
    cuenta[x.tipo-1].cs=cuenta[x.tipo-1].cs+1;

    // sumamos x.total según registro de linea del archivo.
    sumatotal=sumatotal+x.total; // es el gran total


  }

  // Cerramos el archivo.
  archivo.close();

  for (int i=0; i<4; i++){
    cout << tfumigacion[i].descripcion << ": " << cuenta[i].cs << endl;
  }

  cout << "El total vendido es de: " << sumatotal << endl;

}

void menu(){
	int contador;
	bool fin=false;
	char tecla;
	string empty;
	do{
		system ("CLS");
		cout<<"menu."<<endl;
		cout<<"___________________________________________________________________________________"<<endl;
		cout<<"1). ~GRABAR."<<endl;
		cout<<"2). ~LEER."<<endl;
		cout<<"3). ~SALIR."<<endl;
		cout<<"___________________________________________________________________________________"<<endl;
		cout << "Elije una opcion: ";
		
		cin>>tecla;
		switch(tecla){
			case '1':
			system ("CLS");
			grabar();
			contador=contador+1;
			break;
			
			case '2':
			system ("CLS");
			leer();
			break;
			
			case '3':
			fin=true;
			break;
			
			default:
			cout<<"Opcion no valida.";
			getchar();
			getline(cin,empty);
			break;
		}
	}while (fin!=true);
}

