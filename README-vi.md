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
- Constants : Định nghĩa hằng số cho trò chơi.


# Thành phần của trò chơi
- Main Menu.


# Xây dựng và cài đặt
1. Cài đặt [CMake](https://github.com/Kitware/CMake/releases/download/v4.0.0-rc2/cmake-4.0.0-rc2-windows-x86_64.msi) (Chọn "Add CMake to the PATH environment variable", nếu ô đã được chọn thì để nguyên).
Cài đặt [Ninja](https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-win.zip) và thêm nó vào biến môi trường.
> [!NOTE]
> Có thể bỏ qua bước này nếu bạn đã có CMake và Ninja được cài đặt và thêm vào biến môi trường.
2. Clone repository. 
```
git clone https://github.com/sonarxyy/ShapeDominance.git
```
3. Xây dựng.
Trước hết cần đảm bảo trình biên dịch C/C++ được thêm vào biến môi trường.
Trong thư mục vừa clone, gõ:
```
mkdir build
cd build
cmake -G "Ninja" ..
ninja
```
4. Khởi động trò chơi.
5. Chúc bạn chơi game vui vẻ.


# Tham khảo
[Lazy Foo](https://lazyfoo.net/tutorials/SDL/)

[Let's Make Games](https://www.youtube.com/playlist?list=PLhfAbcv9cehhkG7ZQK0nfIGJC_C-wSLrx)

[Game Programming Pattern](https://gameprogrammingpatterns.com/contents.html)

[CMake Tutorial](https://cmake.org/cmake/help/latest/guide/tutorial/index.html)


# Nguồn
| Author |          Thành phần trò chơi        |                                                                 Patreon                                                                |                                                             Itch.io                                                             |
|:------:|:-----------------------:|:--------------------------------------------------------------------------------------------------------------------------------------:|:-------------------------------------------------------------------------------------------------------------------------------:|
|  Kenny | Giao diện chính, Âm thanh, Đồ họa | [![Static Badge](https://img.shields.io/badge/Patreon-white?style=flat&logo=patreon&labelColor=black)](https://www.patreon.com/kenney) | [![Static Badge](https://img.shields.io/badge/Itch.io-white?style=flat&logo=itch.io&labelColor=black)](https://kenney.itch.io/) |
| Lynocs |        Hình nền       |                                                                   N/A                                                                  | [![Static Badge](https://img.shields.io/badge/Itch.io-white?style=flat&logo=itch.io&labelColor=black)](https://lynocs.itch.io/) |