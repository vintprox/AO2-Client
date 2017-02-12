#include "aomusicplayer.h"

#include <string.h>

#include <QDebug>

AOMusicPlayer::AOMusicPlayer(QWidget *parent, AOApplication *p_ao_app)
{
  m_parent = parent;
  ao_app = p_ao_app;
}

AOMusicPlayer::~AOMusicPlayer()
{
  BASS_ChannelStop(m_stream);
}

void AOMusicPlayer::play(QString p_song, int p_volume)
{
  BASS_ChannelStop(m_stream);

  QString f_path = ao_app->get_music_path(p_song);

  m_stream = BASS_StreamCreateFile(FALSE, f_path.toStdString().c_str(), 0, 0, BASS_STREAM_AUTOFREE);

  this->set_volume(p_volume);

  BASS_ChannelPlay(m_stream, false);
}

void AOMusicPlayer::set_volume(int p_value)
{
  float volume = p_value / 100.0f;

  BASS_ChannelSetAttribute(m_stream, BASS_ATTRIB_VOL, volume);

}
