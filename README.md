# HOKS
HOKS – мессенджер с открытым исходным кодом. \
В HOKS вы можете отправлять друг другу сообщения и делиться файлами.

## Сборка и запуск

### Linux
1. Устанавливаем QT с официального сайта.


2. Находясь в директории `Client`, собираем проект: \
`qmake Client.pro` \
`make`


3. Находясь в директории `Client`, создаём папку `downloadFiles`.


4. Находясь в директории `Client`, выполняем команду: \
`chmod +x checkFileExistence.sh openFile.sh`


5. Находясь в директории `Client`, запускаем клиент HOKS: \
`./Client`

### macOS
1. Устанавливаем QT с официального сайта.


2. Выполняем команду: \
`brew install qt`


3. Находясь в директории `Client`, собираем проект: \
`qmake Client.pro` \
`make`


4. Находясь в директории `Client`, создаём папку `downloadFiles`.


5. Находясь в директории `Client`, выполняем команду: \
`chmod +x checkFileExistence.sh openFile.sh`


6. Находясь в директории `Client`, запускаем клиент HOKS: \
`./Client`