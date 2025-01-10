# Папки и файлы

1. Папка `driver_proxy` прокси драйвер для пересылки сообщений между открытым и закрыты интернетом.
2. Папка `driver_rs232_port` драйвер связи между устройствами на основе RS-232 протокола и сервером на основе REST-API.
3. Папка `driver_lan_port` драйвер связи между устройствами на основе Lan (TCP) протокола и сервером на основе REST-API.
4. Папка `emulators` эмуляторы работы некоторых устройств.


### ВНИМАНИЕ !!!
### Описание устарело!


# Прокси драйвер

Flask-приложение, запускаемое на удаленном сервере. Оформлено в Docker контейнер.


# Драйвер rs232_port и lan_port

Flask-приложение, запускаемое на удаленном сервере для обработки данных, присланных с драйверов анализаторов и отправки
их на сервер ЛИС.

Для запуска приложения, необходим файл `.env`.
В нем прописываются следующие данные:

```
DEBUG = True - "True", если необходима отладка - данные СОМ порта будут браться из этого файлв - строчка ниже
SERIAL_DEBUG = {'d4p1:ConnectionType': 'COM', 'd4p1:COMPortNumber': '6', 'd4p1:COMParity': 'None',  'd4p1:COMDataBits': '8', 'd4p1:COMSpeed': 9600, 'd4p1:COMStopBits': '1', 'd4p1:DeviceName': 'Architect I2000SR'}
LIS_URL = http://192.168.1.90/new_lis/ws/DeviceExchange.1cws - адрес сервера ЛИС
HOST = - если необходимо вручную прописать ХОСТ для запуска драйвера. По умолчанию - автоматически пропишется текущий адрес системы
PORT = - если необходимо вручную прописать номер ПОРТа для запуска драйвера. По умолчанию - автоматически пропишется ПОРТ:5000
AUTH = ('Device', '123') - логин и пароль для подключения к серверу ЛИС
# ниже - шаблон для преобразования кирилицы в латиницу
LEGEND = {'а': 'a', 'б': 'b', 'в': 'v', 'г': 'g', 'д': 'd', 'е': 'e', 'ё': 'yo', 'ж': 'zh', 'з': 'z', 'и': 'i', 'й': 'y', 'к': 'k', 'л': 'l', 'м': 'm', 'н': 'n', 'о': 'o', 'п': 'p', 'р': 'r', 'с': 's', 'т': 't', 'у': 'u', 'ф': 'f', 'х': 'h', 'ц': 'ts', 'ч': 'ch', 'ш': 'sh', 'щ': 'shch', 'ъ': 'y', 'ы': 'y', 'ь': "'", 'э': 'e', 'ю': 'yu', 'я': 'ya', 'А': 'A', 'Б': 'B', 'В': 'V', 'Г': 'G', 'Д': 'D', 'Е': 'E', 'Ё': 'Yo', 'Ж': 'Zh', 'З': 'Z', 'И': 'I', 'Й': 'Y', 'К': 'K', 'Л': 'L', 'М': 'M', 'Н': 'N', 'О': 'O', 'П': 'P', 'Р': 'R', 'С': 'S', 'Т': 'T', 'У': 'U', 'Ф': 'F', 'Х': 'H', 'Ц': 'Ts', 'Ч': 'Ch', 'Ш': 'Sh', 'Щ': 'Shch', 'Ъ': 'Y', 'Ы': 'Y', 'Ь': "'", 'Э': 'E', 'Ю': 'Yu', 'Я': 'Ya'}
```

В случае, если данные СОМ порта от ЛИС получить не удалось, драйвер попробует получить их из файла `config.json`, если он существует и/или там есть параметры СОМ порта для данного анализатора.


Для получения данных СОМ порта от ЛИС, драйвер анализатора должен отправить POST запрос по адресу, подобному следующему:
`http://192.168.1.15/:5000/com_port`. В запросе должны быть следующие данные.

``` json
{
    "analyzer_number": номер анализатора (str)
}
```

Для отправки данных анализатора и передачи их в ЛИС, драйвер анализатора должен отправить POST запрос по адресу,
подобному следующему:
`http://192.168.1.15/:5000/` 
![interface_01.JPG](interface_01.JPG)

В запросе должны быть следующие данные.

``` json
{
    "data": предобработанные данные анализатора (list),
    "analyzer": название анализатора (str),
    "device_id": номер анализатора (str),
    "raw_line": необработанные данные анализатора (str)
}
```

Для прочтения логов через Веб-браузер, в строке адреса, следует ввести подобный адрес:
`http://192.168.1.15/:5000/read_logs`
![interface_03.JPG](interface_03.JPG)

Для очистки лог-файла через Веб-браузер, в строке адреса, следует ввести подобный адрес:
`http://192.168.1.15/:5000/clear_logs`

Для просмотра файла БД через Веб-браузер, в строке адреса, следует ввести подобный адрес:
`http://192.168.1.15/:5000/read_bd`
![interface_02.JPG](interface_02.JPG)

Для просмотра только одной записи в файле БД через Веб-браузер, в строке адреса, следует ввести подобный адрес, с указанием id записи:
`http://192.168.1.15/:5000/read_db?id=1`

Для очистки файла БД через Веб-браузер, в строке адреса, следует ввести подобный адрес:
`http://192.168.1.15/:5000/clear_db`

Для удаления только одной записи в файле БД через Веб-браузер, в строке адреса, следует ввести подобный адрес, с указанием id записи:
`http://192.168.1.15/:5000/clear_db?id=1`


