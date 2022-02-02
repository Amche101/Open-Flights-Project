# CS225 Final Project -- Graph

This is the github for cs225 final project Fall 2020. It's a graph implementation for analyzing flights data. 

## Table of contents
* [General info](#General-info)
* [Credits](#Credit)
* [Language](#Language)
* [Implemented Algorithms](#Implemented-Algorithms)
* [Setup](#Setup)

## General-info
This project reads data from the airports.txt and routes.txt, and then parses them to store in an adjacent-list implemented graph data structure. Some visualization methods including printint the graph to terminal and makeing a png are also built in. The data source is from https://openflights.org/data.html#airport.

## Credit
* Haijian Wang
* Alex Chen
* Aasheesh Randeo
* Sabien Bell
	
## Language
Project is created with:
* C++

## Implemented-Algorithms
* BFS
* Dijkstra's Algorithm
* Eulerian Path/Cycle
	
## Setup
To run this project, download it locally:

```
$ cd final_project
$ make
$ ./final_project
```

To run the tests for this project, download it locally:

```
$ cd final_project
$ make test
$ ./test
```
