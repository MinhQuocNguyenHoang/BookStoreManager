# --- CẤU HÌNH CƠ BẢN ---
CXX = g++
TARGET = NhaSachFetel
MINGW_BIN = /d/Tools/msys2/mingw64/bin

# --- INCLUDE ---
INCLUDES = -Isrc/models/include -Isrc/services/include -Isrc/webview/include -Isrc/services/webview2

# --- SOURCE ---
SRCS = $(wildcard src/*.cpp) \
       $(wildcard src/models/*.cpp) \
       $(wildcard src/services/*.cpp) \
	   $(wildcard src/webview/*.cc) 

# --- FLAGS CHUNG ---
CXXFLAGS += -Wall -std=c++17 -O3 $(INCLUDES)

# ==============================
# ===== BUILD CHO LINUX ========
# ==============================
LINUX_LDFLAGS = `pkg-config --cflags --libs gtk+-3.0 webkit2gtk-4.1`
LINUX_FLAGS = -DWEBVIEW_GTK

# ==============================
# ===== BUILD CHO WINDOWS ======
# ==============================
WIN_LDFLAGS = -lole32 -lcomctl32 -lgdi32 -lshlwapi

# ==============================
# ===== RULES ==================
# ==============================

# Default (Linux)
all: linux

linux:
	@echo "Build cho Linux..."
	$(CXX) $(CXXFLAGS) $(LINUX_FLAGS) $(SRCS) -o $(TARGET) $(LINUX_LDFLAGS)
	@echo "OK: $(TARGET)"

windows:
	@echo "Build Windows..."
	$(CXX) $(CXXFLAGS) $(SRCS) -o $(TARGET).exe $(WIN_LDFLAGS)
	@echo "OK: $(TARGET).exe"

run:
	./$(TARGET)

clean:
	rm -f $(TARGET) $(TARGET).exe
	rm -rf release

# ==============================
# ===== PACKAGE (WINDOWS) ======
# ==============================

package: windows
	@echo "Đóng gói ứng dụng..."

	# tạo thư mục release
	mkdir -p release

	# copy file cần thiết
	cp $(TARGET).exe release/
	cp WebView2Loader.dll release/
	cp -r src release/

	# copy runtime DLL của mingw
	cp $(MINGW_BIN)/libstdc++-6.dll release/
	cp $(MINGW_BIN)/libgcc_s_seh-1.dll release/
	cp $(MINGW_BIN)/libwinpthread-1.dll release/

	# copy thư mục UI và data
	cp -r UI release/
	cp -r data release/

	@echo "Done! Thư mục release đã sẵn sàng."