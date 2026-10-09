Đồ án Giữa kỳ - Lập trình Hệ thống: Mô phỏng lệnh `ls`
1. Thông tin sinh viên
- **Họ và tên:** Phạm Tiểu Vy
- **MSSV:** 24IT321
- **Tên học phần:** Lập trình hệ thống
2. Tổng quan dự án
   Dự án này là phiên bản mô phỏng lại lệnh `ls(1)` cốt lõi trong hệ điều hành UNIX/Linux, được viết hoàn toàn bằng ngôn ngữ C. Chương trình có chức năng đọc nội dung thư mục, trích xuất siêu dữ liệu (metadata) của các file và định dạng kết quả hiển thị dựa trên các cờ (flags) được truyền vào từ dòng lệnh.
3. Các tính năng đã cài đặt
   Chương trình hỗ trợ đầy đủ 19 cờ (flags) theo chuẩn tài liệu manual page, được chia thành các nhóm sau:
- **Nhóm hiển thị:**
  - `-a`: Hiển thị tất cả file, bao gồm cả file ẩn (bắt đầu bằng dấu `.`).
  - `-A`: Hiển thị gần như tất cả (giống `-a` nhưng bỏ qua thư mục `.` và `..`).
  - `-d`: Chỉ hiển thị thông tin của chính thư mục đó thay vì liệt kê nội dung bên trong.
- **Nhóm định dạng & Thông tin:**
  - `-l`: Hiển thị danh sách định dạng dài (phân quyền, số link, chủ sở hữu, dung lượng, thời gian sửa đổi).
  - `-n`: Hiển thị giống `-l` nhưng in UID và GID dưới dạng số thay vì tên.
  - `-h`: Hiển thị kích thước file ở định dạng dễ đọc cho con người (Bytes, KB, MB, GB).
  - `-i`: In số index node (inode) của mỗi file.
  - `-s`: In kích thước được cấp phát của mỗi file theo đơn vị block.
  - `-F`: Đính kèm một ký tự nhận dạng loại file (ví dụ: `/` cho thư mục, `*` cho file thực thi).
- **Nhóm sắp xếp:**
  - `-t`: Sắp xếp danh sách theo thời gian thay vì bảng chữ cái.
  - `-S`: Sắp xếp danh sách theo kích thước file giảm dần.
  - `-r`: Đảo ngược thứ tự sắp xếp hiện tại.
  - `-f`: Vô hiệu hóa sắp xếp, in ra danh sách theo đúng thứ tự đọc được từ thư mục gốc.
- **Nhóm đệ quy:**
  - `-R`: Liệt kê đệ quy nội dung của tất cả các thư mục con bên trong.
## 4. Cấu trúc mã nguồn
- `main.c`: Chịu trách nhiệm phân tích các đối số dòng lệnh (sử dụng `getopt`) và gọi hàm xử lý chính.
- `myls.c`: Chứa các thuật toán cốt lõi để đọc thư mục (`opendir`, `readdir`), trích xuất thông tin (`stat`), sắp xếp file (`qsort`) và định dạng đầu ra.
- `myls.h`: File tiêu đề (Header) chứa các thư viện cần thiết, định nghĩa cấu trúc dữ liệu (`LsOptions`, `FileInfo`) và khai báo nguyên mẫu hàm.
- `Makefile`: Script tự động hóa quá trình biên dịch và dọn dẹp mã nguồn.
## 5. Hướng dẫn biên dịch và sử dụng
**Bước 1: Biên dịch chương trình**
Mở terminal tại thư mục chứa mã nguồn và gõ lệnh:
```bash
make
```
Link: github
1.	https://github.com/vitrieumotpham-art/PhamTieuVy_24IT321_midterm 
 
 
