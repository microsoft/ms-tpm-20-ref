# Microsoft Production TA Signing Scripts

##### The Python scripts `generate_digest.py` and `stitch_ta.py` are used to production sign Microsoft-built TAs.

## Usage

1. Compile the TAs as usual.
2. Take the `*.stripped.elf` file (TA with no signature), and run the following Python script.
This script will generate the digest (hash) for the unsigned TA. The digest will be stored in `6b51f84e-a93d-456c-ab0e29ad8f264a47.dig` in the same folder as the TA. The digest will be in ASCII Base64 format.
```
c:\Python34\python.exe "generate_digest.py" --in "6b51f84e-a93d-456c-ab0e29ad8f264a47.stripped.elf"
```
3. Send the `*.dig` file to the Security team for them to sign. They will return a `*.dig.signed` file.
4. Run the following Python script to generate the final Production-signed TA (`6b51f84e-a93d-456c-ab0e29ad8f264a47_signed.ta`):
```
c:\Python34\python.exe "stitch_ta.py" --in "6b51f84e-a93d-456c-ab0e29ad8f264a47.stripped.elf" --dig "6b51f84e-a93d-456c-ab0e29ad8f264a47.dig" --sig "6b51f84e-a93d-456c-ab0e29ad8f264a47.dig.signed" --out "6b51f84e-a93d-456c-ab0e29ad8f264a47_signed.ta"
```