#include <iostream>
using namespace std;

#include "Examen.h"
#include "OrdenProduccion.h"
#include "ArchivoOrdenProduccion.h"

void Examen::EjemploDeListado(){
   ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
   OrdenProduccion registro;

   int i, cantidadRegistros = archivo.CantidadRegistros();
   for(i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      cout << registro.toCSV() << endl;
   }
}

void Examen::Punto1(){
   ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
   OrdenProduccion registro;

   // Matriz para marcar qué tipos de piezas produjo cada máquina
   // Filas: máquinas (1-15), Columnas: tipos de pieza (1-40)
   bool piezasPorMaquina[16][41] = {}; // Inicializar en false

   int cantidadRegistros = archivo.CantidadRegistros();

   // Recorrer todas las órdenes de producción
   for(int i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      int maquina = registro.getIDMaquina();
      int tipoPieza = registro.getIDTipoPieza();

      // Marcar que esta máquina produjo este tipo de pieza
      piezasPorMaquina[maquina][tipoPieza] = true;
   }

   // Contar cuántos tipos de piezas distintas produjo cada máquina
   cout << "Maquinas que produjeron mas de 35 tipos de piezas distintas:" << endl;

   for(int maquina = 1; maquina <= 15; maquina++){
      int tiposDistintos = 0;

      // Contar tipos de piezas distintas para esta máquina
      for(int tipoPieza = 1; tipoPieza <= 40; tipoPieza++){
         if(piezasPorMaquina[maquina][tipoPieza]){
            tiposDistintos++;
         }
      }

      // Si produjo más de 35 tipos distintos, mostrar el número de máquina
      if(tiposDistintos > 35){
         cout << maquina << endl;
      }
   }
}

void Examen::Punto2(){
   ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
   OrdenProduccion registro;

   // Arrays para acumular costos y contar producciones por mes
   float costosPorMes[13] = {}; // Índices 1-12 para los meses
   int produccionesPorMes[13] = {}; // Contar producciones por mes

   int cantidadRegistros = archivo.CantidadRegistros();

   // Recorrer todas las órdenes de producción
   for(int i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      Fecha fecha = registro.getFecha();

      // Filtrar solo órdenes del año 2025
      if(fecha.getAnio() == 2025){
         int mes = fecha.getMes();
         costosPorMes[mes] += registro.getCosto();
         produccionesPorMes[mes]++;
      }
   }

   // Encontrar el mes con menor costo que tenga al menos una producción
   int mesConMenorCosto = -1;
   float menorCosto = -1;

   for(int mes = 1; mes <= 12; mes++){
      // Solo considerar meses con al menos una producción
      if(produccionesPorMes[mes] > 0){
         if(menorCosto == -1 || costosPorMes[mes] < menorCosto){
            menorCosto = costosPorMes[mes];
            mesConMenorCosto = mes;
         }
      }
   }

   cout << "Mes de 2025 con menor costo de produccion: " << mesConMenorCosto << endl;
}

void Examen::Punto3(){
   ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
   OrdenProduccion registro;

   int cantidadRegistros = archivo.CantidadRegistros();

   float maxMateriaPrimaPorPieza = -1;
   int ordenConMaxMateriaPrima = -1;

   // Recorrer todas las órdenes de producción
   for(int i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);

      int cantidad = registro.getCantidad();
      float materiaPrima = registro.getCantidadMateriaPrima();

      // Calcular materia prima por pieza
      if(cantidad > 0){ // Evitar división por cero
         float materiaPrimaPorPieza = materiaPrima / cantidad;

         // Comparar si es la mayor
         if(maxMateriaPrimaPorPieza == -1 || materiaPrimaPorPieza > maxMateriaPrimaPorPieza){
            maxMateriaPrimaPorPieza = materiaPrimaPorPieza;
            ordenConMaxMateriaPrima = registro.getIDProduccion();
         }
      }
   }

   cout << "Numero de orden que uso mas materia prima por pieza: " << ordenConMaxMateriaPrima << endl;
}
