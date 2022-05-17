# Báo cáo dự án cuối khóa
Họ và tên: Trần Tuấn Việt <br />
MSV: 21020421, lớp học phần INT2215 1. <br />
## Dự án lập trình
**Tên trò chơi: Tetris** (Game xếp hình cổ điển) <br />
1. Về cách cài đặt, hướng dẫn để có thể chạy chương trình <br />
2. Mô tả về trò chơi và các ý tưởng chính <br />
2.1. Mô tả <br />
Tetris là trò chơi xếp hình cổ điển được ra đời vào cuối thế kỷ 20 ở Nga. Ngày nay Tetris được xem như là một trong những trò chơi kinh điển và thịnh hành nhất trên thế giới. <br />
2.2. Ý tưởng chính hình thành trò chơi <br/>
Trò chơi có bảy loại khối hình: I (thẳng đứng), J, L, O (vuông), S, T, Z. Ta thấy mỗi khối gạch được cấu tạo từ 4 hình vuông nhỏ xếp lại với nhau. Ta có thể coi các khối gạch đó như là những hình chữ nhật có kích thước khác nhau.<br/>
Các hình khác được tạo ra khi xoay các khối cơ bản này các góc tương ứng 90 độ, 180 độ, 270 độ.<br/>
Một chuỗi ngẫu nhiên của Tetriminos rơi xuống sân chơi (một trục đứng hình chữ nhật, được gọi là "tốt" hay "ma trận").<br/>
Mục đích của người chơi là làm đầy các thanh Tetriminos trên một hàng ngang nhiều nhất có thể để ghi điểm, sao cho không thể làm được nữa thì trò chơi sẽ kết thúc. <br/>
3. Về các chức năng đã cài đặt<br/>
Cùng với ý tưởng chính đã được triển khai ở trên, để làm được trò chơi, ta cần phải thực hiện các công việc sau:<br/>
    * Tạo ra màn hình chơi, bao gồm số hàng và số cột.<br/>
    * Tạo ra các khối Tetriminos.<br/>
    * Thực hiện việc di chuyển, xoay các thanh Tetrimino, và thời gian để thanh Tetrimino rơi xuống.<br/>
    * Hiển thị trò chơi qua đồ họa<br/>
Ngoài các chức năng chính của trò chơi, để nâng cao trải nghiệm của người chơi, cần có các chức năng bổ sung:<br/>
    * Hiển thị thanh Tetrimino kế tiếp<br/>
    * Có thể giữ lấy thanh Tetrimino và thay thế bằng thanh được giấu (nếu có) <br/>
    * Hiển thị điểm của người chơi, và độ khó tỉ lệ thuận với số điểm. <br/>
    * Có thể đặt ngay lập tức thanh Tetrimino xuống tại vị trí có thể để nhanh hơn so với bình thường.<br/>
    * Hiển thị thanh Tetrimino dự đoán trước vị trí có thể của thanh Tetrimino khi rơi xuống.<br/>
    * Có thể tạm dừng nếu như người chơi muốn được tạm nghỉ. <br/>
    * Âm nhạc nhằm tăng cảm giác của người chơi. <br/> 
4. Về các kỹ thuật đã được sử dụng.<br/>
  a. Tạo ra màn hình chơi, bao gồm số hàng và số cột.<br/>
  Để tạo ra màn hình chơi cơ bản thì ta khai báo một mảng 2 chiều kiểu int `int field[Lines][Cols]`, trong đó `Lines` và `Cols` là kiểu giá trị cố định `enum`. Ở đây `Lines = 20, Cols = 10` <br/>
  Mục đích của kiểu `int` thay vì kiểu `bool` là để hiển thị màu cho đồ họa. Nếu như người chơi muốn màu của các thanh Tetriminos sau khi rơi là một màu đồng nhất thì có thể để mảng kiểu `bool` hoặc cho các giá trị cố định ở `field`. Vì trên các trò chơi ngày nay người ta để các màu của các thanh Tetriminos sau khi rơi vẫn như cũ nên ta sẽ theo đó làm chuẩn.<br/>
  b. Tạo ra các khối Tetriminos.<br/>
  Để tạo ra các khối Tetriminos, ta có thể tạo ra từ một mảng 2 chiều (4x4), hoặc 1 chiều (16). Ở đây ta thể hiện các dạng khối qua một cấu trúc `Struct Point()` bao gồm các biến thành viên là:<br/>
          `int x, y, color, figure`<br/>
Trong đó, `x, y` là các tọa độ của các điểm, `color` là kiểu màu sắc đặc trưng cho từng thanh, `figure` là kiểu hình của thanh Tetrimino.<br/>
Ngoài ra ta cần một mảng hằng `const int figures[7][4]` để tạo ra kiểu hình cho các thanh Tetrimino.<br/>
Để tưởng tượng, giả sử ta có 8 vị trí như sau:<br/>
0 1 2 3<br/>
4 5 6 7<br/>
Nếu ta cho figure nhận các giá trị khác 0 ở các vị trí, ví dụ như 0,1,5,6, ta sẽ thu được thanh Tetrimino chữ Z.<br/>
Chúng ta sẽ dựa trên cách đặt này để thể hiện các thanh Tetrimino. Bằng cách tạo ra các mảng 1 chiều kiểu Point, chúng ta có thể thể hiện vị trí của các thanh Tetrimino khởi tạo<br/>
  c.Thực hiện việc di chuyển, xoay các thanh Tetrimino, và thời gian để thanh Tetrimino rơi xuống.<br/>
  Để thực hiện việc di chuyển một cách liên tục, ta cần phải tạo một hàm thực hiện việc bắt sự kiện từ bàn phím `void handleEvents()` dựa trên kiểu biến nhận sự kiện 
 `SDL_Event e`.<br/>
 Theo đó, nếu như bấm RIGHT, các điểm được hiển thị (thanh Tetrimino) sẽ di chuyển sang phải 1 đơn vị, và sang trái 1 đơn vị nếu như bấm LEFT. Nếu như bấm UP, các điểm được hiển thị sẽ thực hiện việc đổi vị trí theo quy luật (thanh Tetrimino sẽ xoay). Cần phải có các điều kiện ràng buộc kiểm tra xem bước đi đó là có thể hay không.<br/>
 d.Hiển thị đồ họa<br/>
 Để thực hiện công việc trên, cần phải làm việc với các thư viện đồ họa. Ngoài các khởi tạo màn hình, bút vẽ, cần phải xây dựng các khối chữ nhật được lấy màu từ ảnh cho trước để hiển thị màu cho các thanh Tetriminos. Để làm được điều đó, để biến thành viên `color` ở cấu trúc `Point` và kiểu mảng 2 chiều `int field[Lines][Cols]` là cần thiết.

