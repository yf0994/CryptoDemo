#ifndef __JNI_EXCEPTIONS_H__
#define __JNI_EXCEPTIONS_H__

#include <exception>
#include <string>

#include <jni.h>

using std::string;

namespace exception
{

class Exception : public std::exception
{
public:
	Exception(string what) noexcept :
		exception(),
		what_(what){}
	virtual ~Exception() throw (){}
	virtual const char* what(){ return what_.c_str(); }

protected:
	string what_;
};

class BaseException : public Exception
{
public:
	BaseException(string what) :
		Exception(what){}
	virtual ~BaseException() throw(){}
	virtual const char* what(){ string tmp = "===" + what_; return tmp.c_str(); }
};

class BaseError : public Exception
{
public:
	BaseError(string what) :
		Exception(what){}
	virtual ~BaseError() throw(){}
	virtual const char* what(){ string tmp = "***" + what_; return tmp.c_str(); }
};

class FileNotFoundException : public BaseException
{
public:
	FileNotFoundException(string what) :
		BaseException(string("<FileNotFoundException>:") + what){}
};

class FileIOException : public BaseException
{
public:
	FileIOException(const char *what) :
		BaseException(string("<FileIOException>:") + what){}
};

class FileReadError : public BaseError
{
public:
	FileReadError(string what) :
		BaseError(string("<FileReadError>:") + what){}
};

class FileWriteError : public BaseError
{
public:
	FileWriteError(string what) :
		BaseError(string("<FileWriteError>:") + what){}
};

/*
extern void throwException(JNIEnv* env,
        jclass exceptionClass,
        jmethodID ctor3,
		jmethodID ctor2,
		const char* functionName,
		int error);

extern void throwErrnoException(JNIEnv* env, const char* functionName);

template<typename rc_t>
rc_t throwIfMinusOne(JNIEnv* env, const char* name, rc_t rc)
{
    LOG_E("throwIfMinusOne");

	if (rc == rc_t(-1))
		throwErrnoException(env, name);
	return rc;
}
*/

}

#endif
