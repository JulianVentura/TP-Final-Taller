#ifndef __COLA_BLOQUEANTE_H__
#define __COLA_BLOQUEANTE_H__

#include <exception>
#include <condition_variable>
#include <queue>
#include <mutex>

/*
*	Al cerrarse la cola bloqueante, es necesario liberar los procesos de retiro
*	en espera. Si al despertarse uno de los hilos no se puede retirar ningún
*	recurso, se rechaza la solicitud con la excepcion ColaVacia.
*/
struct ColaVacia : public std::exception {
   const char * what() const throw() {
      return "Cola vacia";
   }
};

template <class T> class ColaBloqueante{
private:
	bool cerrada;
	std::mutex m;
	std::queue<T> cola;
	std::condition_variable cv;

public:
	ColaBloqueante(const ColaBloqueante&)  = delete;
	ColaBloqueante(const ColaBloqueante&&) = delete;
	ColaBloqueante(ColaBloqueante&&) = delete;

	ColaBloqueante(){
		cerrada = false;
	}

	void depositar(T t){
		std::lock_guard<std::mutex> lock(m);
		cola.push(t);
		cv.notify_one();
	}

	T retirar(){
		std::unique_lock<std::mutex> ul(m);
		if (cola.empty()) cv.wait(ul, [&]{return !cola.empty() || cerrada;});
		if (cola.empty()) throw ColaVacia();
		T elemento = cola.front();
		cola.pop();
		return elemento;
	}

	bool estaVacia(){
		std::lock_guard<std::mutex> lock(m);
		return cola.empty();
	}

	void cerrar(){
		std::lock_guard<std::mutex> lock(m);
		cerrada = true;
		cv.notify_all();
	}

	bool estaCerrada(){
		std::lock_guard<std::mutex> lock(m);
		return cerrada;
	}
};

template <> class ColaBloqueante<void*>{
private:
	bool cerrada;
	std::mutex m;
	std::queue<void*> cola;
	std::condition_variable cv;

public:
	ColaBloqueante(const ColaBloqueante&)  = delete;
	ColaBloqueante(const ColaBloqueante&&) = delete;
	ColaBloqueante(ColaBloqueante&&) = delete;

	ColaBloqueante(){
		cerrada = false;
	}

	void depositar(void* t){
		std::lock_guard<std::mutex> lock(m);
		cola.push(t);
		cv.notify_one();
	}

	void* retirar(){
		std::unique_lock<std::mutex> ul(m);
		if (cola.empty()) cv.wait(ul, [&]{return !cola.empty() || cerrada;});
		if (cola.empty()) throw ColaVacia();
		void* elemento = cola.front();
		cola.pop();
		return elemento;
	}

	bool estaVacia(){
		std::lock_guard<std::mutex> lock(m);
		return cola.empty();
	}

	void cerrar(){
		std::lock_guard<std::mutex> lock(m);
		cerrada = true;
		cv.notify_all();
	}

	bool estaCerrada(){
		std::lock_guard<std::mutex> lock(m);
		return cerrada;
	}
};

template <class T> class ColaBloqueante<T*> : private ColaBloqueante<void*>{
	T* retirar(){
		return (T*) ColaBloqueante<void*>::retirar();
	}
};

#endif /*__COLA_BLOQUEANTE_H__*/
