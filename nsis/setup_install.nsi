;--------------------------------
;Include Modern UI

;  !include "MUI2.nsh"
XPStyle on

; The name of the installer
Name "YAVC"
VIProductVersion "0.1.1.0"
LicenseData License.txt
LicenseForceSelection checkbox

VIAddVersionKey "ProductName" "YAVC"
VIAddVersionKey "Comments" ""
VIAddVersionKey "CompanyName" "SonicIT - Soluções em TI"
VIAddVersionKey "FileDescription" "Instalador do YAVC"
VIAddVersionKey "FileVersion" $VIProductVersion
	
; The file to write
OutFile "yavc-setup.exe"
SetCompressor /SOLID lzma
; The default installation directory
InstallDir $PROGRAMFILES\YAVC


; Registry key to check for directory (so if you install again, it will 
; overwrite the old one automatically)
InstallDirRegKey HKLM "Software\YAVC" "Install_Dir"

; Request application privileges for Windows Vista
RequestExecutionLevel admin

;--------------------------------

; Pages

Page license
Page components
Page directory
Page instfiles

UninstPage uninstConfirm
UninstPage instfiles

;--------------------------------

; The stuff to install
Section "YAVC (required)"

  SectionIn RO
  
  ; Set output path to the installation directory.
  SetOutPath $INSTDIR
  
  ; Put file there
  File "..\..\YAVC-build-desktop-Qt_4_7_4_for_Desktop_-_MinGW_4_4__Qt_SDK__Release\release\YAVC.exe"
  File "C:\QtSDK\mingw\bin\mingwm10.dll"
  File "C:\QtSDK\mingw\bin\libgcc_s_dw2-1.dll"
  File "C:\QtSDK\Desktop\Qt\4.7.4\mingw\bin\QtCore4.dll"
  File "C:\QtSDK\Desktop\Qt\4.7.4\mingw\bin\QtGui4.dll"
  File "C:\Users\Alexandro\Downloads\ffmpeg-git-985e768-win32-static\bin\ffmpeg.exe"
  
  
  ; Write the installation path into the registry
  WriteRegStr HKLM SOFTWARE\YAVC "Install_Dir" "$INSTDIR"
  
  ; Write the uninstall keys for Windows
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\YAVC" "DisplayName" "YAVC"
  WriteRegStr HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\YAVC" "UninstallString" '"$INSTDIR\uninstall.exe"'
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\YAVC" "NoModify" 1
  WriteRegDWORD HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\YAVC" "NoRepair" 1
  WriteUninstaller "uninstall.exe"
  
SectionEnd

; Optional section (can be disabled by the user)
Section "Start Menu Shortcuts"

  CreateDirectory "$SMPROGRAMS\YAVC"
  CreateShortCut "$SMPROGRAMS\YAVC\Uninstall.lnk" "$INSTDIR\uninstall.exe" "" "$INSTDIR\uninstall.exe" 0
  CreateShortCut "$SMPROGRAMS\YAVC\YAVC.lnk" "$INSTDIR\YAVC.exe" "" "$INSTDIR\YAVC.exe" 0
  
SectionEnd

;--------------------------------

; Uninstaller

Section "Uninstall"
  
  ; Remove registry keys
  DeleteRegKey HKLM "Software\Microsoft\Windows\CurrentVersion\Uninstall\YAVC"
  DeleteRegKey HKLM SOFTWARE\YAVC

  ; Remove files and uninstaller
  Delete $INSTDIR\*.*
  Delete $INSTDIR

  ; Remove shortcuts, if any
  Delete "$SMPROGRAMS\YAVC\*.*"

  ; Remove directories used
  RMDir "$SMPROGRAMS\YAVC"
  RMDir "$INSTDIR"

SectionEnd
