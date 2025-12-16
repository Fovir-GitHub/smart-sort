import yaml
import json
import pandas as pd
from pathlib import Path
from tqdm import tqdm
from features.features_extractor import extract_features
from model.model import load_model

project_root = Path(__file__).resolve().parents[1]

config = yaml.safe_load(open(project_root / "config.yaml", "r"))
features = config["features"]

# label map: effect same as train.csv (1 -> bubble_sort, 2 -> selection_sort, 3 -> merge_sort, 4 -> quick_sort)
model_path = project_root / config["save_path"]
label_map_path = model_path.parent / "label_mapping.json"

model = load_model(model_path)

with open(label_map_path) as f:
    label_mapping = json.load(f)

def map_labels(labels):
    return [label_mapping[str(l).strip().lower()] for l in labels] # (1 -> bubble_sort, 2 -> selection_sort, 3 -> merge_sort, 4 -> quick_sort)

test_df = pd.read_csv(project_root / config["data"]["test_path"], header=None)
arrays = test_df[0].apply(lambda x: list(map(int, x.split())))

answer_asc = map_labels(
    pd.read_csv(project_root / config["data"]["test_answer_ascending_path"], header=None)[0] # name of answer column is empty
)
answer_desc = map_labels(
    pd.read_csv(project_root / config["data"]["test_answer_descending_path"], header=None)[0]
)

def extract_feature_df(arrays, direction):
    rows = []
    for arr in tqdm(arrays, desc=f"Extracting features (direction={direction})"):
        feats = extract_features(arr, direction)
        rows.append([feats[f] for f in features]) # keep order of features same as train.csv
    return pd.DataFrame(rows, columns=features)

# calc features
X_asc = extract_feature_df(arrays, +1)
X_desc = extract_feature_df(arrays, -1)

pred_asc = model.predict(X_asc)
pred_desc = model.predict(X_desc)

print(f"Accuracy for ascending: {(pred_asc == answer_asc).mean():.4f}")
print(f"Accuracy for descending: {(pred_desc == answer_desc).mean():.4f}")
