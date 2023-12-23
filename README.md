# txf-ipc
POC for IPC via NTFS TxF. Can be easily made bidirectional, this acts as a mere proof of concept. Possible replacement for named pipes for IPC within child processes.

Use for unrelated process is not recommended, as you will need to OpenProcess with PROCESS_DUP_HANDLE, which is quite suspicious. As the DuplicateHandle call with GetCurrentProcess() for both source and dest processes is commonly used to turn abstract handles (eg what you get when GetCurrentProcess) into a real handle (eg what OpenProcess gives), it should not trigger any alert.
