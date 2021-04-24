
#include <Python.h>
#include <Windows.h>
#include "spider.h"
extern "C"
{
	__declspec(dllexport) int __stdcall _spider(void)
	{
		return spider();
	}
}

BOOL WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpReserved)
{
	static wchar_t* program;
	switch (fdwReason)
	{
	case DLL_PROCESS_ATTACH:
		program = Py_DecodeLocale("spider", NULL);
		//dll初始化的时候调用，这是python3的写法，python2改成，initrun()。参见生成的run.h
		PyImport_AppendInittab("spider", PyInit_spider);
		Py_SetProgramName(program);
		Py_Initialize();
		PyImport_ImportModule("spider");
		break;
	case DLL_PROCESS_DETACH:
		PyMem_RawFree(program);
		Py_Finalize();
		break;
	}
	return TRUE;
}

//int main(int argc, char* argv[])
//{
//	PyObject* pmodule;
//	wchar_t* program = NULL;
//
//	//program = Py_DecodeLocale(argv[0], NULL);
//	/*if (program == NULL) {
//		fprintf(stderr, "Fatal error: cannot decode argv[0], got %d arguments\n", argc);
//		exit(1);
//	}*/
//
//	/* Add a built-in module, before Py_Initialize */
//	if (PyImport_AppendInittab("embedded", PyInit_demo) == -1) {
//		fprintf(stderr, "Error: could not extend in-built modules table\n");
//		exit(1);
//	}
//
//	/* Pass argv[0] to the Python interpreter */
//	//Py_SetProgramName(program);
//
//	/* Initialize the Python interpreter.  Required.
//	   If this step fails, it will be a fatal error. */
//	Py_Initialize();
//
//	/* Optionally import the module; alternatively,
//	   import can be deferred until the embedded script
//	   imports it. */
//	/*pmodule = PyImport_ImportModule("embedded");
//	if (!pmodule) {
//		PyErr_Print();
//		fprintf(stderr, "Error: could not import module 'embedded'\n");
//		goto exit_with_error;
//	}*/
//
//	/* Now call into your module code. */
//	if (spider() < 0) {
//		PyErr_Print();
//		fprintf(stderr, "Error in Python code, exception was printed.\n");
//		goto exit_with_error;
//	}
//
//	/* ... */
//
//	/* Clean up after using CPython. */
//	PyMem_RawFree(program);
//	Py_Finalize();
//
//	return 0;
//
//	/* Clean up in the error cases above. */
//	exit_with_error:
//	PyMem_RawFree(program);
//	Py_Finalize();
//	return 1;
//}
//
