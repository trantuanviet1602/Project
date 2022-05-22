# Báo cáo dự án cuối khóa
Họ và tên: Trần Tuấn Việt <br />
MSV: 21020421, lớp học phần INT2215 1. <br />
## Dự án lập trình
**Tên trò chơi: Tetris** (Game xếp hình cổ điển) <br />
### Về cách cài đặt, hướng dẫn để có thể chạy chương trình <br />
1. Clone toàn bộ source code về máy.<br />
Fork repository và sử dụng câu lệnh git clone https://github.com/[YOUR_USERNAME]/Project.git <br />
2. Cài đặt thư viện đồ họa SDL, thư viện SDL_image, SDL_ttf, SDL_image, SDL_mixer.<br />
Hướng dẫn cài đặt các thư viện SDL có thể tham khảo qua video https://www.youtube.com/watch?v=DoRyZaFZekQ .Cài đặt các thư viện còn lại cũng sẽ tương tự.<br />
3. Tận hưởng trò chơi.<br />
Link YouTube: https://www.youtube.com/watch?v=10DYdEo9kqY <br />.
### Mô tả về trò chơi và các ý tưởng chính <br />
1. Mô tả <br />
Tetris là trò chơi xếp hình cổ điển được ra đời vào cuối thế kỷ 20 ở Nga. Ngày nay Tetris được xem như là một trong những trò chơi kinh điển và thịnh hành nhất trên thế giới. <br />
2. Ý tưởng chính hình thành trò chơi <br/>
Trò chơi có bảy loại khối hình: I (thẳng đứng), J, L, O (vuông), S, T, Z. Ta thấy mỗi khối gạch được cấu tạo từ 4 hình vuông nhỏ xếp lại với nhau. Ta có thể coi các khối gạch đó như là những hình chữ nhật có kích thước khác nhau.<br/>
Các hình khác được tạo ra khi xoay các khối cơ bản này các góc tương ứng 90 độ, 180 độ, 270 độ.<br/>
Một chuỗi ngẫu nhiên của Tetriminos rơi xuống sân chơi (một trục đứng hình chữ nhật, được gọi là "tốt" hay "ma trận").<br/>
Mục đích của người chơi là làm đầy các thanh Tetriminos trên một hàng ngang nhiều nhất có thể để ghi điểm, sao cho không thể làm được nữa thì trò chơi sẽ kết thúc. <br/>
### Về các chức năng đã cài đặt<br/>
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
   * Chế độ chơi Blindfolded.<br/> 
   * Điểm cao và ghi lại dữ liệu điểm của người chơi.<br/> 
   * Vòng lặp trong trò chơi.<br/> 
### Về các kỹ thuật đã được sử dụng.<br/>
  1. Tạo ra màn hình chơi, bao gồm số hàng và số cột.<br/>
  Để tạo ra màn hình chơi cơ bản thì ta khai báo một mảng 2 chiều kiểu int `int field[Lines][Cols]`, trong đó `Lines` và `Cols` là kiểu giá trị cố định `enum`. Ở đây `Lines = 20, Cols = 10` <br/>
  Mục đích của kiểu `int` thay vì kiểu `bool` là để hiển thị màu cho đồ họa. Nếu như người chơi muốn màu của các thanh Tetriminos sau khi rơi là một màu đồng nhất thì có thể để mảng kiểu `bool` hoặc cho các giá trị cố định ở `field`. Vì trên các trò chơi ngày nay người ta để các màu của các thanh Tetriminos sau khi rơi vẫn như cũ nên ta sẽ theo đó làm chuẩn.<br/>
  2. Tạo ra các khối Tetriminos.<br/>
  Để tạo ra các khối Tetriminos, ta có thể tạo ra từ một mảng 2 chiều (4x4), hoặc 1 chiều (16). Ở đây ta thể hiện các dạng khối qua một cấu trúc `Struct Point()` bao gồm các biến thành viên là:<br/>
          `int x, y, color, figure`<br/>
Trong đó, `x, y` là các tọa độ của các điểm, `color` là kiểu màu sắc đặc trưng cho từng thanh, `figure` là kiểu hình của thanh Tetrimino.<br/>
Ngoài ra ta cần một mảng hằng `const int figures[7][4]` để tạo ra kiểu hình cho các thanh Tetrimino.<br/>
Để tưởng tượng, giả sử ta có 8 vị trí như sau:<br/>
0 1 2 3<br/>
4 5 6 7<br/>
Nếu ta cho figure nhận các giá trị khác 0 ở các vị trí, ví dụ như 0,1,5,6, ta sẽ thu được thanh Tetrimino chữ Z.<br/>
Chúng ta sẽ dựa trên cách đặt này để thể hiện các thanh Tetrimino. Bằng cách tạo ra các mảng 1 chiều kiểu Point, chúng ta có thể thể hiện vị trí của các thanh Tetrimino khởi tạo<br/>
  3.Thực hiện việc di chuyển, xoay các thanh Tetrimino, và thời gian để thanh Tetrimino rơi xuống.<br/>
  Để thực hiện việc di chuyển một cách liên tục, ta cần phải tạo một hàm thực hiện việc bắt sự kiện từ bàn phím `void handleEvents()` dựa trên kiểu biến nhận sự kiện 
 `SDL_Event e`.<br/>
 Theo đó, nếu như bấm RIGHT, các điểm được hiển thị (thanh Tetrimino) sẽ di chuyển sang phải 1 đơn vị, và sang trái 1 đơn vị nếu như bấm LEFT. Nếu như bấm UP, các điểm được hiển thị sẽ thực hiện việc đổi vị trí theo quy luật (thanh Tetrimino sẽ xoay). Cần phải có các điều kiện ràng buộc kiểm tra xem bước đi đó là có thể hay không.<br/>
 4. Hiển thị đồ họa<br/>
 Để thực hiện công việc trên, cần phải làm việc với các thư viện đồ họa. Ngoài các khởi tạo màn hình, bút vẽ, cần phải xây dựng các khối chữ nhật được lấy màu từ ảnh cho trước để hiển thị màu cho các thanh Tetriminos. Để làm được điều đó, để biến thành viên `color` ở cấu trúc `Point` và kiểu mảng 2 chiều `int field[Lines][Cols]` là cần thiết. <br/>
 Các khối blocks được lấy từ ảnh bên ngoài trong file `image/blocks.png`. Ứng với mỗi loại thanh Tetrimino, ta lấy một khối blocks màu khác nhau từ ảnh bằng `SDL_RenderCopy(renderer, blocks, &srcR, &destR)`. Trong đó `srcR,destR` là các cấu trúc `SDL_Rect` được gán tọa độ phù hợp với tọa độ rect cần lấy ở `blocks`, còn `blocks` là cấu trúc `SDL_Texture` được lấy từ ảnh.<br/>
 Khi đó, ta có thể xây dụng trò chơi một cách tương đối cơ bản. <br/>
 Tuy nhiên, nếu chỉ làm ra được như vậy, sẽ không thể tạo ra một trò chơi đúng nghĩa. Chúng ta cần phải tạo ra thêm các chức năng để trò chơi thêm thú vị. <br/>
 5. Hiển thị thanh Tetrimino kế tiếp.<br/>
 Nếu như không thực hiện công việc trên, thì thanh Tetrimino hiện tại là thanh đã được tạo ngẫu nhiên. Khi đó nếu như muốn thực hiện việc tạo ra thanh kế tiếp, chỉ cần cho thanh kế tiếp sinh ra ngẫu nhiên, còn thanh hiện tại sẽ nhận các chỉ số của thanh kế tiếp đó. <br/>
 Để hiển thị thanh kế tiếp cũng không phải quá khó khăn, chỉ cần thực hiện những công việc như ở phần d, và chỉnh sửa vị trí của các khối Rect.<br/>
 6. Có thể giữ thanh Tetrimino hiện tại và thay bằng một thanh mới (nếu có) hoặc tạo mới thanh Tetrimino. (Hold)<br/>
 Hiển thị thanh Hold sẽ giống như hiển thị thanh kế tiếp. <br/>
 Trong khi đó việc thực hiện chức năng Hold sẽ áp dụng cơ chế Swap.<br/>
 Ta gọi ra một mảng cấu trúc Point `Point temp[4]` và thực hiện việc hoán đổi 2 thanh Tetrimino. Nếu như chưa có thanh Tetrimino nào được giữ thì sẽ thực hiện việc tạo mới.<br/>
 7. Hiển thị thanh Tetrimino dự đoán vị trí của thanh Tetrimino khi rơi xuống.<br/>
 Để hiển thị thanh Tetrimino dự đoán thì không khó vì ta chỉ cần hiển thị trên sân chơi như các thanh Tetrimino bình thường.<br/>
 Cơ chế của thanh Tetrimino dự đoán như sau:<br/>
 ** Nếu như không di chuyển trái phải, hoặc xoay, thì vị trí khởi tạo của thanh dự đoán sẽ trùng với thanh hiện tại và sẽ rơi xuống cho đến khi không thể rơi được nữa. Nếu như di chuyển trái phải hoặc xoay, ta cần phải khởi tạo lại vị trí của thanh dự đoán và cũng thực hiện như trên.<br/>
 Để tránh việc thanh dự đoán đè lên thanh hiện tại khi 2 thanh ở cùng vị trí, thì ta thực hiện việc render thanh dự đoán trước, sau đó sẽ thực hiện render thanh hiện tại. Làm như vậy thì thanh hiện tại sẽ đè lên thanh dự đoán khi cùng vị trí.<br/>
 8. Cơ chế rơi của thanh Tetrimino.<br/>
 Trong trò chơi có sử dụng biến `unsigned int delay` và 2 biến `Uint32 startTime, currentTime`. Cho `startTime` nhận giá trị của `SDL_GetTicks()`. `currentTime` sẽ thay đổi dựa trên điều kiện `if startTime - currentTime > delay`. Khi đó sẽ thực hiện việc rơi cho thanh Tetrimino. Sau đó cho `startTime = currentTime` là hoàn thành.
 Chú ý rằng delay có thể thay đổi, và khi thay đổi delay thì tốc độ rơi của thanh Tetrimino sẽ thay đổi. Do đó để thực hiện việc thay đổi level cho trò chơi, ta chỉ cần thay đổi giá trị của `delay` tại một ngưỡng nào đó.<br/>
 9. Cơ chế điểm và level của trò chơi.<br/>
 Như đã nói ở trên, có thể thay đổi `delay` tùy ý. Do đó ta cần một cách để thay đổi `delay` dựa trên điều kiện. <br/>
 Ta tạo ra một biến `int score` để nhận điểm từ trò chơi. `score` sẽ tăng lên nếu như liên kết đủ một hàng hoặc sinh ra một thanh Tetrimino mới. Khi đạt đủ điểm, độ khó trò chơi sẽ tăng lên, và khi đó tốc độ rơi sẽ nhanh hơn. <br/>
 Để người chơi có thể thấy được điểm của mình là bao nhiêu, ta cần phải sử dụng thư viện `SDL_ttf.h`.<br/>
 Để có thể ghi chép trên màn hình trò chơi, cũng cần phải sử dụng các cấu trúc gần giống như thể hiện trò chơi. <br/>
 Tuy nhiên, chỉ cần khi sinh ra thanh Tetrimino mới, là cần phải thay đổi số liệu, vì khác với thể hiện trò chơi, thể hiện điểm không liên tục như vậy. Do đó chỉ cần thay đổi số liệu và thực hiện ghi ra điểm/độ khó khi tạo ra thanh Tetrimino mới (Vào thời điểm tạo ra thanh Tetrimino mới cũng là lúc tính điểm từ `unite`).<br/> 
10. Tạm dừng trò chơi.<br/> 
Để tạm dừng trò chơi ta cần phải bắt sự kiện từ bàn phím, thông qua `handleEvent`. Theo đó, nếu như người chơi bấm P, trò chơi sẽ tạm dừng, và bấm P một lần nữa để tiếp tục trò chơi.<br/> 
Ở đây sử dụng biến `int pausing` làm nhiệm vụ thay đổi giá trị khi người chơi bấm P. bằng cách cho `pausing = (pausing + 1) % 2` thì ta sẽ thu được kết quả như trên.<br/> 
Ngoài ra, cần phải hiển thị màn hình chờ khi tạm dừng. Điều này có thể thực hiện qua thư viện đồ họa.<br/> 
11. Âm nhạc trong trò chơi.<br/> 
Để làm việc với âm thanh, ta cần làm việc với thư viện `SDL_mixer`. <br/> 
Ta tạo ra `class Audio` chuyên làm việc với âm thanh, và khi cần, sẽ gọi ra các hàm đảm nhận công việc tạo ra âm nhạc.<br/> 
Cần phải thay đổi trạng thái âm nhạc khi người chơi thực hiện các công việc khác nhau. Ví dụ như từ Menu đến khi bắt đầu chơi, khi ghi điểm, hay Level được nâng lên.<br/> 
Sau khi chương trình kết thúc, cần phải giải phóng âm thanh và thoát `Mix_Quit()`.<br/> 
12. Chế độ chơi Blindfolded.<br/> 
Là chế độ chơi mới trong Tetris. Người chơi sẽ vẫn chơi trò chơi như bình thường, chỉ khác ở chỗ sân chơi sẽ không hiển thị. Người chơi vừa phải tính toán vị trí hợp lý, vừa phải ghi nhớ vị trí đã đặt của các thanh Tetrimino.<br/> 
Tất nhiên, để tránh việc trò chơi quá khó, người chơi có thể thấy được vị trí của các thanh Tetrimino thông qua việc bấm nút U. Người chơi sẽ có thể tháy sân chơi, và có thể chơi như bình thường. Tất nhiên, nếu như không thể nhớ được vị trí, thì việc bấm nút liên tục cũng không khác gì chơi truyền thống.<br/> 
Chỉ cần không hiển thị sân chơi, thì các thanh Tetrimino đã sắp xếp sẽ không được hiển thị.<br/> 
13. Điểm cao và ghi lại dữ liệu điểm của người chơi.<br/> 
Để làm được điều này thì cần phải làm việc với thư viện `fstream`. Theo đó, ta tạo ra `class About` để đảm nhận vai trò đọc và ghi dữ liệu của trò chơi vào các file txt.<br/> 
Để nhận dữ liệu về điểm của người chơi có thể bằng cách nhập dữ liệu điểm vào một mảng `vector<int>`. Để lấy điểm cao ta có thể thực hiện thông qua các hàm sắp xếp.<br/> 
Để ghi dữ liệu điểm hiện tại của người chơi thì ta làm ngược lại, mở file với chế độ ghi lên file và ghi điểm của người chơi khi trò chơi kết thúc.<br/> 
Trong tương lai, có thể dùng lớp `About` để ghi chép thông tin khác về trò chơi, cụ thể như các thông số về âm lượng, bắt đầu trò chơi từ độ khó bao nhiêu,... sao cho người chơi có thể trải nghiệm trò chơi một cách tốt nhất mà không cần phải hiệu chỉnh lại mỗi khi chơi.<br/> 
14. Vòng lặp trò chơi.<br/> 
Bản thân trò chơi không sử dụng chung một bộ điều khiển đồ họa. Do đó cần phải thực hiện việc tạo ra vòng lặp cho trò chơi.<br/> 
Về lý thuyết, vòng lặp có thể là vô hạn. Do đó phải đặt trong một vòng lặp vô hạn.<br/> 
Cần có các điều kiện để đảm bảo rằng trò chơi vẫn có thể thoát được vòng lặp trong các điều kiện khác nhau, ví dụ như khi người chơi bấm chuột vào Close, hoặc là khi người chơi không muốn chơi tiếp.<br/> 

### Kết luận
Tetris là tựa game đã ra mắt từ lâu về trước, nhưng sức hút của trò chơi vẫn kéo dài đến ngày nay. Để làm ra được trò chơi đã khó, để hoàn thiện trò chơi sao cho người chơi có những trải nghiệm chân thực nhất lại càng khó hơn.<br/> 
Bản thân em chưa thực sự hài lòng về trò chơi. Trò chơi vẫn có thể có một số lỗi, cách sắp xếp có thể chưa thực sự tối ưu. Bản thân trò chơi có thể được cải tiến để cho ra sản phẩm càng ngày càng giống với các trò chơi trên thị trường.<br/> 
Qua việc thực hiện dự án bản thân em cũng đã học được nhiều về chương trình. Từ cách đặt tên biến, cách sắp xếp các yếu tố trong một trò chơi vào một lớp, nhóm cụ thể, cho đến làm việc với các mảng trong trò chơi và , em đã có được một số kỹ năng cơ bản.<br/> 
Trò chơi vẫn có thể cải thiện trong tương lai. Một số định hướng sắp tới cho trò chơi cụ thể:<br/> 
  * Tạo ra Settings trong trò chơi và lưu lại các thông tin hiệu chỉnh trong About, để người chơi có thể hiệu chỉnh một lần và không cần hiệu chỉnh lại. <br/> 
  * Các chế độ chơi mới có thể được tạo ra như chơi 2 người, chơi với máy, chơi đối kháng,...<br/> 
  * Sử dụng chung một bộ xử lý đồ họa để tránh việc phải tạo lại khi chuyển sang Node mới.<br/> 
  * Hiệu chỉnh về cơ chế rơi và tạo mới thanh Tetrimino sao cho mượt mà hơn.<br/> 
Trong bài báo cáo của em có thể có những sai sót, rất mong được các thầy cô đánh giá, góp ý để bản thân em có thể hoàn thiện hơn trong tương lai.
