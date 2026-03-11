#include <iostream>
using namespace std;
//herencia
class Persona{
	
	public:
		string nombre;
		
		void saludar(){
			
			cout<<"Hola, soy "<<nombre<<endl;
			
		}
};

class Estudiante : public Persona{
	
	public:
		string carrera;
		void mostraRDatos(){
			cout<<"Carrera:"<<carrera<<endl;
			
			
		}
};



int main(){
	
	Estudiante e1;
	e1.nombre = "Joselyn";
	e1.carrera = "Software";
	e1.saludar();
	e1.mostraRDatos();
	
	return 0;
	

}
