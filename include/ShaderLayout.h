#pragma once

class ShaderLayout {

	/*
		Add all fixed shader locations here. 
		Named uniforms should still be set using the methods in ShaderProgram.

		If you want to reserve blocks do so with comments.
		^^This should only be done as a temporary measure until everything is using this class for all layout bindings.
	*/

public:
	static const int POSITION = 1;
	static const int NORMAL = 2;
	static const int COLOR = 3;
	static const int TEXCOORD = 4;
	static const int TANGENT = 5;
	static const int BITANGENT = 6;
	static const int INSTANCE_POSITION = 7;
	static const int INSTANCE_NORMAL = 8;
};
