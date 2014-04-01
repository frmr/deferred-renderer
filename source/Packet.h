#ifndef PACKET_H
#define PACKET_H

class Packet
{
private:
    string data;

private:
    string Encode( const int16_t num ) const;
    string Encode( const int32_t num ) const;
    string Encode( const float num ) const;

public:
	enum class PayloadType
	{
		PLAYER = 0,

	};
    string GetData() const;

public:
    Packet( const string encodedPacket );
    Packet();
};

#endif
