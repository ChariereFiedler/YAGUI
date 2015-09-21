#version 330 core

// Ouput data


layout(location = 0) out float FragDepth ;

void main(){
	FragDepth = gl_FragCoord.z;
}