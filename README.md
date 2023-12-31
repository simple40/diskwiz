# diskwiz : Master Your Disk Space with Ease

diskwiz is a command-line disk space analyzer tool that helps you understand the space usage of directories on your system.

 ## Features

- **Directory Analysis:** Analyze disk space usage in a specified directory.
  
- **Sorting Options:** Sort results by size, date, or alphabetical order.
  
- **Color-Coded Output:** Visually appealing and informative output. The colours shows the percentage of space taken by the file in that directory.

- **File and Subdirectory Separation:** Results are intelligently separated, presenting a clear distinction between files and subdirectories for a well-organized overview.


![diskwiz_res](https://github.com/simple40/diskwiz/assets/99835388/d53e7e1f-5e84-4dfb-856e-7e9f8fb0d39e)

 ## Installation
  
  ### Prerequisites:
  
  *Visual C++ Redistributable Package:* Ensure you have the appropriate version installed for your system.diskwiz requires the Visual C++ Redistributable for Visual Studio 2015-2022. Download and install it from [here](https://support.microsoft.com/en-us/help/2977003/the-latest-supported-visual-c-downloads).
  
  ### Steps:
  
- **Download the latest release:** Visit the [Releases page](https://github.com/simple40/diskwiz/releases) and download the diskwiz.exe file for your operating system.
  
<!-- - **Extract the contents:** Right-click the downloaded file and choose "Extract All" or use a suitable archive tool.
- **Choose an installation location:**
  -->
  Now you can use the cli by visiting the directory containing diskwiz.exe or you can follow the two option to access it from any directory.
  
-  Option 1: Add to PATH:
    - Copy diskwiz.exe to a directory included in your PATH environment variable (e.g., C:\Windows\System32).
-  Option 2: Create a custom directory:
    - Create a dedicated directory for DiskWiz (e.g., C:\DiskWiz).
    -  Add this directory to your PATH manually 
      
## Usage

Once you have installed the CLI, you can use its set of commands and flags to analyze the directory and monitor the disk usage.

For the commands and flags to work, they must follow this syntax:

```bash
diskwiz {COMMAND} {FLAGS}
```

- **{COMMAND}** specifies the operation you want to perform.
- **{FLAGS}** specifies optional flags you can use to enrich your command.
  
  **Basic Usage:**
  
  - Open a command prompt or terminal.
    
  - Navigate to the directory containing diskwiz.exe:
    
  - Use the cd command (e.g., cd C:\DiskWiz). (if path of the diskwiz.exe is not in the environment variables)
    
  - Run DiskWiz commands:
    
  - Type diskwiz followed by the desired command and options.
  
  **Common Commands:**

  
  - **diskwiz analyze <drive_letter>:** Analyze disk space usage on the specified drive.
    
  - **diskwiz analyze:** Analyze the directory currently opened in the terminal.
    
  - **diskwiz analyze -s <drive_letter>:** Analyze and sort the result according to the size.
    
  - **diskwiz analyze -d <drive_letter>:** Analyze and sort the result according to the last date modified.
    
  - **diskwiz analyze -n <drive_letter>:** Analyze and sort the result according to the name.
 
  - **diskwiz -v:** To get the version of the cli.

  **<drive_letter>** paste the path of directory under double quotes "" here

  for eg:
  ```bash
  diskwiz analyze -s "C:\path\of\directory"

  diskwiz -v
  ```
    
  For a complete list of commands and options, run diskwiz help.

## Development
  
  ### Build from Sources
  
  Alternatively, you can also build the Kyma CLI from the sources:
  
  1. To clone the Kyma CLI repository, run:
  
  ```bash
  git clone https://github.com/simple40/diskwiz.git
  ```
  2. Enter the root folder of the cloned repository and open the diskwiz.sln solution file.
     (ensure you have a compatible version installed, e.g., Visual Studio 2019 or later).
  
  3. Configure the build settings and build the solution.

  4. After a successful build, find the compiled binaries in the **x64/Debug** or **x64/Release** directory within the project folder.
     
  - To run DiskWiz from any directory, add the path to the directory containing diskwiz.exe to your system's PATH environment variable.
  
 ## Download

  Downloads are available from the [releases page](https://github.com/simple40/diskwiz/releases).

## Licensing

- Licensed under MIT [License](https://github.com/simple40/diskwiz/blob/main/LICENSE)

  

 

 
