import osmnx as ox

# קואורדינטות של אזור מסוים
G = ox.graph_from_place("Tel Aviv, Israel", network_type="drive")

# שמירת nodes ו-edges כ-JSON
nodes, edges = ox.graph_to_gdfs(G)
nodes.to_file("data_base/nodes.json", driver="GeoJSON")
edges.to_file("data_base/edges.json", driver="GeoJSON")