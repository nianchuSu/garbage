#include "Python.h"
#include "retfunc.h"

/*
 *老实的认真读代码
 不懂就百度,chatGPT查
 * */

void py_init(void)	// 初始化python环境
{
	Py_Initialize();	// 初始化解释器
						//
	PyObject *sys = PyImport_ImportModule("sys");		// 当前路径或者需要用的py模块/文件路径导入
	PyObject *path = PyObject_GetAttrString(sys,"path");	// sys导入path列表	获取path引用
	PyList_Append(path, PyUnicode_FromString("."));	// 将当前路径添加到path列表里	将c字符串转化为py字符串
}

void py_finish(void)	// 释放资源都要执行,关闭python环境
{
	Py_Finalize();	// py解释器关闭
}

/*
 *这个程序是无参调用函数,获得返回值,并解析返回值
 *返回值给c使用
 */
char *par_retfunc(char* rets)	// 传入一个指针
{
	PyObject *pModule = PyImport_ImportModule("img_discern");	// 导入模块,获取对应模块的引用,参数就是使用的模块名
	
	if(!pModule){	// 为NULL就进入
		PyErr_Print();	// 调用py异常报错
		printf("error Module\n");
		goto f_pmodu;
	}

	PyObject *pFunc = PyObject_GetAttrString(pModule,"image_identification");	// 获取模块中已有的函数名称如img_discern模块中的pr函数的对象与引用,并传入C字符串参数函数名
	if(!pFunc){	// 为NULL就进入
		PyErr_Print();	// 调用py异常报错
		printf("error Func\n");
		goto f_pfunc;
	}


	PyObject *pValue = PyObject_CallObject(pFunc,NULL);	// 调用函数获取返回值,参数1函数引用参数2是函数参数元组
	if(!pValue){	// 为NULL就进入
		PyErr_Print();	// 调用py异常报错
		printf("error Value\n");
		goto f_pval;
	}

	// 获得函数调用返回值
	char *ret=NULL;	
	if(!PyArg_Parse(pValue,"s",&ret)){	// 这个函数是取得函数调用返回值,存入ret中,让C使用,这里需要注意返回值类型与承接变量类型一致,"i"表示整数型,其他类型,网上找相关资料
		PyErr_Print();	// 调用py异常报错
		printf("error return\n");
		exit(-1);
	}

	printf("return:%s\n",ret);
	rets = (char*)malloc(sizeof(char)*strlen(ret)+1);	// 给传入的参数开辟空间
	memset(rets,0,strlen(ret)+1);	// 清空开辟的空间
	strncpy(rets,ret,strlen(ret)+1);		// 拷贝python获取到的值给C的返回值

f_pval:		// goto语句,百度查
	Py_DECREF(pValue);	// 关闭所有对象,依次向上关闭
f_pfunc:
	Py_DECREF(pFunc);	// 关闭所有对象,依次向上关闭
f_pmodu:
	Py_DECREF(pModule);	// 关闭所有对象,依次向上关闭


	return rets;
}
