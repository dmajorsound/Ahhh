; Roomservice installer for Windows (Inno Setup 6). The version comes from the build: ISCC /DAppVer=1.0.1 /DFileVer=1.0.1
#ifndef AppVer
  #define AppVer "1.0.1"
#endif
#ifndef FileVer
  #define FileVer "1.0.1"
#endif

[Setup]
AppId={{6F1C2B7E-4A3D-4E8B-9C21-7D5E0A1B2C33}
AppName=Roomservice
AppVersion={#AppVer}
AppPublisher=dmajorsound
AppPublisherURL=https://dmajorsound.com
DefaultDirName={commoncf64}\VST3
DisableDirPage=yes
DirExistsWarning=no
DisableProgramGroupPage=yes
PrivilegesRequired=admin
OutputBaseFilename=Roomservice_{#FileVer}_installer_win64
ArchitecturesAllowed=x64compatible
ArchitecturesInstallIn64BitMode=x64compatible
Uninstallable=yes
UninstallDisplayName=Roomservice (VST3)
UninstallFilesDir={commonappdata}\dmajorsound\Roomservice
WizardStyle=modern
WizardImageFile=wizard-100.bmp,wizard-200.bmp
WizardSmallImageFile=small-100.bmp,small-200.bmp
WizardImageStretch=no
DisableWelcomePage=no

[Files]
Source: "..\..\build\Roomservice_artefacts\Release\VST3\Roomservice.vst3\*"; DestDir: "{commoncf64}\VST3\Roomservice.vst3"; Flags: ignoreversion recursesubdirs createallsubdirs

[Messages]
WelcomeLabel1=Roomservice%nRoom Simulation
WelcomeLabel2=This installs Roomservice as VST3 plug-in into the common plug-in folder.%n%nAfterwards, rescan your plug-ins in your Applications.
