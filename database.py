import os
import osmnx as ox
import json

# Create directory if it doesn't exist
os.makedirs("data_base", exist_ok=True)

# Define city
city_name = "Tel Aviv, Israel"

# Download street network
G = ox.graph_from_place(city_name, network_type='drive')

# Get nodes and edges GeoDataFrames
nodes, edges = ox.graph_to_gdfs(G, nodes=True, edges=True)

# Reindex nodes with consecutive integers
old_to_new = {old_id: new_id for new_id, old_id in enumerate(nodes.index)}
nodes = nodes.reset_index(drop=True)

# Build nodes GeoJSON
nodes_features = []
for idx, row in nodes.iterrows():
    feature = {
        "type": "Feature",
        "geometry": {
            "type": "Point",
            "coordinates": [row["x"], row["y"]]  # lon, lat
        },
        "properties": {
            "id": idx
        }
    }
    nodes_features.append(feature)

nodes_geojson = {
    "type": "FeatureCollection",
    "features": nodes_features
}

with open("data_base/nodes.geojson", "w", encoding="utf-8") as f:
    json.dump(nodes_geojson, f, ensure_ascii=False, indent=2)

# Build edges GeoJSON
edges_features = []
for idx, row in edges.iterrows():
    u_old, v_old, *rest = idx  # unpack MultiIndex
    u = old_to_new[u_old]
    v = old_to_new[v_old]
    feature = {
        "type": "Feature",
        "geometry": None,  # optional: could add LineString coordinates here
        "properties": {
            "u": u,
            "v": v,
            "length": row.get("length", None)
        }
    }
    edges_features.append(feature)

edges_geojson = {
    "type": "FeatureCollection",
    "features": edges_features
}

with open("data_base/edges.geojson", "w", encoding="utf-8") as f:
    json.dump(edges_geojson, f, ensure_ascii=False, indent=2)

print("GeoJSON database saved to data_base/nodes.geojson and data_base/edges.geojson successfully!")
