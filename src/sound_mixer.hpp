#ifndef SOUND_MIXER_HPP
#define SOUND_MIXER_HPP

namespace Domodhoro
{
    // Classe responsável por gerenciar a reprodução de música usando a SDL Mixer.
    class Sound_Mixer final
    {
    public:
        // Construtor que inicializa o sistema de áudio com parâmetros padrão.
        Sound_Mixer()
        {
            if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
            {
                // Em caso de falha na inicialização do SDL_Mixer.
                throw Game_Exception(Mix_GetError(), __FILE__, __LINE__);
            }
        }

        // Destrutor que libera recursos associados ao sistema de áudio.
        ~Sound_Mixer()
        {
            // Libera as músicas.
            for (const auto& it : musics)
            {
                Mix_FreeMusic(it.second);
            }

            // Encerra o SDL_Mixer.
            Mix_Quit();
        }

        // Carrega um arquivo de música e o associa a um ID.
        void load(const std::string& file_path, const std::string& music_name)
        {
            musics[music_name] = Mix_LoadMUS(file_path.c_str());

            if (!musics[music_name])
            {
                throw Game_Exception(Mix_GetError(), __FILE__, __LINE__);
            }
        }

        // Reproduz a música associada a um ID em loop.
        void play(const std::string& music_name)
        {
            if (musics[music_name])
            {
                Mix_PlayMusic(musics[music_name], -1);
            }
        }

        // Pausa a reprodução da música atual.
        void pause() const
        {
            Mix_PauseMusic();
        }

        // Retoma a reprodução da música após uma pausa.
        void resume() const
        {
            Mix_ResumeMusic();
        }

        // Interrompe a reprodução da música atual.
        void reset() const
        {
            Mix_HaltMusic();
        }
    private:
        // Mapa associando IDs a ponteiros de música.
        std::map<std::string, Mix_Music*> musics;
    };
}

#endif // SOUND_MIXER_HPP