
// Vector3i.h

// Declares the Vector3i class representing an int-based 3D vector





#pragma once





// fwd:
class Vector3d;





// tolua_begin
class Vector3i
{
public:
	/** Creates an int vector based on the floor()-ed coords of a double vector. */
	Vector3i(const Vector3d & v);

	Vector3i(void);
	Vector3i(int a_x, int a_y, int a_z);

	inline void Set(int a_x, int a_y, int a_z) { x = a_x, y = a_y, z = a_z; }
	inline float Length() const { return sqrtf( (float)( x * x + y * y + z * z) ); }
	inline int SqrLength() const { return x * x + y * y + z * z; }

	inline bool Equals( const Vector3i & v ) const { return (x == v.x && y == v.y && z == v.z ); }
	inline bool Equals( const Vector3i * v ) const { return (x == v->x && y == v->y && z == v->z ); }
	
	void Move(int a_MoveX, int a_MoveY, int a_MoveZ);
	
	// tolua_end

	void operator += ( const Vector3i& a_V ) { x += a_V.x; y += a_V.y; z += a_V.z; }
	void operator += ( Vector3i* a_V ) { x += a_V->x; y += a_V->y; z += a_V->z; }
	void operator -= ( const Vector3i& a_V ) { x -= a_V.x; y -= a_V.y; z -= a_V.z; }
	void operator -= ( Vector3i* a_V ) { x -= a_V->x; y -= a_V->y; z -= a_V->z; }
	void operator *= ( int a_f ) { x *= a_f; y *= a_f; z *= a_f; }

	friend Vector3i operator + ( const Vector3i& v1, const Vector3i& v2 ) { return Vector3i( v1.x + v2.x, v1.y + v2.y, v1.z + v2.z ); }
	friend Vector3i operator + ( const Vector3i& v1, Vector3i* v2 ) { return Vector3i( v1.x + v2->x, v1.y + v2->y, v1.z + v2->z ); }
	friend Vector3i operator - ( const Vector3i& v1, const Vector3i& v2 ) { return Vector3i( v1.x - v2.x, v1.y - v2.y, v1.z - v2.z ); }
	friend Vector3i operator - ( const Vector3i& v1, Vector3i* v2 ) { return Vector3i( v1.x - v2->x, v1.y - v2->y, v1.z - v2->z ); }
	friend Vector3i operator - ( const Vector3i* v1, Vector3i& v2 ) { return Vector3i( v1->x - v2.x, v1->y - v2.y, v1->z - v2.z ); }
	friend Vector3i operator * ( const Vector3i& v, const int f ) { return Vector3i( v.x * f, v.y * f, v.z * f ); }
	friend Vector3i operator * ( const Vector3i& v1, const Vector3i& v2 ) { return Vector3i( v1.x * v2.x, v1.y * v2.y, v1.z * v2.z ); }
	friend Vector3i operator * ( const int f, const Vector3i& v ) { return Vector3i( v.x * f, v.y * f, v.z * f ); }
	friend bool operator < ( const Vector3i& v1, const Vector3i& v2 ) { return (v1.x<v2.x)||(v1.x==v2.x && v1.y<v2.y)||(v1.x==v2.x && v1.y == v2.y && v1.z<v2.z); }

	int x, y, z;	// tolua_export
};	// tolua_export

typedef std::list<Vector3i>   cVector3iList;
typedef std::vector<Vector3i> cVector3iArray;




