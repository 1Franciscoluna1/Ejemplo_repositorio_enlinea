#include <stdio.h>
#include <windows.h>
#pragma warning(disable : 4996)
#pragma warning(disable : 6054)
#pragma warning(disable : 6328)
#pragma warning(disable : 4477)


struct Morros {

	char Alumno[50];
	int telefono;

	int estatus;

};

void mostrarlista();
void MeterMorro();

void cambiarStatusOK();
void cambiarStatus();
void buscador();
void modificarcontacto();

//void bucarMorro();

int main() {
	char opc;

	do
	{
		opc = menu();
		switch (opc)
		{
		case 'a':
			MeterMorro();
			break;
            case 'e':
			buscador();
			break;
		case 'f':
			mostrarlista();
			break;
		case 'g':
			cambiarStatusOK();
			break;
		case 'd':
			cambiarStatus();
			break;
		defaul;
		case 'f':
			modificarcontacto();
			break;
			break;
		}
	} while (opc != 'h');

	//system("pause");
}

char menu() {
	char op;
	int z;

	FILE* MENU = fopen("MENU.txt", "r");
	while ((z = fgetc(MENU)) != EOF) { printf("%c", z); }        //sirve para escribir una variable en la consola

	scanf_s(" %c", &op, sizeof(op)); //  soluciona problemas en visual 
	fclose(MENU);
	return op;
}

void MeterMorro() {
	Morros datos; // llamar la estrura en  funciones 
	system("cls");
	printf("¿Como se llama la persona que quieres añadir a la agenda?\n\n");
	scanf_s(" %[^\n]s", &datos.Alumno, sizeof(datos.Alumno));
	printf("¿Cual es el telefono \n");
	scanf_s(" %i", &datos.telefono);
	datos.estatus = 1; // bandera en verde  =1

	FILE* lista = fopen("Lista de contactos.alv", "ab");
	fwrite(&datos, sizeof(Morros), 1, lista);
	fclose(lista);
	system("pause");
}

void mostrarlista() {
	system("cls");
	printf("\n\n\t\tContactos guardados\n\n");
	Morros chamacos[20];
	FILE* lalista = fopen("Lista de contactos.alv", "rb");
	int tamaño;
	// printf(" \n nombre : %c \n, direccion: %c \n , edad :%i\n ,movil : %i \n, email : %c\n ",*dato[30].nombre,*dato[30].direccion,dato[30].edad,dato[30].movil,*dato[30].email);
	fseek(lalista, 0, SEEK_END); // e l numero consta la cantidad de datos que nos vamos a mover 
	tamaño = ftell(lalista); // dar tamaño de lista 
	tamaño = tamaño / sizeof(Morros); // dividir cantidad total de carcateres ente el tamaño del arreglo 
	rewind(lalista); // regresar al inicio del archivo 

	printf("%-30s %-30s\n", "Nombre", "Telefono"); //  imprime un espaciado  entre   la cadena y el tex

	for (int i = 0; i < tamaño; i++)
	{
		fread(&chamacos[i], 1, sizeof(Morros), lalista);
		if (chamacos[i].estatus == 1) {
			printf("%-30s", chamacos[i].Alumno);
			printf("%-30i", chamacos[i].telefono);
			printf("\n");
		}

	}
	system("pause");
	system("cls");
	fclose(lalista);
} 

void cambiarStatus() { // bloquear 
	int cuchao = 0;
	char  a[50];
	FILE* lalista = fopen("Lista de contactos.alv", "r+b");
	Morros status;

	printf("¿que alumno va a bloquear?");
	scanf_s(" %[^\n]s", a, sizeof(a));
	fread(&status, sizeof(Morros), 1, lalista);
	while (!feof(lalista)) {
		if (!strcmp(status.Alumno, a) && status.estatus == 1) {
			printf("%-30s%-30s\n", "Nombre", "Telefono");
			printf("%-30s", status.Alumno);
			printf("%-30i", status.telefono);
			int ontoi = ftell(lalista) - sizeof(status);
			fseek(lalista, ontoi, SEEK_SET); //

			status.estatus = 0;
			fwrite(&status, sizeof(Morros), 1, lalista);
			cuchao++;

			break;
		}
		fread(&status, sizeof(Morros), 1, lalista);
	}
	if (cuchao == 0) {
		printf("\n\nMorro no encontrado\n\n");
	}
	else
	{
		printf("\n\nContacto bloqueado\n\n");
	}

	system("pause");
	system("cls");
	fclose(lalista);
}

void cambiarStatusOK() {  // desbloquear
	int cuchao = 0;
	char  a[50];
	FILE* lalista = fopen("Lista de contactos.alv", "r+b");
	Morros status;

	printf("¿que alumno va a bloquear?");
	scanf_s(" %[^\n]s", a, sizeof(a));

	while (!feof(lalista)) {
		fread(&status, sizeof(Morros), 1, lalista);
		if (!strcmp(status.Alumno, a) && status.estatus == 0) {
			printf("%-30s%-30s\n", "Nombre", "Telefono");
			printf("%-30s", status.Alumno);
			printf("%-30i", status.telefono);
			status.estatus = 1;

			int ontoi = ftell(lalista) - sizeof(status);
			fseek(lalista, ontoi, SEEK_SET); //
			fwrite(&status, sizeof(Morros), 1, lalista);

			cuchao++;
			break;
			//123466789
		}
	}
	if (cuchao == 0) {
		printf("\n\nMorro no encontrado\n\n");
	}
	else
	{
		printf("\n\nContacto bloqueado\n\n");
	}

	system("pause");
	system("cls");
	fclose(lalista);
} void buscador() {

	int cuchao = 0;
	char  a[50];
	FILE* lalista = fopen("Lista de contactos.alv", "rb");
	Morros status;

	printf("¿que alumno va a BUSCAR?\n\n\n");
	scanf_s(" %[^\n]s", a, sizeof(a));

	while (!feof(lalista)) {
		fread(&status, sizeof(Morros), 1, lalista);
		if (!strcmp(status.Alumno, a) && status.estatus == 1) {
			printf("%-30s%-30s\n", "Nombre", "Telefono");
			printf("%-30s", status.Alumno);
			printf("%-30i", status.telefono);
			printf("\n\n\n");

			break; 
		}
	}
	printf("alumno no encontrado\n");

	fclose(lalista);
}void modificarcontacto() {
	system("cls");
	char NOMBRE[30];
	int posicion = 0;
	int re;
	FILE* MODIFICAR;
	MODIFICAR = fopen("Lista de contactos.alv", "rb+");
	Morros edicion;

	printf("\n¿cual es el nombre?  :\n");
	scanf_s(" %[^\n]s", &NOMBRE, sizeof(NOMBRE));

	fread(&edicion, sizeof(Morros), 1, MODIFICAR);
	while (!feof(MODIFICAR))
	{
		if (!strcmp(edicion.Alumno, NOMBRE) && edicion.estatus == 1) {
			printf("\tNombre  registro\n\t");
			printf("%s\t", edicion.Alumno);
			printf("%i\n", status.telefono;

			posicion = ftell(MODIFICAR) - sizeof(edicion);  // me indica la posicion actual del fichero
			fseek(MODIFICAR, posicion, SEEK_SET);//identificador del fichero, el desplazamiento, la posición de origen
			printf("\nQue dato desea modificar?");
			printf("\n\t 1 Nombre \n\t 2 registro");
			scanf_s(" %i", &re);

			if (re == 1)
			{
				printf("\n nuevo nombre :\t");
				scanf_s(" %[^\n]s", &edicion.Alumno, sizeof(edicion.Alumno));
				fwrite(&edicion, sizeof(Morros), 1, MODIFICAR);
			}
			if (re == 2)
			{
				printf("\nnuevo numero  :\t");
				scanf_s("%i", &edicion.registro, sizeof(edicion.registro));
				fwrite(&edicion, sizeof(Morros), 1, MODIFICAR);
			}
			break;
		}
		fread(&edicion, sizeof(Morros), 1, MODIFICAR);
	}

	fclose(MODIFICAR);
	system("pause");
	system("cls");
}




//simon!!!!!