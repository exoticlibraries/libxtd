
# Download

## Using installation scripts

### Windows

Install the library using powershell. It auto detect your insalled C and C++ compilers include directory and install libxtd into the include folder. Execute the command in powershell as admin to install libxtd for compiler like Visual C++.

```powershell
& $([scriptblock]::Create((New-Object Net.WebClient).DownloadString("https://exoticlibraries.github.io/magic/install.ps1"))) libxtd
```

If you have one of the following compilers in your system the library will be installed for each of them.

- GCC
- Clang
- Visual C++

For other compilers the files library will be downloaded into the current working directory and can be moved into your include path or used directly in your project.

### Linux
Use the remote installation script to install libxtd with bash. If the command is executes with super user priviledge (sudo) it will be installed in the folder /usr/include else it will be installed in the folder /usr/local/include. Or you can specify where to install it using the option –installfolder=./

```bash
bash <(curl -s https://exoticlibraries.github.io/magic/install.sh) libxtd
```

The command above also works for installing libxtd on Android using the Termux application.

## Other Platforms

You can simply clone the repository into your project source folder and include it in your project. Download the repository from https://github.com/exoticlibraries/libxtd/releases. Then you can include it in your project relatively like #include “exotic/xtd/io/fs.h”.
