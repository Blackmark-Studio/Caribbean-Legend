// Вильям Патерсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "원하는 게 있소?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "catoche":
			dialog.text = "안녕하시오, 나리. 젠장, 이 근방에서 군사 소동을 일으킨 장본인이 바로 자네였군?!";
			link.l1 = TimeGreeting()+", 나리. 네, 상륙한 배는 제 배가 맞습니다. 그런데 무슨 일입니까? 당신은 누구요? 영국인인가요?";
			link.l1.go = "catoche_1";
		break;
		
		case "catoche_1":
			dialog.text = "스코틀랜드인입니다, 나리. 영국 해군의 선장 윌리엄 패터슨이고, 이쪽은 내 일등항해사이자 오른팔인 아치볼드 칼훈이오. 사실 정글에 스페인 요새가 하나 있소. 내 임무는 저주받은 놈들을 영국 영토와 너무 가깝게 세운 그 요새에서 몰아내는 것이오.\n최근에 우리가 돌격을 시도했으나, 놈들은 피해를 입었음에도 불구하고 버텨냈소. 나는 지원군을 데리러 떠났고...";
			link.l1 = "이제 그럴 필요 없소. 당신이 못 끝낸 일을 내가 마무리했소; 정글 요새는 비었소. 스페인 지휘관 디에고 데 몬토야는 죽었고, 그의 함대도 전멸했소.";
			link.l1.go = "catoche_2";
		break;
		
		case "catoche_2":
			dialog.text = "이건 무슨 자경단 짓이오? 영국 영토에서 이런 군사 행동을 일으키는 동기가 뭐요?";
			link.l1 = "감히 상기시켜 드리오, Paterson 선장, 여기는 벨리즈가 아니오. 무슨 영국령이란 말이오? 이 모든 소동은 Don Diego de Montoya와 그 자의 무모한 결정, 즉 나와 내 배들을 공격한 것에서 시작됐소.";
			link.l1.go = "catoche_3";
		break;
		
		case "catoche_3":
			dialog.text = "에헴... 그런데 도니에고가 당신을 공격한 이유가 뭔가, 선장?";
			link.l1 = "그 자와 나는 오랜 원한이 있지... 그가 이끌던 함대가 생피에르를 공격했던 날부터, 그리고 얼마 지나지 않아 내가 직접 개입해서 그 함대를 소탕한 그때부터 말이야.";
			link.l1.go = "catoche_4";
		break;
		
		case "catoche_4":
			dialog.text = "젠장! 저 고귀한 카바예로를 살아 있게 두어야 했는데! 왜 그자가 정글에 군사 기지를 세웠는지 심문하려 했단 말이야. 아무 이유 없이 그런 짓을 했을 리가 없잖아...";
			link.l1 = "죄송하지만, 그는 지금 아무것도 말할 수 없습니다. 어쨌든 요새 안에는 주둔군의 부상병들이 있을지도 모릅니다.\n혹시 그들이 말해줄 가능성은 있습니까?";
			link.l1.go = "catoche_5";
		break;
		
		case "catoche_5":
			dialog.text = "군인들... 아, 저 고집불통 머스킷병들이 무슨 소용이람!... 돈 디에고의 시체는 어디 있지? 그 자가 중요한 문서를 가지고 있었을 수도 있는데!";
			link.l1 = "나는 돈 디에고를 무기고 요새 부지에 두고 왔다네.\n그가 그렇게 필요하다면 거기서 찾을 수 있을 것이오.\n그가 도망칠 수 있을 것 같진 않소.";
			link.l1.go = "catoche_6";
		break;
		
		case "catoche_6":
			dialog.text = "에... 누가 남의 일에 끼어들라고 했냐... 너 때문에 이미 머리가 아프단 말이야...";
			link.l1 = "선장님, 왜 저를 꾸짖으시는지 이해하지 못하겠습니다. 저는 선장님의 일을 해냈고, 제 사람들을 전투에 투입했으며, 제 목숨까지 걸었습니다. 그런데도 선장님은 불만이시군요. 이제 선장님께서 하실 일은 임무의 성공과 모든 일을 포트 로열에 알리기만 하면 됩니다. 선장님의 영광에 대해 저는 어떤 공도 주장하지 않을 테니, 그 점은 안심하셔도 됩니다.";
			link.l1.go = "catoche_7";
		break;
		
		case "catoche_7":
			dialog.text = "공을 가로채겠다고? 영광이 뭐냐고?! 너 정말 아무것도 모르잖아... 에이, 됐다. 잘 가라, 나리.";
			link.l1 = "당신도 행운을 빕니다!";
			link.l1.go = "catoche_8";
		break;
		
		case "catoche_8":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "GuardOT_OpenCatocheDoor", 10.0);
			sld = CharacterFromID("Archy");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 7.0);
			AddQuestRecord("Guardoftruth", "57");
		break;
		
		case "isladevieques":
			PlaySound("Voice\English\sharlie\Willie Paterson.wav");
			dialog.text = "이봐, 소문쟁이들이 네가 고양이처럼 아홉 목숨 있다고 한 말이 거짓이 아니었구나! "+TimeGreeting()+", 드 모르 나리. 안색이 별로 좋지 않으시군요...";
			link.l1 = TimeGreeting()+", Paterson 나리. 솔직히 말하자면, 그대와 친구인 Archibald가 제 역할을 아주 잘 해내서 나를 제대로 속였소. 모두 다 저주받으라지! 전혀 눈치채지 못했는데...";
			link.l1.go = "isladevieques_1";
		break;
		
		case "isladevieques_1":
			dialog.text = "이봐, 성지의 문 앞에서 욕하지 마라. 예상 못 했나? 영광이군, 내가 군도의 가장 유명한 책략가 중 한 명을 속였으니 말이야. 일기장 아이디어, 기막히지 않았어?\n널 어딘가 음침한 곳으로 유인해야 했지. 대놓고 죽이면 스캔들이 될 테니까. 넌 필리프 드 푸앵시와 막역한 사이잖아, 맞지? 이제 넌 흔적도 없이 사라질 거고, 아무도 어떻게 된 일인지 영영 모를 거다.";
			link.l1 = "그럼, 칼훈이 내게 한 모든 말이... 거짓이었다는 건가?";
			link.l1.go = "isladevieques_2";
		break;
		
		case "isladevieques_2":
			dialog.text = "전혀 아니오. 나는 정말로 이곳에서 불쌍한 아치볼드를 발견했소. 하지만 그는 회고록을 쓰지 않았소; 당신이 그의 방에서 찾은 일기는 내 부탁으로, 특별히 당신을 위해 쓴 것이오, 드 모르 나리.\n우리가 카포 카토체에서 만난 이후로 나는 줄곧 당신을 지켜보고 있었소. 두 얼굴의 지도를 돈 디에고의 시체에서 가져간 것도 바로 당신이었지? 부정하지 마시오, 내가 다 알고 있으니.";
			link.l1 = "너도 진리의 수호자에 대해 아는 거야?";
			link.l1.go = "isladevieques_3";
		break;
		
		case "isladevieques_3":
			dialog.text = "그건 멍청한 질문이군. 당연히 알고 있지. 그리고 네가 족장의 발톱도 가지고 있다는 것도 알아. 곧 네가 네 것이 아닌 그 물건들을 돌려주게 될 거다.";
			link.l1 = "당신이 돈 디에고처럼 비틀거리지 않아서 다행이오. 나는 솔직함과 직설적인 태도를 높이 평가하오. 내 이해가 맞다면, 당신이 나침반과 길의 화살을 가지고 있소?";
			link.l1.go = "isladevieques_4";
		break;
		
		case "isladevieques_4":
			dialog.text = "하하! 그래, 끝까지 솔직하게 가지. 나리, 정말 내가 당신이나 돈 디에고처럼 멍청해서 그런 귀중한 물건을 몸에 지니고 다닐 거라 믿는 건가? 나침반은 자메이카에 있어. 포트 로열에도 아니고, 아무도 찾으려 하지 않을 만한 곳에, 단단히 잠가 두었지. 하지만 그 정보는 당신에게 필요 없을 거야.";
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.OfficerKill"))
			{
				link.l1 = "내가 알기로는, 패터슨 나리, 자네는 이미 날 묻어버린 모양이군? 감히 말하건대, 고양이에게 목숨이 하나 남아 있지!.. 내 장교들은 어디 있지?";
				link.l1.go = "isladevieques_5_1";
			}
			else
			{
				link.l1 = "내가 알기로는, 패터슨 나리, 자네는 이미 나를 땅에 묻었다고 생각하나? 감히 말하건대, 고양이에게 목숨이 하나 더 남았네!..";
				link.l1.go = "isladevieques_5_2";
			}
		break;
		
		case "isladevieques_5_1":
			if (CheckAttribute(pchar, "questTemp.Guardoftruth.GirlKill"))
			{
				dialog.text = "여자 친구가 걱정되나, 선장? 네 여자는 저기 덤불 속에 이마에 구멍이 난 채로 누워 있어. 네 앞길을 닦아줬으니 곧 따라가게 되겠지. 솔직히, 꽤 예쁜 아가씨였어! 한 번만 같이 잔 건 아니길 바란다만?";
				link.l1 = "개새끼로군! 그 대가를 치르게 해주마, 이 자식아?!";
				link.l1.go = "isladevieques_6";
			}
			else
			{
				dialog.text = "당신의 장교들이 길을 닦아 놓았소, 드 모르 나리. 저기 덤불 속에 쓰러져 있지. 곧 당신도 그들과 함께하게 될 거요.";
				link.l1 = "그건 두고 보자!";
				link.l1.go = "isladevieques_6";
			}
		break;
		
		case "isladevieques_5_2":
			dialog.text = "정말로 마지막이 되게 해주지.";
			link.l1 = "그건 두고 보자!";
			link.l1.go = "isladevieques_6";
		break;
		
		case "isladevieques_6":
			dialog.text = "너 때문에 웃음이 나오는군. 혼자서 한 무리와 맞서겠다니! 아무튼, 잡담은 그만하고... 머스킷 겨눠라! 쏴라!";
			link.l1 = "...";
			link.l1.go = "isladevieques_7";
		break;
		
		case "isladevieques_7":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться patch-8
			LAi_ActorRunToLocation(npchar, "quest", "teleport", "IslaDeVieques_HouseEntrance", "quest", "mushketer", "GuardOT_WillyGetReady", 10.0);
			for(i=1; i<=5; i++)
			{
				sld = CharacterFromID("GuardOT_willymushketer_"+i);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "GuardOT_WillyMushketerDie");
			DoQuestFunctionDelay("Terrapin_SetMusic", 0.2);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
