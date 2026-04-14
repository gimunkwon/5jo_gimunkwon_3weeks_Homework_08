#include "NBC_Dowork_08/Public/Global/ShootingGameMode.h"

#include "NBC_Dowork_08/Public/Player/ShootingPlayer.h"

AShootingGameMode::AShootingGameMode()
{
	static ConstructorHelpers::FClassFinder<AShootingPlayer> Player(TEXT("/Game/MyAsset/Player/Blueprints/BP_ShootingPlayer.BP_ShootingPlayer_C"));
	DefaultPawnClass = Player.Class;
}
