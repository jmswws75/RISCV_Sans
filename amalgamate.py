import os
import re
import glob

# Configuration
OUTPUT_FILE = "amalgamated.c"

# Regex pattern to catch local includes: #include "something.h"
# It ignores system includes like #include <something.h>
LOCAL_INCLUDE_PATTERN = re.compile(r'^\s*#\s*include\s+"([^"]+)"')

def process_file(filepath, outfile):
    """Reads a file, strips local includes, and writes it to the output."""
    # Skip the output file itself so we don't create an infinite loop
    if not os.path.exists(filepath) or filepath == OUTPUT_FILE:
        return

    with open(filepath, 'r', encoding='utf-8') as infile:
        outfile.write(f"\n// {'='*50}\n")
        outfile.write(f"// BEGIN FILE: {filepath}\n")
        outfile.write(f"// {'='*50}\n\n")
        
        for line in infile:
            match = LOCAL_INCLUDE_PATTERN.match(line)
            if match:
                # Comment out the local include instead of deleting it, 
                # just in case you need to debug later!
                outfile.write(f"// [Amalgamator] Removed: {line.strip()}\n")
            else:
                outfile.write(line)
        
        outfile.write(f"\n// END FILE: {filepath}\n\n")

def main():
    print("Starting C amalgamation process...")
    
    # Grab all headers and source files in the current directory
    headers = sorted(glob.glob("*.h"))
    sources = sorted(glob.glob("*.c"))
    
    with open(OUTPUT_FILE, 'w', encoding='utf-8') as outfile:
        outfile.write("// AUTO-GENERATED AMALGAMATED C FILE\n\n")
        
        # Process Headers First
        print(f"Found {len(headers)} header files.")
        for header in headers:
            print(f" -> Merging {header}")
            process_file(header, outfile)
            
        # Process Sources Second
        print(f"\nFound {len(sources)} source files.")
        for source in sources:
            if source != OUTPUT_FILE:
                print(f" -> Merging {source}")
                process_file(source, outfile)

    print(f"\nSuccess! Cleaned and merged all files into '{OUTPUT_FILE}'.")

if __name__ == "__main__":
    main()
