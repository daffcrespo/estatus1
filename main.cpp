/*
DosSiete
Pr�ctica #3: Variables Globales y Variables Locales
TiempoTraduccion=01:20
*/
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include<fstream>

#ifdef _WIN32
#define CLEAR "cls"
#elif defined(unix)||defined(__unix__)||defined(__unix)||defined(__APPLE__)||defined(__MACH__)
#define CLEAR "clear"
#else
#error "SO no soportado para limpiar pantalla"
#endif
//Declaraci�n y definici�n de constantes simb�licas
#define PORCENTAJE_IVA 16
#define RETENCION_ISR 10
#define RETENCION_IVA 10
#define GANANCIA_BRUTA 11
#define GASTO_IVA 16
#define C_100 100
#define MAX_MONTOS 3
#define MAX_ISR 3
#define TOTAL_MESES 12
#define CENTAVOS 2
#define TXT_INGRESOS "Ingresos.txt"
#define TXT_GASTOS "Gastos.txt"
enum{ESTABLECER_MES=1,CAPTURA_INGRESO,CAPTURA_GASTO,MOSTRAR_LISTA_INGRESOS,
    MOSTRAR_LISTA_GASTOS,CALCULO_IMPUESTOS,GUARDAR_ARCHIVO, SALIR}opcionesMenu;

using namespace std;

//Variables globales de uso interno del programa
string mes[TOTAL_MESES];
//Declaraci�n de variables para entrada de datos
int seleccionMes;
float ingreso[TOTAL_MESES],gasto[TOTAL_MESES];

void inicializarVariables();
int menuPrincipal();
void capturarMes();
void capturarIngresos();
void capturarGastos();
void mostrarIngresos();
void mostrarGastos();
void calcularImpuestos();
float calculoPorcentajesISR(int gananciaBruta);
void imprimirCalculoDeImpuestos(float ivaTotal, float subtotal, float retIsr, float retIva,
        float total, float gananciaBruta, float isr, float gananciaNeta, float isrPagar,
        float gastoIva, float ivaPagar, float ingresoTotal, float gastoTotal);
void guardarArchivo();
void pausa();

int main()
{
    setlocale(LC_CTYPE, "Spanish");
    bool continuarPrograma;
    continuarPrograma=true;
    cout<<fixed<<setprecision(CENTAVOS);
    inicializarVariables();
    do{
        switch (menuPrincipal()){
        case ESTABLECER_MES:            capturarMes();          break;
        case CAPTURA_INGRESO:           capturarIngresos();     break;
        case CAPTURA_GASTO:             capturarGastos();       break;
        case MOSTRAR_LISTA_INGRESOS:    mostrarIngresos();      break;
        case MOSTRAR_LISTA_GASTOS:      mostrarGastos();        break;
        case CALCULO_IMPUESTOS:         calcularImpuestos();    break;
        //case GUARDAR_ARCHIVO:           guardarArchivo();       break;
        case SALIR:                     continuarPrograma=false;    break;
        default: cout<<"Opci�n no valida.";
        }
        if(continuarPrograma){
            pausa();
        }
    }while(continuarPrograma);
    return 0;
}
void calcularImpuestos(){
    //Declaraci�n de variables
    float ivaTotal, subtotal, retIsr, retIva, total, gananciaBruta, isr, gananciaNeta, isrPagar,
        gastoIva, ivaPagar, ingresoTotal, gastoTotal;
    int m;
    system(CLEAR);
    ingresoTotal=gastoTotal=0;
    //C�lculo de impuestos
    for(m=0; m<TOTAL_MESES; m++){
        ingresoTotal+=ingreso[m];
        gastoTotal+=gasto[m];
    }
    ivaTotal=ingresoTotal*PORCENTAJE_IVA/C_100;
    subtotal=ingresoTotal+ivaTotal;
    retIsr=ingresoTotal*RETENCION_ISR/C_100;
    retIva=ingresoTotal*RETENCION_IVA/C_100;
    total=subtotal-retIsr-retIva;
    gananciaBruta=ingresoTotal-gastoTotal;
    isr=gananciaBruta*calculoPorcentajesISR(gananciaBruta)/C_100;
    gananciaNeta=gananciaBruta-isr;
    retIsr=ingresoTotal*RETENCION_ISR/C_100;
    isrPagar=isr-retIsr;
    gastoIva=gastoTotal*GASTO_IVA/C_100;
    ivaPagar=ivaTotal-gastoIva-retIva;
    //Salida de datos
    imprimirCalculoDeImpuestos(ivaTotal, subtotal, retIsr, retIva, total, gananciaBruta, isr,
    gananciaNeta, isrPagar, gastoIva, ivaPagar, ingresoTotal, gastoTotal);
}
float calculoPorcentajesISR(int gananciaBruta){
    float porcentaje,monto[MAX_MONTOS]={0,10000.01,20000.01},porcentajeIsr[MAX_ISR]={11,15,20};
    int i;
    porcentaje=0;
    for(i=MAX_MONTOS-1;i>=0;i--)
    {
        if(gananciaBruta>=monto[i])
        {
            porcentaje=porcentajeIsr[i];
            break;
        }
    }
    return porcentaje;
}
void imprimirCalculoDeImpuestos(float ivaTotal, float subtotal, float retIsr, float retIva,
float total, float gananciaBruta, float isr, float gananciaNeta, float isrPagar,
float gastoIva, float ivaPagar, float ingresoTotal, float gastoTotal){
    cout<<fixed<<setprecision(2)<<"C�lculo de impuestos anual"<<endl<<endl
    <<"***Tabla Recibo de Honorarios***"<<endl
    <<"Ingresos               "<<setw(10)<<ingresoTotal<<endl
    <<"(+) IVA                "<<setw(10)<<ivaTotal<<endl
    <<"(=) Subtotal           "<<setw(10)<<subtotal<<endl
    <<"(-) Retencion ISR      "<<setw(10)<<retIsr<<endl
    <<"(-) Retencion IVA      "<<setw(10)<<retIva<<endl
    <<"(=) Total              "<<setw(10)<<total<<endl
    <<"***Tabla Ganancias***"<<endl
    <<"Ingresos               "<<setw(10)<<ingresoTotal<<endl
    <<"(-) Gasto              "<<setw(10)<<gastoTotal<<endl
    <<"(=) Ganancia Bruta     "<<setw(10)<<gananciaBruta<<endl
    <<"(-) ISR "<<calculoPorcentajesISR(gananciaBruta)<<"%    "<<setw(15)<<isr<<endl
    <<"(=) Ganancia Neta      "<<setw(10)<<gananciaNeta<<endl
    <<"***Tabla ISR***"<<endl
    <<"ISR "<<calculoPorcentajesISR(gananciaBruta)<<"%        "<<setw(15)<<isr<<endl
    <<"(-) ISR retenido       "<<setw(10)<<retIsr<<endl
    <<"(=) ISR a pagar        "<<setw(10)<<isrPagar<<endl
    <<"***TABLA IVA***"<<endl
    <<"IVA                    "<<setw(10)<<ivaTotal<<endl
    <<"(-) Gasto IVA          "<<setw(10)<<gastoIva<<endl
    <<"(-) Retencion IVA      "<<setw(10)<<retIva<<endl
    <<"(=) IVA a Pagar        "<<setw(10)<<ivaPagar<<endl;
}
void guardarArchivo()
{
    ofstream salida;
    //cout<<"\nGuardar en archivo"<<endl<<endl
     //   <<"Archivo en construcci�n..."<<endl;
    //Guardar ingresos
    salida.open(TXT_INGRESOS,ios::out);
    if (salida.is_open()){
        for(int i=0;i<TOTAL_MESES;i++){
                salida<<ingreso[i]<<endl;
        }
        salida.close();
    }
    else{
        cout<<"No se pudieron guardar los cambios"<<endl;
    }
    //Guardar gastos
    salida.open(TXT_GASTOS,ios::out);
    if (salida.is_open()){
        for(int i=0;i<TOTAL_MESES;i++){
                salida<<gasto[i]<<endl;
        }
        salida.close();
    }
    else{
        cout<<"No se pudieron guardar los cambios"<<endl;
    }
}
void mostrarGastos(){
    system(CLEAR);
    int j;
    for(j=0; j<TOTAL_MESES; j++){
        cout<<setw(10)<<mes[j]<<" = "<<setw(10)<<gasto[j]<<endl;
    }
}
void mostrarIngresos(){
    system(CLEAR);
    int k;
    for(k=0; k<TOTAL_MESES; k++){
        cout<<setw(10)<<mes[k]<<" = "<<setw(10)<<ingreso[k]<<endl;
    }
}
void capturarGastos(){
    cout<<endl<<"Captura de gastos"<<endl;
    cout<<"Dame el gasto del mes de "<<mes[seleccionMes-1]<<":";
    cin>>gasto[seleccionMes-1];
    guardarArchivo();
}
void capturarIngresos(){
    cout<<endl<<"Captura de ingresos"<<endl;
    cout<<"Dame el ingreso del mes de "<<mes[seleccionMes-1]<<":";
    cin>>ingreso[seleccionMes-1];
    guardarArchivo();
}
void inicializarVariables(){
    ifstream entrada;
    mes[0]="Enero";
    mes[1]="Febrero";
    mes[2]="Marzo";
    mes[3]="Abril";
    mes[4]="Mayo";
    mes[5]="Junio";
    mes[6]="Julio";
    mes[7]="Agosto";
    mes[8]="Septiembre";
    mes[9]="Octubre";
    mes[10]="Noviembre";
    mes[11]="Diciembre";
    seleccionMes=1;
    //Cargar ingresos
    entrada.open(TXT_INGRESOS,ios::in);
    if(entrada.is_open()){
        for(int i=0;i<TOTAL_MESES;i++){
            entrada>>ingreso[i];
        }
        entrada.close();
    }
    else{
        for(int i=0;i<TOTAL_MESES;i++){
            ingreso[i]=0;
        }
    }
    //Cargar gastos
    entrada.open(TXT_GASTOS,ios::in);
    if(entrada.is_open()){
        for(int i=0;i<TOTAL_MESES;i++){
            entrada>>gasto[i];
        }
        entrada.close();
    }
    else{
        for(int i=0;i<TOTAL_MESES;i++){
            gasto[i]=0;
        }
    }
}
int menuPrincipal(){
    int opcionMenu;
    //Entrada de datos
    system(CLEAR);
    cout<<"CaLCULO DE IMPUESTOS ANUAL"<<endl<<endl;
    cout<<"Menu principal:"<<endl;
    cout<<"1. Establecer mes para captura (mes actual es "<<mes[seleccionMes-1]<<")"<<endl;
    cout<<"2. Captura de ingresos"<<endl;
    cout<<"3. Captura de gastos"<<endl;
    cout<<"4. Mostrar lista de ingresos anual"<<endl;
    cout<<"5. Mostrar lista de gastos anual"<<endl;
    cout<<"6. Calculo de impuestos anual"<<endl;
    //cout<<"7. Guardar en archivo"<<endl;
    cout<<"8. Salir"<<endl;
    cout<<endl<<"Opcion: "<<endl;
    cin>>opcionMenu;
    return opcionMenu;
}
void capturarMes(){
    int i;
    do{
        system(CLEAR);
        cout<<"Establecer mes para captura"<<endl;
        for(i=0; i<TOTAL_MESES; i++){
            cout<<i+1<<")"<<mes[i]<<endl;
        }
        cout<<"Elige el mes (1-12): ";
        cin>>seleccionMes;
        if(seleccionMes>0 && seleccionMes<=12){
            cout<<"Se ha establecido el mes de captura en "<<mes[seleccionMes-1];
        }
        else {
            cout<<"Mes no v�lido."<<endl;
            cout<<endl<<"Presione entrar para continuar...";
            cin.get();
            cin.get();
        }
    }while(seleccionMes<1 || seleccionMes>12);
}
void pausa(){
    cout<<endl<<"Presione entrar para continuar...";
    cin.get();
    cin.get();
}
