# Class: CSC-615-01 Spring 2020
# Name: Osbaldo Martinez
# Student ID: 916754207
# Project: <Assignment 2 - Tapeless Ruler>
CC=gcc
CFLAGS= -g -Wall -I.
DEPS = echoSensor.h
OBJ = assigment2.o echoSensor.o 

%.o: %.c $(DEPS)
	sudo $(CC) -c -o $@ $< $(CFLAGS)

assigment2: $(OBJ)
	sudo $(CC) -o $@ $^ $(CFLAGS) -lwiringPi
