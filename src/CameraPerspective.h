// Perspective Camera class
// Written by Sergey Kosov in 2005 for Rendering Competition
#pragma once

#include "ICamera.h"
#include "math.h"

/**
 * @brief Perspective Camera class
 */
class CCameraPerspective : public ICamera
{

private:
	// input values
	Vec3f m_pos;
	Vec3f m_dir;
	Vec3f m_up;

	// preprocessed values
	float m_focus;
	Vec3f m_xAxis;
	Vec3f m_yAxis;
	Vec3f m_zAxis;
	float m_aspect;


public:
	/**
	 * @brief Constructor
	 * @param pos Camera origin (center of projection)
	 * @param dir Camera viewing direction
	 * @param up Up-vector
	 * @param angle (Vertical) full opening angle of the viewing frustum (in degrees)
	 * @param resolution The image resolution
	 */
	CCameraPerspective(Vec3f pos, Vec3f dir, Vec3f up, float angle, Size resolution)
		: ICamera(resolution)
		, m_pos(pos)
		, m_dir(dir)
		, m_up(up)
	{
		// --- PUT YOUR CODE HERE ---
		cv::normalize(dir, m_zAxis);
		cv::normalize(m_zAxis.cross(m_up), m_xAxis);
		cv::normalize(m_xAxis.cross(m_zAxis), m_yAxis);
		
		//calculate for aspect?
		m_aspect = getResolution().width/getResolution().height;

		float angR = angle*2*M_PI/180.0;
		m_focus = 1.0/tan(angR/2.0);
	}
	virtual ~CCameraPerspective(void) = default;

	virtual bool InitRay(float x, float y, Ray& ray) override
	{
		// --- PUT YOUR CODE HERE ---
		ray.org = m_pos;
		ray.dir = (m_xAxis*(2.0*((x+0.5)/getResolution().width)*m_aspect))
				+ (m_yAxis*(1.0-2*(y+0.5)/getResolution().height))
				+ (m_zAxis*m_focus);
		cv::normalize(ray.dir, ray.dir);
		return true;
	}



};

