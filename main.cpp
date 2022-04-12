#include <stdio.h>
#include <iostream>
#include <unistd.h>
#include <vector>

#include <Python.h>

using namespace std;


// PyObject -> Vector
vector<float> listTupleToVector_Float(PyObject* incoming) {
	vector<float> data;
	if (PyTuple_Check(incoming)) {
		for(Py_ssize_t i = 0; i < PyTuple_Size(incoming); i++) {
			PyObject *value = PyTuple_GetItem(incoming, i);
			data.push_back( PyFloat_AsDouble(value) );
		}
	} else {
		if (PyList_Check(incoming)) {
			for(Py_ssize_t i = 0; i < PyList_Size(incoming); i++) {
				PyObject *value = PyList_GetItem(incoming, i);
				data.push_back( PyFloat_AsDouble(value) );
			}
		} else {
			throw logic_error("Passed PyObject pointer was not a list or tuple!");
		}
	}
	return data;
}


int main() {
  

    Py_Initialize();

    // para encontrar o codigo python, colocamos no path do python o local atual.
    PyRun_SimpleString("import sys");
    PyRun_SimpleString("sys.path.append('./')");

    // importamos o script python env.py
    PyObject* my_module = PyImport_ImportModule("env");

    PyErr_Print();

    // referenciamos a funcao do modulo que queremos utilizar.
    PyObject* my_function = PyObject_GetAttrString(my_module,"create_list");

    
    // enviamos para sum
    int arg = 10;

    PyObject* arglist = Py_BuildValue("(i)", arg); // tipos=> https://docs.python.org/release/1.5.2p2/ext/buildValue.html

    PyObject* my_result = PyObject_CallObject(my_function,arglist);

    //double result = PyFloat_AsDouble(my_result);
    //printf("%d My result is :  %f\n", i, result);

    vector<float> data =  listTupleToVector_Float(my_result);

    cout << "A seguinte lista foi criada no python e retornada:" << endl;
    for(int i=0; i<data.size(); i++){
        printf("%f ", data[i]);
    }
    cout << endl;


    Py_Finalize();


    return 0;
}