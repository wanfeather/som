import matplotlib.pyplot as plt
import pandas as pd
import networkx as nx
import math

df = pd.read_csv('weights_end.txt', index_col = False, header = None, sep = '\s+')

data_length = len(df)
map_length = int(math.sqrt(data_length))

graph = {df.iloc[index, 0]:(df.iloc[index, 1], df.iloc[index, 2]) for index in range(data_length)}

G = nx.Graph()
G.add_nodes_from(graph.keys())

edge = []
for index in range(data_length):
    if index % map_length < map_length-1:
        edge.append((index, index+1))
    if index / map_length < map_length-1:
        edge.append((index, index + map_length))
G.add_edges_from(edge)

nx.draw_networkx(G, pos = graph, with_labels = False, node_size = 30)
plt.savefig('graph.png')

plt.figure()
df = pd.read_csv('loss.csv', header = None, names = ['x', 'y'])
plt.plot(df['x'], df['y'])
plt.savefig('loss.png')