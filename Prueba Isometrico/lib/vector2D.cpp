#include <cmath>
#include "vector2D.h"

using namespace std;

const vector2D vector2D::VECTOR_NULO(0,0);

vector2D::vector2D(){
	this -> x = 0;
	this -> y = 0; 
}

vector2D::vector2D(float x,float y){
	this -> x = x;
	this -> y = y; 
}


// ASIGNACION //

void vector2D::operator = (vector2D vector){
	x = vector.x;
	y = vector.y;
}

// OPERACIONES ELEMENTALES //

vector2D vector2D::operator * (float escalar){
	vector2D vector_resultado(x*escalar,y*escalar);
	return vector_resultado;
} 

void vector2D::operator *= (float escalar){
	x *= escalar;
	y *= escalar;
}


vector2D vector2D::operator / (float escalar){
	vector2D vector_resultado(x/escalar,y/escalar);
	return vector_resultado;
} 

void vector2D::operator /= (float escalar){
	x /= escalar;
	y /= escalar;
}

vector2D vector2D::operator + (vector2D vector){
	vector2D vector_resultado(vector.x + x,vector.y + y);
	return vector_resultado;
}

void vector2D::operator += (vector2D vector){
	this -> x += vector.x;
	this -> y += vector.y;
}

vector2D vector2D::operator - (vector2D vector){
	return *this + (vector*(-1));
}

void vector2D::operator -= (vector2D vector){
	this -> x -= vector.x;
	this -> y -= vector.y;
}

// ESPACIO METRICO //

float vector2D::modulo(){
	return sqrt(x*x + y*y);
}

void vector2D::normalizar(){

	float modulo = this -> modulo();
	if(modulo == 0) return;
	this -> x /= modulo;
	this -> y /= modulo;
}

void vector2D::truncar(float valor_max){

	float modulo = this -> modulo();
	if(modulo <= valor_max) return;

	this -> normalizar();
	*this *= valor_max;
}

float vector2D::distancia_Pitagoras(vector2D vector){
	return (*this - vector).modulo();
}

vector2D vector2D::obtener_vector_ortogonal(){
	vector2D vector(y,-x);
	return vector;
}


// COMPARACION //

bool vector2D::operator == (vector2D vector){
	return (x == vector.x && y == vector.y);
}

bool vector2D::operator != (vector2D vector){
	return (x != vector.x || y != vector.y);
}