#pragma once
#include <string>

//class based off first year sound class
namespace dae{
class SoundEffect
{
public:
	explicit SoundEffect( std::string path );
	~SoundEffect( );
	SoundEffect(const SoundEffect& other) = delete;
	SoundEffect& operator=(const SoundEffect& rhs) = delete;
	SoundEffect( SoundEffect&& other) = delete;
	SoundEffect& operator=( SoundEffect&& rhs) = delete;

	bool IsLoaded( ) const;
	bool Play( int loops );
	void SetVolume( int value ); 
private:
	Mix_Chunk* m_pMixChunk;
};
	}
