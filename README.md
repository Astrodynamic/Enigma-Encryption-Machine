# Enigma Encryption Machine

## Description
The Enigma Encryption Machine is a C++ program that implements the famous Enigma encryption machine from the era of encryption machines. The program allows you to encrypt arbitrary files using the Enigma algorithm. It provides a console interface and supports various features such as file encryption, machine configuration, and state saving.

## Dependencies
The Enigma Encryption Machine has the following dependencies:
- C++17 compiler
- CMake (minimum version 3.5)

## Build
To build the Enigma Encryption Machine, follow these steps:
1. Open a terminal.
2. Navigate to the root directory of the project.
3. Run the following command:

```bash
make build
```

This command will compile the source code and create an executable file named "Enigma" in the `bin` directory.

## Usage
To use the Enigma Encryption Machine, follow these steps:
1. Make sure you have successfully built the program.
2. Open a terminal.
3. Navigate to the `bin` directory.
4. Run the following command:

```bash
./Enigma
```

Replace `<file_path>` in the app with the absolute path to the file you want to encrypt.
The program will encrypt the file using the Enigma algorithm and save the encrypted file as `<source_file_name>_encoded` in the same directory as the source file.

## Development
If you want to contribute to the development of the Enigma Encryption Machine, follow these steps:

1. Clone the GitHub repository:

```bash
git clone https://github.com/your-username/enigma.git
```

2. Navigate to the project directory:

```bash
cd enigma
```

3. Make the necessary changes to the source code or add new features.

4. Build the program using the following command:

```bash
make build
```

5. Test the program using the following command:

```bash
make tests
```

6. If all tests pass successfully, you can commit your changes and push them to the repository:

```bash
git commit -am "Add new features"
git push
```

7. Create a pull request on GitHub to merge your changes into the main repository.

## License
The Enigma Encryption Machine is licensed under the [MIT License](LICENSE). Feel free to use, modify, and distribute the code for both commercial and non-commercial purposes.