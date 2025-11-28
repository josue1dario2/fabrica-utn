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
   // Filas: máquinas 1-15 (índices 0-14), Columnas: tipos de pieza 1-40 (índices 0-39)
   bool piezasPorMaquina[15][40] = {}; // Inicializar en false

   int cantidadRegistros = archivo.CantidadRegistros();

   // Recorrer todas las órdenes de producción
   for(int i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      int maquina = registro.getIDMaquina();
      int tipoPieza = registro.getIDTipoPieza();

      // Marcar que esta máquina produjo este tipo de pieza
      piezasPorMaquina[maquina - 1][tipoPieza - 1] = true;
   }

   // Contar cuántos tipos de piezas distintas produjo cada máquina
   cout << endl;
   cout << "========================================" << endl;
   cout << "           PUNTO 1 - RESULTADOS         " << endl;
   cout << "========================================" << endl;
   cout << "Maquinas que produjeron MAS DE 35 tipos de piezas distintas:" << endl;
   cout << "----------------------------------------" << endl;

   int cantidadMaquinas = 0;
   for(int i = 0; i < 15; i++){
      int tiposDistintos = 0;

      // Contar tipos de piezas distintas para esta máquina
      for(int j = 0; j < 40; j++){
         if(piezasPorMaquina[i][j]){
            tiposDistintos++;
         }
      }

      // Si produjo más de 35 tipos distintos, mostrar el número de máquina
      if(tiposDistintos > 35){
         cout << "  >> Maquina #" << (i + 1) << " - Produjo " << tiposDistintos << " tipos diferentes" << endl;
         cantidadMaquinas++;
      }
   }

   if(cantidadMaquinas == 0){
      cout << "  No se encontraron maquinas con mas de 35 tipos de piezas." << endl;
   }
   cout << "========================================" << endl;
   cout << endl;
}

void Examen::Punto2(){
   ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
   OrdenProduccion registro;

   // Arrays para acumular costos y contar producciones por mes
   float costosPorMes[12] = {}; // Índices 0-11 para los meses 1-12
   int produccionesPorMes[12] = {}; // Contar producciones por mes

   int cantidadRegistros = archivo.CantidadRegistros();

   // Recorrer todas las órdenes de producción
   for(int i = 0; i < cantidadRegistros; i++){
      registro = archivo.Leer(i);
      Fecha fecha = registro.getFecha();

      // Filtrar solo órdenes del año 2025
      if(fecha.getAnio() == 2025){
         int mes = fecha.getMes();
         costosPorMes[mes - 1] += registro.getCosto();
         produccionesPorMes[mes - 1]++;
      }
   }

   // Encontrar el mes con menor costo que tenga al menos una producción
   int mesConMenorCosto = -1;
   float menorCosto = -1;

   for(int i = 0; i < 12; i++){
      // Solo considerar meses con al menos una producción
      if(produccionesPorMes[i] > 0){
         if(menorCosto == -1 || costosPorMes[i] < menorCosto){
            menorCosto = costosPorMes[i];
            mesConMenorCosto = i + 1; // Convertir índice a número de mes
         }
      }
   }

   cout << "========================================" << endl;
   cout << "           PUNTO 2 - RESULTADOS         " << endl;
   cout << "========================================" << endl;
   cout << "Mes de 2025 con MENOR costo de produccion:" << endl;
   cout << "----------------------------------------" << endl;

   if(mesConMenorCosto != -1){
      string nombreMes[12] = {"Enero", "Febrero", "Marzo", "Abril", "Mayo", "Junio",
                              "Julio", "Agosto", "Septiembre", "Octubre", "Noviembre", "Diciembre"};

      cout << "  >> Mes: " << nombreMes[mesConMenorCosto - 1] << " (mes #" << mesConMenorCosto << ")" << endl;
      cout << "  >> Costo total: $" << menorCosto << endl;
      cout << "  >> Cantidad de ordenes: " << produccionesPorMes[mesConMenorCosto - 1] << endl;
   } else {
      cout << "  No se encontraron producciones en 2025." << endl;
   }

   cout << "========================================" << endl;
   cout << endl;
}

void Examen::Punto3(){
   ArchivoOrdenProduccion archivo("ordenes_produccion.dat");
   OrdenProduccion registro;

   int cantidadRegistros = archivo.CantidadRegistros();

   float maxMateriaPrimaPorPieza = -1;
   int ordenConMaxMateriaPrima = -1;
   OrdenProduccion ordenMaxima;

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
            ordenMaxima = registro;
         }
      }
   }

   cout << "========================================" << endl;
   cout << "           PUNTO 3 - RESULTADOS         " << endl;
   cout << "========================================" << endl;
   cout << "Orden con MAYOR materia prima por pieza fabricada:" << endl;
   cout << "----------------------------------------" << endl;

   if(ordenConMaxMateriaPrima != -1){
      cout << "  >> Numero de orden: #" << ordenConMaxMateriaPrima << endl;
      cout << "  >> Maquina: #" << ordenMaxima.getIDMaquina() << endl;
      cout << "  >> Tipo de pieza: #" << ordenMaxima.getIDTipoPieza() << endl;
      cout << "  >> Cantidad fabricada: " << ordenMaxima.getCantidad() << " piezas" << endl;
      cout << "  >> Materia prima total: " << ordenMaxima.getCantidadMateriaPrima() << endl;
      cout << "  >> Materia prima por pieza: " << maxMateriaPrimaPorPieza << endl;
      cout << "  >> Fecha: " << ordenMaxima.getFecha().toString() << endl;
   } else {
      cout << "  No se encontraron ordenes de produccion." << endl;
   }

   cout << "========================================" << endl;
   cout << endl;
}
