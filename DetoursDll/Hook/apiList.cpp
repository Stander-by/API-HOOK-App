void EnableDetours()
{
    DetourAttach(&(PVOID &)OldMessageBoxA, NewMessageBoxA);
    DetourAttach(&(PVOID &)OldMessageBoxW, NewMessageBoxW);

    DetourAttach(&(PVOID &)OldHeapCreate, NewHeapCreate);
    DetourAttach(&(PVOID &)OldHeapAlloc, NewHeapAlloc);
    DetourAttach(&(PVOID &)OldHeapDestroy, NewHeapDestroy);
    DetourAttach(&(PVOID &)OldHeapFree, NewHeapFree);

    DetourAttach(&(PVOID &)OldCreateFile, NewCreateFile);
    DetourAttach(&(PVOID &)OldDeleteFile, NewDeleteFile);
    DetourAttach(&(PVOID &)OldWriteFile, NewWriteFile);
    DetourAttach(&(PVOID &)OldReadFile, NewReadFile);
    DetourAttach(&(PVOID &)OldCopyFile, NewCopyFile);


    DetourAttach(&(PVOID&)OldRegCreateKeyExA, NewRegCreateKeyExA);
    DetourAttach(&(PVOID&)OldRegOpenKeyExA, NewRegOpenKeyExA);
    DetourAttach(&(PVOID&)OldRegQueryValueExA, NewRegQueryValueExA);
    DetourAttach(&(PVOID&)OldRegSetValueExA, NewRegSetValueExA);
    DetourAttach(&(PVOID&)OldRegCloseKey, NewRegCloseKey);


    DetourAttach(&(PVOID &)OldSocket, NewSocket);
    DetourAttach(&(PVOID &)OldConnect, NewConnect);
    DetourAttach(&(PVOID &)OldSend, NewSend);
    DetourAttach(&(PVOID &)OldRecv, NewRecv);

    DetourTransactionCommit();
}

void DisableDetours()
{
    DetourDetach(&(PVOID &)OldMessageBoxA, NewMessageBoxA);
    DetourDetach(&(PVOID &)OldMessageBoxW, NewMessageBoxW);

    DetourDetach(&(PVOID &)OldHeapCreate, NewHeapCreate);
    DetourDetach(&(PVOID &)OldHeapAlloc, NewHeapAlloc);
    DetourDetach(&(PVOID &)OldHeapDestroy, NewHeapDestroy);
    DetourDetach(&(PVOID &)OldHeapFree, NewHeapFree);

    DetourDetach(&(PVOID &)OldCreateFile, NewCreateFile);
    DetourDetach(&(PVOID &)OldDeleteFile, NewDeleteFile);
    DetourDetach(&(PVOID &)OldWriteFile, NewWriteFile);
    DetourDetach(&(PVOID &)OldReadFile, NewReadFile);
    DetourDetach(&(PVOID &)OldCopyFile, NewCopyFile);

    DetourDetach(&(PVOID&)OldRegCreateKeyExA, NewRegCreateKeyExA);
    DetourDetach(&(PVOID&)OldRegOpenKeyExA, NewRegOpenKeyExA);
    DetourDetach(&(PVOID&)OldRegQueryValueExA, NewRegQueryValueExA);
    DetourDetach(&(PVOID&)OldRegSetValueExA, NewRegSetValueExA);
    DetourDetach(&(PVOID&)OldRegCloseKey, NewRegCloseKey);

    DetourDetach(&(PVOID &)OldSocket, NewSocket);
    DetourDetach(&(PVOID &)OldConnect, NewConnect);
    DetourDetach(&(PVOID &)OldSend, NewSend);
    DetourDetach(&(PVOID &)OldRecv, NewRecv);

    DetourTransactionCommit();
}

