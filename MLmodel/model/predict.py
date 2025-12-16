import yaml
import pandas as pd
from model.model import load_model
from features.features_extractor import extract_features
import ast
import sys

config = yaml.safe_load(open("config.yaml", "r"))
features = config["features"]
save_path = config["save_path"]

_model = load_model(save_path) # load model

# +1 means ascending; -1 means descending
def predict_best_algorithm(arr, sort_direction=+1):
    feats = extract_features(arr, direction=sort_direction)
    X = pd.DataFrame([[feats[f] for f in features]], columns=features)
    pred = _model.predict(X)[0]
    return pred

if __name__ == "__main__":
    if len(sys.argv) >= 2:
        arr_raw = sys.argv[1]
        try:
            arr = ast.literal_eval(arr_raw)
            if not isinstance(arr, (list, tuple)):
                raise ValueError
        except Exception:
            print("First arg should be a python list literal, e.g. \"[5,3,1,4]\"")
            sys.exit(1)

        # default sort_direction
        direction = +1

        # sort_direction argv
        if len(sys.argv) >= 3:
            direction = int(sys.argv[2])
            if direction not in (+1, -1):
                print("Direction must be +1 or -1. Using +1")
                direction = +1
        print("Predict for array: ", arr, " direction: ", direction)
        print("Prediction: ", predict_best_algorithm(arr, sort_direction=direction))
    else:
        demo = [5,3,1,4,2] # demo test for unit testing
        print("Demo predict for ", demo, " asc -> ", predict_best_algorithm(demo, +1))
        print("Demo predict for ", demo, " desc -> ", predict_best_algorithm(demo, -1))