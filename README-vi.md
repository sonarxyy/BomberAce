[![Static Badge](https://img.shields.io/badge/Language-English-orange)](https://github.com/sonarxyy/ShapeDominance/blob/main/README.md)


# Bomber Ace
Một dự án trò chơi nhỏ được viết bằng C++ dựa trên thư viện [SDL2](https://wiki.libsdl.org/SDL2/FrontPage).


# Các lớp quản lý chính của trò chơi
- Audio Manager: Quản lí âm thanh của trò chơi.
  - Tái sử dụng nhạc nền, hiệu ứng âm thanh.
  - Nạp vào nhạc nền, hiệu ứng âm thanh.
  - Phát nhạc nền, hiệu ứng âm thanh.
  - Dừng hẳn nhạc nền.
  - Dừng nhạc nền, hiệu ứng âm thanh.
  - Tùy chỉnh âm lượng cho nhạc nền, hiệu ứng âm thanh.
- Constants: Định nghĩa hằng số cho trò chơi.
- Engine: Quản lý những chức năng chính của trò chơi.
  - Khởi tạo từng chức năng của trò chơi.
  - Quản lý các sự kiện.
  - Cập nhật.
  - Kết xuất.
  - Dọn dẹp.
- Game Object: Quản lý các đối tượng của trò chơi.
  - Cập nhật đối tượng.
  - Kết xuất đối tượng.
- Game State Manager: Quản lý trạng thái của trò chơi.
  - Thiết đặt trạng thái hiện tại cho trò chơi.
  - Lấy trạng thái hiện tại của trò chơi.
- Level Manager: Quản lý nạp vào màn chơi.
  - Nạp màn chơi từ tập tin chữ.
- Text Manager: Quản lý kết xuất chữ.
  - Tái sử dụng phông chữ.
  - Tạo đồ họa từ chữ.
  - Bỏ nạp phông chữ.
  - Bỏ nạp đồ họa tạo từ phông chữ.
- Texture Manager: Quản lý đồ họa của trò chơi.
  - Tái sử dụng đồ họa (nếu đồ họa đã được nạp).
  - Nạp vào đồ họa.
  - Bỏ nạp đồ họa.
- Tile Manager: Quản lý bản đồ ô của trò chơi.
  - Nạp vào đồ họa của từng kiểu ô.
  - Kết xuất bản đồ ô.
  - Kiểm tra va chạm với bất cứ vật thể nào (người chơi, kẻ địch, vụ nổ).
  - Kiểm tra một ô chỉ định là tường.
  - Phá hủy những ô có thể phá.
  - Lấy kiểu ô ở vị trí chỉ định.


# Lớp không thể thiếu của trò chơi.
- Bomb: Kaboom!
  - Nạp vào đồ họa của bom.
  - Cập nhật trạng thái của bom.
  - Kết xuất đồ họa của bom.
  - Lấy bán kính nổ của bom.
- Enemy: Mèo.
  - Cập nhật trạng thái kẻ địch.
  - Đặt bom ở vị trí bất kì (ưu tiên gần tường phá được).
  - Cố gắng thoát khỏi vụ nổ.
  - Kết xuất đồ họa của kẻ địch.
- Explosion: Kẻ đột phá.
  - Nạp vào đồ họa của vụ nổ.
  - Cập nhật trạng thái vụ nổ (trước khi nổ, sau khi nổ).
  - Kết xuất vụ nổ.
- Fade transition: Cho trải nghiệm mượt mà hơn.
  - Hiệu ứng chuyển cảnh fade in, fade out cho trò chơi.
- HUD: Head-up display
  - Cập nhật và hiển thị những thông tin cơ bản về trạng thái của người chơi.
- In Game: Khi đang chơi
  - Quản lý dữ liệu nhập từ người chơi.
  - Cập nhật thông tin của trò chơi.
  - Hiển thị những thay đổi cho trò chơi.
- Main menu: Một nồi những lựa chọn.
  - Tạo một bảng lựa chọn.
  - Quản lý dữ liệu nhập từ người chơi.
  - Cập nhật những thay đổi dựa vào dữ liệu nhập vào (Chuột, bàn phím, con lăn).
  - Hiển thị những thay đổi ra màn hình.
- Options menu: Là main menu nhưng ở diễn biến khác.
- Player: Một con mèo.
  - Quản lý dữ liệu nhập vào từ người chơi.
  - Cập nhật hoạt họa (đứng im, di chuyển, hướng của nhân vật).
  - Kết xuất hoạt họa.
  - Lấy vị trí của người chơi.
  - Đặt bom ở nơi được chỉ định.
  - Có thể mất máu.
  - Trò chơi kết thúc khi máu giảm về 0.
- Power-ups:


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
|                              Tác giả                              |             Tài sản            |
|:-----------------------------------------------------------------:|:------------------------------:|
|  [Gemini Imagen3](https://deepmind.google/technologies/imagen-3/) |            Main menu           |
|                   [bigjpg](https://bigjpg.com/)                   |        Phóng tỏ hình ảnh       |
|           [Netherzapdos](https://netherzapdos.itch.io/)           | Đồ họa của người chơi, kẻ địch |
|                 [Kenney](https://kenney.nl/assets)                |        Hiệu ứng âm thanh       |
|      [Caz Creates Games](https://caz-creates-games.itch.io/)      |         Đồ họa của bom         |
|            [JAR Incorporated](https://jarinc.itch.io/)            |         Đồ họa trái tim        |
|               [CodeManu](https://codemanu.itch.io/)               |       Hiệu ứng nổ của bom      |
| [Raymond Larabie](https://www.dafont.com/profile.php?user=137418) |         Phông chữ Xirod        |