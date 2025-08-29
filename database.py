import os
import osmnx as ox
import geopandas as gpd
import json
import math
from pyproj import Transformer

os.makedirs("data_base", exist_ok=True)

city_name = "Tel Aviv, Israel"

# Load the driving network
G = ox.graph_from_place(city_name, network_type='drive')
nodes, edges = ox.graph_to_gdfs(G, nodes=True, edges=True)
nodes = nodes.reset_index()

# Mapping old node IDs to new sequential IDs
node_id_map = {old_id: new_id for new_id, old_id in enumerate(nodes['osmid'])}
nodes.set_index('osmid', inplace=True)

# Transformer for lat/lon to UTM (meters)
transformer_to_utm = Transformer.from_crs("epsg:4326", "epsg:2039", always_xy=True)
transformer_to_latlon = Transformer.from_crs("epsg:2039", "epsg:4326", always_xy=True)

def interpolate_edge(u_coords, v_coords, max_dist_m=20):
    """Interpolate points along an edge every max_dist_m meters (denser)."""
    x1, y1 = transformer_to_utm.transform(u_coords[0], u_coords[1])
    x2, y2 = transformer_to_utm.transform(v_coords[0], v_coords[1])
    dist = math.hypot(x2 - x1, y2 - y1)
    points = [u_coords]
    if dist > max_dist_m:
        n = int(dist // max_dist_m)
        for i in range(1, n+1):
            t = i / (n + 1)
            xi = x1 + t * (x2 - x1)
            yi = y1 + t * (y2 - y1)
            lon, lat = transformer_to_latlon.transform(xi, yi)
            points.append([lon, lat])
    points.append(v_coords)
    return points

# Nodes
nodes_list = []
nodes_coords_map = {}
new_node_id = 0
for osmid, row in nodes.iterrows():
    coord = [row['x'], row['y']]
    nodes_list.append({
        "type": "Feature",
        "geometry": {"type": "Point", "coordinates": coord},
        "properties": {"id": new_node_id}
    })
    nodes_coords_map[tuple(coord)] = new_node_id
    new_node_id += 1

# Edges
edges_list = []
for idx, row in edges.iterrows():
    u, v = idx[0], idx[1]
    u_coord = [nodes.loc[u]['x'], nodes.loc[u]['y']]
    v_coord = [nodes.loc[v]['x'], nodes.loc[v]['y']]
    interpolated_points = interpolate_edge(u_coord, v_coord, max_dist_m=20)  # 1 meter spacing
    prev_id = nodes_coords_map[tuple(interpolated_points[0])]
    for pt in interpolated_points[1:]:
        key = tuple(pt)
        if key in nodes_coords_map:
            curr_id = nodes_coords_map[key]
        else:
            curr_id = new_node_id
            nodes_coords_map[key] = curr_id
            nodes_list.append({
                "type": "Feature",
                "geometry": {"type": "Point", "coordinates": pt},
                "properties": {"id": curr_id}
            })
            new_node_id += 1
        length = math.hypot(pt[0]-interpolated_points[0][0], pt[1]-interpolated_points[0][1]) * 111000
        edges_list.append({
            "type": "Feature",
            "geometry": None,
            "properties": {"u": prev_id, "v": curr_id, "length": length}
        })
        prev_id = curr_id
        interpolated_points[0] = pt

# Save nodes and edges as GeoJSON
with open("data_base/nodes.geojson", "w", encoding="utf-8") as f:
    json.dump({"type": "FeatureCollection", "features": nodes_list}, f, ensure_ascii=False, indent=2)

with open("data_base/edges.geojson", "w", encoding="utf-8") as f:
    json.dump({"type": "FeatureCollection", "features": edges_list}, f, ensure_ascii=False, indent=2)

print(f"Dense GeoJSON database saved with {len(nodes_list)} nodes and {len(edges_list)} edges.")
