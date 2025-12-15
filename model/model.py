import pickle
from pathlib import Path

def save_model(model, path):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True) # automatically create if not exists parent dir
    with open(path, "wb") as f: # write binary
        pickle.dump(model, f)

def load_model(path):
    with open(path, "rb") as f: # read binary
        return pickle.load(f)
