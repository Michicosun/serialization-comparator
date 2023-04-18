# Serialization format comparator

Данный проект позволяет сранивать различные форматы сериализации данных.

## Архитектура

Для тестирования каждого формата поднимается отдельный контейнер, который прослушивает определенный UDP порт для обработки запросов на вычисление результата.

Координирует запросы специальный контейнер Proxy, который определяет нужный контейнер с необходимым типом сериализации и перенаправляет запрос туда, также он поддерживает multicast рассылку.

## Run containers

Все образы залиты в docker-hub, поэтому для запуска достаточно запустить docker-compose

```bash
path/serialization-comparator$ docker-compose up
```

## Build images

Для начала нужно создать базовый образ, в котором соберется CMake проект и нужные бинари.

```bash
path/serialization-comparator$ docker build . -f Dockerfile -t soa-project-1-base
```

После этого образ soa-project-1-base, собранный на прошлом этапе будет переиспользоваться в worker/proxy образах, это сделано, чтобы ускорить сборку.

Создание worker image, в аргументах указывается прослушиваемый порт и метод сериализации

```bash
path/serialization-comparator$ docker build . -f worker/Dockerfile -t soa-project-1-worker-xml --build-arg PORT=2025 --build-arg METHOD=xml
```

Создание proxy image, в аргументах указывается прослушиваемый порт и порт, на котором слушают воркеры

```bash
path/serialization-comparator$ docker build . -f proxy/Dockerfile -t soa-project-1-proxy --build-arg PROXY_PORT=2000 --build-arg WORKER_PORT=2025
```

## Формат запросов

Единственный доступный порт извне является 2000 UDP порт, который прослушивает proxy. Всего есть 2 типа запросов, с форматом, похожим на JSON-RPC:

- Запрос результата по конкретному типу сериализации:
    ```json
    {"method": "get_result", "params": ["json"]}
    ```

- Запрос результатов со всех worker контейнеров:
    ```json
    {"method": "get_result_all", "params": []}
    ```
    В данном случае запрос будет отправлен на адрес multicast группы, задаваемой в environment переменных контейнеров

## Формат ответа

Ответы предоставляются в формате {format} – {size} – {serialization time} – {deserialization time}, время отдается в наносекундах, а размер в байтах.

Пример запроса и ответа через netcat:

```bash
~/serialization-comparator$ cat | nc -uq0 127.0.0.1 2000

{"method": "get_result", "params": ["json"]}
json - 122b - 1884ns - 775ns

{"method": "get_result_all", "params": []}
json - 122b - 1897ns - 765ns
native - 128b - 331ns - 348ns
avro - 46b - 578ns - 653ns
protobuf - 54b - 518ns - 679ns
msgpack - 45b - 942ns - 718ns
xml - 634b - 12838ns - 24178ns
yaml - 143b - 29850ns - 7535ns
```
