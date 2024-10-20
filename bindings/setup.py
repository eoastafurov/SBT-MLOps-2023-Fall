from setuptools import setup, find_packages
from glob import glob

so_files = glob("linalg/python/linalg_core*.so")

setup(
    name="linalg",
    version="0.1",
    description="Linear algebra utilities with Python bindings",
    packages=find_packages(),
    package_data={
        "linalg": ["python/*.so"],
    },
)
