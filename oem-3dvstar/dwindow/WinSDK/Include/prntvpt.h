
/*++

Copyright (c) 1996-2004 Microsoft Corporation

Module Name:

    prnptntv.h

Abstract:

    Print ticket APIs for Win32 applications

--*/

#ifndef _PRNPTNTV_H_
#define _PRNPTNTV_H_

#ifdef __cplusplus
extern "C" {
#endif  /* __cplusplus */

DECLARE_HANDLE(HPTPROVIDER);

#define PRINTTICKET_ISTREAM_APIS 1

#define S_PT_NO_CONFLICT                 (0x00040001)
#define S_PT_CONFLICT_RESOLVED           (0x00040002)

/*
    PrintTicket stream provided by the caller did not
    follow PrintTicket framework specification or the XML
    could not be parsed.  If returned by 
    PTMergeAndValidatePrintTicket, it indicates that the 
    base ticket contained the error.
*/
#define E_PRINTTICKET_FORMAT             (0x80040003)

/*
    PrintCapabilities document generated by the driver
    did not follow the specification.  This indicates an
    error in the driver.
*/
#define E_PRINTCAPABILITIES_FORMAT       (0x80040004)

/*
    The delta print ticket parameter passed to 
    PTMergeAndValidatePrintTicket did not
    follow PrintTicket framework specification or
    the XML could not be parsed.
*/
#define E_DELTA_PRINTTICKET_FORMAT       (0x80040005)

typedef enum tagEDefaultDevmodeType
{
    kUserDefaultDevmode,
    kPrinterDefaultDevmode
} EDefaultDevmodeType;

typedef enum 
{
    kPTPageScope,
    kPTDocumentScope,
    kPTJobScope
} EPrintTicketScope;


HRESULT WINAPI
PTQuerySchemaVersionSupport(
            __in        PCWSTR       pszPrinterName,
            __out       DWORD       *pMaxVersion
            );

HRESULT WINAPI
PTOpenProvider( 
            __in        PCWSTR       pszPrinterName,
                        DWORD        dwVersion,
            __out       HPTPROVIDER *phProvider
            );

HRESULT WINAPI
PTOpenProviderEx( 
            __in  PCWSTR       pszPrinterName,
                  DWORD        dwMaxVersion,
                  DWORD        dwPrefVersion,
            __out HPTPROVIDER *phProvider,
            __out DWORD       *pUsedVersion
            );

HRESULT WINAPI
PTCloseProvider(
            __in  HPTPROVIDER hProvider
            );

HRESULT WINAPI
PTReleaseMemory(
    __in PVOID pBuffer
    );
    
HRESULT WINAPI
PTGetPrintCapabilities( 
            __in            HPTPROVIDER         hProvider,
            __in_opt        IStream            *pPrintTicket,
            __inout         IStream            *pCapabilities,
            __out_opt       BSTR               *pbstrErrorMessage
            );
        
HRESULT WINAPI
PTMergeAndValidatePrintTicket(
            __in            HPTPROVIDER        hProvider,
            __in            IStream           *pBaseTicket,
            __in_opt        IStream           *pDeltaTicket,
            __in            EPrintTicketScope  scope,
            __inout         IStream           *pResultTicket, 
            __out_opt       BSTR              *pbstrErrorMessage 
            );

HRESULT WINAPI
PTConvertPrintTicketToDevMode( 
            __in                     HPTPROVIDER          hProvider,
            __in                     IStream             *pPrintTicket,
                                     EDefaultDevmodeType  baseDevmodeType,
            __in                     EPrintTicketScope  scope,
            __out                    ULONG               *pcbDevmode,
            __deref_out_bcount(*pcbDevmode) OUT PDEVMODE *ppDevmode,
            __out_opt                BSTR                *pbstrErrorMessage 
            );
        
HRESULT WINAPI
PTConvertDevModeToPrintTicket( 
            __in        HPTPROVIDER        hProvider,
                        ULONG              cbDevmode,
            __in        PDEVMODE           pDevmode,
            __in        EPrintTicketScope  scope,
            __inout     IStream           *pPrintTicket
            );
        
#ifdef __cplusplus
}
#endif /* __cplusplus */

#endif /* _PRNPTNTV_H_ */

