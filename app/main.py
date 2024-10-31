
from fastapi import FastAPI
import quantization
from pydantic import BaseModel
from typing import List
import json

app = FastAPI()

class Vector(BaseModel):
    vector: List[float]


@app.get("/")
async def root():
    return {"message": "Quantization"}

@app.post("/quantization")
async def kd(data: Vector, niveles: int):
    # Cuantizar los datos
    quantized_data = quantization.quantize(data.vector, niveles)

    result = {
        "Datos originales": data.vector,
        "Datos cuantizados": quantized_data
    }
    return json.dumps(result)