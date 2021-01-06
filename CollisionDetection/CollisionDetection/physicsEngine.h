#ifndef PHYSICSENGINE_H
#define PHYSICSENGINE_H

# include "global.h"
#include <helper_functions.h>
#include "particles_kernel.cuh"
#include "vector_functions.h"

class PhysicsEngine
{
public:
	PhysicsEngine(uint sphere_num= SPHERE_NUM, uint grid_size=GRID_SIZE);
	~PhysicsEngine();
	void initData();
	float* outputPos();
	void update(float deltaTime);

protected:
	inline void createArrayOnGPU();

protected:
	uint sphere_num_;
	// CPU data
	float *h_pos_;              // particle positions
	float *h_velo_;              // particle velocities

	float *h_mass_;
	float *h_rest_;
	float *h_radius_;
	float *h_color_;

	// GPU data
	float *d_pos_;        // these are the CUDA deviceMem Pos
	float *d_velo_;
	float *d_velo_delta_;
	float *d_mass_;
	float *d_rest_;
	float *d_radius_;

	float *d_pos_sorted_;
	float *d_velo_sorted_;

	// grid data for sorting method
	uint  *d_hash_; // grid hash value for each particle
	uint  *d_index_;// particle index for each particle
	uint  *m_dCellStart;        // index of start of each cell in sorted list
	uint  *m_dCellEnd;          // index of end of cell

	

	uint   m_gridSortBits;

	//uint   m_posVbo;            // vertex buffer object for particle positions
	//uint   m_colorVBO;          // vertex buffer object for colors

	
	//float *m_cudaColorVBO;      // these are the CUDA deviceMem Color

	//struct cudaGraphicsResource *m_cuda_posvbo_resource; // handles OpenGL-CUDA exchange
	//struct cudaGraphicsResource *m_cuda_colorvbo_resource; // handles OpenGL-CUDA exchange

	// env
	SimulationEnv m_params;
	uint3 m_gridSize;
	uint3 grid_exp_;
	uint cell_num_;


public:

	void setDamping(float x)
	{
		m_params.globalDamping = x;
	}
	void setGravity(float x)
	{
		m_params.gravity = make_float3(0.0f, x, 0.0f);
	}

	void setCollideSpring(float x)
	{
		m_params.spring = x;
	}
	void setCollideE(float x)
	{
		m_params.e = x;
	}
	void setCollideDamping(float x)
	{
		m_params.damping = x;
	}
	void setCollideShear(float x)
	{
		m_params.shear = x;
	}
	void setCollideAttraction(float x)
	{
		m_params.attraction = x;
	}

	float *getSphereRadius()
	{
		return h_radius_;
	}
};

#endif // !PHYSICSENGINE_H
