#pragma once

class Device
{
private:
	ID3D11Device* device;    
	ID3D11DeviceContext* device_context;

	IDXGISwapChain* swap_chain;  
	ID3D11RenderTargetView* render_target_view;  

	static Device* instance;

	Device();
	~Device();

public:
	static Device* Get()
	{
		if (instance == nullptr)
			instance = new Device();

		return instance;
	}

	static void Delete() { delete instance; }

	void CreateDeviceAndSwapChain();
	void CreateBackBuffer();
	void SetViewPoint();

	void Clear();
	void Present();

	ID3D11Device* GetDevice() { return device; }
	ID3D11DeviceContext* GetDeviceContext() { return device_context; }
};