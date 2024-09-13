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

Examples:
````
./synonym -t openbsd -p                  
# OpenBSD-specific aliases:
alias pkgup='doas pkg_add -u'
alias pfstat='doas pfctl -si'
alias pflog='doas tcpdump -n -e -ttt -i pflog0'
````
````
./synonym -t openbsd -p >> .profile
````
````
./synonym -m 2 -t openbsd 'vmctl status'
alias vmst='vmctl status'
````

````
./synonym -t linux -p
# Popular aliases people use:
alias ll='ls -la'
alias la='ls -A'
alias l='ls -CF'
alias grep='grep --color=auto'
alias df='df -h'
alias du='du -h'
alias vi='vim'
alias cls='clear'
alias cpv='rsync -ah --info=progress2'
alias mv='mv -i'
````



