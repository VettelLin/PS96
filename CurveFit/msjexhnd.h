// 【交接】 CurveFit\msjexhnd.h
// 作用：msjexhnd。本文件属于仪器上位机源码，打开时先看下面列出的函数名即可知道它负责的操作。
// 先看这些函数：MSJExceptionHandler、SetLogFileName、MSJUnhandledExceptionFilter、GenerateExceptionReport、GetExceptionString、GetLogicalAddress、IntelStackWalk、ImagehlpStackWalk。
#ifndef __MSJEXHND_H__
#define __MSJEXHND_H__
class MSJExceptionHandler
{
    public:
    
    MSJExceptionHandler( );
    ~MSJExceptionHandler( );
    
    void SetLogFileName( PTSTR pszLogFileName );

    private:

    // entry point where control comes on an unhandled exception
    static LONG WINAPI MSJUnhandledExceptionFilter(
                                PEXCEPTION_POINTERS pExceptionInfo );

    // where report info is extracted and generated 
    static void GenerateExceptionReport( PEXCEPTION_POINTERS pExceptionInfo );

    // Helper functions
    static LPTSTR GetExceptionString( DWORD dwCode );
    static BOOL GetLogicalAddress(  PVOID addr, PTSTR szModule, DWORD len,
                                    DWORD& section, DWORD& offset );
    static void IntelStackWalk( PCONTEXT pContext );
	#if 1
	// 函数 ImagehlpStackWalk
	// 作用：执行ImagehlpStackWalk。
	// 参数：pContext：指针，指向调用方传入的对象。
	// 返回：没有返回值。
	static void ImagehlpStackWalk( PCONTEXT pContext );
	#endif
    static int __cdecl _tprintf(const TCHAR * format, ...);

	#if 1
	// 函数 InitImagehlpFunctions
	// 作用：初始化InitImagehlpFunctions。
	// 参数：无。
	// 返回：返回是或否。
	static BOOL InitImagehlpFunctions( void );
	#endif

	#if 1
	// 函数 InitDbghelpFunctions
	// 作用：初始化InitDbghelpFunctions。
	// 参数：无。
	// 返回：返回是或否。
	static BOOL InitDbghelpFunctions( void );
	#endif
    // Variables used by the class
    static TCHAR m_szLogFileName[MAX_PATH];
    static LPTOP_LEVEL_EXCEPTION_FILTER m_previousFilter;
    static HANDLE m_hReportFile;

	static TCHAR m_szDmpFileName[MAX_PATH];
	#if 1
	// Make typedefs for some IMAGEHLP.DLL functions so that we can use them
	// with GetProcAddress
	// 函数 BOOL
	// 作用：执行BOOL。
	// 参数：HANDLE；LPSTR；BOOL：是或否。
	// 返回：返回 typedef。
	typedef BOOL (__stdcall * SYMINITIALIZEPROC)( HANDLE, LPSTR, BOOL );
	// 函数 BOOL
	// 作用：执行BOOL。
	// 参数：HANDLE。
	// 返回：返回 typedef。
	typedef BOOL (__stdcall *SYMCLEANUPPROC)( HANDLE );

	// 函数 BOOL
	// 作用：执行BOOL。
	// 参数：STACKWALKPROC。
	// 返回：返回 typedef。
	typedef BOOL (__stdcall * STACKWALKPROC)
					( DWORD, HANDLE, HANDLE, LPSTACKFRAME, LPVOID,
					PREAD_PROCESS_MEMORY_ROUTINE,PFUNCTION_TABLE_ACCESS_ROUTINE,
					PGET_MODULE_BASE_ROUTINE, PTRANSLATE_ADDRESS_ROUTINE );

	// 函数 LPVOID
	// 作用：执行LPVOID。
	// 参数：HANDLE；DWORD：小数。
	// 返回：返回 typedef。
	typedef LPVOID (__stdcall *SYMFUNCTIONTABLEACCESSPROC)( HANDLE, DWORD );

	// 函数 DWORD
	// 作用：执行DWORD。
	// 参数：HANDLE；DWORD：小数。
	// 返回：返回 typedef。
	typedef DWORD (__stdcall *SYMGETMODULEBASEPROC)( HANDLE, DWORD );

	// 函数 BOOL
	// 作用：执行BOOL。
	// 参数：SYMGETSYMFROMADDRPROC。
	// 返回：返回 typedef。
	typedef BOOL (__stdcall *SYMGETSYMFROMADDRPROC)
								( HANDLE, DWORD, PDWORD, PIMAGEHLP_SYMBOL );

	static SYMINITIALIZEPROC _SymInitialize;
	static SYMCLEANUPPROC _SymCleanup;
	static STACKWALKPROC _StackWalk;
	static SYMFUNCTIONTABLEACCESSPROC _SymFunctionTableAccess;
	static SYMGETMODULEBASEPROC _SymGetModuleBase;
	static SYMGETSYMFROMADDRPROC _SymGetSymFromAddr;

	// Make typedefs for some dbghelp.dll functions so that we can use them
	// 函数 BOOL
	// 作用：执行BOOL。
	// 参数：MINIDUMPWRITEDUMP。
	// 返回：返回 typedef。
	typedef BOOL (__stdcall *MINIDUMPWRITEDUMP)
		( HANDLE, DWORD, HANDLE, MINIDUMP_TYPE,
		PMINIDUMP_EXCEPTION_INFORMATION,PMINIDUMP_USER_STREAM_INFORMATION,PMINIDUMP_CALLBACK_INFORMATION );

	static MINIDUMPWRITEDUMP _MiniDumpWriteDump;

	#endif
	
};
extern MSJExceptionHandler g_MSJExceptionHandler;   //  global instance of class

#endif
