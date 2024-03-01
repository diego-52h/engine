#include "GraphicsEngine.hxx"

GraphicsEngine::GraphicsEngine(GameSection& section, Renderer& renderer) : section(section), renderer(renderer) { }

void GraphicsEngine::update(const Int_16 dt)
{
	for(GameNode& node : this -> section.getNodes())
	{
		if(node.getGraphicsComponent() == nullptr)
			continue;
		
		GraphicsComponent& graphicsComponent = *node.getGraphicsComponent();
		
		std::string spriteName = graphicsComponent.getSprite();
		std::string animationName = graphicsComponent.getAnimation();
		
		Animation animation = this -> getSprite(spriteName).getAnimation(animationName);
		
		Int_16 frame = graphicsComponent.getFrame();
		
		Int_16 frameSpan = animation.frameSpan;
		Int_16 frameTime = graphicsComponent.getFrameTime();
		
		frameTime += dt;
		
		if(frameTime > frameSpan)
		{
			frameTime -= frameSpan;
			
			frame += 1;
			frame %= animation.frames.size();
		}
		
		graphicsComponent.setFrame(frame);
		graphicsComponent.setFrameTime(frameTime);
	}
}

void GraphicsEngine::render(const Camera& camera)
{
	Matrix3 inverseCamera = camera.getTransform().getMatrix().getInverse();
	
	std::queue<GameNode&> remaining;
	
	for(GameNode& next : this -> section.getRoot().getSons())
		remaining.push(next);
	
	while(!remaining.empty())
	{
		GameNode& node = remaining.front(); remaining.pop();
		
		this -> draw(inverseCamera, node);
		
		for(GameNode& next : node -> getSons())
			remaining.push(next);
	}
	
	this -> renderer.show();
}

void GraphicsEngine::draw(const Matrix3& inverseCamera, const GameNode& node)
{
	if(node.getGraphicsComponent() == nullptr)
		return;
	
	GraphicsComponent graphicsComponent& = *node.getGraphicsComponent();
	
	Int_16 frame = graphicsComponent.getFrame();
	
	std::string spriteName = graphicsComponent.getSprite();
	std::string animationName = graphicsComponent.getAnimation();
	
	Sprite sprite = this -> getSprite(spriteName);
	
	Matrix3 transform = inverseCamera * node.getTransform().getMatrix();
	
	this -> renderer.render(sprite.getTexture(), sprite.getAnimation(animationName).frames[frame], transform);
}

const Sprite& GraphicsEngine::getSprite(const std::string& path) const
{
	if(!this -> sprites.contains(path))
		this -> sprites[path] = Sprite(path);
	
	return this -> sprites[path];
}