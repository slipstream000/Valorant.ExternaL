#include "Vector.hpp"
#include "Camera.h"

#pragma comment(lib, "d3d9.lib")
#pragma comment(lib, "d3dx9.lib")
#pragma comment(lib, "dwmapi.lib")

LPDIRECT3D9			d3d;
LPDIRECT3DDEVICE9	d3ddev;

HANDLE pHandle;
HWND targetHwnd, overlayHwnd;
Vec2 vecScreen;
int windowWidth, windowHeight, windowX, windowY;
bool bMenuShow = false, bEsp = false, bSnapLines = false, bEspBox = false, bHeadBoxes = false, bShadedBoxes = false;

D3DCOLOR espColor = D3DCOLOR_ARGB(255, 0, 255, 255);

DWORD modBase;
DWORD localPlayer;
DWORD entityList;
DWORD* dwViewMatrix;

void initD3D(HWND hwnd);
void renderFrame(void);
void cleanD3D(void);
void espThread();

LRESULT CALLBACK WindowProc(HWND hwnd, UINT message, WPARAM wParam, LPARAM lParam);

struct ents
{
	DWORD ent[32];
	int health[32];
	Vec3 pos[32];
	Vec3 headPos[32];
	Vec3 angles[32];
	Vec2 ent2D[32];
	Vec2 entHead2D[32];
	float viewMatrix[16];
	char entName[16];
}mainInfo;


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR nCmdLine, int nCmdShow)
{
	AllocConsole();
	FILE* f;
	freopen_s(&f, "conout$", "w", stdout);
	std::cout << "[*] Loading..." << std::endl;
	std::cout << "[*] Launch Game..." << std::endl;

	while (!targetHwnd)
	{
		targetHwnd = FindWindowA(NULL, "AssaultCube");
	}

		ImpDef(PsLookupProcessByProcessId);
		ImpDef(KeStackAttachProcess);
		ImpDef(KeUnstackDetachProcess);
		ImpDef(ZwProtectVirtualMemory);
		ImpDef(ObfDereferenceObject);
		ImpSet(PsLookupProcessByProcessId);
		ImpSet(KeStackAttachProcess);
		ImpSet(KeUnstackDetachProcess);
		ImpSet(ZwProtectVirtualMemory);
		ImpSet(ObfDereferenceObject);
	
	

	void cache()
{
	while (true)
	{
		vector<TslEntity> tmpList;

		world = read<std::uint64_t>(m_base + 0x5DD8EF8);
		persistent_level = read<std::uint64_t>(world + 0x38);
		game_instance = read<std::uint64_t>(world + 0x180);

		local_player_array = read<std::uint64_t>(game_instance + 0x40);
		local_player = read<std::uint64_t>(local_player_array);
		local_player_controller = read<std::uint64_t>(local_player + 0x38);
		local_player_pawn = read<std::uint64_t>(local_player_controller + 0x518);

		camera_manager = read<std::uint64_t>(local_player_controller + 0x530);

		actors = read<std::uint64_t>(persistent_level + 0xB0);
		actor_count = read<int>(persistent_level + 0xB8);

		LocalRoot = read<std::uint64_t>(local_player_pawn + 0x238);
		LocalPos = read<Vector3>(LocalRoot + 0x1E0);

		damage_controller = read<std::uint64_t>(local_player_pawn + 0xAF8);

		for (unsigned long i = 0; i < actor_count; ++i)
		{
			std::uint64_t actor = read<std::uint64_t>(actors + i * 0x8);

			if (actor == 0x00)
			{
				continue;
			}

			

			int ID = read<int>(actor + 0x18);

		if (!NT_SUCCESS(ImpCall(PsLookupProcessByProcessId, HANDLE(local.pid), &target))) { return false; }

		KAPC_STATE apc;
		ImpCall(KeStackAttachProcess, target, &apc);
		status = ImpCall(ZwAllocateVirtualMemory, ZwCurrentProcess(), &alloc_base, 0, &local.size,
			(ULONG)local.allocation_type, (ULONG)local.protect);

			uint64_t mesh = read<uint64_t>(actor + 0x4F0);

			int UniqueID = read<int>(actor + 0x3C);
			if (UniqueID != 16777502)
				continue;

			if (mesh != 0x00 && UniqueID != 0x00)
			{
				tslEntity.mesh = mesh;

				tmpList.push_back(tslEntity);
			}
		}
		entityList = tmpList;
		Sleep(1);
	}
}

	
		Vector3 WorldToScreen(Vector3 world_location, Vector3 position, Vector3 rotation, float fov)
	{
		Vector3 screen_location = Vector3(0, 0, 0);

		_MYMATRIX tempMatrix = ToMatrix(rotation);

		Vector3 vAxisX, vAxisY, vAxisZ;

		vAxisX = Vector3(tempMatrix.m[0][0], tempMatrix.m[0][1], tempMatrix.m[0][2]);
		vAxisY = Vector3(tempMatrix.m[1][0], tempMatrix.m[1][1], tempMatrix.m[1][2]);
		vAxisZ = Vector3(tempMatrix.m[2][0], tempMatrix.m[2][1], tempMatrix.m[2][2]);

		Vector3 vDelta = world_location - position;
		Vector3 vTransformed = Vector3(vDelta.Dot(vAxisY), vDelta.Dot(vAxisZ), vDelta.Dot(vAxisX));

		if (vTransformed.z < 1.f)
			vTransformed.z = 1.f;

		float FovAngle = fov;
		float ScreenCenterX = globals::wnd::screen_res_width / 2.0f;
		float ScreenCenterY = globals::wnd::screen_res_height / 2.0f;

		screen_location.x = ScreenCenterX + vTransformed.x * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;
		screen_location.y = ScreenCenterY - vTransformed.y * (ScreenCenterX / tanf(FovAngle * (float)M_PI / 360.f)) / vTransformed.z;

		return screen_location;
	}
