#include <iostream>
#define MAX 100000
using namespace std;

// Esta funcion se encarga de convertir los Chars en Numeros (de 1 a 9).
// En caso de que tenga otro valor, retorna un -1
int ASCII(char L)
{
    if (L>47 && L<58)
        return (L-48);
    else
        return (-1);
}

float potencia(float base, float exponente) //calcula potencias
{
    float auxiliar = 1;
    while(exponente > 0)
    {
        auxiliar  = base*auxiliar;
        exponente = exponente - 1;
    }
    return auxiliar;
}

float evaluar(int funcion[MAX],float valor, int n) //no errores
{
    int indice = 0;
    float sumatoria = 0;
    for(indice = 0; indice < n; indice++)
    {
        if((indice%2) == 0)
        {
           sumatoria= sumatoria + (potencia(valor,funcion[indice+1]))*funcion[indice];
        }
    }
    return sumatoria;
}

float derivar(int funcion[MAX],float valor, int n) //evalua y calcula derivadas considerando el arreglo a analizar
{
    int indice = 0;
    float sumatoria = 0, multiplicando = 0, exponente = 0;
    for(indice = 0; indice < n; indice++)
    {
        if((indice%2) == 0)
        {
           multiplicando = funcion[indice]*funcion[indice + 1];
           exponente = funcion[indice + 1] - 1;
           sumatoria = sumatoria + (potencia(valor,exponente))*multiplicando;
        }
    }
    return sumatoria;
}

float Evaluacion_Newton(int funcion[MAX], int n) //Evalua el valor a analizar por el programa
{
    float indice = 0;
    while(evaluar(funcion, indice, n) <= 0)
    {
        indice = indice +1;
    }
    return indice;
}

float Ecuacion(float valor, int funcion[MAX], int n)//calcula la ecuación diseñada
{
    float resultado = 0;
    if(derivar(funcion, valor, n) == 0)
    {
        valor = valor + 0.01;
    }
    resultado = valor - (evaluar(funcion, valor, n))/(derivar(funcion, valor, n));
    return resultado;
}

float Desarrollo_Ejercicio(int funcion[MAX], int n) //Evalua el ejercicio aplicando las funciones anteriores
{
    float valor_inicial = 0, valor_prueba = 0;
    valor_inicial = Evaluacion_Newton(funcion, n);


    valor_prueba = Ecuacion(valor_inicial - 1,funcion,n);
    float margen_error = 0.005;//margen de error, del ejercicio
    valor_inicial = valor_inicial - 1;
    valor_inicial = valor_prueba;
    valor_prueba = Ecuacion(valor_inicial,funcion,n);
    while((valor_inicial - valor_prueba > margen_error)||(valor_inicial - valor_prueba < (-1*margen_error)))
    {
        valor_inicial = valor_prueba;
        valor_prueba = Ecuacion(valor_inicial,funcion,n);
    }
    return valor_prueba;
}

int main(int argc, char *argv[])
{
    // Creo arreglo para rellenar con los valores.
    int Arreglo[99];
    // NO SE HARA NINGUNA COMPROBACION, SE ASUME QUE EL USUARIO INGRESARA CORRECTAMENTE EL PARAMETRO
    // Se crean contadores, uno para la Ecuacion y otra para el Arreglo
    int iEc=0;
    int jArr=0;
    // Mientras los valores empiecen con una x, resta, suma o numero entre 1 y 9
    while (argv[1][iEc]=='x' || argv[1][iEc]=='X' || argv[1][iEc]=='-' || argv[1][iEc]=='+' || ASCII(argv[1][iEc])!=-1)
    {
        // ¿Es negativa la cte?
        int Neg=1;
        if (argv[1][iEc]=='-')
        {
            Neg=-1;
            iEc++;
        }
        // ¿Es positiva la cte?
        if (argv[1][iEc]=='+')
        {
            iEc++;
        }
        // Trabajo con la cte (o x respectivamente)
        if (argv[1][iEc]!='x' || argv[1][iEc]!='X')
            Arreglo[jArr]=ASCII(argv[1][iEc])*Neg;
        else
            Arreglo[jArr]=Neg;
        // En caso de que la cte tenga mas de 1 digito.
        while (ASCII(argv[1][iEc+1])>-1 && ASCII(argv[1][iEc+1])<10)
        {
            Arreglo[jArr]=Arreglo[jArr]*10+ASCII(argv[1][iEc+1]);
            iEc++;
        }
        // Salto valores tipicos, es decir, el "x**" y paso a almacenar la siguiente variable.
        iEc=iEc+4;
        jArr++;
        // ¿Es negativa la 2nda cte?
        Neg=1;
        if (argv[1][iEc]=='-')
        {
            Neg=-1;
            iEc++;
        }
        // Trabajo con la cte
        Arreglo[jArr]=ASCII(argv[1][iEc])*Neg;
        // En caso de que la cte tenga mas de 1 digito.
        while (ASCII(argv[1][iEc+1])>-1 && ASCII(argv[1][iEc+1])<10)
        {
            Arreglo[jArr]=Arreglo[jArr]*10+ASCII(argv[1][iEc+1]);
            iEc++;
        }
        // Leo lo siguiente y preparo el arreglo para los siguientes valores.
        iEc++;
        jArr++;
    }
    cout <<"La raiz encontrada es: "<<endl;
    cout << Desarrollo_Ejercicio(Arreglo,jArr)<<endl;
    return 0;
}
