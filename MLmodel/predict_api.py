import sys
import json
import yaml
import pandas as pd
from pathlib import Path
from model.model import load_model
from features.features_extractor import extract_features

def main():
    if len(sys.argv) != 3: # argv check
        print("Usage: python predict_api.py '[1,2,3]' 1", file=sys.stderr)
        sys.exit(1)

    try: # analyze input params: array, sort_direction
        arr = json.loads(sys.argv[1])
        sort_direction = int(sys.argv[2])
        if sort_direction not in (+1, -1):
            raise ValueError
    except Exception:
        print("Invalid arguments", file=sys.stderr)
        sys.exit(2)

    project_root = Path(__file__).resolve().parent
    config = yaml.safe_load(open(project_root / "config.yaml", "r"))

    features = config["features"]
    model_path = project_root / config["save_path"]
    label_map_path = model_path.parent / "label_mapping.json"

    model = load_model(model_path)

    with open(label_map_path, "r") as f:
        label_mapping = json.load(f)

    inverse_label_mapping = {v: k for k, v in label_mapping.items()}

    feats = extract_features(arr, sort_direction)
    X = pd.DataFrame([[feats[f] for f in features]], columns=features) # keep order of features same as train.csv

    pred_id = int(model.predict(X)[0])
    pred_label = inverse_label_mapping[pred_id]

    print(pred_label) # (1 -> bubble_sort, 2 -> selection_sort, 3 -> merge_sort, 4 -> quick_sort)

if __name__ == "__main__":
    main()
