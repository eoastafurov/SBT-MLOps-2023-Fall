from tritonclient.http import InferenceServerClient, InferInput, InferRequestedOutput
import tritonclient.utils as trutils
from functools import lru_cache
import numpy as np
from transformers import AutoTokenizer
import torch


@lru_cache
def get_client():
    return InferenceServerClient(url="0.0.0.0:8500")


def call_tirton_ensemble_onnx(text: str) -> np.ndarray:
    triton_client = get_client()
    text = np.array([text.encode("utf-8")], dtype=object)

    input_text = InferInput(
        name="TEXTS", shape=text.shape, datatype=trutils.np_to_triton_dtype(text.dtype)
    )
    input_text.set_data_from_numpy(text, binary_data=True)

    infer_response = triton_client.infer(
        "ensemble-onnx",
        [input_text],
        outputs=[InferRequestedOutput("EMBEDDINGS", binary_data=True)],
    )
    embeddings = infer_response.as_numpy("EMBEDDINGS")[0]
    return embeddings


def call_triton_tokenizer(text: str) -> np.ndarray:
    triton_client = get_client()
    text = np.array([text.encode("utf-8")], dtype=object)

    input_text = InferInput(
        name="TEXTS", shape=text.shape, datatype=trutils.np_to_triton_dtype(text.dtype)
    )
    input_text.set_data_from_numpy(text, binary_data=True)

    infer_response = triton_client.infer(
        "python-tokenizer",
        [input_text],
        outputs=[
            InferRequestedOutput("INPUT_IDS", binary_data=True),
            InferRequestedOutput("ATTENTION_MASK", binary_data=True),
        ],
    )
    input_ids = infer_response.as_numpy("INPUT_IDS")[0]
    attention_mask = infer_response.as_numpy("ATTENTION_MASK")[0]
    return input_ids, attention_mask


def main():
    texts = [
        "Сегодня солнечный день",
        "Сегодня пасмурный день",
        "Датасаенс -- это не эмэль",
        "Стальная ложка",
    ]

    tokenizer = AutoTokenizer.from_pretrained("ai-forever/ruBert-base")
    encoded = tokenizer(
        texts[0],
        padding="max_length",
        max_length=16,
        truncation=True,
    )
    input_ids, attention_mask = encoded["input_ids"], encoded["attention_mask"]
    _input_ids, _attention_mask = call_triton_tokenizer(texts[0])
    assert (input_ids == _input_ids).all() and (attention_mask == _attention_mask).all()

    embeddings = torch.tensor(
        [call_tirton_ensemble_onnx(row).tolist() for row in texts]
    )
    distances = torch.cdist(embeddings, embeddings, p=2)

    print(distances)


if __name__ == "__main__":
    main()
