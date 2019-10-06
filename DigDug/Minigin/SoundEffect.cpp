#include "MiniginPCH.h"
#include "SoundEffect.h"
#include <iostream>

//class based off first year sound class
dae::SoundEffect::SoundEffect( std::string path )
	:m_pMixChunk{ Mix_LoadWAV( path.c_str( ) ) }
{
	if ( m_pMixChunk == nullptr )
	{
		std::cout << "Exception occurred!\n";
		std::string errorMsg = "SoundEffect: Failed to load " + path + ",\nSDL_mixer Error: " + Mix_GetError( );
		std::cerr << errorMsg;
		try
		{
			throw IsLoaded();
		}
		catch (const std::exception& ex)
		{
			std::cout << ex.what();
		}
	}
}
dae::SoundEffect::~SoundEffect( )
{
	Mix_FreeChunk( m_pMixChunk );
	m_pMixChunk = nullptr;
}

bool dae::SoundEffect::IsLoaded( ) const
{
	return m_pMixChunk != nullptr;
}

bool dae::SoundEffect::Play( int loops )
{
	if ( m_pMixChunk != nullptr )
	{
		int channel{ Mix_PlayChannel( -1, m_pMixChunk, loops ) };
		return channel == -1 ? false : true;
	}
	else
	{
		return false;
	}
}

void dae::SoundEffect::SetVolume( int value )
{
	if ( m_pMixChunk != nullptr )
	{
		Mix_VolumeChunk( m_pMixChunk, value );
	}
}




