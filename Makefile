.PHONY: all build rebuild enigma _test unistall clean

all: build

build: enigma
	mkdir -p ./bin
	cp ./build/Enigma ./bin

rebuild: clean build

define CRYPTO_TARGET
$(1): $(1)_app
endef

$(foreach app, enigma, $(eval $(call CRYPTO_TARGET,$(app))))

%_app:
	cmake -S ./ -B ./build -DCMAKE_BUILD_TYPE=Release
	cmake --build ./build --config Release

tests: enigma_test

%_test:
	cmake -S ./tests -B ./tests/build
	cmake --build ./tests/build
	cd ./tests/build; ./TEST

unistall:
	find ./ -name "build" -type d -exec rm -rf {} +

clean: unistall
	rm -rf ./bin

style:
	find . -type f \( -name "*.cc" -o -name "*.h" \) -exec clang-format -i --verbose -style=Google {} +
