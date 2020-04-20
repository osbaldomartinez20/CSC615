# Class: CSC-615-01 Spring 2020
# Name: Osbaldo Martinez
# Student ID: 916754207
# Project: <Assignment 4 - Motors>
# File: makefile
CC=gcc
CFLAGS= -g -Wall -I.
DEPS = motorsController.h encoderController.h
OBJ = assignment4.o motorsController.o encoderController.o 

%.o: %.c $(DEPS)
	sudo $(CC) -c -o $@ $< $(CFLAGS)

assignment3: $(OBJ)
	sudo $(CC) -o $@ $^ $(CFLAGS) -lwiringPi -lpthread