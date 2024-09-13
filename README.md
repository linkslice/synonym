# synonym
*nix command alias generator


to install:

`make && make install`


Usage: 
````
./synonym [-m method] [-f file] [-p] [-h] [-t target] <command>
Options:
  -m <method>   : Alias generation method
                  1 : Use first letter of each word (default)
                  2 : Use first two letters of each word
                  3 : Use first three letters of each word
  -f <file>     : Specify file to check for existing aliases (default: .profile)
  -p            : Display a list of popular aliases
  -h            : Display this help screen
  -t <target>   : Specify target OS for alias generation (linux, macos, freebsd, openbsd, solaris, aix, hpux)
````




