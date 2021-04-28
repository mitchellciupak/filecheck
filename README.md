# filecheck

## Usage
1. make the project
    ```
    make
    ```
2. run the project
    ```
    ./filecheck -p r ./README.md
    ```
    ```
    ./filecheck -p rwx ./filecheck
    ```
    ```
    ./filecheck -i ./README.md
    ```

## Documents
[Project Specifications](https://engineering.purdue.edu/~ee469/labs_2021/lab5_regular.html)
[access() Documentation](https://linux.die.net/man/2/access)
[errno() Documentation](https://man7.org/linux/man-pages/man3/errno.3.html)
[errno() Macros](httpshttps://www-numi.fnal.gov/offline_software/srt_public_context/WebDocs/Errors/unix_system_errors.html)
[lstat() Documentation](https://stackoverflow.com/questions/40564474/how-to-use-lstat-to-determine-if-hard-link-or-not)