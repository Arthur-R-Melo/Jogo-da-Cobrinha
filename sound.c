#include "sound.h"
#include "jogo.h"
#include "snake.h"
#include "coord.h"

void CarregaSons(Jogo* jogo){
    jogo->hit = LoadSound("sound/hit.mp3");
    jogo->foodSound = LoadSound("sound/eating.mp3");
}

void DescarregaSons(Jogo* jogo){
    UnloadSound(jogo->hit);
    UnloadSound(jogo->foodSound);
}

void CarregaMusicaDif(Jogo* jogo){
    if(jogo->dificuldade == 0){
        jogo->dif = LoadMusicStream("sound/mapa1.mp3");
        SetMusicVolume(jogo->dif, 0.1f);
    }else if(jogo->dificuldade == 1){
        jogo->dif = LoadMusicStream("sound/mapa2.mp3");
        SetMusicVolume(jogo->dif, 0.1f);
    }else if(jogo->dificuldade == 2){
        jogo->dif = LoadMusicStream("sound/mapa3.mp3");  
        SetMusicVolume(jogo->dif, 0.1f);
    }
}

void DescarregaMusicaDif(Jogo* jogo){
    UnloadMusicStream(jogo->dif);
}

void CarregaMusicaMenu(Jogo* jogo){
    jogo->menu = LoadMusicStream("sound/menu.mp3");
    SetMusicVolume(jogo->menu, 0.1f);
}

void DescarregaMusicaMenu(Jogo* jogo){
    UnloadMusicStream(jogo->menu);
}
