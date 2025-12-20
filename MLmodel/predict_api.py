import sys
import json
import yaml
import pandas as pd
from pathlib import Path
from model.model import load_model
from features.features_extractor import extract_features


def load_array_from_arg(arg: str):
    """
    if argv is array type string -> directly analysis
    if argv is file path -> read file then analysis
    """
    # condition 1: array type string
    if arg.strip().startswith("["):
        try:
            return json.loads(arg)
        except Exception:
            print("Invalid array format")
            sys.exit(2)

    # condition 2: file path
    path = Path(arg)
    if not path.exists():
        print(f"File not found: {arg}")
        sys.exit(3)

    try:
        with open(path, "r") as f:
            content = f.read().strip()
            return json.loads(content)
    except Exception:
        print("Failed to read array from file")
        sys.exit(4)


def main():
    if len(sys.argv) != 3:
        print(
            "Usage:\n"
            "  python predict_api.py \"[1,2,3]\" 1\n"
            "  python predict_api.py dataset/train.csv -1"
        )
        sys.exit(1)

    input_arg = sys.argv[1]
    sort_direction_arg = sys.argv[2]

    # analysis sort_direction
    try:
        sort_direction = int(sort_direction_arg)
        if sort_direction not in (1, -1):
            raise ValueError
    except ValueError:
        print("sort_direction must be 1 or -1")
        sys.exit(5)

    arr = load_array_from_arg(input_arg)
    project_root = Path(__file__).resolve().parent

    with open(project_root / "config.yaml", "r") as f: # read config
        config = yaml.safe_load(f)

    features = config["features"]
    model_path = project_root / config["save_path"]
    label_map_path = model_path.parent / "label_mapping.json"

    model = load_model(model_path)
    with open(label_map_path, "r") as f: # load label_mapping.json
        label_mapping = json.load(f)
    inverse_label_mapping = {v: k for k, v in label_mapping.items()}

    feats = extract_features(arr, sort_direction)
    X = pd.DataFrame([[feats[f] for f in features]], columns=features)

    pred_id = int(model.predict(X)[0])
    pred_label = inverse_label_mapping[pred_id]

    print(pred_label)


if __name__ == "__main__":
    main()
