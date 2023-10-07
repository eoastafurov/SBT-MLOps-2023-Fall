# MinIO

```bash
docker-compose up -d
```

1. Поднимаем контейнер: `docker-compose up` (или `up -d` для detached режима)
1. Пробрасываем порты `9091` и `9000`
1. Логинимся в http://localhost:9091/
1. Заводим бакет, конфиругируем свойства

Для работы через различных клиентов
- `MINIO_ROOT_USER` = `access_key`
- `MINIO_ROOT_PASSWORD` = `secret_key`
