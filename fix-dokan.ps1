<#
.SYNOPSIS
    Rewrites vslvmmount.vcxproj to link against an installed Dokan library
    (BUILDS.md Step 4), instead of the from-source dokan build.

.DESCRIPTION
    For every <ItemDefinitionGroup> in the project it sets:
      - C/C++  > AdditionalIncludeDirectories : <DokanPath>\include\dokan
      - Linker > AdditionalLibraryDirectories : <DokanPath>\lib   (x64)
                                                <DokanPath>\x86\lib (Win32)
      - Linker > AdditionalDependencies       : dokan2.lib

.EXAMPLE
    .\fix-dokan.ps1
    .\fix-dokan.ps1 -DokanPath "C:\Program Files\Dokan\DokanLibrary-2.3.1" -LibName dokan2.lib
#>
[CmdletBinding()]
param(
    [string]$ProjectPath = "$PSScriptRoot\vs2022\vslvmmount\vslvmmount.vcxproj",
    [string]$DokanPath   = "C:\Program Files\Dokan\DokanLibrary-2.3.1",
    [string]$LibName     = "dokan2.lib"
)

$ErrorActionPreference = 'Stop'

if (-not (Test-Path $ProjectPath)) { throw "Project not found: $ProjectPath" }

$incDir    = Join-Path $DokanPath 'include\dokan'
$libDirX64 = Join-Path $DokanPath 'lib'
$libDirX86 = Join-Path $DokanPath 'x86\lib'

# Backup once
$backup = "$ProjectPath.bak"
if (-not (Test-Path $backup)) { Copy-Item $ProjectPath $backup }

[xml]$xml = Get-Content -Raw -LiteralPath $ProjectPath
$ns = New-Object System.Xml.XmlNamespaceManager($xml.NameTable)
$ns.AddNamespace('m', 'http://schemas.microsoft.com/developer/msbuild/2003')

# Replace the from-source dokan include token; keep all other include dirs intact.
$srcIncToken = '..\..\..\dokan\dokan'

$changed = 0
foreach ($idg in $xml.SelectNodes('//m:ItemDefinitionGroup', $ns)) {
    $cond = $idg.GetAttribute('Condition')
    $isX64 = $cond -match 'x64'
    $libDir = if ($isX64) { $libDirX64 } else { $libDirX86 }

    # --- C/C++ include dirs ---
    $inc = $idg.SelectSingleNode('m:ClCompile/m:AdditionalIncludeDirectories', $ns)
    if ($inc) {
        if ($inc.InnerText -like "*$srcIncToken*") {
            $inc.InnerText = $inc.InnerText.Replace($srcIncToken, $incDir)
        } elseif ($inc.InnerText -notlike "*$incDir*") {
            $inc.InnerText = "$incDir;" + $inc.InnerText
        }
        $changed++
    }

    $link = $idg.SelectSingleNode('m:Link', $ns)
    if ($link) {
        # --- Additional dependencies -> dokan2.lib ---
        $dep = $link.SelectSingleNode('m:AdditionalDependencies', $ns)
        if ($dep) {
            # strip any existing dokan*.lib token(s), prepend LibName
            $tokens = $dep.InnerText.Split(';') | Where-Object { $_ -and ($_ -notmatch 'dokan.*\.lib$') }
            $dep.InnerText = (@($LibName) + $tokens) -join ';'
        }
        # --- Additional library directories ---
        $libdirs = $link.SelectSingleNode('m:AdditionalLibraryDirectories', $ns)
        if ($libdirs) {
            if ($libdirs.InnerText -notlike "*$libDir*") {
                $libdirs.InnerText = "$libDir;" + $libdirs.InnerText
            }
        }
    }
}

$xml.Save($ProjectPath)
Write-Host "Patched $changed config(s) in $ProjectPath" -ForegroundColor Green
Write-Host "  include : $incDir"
Write-Host "  lib(x64): $libDirX64"
Write-Host "  lib(x86): $libDirX86"
Write-Host "  dep     : $LibName"
Write-Host "Backup    : $backup"
