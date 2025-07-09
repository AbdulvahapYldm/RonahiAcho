#pragma once
#include "DrawDebugHelpers.h"

//Create Debug makro.
#define DRAW_DEBUG_SPHERE(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location,20.f,12,FColor::Red,true);
#define DRAW_DEBUG_SPHERE_SingleFrame(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location,20.f,12,FColor::Red,false,-1.f);

#define DRAW_DEBUG_LINE(StartLocation,EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Red,true,-1.f,0,1.f);
#define DRAW_DEBUG_LINE_SingleFrame(StartLocation,EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(),StartLocation,EndLocation,FColor::Red,false,-1.f,0,1.f);

#define DRAW_DEBUG_POINT(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),Location,15.f,FColor::Green,true);
#define DRAW_DEBUG_POINT_SingleFrame(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),Location,15.f,FColor::Green,false,-1.f);

#define DRAW_DEBUG_LINE_POINT(StartLocation, EndLocation) if(GetWorld()) \
{ \
    DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, true, -1.f, 0, 1.f); \
    DrawDebugPoint(GetWorld(),EndLocation, 15.f, FColor::Green, true); \
};
#define DRAW_DEBUG_LINE_POINT_SingleFrame(StartLocation, EndLocation) if(GetWorld()) \
{ \
    DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Red, false, -1.f, 0, 1.f); \
    DrawDebugPoint(GetWorld(),EndLocation, 15.f, FColor::Green, false,-1.f); \
};




/*

if (GEngine)
{
    GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString("E KeyPressed"));
}

*/