from pyvis.network import Network

g = Network(height="750px", width="100%")
edges = []
with open("/tmp/debug.csv") as f:
    for l in f:
        l = l[:-1].split(",")
        l = [int(e) for e in l]
        g.add_node(l[0], label=f"{l[0]}")
        print(l[0])
        for e in l[1:]:
            edges.append((l[0], e))

for e in edges:
    g.add_edge(e[0], e[1])

g.show_buttons()
g.show("g.html", notebook=False)
