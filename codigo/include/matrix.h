#include <vector>
#include <ostream>
#include <fstream>
#include <cmath>

#ifndef MATRIX_H
#define MATRIX_H

using namespace std;

template<class T>
void intercambiar(unsigned int o,unsigned int d,vector<T>& a)
{
    T aux = a[o];
    a[o] = a[d];
    a[d] = aux;
}

template<class T>
void intercambiar(int o,int d,vector<T>& a){v_swap((unsigned int)o,(unsigned int)d,a);}

template<class T>
void v_imprimir(vector<T> v, ostream & os)
{
	os << "[";
	for(unsigned int i = 0; i < v.size(); ++i){
		os << v[i];
		if(i == v.size()-1){
			os << "]" << endl;
		}
		else{
			os << ", ";
		}
	}
}

template<class T>
void v_imprimir(vector<T> v, ofstream & os)
{
	os << "[";
	for(unsigned int i = 0; i < v.size(); ++i){
		os << v[i];
		if(i == v.size()-1){
			os << "]" << endl;
		}
		else{
			os << ", ";
		}
	}
}

template<class T>
void m_imprimir(vector<vector<T> > m, ostream & os)
{
	for(unsigned int f = 0; f < m.size(); ++f){
		for(unsigned int c = 0; c < m[f].size(); ++c){
			os << m[f][c];
			if(c == m[f].size()-1){
				os << endl;
			}
			else{
				os << " ";
			}
		}
	}
}

template<class T>
void m_imprimir(vector<vector<T> > m, ofstream & os)
{
	for(unsigned int f = 0; f < m.size(); ++f){
		for(unsigned int c = 0; c < m[f].size(); ++c){
			os << m[f][c];
			if(c == m[f].size()-1){
				os << endl;
			}
			else{
				os << " ";
			}
		}
	}
}

#endif