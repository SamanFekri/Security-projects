# DES in Openssl
## Introduction
encrypt orginal.txt file with openssl des algorithm to enc.txt, then decrypt enc.txt to dec.txt.
## Usage
### Instal openssl
- List Item Download the tarball: openssl-1.0.0d.tar.gz
- Unpack the package	
~~~~
    ginzip openssl-1.0.2j.tar.gz	
~~~~
- Extractin files from the archive
	
~~~~
    tar xvf openssl-1.0.2j.tar
~~~~
- Install the package
	
~~~~
            cd openssl-1.0.2j 
            ./config
            sudo make
            sudo make test
            sudo make install	
~~~~
            
### Run application
	
~~~~
        gcc main.c -o main -lssl -lcrypto 
        ./main
~~~~