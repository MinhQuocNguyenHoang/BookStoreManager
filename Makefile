# --- CẤU HÌNH CƠ BẢN ---
CXX = g++
TARGET = NhaSachFetel

# --- 1. CHỈ ĐƯỜNG CHO C++ TÌM FILE .HPP ---
# -I là "Include". Báo cho C++ biết hãy chui vào 2 thư mục này để tìm header
INCLUDES = -Isrc/models/include -Isrc/services/include

# --- 2. GOM TẤT CẢ FILE .CPP Ở MỌI THƯ MỤC ---
SRCS = $(wildcard src/*.cpp) \
       $(wildcard src/models/*.cpp) \
       $(wildcard src/services/*.cpp)

# --- CỜ BIÊN DỊCH VÀ THƯ VIỆN ---
CXXFLAGS = -Wall -std=c++17 -O3 $(INCLUDES)
LDFLAGS = `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.1`

# --- CÁC QUY TẮC (RULES) ---
all: $(TARGET)

$(TARGET): $(SRCS)
	@echo "Đang biên dịch hệ thống..."
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET) $(LDFLAGS)
	@echo "Thành công! Tên file: $(TARGET)"

run: $(TARGET)
	@echo "Khởi động ứng dụng..."
	./$(TARGET)

clean:
	@echo "Đang dọn dẹp..."
	rm -f $(TARGET)