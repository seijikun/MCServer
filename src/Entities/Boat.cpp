
// Boat.cpp

// Implements the cBoat class representing a boat in the world

#include "Globals.h"
#include "Boat.h"
#include "../World.h"
#include "../ClientHandle.h"
#include "Player.h"





cBoat::cBoat(double a_X, double a_Y, double a_Z) :
	super(etBoat, a_X, a_Y, a_Z, 0.98, 0.7)
{
	SetMass(20.f);
	SetMaxHealth(6);
	SetHealth(6);
}




void cBoat::SpawnOn(cClientHandle & a_ClientHandle)
{
	a_ClientHandle.SendSpawnVehicle(*this, 1);
}





void cBoat::DoTakeDamage(TakeDamageInfo & TDI)
{
	super::DoTakeDamage(TDI);

	if (GetHealth() == 0)
	{
		if (TDI.Attacker != NULL)
		{
			if (TDI.Attacker->IsPlayer())
			{
				cItems Pickups;
				Pickups.Add(cItem(E_ITEM_BOAT));
				m_World->SpawnItemPickups(Pickups, GetPosX(), GetPosY(), GetPosZ(), 0, 0, 0, true);
			}
		}
		Destroy(true);
	}
}





void cBoat::OnRightClicked(cPlayer & a_Player)
{
	if (m_Attachee != NULL)
	{
		if (m_Attachee->GetUniqueID() == a_Player.GetUniqueID())
		{
			// This player is already sitting in, they want out.
			a_Player.Detach();
			return;
		}
		
		if (m_Attachee->IsPlayer())
		{
			// Another player is already sitting in here, cannot attach
			return;
		}
		
		// Detach whatever is sitting in this boat now:
		m_Attachee->Detach();
	}
	
	// Attach the player to this boat
	a_Player.AttachTo(this);
}





void cBoat::Tick(float a_Dt, cChunk & a_Chunk)
{
	super::Tick(a_Dt, a_Chunk);
	BroadcastMovementUpdate();
	SetSpeed(GetSpeed() * 0.97); // Slowly decrease the speed.
	if (IsBlockWater(m_World->GetBlock((int) GetPosX(), (int) GetPosY(), (int) GetPosZ())))
	{
		SetSpeedY(1);
	}
}





void cBoat::HandleSpeedFromAttachee(float a_Forward, float a_Sideways)
{
	if (GetSpeed().Length() > 7)
	{
		return;
	}
	
	Vector3d ToAddSpeed(m_Attachee->GetLookVector() * (a_Sideways * 1.5));
	ToAddSpeed.y = 0;

	AddSpeed(ToAddSpeed);
}

	