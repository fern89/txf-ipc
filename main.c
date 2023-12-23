#include <stdio.h>
#include <windows.h>
#include <ktmw32.h>
int main(int argc, char** argv){
    if(argc==2){
        HANDLE tra = (void*)atoi(argv[1]);
        HANDLE fl = CreateFileTransactedA("C:\\Users\\Public\\secret.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL, tra, NULL, NULL);
        char fbuf[100]={0};
        DWORD br;
        ReadFile(fl, fbuf, 100, &br, NULL);
        printf("Child process: %s\n", fbuf);
        CloseHandle(fl);
        return 0;
    }

    HANDLE tra = CreateTransaction(NULL, NULL, 0, 0, 0, 0, NULL);
    
    //pick any file you can write to
    HANDLE fl = CreateFileTransactedA("C:\\Users\\Public\\secret.txt", GENERIC_READ | GENERIC_WRITE, FILE_SHARE_READ | FILE_SHARE_WRITE, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL, tra, NULL, NULL);
    char data[] = "lorem ipsum dolor sit amet";
    DWORD a;
    WriteFile(fl, data, sizeof(data), &a, NULL);
    CloseHandle(fl);
    printf("Parent process: %s\n", data);
    
    HANDLE rl;
    //note: if not parent-child process, u can also OpenProcess then dup, but may as well use named pipes if you will be so noisy
    DuplicateHandle(GetCurrentProcess(), tra, GetCurrentProcess(), &rl, 0, TRUE, DUPLICATE_SAME_ACCESS);
    
    char cmd[100]={0};
    char flm[MAX_PATH];
    GetModuleFileName(NULL, flm, MAX_PATH);
    sprintf(cmd, "%s %d", flm, rl);
    system(cmd);
    getchar();
    RollbackTransaction(tra);
    CloseHandle(tra);
}
