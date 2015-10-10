# Yiying Wang 10-9-2015
# Function: Convert the SNAP graph file into adjacency list format 
# Input file: amazon0302.txt 
# Output file: amazon0302.adjacencyList.txt


import sys 
import resource
 

def EdgeToAdjencyList(edge, n): 
    AdjencyList = {}
    for i in range(0,n+1):
        AdjencyList[i] = []
    
    for i in range(0, len(edge)):
        AdjencyList[edge[i][0]].append(edge[i][1])
    return AdjencyList


text_file = open('amazon0302.txt', 'r')
lines = text_file.readlines()
edge = []
n = 262110
for i in range(0, len(lines)):
	new_line = lines[i].strip().split()
	tail = int(new_line[0])
	head = int(new_line[1])
	edge.append([tail, head])
graph = EdgeToAdjencyList(edge, n)
for i in range(0,n+1):
	print i,
	for item in graph[i]:
		print item,
	print \



