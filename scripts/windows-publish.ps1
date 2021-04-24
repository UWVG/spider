function Main() {
    New-Item -ItemType Directory "spider"
    Copy-Item *.dll spider\
    Copy-Item *.lib spider\
    Copy-Item  C:\hostedtoolcache\windows\Python\3.8.5\x64\python38.dll spider\
    Copy-Item  inc\spider.h spider\
    Compress-Archive -Path spider\* 'spider.zip'
}
Main

