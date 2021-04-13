#!/bin/bash

g++ serveur.cpp msglib.cc pcslib.cc -o server
g++ client.cpp msglib.cc pcslib.cc -o client
g++ main.cpp msglib.cc pcslib.cc memlib.cc -o go

chmod 777
./go