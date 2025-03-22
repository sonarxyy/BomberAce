[![Static Badge](https://img.shields.io/badge/Language-English-orange)](https://github.com/sonarxyy/ShapeDominance/blob/main/README.md)


# Shape Dominance
Một dự án trò chơi nhỏ được viết bằng C++ dựa trên thư viện [SDL2](https://wiki.libsdl.org/SDL2/FrontPage).


# Các lớp quản lý chính của trò chơi
- Engine: Quản lý những chức năng chính của trò chơi.
  - Khởi tạo từng chức năng của trò chơi.
  - Quản lý các sự kiện.
  - Cập nhật.
  - Kết xuất.
  - Dọn dẹp.
- Game Object: Quản lý các đối tượng của trò chơi.
  - Cập nhật đối tượng.
  - Kết xuất đối tượng.
- Text Manager: Quản lý kết xuất chữ.
  - Tái sử dụng phông chữ.
  - Tạo đồ họa từ chữ.
  - Bỏ nạp phông chữ.
  - Bỏ nạp đồ họa tạo từ phông chữ.
- Texture Manager: Quản lý đồ họa của trò chơi.
  - Tái sử dụng đồ họa (nếu đồ họa đã được nạp).
  - Nạp vào đồ họa.
  - Bỏ nạp đồ họa.
- Audio Manager: Quản lí âm thanh của trò chơi.
  - Tái sử dụng nhạc nền, hiệu ứng âm thanh.
  - Nạp vào nhạc nền, hiệu ứng âm thanh.
  - Phát nhạc nền, hiệu ứng âm thanh.
  - Dừng hẳn nhạc nền.
  - Dừng nhạc nền, hiệu ứng âm thanh.
  - Tùy chỉnh âm lượng cho nhạc nền, hiệu ứng âm thanh.
- Game State Manager: Quản lý trạng thái của trò chơi.
  - Thiết đặt trạng thái hiện tại cho trò chơi.
  - Lấy trạng thái hiện tại của trò chơi.
- Constants: Định nghĩa hằng số cho trò chơi.
- Tile Manager: Quản lý bản đồ ô của trò chơi.
  - Nạp vào đồ họa của từng kiểu ô.
  - Kết xuất bản đồ ô.
  - Kiểm tra va chạm với bất cứ vật thể nào (người chơi, kẻ địch, vụ nổ).
  - Check if designated position is a wall.
  - Phá hủy những ô có thể phá.
  - Lấy kiểu ô ở vị trí chỉ định.
- Level Manager: Quản lý nạp vào màn chơi.
  - Nạp màn chơi từ tập tin chữ.


- Lớp không thể thiếu của trò chơi.


# Xây dựng và cài đặt
1. Clone repository của tôi.
```
git clone https://github.com/sonarxyy/ShapeDominance.git
```
2. Cài đặt và xây dựng.
> [!IMPORTANT]
> Đầu tiên, đảm bảo rằng trình biên dịch C/C++ được thêm vào biến môi trường.

> [!NOTE]
> Từ lần sau, chỉ cần chạy build.bat để xây dựng trò chơi.

Trong thư mục vừa clone, chạy install.bat. Sau khi cài đặt xong, chạy build.bat.  
3. Khởi động trò chơi.  
4. Chúc bạn chơi trò chơi vui vẻ.


# Tham khảo
[Lazy Foo](https://lazyfoo.net/tutorials/SDL/)

[Let's Make Games](https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx)

[Game Programming Pattern](https://gameprogrammingpatterns.com/contents.html)

[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)


# Nguồn
|                              Tác giả                              |             Tài sản             |
|:-----------------------------------------------------------------:|:-------------------------------:|
|  [Gemini Imagen3](https://deepmind.google/technologies/imagen-3/) |            Main Menu            |
|                   [bigjpg](https://bigjpg.com/)                   |          Upscale Image          |
|           [Netherzapdos](https://netherzapdos.itch.io/)           | Player's sprite, enemy's sprite |
|                 [Kenney](https://kenney.nl/assets)                |               SFX               |
|      [Caz Creates Games](https://caz-creates-games.itch.io/)      |         Bomb's textures         |
|            [JAR Incorporated](https://jarinc.itch.io/)            |         Heart's textures        |
|               [CodeManu](https://codemanu.itch.io/)               |       Explosion's textures      |
| [Raymond Larabie](https://www.dafont.com/profile.php?user=137418) |           Xirod's font          |