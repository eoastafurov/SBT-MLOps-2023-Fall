```bash
# Build
docker build -t my_iris_environment .

# Run script using docker as environment
docker run --rm -v $(pwd):/usr/src/app my_iris_environment python run.py
```
