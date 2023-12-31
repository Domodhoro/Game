#ifndef SOUND_HPP
#define SOUND_HPP

namespace Domodhoro
{

class Sound final
{
public:
    Sound()
    {
        if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
        {
            throw Game_Exception("Falha ao inicializar o SDL_mixer.", __FILE__, __LINE__);
        }
    }

    ~Sound()
    {
        for (const auto& it : musics)
        {
            Mix_FreeMusic(it.second);
        }

        Mix_Quit();
    }

    void load(const std::string& file_path, const std::string& music_name)
    {
        musics[music_name] = Mix_LoadMUS(file_path.c_str());

        if (!musics[music_name])
        {
            throw Game_Exception("Falha ao carregar música: " + file_path, __FILE__, __LINE__);
        }
    }

    void play(const std::string& music_name)
    {
        if (musics[music_name])
        {
            Mix_PlayMusic(musics[music_name], -1);
        }
    }

    void pause() const
    {
        Mix_PauseMusic();
    }

    void resume() const
    {
        Mix_ResumeMusic();
    }

    void reset() const
    {
        Mix_HaltMusic();
    }
private:
    std::map<std::string, Mix_Music*> musics;
};

}

#endif