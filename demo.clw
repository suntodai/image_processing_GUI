; CLW file contains information for the MFC ClassWizard

[General Info]
Version=1
LastClass=CDemoView
LastTemplate=CDialog
NewFileInclude1=#include "stdafx.h"
NewFileInclude2=#include "demo.h"
LastPage=0

ClassCount=14
Class1=CDemoApp
Class2=CDemoDoc
Class3=CDemoView
Class4=CMainFrame

ResourceCount=21
Resource1=IDR_DEMOTYPE
Resource2=IDD_RotateDlg
Class5=CChildFrame
Class6=CAboutDlg
Resource3=IDD_ZoomTimesDlg
Class7=ZoomTimesDlg
Resource4=IDD_ThreshDlg
Class8=RotateDlg
Resource5=IDD_MaskDlg
Class9=MaskDlg
Resource6=IDD_LinearStrech
Class10=DefineMaskDlg
Resource7=IDD_ABOUTBOX
Class11=threshDlg
Resource8=IDR_MAINFRAME
Class12=linearStretch
Resource9=IDD_DefineMask
Class13=morphologyDlg
Resource10=IDD_MorphologyDlg
Resource11=IDR_MAINFRAME (Chinese (中国))
Resource12=IDD_DefineMask (Chinese (中国))
Resource13=IDR_DEMOTYPE (Chinese (中国))
Resource14=IDD_ZoomTimesDlg (Chinese (中国))
Resource15=IDD_ABOUTBOX (Chinese (中国))
Resource16=IDD_RotateDlg (Chinese (中国))
Resource17=IDD_LinearStrech (Chinese (中国))
Resource18=IDD_ThreshDlg (Chinese (中国))
Resource19=IDD_MaskDlg (Chinese (中国))
Resource20=IDD_MorphologyDlg (Chinese (中国))
Class14=noiseDlg
Resource21=IDD_NoiseDlg

[CLS:CDemoApp]
Type=0
HeaderFile=demo.h
ImplementationFile=demo.cpp
Filter=N

[CLS:CDemoDoc]
Type=0
HeaderFile=demoDoc.h
ImplementationFile=demoDoc.cpp
Filter=N
LastObject=CDemoDoc

[CLS:CDemoView]
Type=0
HeaderFile=demoView.h
ImplementationFile=demoView.cpp
Filter=C
LastObject=ID_OPEN_SEQ
BaseClass=CScrollView
VirtualFilter=VWC


[CLS:CMainFrame]
Type=0
HeaderFile=MainFrm.h
ImplementationFile=MainFrm.cpp
Filter=T
LastObject=ID_FILE_OPEN


[CLS:CChildFrame]
Type=0
HeaderFile=ChildFrm.h
ImplementationFile=ChildFrm.cpp
Filter=M
LastObject=CChildFrame


[CLS:CAboutDlg]
Type=0
HeaderFile=demo.cpp
ImplementationFile=demo.cpp
Filter=D
LastObject=CAboutDlg

[DLG:IDD_ABOUTBOX]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[MNU:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[TB:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_DEMOTYPE]
Type=1
Class=CDemoView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=id_ImgReverse
Command16=id_RGBToGray
Command17=id_linearTrans
Command18=id_histAver
Command19=id_FFT
Command20=id_IFFT
Command21=id_Zoom
Command22=id_RotateTrans
Command23=ID_SOBEL
Command24=ID_Robot
Command25=id_prewitt
Command26=id_Laplacian
Command27=id_DajinThresh
Command28=ID_MENUITEM32774
Command29=id_MidleFilter
Command30=id_MeanFilter
Command31=id_ErosionErzhi
Command32=id_ErzhiExpand
Command33=id_ErzhiOpen
Command34=id_ErzhClose
Command35=id_GrayErose
Command36=id_GrayExpand
Command37=id_GrayOpen
Command38=id_GreyClose
Command39=id_MorphologyGrad
Command40=id_TopHatPeak
Command41=id_TopHatVally
Command42=id_TophatPeakVally
Command43=ID_VIEW_TOOLBAR
Command44=ID_VIEW_STATUS_BAR
Command45=ID_WINDOW_NEW
Command46=ID_WINDOW_CASCADE
Command47=ID_WINDOW_TILE_HORZ
Command48=ID_WINDOW_ARRANGE
Command49=ID_APP_ABOUT
CommandCount=49

[ACL:IDR_MAINFRAME]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ZoomTimesDlg]
Type=1
Class=ZoomTimesDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO1,button,1342373897
Control7=IDC_RADIO2,button,1342242825
Control8=IDC_STATIC,button,1342177287
Control9=IDC_RADIO3,button,1342373897
Control10=IDC_RADIO4,button,1342242825

[CLS:ZoomTimesDlg]
Type=0
HeaderFile=ZoomTimesDlg.h
ImplementationFile=ZoomTimesDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_RotateDlg]
Type=1
Class=RotateDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[CLS:RotateDlg]
Type=0
HeaderFile=RotateDlg.h
ImplementationFile=RotateDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_MaskDlg]
Type=1
Class=MaskDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO1,button,1342373897
Control5=IDC_RADIO2,button,1342242825
Control6=IDC_RADIO3,button,1342242825
Control7=IDC_RADIO4,button,1342177289

[CLS:MaskDlg]
Type=0
HeaderFile=MaskDlg.h
ImplementationFile=MaskDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=ID_APP_ABOUT
VirtualFilter=dWC

[DLG:IDD_DefineMask]
Type=1
Class=DefineMaskDlg
ControlCount=27
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_EDIT5,edit,1350631552
Control8=IDC_EDIT6,edit,1350631552
Control9=IDC_EDIT7,edit,1350631552
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_EDIT9,edit,1350631552
Control12=IDC_EDIT10,edit,1350631552
Control13=IDC_EDIT11,edit,1350631552
Control14=IDC_EDIT12,edit,1350631552
Control15=IDC_EDIT13,edit,1350631552
Control16=IDC_EDIT14,edit,1350631552
Control17=IDC_EDIT15,edit,1350631552
Control18=IDC_EDIT16,edit,1350631552
Control19=IDC_EDIT17,edit,1350631552
Control20=IDC_EDIT18,edit,1350631552
Control21=IDC_EDIT19,edit,1350631552
Control22=IDC_EDIT20,edit,1350631552
Control23=IDC_EDIT21,edit,1350631552
Control24=IDC_EDIT22,edit,1350631552
Control25=IDC_EDIT23,edit,1350631552
Control26=IDC_EDIT24,edit,1350631552
Control27=IDC_EDIT25,edit,1350631552

[CLS:DefineMaskDlg]
Type=0
HeaderFile=DefineMaskDlg.h
ImplementationFile=DefineMaskDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=DefineMaskDlg
VirtualFilter=dWC

[DLG:IDD_ThreshDlg]
Type=1
Class=threshDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[CLS:threshDlg]
Type=0
HeaderFile=threshDlg.h
ImplementationFile=threshDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

[DLG:IDD_LinearStrech]
Type=1
Class=linearStretch
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4,edit,1350631552
Control11=IDC_STATIC,static,1342308352

[CLS:linearStretch]
Type=0
HeaderFile=linearStretch.h
ImplementationFile=linearStretch.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_EDIT1
VirtualFilter=dWC

[DLG:IDD_MorphologyDlg]
Type=1
Class=morphologyDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO1,button,1342373897
Control5=IDC_RADIO2,button,1342242825

[CLS:morphologyDlg]
Type=0
HeaderFile=morphologyDlg.h
ImplementationFile=morphologyDlg.cpp
BaseClass=CDialog
Filter=D
LastObject=IDC_RADIO1
VirtualFilter=dWC

[TB:IDR_MAINFRAME (Chinese (中国))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_EDIT_CUT
Command5=ID_EDIT_COPY
Command6=ID_EDIT_PASTE
Command7=ID_FILE_PRINT
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_MAINFRAME (Chinese (中国))]
Type=1
Class=CMainFrame
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_PRINT_SETUP
Command4=ID_FILE_MRU_FILE1
Command5=ID_APP_EXIT
Command6=ID_VIEW_TOOLBAR
Command7=ID_VIEW_STATUS_BAR
Command8=ID_APP_ABOUT
CommandCount=8

[MNU:IDR_DEMOTYPE (Chinese (中国))]
Type=1
Class=CDemoView
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_CLOSE
Command4=ID_FILE_SAVE
Command5=ID_FILE_SAVE_AS
Command6=ID_FILE_PRINT
Command7=ID_FILE_PRINT_PREVIEW
Command8=ID_FILE_PRINT_SETUP
Command9=ID_FILE_MRU_FILE1
Command10=ID_APP_EXIT
Command11=ID_EDIT_UNDO
Command12=ID_EDIT_CUT
Command13=ID_EDIT_COPY
Command14=ID_EDIT_PASTE
Command15=id_ImgReverse
Command16=id_RGBToGray
Command17=id_linearTrans
Command18=id_histAver
Command19=id_FFT
Command20=id_IFFT
Command21=id_Zoom
Command22=id_RotateTrans
Command23=ID_SOBEL
Command24=ID_Robot
Command25=id_prewitt
Command26=id_Laplacian
Command27=id_DajinThresh
Command28=ID_MENUITEM32774
Command29=id_MidleFilter
Command30=id_MeanFilter
Command31=id_ErosionErzhi
Command32=id_ErzhiExpand
Command33=id_ErzhiOpen
Command34=id_ErzhClose
Command35=id_GrayErose
Command36=id_GrayExpand
Command37=id_GrayOpen
Command38=id_GreyClose
Command39=id_MorphologyGrad
Command40=id_TopHatPeak
Command41=id_TopHatVally
Command42=id_TophatPeakVally
Command43=ID_ZoomSmall
Command44=ID_ZoomLarge
Command45=ID_GaussNoise
Command46=ID_Rotate
Command47=ID_Shift
Command48=ID_Blur
Command49=ID_MotionBlur
Command50=ID_GenLR
Command51=ID_OPEN_SEQ
Command52=ID_Winner
Command53=ID_TSS
Command54=ID_DS
Command55=ID_POCS
Command56=ID_VIEW_TOOLBAR
Command57=ID_VIEW_STATUS_BAR
Command58=ID_WINDOW_NEW
Command59=ID_WINDOW_CASCADE
Command60=ID_WINDOW_TILE_HORZ
Command61=ID_WINDOW_ARRANGE
Command62=ID_APP_ABOUT
CommandCount=62

[ACL:IDR_MAINFRAME (Chinese (中国))]
Type=1
Class=?
Command1=ID_FILE_NEW
Command2=ID_FILE_OPEN
Command3=ID_FILE_SAVE
Command4=ID_FILE_PRINT
Command5=ID_EDIT_UNDO
Command6=ID_EDIT_CUT
Command7=ID_EDIT_COPY
Command8=ID_EDIT_PASTE
Command9=ID_EDIT_UNDO
Command10=ID_EDIT_CUT
Command11=ID_EDIT_COPY
Command12=ID_EDIT_PASTE
Command13=ID_NEXT_PANE
Command14=ID_PREV_PANE
CommandCount=14

[DLG:IDD_ABOUTBOX (Chinese (中国))]
Type=1
Class=CAboutDlg
ControlCount=5
Control1=IDC_STATIC,static,1342177283
Control2=IDC_STATIC,static,1342308480
Control3=IDC_STATIC,static,1342308352
Control4=IDOK,button,1342373889
Control5=IDC_STATIC,static,1342308352

[DLG:IDD_ZoomTimesDlg (Chinese (中国))]
Type=1
Class=ZoomTimesDlg
ControlCount=10
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352
Control5=IDC_STATIC,button,1342177287
Control6=IDC_RADIO1,button,1342373897
Control7=IDC_RADIO2,button,1342242825
Control8=IDC_STATIC,button,1342177287
Control9=IDC_RADIO3,button,1342373897
Control10=IDC_RADIO4,button,1342242825

[DLG:IDD_RotateDlg (Chinese (中国))]
Type=1
Class=RotateDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_STATIC,static,1342308352

[DLG:IDD_MaskDlg (Chinese (中国))]
Type=1
Class=MaskDlg
ControlCount=7
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO1,button,1342373897
Control5=IDC_RADIO2,button,1342242825
Control6=IDC_RADIO3,button,1342242825
Control7=IDC_RADIO4,button,1342177289

[DLG:IDD_DefineMask (Chinese (中国))]
Type=1
Class=DefineMaskDlg
ControlCount=27
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_EDIT1,edit,1350631552
Control4=IDC_EDIT2,edit,1350631552
Control5=IDC_EDIT3,edit,1350631552
Control6=IDC_EDIT4,edit,1350631552
Control7=IDC_EDIT5,edit,1350631552
Control8=IDC_EDIT6,edit,1350631552
Control9=IDC_EDIT7,edit,1350631552
Control10=IDC_EDIT8,edit,1350631552
Control11=IDC_EDIT9,edit,1350631552
Control12=IDC_EDIT10,edit,1350631552
Control13=IDC_EDIT11,edit,1350631552
Control14=IDC_EDIT12,edit,1350631552
Control15=IDC_EDIT13,edit,1350631552
Control16=IDC_EDIT14,edit,1350631552
Control17=IDC_EDIT15,edit,1350631552
Control18=IDC_EDIT16,edit,1350631552
Control19=IDC_EDIT17,edit,1350631552
Control20=IDC_EDIT18,edit,1350631552
Control21=IDC_EDIT19,edit,1350631552
Control22=IDC_EDIT20,edit,1350631552
Control23=IDC_EDIT21,edit,1350631552
Control24=IDC_EDIT22,edit,1350631552
Control25=IDC_EDIT23,edit,1350631552
Control26=IDC_EDIT24,edit,1350631552
Control27=IDC_EDIT25,edit,1350631552

[DLG:IDD_ThreshDlg (Chinese (中国))]
Type=1
Class=threshDlg
ControlCount=4
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552

[DLG:IDD_LinearStrech (Chinese (中国))]
Type=1
Class=linearStretch
ControlCount=11
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,static,1342308352
Control4=IDC_EDIT1,edit,1350631552
Control5=IDC_STATIC,static,1342308352
Control6=IDC_EDIT3,edit,1350631552
Control7=IDC_STATIC,static,1342308352
Control8=IDC_EDIT2,edit,1350631552
Control9=IDC_STATIC,static,1342308352
Control10=IDC_EDIT4,edit,1350631552
Control11=IDC_STATIC,static,1342308352

[DLG:IDD_MorphologyDlg (Chinese (中国))]
Type=1
Class=morphologyDlg
ControlCount=5
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_STATIC,button,1342177287
Control4=IDC_RADIO1,button,1342373897
Control5=IDC_RADIO2,button,1342242825

[DLG:IDD_NoiseDlg]
Type=1
Class=noiseDlg
ControlCount=6
Control1=IDOK,button,1342242817
Control2=IDCANCEL,button,1342242816
Control3=IDC_NioseAuto,edit,1350631552
Control4=IDC_NoiseVar,edit,1350631552
Control5=IDC_STATIC,static,1342308353
Control6=IDC_STATIC,static,1342308353

[CLS:noiseDlg]
Type=0
HeaderFile=noiseDlg.h
ImplementationFile=noiseDlg.cpp
BaseClass=CDialog
Filter=D
VirtualFilter=dWC

