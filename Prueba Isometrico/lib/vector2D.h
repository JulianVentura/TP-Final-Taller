#ifndef VECTOR2D_H
#define VECTOR2D_H

class vector2D {
	public:

		static const vector2D VECTOR_NULO;

		float x;
		float y;

		// ASIGNACION //

		void operator = (vector2D vector);

		// OPERACIONES ELEMENTALES //

		vector2D();
		
		vector2D(float x,float y);

		vector2D operator  * (float escalar);

		void     operator *= (float escalar);

		vector2D operator  / (float escalar);

		void     operator /= (float escalar);

		vector2D operator  + (vector2D vector);

		void     operator += (vector2D vector);

		vector2D operator  - (vector2D vector);

		void     operator -= (vector2D vector);


		// ESPACIO METRICO //

		float modulo();

		void normalizar();

		void truncar(float valor_max);

		float distancia_Pitagoras(vector2D vector);

		vector2D obtener_vector_ortogonal();


		// COMPARACION //

		bool operator == (vector2D vector);

		bool operator != (vector2D vector);
};

#endif /*VECTOR2D_H */

