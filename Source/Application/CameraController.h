#include "Component/Camera.h"
class CameraController;

static CameraController* m_CameraController;

class CameraController
{
public:
	static CameraController* Get()
	{
		if (m_CameraController == nullptr)
		{
			m_CameraController = new CameraController();
		}

		return m_CameraController;
	}

	CameraController();
	~CameraController();

	void Init();
	void Tick();
private:
	Camera* m_MainCamera = nullptr;
};
