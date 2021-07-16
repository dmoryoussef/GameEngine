class _PlatformLayer
{
private:

public:
	_PlatformLayer() {};

	virtual void RenderToBuffer() {};
	virtual void CopyBufferToWindow() {};
	virtual void ResizeBuffer() {};
};