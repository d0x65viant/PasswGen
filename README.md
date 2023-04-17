# PasswGen
#### A small password generator with a length of 20 characters, created for test purposes using the GTK3 library in C and the Glade graphics framework.

###  The ways to install GTK3 for your platform can be found at the following link:
https://www.gtk.org/docs/installations/
For Windows (MinGW-w64), after installing msys2 and all the necessary gtk3 development packages, you also need to add the path to the MinGW-w64 package to access gcc and pkg-config, and export this variable to msys2:
```
nano ~/.bashrc
export PATH="/c/msys64/mingw64/bin/:$PATH"
```

### Compilation:
```
./builder
```
---
![passwgen window](https://github.com/d0x65viant/Images/blob/main/PasswGen.png)
