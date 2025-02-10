# **my_copy - A Custom File Copy Utility**  

## **Overview**  
`my_copy` is a command-line utility that replicates the functionality of the `cp` command in Linux using system calls like `open`, `read`, `write`, and `fstat`. It allows copying files while preserving their size and, optionally, their permissions.  

## **Features**  
- Copy file contents from a source to a destination.  
- Preserve file permissions using the `-p` option.  
- Prompt the user before overwriting an existing file.  
- Handle common errors like missing arguments, permission issues, and non-existent files.  

## **Usage**  

### **Basic Copy**  
```bash  
./my_copy source.txt destination.txt  
```
- If `destination.txt` does not exist, it will be created.  
- If `destination.txt` exists, the program will prompt before overwriting.  

### **Copy with Permissions**  
```bash  
./my_copy -p source.txt destination.txt  
```
- Copies the **content** along with the **permissions** of `source.txt`.  

### **When No Arguments Are Passed**  
```bash  
./my_copy  
```
Output:  
```
Insufficient arguments  
Usage: ./my_copy [option] <source> <destination>  
```

## **Example Runs**  

#### **Copying a file when the destination does not exist:**  
```bash  
./my_copy file1.txt file2.txt  
```
Output:  
```
New file2.txt created and file1.txt copied successfully.  
```

#### **Copying a file when the destination exists:**  
```bash  
./my_copy file1.txt file2.txt  
```
Output:  
```
File "file2.txt" already exists. Do you want to overwrite? (Y/n)  
```

#### **Copying a file with permissions preserved:**  
```bash  
./my_copy -p file1.txt file2.txt  
```
Output:  
```
File copied successfully with permissions.  
```

## **Error Handling**  
- **Missing arguments:** Displays usage instructions.  
- **File not found:** Shows an error if the source file doesn’t exist.  
- **Permission issues:** Alerts the user if read/write permissions are denied.  

## **System Calls Used**  
- `open()` – Open files in read/write mode.  
- `read()` – Read file data into a buffer.  
- `write()` – Write buffer data to destination.  
- `close()` – Close file descriptors.  
- `fstat()` – Get file metadata (for `-p` option).  
- `fchmod()` – Apply source file permissions to the destination.  

## **How to Compile and Run**  
```bash  
gcc main.c -o my_copy  
./my_copy source.txt dest.txt  
```

## **License**  
This project is open-source and available under the **MIT License**.  
