gridfire_c
==========

Gridfire space game written in C with SFML 2.0

Installation
==========

````
./generate_objects 50000 [NUMBER OF ENEMIES e.g. 1000]
cmake .
make
./gridfire
````
or

```
./build_and_install.sh
```

Requirements
==========

- X11 headers (On OSX you'll need to either install xquartz or link the headers (see the net) )
- CSFML 2.0
    -Requires SFML2.0 Cbinding 
    -On linux this can usually be installed straight from package manager.
      -From OS X via http://www.sfml-dev.org/download/bindings.php
