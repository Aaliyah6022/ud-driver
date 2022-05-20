/*++

Module Name:

    public.h

Abstract:

    This module contains the common declarations shared by driver
    and user applications.

Environment:

    user and kernel

--*/

//
// Define an Interface Guid so that app can find the device and talk to it.
//

DEFINE_GUID (GUID_DEVINTERFACE_uddriver,
    0x6362bbf0,0x16c5,0x4657,0xaa,0xc5,0xea,0xfa,0x5f,0x9e,0x69,0x5d);
// {6362bbf0-16c5-4657-aac5-eafa5f9e695d}
