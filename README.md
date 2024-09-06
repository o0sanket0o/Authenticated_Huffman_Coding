<div style="text-align: center;">
  <img src="https://github.com/user-attachments/assets/a70d7166-02ac-4fef-a9fd-d1577abe5d01" alt="Logo" width="700" height="400">
</div>

# Authenticated Huffman Encoding

## About the Project

This project implements Huffman encoding, a popular algorithm for data compression, along with a password protection mechanism. The project allows users to encode strings using Huffman coding while securing access through a password system. The password is stored in a hashed form, and the history of successful logins and password changes is logged for security and auditing purposes.

<br/>

## Use Case and Problem Solved

### Data Compression with Huffman Coding <br/>

This project provides a solution for efficiently encoding data, thereby reducing its size without any loss of information. Huffman coding is particularly useful in scenarios where storage space is limited or where data transmission bandwidth needs to be minimized. By assigning shorter codes to frequently occurring characters and longer codes to less frequent characters, the overall data size is reduced, leading to more efficient storage and faster data transmission.

### Secure Access to Data Compression <br/>

Beyond just data compression, this project addresses the need for secure access to the compression tool. It integrates a password-based authentication system, ensuring that only authorized users can perform encoding operations. This added layer of security is crucial in environments where data confidentiality is essential, protecting both the process and the data from unauthorized access.

This dual functionality makes Authenticated Huffman Coding particularly useful in environments where both data efficiency and security are critical, such as in secure communication systems, file storage solutions, and data transfer protocols within restricted networks.

<br/>

## Functions and Libraries Used

### Custom Functions

* ```hashPassword()```: Generates a SHA-256 hash of the provided password.<br/>

* ```printHash()```: Prints the SHA-256 hash in hexadecimal format.<br/>

* ```compareHashes()```: Compares two SHA-256 hashes to verify if they are identical.<br/>

* ```hexStringToBytes()```: Converts a hexadecimal string to a byte array.<br/>

* ```readHashFromFile()```: Reads a stored password hash from pass.txt.<br/>

* ```writeHashToFile()```: Writes a SHA-256 hash to pass.txt.<br/>

* ```checkPass()```: Verifies the user-entered password against the stored hash. Allows password changes if verification fails.<br/>

* ```createPassWord()```: Generates a random password using a predefined character set.<br/>

* ```loginHistory()```: Logs successful logins and password changes to history.txt.<br/>

* ```implementHuffman()```: Encodes a string using the Huffman coding algorithm.<br/>

* ```combine()``` and ```create()```: Functions used for building and traversing the Huffman Tree in tree.c.<br/>

<br/>

## Standard Libraries

* ```stdio.h```: For input/output operations. <br/>

* ```string.h```: For string manipulation functions. <br/>

* ```stdlib.h```: For memory allocation and random number generation. <br/>

* ```stdbool.h```: For boolean data type. <br/>
  
* ```sys/time.h```: For calculating the time taken to encode the string. <br/>

* ```unistd.h```: For file operations like reading and writing. <br/>
  
* ```CommonCrypto.h```: For SHA-256 hashing functionality (specific to macOS). <br/>

<br/>

## Compatibility

This project currently uses the ```CommonCrypto``` library for hashing functionality, which is specific to macOS and iOS. As a result, the project is fully compatible with Apple platforms. However, for users on Windows or Linux, the ```CommonCrypto``` library is not available, and additional steps are required to ensure compatibility. <br/>

### Running on macOS
No additional steps are needed. The project will compile and run seamlessly using the provided ```CommonCrypto``` library for SHA-256 hashing. <br/>

### Running on Windows
To run the project on Windows, you will need to replace ```CommonCrypto``` with a cross-platform cryptography library such as OpenSSL or libsodium. Follow these steps: <br/>

* Install ```OpenSSL``` or ```libsodium```: <br/>

* ```OpenSSL```: Can be installed via ```vcpkg``` or by downloading pre-built binaries. <br/>

* ```libsodium```: Available through package managers like vcpkg or from the libsodium website. <br/>

* Replace any ```CommonCrypto``` function calls with the equivalent OpenSSL or libsodium functions. For example: <br/>

* For SHA-256 hashing using OpenSSL, include ```openssl/sha.h``` and use ```SHA256()``` instead of ```CC_SHA256()```. <br/>

* Modify the build command to link the appropriate libraries:<br/>

* ```gcc main.c -L. -lssl -lcrypto -o HuffmanCoding```

### Running on Linux
On Linux , similar steps are required:

* Install OpenSSL or libsodium using your distribution's package manager (e.g., ```apt```, ```yum```, or ```pacman```):

* For OpenSSL: ```sudo apt-get install libssl-dev``` <br/>

* For libsodium: ```sudo apt-get install libsodium-dev``` <br/>

* Replace the ```CommonCrypto``` function calls with ```OpenSSL``` or ```libsodium``` equivalents, as described in the Windows section.<br/>


* Update the build command to link the necessary libraries: <br/>

   ```gcc main.c -L. -lssl -lcrypto -o HuffmanCoding``` <br/>

### Future Compatibility Considerations <br/>
To make the project more platform-agnostic, i will try to switch to a cross-platform library like OpenSSL or libsodium by default. This will ensure that users on any operating system can run the project without additional setup.

<br/>

## Usage
1. Clone the repository: <br/>

   Copy code : ```git clone https://github.com/o0sanket0o/Huffman-Coding```
   
2. Enter in directory: <br/>

   Copy code : ```cd Huffman-Coding```

3. Build the program: <br/>

   Copy code : ```gcc main.c -L. myLibrary.a```

4. Run the program: <br/>

    Copy code : ```./a.out```

<br/>

## User Interaction

### Password Verification: <br/>

* Upon running the program, the user will be prompted to enter a password. The entered password is hashed and compared with the hash stored in pass.txt.

* If the password matches, the user can proceed to encode a string.

* If the password does not match, the user is given the option to create a new password or generate a random password.


### String Encoding: <br/> 

After successful authentication, the user is prompted to enter the string they wish to encode. The Huffman encoding algorithm is then applied, and the encoded string is processed.

<br/>

## Important files

* ```pass.txt```: Ensure this file is present to store the password hash. <br/>

* ```history.txt```: This file logs all successful logins and password changes. It will be created automatically if it does not exist.

<br/>

## Future Scope:
* Implementing a more sophisticated user interface. <br/>

* Expanding the functionality to include other compression algorithms. <br/>

* Adding encryption to further secure the encoded data. <br/>

<br/>

## Contributions:
Contributions are welcome! If you'd like to contribute to this project, please fork the repository and create a pull request with your changes.

<br/>

## Contact : 
Email : sanketchugh5@gmail.com  <br/>
Github Profile : https://github.com/o0sanket0o <br/>
LinkedIn : https://www.linkedin.com/in/sanket-chugh-6a52a4216
