#include <Windows.h>
#include <iostream>
#include <fstream>
#include <cstdio>
#include <string>
#include <winsock.h>
#pragma comment(lib, "ws2_32.lib")
using namespace std;

const DWORD ALL_ZERO = 0;
const DWORD ALL_ONE = ~ALL_ZERO;
const DWORD INTERVAL1 = 0x55555555;
const DWORD INTERVAL2 = 0x33333333;
const DWORD INTERVAL4 = 0x0F0F0F0F;
const DWORD INTERVAL8 = 0x00FF00FF;
const DWORD INTERVAL16 = 0x0000FFFF;

DWORD GetTheOneZeros(DWORD p_src)
{
    return p_src & ((~p_src) + 1); // p_src & (-p_src)
}

DWORD swapHighAndLow(DWORD p_src)
{
    return (p_src << 16) | (p_src >> 16);
}

DWORD reverseBinary(DWORD p_src)
{
    p_src = ((p_src & INTERVAL1) << 1) | ((p_src >> 1) & INTERVAL1);
    p_src = ((p_src & INTERVAL2) << 2) | ((p_src >> 2) & INTERVAL2);
    p_src = ((p_src & INTERVAL4) << 4) | ((p_src >> 4) & INTERVAL4);
    p_src = ((p_src & INTERVAL8) << 8) | ((p_src >> 8) & INTERVAL8);
    p_src = (p_src << 16) | (p_src >> 16);
    return p_src;
}

DWORD calculateOnesEx(DWORD p_src)
{
    DWORD res = 0;
    while (p_src)
    {
        res += 1;
        p_src = p_src & (p_src - 1);
    }
    return res;
}

DWORD calculateOnes(DWORD p_src)
{
    p_src = (p_src & INTERVAL1) + ((p_src >> 1) & INTERVAL1);
    p_src = (p_src & INTERVAL2) + ((p_src >> 2) & INTERVAL2);
    p_src = (p_src & INTERVAL4) + ((p_src >> 4) & INTERVAL4);
    p_src = (p_src & INTERVAL8) + ((p_src >> 8) & INTERVAL8);
    p_src = (p_src & INTERVAL16) + ((p_src >> 16) & INTERVAL16);
    return p_src;
}

DWORD calculateZerosEx(DWORD p_src)
{
    return 32 - calculateOnesEx(p_src);
}

DWORD calculateZeros(DWORD p_src)
{
    return 32 - calculateOnes(p_src);
}

DWORD calculateFrontZero(DWORD p_src)
{
    if (p_src == ALL_ZERO) return 32;
    if (p_src == ALL_ONE) return 0;
    DWORD res = 0;
    if (p_src >> 16 == 0) { res += 16; p_src <<= 16; }
    if (p_src >> 24 == 0) { res += 8;  p_src <<= 8; }
    if (p_src >> 28 == 0) { res += 4;  p_src <<= 4; }
    if (p_src >> 30 == 0) { res += 2;  p_src <<= 2; }
    if (p_src >> 31 == 0) { res += 1; }
    return res;
}

DWORD calculateFrontOne(DWORD p_src)
{
    if (p_src == ALL_ZERO) return 0;
    if (p_src == ALL_ONE) return 32;
    DWORD res = 0;
    if (p_src >> 16 == 0x0000FFFF) { res += 16; p_src <<= 16; }
    if (p_src >> 24 == 0x000000FF) { res += 8;  p_src <<= 8; }
    if (p_src >> 28 == 0x0000000F) { res += 4;  p_src <<= 4; }
    if (p_src >> 30 == 0x00000003) { res += 2;  p_src <<= 2; }
    if (p_src >> 31 == 0x00000001) { res += 1; }
    return res;
}

DWORD calculateRearZero(DWORD p_src)
{
    if (p_src == ALL_ZERO) return 32;
    if (p_src == ALL_ONE) return 0;
    DWORD res = 0;
    if (p_src << 16 == 0) { res += 16; p_src >>= 16; }
    if (p_src << 24 == 0) { res += 8;  p_src >>= 8; }
    if (p_src << 28 == 0) { res += 4;  p_src >>= 4; }
    if (p_src << 30 == 0) { res += 2;  p_src >>= 2; }
    if (p_src << 31 == 0) { res += 1; }
    return res;
}

DWORD calculateRearOne(DWORD p_src)
{
    if (p_src == ALL_ZERO) return 0;
    if (p_src == ALL_ONE) return 32;
    DWORD res = 0;
    if (p_src << 16 == 0xFFFF0000) { res += 16; p_src <<= 16; }
    if (p_src >> 24 == 0xFF000000) { res += 8;  p_src <<= 8; }
    if (p_src >> 28 == 0xF0000000) { res += 4;  p_src <<= 4; }
    if (p_src >> 30 == 0x30000000) { res += 2;  p_src <<= 2; }
    if (p_src >> 31 == 0x10000000) { res += 1; }
    return res;
}


/*int main()
{
    const char* messages[] =
    {
        "%s,ok,SegmentRootWD,Maguro:SegmentRoot:WarmingUp",
        "%s,ok,SegmentRootWD,Maguro:SegmentRoot:Serving",
        "%s,warning,SegmentRootWD,Maguro:SegmentRoot:NotAvailable",
    };
    ifstream in("d:\\code\\CPPRelated\\Debug\\output.csv", std::ios::in);
    if (!in)
    {
        cout << "Ang" << endl;
        system("pause");
        return 0;
    }
    // Verify the output WD report
    string line;
    int i = 0;
    char hostname[201];
    WSADATA wsaData;
    PHOSTENT hostinfo;
    WORD wVersionRequested = MAKEWORD(2, 0);
    if (WSAStartup(wVersionRequested, &wsaData) == 0)
    {
        gethostname(hostname, sizeof(hostname));
        cout << hostname << endl;
    }

    while (getline(in, line))
    {
        char message[201];
        sprintf_s(message, sizeof(message), messages[i], hostname);
        cout << message << endl;
        if (0 == _strnicmp(message, line.c_str(), strlen(message)))
        {
            printf("Right\n");
        }
        else
        {
            printf("Error\n");
        }
        ++i;
    }

    in.close();
    /*int logicalDriveCount = 0;
    DWORD DiskInfo = GetLogicalDrives();
    while (DiskInfo)
    {
        if (DiskInfo & 1)
        {
            ++logicalDriveCount;
        }
        DiskInfo = DiskInfo >> 1;
    };
    cout << "Logical Drive Number:" << logicalDriveCount << endl;
    int driveStringLength = GetLogicalDriveStrings(0, NULL);
    char*    sDriveString = new    char[driveStringLength];
    wchar_t* wDriveString = new wchar_t[driveStringLength];
    GetLogicalDriveStrings(driveStringLength,(LPTSTR)wDriveString);
    WideCharToMultiByte(0, 0, wDriveString, driveStringLength, sDriveString, driveStringLength, NULL, NULL);
    int driveType;
    int ordinal = 0;
    bool bFlag;
    unsigned _int64 i64FreeBytesToCaller;
    unsigned _int64 i64FreeBytes;
    unsigned _int64 i64TotalBytes;
    for (int i = 0; i < (driveStringLength >> 2); ++i)
    {
        char    sDir[4] = { sDriveString[ordinal], ':', '\\', '\0' };
        wchar_t wDir[4];
        MultiByteToWideChar(0, 0, sDir, 4, wDir, 4);
        cout << sDir;
        driveType = GetDriveType(wDriveString + (i << 2));
        if (driveType == DRIVE_FIXED)
        {
            cout << "Fixed Disk" << endl;
        }
        else if (driveType == DRIVE_REMOVABLE)
        {
            cout << "Removable Disk" << endl;
        }
        else if (driveType == DRIVE_CDROM)
        {
            cout << "CD/DVD ROM" << endl;
        }
        else if (driveType = DRIVE_REMOTE)
        {
            cout << "Network Drive" << endl;
        }
        else if (driveType == DRIVE_RAMDISK)
        {
            cout << "Virtual RAM Disk";
        }
        else if (driveType == DRIVE_UNKNOWN)
        {
            cout << "Unknown Device";
        }
        bFlag = GetDiskFreeSpaceEx(wDir, (PULARGE_INTEGER)&i64FreeBytesToCaller, (PULARGE_INTEGER)&i64TotalBytes, (PULARGE_INTEGER)&i64FreeBytes);
        if (bFlag)
        {
            cout << "Total Disk Space:" << (float)(_int64)i64TotalBytes / 1024 / 1024 << "MB" << endl;
            cout << "Free Disk Space:" << (float)(_int64)i64FreeBytesToCaller / 1024 / 1024 << "MB" << endl;
        }
        else
        {
            cout << "Device is not available";
        }
        cout << endl;
        ordinal += 4;
    }
    if (sDriveString) delete[] sDriveString;
    if (wDriveString) delete[] wDriveString;
    system("pause");
    return 0;
}*/

const DWORD NQUEENS = 8;
const DWORD UPPERLIMIT = (1 << NQUEENS) - 1;
DWORD sum = 0;
void EightQueen(DWORD row, DWORD ld, DWORD rd)
{
    DWORD p, pos;
    if (row != UPPERLIMIT) {
        pos = UPPERLIMIT & ~(row | ld | rd);
        while (pos != 0) { p = pos & ((~pos)+1), pos = pos - p; EightQueen(row + p, (ld + p) << 1, (rd + p) >> 1); }
    } else {
        sum += 1;
    }
}


void Gray_2D(DWORD m, DWORD n)
{
    DWORD ii = (1<<m)-1, jj = (1<<n)-1, u;
    for (DWORD i = 0; i <= ii; ++i)
    {
        u = (i ^ (i >> 1)) << n;
        for (DWORD j = 0; j <= jj; ++j)
            cout << (u | (j ^ (j >> 1))) << " ";
        cout << endl;
    }
}

int main()
{
    using std::cout;
    using std::endl;
    DWORD dw = 0;
    cout << calculateFrontZero(dw) << endl;
    cout << calculateFrontZero(~dw) << endl;
    dw = 1;
    cout << calculateFrontZero(dw) << endl;
    cout << calculateFrontZero(~dw) << endl;
    dw = 0x55555555;
    cout << calculateFrontZero(dw) << endl;
    dw = 0x33333333;
    cout << calculateFrontZero(dw) << endl;
    dw = 0x0F0F0F0F;
    cout << calculateFrontZero(dw) << endl;
    dw = 0x00FF00FF;
    cout << calculateFrontZero(dw) << endl;
    sum = 0;
    EightQueen(0, 0, 0);
    cout << sum << endl;
    Gray_2D(4, 4);
    return 0;
}
