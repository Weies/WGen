#include"render.h"

int Shader::cur_id = 0;

Render2D::Render2D() :BaseRender(Shading2D) {
	transform = glGetUniformLocation(id, "transform");
	proj = glGetUniformLocation(id, "proj");
	prior = glGetUniformLocation(id, "prior");
	color = glGetUniformLocation(id, "color");
}

void Render2D::renderList(const mat3& transform) {
	bind();
	setTransformM(transform);
	int len = 0; int s = 0;
	vbo.setData(vers.size * 8, vers.arr);
	vbo.setAttribPointer(0, 2, 8, (void*)0);
	for (int i = 0; i < vers.cur; i++)
	{
		len = vers.cutoff[i + 1] - vers.cutoff[i];
		setColor(vers.colors[i].vec4());
		setPrior(vers.prior[i]);
		if (vers.fixed[i])setTransformM(mat3(1.0f));
		glDrawArrays(vers.modes[i], s, len);
		if (vers.fixed[i])setTransformM(transform);
		s += len;
	}
	vers.reset();
}

void Render3D::renderList(const CameraBlock& b) {//渲染ptr3所绘制的内容
	int s = 0; int len = 0;
	bind();
	vbo.setData(vers3.size3 * 12, vers3.arr3);
	vbo.setAttribPointer(0, 3, 12, (void*)0);
	for (int i = 0; i < vers3.cur3; i++)
	{
		setTransformM(b.mPVTransform * vers3.model[i]);
		//debug((b.mPVTransform * vers3.model[i]).t());
		setColor(vers3.colors3[i].vec4());
		if (vers3.modes3[i] == GL_TRIANGLES) {
			setModel(vers3.model[i]);
			setViewPos(b.mCameraPosition);
			setNormal(vers3.normal[i]);
		}
		else setNormal(vec3(-1000, 0, 0));
		len = vers3.cutoff3[i + 1] - vers3.cutoff3[i];
		glDrawArrays(vers3.modes3[i], s, len);
		s += len;
	}
	vers3.reset();
}

//void BaseLightRender::renderList(const mat4& PV_trans , const vec3& viewPos , const vec3& lightColor , const vec3& lightPos) {
//	int s = 0; int len = 0;
//	bind();
//	glUniform1i(light_rendering , 0);
//	vbo.setData(vers3.size3 * 12 , vers3.arr3);
//	vbo.setAttribPointer(0 , 3 , 12 , (void*)0);
//
//	setLightColor(lightColor);
//	setLightPos(lightPos);
//	setViewPos(viewPos);
//	for (int i = 0; i < vers3.cur3; i++)
//	{
//		len = vers3.cutoff3[i + 1] - vers3.cutoff3[i];
//		setColor(vers3.colors3[i].vec3());
//		setTransformM(PV_trans * vers3.model[i]);
//		setModelM(vers3.model[i]);
//		setNormal(vers3.normal[i]);
//		glDrawArrays(vers3.modes3[i] , s , len);
//		s += len;
//	}
//	vers3.reset();
//}
//
//void BaseLightRender::renderList(const CameraBlock& b) {
//	int s = 0; int len = 0;
//	bind();
//	glUniform1i(light_rendering , 0);
//	vbo.setData(vers3.size3 * 12 , vers3.arr3);
//	vbo.setAttribPointer(0 , 3 , 12 , (void*)0);
//	setViewPos(b.mCameraPosition);
//	for (int i = 0; i < vers3.cur3; i++)
//	{
//		len = vers3.cutoff3[i + 1] - vers3.cutoff3[i];
//		setColor(vers3.colors3[i].vec3());
//		setTransformM(b.mPVTransform * vers3.model[i]);
//		setModelM(vers3.model[i]);
//		setNormal(vers3.normal[i]);
//		glDrawArrays(vers3.modes3[i] , s , len);
//		s += len;
//	}
//	vers3.reset();
//}