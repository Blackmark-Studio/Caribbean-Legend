// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			// Jason НСО
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "찰스, 대체 뭐야?";
				link.l1 = "스티븐, 문제가 있었어. 오지도 못했고, 네게 내가 못 온다는 것도 알리지 못했어...";
				link.l1.go = "patria_33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "반갑다, 친구! 뭐 도와줄까? ";
				link.l1 = "나도 반갑다, 스티브. 그 완벽하게 진행된 구경거리에 대해 고맙다고 말하고 싶어!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "반갑다, 친구! 뭘 도와줄까?";
				link.l1 = "너한테 제안이 있어, 스티븐. 해적다운 제안이지.";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "저기 우리 놈이 있군! 일은 끝났어; 네 바론은 경비가 삼엄한 감옥에 처박혀 있지. 혹시 구경이라도 하고 싶어? 크하하!";
				link.l1 = "하, 그건 나중에 할 시간 많지. 그 녀석, 잘 대접받고 있나?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
			{
				dialog.text = "반갑다, 친구! 뭐 도와줄까?";
				link.l1 = "뭔가 필요해, 스티븐...";
				link.l1.go = "tieyasal";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
			{
				dialog.text = "반갑다, 친구! 뭐 도와줄까?";
				link.l1 = "스티븐, 너한테 줄 게 있어.";
				link.l1.go = "guardoftruth";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
			{
				dialog.text = "반가워, 친구! 뭘 도와줄까?";
				link.l1 = "스티븐, 물어볼 게 있어. 너한텐 좀 거슬릴 수도 있겠지만... 네 도움이 필요해.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
			{
				dialog.text = "아, 거기 있었군, "+pchar.name+". 너를 기다리고 있었지; 숲의 악마가 토르투가에서 네가 겪은 문제에 대해 말해줬거든...";
				link.l1 = "그가 그러던데, 너 이미 해결책을 찾았다고 하더라. 사실이야?";
				link.l1.go = "terrapin";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
			{
				dialog.text = "우리 상황이 어떤가, "+pchar.name+"?";
				link.l1 = "비밀이 사방에 있군... 조언이 필요해, 스티븐.";
				link.l1.go = "terrapin_8";
				break;
			}
			// belamour legendary edition хвастовство "Фортуной"
			if(CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar,"questTemp.SharkFrigate"))
			{
				link.l2 = "뭔가 보여주고 싶어... 나랑 부두까지 같이 걸을래?";
				link.l2.go = "check_out_my_frigate";
			}
			
			// belamour legendary edition на пару с Акулой
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
			{
				dialog.text = "아, 내 친구 "+GetFullName(pchar)+"! 들어와, 들어와, 이렇게 보니 반갑군!";
				link.l1 = "이봐, 스티븐! 약속대로 왔어. 네 배 준비됐냐?";
				link.l1.go = "SharkGoldFleet";
				break;
			}
			if(CheckAttribute(pchar,"questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
			{
				link.l2 = "그래서, 요즘 장사는 어때? 아직도 '황금 함대' 쫓고 있나?";
				link.l2.go = "SharkGoldFleet_10";
			}
			dialog.text = "아, 내 친구 "+GetFullName(pchar)+"! 들어와, 들어와, 보니 반갑구만!";
			link.l1 = "안녕, 스티븐. 나 샤프타운에 볼일 있어서 잠깐 들렀어.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		// --------------------------------------вариант R-----------------------------------------------
		case "Chad_die":
			dialog.text = "하! 네가 우리 밤손님이구만? 방금 전에야 이 사건에 대해 들었지. 네 소지품을 확인해보니 포레스트 데빌이 보낸 편지가 있더군. 젠장, 거의 신(新) 스페인 정글 냄새가 날 지경이었어!\n네 이름은 "+GetFullName(pchar)+"뭐야? 나는 스티븐 도드슨이다, 어떤 놈들한테는 상어로 더 잘 알려져 있지. 스벤슨이 내 얘기 했겠지. 하지만 정의의 섬 근방에선, 난 제독으로 통한다.\n어젯밤 내 부하들이 저지른 짓에 대해 사과하지. 내 명령으로, 창고에 몰래 들어온 놈들은 전부 잡아들이라고 했거든. 나왈과 리바도스 놈들이 늘 식량 훔치러 도둑을 보내니까.\n채드가 널 풀어줬나 보군? 이상하네... 방금 막 놔주라고 명령하려던 참이었는데.\n네 배는 어디 있지? 멀쩡하냐?";
			link.l1 = "채드? 내가 알기로는 네 보선장이 날 감옥에서 살아 나가게 두지 않았을 거다. 내가 직접 빠져나왔지, 그... 그 리바도스 놈 하나랑 같이.";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "이거 참 흥미롭군. 그런데 어떻게 타르타로스에서 빠져나왔지? 챈드랑 그 놈들하고 한 판 얘기 좀 해야겠는걸...";
			link.l1 = "일방적인 대화가 되겠군, 유감이지만. 다들 죽었어. 채드는 날 영원히 우리에 가두겠다고 협박했지. 나를 리바도스라고 부르면서, 그게 아니란 걸 증명하려면 흑마법사 치미셋을 죽여야 한다고 했어.";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "뭐라고?! 아, 카퍼 이 멍청한 자식아...\n치미셋은 살아 있어야 했고, 채드도 그걸 알고 있었잖아! 그리고 왜 네가 리바도스라고 생각했겠어, 저놈들은 전부 흑인인데?!";
			link.l1 = "치미셋은 죽지 않았어, 스티븐. 그 늙은 마법사가 나를 설득했지. 내가 그를 죽인다 해도, 채드는 절대 내가 타르타로스에서 살아 나가게 두지 않을 거라고...\n";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "";
			link.l1 = "치미셋을 죽이는 대신, 나는 무기와 탄약이 든 상자를 부수고 챈드와 그 놈들의 목숨을 베어버렸지.";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = "좋아! 이거 완전 엿같이 잘됐네! 그런데도 아직 이해가 안 가... 대체 왜 Chad가 이런 짓을 다 한 거지?";
			link.l1 = "가고 있어! 치미셋이 그러더군, 채드가 너를 죽이고 해적 우두머리 자리를 차지하려고 나왈족이랑 거래를 했다고 했어. 나왈족은 네가 자기네 두목 앨런을 죽였다고 확신해서 널 죽이려 해... 앨런 밀턴? 밀러?";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "헛소리 마! 내가 앨런 밀로우를 죽인 게 아니야! 그건 다른 놈이 한 짓이야 - 어쩌면 나왈 녀석들 중 하나일 수도 있지! 난 심지어 지금 그쪽 두목인 도널드 그린스팬일지도 모른다고 생각했어.";
			link.l1 = "아니. 채드가 그를 죽였어. 치미셋이 그 현장을 봤지. 그래서 채드가 치미셋도 죽이려고 했던 거야. 직접 손대긴 겁났던 거지, 치미셋이 귀신이 되어 따라올까 봐, 아니면... 뭐, 나도 잘은 몰라. 어쨌든 그래서 나한테 그 일을 시키려고 했던 거야.";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			dialog.text = "그리고... 왜 채드가 앨런을 죽였겠어?";
			link.l1 = "너를 함정에 빠뜨려서 너를 나왈족의 적으로 만들려고 한 거지. 네가 모든 죄를 뒤집어쓰게끔 소문을 퍼뜨려서, 네가 대중 앞에 얼굴을 드러내는 것조차 위험하게 만들었어.\n그리고 네가 죽으면, 네 살인을 리바도스 탓으로 돌려서 네 해적들이 그들에게 등을 돌리게 만들 생각이었지.";
			link.l1.go = "Chad_die_7";
		break;
		
		case "Chad_die_7":
			dialog.text = "";
			link.l1 = "이 편지를 챈드의 상자에서 찾았어. 읽어 봐. 간접적이긴 해도 확실한 증거로 보이거든.";
			link.l1.go = "Chad_die_8";
		break;
		
		case "Chad_die_8":
			RemoveItems(pchar, "letter_chad", 1);
			dialog.text = "...(읽으면서)... 허! 지금 생각해보니 챠드가 배신한 것도 놀랍지 않군. 그 개자식은 항상 더 많은 권력을 원했으니까.\n하지만 나월 놈들! 내가 앨런을 죽였다고 진심으로 믿다니! 이제 식량값을 두 배로 쳐줄 거다!\n치미셋 말인데... 어차피 놈은 풀어줄 생각이었어. 리바도스랑은 이제 화해할 때가 됐지. 네가 날 놀라게 했구나, 이 친구야, 정말로...";
			link.l1 = "알겠어, 스티븐. 나도 이 상황이 마음에 들지 않아. 나는 이런 정치적 음모에 휘말리려고 여기 온 게 아니야, 널 그리고 네이선리얼 호크를 찾으러 온 거라고--";
			link.l1.go = "Chad_die_9";
		break;
		
		// ноды пересечения
		case "Chad_die_9":
			dialog.text = "호크? 걔 자메이카에 있는 거 아니야?";
			link.l1 = "아니. 이제 마룬 타운은 잭맨이 지배하고 있지. 나도 호크가 여기 온 방법을 알게 됐어. 나처럼 쿠쿨칸의 우상 덕분이더군.";
			link.l1.go = "Chad_die_10";
		break;
		
		case "Chad_die_10":
			dialog.text = "... 대체 무슨 개소리를 하는 거야?";
			link.l1 = "나는 배 타고 여기 온 게 아니야, 스티븐. 믿기 힘들겠지만, 스페인 본토에 어떤 인디언 우상이 있는데, 그게 무슨 문 같은 역할을 해. 그렇게 쳐다보지 마, 나 미친 것도 아니고, 취한 것도 아니야! 이게 어떻게 가능한지 나도 모르겠지만, 사실이야!";
			link.l1.go = "Chad_die_11";
		break;
		
		case "Chad_die_11":
			dialog.text = "...";
			link.l1 = "아마티크 만 남쪽에 있는 미스키토 마을의 스네이크 아이라는 주술사가 호크가 그를 죽이려는 놈들에게서 도망칠 수 있도록 도와줬지. 그 주술사는 호크에게 인디언 우상, 쿠쿨칸의 상징을 보여줬고, 그게 호크를 이 섬으로 데려왔어. 스네이크 아이는 예전에 자기도 똑같은 방식으로 이 섬에 온 적이 있다고 했고, 나한테도 그 방법을 알려줬지.";
			link.l1.go = "Chad_die_12";
		break;
		
		case "Chad_die_12":
			dialog.text = "...";
			link.l1 = "나는 그가 시킨 대로 한밤중에 우상에게 갔지. 그리고 이 우상은, 온종일 평범한 돌로 만들어져 있던 게, 순금으로 변해 있었어! 게다가 이상한 빛이 거기서 뿜어져 나오더군.";
			link.l1.go = "Chad_die_13";
		break;
		
		case "Chad_die_13":
			dialog.text = "...";
			link.l1 = "내가 그 우상을 만지자, 우상 주위에 빛의 원이 생기고, 사방에 불길이 치솟았어. 그리고 난 우상 안으로 빨려 들어갔지. 그 다음 여기, 네 배의 화물칸, 아래층 선수 근처, 파손된 틈에서 내던져졌어...";
			link.l1.go = "Chad_die_14";
		break;
		
		case "Chad_die_14":
			dialog.text = "...";
			link.l1 = "끔찍했어, 정말로. 건너온 뒤에 속도 안 좋고 완전히 지쳐버렸지. 그래도 스네이크 아이가 그 효과를 없애는 특별한 약을 줬어. 그런데 결정적으로, 존나 큰 게한테 공격까지 당했다니까! (심호흡) ";
			link.l1.go = "Chad_die_15";
		break;
		
		case "Chad_die_15":
			dialog.text = "... 좋아, 네 말을 믿어주지.\n그러니까, 게 얘기는 믿겠다는 거다. 저 정의의 섬 주변엔 그런 괴물들이 많지. 우린 죽은 물고기로 유인해서, 선체에 잠긴 틈에 머물게 해.\n도둑놈들 간 떨어지게 만드는 멋진 경비지. 그런데 그 우상 얘기는...\n그 부분도 단번에 거부하진 않겠다; 리바도스 놈들이 배 위에서 이상한 의식을 치렀다는 소문은 들은 적 있으니까... 인간을 제물로 바치는, 그런 인디언 우상에 대한 얘기도 있었지...";
			link.l1 = "맹세코 전부 사실이야.";
			link.l1.go = "Chad_die_16";
		break;
		
		case "Chad_die_16":
			dialog.text = "나는 네가 그걸 믿는다는 건 믿겠다. 하지만 지금은 마법 우상 얘기는 접어두자고.\n얀의 편지에 따르면, 네가 나보고 해적 연맹의 우두머리가 되라고 한다던데?";
			link.l1 = "맞아. 너랑 호크가 사라진 뒤로 많은 게 변했지. 잭맨이 해적 동맹의 우두머리가 되려고 해. 내가 얀과 함께 막지 않으면 진짜 그렇게 될 거야.";
			link.l1.go = "Chad_die_17";
		break;
		
		case "Chad_die_17":
			dialog.text = "";
			link.l1 = "잭맨은 진짜 피비린내 나는 위험한 놈이지. 호크를 덫에 빠뜨린 것도 분명 저 자식 짓이야. 블레이즈 샤프를 죽인 것도 그놈이라고 본다. 널 형제단의 두목으로 세우는 것만이 저놈을 막을 유일한 방법이다.";
			link.l1.go = "Chad_die_18";
		break;
		
		case "Chad_die_18":
			dialog.text = "이봐, 내가 왕관을 쓰는 건 기꺼이 하겠지만, 먼저 이 정의의 섬을 떠나야 해.\n여긴 진절머리가 나. 원래 계획은 덱스터한테 여기 기지를 맡기고 나는 오래 있을 생각 없었는데, 내 배가 부족 놈들이랑 싸우다 불타버렸지.\n그리고 인디언들 무슨 신비한 헛소리 같은 걸로 섬을 나가자고 할 생각은 꿈도 꾸지 마. 난 배 아니면 아무것도 아니야.";
			link.l1 = "스티븐... (한숨) 아직도 그 우상을 찾아야 해! 스네이크 아이가 분명 여기 있을 거라고 맹세했거든. 그런데, 네가 리바도스 놈들이 우상을 써서 의식을 치른다는 걸 안다고 했지. 더 아는 게 뭐 있냐?";
			link.l1.go = "Chad_die_19";
		break;
		
		case "Chad_die_19":
			dialog.text = "아무것도 아니야. 그건 내가 여기 오기 전, 아주 오래 전 일이었지.";
			link.l1 = "이제는 이... 쿠쿨칸의 포탈을 통과하는 게 더 이상 두렵지 않아. 이게 내가 정의의 섬을 벗어나서 배를 구하고, 너를 집에 데려다주는 가장 빠른 길이 될 거야. 다른 건 몰라도, 내가 널 도우려 한다는 것만은 믿어줘.";
			if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary") link.l1.go = "entrance_4";
			else link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения
		
		case "Chad_die_20":
			dialog.text = "알겠어... 하지만 난. 도와줄. 수. 없어. 소문 말고는, 그 우상에 대해선 내가 아는 게 좆도 없어.\n그리고 말인데, 이기적으로 들릴지 몰라도 난 지금 암살 사건 때문에 더 신경이 곤두서 있거든; 채드는 죽었지만, 나르왈 놈들이 날 죽이려는 걸 포기할 거라고는 전혀 생각 안 해.\n네가 날 살려야 하고 이미 이 난장판에 휘말렸으니, 이 음모를 조사해 줬으면 한다.\n넌 신참이라 내 부하들이 절대 갈 수 없는 곳에도 갈 수 있고, 만날 수 없는 놈들도 만날 수 있지. 채드의 동료들을 찾아서 내게 데려와. 아니면 죽여도 상관없고, 난 신경 안 써.\n치미셋하고 얘기해 봐; 그 늙은 흑인은 겉으로 보이는 것보다 더 많은 걸 알고 있어. 네 우상에 대해서도 뭔가 더 알지도 몰라...\n나르왈 놈들 조심하고, 그놈들 구역 넘나들 땐 반드시 최신 암호를 알아둬—매주 바뀌거든.\n이 모든 게 끝나면 내 항해 일지를 줄게. 정의의 섬을 오가려면 꼭 필요한 항로와 정보가 담겨 있어.\n가. 음모자들을 찾아. 질서를 되찾아. 그리고 날 살려둬.\n이제... 덱스터는 감옥에서 시체 치워야 하고... 타르타로스는 새 간수가 필요하고... 난 럼주가 좀 필요하군. 젠장, 오늘 하루 정말 지랄맞네.";
			link.l1 = "...";
			link.l1.go = "Chad_die_21";
		break;
		
		case "Chad_die_21":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.questTemp.LSC.rvd_friend = "true"; //флаг на проход по кораблям ривадос
			// // ривадосы не будут останавливать где просят пароль
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "Friend"; //ноду Чимисету
			pchar.quest.LSC_Eddy.win_condition.l1 = "location";
			pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
			pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; //на разговор с Эдди
			AddQuestRecord("SharkHunt", "10");
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			for (i=7; i<=12; i++)
			{
				sld = CharacterFromID("RivadosSold_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			for (i=4; i<=8; i++)
			{
				sld = CharacterFromID("RivadosProt_"+i);
				LAi_SetWarriorType(sld);
				LAi_warrior_SetStay(sld, true);
			}
			AddSimpleRumourCityTip("Would you believe it? Someone has killed the Admiral's gaoler, Chad Kapper! No doubt the work of that Rivados wizard he locked up, Chimiset...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I heard that Chad Kapper is dead, but there's been no official statement and his body hasn't turned up. Perhaps, the Admiral simply gave him a secret mission...?", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("I haven't seen our gaoler, Chad Kapper, lately. Some say he was killed, some say he's still alive. The only thing people agree on is that no one has seen him...", "LostShipsCity", 7, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that the Admiral doubled provision prices for the Narwhals! That pirate is truly reckless!", "LostShipsCity", 7, 3, "LSC", "");
		break;
		
			case "Mary_Die":
			dialog.text = "그래, 뭐 가지고 왔나, "+pchar.name+"나르왈 놈들 소식 있냐?";
			link.l1 = "그래. 스티븐, 음모가 드러났고 음모자들은 모두 죽었다는 걸 알면 기뻐할 거야. 이제 나는 모든 걸 알고 있어.";
			link.l1.go = "Mary_Die_1";
		break;
		
		case "Mary_Die_1":
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) dialog.text = "총소리 들었을 때부터 그럴 줄 알았지... 나랑 얘기해.";
			else dialog.text = "그래? 그거 다행이군! 말해 봐.";
			link.l1 = "이건 다 네 보스운, 채드 캐퍼가 꾸민 짓이야. 타르타로스 감방에서 앨런 밀로우를 죽이고, 네가 한 짓이라고 거짓 소문을 퍼뜨렸지. 나왈 선원들은 분노했어—특히 앨런의 여자친구, 레드 메리는 더더욱...";
			link.l1.go = "Mary_Die_2";
		break;
		
		case "Mary_Die_2":
			dialog.text = "";
			link.l1 = "메리는 복수심에 불타 있었고, 채드 카퍼는 그 분노를 이용했지. 둘이서 너를 암살할 계획을 세웠다. 매일 저녁 산 아우구스틴호의 선미 갤러리 주변을 산책하는 버릇이 있다는 것도 알고 있더군...";
			link.l1.go = "Mary_Die_3";
		break;
		
		case "Mary_Die_3":
			dialog.text = "크하! 그 버릇은 고쳐야겠군... 계속해.";
			link.l1 = "그들은 계획을 실행하려면 장거리 사격이 가능하고 정확한 소총이 필요했지. 그래서 아돌프 바르비에르라는 놈이 그걸 제공했어. 하지만 그의 슈투첸은 주세페 파지오에게 전당 잡혀 있었지. 그래서 메리와 채드는 그걸 다시 사야 했고, 아돌프가 슈투첸을 되찾았지...";
			link.l1.go = "Mary_Die_4";
		break;
		
		case "Mary_Die_4":
			dialog.text = "";
			link.l1 = "그들은 전직 왕실 사냥꾼 마르첼로 사이클롭스를 고용해서 총을 쏘게 했지. 그 다음엔 메리가 그를 죽이고, 그의 시체와 소총을 리바도스가 공격의 주범이라는 증거로 쓸 계획이었어. 사이클롭스는 혼혈이었지.";
			link.l1.go = "Mary_Die_5";
		break;
		
		case "Mary_Die_5":
			dialog.text = "이 모든 게 챈드의 교활한 머리에서 나온 거지... 영리한 놈이야!";
			link.l1 = "그리고 결국, 나왈과 해적들이 리바도스 일족을 공격해서 박살냈겠지. 채드는 제독이 되고 메리는 그의 여자가 됐을 거야. 하지만... 몇 번 같이 뒤엉킨 뒤엔, 아마 채드가 그냥 메리 목을 따 버렸을 거다, 너무 많은 걸 알아버렸으니까.";
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack")) link.l1.go = "Mary_Die_6a";
			else link.l1.go = "Mary_Die_6";
		break;
		
		case "Mary_Die_6":
			dialog.text = "";
			link.l1 = "어쨌든, 이제 끝났지. 아돌프는 말이 별로 없어서 선실에서 바로 죽여버렸어. 메리랑 외눈박이도 아돌프한테서 슈투첸을 가지러 왔길래 같이 처리했지.";
			link.l1.go = "Mary_Die_7";
		break;
		
		case "Mary_Die_7":
			dialog.text = "그래서, 그놈들 전부 산타 플로렌티나 안에서 죽어 있다는 거냐? 아무도 모른단 말이지?";
			link.l1 = "그래. 셋 다 그렇지 - 그리고 우리 말고는 아무도 몰라.";
			link.l1.go = "Mary_Die_8";
		break;
		
		case "Mary_Die_8":
			dialog.text = "좋아. 목격자가 있으면 일이 복잡해지지. 시체는 내가 처리할게. 너 잘했어, "+pchar.name+"! 네가 내 선원이었으면, 내가 널 일등항해사로 삼았을 거다.";
			link.l1 = "칭찬이 높군, 상어. 고맙다. 아, 이 편지들도 좀 봐라. 내가 키클롭스랑 메리 시체에서 챙긴 거다...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Have you heard that? Our scrappy madcap Red Mary has disappeared. I wouldn't be surprised if she's dead...", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary has disappeared. You heard about that?", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("Mary Casper has vanished. Some people say that she's still inside her cabin, but I don't believe it; it's been a long time since I saw a light in her window.", "LostShipsCity", 10, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that Red Mary was murdered. Poor girl! Yes, she was a tough sort, but everybody loved her. Who could have done such a thing?", "LostShipsCity", 10, 1, "LSC", "");
		break;
		
		case "Mary_Die_6a":
			dialog.text = "";
			link.l1 = "어쨌든 이제 끝났어. 아돌프는 말이 별로 없어서, 그의 선실에서 바로 죽여버렸지. 그리고 메리랑 외눈박이도 아돌프한테 슈투첸을 가지러 왔을 때 처리했어.";
			link.l1.go = "Mary_Die_7a";
		break;
		
		case "Mary_Die_7a":
			dialog.text = "에바호에서 싸움을 시작한 건 아쉽군. 너 때문에 나왈 놈들이 열받았을 거야, 자기네 사람 죽였으니. 당분간은 걔들 근처 얼씬도 하지 마라, 화해할 때까지는.\n그래도 전체적으로는 잘했어, "+pchar.name+"! 네가 내 선원이었으면, 내가 바로 너를 내 첫 번째 부선장으로 삼았을 거다.";
			link.l1 = "높이 평가한다, 상어야. 고맙다. 아, 이 편지들도 좀 봐라. 내가 키클롭스랑 메리 시체에서 챙긴 거다...";
			link.l1.go = "Mary_Die_9";
			AddSimpleRumourCityTip("Such a massacre you've committed! The Narwhals won't forget it!", "LostShipsCity", 5, 2, "LSC", "");
			AddSimpleRumourCityTip("I understand killing Cyclops and two Narwhal bandits, but... the girl. Why did you have to kill poor Mary?", "LostShipsCity", 7, 5, "LSC", "");
		break;
		
		case "Mary_Die_9":
			RemoveItems(pchar, "letter_chad", 1);
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "가엾은 메리? 설마 그 창녀를 불쌍하게 여기고 있는 건 아니겠지.";
			link.l1 = "그래. 채드는 그녀를 속이고, 감정과 타고난 성급함을 이용했지... 그녀가 그의 야망 때문에 죽을 필요는 없었어.";
			link.l1.go = "Mary_Die_10";
		break;
		
		case "Mary_Die_10":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			CloseQuestHeader("SharkHunt");
			bDisableFastReload = false; // belamour legendary edition
			dialog.text = "기분이 그렇게 더럽게 찝찝하면 줄리안 형제한테 가서 촛불이나 켜고 와라. 난 솔직히 그 계집이 죽어서 존나 속이 시원하다.\n됐고, 이 얘긴 그만하자. 네가 도와줘서 고맙다. "+pchar.name+". 이제 내 지원을 믿어도 된다. 네 훌륭한 일에 보답하고 싶다. 여기 오백 두블룬이다.";
			link.l1 = "고마워, 스티븐...";
			link.l1.go = "LSC_navy";
			AddSimpleRumourCityTip("They say the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you're the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант N---------------------------------------------------
		case "entrance":
			dialog.text = "난 너를 모른다. 뭐 원하는 거냐?";
			link.l1 = "물론, 모를 수밖에. 우리 만난 적 없으니까, 나도 이제 막 도착했지. 안녕, 스티븐. 너를 찾고 있었어.";
			link.l1.go = "entrance_1";
		break;
		
		case "entrance_1":
			dialog.text = "나를 찾으러 온 놈들이 많았지. 대부분 지금은 묘지에 누워 있어. 그 꼴 나기 싫으면, 네가 왜 나를 찾았는지나 말해봐라.";
			link.l1 = "우리에게 공통된 친구가 있지. 자, 이 편지를 받아. 얀 스벤손이 쓴 거야. 올드 포레스트 데블이 나보다 훨씬 잘 설명해 줄 거다.";
			link.l1.go = "entrance_2";
		break;
		
		case "entrance_2":
			RemoveItems(pchar, "letter_svenson", 1);
			PlaySound("interface\important_item.wav");
			dialog.text = "(읽으면서)... 흠. 그거라면 설명이 되겠군. 난 네가 블레이즈를 죽인 죄로 나한테 흑점을 주러 온 줄 알았지 - 요즘 그 일 하려고 안달난 해적들이 많거든.\n네 배는 바깥 고리에 두고 왔나? 그리고 내가 여기 있는 건 어떻게 알았지?";
			link.l1 = "나 아니야. 완전 우연이었지. 그리고 블레이즈에 관해서는... 나랑 얀 둘 다 네가 그 죽음에 책임 있다고 생각 안 해.";
			link.l1.go = "entrance_3";
		break;
		
		case "entrance_3":
			dialog.text = "맞아, 나는 아니야. 하지만 누군가는 형제단이 내가 그랬다고 믿게 만들고 싶어 해.";
			link.l1 = "재밌군... 있잖아, 난 여기 네이선리얼 호크를 찾으러 왔는데, 대신 네가 있네, 헤!";
			link.l1.go = "Chad_die_9";
		break;
		
		case "entrance_4":
			dialog.text = "그건 이 섬의 고참 놈들이랑 얘기해 봐야 할 거다. 리바도스의 마법사, 치미셋을 찾아가 봐. 그 늙은 흑인 놈이 겉으로 보이는 것보다 훨씬 더 많이 알고 있지.";
			link.l1 = "그 마법사는 어디서 찾을 수 있지?";
			if (pchar.questTemp.LSC == "mary") link.l1.go = "mary";
			else link.l1.go = "entrance_5";
		break;
		
		case "entrance_5":
			dialog.text = "내 감옥, 타르타로스 호 안에 있다. 곧 풀어주려고 했지; 이제 리바도스와의 관계를 개선할 때거든.\n직접 명령을 전달해도 돼! 타르타로스 호로 가서 간수 챈드 캐퍼에게 내가 치미셋을 풀어주라고 했다고 전해라.\n아니, 그보다 먼저 치미셋을 직접 만나보는 게 낫겠군. 내가 보냈다고 말하고, 입이 가볍다면 풀어주겠다고 해라. 네가 원하는 걸 분명히 말해줄 거다.";
			link.l1 = "흠... 타르타로스는 어디 있지?";
			link.l1.go = "entrance_6";
		break;
		
		case "entrance_6":
			dialog.text = "내 거처를 나가서, 다리를 건너고, 왼쪽으로 돌아, 프리깃 캐롤라인을 지나 갈레온 글로리아로 가서 에스메랄다에 도착해. '상점'이라고 적힌 표지판을 찾아서 그 아래 문으로 들어가. 배의 선수 쪽 문을 지나면 타르타로스에 도착할 거야.\n에스메랄다에서는 조심해라, 거긴 나왈 녀석들 구역이야. 다른 놈들도 방문할 수는 있지만, 그 경비병들 건드리지 말고 문제 일으키지 마라.";
			link.l1 = "이 리바도스랑 나왈은 누구야?";
			link.l1.go = "entrance_7";
		break;
		
		case "entrance_7":
			dialog.text = "그들은 정의의 섬에 처음 정착한 자들의 후손인 씨족들이야. 나왈족은 주로 영국, 네덜란드, 프랑스계 놈들이고, 리바도스는 전부 흑인들이지.\n각 씨족마다 우두머리가 있고, 각자 몇 척의 배를 소유해서 그게 곧 자기들만의 영역이 돼. 외부인은 함부로 들어갈 수 없어.\n나왈이나 리바도스 영역에 들어가려면 올바른 암호를 알아야 하는데, 그 암호는 매주 바뀐다.";
			link.l1 = "알아둬서 좋군, 그런데 내가 감옥 안에 들어갈 수 있게 해줄까?";
			link.l1.go = "entrance_8";
		break;
		
		case "entrance_8":
			dialog.text = "그럴 거다. 자, 이게 열쇠니까, 채드가 내가 보냈다는 걸 알 거야. 잃어버리지 마라.";
			link.l1 = "고맙다. 그... 그 치미셋이랑 얘기하고 결과 가지고 돌아올게.";
			link.l1.go = "entrance_9";
		break;
		
		case "entrance_9":
			DialogExit();
			GiveItem2Character(pchar, "key_capper");
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Chimiset");
			sld.dialog.currentnode = "prisoner"; //даем ноду Чимисету
			sld.quest.chimiset_die = "true";
			ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
			LAi_SetGroundSitTypeNoGroup(sld);
			sld = characterFromId("Capper");
			sld.dialog.currentnode = "prisoner"; //даем ноду Капперу
			LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true);//запретить драться
			// прерывания на локаторы тартаруса
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
			pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
			pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
			AddQuestRecord("SharkHunt", "19");
		break;
		
		case "entrance_10":
			dialog.text = "타르타로스에 가 본 적 있어?";
			link.l1 = "그래. 네 명령을 채드에게 전했고 치미셋하고도 얘기했어.";
			link.l1.go = "entrance_11";
		break;
		
		case "entrance_11":
			dialog.text = "마법사가 너한테 뭐라고 했냐?";
			link.l1 = "아, 그래. 그가 내가 찾고 있는 우상을 어디서 찾을 수 있는지 말해줬지. 산 헤로니모호에 있었어, 나르왈 영토 근처에서 몇 년 전에 침몰한 배야.";
			link.l1.go = "entrance_12";
		break;
		
		case "entrance_12":
			dialog.text = "하하하! 그래서 네 마법 우상은 이제 바닷속에 처박혔구나, 응? 뭐야, 이 친구야, 이제 우리랑 같이 꼼짝없이 있어야겠네.";
			link.l1 = " 내가 우상에 접근할 방법을 찾아볼게. 그리고 치미셋이 카퍼를 믿지 말라고 했어, 왜냐면 그가 채드가 앨런 밀로우라는 놈을 죽이는 걸 봤다고 하더군--\n";
			link.l1.go = "entrance_13";
		break;
		
		case "entrance_13":
			dialog.text = "뭐라고?! 채드가 앨런을 죽였다고? 치미셋 그 녀석이 거짓말하는 거야, 그럴 리가 없어!";
			link.l1 = "스티브, 치미셋은 완전히 겁에 질려 있었어. 만약 거짓말이었다면, 정말 기가 막히게 잘 속인 거야...";
			link.l1.go = "entrance_14";
		break;
		
		case "entrance_14":
			dialog.text = "젠장, 이게 다 뭐야!\n앨런이 죽은 일로 내가 나왈 선원들이랑 사이가 틀어졌는데, 몇몇은 내가 범인이라고까지 생각하고 있다니까. 그런데 알고 보니 내 부하 중 한 놈이 그 짓을 저질렀다고?!";
			link.l1 = "네가 안 한 일들까지 죄다 뒤집어쓰는구나.";
			link.l1.go = "entrance_15";
		break;
		
		case "entrance_15":
			dialog.text = "눈치챘지.";
			link.l1 = "글쎄, 더 재밌는 소식이 있지: 치미셋이 네 놈 부하 몇몇이 널 죽일 계획을 세우는 걸 엿들었대. 놈은 풀어주고, 단둘이 있을 때만 더 얘기해 주겠다고 하더라.";
			link.l1.go = "entrance_16";
		break;
		
		case "entrance_16":
			dialog.text = "좋아. 오늘 일이 너무 순조롭다 싶더라니.\n치미셋이 뭐라고 자세히 말해줬나?";
			link.l1 = "아니. 걔는 채드를 너무 두려워해. 자기 안전이 먼저 보장돼야 한대.";
			link.l1.go = "entrance_17";
		break;
		
		case "entrance_17":
			dialog.text = "좋아. 리바도스 놈들한테 내가 치미셋을 만나고 싶다고 전해. 그 자가 무슨 말을 할지 두고 보자고. 내 목숨을 노린 일에 관해서는... 조심하는 수밖에 없지.\n그래서, 이제 뭘 할 생각이냐, "+pchar.name+"?";
			link.l1 = "아직 딱히 특별한 건 없어. 정의의 섬을 좀 돌아다니면서 여기 놈들 좀 알아볼 생각이야. 그러다 보면 여기서 빠져나갈 방법이 떠오를지도 모르지. 그리고 네이선리얼 호크를 찾아야 해, 내가 여기 온 이유가 바로 그 놈 때문이거든.";
			link.l1.go = "entrance_18";
		break;
		
		case "entrance_18":
			dialog.text = "그래. 이 섬에서 나갈 방법을 찾으면 꼭 나한테 들르라고. 내가 항로 지침이 적힌 뤼터를 줄 테니, 그걸로 배를 몰고 다시 정의의 섬에 올 수 있을 거야. 그리고 네가 필요로 할 다른 정보도 준비해두지.";
			link.l1 = "좋아. 꼭 찾아갈게, 스티브!";
			link.l1.go = "entrance_19";
		break;
		
		case "entrance_19":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			// прерывание на вызов к Акуле
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			pchar.quest.LSC_GotoShark.win_condition.l1.date.hour  = 9.00;
			pchar.quest.LSC_GotoShark.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
			pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
			pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
			AddQuestRecord("SharkHunt", "21");
		break;
		
		case "entrance_20":
			dialog.text = ""+pchar.name+", 나쁜 소식이야: 치미셋은 죽었고 챠드 캐퍼는 사라졌어.";
			link.l1 = "젠장! 그래서 결국 채드가 그 늙은 마법사를 죽였군...";
			link.l1.go = "entrance_21";
		break;
		
		case "entrance_21":
			dialog.text = "그런 것 같군. 상황이 시간이 갈수록 더 악화되고 있어. 블랙 에디랑 휴전 준비 다 해놨는데, 이제는...\n이제 리바도스 놈들이랑 평화는 물 건너갔지. 그런데 말인데, 네가 치미셋 죽기 전에 그랑 얘기한 거 리바도스 놈들이 다 알아. 이제 널 내 부하로 여긴다더라. 그러니까 그놈들 근처엔 얼씬도 하지 마.";
			link.l1 = "훌륭하군.";
			link.l1.go = "entrance_22";
		break;
		
		case "entrance_22":
			dialog.text = "더 있어. 나는 정의의 섬 중재자이자 외교관인 주세페 파지오한테서 편지를 받았어. 그자가 한밤중에 캐롤라인 호에 있는 자기 선실로 오라고 초대했지.\n그리고 반드시 혼자 오라고 했어. 내 목숨이 위태롭고, 내 부하들은 믿을 수 없다고 말이야.\n이치에 맞긴 해. 치미셋이 우리 선원 중에 배신자가 있다고 경고했으니까. 그래도 뭔가 수상쩍은 냄새가 진하게 나. 한밤중에, 혼자서라니...\n평소라면 그 뚱보가 나한테 오지. 네 도움이 필요할 것 같다. "+pchar.name+"얀은 너를 수완 있고 용감한 놈, 그리고 뛰어난 싸움꾼이라고 하더군. 자정에 있을 회합까지 나를 호위해 줬으면 한다.";
			link.l1 = "물어볼 필요 없어, 스티븐. 나도 할 거야. 나도 이 초대가 마음에 안 들어 – 거의 확실히 함정이거든.";
			link.l1.go = "entrance_23";
		break;
		
		case "entrance_23":
			dialog.text = "그럴지도 모르지. 내가 틀렸길 바라지만, 그래도 대비는 해두는 게 낫지. 네가 함께 있어서 든든하다\n자정에 산 아우구스틴호의 주 갑판으로 와라. 파지오를 만나러 가자. 캐롤라인호까지는 금방이니까.";
			link.l1 = "그럼 자정이다. 무장 단단히 하고 있겠다.";
			link.l1.go = "entrance_24";
		break;
		
		case "entrance_24":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
			SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
			AddQuestRecord("SharkHunt", "22");
		break;
		
		case "caroline":
			dialog.text = "좋아, "+pchar.name+", 시간 낭비하지 말자. 저 뚱뚱한 파지오 영감이 뭐라고 하는지 들어보자고. 내 옆에 딱 붙어 있어.";
			link.l1 = "나도 함께할게, 스티브. 무기는 항상 준비해 둬...";
			link.l1.go = "caroline_1";
		break;
		
		case "caroline_1":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;
		
		case "caroline_2":
			dialog.text = "그 뚱뚱한 놈 어디 갔지? 어디로 사라진 거야? 손님 대접이 이게 뭐냐! 저 자식 보여? "+pchar.name+"? 난 몰라.\n아마, 그의 상자들을 뒤져봐야겠지, 거기 있을지도 모르니까... 아니면 최소한 고생한 보상은 챙길 수 있겠지, 하하!";
			link.l1 = "크크, 세상에 그놈이 들어갈 만한 상자가 있을까 싶다만... 쉿! 스티븐! 뭔가 들렸어...";
			link.l1.go = "caroline_3";
		break;
		
		case "caroline_3":
			dialog.text = "... 준비해라, "+pchar.name+".";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LSC_Caroline_DlgExit_3");
		break;
		
		case "caroline_5":
			dialog.text = "아악! 해냈다... 젠장, 진짜로 당하는 줄 알았잖아.";
			link.l1 = "난 이것보다 더 험한 일도 겪어봤지만, 이번엔 나도 인정하지. 정말 아슬아슬했어. 치미셋 말이 맞았군. 채드는 배신자였어. 그런데 저놈들을 지휘하던 그 계집애는 누구였지?";
			link.l1.go = "caroline_6";
		break;
		
		case "caroline_6":
			dialog.text = "메리 캐스퍼, 일명 붉은 메리. 고 앨런 밀로우의 연인이었지.\n채드는 내 자리를 차지하려고 여기 온 거라는 건 알겠는데, 메리는 대체 왜 여기 있었던 거지?";
			link.l1 = "그 여자가 앨런의 연인이었다면, 뻔하지. 앨런의 죽음에 복수하고 싶었던 거야. 불쌍한 계집애, 자기가 앨런을 죽인 바로 그 놈이랑 한패가 되어 싸우고 있다는 것도 몰랐지...";
			link.l1.go = "caroline_7";
		break;
		
		case "caroline_7":
			dialog.text = "그럴 만도 하지. 이런, 내가 이 일에 대해 나왈 놈들한테 제대로 갚아줄 거다! 식량 공급 끊어버리고 굶어 죽게 놔둘 거야!\n걔네가 뭘 어쩌겠어? 우리를 공격한다고 해도 산 아우구스틴은 어떤 포위도 버틸 수 있지! 분명히 후회하게 될 거다. 그리고 파지오 그 뚱땡이 자식 엉덩이는 내 의자 뒤 벽에 박아버릴 거야!";
			link.l1 = "스티브, 스티브, 잠깐만! 만약... 만약 이 일에 나왈족은 아무 관련이 없다면 어쩌지? 채드는 네 해적 중 한 명이었지, 나왈족이 아니었어. 채드가 앨런을 죽였고, 채드가 치미셋을 죽였고, 채드가 너에 대한 소문을 퍼뜨렸어. 이 모든 일이 채드로 시작해서 채드로 끝난다면?";
			link.l1.go = "caroline_8";
		break;
		
		case "caroline_8":
			dialog.text = "... 젠장, 너. "+pchar.name+", 하지만... 네 말이 일리가 있군.\n좋아, 내가 너한테 빚진 게 있으니 이 일 조사할 기회를 주겠다. 만약 네가 나왈족이 이 일에 관여하지 않았다는 걸 증명하면, 전쟁은 철회하겠다.\n넌 내 신뢰를 얻었고, 앞으로 무슨 일이든 내 도움을 믿어도 된다. 내가 아직 배가 있었다면 널 갑판장으로 삼았을 거다.";
			link.l1 = "여기서 나가면 해적 연맹의 우두머리를 맡아서 내 은혜를 갚으면 되지. 가서 좀 쉬어, 나는 이 선실에서 단서가 더 있는지 찾아볼 테니. 그리고 내가 없는 동안 죽기만은 하지 마라!";
			link.l1.go = "caroline_9";
		break;
		
		case "caroline_9":
			dialog.text = "헤, 꿈도 꾸지 마라. 이 시체들 치우라고 사람 시킬 거다. 오늘 밤엔 게들이 배불리 먹겠군! (침 뱉으며) 잘 가라, 내 친구.";
			link.l1 = "잘 자.";
			link.l1.go = "caroline_10";
		break;
		
		case "caroline_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
			AddQuestRecord("SharkHunt", "24");
		break;
		
		case "narval":
			dialog.text = "그래, "+pchar.name+", 새로 알게 된 거라도 있어?";
			link.l1 = "복수는 그만둬도 돼, 스티븐. 너한테 음모를 꾸민 건 너와 캐롤라인에서 싸웠던 메리랑 그 녀석들뿐이야. 내 생각엔 메리가 녀석들을 꼬드겨 우리를 공격하게 한 것 같아. 파지오는 어쩔 수 없이 너한테 초대장을 보낸 거였어. 내가 그의 선실에서 많은 걸 설명해 주는 편지를 찾았지. 읽어봐.";
			link.l1.go = "narval_1";
		break;
		
		case "narval_1":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = "(읽으면서)... 흠... 이게 바로 파지오답지: 자기 목숨만 챙기는 놈이지. 결국 처음부터 끝까지 전부 챈드 짓이었군...";
			link.l1 = "그리고 다 그놈이 제독이 되고 싶어서 그런 거지. 나는 도널드 그린스팬을 만났어. 그 자식은 자기나 자기 부하 누구도 너한테 반역을 꾸민 적 없다고 맹세하더라.";
			link.l1.go = "narval_2";
		break;
		
		case "narval_2":
			dialog.text = "걔를 믿냐?";
			link.l1 = "그래. 도널드가 알런 살인 누명을 벗겨줄 거야. 직접 찾아와서 얘기할 준비가 되어 있지.";
			link.l1.go = "narval_3";
		break;
		
		case "narval_3":
			dialog.text = "좋아. 난 싸움질을 좋아하긴 하지만, 이 시점에서 전쟁은 아무 의미도 없지. 이미 너무 많은 놈들이 죽었고, 이 모든 걸 시작한 자들은 이제 게밥이 됐으니까.\n도널드가 사과할 준비가 됐다고? 좋아, 나왈들과의 관계라도 어떻게든 살려보자고. 리바도스 쪽은 치미셋 때문에 우리와는 끝난 것 같으니.";
			link.l1 = "이번이 네가 평화를 얻을 수 있는 유일한 기회일지도 몰라.";
			link.l1.go = "narval_4";
		break;
		
		case "narval_4":
			dialog.text = "이미 나를 설득했어. 도널드에게 내가 그를 만나 화해할 준비가 됐다고 전해 줘.";
			link.l1 = "가는 중이다.";
			link.l1.go = "narval_5";
		break;
		
		case "narval_5":
			dialog.text = "기다려, "+pchar.name+". 잘했으니 보수도 제대로 받아야지. 여기 오백 두블룬이다.";
			link.l1 = "고맙다!";
			link.l1.go = "LSC_navy";
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("SharkHunt", "27");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "shark_16"; // ноду Дональду Гринспи
			SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		// ----------------------------------------вариант M----------------------------------------------------
		case "mary":
			dialog.text = "내 감옥 타르타로스에 있다. 거기로 가서 직접 볼 수 있지. 열쇠는 내가 줄게. 우리 간수 챈드 카퍼에게 말해봐--";
			link.l1 = "잠깐, 스티븐. 카퍼에 대해 알아둬야 할 게 있어...";
			link.l1.go = "mary_1";
		break;
		
		case "mary_1":
			dialog.text = "... 듣고 있지...";
			link.l1 = "다른 말로 어떻게 해야 할지 모르겠는데... 카퍼가 널 죽이려고 음모를 꾸미고 있어.";
			link.l1.go = "mary_2";
		break;
		
		case "mary_2":
			dialog.text = "... 내 오랜 동료 중 한 놈을 배신자로 몰아세우는 데는 그만한 빌어먹을 이유가 있어야 할 거다.";
			link.l1 = "내가 전부 다 이야기해 주지--";
			link.l1.go = "mary_3";
		break;
		
		case "mary_3":
			dialog.text = "빨리 말해.";
			link.l1 = "물에 잠긴 화물칸에서 정신을 차리고, 선체에 난 구멍으로 빠져나와 난파선들 사이를 헤엄치며 올라갈 곳을 찾았지. 결국 선수 쪽 문으로 들어갈 수 있는 난파선을 하나 발견했어. 거기서 빨간 재킷을 입은 어떤 아가씨와 건장한 놈 둘이 싸우고 있더군--";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1.go = "mary_4"; // Мэри жива
			else link.l1.go = "mary_15";
		break;
		
		case "mary_4":
			dialog.text = "누가 레드 메리를 죽이려고 했다고?";
			link.l1 = "그런 것 같아. 내가 그녀랑 같이 그 놈들을 끝장내줬고, 그 뒤에 꽤 흥미로운 대화를 나눴지... 그런데 말이야, 스티브, '나월'이랑 '리바도스'가 대체 누구야? 그녀가 여러 번 언급하더라고.";
			link.l1.go = "mary_5";
		break;
		
		case "mary_5":
			dialog.text = "그들은 정의의 섬에 처음 정착한 자들의 후손인 씨족들이야. 나왈족은 주로 영국, 네덜란드, 프랑스 혈통이고, 리바도스는 모두 흑인들이지.\n각 씨족마다 우두머리가 있고, 각자 여러 척의 배를 소유해서 외부인 출입이 제한된 자기들만의 구역을 가지고 있어.\n나왈이나 리바도스 구역을 방문하려면 올바른 암호를 알아야 하고, 그 암호는 매주 바뀐다.";
			link.l1 = "아-아, 알겠군... 그런데 메리는 나르왈이냐?";
			link.l1.go = "mary_6";
		break;
		
		case "mary_6":
			dialog.text = "그래. 그래서, 그 여자가 뭐라고 했지?";
			link.l1 = "채드 카퍼가 당신에게 붙잡힌 그녀의 연인 앨런 밀로우를 죽였어. 그 후에 네가 그 살인을 저질렀다는 소문을 퍼뜨렸지. 메리의 복수심을 자기 목적을 위해 이용하려고 했어.";
			link.l1.go = "mary_7";
		break;
		
		case "mary_7":
			dialog.text = "채드가 앨런을 죽였다고?! 그런데 왜?";
			link.l1 = "네 탓으로 돌리고, 너에게 나왈족을 적대적으로 만들려는 거지. 카퍼의 궁극적인 목표는 널 제거하고 제독 자리를 차지하는 거야. 메리는 그의 계획에 가담하는 것도, 그의 연인이 되는 것도 거부했지. 그래서 그는 부하들에게 메리를 죽이라고 명령했어.";
			link.l1.go = "mary_8";
		break;
		
		case "mary_8":
			dialog.text = "그리고 그 여자가 이 모든 걸 너한테 다 말했다고?";
			link.l1 = "그래. 거짓말하는 것 같진 않았어. 게다가 채드 캐퍼한테서 온 편지도 줬지. 이미 읽어봤어. 여기.";
			link.l1.go = "mary_9";
		break;
		
		case "mary_9":
			RemoveItems(pchar, "letter_chad_1", 1);
			dialog.text = " (읽으면서) ... 그래, 이건 분명 챈드의 필체야. 아악! 믿을 수가 없군! 개자식! 배신자 놈!\n저 놈 창자를 끄집어내서 거기에 매달아 죽여주마! 레이튼! 놈들과 함께 다섯 명 데려와서--\n잠깐, 다시 생각해보니... 그만둬, 레이튼. 해산! 이번엔 머리를 써서 처리하지.\n리바도스 놈들과 관계를 개선할 방법을 찾고 있었는데, 이게 기회가 될 수 있겠군.\n그놈들 마법사 치미셋이 타르타로스, 그러니까 이 지역 감옥에 갇혀 있다. 리바도스 놈들이 자기 사람을 구출하게 두고, 그 과정에서 챈드를 죽이게 만들 거다.\n레이튼! 타르타로스로 가서 우리 경비병 전부 그녀 상갑판에서 빼와! "+pchar.name+", 중요한 일이 있다. 리바도스의 두목 블랙 에디를 찾아가서 협상해라--";
			link.l1 = "나라고? 하지만 여기 아는 사람 아무도 없어!";
			link.l1.go = "mary_10";
		break;
		
		case "mary_10":
			dialog.text = "곧 알게 될 거야, 에디부터 시작해서 말이지. 그 자가 리바도스 일족 전체의 우두머리거든.\n우리 대신 외교를 할 사람으론 네가 최고야. 내 해적들 중 누구도 에디와 면담할 기회조차 못 얻을 거고... 솔직히 말해서, 말재주도 별로 없는 놈들뿐이거든.";
			link.l1 = "(한숨) 알겠다, 가서 그... 블랙 에디를 보지.";
			link.l1.go = "mary_11";
		break;
		
		case "mary_11":
			GiveItem2Character(pchar, "key_capper");
			Log_Info("You have received 50 doubloons");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "gold_dublon", 50);
			dialog.text = "이 열쇠를 가져가서 그에게 줘라. 이건 타르타로스의 모든 문을 열 수 있다. 흑인들이 치미셋을 구하려면 이게 필요할 거다.\n그리고 이 오십 두블론도 가져가라. 곧 알게 될 또 다른 현지인은 캐롤라인의 중재자이자 외교관인 주세페 파지오다. 두블론을 가지고 이번 주 리바도스 구역의 암호를 사라. 파지오는 새 암호가 정해질 때마다 그걸 구해두는 게 일이거든.\n다음으로 프로텍터에게 가라. 거긴 블랙 에디의 거처다. 그에게 채드 캐퍼가 나와의 명령을 끊고 나왈스에 합류했으며, 오늘 치미셋을 죽이려 한다고 전해라.\n그에게 열쇠를 주고, 강한 인원을 이끌고 타르타로스를 공격하라고 해라.\n이렇게 하면 일석이조다. 리바도스 놈들은 우리를 동맹으로 여기게 되고, 캐퍼는 흑인들 손에 죽게 될 거다. 다 알아들었지?";
			if (pchar.questTemp.LSC.Mary == "alive")// Мэри жива
			{
				link.l1 = "나도 그렇게 생각해. 그런데 보호자랑 캐롤라인은 어디서 찾아야 하지?";
				link.l1.go = "mary_12";
			}
			else
			{
				link.l1 = "이봐, 스티브, 그 리바도스랑 나왈이 누구인지 말해 봐. 난 아직 걔네들에 대해 아무것도 몰라.";
				link.l1.go = "mary_12_1";
			}
		break;
		
		case "mary_12_1":
			dialog.text = "그들은 정의의 섬에 처음 정착한 자들의 후손인 씨족들이야. 나왈족은 주로 영국, 네덜란드, 프랑스 혈통이고, 리바도스는 모두 흑인들이지.\n각 씨족마다 두목이 있고, 각자 여러 척의 배를 소유해서 그게 곧 외부인 출입이 제한된 자기네 영토가 돼.\n나왈이나 리바도스 영토를 방문하려면 올바른 암호를 알아야 하고, 그 암호는 매주 바뀐다.";
			link.l1 = "이제 알겠군. 그런데 보호자랑 캐롤라인은 어디서 찾지?";
			link.l1.go = "mary_12";
		break;
		
		case "mary_12":
			dialog.text = "내 집을 나가서 밧줄 다리를 건너고, 왼쪽으로 꺾어. 거기가 캐롤라인이야.\
프로텍터로 가는 길은 좀 더 까다로워. 다리를 건넌 다음 오른쪽으로 가서 산타 플로렌티나로 가. 판자 다리 반대편이야.\n리바도스 병사들을 찾아. 내가 말했듯이, 전부 흑인이야. 그놈들이 암호를 물을 거다. 크고 분명하게 대답해. 그 다음 퓨리에 들어가서 선미 쪽으로 들어가면 프로텍터로 갈 수 있어.";
			link.l1 = "좋아... 이제 알겠어.";
			link.l1.go = "mary_13";
		break;
		
		case "mary_13":
			dialog.text = "그럼, 어서 해라, 친구!";
			link.l1 = "곧 돌아올게.";
			link.l1.go = "mary_14";
		break;
		
		case "mary_14":
			DialogExit();
			NextDiag.CurrentNode = "dodson_warwait";
			AddQuestRecord("SharkHunt", "32");
			sld = characterFromId("Eddy");
			sld.dialog.currentnode = "capper"; // ноду Эдди
			sld = characterFromId("Facio");
			sld.quest.parol = true;
			pchar.questTemp.LSC = "mary_go"; //меняем флаг
		break;
		
		case "dodson_warwait":
			dialog.text = "아직도 여기 있냐? 당장 블랙 에디한테 가!";
			link.l1 = "가는 중이다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "dodson_warwait";
		break;
		
		case "mary_15":
			dialog.text = "누가 레드 메리를 죽이려고 했다고?.";
			link.l1 = "그게 그녀 이름이었나? 내가 구하려 했는데, 공격자 중 한 놈이 칼로 그녀를 베어버렸지.";
			link.l1.go = "mary_16";
		break;
		
		case "mary_16":
			dialog.text = "그 여자애는 안됐지만, 놀랍진 않아. 메리는 항상 말썽꾸러기였지.\n그럼 챈드는? 내 갑판장이야.";
			link.l1 = "네 보선장? 아... 음, 여기, 이 편지를 읽어봐. 그 여자 시체에서 찾았어. 카퍼가 네 목숨을 노리고 뭔가 꾸미고 있어, 스티븐.";
			link.l1.go = "mary_9";
		break;
		
		// Каппер сбежал
		case "Chad_escape":
			dialog.text = "어디 갔다 온 거야?! 리바도스 놈들이 자기네 마법사를 풀어줬다고 들었는데, 몇 시간째 너를 본 사람이 없어!";
			link.l1 = "미안해, 스티븐. 흑인들이 네가 배신할까 봐 자기들 안전을 보장하려고 나를 프로텍터 호에서 인질로 잡았어. 치미셋은 풀려났지만, 채드는 도망쳤어.";
			link.l1.go = "Chad_escape_1";
		break;
		
		case "Chad_escape_1":
			dialog.text = "젠장! 흑인 놈한테 백인 일이란 걸 맡기면 안 되는 거였지... 이런 간단한 일도 제대로 못 해... 젠장할 리바도스 놈들!";
			link.l1 = "채드는 나왈 무리 속에 숨어 있어...";
			link.l1.go = "Chad_escape_2";
		break;
		
		case "Chad_escape_2":
			dialog.text = "당연히 그랬지! 그 자식 바보 아니거든 - 내 도움이 없었다면 리바도스 놈들이 타르타로스 안에 들어올 수 없다는 걸 잘 알아! 이제 저놈은 숨어서 그림자 속에서 음모를 꾸미겠지.\n레이튼! 경비 두 배로 늘려! 항상 눈 똑바로 뜨고 있어라! 채드 캐퍼를 지옥으로 보내는 놈한테는 큰돈이 간다!!";
			link.l1 = "스티븐, 나 이제 간다. 어쩌면 채드를 추적할 수 있을지도 모르지. 소식 있으면 돌아올게.";
			link.l1.go = "Chad_escape_3";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Chad_escape_3":
			DialogExit();
			if (pchar.questTemp.LSC.Mary == "alive") 
			{
				pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
				AddQuestRecord("SharkHunt", "34");
			}
			else
			{ // не уберег Мэри - допетривай сам, куда идти
				pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
			}
			NextDiag.CurrentNode = "Total_wait";
			// добавим немного атмосферы - уберем Акселя до утра
			sld = characterFromId("Axel");
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
			sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
			FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
			sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
			sld.dialog.currentnode = "AxelHelper";
			LAi_SetOwnerType(sld);
			ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
			LAi_group_MoveCharacter(sld, "LSC_NARVAL");
			SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;
		
		case "whiskey":
			dialog.text = "무슨 일이야, "+pchar.name+"? 악마한테 쫓기는 놈처럼 보이는데!";
			link.l1 = "위스키 한 통 구했냐?";
			link.l1.go = "whiskey_1";
		break;
		
		case "whiskey_1":
			dialog.text = "어떤 위스키--?";
			link.l1 = "위스키 한 통 구했냐?!";
			link.l1.go = "whiskey_2";
		break;
		
		case "whiskey_2":
			dialog.text = "목소리 낮춰, 이놈아! 위스키는 없어! 뭐가 문제야?";
			link.l1 = "제시간에 와서 다행이군... 채드 캐퍼가 악셀 요스트한테서 부시밀스 한 통을 샀다더라--";
			link.l1.go = "whiskey_3";
		break;
		
		case "whiskey_3":
			dialog.text = "부쉬밀스? 그거 내가 제일 좋아하는 술이야! 진짜 오랜만에 마시네!";
			link.l1 = "그래, 그래, 그리고 카퍼도 그걸 알고 있지. 자기 친구 마르첼로 외눈박이한테 산초 카르펜테로한테서 비소 좀 사달라고 부탁했거든. 이제 이해가 가지?";
			link.l1.go = "whiskey_4";
		break;
		
		case "whiskey_4":
			dialog.text = "나를 독살하려고 했던 거야...?";
			link.l1 = "그래! 그래서 내가 그렇게 급했지. 젠장, 내 심장... 이봐, 누가 너한테 위스키 한 통 가져오면 절대 마시지 마! 독이 들어 있을 거야.";
			link.l1.go = "whiskey_5";
		break;
		
		case "whiskey_5":
			dialog.text = ""+pchar.name+", 경고 고맙다, 조심할게 - 잠깐, 지금 어디 가는 거야?";
			link.l1 = "카퍼랑 사이클롭스를 찾아야 해. 어디 있는지 알 것 같아. 곧 다시 얘기하자!";
			link.l1.go = "whiskey_6";
		break;
		
		case "whiskey_6":
			DialogExit();
			pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "45");
		break;
		
		case "whiskey_7":
			dialog.text = "하! 내가 찾던 바로 그 놈이군! 내 목숨을 빚진 것 같아.";
			link.l1 = "위스키는 도착했냐?";
			link.l1.go = "whiskey_8";
		break;
		
		case "whiskey_8":
			dialog.text = "그랬지! 부쉬밀스, 네 말대로였어. 우리 파지오 친구가 아주 친절하게도 선물로 내놓더군. 당연히, 나는 그놈을 체포했지.";
			link.l1 = "그 자가 자백했나?";
			link.l1.go = "whiskey_9";
		break;
		
		case "whiskey_9":
			dialog.text = "그랬다더군. 카퍼가 억지로 시켰다고, 위스키는 나왈 선원들이 준 선물이라고 나한테 전하라고 했대..";
			link.l1 = "카퍼는 죽었어. 그의 나왈 친구들도 다 죽었지. 이제 남은 놈은 딱 하나, 마르첼로 사이클롭스뿐이야... 파지오가 그 자식이 어디 있는지 분명히 알 거다. 내가 좀 쥐어짜 볼게!";
			link.l1.go = "whiskey_10";
		break;
		
		case "whiskey_10":
			dialog.text = "편하게 해. 하지만 죽이지는 마라, 우리 파지오 녀석이 요즘 건강이 영 안 좋거든.";
			link.l1 = "대부분은... 살살 해주지.";
			link.l1.go = "whiskey_11";
		break;
		
		case "whiskey_11":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			chrDisableReloadToLocation = true;//закрыть локацию
			sld = CharacterFromID("Facio");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "poison":
			pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
			dialog.text = "으르릉... "+pchar.name+", 친구야, 나한테 뭔가 아주 잘못됐어...";
			link.l1 = "스티븐! 네가 이 위스키 마셨냐?!";
			link.l1.go = "poison_1";
		break;
		
		case "poison_1":
			dialog.text = "그래... 부쉬밀스... 오늘 주세페 파지오가 가져왔지, 나왈 선장 놈이 준 선물이라더군... 평화의 증표라나 뭐라나...\n악, 젠장 아파 죽겠네!";
			link.l1 = "그 위스키에 비소가 들어 있었어!! 채드랑 외눈박이 그놈들이 한 짓이야!";
			link.l1.go = "poison_2";
		break;
		
		case "poison_2":
			dialog.text = "아으... 결국 이 개자식한테 당했군...";
			if (CheckCharacterItem(pchar, "ultimate_potion"))
			{
				link.l1 = "너 죽지 않을 거야! 들려? 절대 안 죽어! 빨리, 이 플라스크 받아. 이건 세상에서 제일 강력한 치료약이야, 모든 상처를 낫게 해. 마셔... 지금!";
				link.l1.go = "poison_3";
			}
			else
			{
				link.l1 = "스티븐...!";
				link.l1.go = "dodson_poison";
			}
		break;
		
		case "dodson_poison": // Акула умирает
			DialogExit();
			LAi_SetImmortal(npchar, false);
			LAi_KillCharacter(npchar);
			SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				AddQuestRecord("SharkHunt", "41");
				sld = CharacterFromID("Facio");
				sld.dialog.currentnode = "whiskey";
				sld.greeting = "facio_2";
				sld.quest.poisonnode = 1;
			}
			else AddQuestRecord("SharkHunt", "42");
			pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;
		
		case "poison_3":
			RemoveItems(pchar, "ultimate_potion", 1);
			Log_Info("Comanche potion was used");
			Log_Info("Poison was cured!");
			PlaySound("interface\notebook.wav");
			dialog.text = "오... "+pchar.name+", 그 물건 진짜 끝내주더라. 아직 좀 속이 안 좋긴 한데, 통증은 거의 사라졌어...";
			link.l1 = "인디언 주술사가 내게 준 거다. 전부 다 마셔, 얼른! 그래, 그렇지...";
			link.l1.go = "poison_4";
		break;
		
		case "poison_4":
			LAi_SetStayType(npchar);
			dialog.text = "기적이군... 몸이 멀쩡해! 고맙다, 친구... 이 은혜 잊지 않겠다!";
			if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
			{
				link.l1 = "이제 좀 쉬는 게 좋겠군. 꼴이 거의 죽은 사람 같아. 그 자식 카퍼는 더 이상 널 위협 못 해 – 내가 그놈이랑 그의 나왈 패거리 몇 놈도 처리했거든. 이제 마르첼로 사이클롭스만 남았지. 파지오가 위스키 가져다줬다고 했지?";
				link.l1.go = "poison_5";
			}
			else
			{
				link.l1 = "이제 좀 쉬는 게 좋겠군. 너 꼴이 거의 죽은 놈 같아. 파지오가 위스키 가져왔다고 했지?";
				link.l1.go = "poison_7";
			}
		break;
		
		case "poison_5":
			dialog.text = "그래. 왜 그 자식이 그렇게 초조해 보였는지 궁금했지... 내 위대한 존재 앞에 서 있어서 그런 줄만 알았는데, 크크...";
			link.l1 = "카퍼가 저 놈을 억지로 끌어들였나 보군. 좋아, 그 뚱뚱한 돼지한테 가서 정보를 좀 뽑아내야겠어. 이제 쉬어, 스티븐!";
			link.l1.go = "poison_6";
		break;
		
		case "poison_6":
			DialogExit();
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "40");
		break;
		
		case "poison_7":
			dialog.text = "그래. 왜 그 자가 그렇게 초조해 보였는지 궁금했지... 내 위대한 존재 앞에 서 있어서 그런 줄만 알았는데, 크크...";
			link.l1 = "카퍼가 저 놈을 억지로 끌어들였겠지. 저 뚱뚱한 돼지는 언젠가 내가 잡을 거다만, 지금은 카퍼랑 외눈박이부터 처리해야 해. 놈들이 어디 숨었는지 알고 있거든. 이제 좀 쉬어, 스티븐!";
			link.l1.go = "poison_8";
		break;
		
		case "poison_8":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);//запрещаем диалог
			AddQuestRecord("SharkHunt", "43");
		break;
		
		case "clear":
			dialog.text = "이봐, "+pchar.name+"! 에바호에서 카퍼랑 한판 붙었다는 소문 들었어, 하하! 대단한데! 챈드랑 그 놈들 전부 혼자서 해치웠다니... 얀 말대로 싸움 실력이 보통이 아니구만.";
			link.l1 = "카퍼도 처리했고, 네 목숨을 노린 시도도 막았어. 독살당할 뻔했어, 스티븐. 하지만 괜찮아, 내가 다 해결했으니까.";
			link.l1.go = "clear_1";
		break;
		
		case "clear_1":
			dialog.text = "나를 독살한다고? 어떻게?";
			link.l1 = "채드는 악셀에게서 아이리시 부시밀스 위스키 한 통을 샀어--";
			link.l1.go = "clear_2";
		break;
		
		case "clear_2":
			dialog.text = "부쉬밀스? 이거 내 제일 좋아하는 술이야! 진짜 오랜만에 마시네!";
			link.l1 = "카퍼도 그걸 알고 있었지. 자기 친구 마르첼로 외눈박이한테 산초 카르펜테로에게서 비소를 사 오라고 시켰어. 그다음 자기 패거리랑 같이 파지오를 붙잡아서 에바호의 화물칸으로 내려갔지. 위스키에 독을 타서 파지오에게 '나르왈 놈들이 준 선물'이라며 너한테 가져가게 하려고 했던 거야.";
			link.l1.go = "clear_3";
		break;
		
		case "clear_3":
			dialog.text = "젠장... 잘만 하면 됐을 텐데; 그 위스키 한 파인트는 단숨에 마셨을 거다.";
			if (CheckCharacterItem(pchar, "cask_whisky"))
			{
				link.l1 = "채드는 그걸 노리고 있었지. 하지만 실패했어 - 비소를 넣을 시간조차 없었거든. 그러니... 내가 그 통을 챙겼다. 손대지 않은 채로, 네가 가져가도 돼.";
				link.l1.go = "clear_4";
			}
			else
			{
				link.l1 = "채드는 그걸 노리고 있었지. 하지만 실패했어 - 비소를 넣을 시간조차 없었거든.";
				link.l1.go = "clear_7";
			}
		break;
	
		case "clear_4":
			RemoveItems(pchar, "cask_whisky", 1);
			PlaySound("interface\notebook.wav");
			dialog.text = "보여줘... "+pchar.name+", 이게 바로 진짜 부시밀스다! 최고의 아일랜드 위스키지! 아으, 몇 년 동안이나 이걸 꿈꿔왔지!\n너, 내 친구야... 젠장, 넌 기적을 일으키는 놈이구나! 채드를 없애주고, 내 목숨을 구해주고, 내가 제일 좋아하는 위스키 한 통까지 아무렇지 않게 가져오다니!\n이건 제대로 보상해야겠군.\n (뒤적거리며) 젠장, 어디 있지...? 아! 여기 있다. 이걸 가져가라. 토르의 망치라고 불리는 건데, 영원히 쓸 수 있지. 이제는 네 대포가 네 얼굴에서 터질까봐 두려워할 필요 없어! 네 포수도 이거 엄청 좋아할 거다!";
			link.l1 = "이런 맙소사, 스티븐... 고마워! 분명 그럴 거야.";
			link.l1.go = "clear_5";
		break;
		
		case "clear_5":
			GiveItem2Character(pchar, "talisman3"); 
			PlaySound("interface\notebook.wav");
			Log_Info("You have received a 'Thor's hammer' amulet");
			dialog.text = "이제 실례하지. 이 훌륭한 위스키랑 좀 친해질 시간이거든... "+pchar.name+", 내일 나한테 와라. 그동안 나는 좀 생각 좀 해야겠다...";
			link.l1 = "좋아, 스티븐, 네 위스키 방해 안 할게, 하하!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "53");
		break;
		
		case "clear_6":
			DialogExit();
			NextDiag.CurrentNode = "Total_wait";
			DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
			if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
			{
				SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
				DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
			}
		break;
		
		case "clear_7":
			dialog.text = "네가 이런 얘기를 해줘서 큰 도움이 됐어. 네 말이랑 채드가 한 짓을 곱씹어 봐야겠군... 그 다음에 내가 널 부를 거다.";
			link.l1 = "기다리고 있겠다!";
			link.l1.go = "clear_6";
			AddQuestRecord("SharkHunt", "54");
		break;
		
		case "whyskey_final":
			dialog.text = "하, 거기 있었군, "+pchar.name+". 이제 모두 모였으니 시작하자. 내가 너랑 레이튼을 부른 건 상황을 논의하고, 나왈 문제를 어떻게 할지 결정하려고였어.";
			link.l1 = "‘나왈 고래 놈들 어떻게 할 거냐’가 무슨 뜻이야?";
			link.l1.go = "whyskey_final_1";
		break;
		
		case "whyskey_final_1":
			dialog.text = "뭐라니, '뭐라니?' 채드가 나를 죽이려고 나왈들과 짜고 덤볐잖아.\n이건 명백한 적대 행위야. 그냥 넘어갈 수 없지. 우리가 리바도스랑 우호적인 관계라는 걸 감안해서 내 제안을 해보지...\n니그로들과 동맹을 공식화하고, 우리 놈들 다 모아서 나왈 놈들을 완전히 쓸어버리자고.\n너, "+pchar.name+", 또다시 우리 외교관 노릇을 해야겠군. 블랙 에디랑 치미셋한테 가서 내 우정 제안을 받아들이라고 설득해. 전투 계획은 덱스터가 짤 거야, 이 섬을 누구보다 잘 아니까. 레이튼?";
			link.l1 = "";
			link.l1.go = "whyskey_final_2";
		break;
		
		case "whyskey_final_2": // перекидываем ноду Декстеру
			DialogExit();
			sld = characterFromId("Dexter");
			sld.greeting = "";
			LAi_SetActorType(sld);
			LAi_ActorSetHuberMode(sld);
			LAi_CharacterEnableDialog(sld);
			LAi_ActorDialogNow(sld, pchar, "", -1);
		break;
		
		case "whyskey_final_3":
			dialog.text = "처음부터 나르왈 놈들을 전멸시킬 필요는 없어; 우리는 정의의 섬의 식량을 쥐고 있지.\n놈들을 산 가브리엘로 몰아넣으면, 가둬서 굶겨 죽일 수 있어. 어때, "+pchar.name+"?";
			link.l1 = "뭐라고 하냐고? ... 내 말은, 너는 나왈 선원들을 그냥 풀어줘야 한다는 거야, 스티븐.";
			link.l1.go = "whyskey_final_4";
		break;
		
		case "whyskey_final_4":
			dialog.text = "... 여기 오기 전에 머리라도 다쳤냐? 채드랑 싸운 놈들이 바로 나월 해적단이었다는 걸 잊었어?";
			link.l1 = "전부 그런 건 아니야. 마르첼로 사이클롭스는 아니었지. 사실 그는 리바도스에게 충성했어 — 어차피 혼혈이었으니까. 내 생각엔 채드 편에 붙은 나르왈들은 돈으로 사거나, 네가 앨런 밀로우를 죽였다는 거짓말에 속은 놈들뿐이었지.";
			link.l1.go = "whyskey_final_5";
		break;
		
		case "whyskey_final_5":
			dialog.text = "그래서 어쩌라고, 이 모든 걸 그냥 무시하란 말이야?";
			link.l1 = "내가 외교관 역할을 맡아보지... 하지만 이번엔 나르왈 두목 도널드 그린스팬과 말이야. 내 말 좀 들어볼래, 스티븐?";
			link.l1.go = "whyskey_final_6";
		break;
		
		case "whyskey_final_6":
			dialog.text = "... 계속해...";
			link.l1 = "여기에 도착한 이후로 나는 버려진 배들의 도시에 대해 많은 것을 배웠지. 주민들 말로는, 정의의 섬에 두 개의 씨족만 있었을 때는 전쟁이 끊이지 않았다고 하더군. 그런데 네 해적들이 들어오면서 섬에 세 번째 세력이 생겨, 처음으로 균형과 평화가 찾아왔다지. 하지만 나왈과 리바도스는 여전히 강하고, 승리를 거두려면 엄청난 대가를 치러야 할 거다.";
			link.l1.go = "whyskey_final_7";
		break;
		
		case "whyskey_final_7":
			dialog.text = "";
			link.l1 = "나월호를 파괴하는 대가로 많은 해적들과 리바도스 놈들이 목숨을 잃게 될 거야. \n게다가, 레이튼 말로는 산 가브리엘 공성전이 오래 걸릴 거라더군. 리바도스 놈들이 이번 작전에서 너무 많은 걸 잃었다고 느끼면, 물러날 수도 있어... 어쩌면 우리를 배신할 수도 있지.";
			link.l1.go = "whyskey_final_8";
		break;
		
		case "whyskey_final_8":
			dialog.text = "";
			link.l1 = "두 부족 모두 아직도 정의의 섬을 지배하려는 욕심이 남아 있다는 걸 잊지 마라, 그리고 얼마 전까지만 해도 너한테 맞서기 위해 힘을 합쳤지. 이 전쟁이 네가 생각하는 것처럼 빨리, 혹은 뻔하게 끝나진 않을 거다. 그 한가운데에는 평범한 사람들도 있고. 정말로 무덤 위에 군림하고 싶은 거냐?";
			link.l1.go = "whyskey_final_9";
		break;
		
		case "whyskey_final_9":
			dialog.text = "... 네 말에도 일리가 있긴 한데... 아직은 내가 설득되진 않았어.";
			link.l1 = "나도 어떻게든 이 섬을 떠나야 해. 바닷속에 있는 쿠쿨칸의 우상까지 가야 하거든. 리바도스 놈들은 나를 도와줄 수 없어... 하지만 혹시 나월 놈들은 가능할지도 몰라. 그쪽에 똑똑하고 재주 있는 녀석들이 있다는 소문을 들었거든. 근데 걔들이랑 전쟁 중이면 날 도와주진 않겠지.";
			link.l1.go = "whyskey_final_10";
		break;
		
		case "whyskey_final_10":
			if (pchar.questTemp.LSC.Mary != "die") sTemp = "A-ha! I knew you had selfish reasons for wanting peace! And I guess that one of them is that redhead on the Ceres, eh, my friend? Am I right? Don't worry about her, "+pchar.name+", we'll find a safe place for her before the fighting starts.\n";
			else sTemp = "";
			dialog.text = ""+sTemp+" 그렇게까지 고집한다면, 좋아. 도널드한테 가 봐. 에스메랄다 뒤쪽에 그 자식 집이 있다. 그 놈이 무슨 말을 하는지 들어봐라.\n도널드와 그 족속이 챈 놈의 계략에 관여하지 않았다고 네가 확신한다면... 평화도 생각해 보지.";
			link.l1 = "고마워, 스티븐. 이게 분명 옳은 결정일 거야.";
			link.l1.go = "whyskey_final_11";
		break;
		
		case "whyskey_final_11":
			DialogExit();
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations"; // ноду Гринспи
			sld = characterFromId("Dexter");
			LAi_SetHuberType(sld);
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "negotiations_wait";
			pchar.questTemp.LSC.Donald_enter = "true";
			AddQuestRecord("SharkHunt", "55");
		break;
		
		case "negotiations_wait":
			dialog.text = "하지만 너무 쉽게 넘어가게 두지 마라, 알겠지! 그래도 걔네는 채드랑 같이 있던 그 놈의 부하들이었으니까 - 여전히 나왈들이잖아! 신발이나 핥게 하고, 제대로 뉘우치게 만들어!";
			link.l1 = "알겠어, 알겠다고.";
			link.l1.go = "exit";
			NextDiag.TempNode = "negotiations_wait";
		break;
		
		case "peace":
			dialog.text = "그래서, 도널드랑 얘기해 봤나?";
			link.l1 = "그래, 그리고 그는 내 의심을 확인해줬지. 그도, 그 일족 전체도 채드의 계획과는 아무 상관이 없었어. 그 일에 가담한 모든 나르왈들은 카퍼가 끌어들인 자들이야. 그는 지금 매우 화가 나 있고, 너를 앨런 밀로우의 살인과 그 이후에 벌어진 모든 일에 대해 전혀 탓하지 않는다고 내게 확실히 말했어.";
			link.l1.go = "peace_1";
		break;
		
		case "peace_1":
			dialog.text = "그 자가 내 앞에 당당히 서서 이 모든 말을 내 얼굴에 대고 할 준비가 됐다는 거냐?";
			link.l1 = "그는 성경에 맹세했지, 반드시 그렇게 하겠다고.";
			link.l1.go = "peace_2";
		break;
		
		case "peace_2":
			dialog.text = "허, 이런 젠장... 결국 죄를 뒤집어쓸 놈은 내 배신자 보스운밖에 없는 모양이군...";
			link.l1 = "나도 그렇게 생각해, 스티븐. 우리한테 이 전쟁은 필요 없어, 아무도 필요 없지. 장사에도 전혀 도움이 안 될 거야.";
			link.l1.go = "peace_3";
		break;
		
		case "peace_3":
			dialog.text = "(탁자를 쾅 친다) 좋아, 그럼! 거래 성사다. 그린스팬이 와서 내 엉덩이에 입 맞추면, 다 용서해주지... 그리고 평화가 올 거다.";
			link.l1 = "바로 전하겠소. 스티븐... 이 전쟁을 막아서 다행이야.";
			link.l1.go = "peace_4";
		break;
		
		case "peace_4":
			if (pchar.questTemp.LSC.Mary == "alive") sTemp = "Feel free to bring your Mary over to the San Augustine, I can set aside some quarters for the two of you.";
			else sTemp = "";
			dialog.text = "잠깐만... "+pchar.name+", 네가 이 빌어먹을 정의의 섬에 나타나서 정말 반갑구나.\n얀 놈이 편지에서 너를 엄청 치켜세웠지... 그런데 내가 기대했던 것보다 훨씬 더 대단하더군.\n네가 내 선원이었으면... 아니, 잠깐! 여기 있는 동안은 카퍼 자리를 너한테 주겠다. 타르타로스에 있는 내 주둔군을 네가 지휘해라. "+sTemp+".";
			if (pchar.questTemp.LSC.Mary == "alive") link.l1 = "아니, 스티븐, 고맙지만 난 여기 오래 있지 않을 거야. 그 일은 더 믿을 만하고 자격 있는 녀석에게 맡겨. 그리고 메리에 관해서라면... 우리 세레스호에서는 잘 지내고 있어.";
			else link.l1 = "아니, 스티븐, 고맙지만 난 여기 오래 있지 않을 거야. 그 일은 더 믿을 만하고 자격 있는 녀석에게 맡겨.";
			link.l1.go = "peace_5";
		break;
		
		case "peace_5":
			TakeNItems(pchar, "gold_dublon", 500);
			Log_Info("You have received 500 doubloons");
			PlaySound("interface\important_item.wav");
			dialog.text = "너만큼 자격 있고 믿을 만한 녀석도 드물지. 네가 뭐라 해도, 이 정의의 섬에서 빠져나가는 게 네가 바라는 것만큼 쉽진 않을 거라고 본다.\n뭐, 어쨌든 좋다. 그냥 보낼 순 없으니, 입 닫고 이 오백 두블룬이나 받아라.";
			link.l1 = "고맙다!";
			link.l1.go = "LSC_navy";
			AddQuestRecord("SharkHunt", "57");
			pchar.questTemp.Saga.SharkHunt = "find"; //флаг - покушение предотвращено
			sld = characterFromId("Grinspy");
			sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
			AddSimpleRumourCityTip("They say that the Admiral respects you, mister...", "LostShipsCity", 15, 2, "LSC", "");
			AddSimpleRumourCityTip("They say that you are the Admiral's loyal friend. Is that true?", "LostShipsCity", 15, 2, "LSC", "");
		break;
		
		case "LSC_navy":
			dialog.text = "우리 일 얘기나 하자... 내 항해 지침서를 가져가라. 거기엔 정의의 섬까지 배를 무사히 몰고 갈 수 있는 항로가 적혀 있다.\n잃어버리지 마라! 그거 없으면 네 배는 암초에 걸려 침몰하거나 폭풍에 찢겨 나갈 거다. 그리고 반드시 기억해라, 그 섬엔 비교적 작은 배로만 접근할 수 있다! 노 젓는 배, 타르탄, 러거, 스쿠너, 그 이상은 안 된다.\n나중에 나를 데리러 오면, 나도 너랑 스벤손이랑 한패가 되어주지.\n가라앉은 인디언 우상이 널 도울 거란 건 아직도 믿기 힘들지만... 행운을 빈다, 친구야.";
			link.l1 = "신에게 의지할 게 아니라, 스티븐, 쿠쿨칸에게 기대야지. 다시 만날 때까지.";
			link.l1.go = "LSC_navy_1";
		break;
		
		case "LSC_navy_1":
			GiveItem2Character(pchar, "LSC_navigation_map");
			dialog.text = ""+pchar.name+"... 최대한 빨리 돌아와라. 내 창고가 바닥나고 있다; 곧 식량이 하나도 안 남을 거다. 무장한 배고픈 놈들이 뭘 저지를 수 있는지 알지?";
			link.l1 = "뭔가 감이 오긴 하지. 잘 가라.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
			AddQuestRecord("LSC", "5");
			// убираем квестовые предметы
			sld = ItemsFromID("key_capper");
			sld.price = 10;
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
		break;
		
		case "Dodson_wait":
			dialog.text = "섬에서 나갈 방법을 찾았나, "+pchar.name+"?";
			link.l1 = "아직 아니야, 스티븐. 아직 작업 중이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Dodson_wait";
		break;
		
		// --> информационный блок
		case "Total_wait":
			dialog.text = "그래, 뭘 가지고 왔어, "+pchar.name+"재밌는 소식이라도 있냐?";
			
			if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
			{
				link.l1 = "스티븐, 네가 압수한 내 물건들을 돌려줬으면 해.";
				link.l1.go = "Items";
			}
			if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l2 = "스티븐, 이 섬에 대해 좀 더 말해 줘.";
				link.l2.go = "Story_island";
			}
			if (!CheckAttribute(npchar, "quest.natan"))
			{
				link.l3 = "호크가 정의의 섬에 없다는 거 확실해? 그놈이 우상 쪽으로 들어왔으니, 분명 여기 있을 텐데.";
				link.l3.go = "Natan";
			}
			if (!CheckAttribute(npchar, "quest.whiteboy"))
			{
				link.l4 = "White Boy라는 놈을 아나?";
				link.l4.go = "Whiteboy";
			}
			if (!CheckAttribute(npchar, "quest.ships"))
			{
				link.l5 = "나르왈과 리바도스의 영토는 어디지?";
				link.l5.go = "ships";
			}
			if (!CheckAttribute(npchar, "quest.parol"))
			{
				link.l6 = "어떻게 해야 그 족속들 배에 올라탈 때 필요한 암호를 알 수 있지?";
				link.l6.go = "parol";
			}
			if (!CheckAttribute(npchar, "quest.map"))
			{
				link.l7 = "이봐, 이 섬의 지도 있냐?";
				link.l7.go = "map";
			}
			if (!CheckAttribute(npchar, "quest.blade"))
			{
				link.l8 = "저런 멋진 브로드소드 처음 본다. 이런 건 한 번도 본 적 없어...";
				link.l8.go = "blade";
			}
			link.l9 = "아직 물어볼 게 없어. 곧 생길지도 모르지...";
			link.l9.go = "exit";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Items":
			dialog.text = "아, 그래! 완전히 잊고 있었군... 네 물건은 위층 상자에 있다. 가져가도 돼, 레이튼이 막지 않을 거야.";
			link.l1 = "고맙다!";
			link.l1.go = "exit";
			npchar.quest.items = "true";
			NextDiag.TempNode = "Total_wait";
			ref location = &Locations[FindLocation(pchar.location)];
			DeleteAttribute(location, "private1.key");
			for (i=1; i<=10; i++) // можно лезть в сундук
			{
				sld = characterFromId("SharkSoldInside_"+i);
				DeleteAttribute(sld, "watchBoxes");
			}
		break;
		
		case "Story_island":
			dialog.text = "이 섬은 백 년이 훨씬 넘었지; 바깥쪽에 있는 카라벨 중에는 1550년이나 그 이전에 용골이 놓인 배들도 내가 봤다네.\n우리 발밑엔 얕은 모래톱이 있어서, 여기 난파된 배들을 받쳐주고, 물 위에 떠 있게 해주지. 매년 수많은 배가 썩어 먼지가 되지만, 폭풍과 강한 해류가 또 다른 배들을 끌고 오지.\n정의의 섬은 살아있는 것처럼 똥 싸고, 먹고, 자라난다네.\n첫 정착민들은 드 베탕쿠르 원정대와 함께 도착했는데, 그중에 산 아우구스틴과 타르타로스가 있었지. 타르타로스에는 흑인 노예들이 많이 실려 있었고, 그 중 한 명이 페드로 리바도스라는 남자였어. 그는 스페인인 포획자들에게 반란을 일으켰지만 실패했고, 천천히 죽으라는 형벌을 받았지: 돛대에 묶여 태양 아래에서 천천히 익어가게 내버려졌거든.\n하지만 그의 자유를 향한 시도가 드 베탕쿠르 일행을 약화시켜, 두 번째 반란은 성공했고, 그를 기려 리바도스 일족을 세웠지.\n리바도스가 섬을 지배할까 두려웠던 백인 기독교 정착민들은, 그 야성적인 아프리카식 방식에 맞서 기적적으로 서로의 국적을 뛰어넘어 힘을 합쳐 나르왈 일족을 만들었지.\n허, 백인들이 흑인 밑으로 들어갈 위협 앞에선 별의별 차이도 순식간에 잊어버리더군.\n나르왈 일족에는 용병, 군인, 장교, 모험가들이 많아. 해마다 물자를 모으고, 이곳에 난파되어 온 배에서 새 사람들을 골라 뽑지. 오늘날 그 결과를 볼 수 있지: 그들은 훈련된 전문 군대야. 그래서 리바도스가 섬을 지배하려는 야심도 꺾을 수 있었던 거지.";
			link.l1 = "이 섬이랑 카리브 해 다른 곳들이랑 연결된 게 있나?";
			link.l1.go = "Story_island_1";
		break;
		
		case "Story_island_1":
			dialog.text = "지난 10년 동안은 아무도 없었지. 이 근처 놈들 말 들어보면, 정의의 섬을 둘러싼 날씨가 변했다더라. 폭풍이 더 자주 몰아치고, 해류도 훨씬 강해졌지.\n마치 어느 날 갑자기 이 섬이 카리브 해의 나머지 지역과 완전히 단절된 것처럼 말이야.\n섬 사람들은 예전엔 쿠바의 버커니어들과 거래하며, 난파선에서 건진 금이나 값나가는 물건으로 식량을 샀었지. 하지만 지난 10년간 정의의 섬에 온 버커니어는 없어.\n뭐, 돌아간 놈은 아무도 없었으니까.";
			link.l1 = "흠. 그러니까 숲의 악마랑 검은 신부 둘 다 맞았던 거군... 그런데 왜 사람들은 기회가 있었을 때 정의의 섬을 떠나지 않았지?";
			link.l1.go = "Story_island_2";
		break;
		
		case "Story_island_2":
			dialog.text = "몇몇은 그랬지만, 대부분은 여기 남고 싶어 했지. 많은 놈들이 여기서 터를 잡았고, 또 어떤 놈들은 여기서 태어나서 다른 세상을 몰라.\n떠나고 싶어하는 사람들도 있지만, 낡고 대충 만든 배로 폭풍 지대를 항해할 용기가 없어서 못 나가는 거야.\n리바도스에 관해서라면... 흑인들이지. 내가 마지막으로 확인했을 때, 저 바깥세상은 백인 놈들 세상이더군. 걔들이 여기 남고 싶어 하는 걸 탓할 수 있겠어?";
			link.l1 = "그런데 도드슨, 왜 여기 온 거지? 너한텐 프리깃함도 있었고, 존경받는 해적이었잖아--";
			link.l1.go = "Story_island_3";
		break;
		
		case "Story_island_3":
			dialog.text = "(탁자를 쾅 내리치며) 내가 사냥당하고 있었지!!\n블레이즈 샤프 살인 누명을 썼어! 누가, 무슨 이유로 그랬는지는 전혀 몰라.\n누군가 날 자기 판의 졸로 만들었고, 적들에게 둘러싸여 친구들에게도 버림받았으니, 이슬라 테소로를 떠나 몸을 숨길 수밖에 없었지.\n이 정의의 섬에 대해선 오래전부터 알고 있었지만, 내 프리깃으로는 암초를 피해 들어올 수가 없었어. 너무 커서 말이지. 그래서 브리그로 바꿨어.\n여기 도착하자마자 나르왈 놈들과 리바도스 놈들이 덤벼들더군 – 흑인 놈들이랑 백인 놈들이 서로보다 더 싫어하는 게 해적들이란 말이지, 크크. 밤에 장정배를 저어 내 배까지 와서 불을 질렀어.\n우린 대포로 그놈들 배를 쪼개놨지만, 불이 제대로 번져서 내 불쌍한 브리그는 뼈대만 남기고 다 타버렸지.\n우린 열 받아서 제대로 복수했다: 산 아우구스틴을 습격해서 해적이 어떻게 싸우는지 보여줬지! 놈들은 배를 지키지 못하고 겁쟁이처럼 도망쳤어.\n산 아우구스틴을 점령하고 보니, 이 섬 전체가 그 배를 창고로 쓰고 있더군! 하룻밤 새에 우린 섬에서 제일 중요한 패거리가 됐지.\n이제는 정의의 섬에 사는 놈들 전부가 자기 식량을 우리한테서, 우리가 부르는 값에 사가야 해, 하하하!\n또, 패거리 두목 둘도 잡았지: 나르왈의 앨런 밀로우랑, 리바도스의 부두 주술사 치미셋. 내 동료 레이튼이 며칠간 섬을 정찰하고, 그다음엔 타르타로스, 옛 노예선을 공격했어.\n이제 우린 배 두 척을 손에 넣었고, 패거리 놈들은 우리랑 거래를 하든가 굶어 죽든가 해야지. 요즘은 여기서 그럭저럭 평화 비슷한 게 유지되고 있어.\n섬 주민들은 말이지... 걔네한텐 식량을 제대로 싸게 팔아. 우릴 상대로 무기 들진 않았으니까. 아무튼, 우리가 다른 두 패거리를 어느 정도 견제해주니 그 점은 좋아하는 것 같더라.";
			link.l1 = "믿기 힘들군... 정말 대단한 이야기야!";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Natan":
			dialog.text = "난 그를 본 적 없어. 호크가 마룬 타운 말고 다른 데 있다는 얘기는 이번이 처음 듣는군.\n섬이나 바깥 고리 어딘가에 몰래 숨어 있을 수도 있지. 숨을 곳은 충분하니까. 하지만 지금쯤이면 나를 한번쯤 찾아왔을 법도 한데...";
			link.l1 = "그래...";
			link.l1.go = "exit";
			npchar.quest.natan = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "Whiteboy":
			dialog.text = "백인 꼬마? 흠... 아니, 그 이름은 들어본 적 없어. 하지만 여기 없다는 뜻은 아니지 – 내가 이 동네 잡놈들 전부를 알아야 할 이유라도 있나?";
			link.l1 = "아니, 아니야. 좋아, 다른 놈한테 물어볼게.";
			link.l1.go = "exit";
			npchar.quest.whiteboy = "true";
			NextDiag.TempNode = "Total_wait";
		break;
		
		case "ships":
			dialog.text = "섬은 나와 내 해적들, 그리고 나르왈과 리바도스가 나눠서 차지하고 있고, 우리 사이에는 중립 구역이 있다.\n나는 산 아우구스틴과 타르타로스를 장악하고 있지.\n리바도스는 프로텍터(그들의 두목 거처), 퓨리(병영), 벨라스코(창고)를 차지하고 있다. 이 구역들은 이방인 출입이 금지되어 있고, 들어가려면 특별한 암호를 말해야 해.\n나르왈은 여러 배를 차지하고 있는데, 에스메랄다는 상점이자 그들 두목의 거처고, 산 가브리엘과 피닉스는 무슨 과학자가 운영하고 있어. 그리고 케레스는 대장간이지.\n에스메랄다를 제외한 모든 배는 출입이 제한된 구역이라, 들어가려면 암호를 말해야 해. 리바도스 쪽도 마찬가지야. 그리고 암호는 매주 바뀐다.\n나머지 배들은 중립 구역으로 간주되고, 시민들이 거기서 살아.\n내가 누구를 빼먹었지...? 아, 플뢰롱은 산초 카르펜테로라는 놈이 운영하는 선술집이고, 글로리아는 지역 교회야 - 줄리안 형제가 거기 목사로 있지.";
			link.l1 = "기억할 게 참 많군... 직접 걸어 다니면서 도시를 익혀야겠어.";
			link.l1.go = "exit";
			npchar.quest.ships = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "2");
		break;
		
		case "parol":
			dialog.text = "족속들이랑 손잡는 거지. 하지만 너는 나왈 놈들한테는 깡이 부족하고, 리바도스 놈들한테는 피부가 안 맞으니, 캐롤라인이라는 오래된 프리깃선에 가서 주세페 파지오라는 뚱뚱한 자식을 찾아봐. 이 자식이 여기서는 외교관 비슷한 역할을 해.\n이 섬에 오기 전에 뭘 했는지는 모르겠지만, 제대로 된 악당이야. 누구랑도 거래하지. 족속들이 중재자로 쓰기 때문에 매주 암호도 항상 받아.\n파지오는 욕심쟁이라, 금화 한 닢이면 자기 몸도 뜯어먹을 놈이지. 리바도스나 나왈 구역의 최신 암호를 물어볼 수는 있는데, 금으로 값을 치를 각오나 해라.";
			link.l1 = "캐롤라인... 파지오... 그래, 고맙다.";
			link.l1.go = "exit";
			npchar.quest.parol = "true";
			NextDiag.TempNode = "Total_wait";
			AddQuestRecord("LSC", "3");
		break;
		
		case "map":
			dialog.text = "덱스터가 하나 가지고 있어. 내 첫 번째 부하지. 우리가 도착하자마자 자세한 지도를 만들었어. 위층에 올라가서 그 녀석이랑 얘기해 봐, 팔 생각이 있는지 물어봐.";
			link.l1 = "알겠어. 고마워!";
			link.l1.go = "exit";
			npchar.quest.map = "true";
			NextDiag.TempNode = "Total_wait";
			sld = characterFromId("Dexter");
			sld.quest.map = "true";
		break;
		
		case "blade":
			dialog.text = "하! 나왈 일족의 우두머리 앨런 밀로우에게서 얻은 전리품이지.\n나왈 대장장이 위르겐이 바다 밑바닥에서 찾아낸 희귀한 철로 만들었어. 녹슬지도 않고, 무뎌지지도 않으며, 한 번 휘두르면 놈 둘을 반으로 잘라버릴 수 있지.\n이 검은 이번 원정에서 건진 몇 안 되는 쓸만한 물건 중 하나야. 그래서 이건 어떤 값에도 내놓지 않을 거다.";
			link.l1 = "위르겐이 이런 브로드소드 하나 더 만들 수 있나?";
			link.l1.go = "blade_1";
		break;
		
		case "blade_1":
			dialog.text = "쳇! 그럴 리 없지. 위르겐은 나르왈족이야. 자기 부족에게만 충성하고, 외부인한테는 무기를 절대 안 만들어줘.\n 게다가, 두 번째 검을 만들려면 그 특별한 철이 필요해. 그 철은 바다 밑바닥에서만 구할 수 있는데, 아가미라도 달렸나? 어떻게 거길 가겠어? 그러니까 그냥 포기해.";
			link.l1 = "그래... 안타깝군...";
			link.l1.go = "exit";
			npchar.quest.blade = "true";
			NextDiag.TempNode = "Total_wait";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
			{
				sld = characterFromId("Schmidt");
				sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
			}
		break;
		// <-- информационный блок
		
		case "return":
			chrDisableReloadToLocation = true;//закрыть локацию
			dialog.text = ""+pchar.name+"! 이 미친 놈아, 하하하, 해냈구나!! 네 돛이 수평선에 보이더라! 잘 지냈냐, 친구? 항해는 어땠어?";
			link.l1 = "헤, 나도 반갑다, 스티븐. 살아남았지.";
			link.l1.go = "return_1";
		break;
		
		case "return_1":
			dialog.text = "좋아! 젠장, 난 이제 이 정의의 섬을 떠나서 포레스트 데빌이랑 한잔하고 싶어 죽겠군.\n레이튼은 계속 제독으로 남을 거야 - 벌써 내 자리를 차지했지, 하하! 이 녀석, 이곳이 진짜 마음에 드는 모양이야.";
			link.l1 = "예전에 여기 상륙한 많은 사람들이 바깥세상보다 이곳에서의 삶을 더 좋아하게 된다고 했지. 덱스터도 다르지 않다는 게 놀랍냐?";
			link.l1.go = "return_2";
		break;
		
		case "return_2":
			dialog.text = "에이, '놀랐다'기보단... 그냥 그 녀석을 잃어서 슬플 뿐이지. 저만한 일등항해사는 다시 못 구해.\n그래서... 언제 닻 올릴 생각이냐?";
			link.l1 = "곧이야. 내 배에 타, 스티븐. 여기 일만 끝나면 바로 출항할 거야.";
			link.l1.go = "return_3";
		break;
		
		case "return_3":
			dialog.text = "네가 선장이구나! 아, 다시 갑판이 내 발 아래서 흔들리는 걸 느끼게 된다니 정말 좋겠군!";
			link.l1 = "...";
			link.l1.go = "return_4";
		break;
		
		case "return_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;
		
		case "return_5":
			dialog.text = "블루웰드... 이상하군... 내 한쪽 마음은 다시는 푸른 나무랑 들판을 못 볼 줄 알았지...\n...\n ... 크흠, 뭐... 난 스벤슨 좀 만나고 오겠다. 너도 가서 그 자식이랑 앞으로 어떻게 할지 얘기해 봐. 뜨거운 나날이 우리를 기다리고 있으니, 안 그래?";
			link.l1 = "의심할 필요 없지, 스티븐. 순풍이 불길 바란다!";
			link.l1.go = "return_6";
		break;
		
		case "return_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
			sld = ItemsFromID("LSC_navigation_map");
			sld.price = 1000; // лоцию можно выкладывать 270912
			sld = ItemsFromID("keys_skel");
			sld.price = 3000; // отмычки можно выкладывать 270912 
			pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
			CloseQuestHeader("LSC"); // 280313
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "그래, 내가 할 수 있는 건 해줄게! 계속 말해.";
			link.l1 = "스티브, 이것 좀 봐... 상어 이빨이다. 이게 낯설다고는 하지 마라!";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "하! 맞아, 내 이빨이지. 아니, 정확히 말하면 내가 한 여자를 꼬시려고 잡은 상어 이빨이야. 그래서 사람들이 나를 '상어' 도드슨이라고 부르지.\n물속에서 단검 하나로 그런 짓을 해낸 놈은 드물어. 하지만 그땐 내가 젊고 멍청했지, 그리고 비어트리스 샤프는 카리브에서 제일 예쁜 여자였어...\n그걸 어떻게 손에 넣었지?";
			link.l1 = "세인트 존스의 전직 형리한테 받은 거다. 이 칼로 한 남자가 도륙당했지. 이름은 조슈아 리드비터였어.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "음, 네 도살꾼을 찾았구만; 내가 이 이빨로 놈의 목을 그어버렸지.\n베아트리스가 죽었을 때 내 마음이 찢어졌고, 내 손이 닿는 곳에 있는 유일한 죄인은 리드비터라고 믿었어.\n놈이 마지막 숨을 헐떡일 때 주머니에서 몇 장의 서류를 찾았는데, 몇 가지가 명확해지더군. 놈도 복수를 갈망할 만한 이유가 있었지.\n블레이즈의 여동생은 그냥 운이 나쁘게 거기 있었던 것뿐이야. 마스크는 그녀의 죽음에 책임이 없어 – 놈은 오직 도살꾼에게만 관심이 있었으니까. 솔직히... 내가 그를 죽인 걸 후회한다.\n그년 제시카가 이 모든 일을 꾸민 거야.";
			link.l1 = "아직 그 서류들 가지고 있냐?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "당연히 아니지. 난 그놈들이 필요 없었어. 하지만 관심 있으면 왜 마스크가 도살꾼을 쫓았는지 말해줄 수 있지.";
			link.l1 = "그래, 아주 그렇지. 자, 잉크랑 깃펜 좀 줘봐. 내가 전부 적어줄 테니까.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "그래. 그럼 들어봐. 조슈아 리드비터는 영국 함대의 네프튠 호를 지휘하던 선장이었지, 그 배는 이제 전설이 되어버렸어...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("One hour later...", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "... 하지만 리드비터는 살아남았고, 지나가던 배에 의해 구출되었지. 상처 때문에 흉측하게 변했지만 말이야.\n그때부터 그는 항상 가면을 쓰고 다녔고, 자신을 불행에 빠뜨린 놈을 찾아 벌주는 게 인생의 목표가 되었지.";
			link.l1 = "알겠어... 좋아, 내가 한마디도 빠뜨리지 않고 다 적었지. 나중에 다시 읽어볼 거야. 슬픈 이야기군. 제시카를 알았어?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "그래! 그녀는 도살자와 모든 항해를 함께했지, 그가 베아트리스를 위해 그녀를 버릴 때까지 말이야. 제스는 그를 절대 용서하지 않았어.\n사람들은 그녀를 도살자의 부적으로 불렀지. 그녀가 곁에 있는 한, 도살자에게 행운이 따랐거든.\n그가 바베이도스에 그녀를 두고 떠나자마자, 일이 꼬이기 시작했지. 전리품도 끊기고, 넵튠 호는 이슬라 테소로르 조선소의 단골손님이 됐어. 물론 그건 도살자가 갑판이 아니라 선실에서 베아트리스와만 시간을 보냈기 때문이기도 하지.\n베아트리스는 제시카와 달랐어. 모험이나 전투를 갈망하지 않았지. 니콜라스가 그녀에게 검술과 항해술을 가르치긴 했지만, 그녀는 낭만적인 사람이었고 해적이 되기엔 강인하지 못했어.\n이런 삶은 그녀와 맞지 않았고, 결국 그녀를 죽였지.";
			link.l1 = "그럼 제시카는 어쩔 건데?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "오, 그 여자는 정말 대단했지! 넵튠호의 모든 선원들이 그녀의 명령에 토 달지 않고 따랐어, 그게 단지 선장의 여자가 아니라서가 아니었지.\n제스는 검술과 항해술의 달인이었어 - 그녀가 아는 모든 걸 부처에게서 배웠고, 심지어 그를 능가하기도 했지. 강인하고 두려움을 몰랐으며, 천사도 얼굴을 붉힐 만큼 아름다움까지 갖췄지.\n많은 남자들이 그녀를 탐냈지만, 그녀는 오직 부처만을 원했어. 그녀를 쫓는 건 위험한 일이었지; 원치 않는 관심을 보였다간 검술 강의를 공짜로 받게 됐고, 많은 이들에게 그게 마지막 수업이었지.\n제스는 카리브 해에서 유일한 아주 특별한 검을 가지고 있었어. 어디서 구했는지는 나도 전혀 몰라. 불꽃 모양의 칼날을 가진 검이었지. 그 칼날이 살짝만 스쳐도 끔찍한 상처가 남았어.\n제스는 모험가였어 - 태생이 아니라, 스스로 선택한 삶이었지. 그녀에 대해 더 알고 싶으면, 네 친구 중 한 명이 너보다 훨씬 더 많은 이야기를 들려줄 수 있을 거다.";
			link.l1 = "정말이냐? 그게 누구냐?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "얀 스벤손.\n올드 포레스트 데빌은 절대 인정하지 않겠지만, 제시카를 노리고 있었지. 그때가 바로 그가 스페인령 본토를 자기 손에 넣고 명성이 카리브 해 전역에 퍼졌을 때라, 호랑이 같은 그 여자도 자기 것이라 여겼던 거야.\n도살자가 제스를 처리한 뒤, 얀은 바베이도스에 정기적으로 드나들기 시작했지. 그 때문에 영국 놈들이 신경을 곤두세웠어. 알다시피, 제시카는 브리지타운 플랜터의 딸이었거든.\n우린 모두 얀이 무슨 속셈인지 알았고, 이게 아주 나쁘게 끝날 수도 있다는 것도 알았지만 아무 말도 안 했지. 요즘 얀은 블루웰드에서 뒷짐 지고 앉아 있지만, 그땐 그에 대해 조금이라도 험담했다간 독 묻은 칼과 거친 버커니어 무리를 이끌고 네 집 문 앞에 나타났을 거야, 크크...\n결국 얀의 계획은 물거품이 됐지. 제스는 도살자가 자신을 대하는 걸 견딜 수 없었고, 1년 뒤 마스크의 도움을 받아 복수했거든.\n결국 그녀의 복수는 자신을 파멸시켰고, 마스크와 비트리스, 도살자까지 모두 함께 무너졌지.";
			link.l1 = "도살자는 아직 살아 있어.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "... 헛소리야...";
			link.l1 = "스티븐, 부처 선장은 아직 살아 있어. 제이콥 잭맨이랑 헨리 더 행맨이 형리한테 찾아갔지. 교수형은 연극이었어. 내가 증거도 갖고 있어.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "가짜였다고... 그럼 지금 도살자는 어디 있지?!";
			link.l1 = "지금은 자기 이름을 로렌스 벨트로프라고 하고, 포트 로얄에 살고 있어. 그래도 여전히 위험한 놈이지; 형제단에 그렇게 많은 문제를 일으킨 잭맨도 도살자의 명령을 받고 움직였거든.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "빌어먹을! 결국 사관장이 자기 선장한테 돌아왔군!\n벨트로프라고 했지... 잠깐! 이제야 알겠군, 왜 블레이즈 서류에 이상한 심문 기록이 있었는지... 블레이즈도 도살자 벨트로프에 대해 알아낸 모양이야...";
			link.l1 = "무슨 소리를 하는 거야?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "내가 이 거처를 차지한 뒤에, 블레이즈의 옛 문서들을 뒤져봤지. 어떤 새뮤얼 브룩스라는 자의 심문 기록을 찾았어.\n거기엔 '토머스 벨트로프의 모험' 이야기가 있었고, 그가 해적이자 니콜라스 샤프와 매우 가까운 친구로 알려져 있다고 나와 있더군!\n토머스가 바로 부처의 아버지였던 것 같아.";
			link.l1 = "흥미롭군... 샤프와 벨트로프의 자식들이 부모의 일을 이어가는 모양이네...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "그런 것 같군... 그런데 말이지, 친구야, 왜 죽은 자들의 행적에 그리 관심이 많은 거냐?";
			link.l1 = "나는 서류가 필요해 - 헬렌 맥아더가 비트리스 샤프의 딸이며 그녀가 그 재산에 대한 모든 권리를 가진다는 걸 증명할 서류 말이야. 벨트로프의 딸이기도 하다는 건 신경 안 써.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "리드비터의 서류나 블레이즈의 기록 어디에도 헬렌 맥아더에 대한 내용은 없어.\n비트리스가 조카가 태어난 걸 블레이즈에게 말하지 않았다니, 그 여자답지 않게 이상하군...";
			link.l1 = "이봐, 샤프의 서류에 다른 뭔가라도 있나? 모든 세부사항이 필요해!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "흠, 그런가... 블레이즈의 기록에 따르면, 그는 여동생이 죽은 섬을 찾으려고 했던 모양이야.\n리드비터의 징벌 원정에 관한 문서들도 있군... 위도 숫자 말고는 별로 흥미로운 건 없어.\n이 위도선은 카리브해 북부를 가로지르지. 하지만 경도는 없어.\n분명 블레이즈의 수색은 실패했겠지; 그 위도선 따라 작은 섬이 얼마나 많은지 상상도 못할 거야.";
			link.l1 = "숫자나 말해.";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "보자... 여기 있군: 북위 21도 32분이야.\n하지만 경도가 없으면 무슨 소용이 있겠어.";
			link.l1 = "그건 내가 알아서 할게. 이야기 들려줘서 고마워, 스티븐. 다음에 또 보자!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "First time";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "dodson"; // 280912
		break;
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "그렇다고 할 수 있지. 이제 토르투가 얘기를 해보자고.\n그 섬 이름이 그렇게 붙은 건 거북이처럼 생겨서야. 뭐, 르바쇠르는 12년 동안 거북이 등껍질을 두껍게 만들고 있었지.\n그 자식의 걸작이 바로 라 로슈 요새야. 정면 공격은 자살행위지; 요새의 대포는 전열함도 박살낼 수 있어.\n이 멋진 섬을 국물로 끓여내긴 쉽지 않을 거다. 스페인 놈들도 오랫동안 시도했지만 아직 성공 못 했으니까.";
			link.l1 = "스벤손이 레바쇠르를 잡는 데 도와주겠다고 약속했어. 네가 계획이 있다던데, 그게 뭐지?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "지난 몇 주 동안 내가 토르투가 거리를 돌아다니게 한 놈들이 꽤 흥미로운 정보를 많이 얻어왔지. 좋은 소식이 있어, 친구야: 라 로슈의 대포를 상대할 필요는 없을 것 같다. 우리만 르바쇠르에게 질린 게 아니야; 그 자를 죽이고 싶어하는 친구들도 있거든.";
			link.l1 = "계속해...";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "르바쇠르가 어린 여자애들을 좋아한다는 건 꽤 유명한 일이야. 한 번 재미를 보고 나면, 그 애들은 사라지지.\n토르투가에서 노예를 주로 공급하는 놈은 갤리온선 볼티쥬르의 로버트 마튼이다. 그의 동료이자 르바쇠르의 조카인 앙리 티보가 항구에서 제일 예쁜 여자애들을 자기 후견인한테 골라주지.\n얼마 전, 마튼이 몰리 존스라는 이름의 영국 브리그에서 미녀 하나를 손에 넣었어. 그 애를 밤에 토르투가의 어떤 비밀 동굴에서 르바쇠르의 조카 티보에게 넘겼지.\n선원들한테는 그 애가 심장마비로 죽어서 시신을 바다에 던졌다고 했지만, 사실 그 시신은 돈 받고 죽인 불쌍한 항구 창녀였을 거다.\n결국 마튼과 티보가 몰리를 르바쇠르한테 넘기지 않고 둘이서 챙기기로 한 모양이야. 르바쇠르가 이걸 알게 되면, 난리 날 거다.";
			link.l1 = "이걸 정말로 우리가 이용할 수 있다고 확신하나? 마르텐이랑 티보도 자기들이 어떤 위험을 감수하는지 잘 알 거다; 분명히 대비책을 세웠을 거야.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			dialog.text = "맞아. 하지만 모든 사슬에는 약한 고리가 있지.\n사흘 전에, 볼티지어 선원 출신 페르낭 루카스라는 놈이 바스테르 선술집에서 술을 너무 마시고 별별 얘기를 다 떠들었어...\n알고 보니 몰리 존스가 자기 오빠한테 도움을 청해 달라고 루카스에게 부탁했다더군. 하지만 루카스는 끝내 그 오빠를 만나지 못했지.\n그는 선장한테서 도망쳐서 지금은 과들루프에서 자신의 비겁함을 잊으려고 술만 퍼마시고 있어.\n앙티가는 프랑스 해적들에게 안전한 곳이 아니야 - 명심해라! 폭스 대령은 자기 아내가 프랑스 사략선에게 죽은 뒤로 섬의 모든 야자수마다 해적을 매달겠다고 맹세했고, 그의 해병대도 그 소원을 이루려고 온 힘을 다하고 있지.";
			link.l1 = "정신 똑바로 차려, 스티븐... 마르텐이랑 티보에 대해 말해 봐. 대체 왜 그렇게 위험을 감수한 거지? 몰리의 매력이 그렇게 강했던 건가, 아니면 그 노예상들이 이번엔 정말 자비라도 베푼 건가?";
			link.l1.go = "terrapin_4";
		break;
		
		case "terrapin_4":
			dialog.text = "나는 그 쓰레기 마르텐을 아주 잘 알지. 저놈이 이런 위험을 감수한다면, 그건 금이 걸려 있거나 아니면 자기 목숨이 달렸다는 뜻이야.\n마르텐이 그 여자애로부터 큰 몸값을 받을 수 있다고 생각하는 걸지도 모르지 - 하지만 그럴 가능성은 적어. 그 아가씨는 하녀 차림으로 토르투가에 도착했거든.\n아니면... 하! 마르텐이 르바쇠보다 더 두려워할 사람이 누굴지 궁금하군...";
			link.l1 = "흠... 티보에 대해 더 말해 봐.";
			link.l1.go = "terrapin_5";
		break;
		
		case "terrapin_5":
			dialog.text = "그 남자에 대해 아는 건 별로 없어, 다만 르바쇠르가 그를 후계자로 삼을 만큼 신뢰한다는 것뿐이지.\n그 여자가 어디에 잡혀 있는지, 왜 티보가 마르텐을 저렇게 풀어놓는지 명확하지 않지만, 이 수수께끼의 답을 알면 토르투가를 쳐들어가지 않고도 이 판을 이길 수 있을 거야. 넌 프랑스 놈이니 이렇게 하는 게 더 좋을 거라 생각했다.\n하지만 서둘러야 해, 루카스의 술주정이 언제 토르투가로 가는 배에 실릴지 아무도 몰라. 우리가 움직이기 전에 르바쇠르 귀에 들어가면... 우린 좆되는 거다!";
			link.l1 = "바로 떠나겠다.";
			link.l1.go = "terrapin_6";
		break;
		
		case "terrapin_6":
			dialog.text = "이렇게 해라: 먼저 앤티과에 가. 몰리가 루카스를 자기 오빠 찾으라고 거기로 보냈거든; 아마 그 오빠가 네게 도움이 될 만한 정보를 갖고 있을지도 몰라.\n그 다음엔 과들루프로 엉덩이 끌고 가. 루카스를 찾아서 마르탱, 티보, 볼티저, 그리고 몰리에 대해 알아낼 수 있는 건 전부 캐내.";
			link.l1 = "고마워, 스티븐. 앤티가, 그리고 그 다음은 과들루프.";
			link.l1.go = "terrapin_7";
		break;
		
		case "terrapin_7":
			DialogExit();
			AddMapQuestMarkCity("SentJons", true);
			AddMapQuestMarkCity("BasTer", true);
			AddQuestRecord("Terrapin", "1");
			pchar.questTemp.Terrapin = "baster";
			pchar.questTemp.Terrapin.SJ_count = 0;
			// прячем Фокса
			sld = characterFromId("Fox");	
			ChangeCharacterAddressGroup(sld, "none", "", "");
			// садим в таверну Робера Мартэна
			float fMft = MOD_SKILL_ENEMY_RATE/10;
			sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
			FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
			sld.name = "Rober";
			sld.lastname = "Marten";
			sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
			sld.dialog.currentnode = "Rober";
			sld.greeting = "pirat_common";
			TakeNItems(sld, "potion2", 1);
			TakeNItems(sld, "potion3", 2);
			SetCharacterPerk(sld, "Energaiser");
			SetCharacterPerk(sld, "BasicDefense");
			SetCharacterPerk(sld, "AdvancedDefense");
			SetCharacterPerk(sld, "CriticalHit");
			SetCharacterPerk(sld, "Tireless");
			SetCharacterPerk(sld, "HardHitter");
			SetCharacterPerk(sld, "Sliding");
			SetCharacterPerk(sld, "BladeDancer");
		
			SetCharacterPerk(sld, "Gunman");
			SetCharacterPerk(sld, "GunProfessional");
			SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterPerk(sld, "LongRangeGrappling");
			SetCharacterPerk(sld, "GrapplingProfessional");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "SailsDamageUp");
			SetCharacterPerk(sld, "CrewDamageUp");
			SetCharacterPerk(sld, "CriticalShoot");
			SetCharacterPerk(sld, "LongRangeShoot");
			SetCharacterPerk(sld, "BasicBattleState");
			SetCharacterPerk(sld, "AdvancedBattleState");
			SetCharacterPerk(sld, "ShipDefenseProfessional");
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "ShipTurnRateUp");
			SetCharacterPerk(sld, "WindCatcher");
			SetCharacterPerk(sld, "SailsMan");
			SetCharacterPerk(sld, "Doctor1");
			SetCharacterPerk(sld, "Doctor2");
			sld.MultiFighter = 1.0+fMft; // мультифайтер
			LAi_SetSitType(sld);
			UpgradeShipParameter(sld, "SpeedRate");//апгрейдить скорость
			UpgradeShipParameter(sld, "TurnRate");//манёвренность
			FreeSitLocator("Baster_tavern", "sit1");
			ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
			if(bImCasual)
			{
				NewGameTip("Exploration mode: quest duration doubled");
				SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
			}
			else SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер
			
			// Квест "Погасшая Звезда" провалена, всё удаляем
			if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
			{
				CloseQuestHeader("PZ");
				DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
				DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
				DeleteQuestCondition("PZ_Etap5_Start");
				DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
				DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
				DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
				pchar.questTemp.PZ_ProvalFinal = true;
			}
		break;
		
		case "terrapin_8":
			dialog.text = "계속해!";
			link.l1 = "나는 세인트 존스에서 몰리의 오빠를 찾았어. 그 사람은 폭스 대령의 서기야. 그런데 뭔가 이상해... 그가 자기 여동생 몰리를 네 키만큼 크고, 유명한 마녀라고 묘사했거든. 물론 너만큼 예쁘진 않다고도 했지. 몰리는 폭스의 딸 캐서린의 하녀고, 최근까지 영국에서 캐서린과 함께 있었다더라...\n";
			link.l1.go = "terrapin_9";
		break;
		
		case "terrapin_9":
			dialog.text = "";
			link.l1 = "캐서린이라면, 미인으로 소문난 건 사실이고 아버지 생신에 맞춰 방문하려 했지만, 그녀를 태운 함대가 지연됐지...";
			link.l1.go = "terrapin_10";
		break;
		
		case "terrapin_10":
			dialog.text = "";
			link.l1 = "폭스 대령이 호위 함대 없이 영국을 떠나는 걸 금지했으니, 몰리 존스가 티보의 포로일 리는 없어. 그럼 대체 그녀는 누구지...?";
			link.l1.go = "terrapin_11";
		break;
		
		case "terrapin_11":
			dialog.text = "흠... 젠장, 나도 모르겠군. 아마 네가 찾던 그 몰리 존스가 아니라 그냥 다른 몰리 존스일지도 모르지.\n하지만... 우연치고는 너무 많아. 이게 다 우연이라고는 믿기 힘들어!\n있잖아... 나도 짐작은 가는데, 말이지...";
			link.l1 = "무슨 소리야? 말해 봐!";
			link.l1.go = "terrapin_12";
		break;
		
		case "terrapin_12":
			dialog.text = "... 만약 캐서린이 아버지의 명령을 어기고 호위도 없이 출항했다면 어쩌겠어? 지난달은 폭풍이 심했으니, 알바트로스가 손상돼서 마르텐에게 손쉬운 먹잇감이 됐을 수도 있지.\n내 생각엔 캐서린이 진짜 이름을 마르텐에게 숨기고, 대신 몰리의 이름을 댄 것 같아 - 이유는 알겠지!";
			link.l1 = "젠장! 그렇다면 모든 게 맞아떨어지긴 하는데... 그래도 이건 지옥 같은 추측이잖아!";
			link.l1.go = "terrapin_13";
		break;
		
		case "terrapin_13":
			dialog.text = "내 말이 그거야, 친구. 내가 틀릴 수도 있지만...";
			link.l1 = "... 하지만 그게 사실이라면, 모든 게 달라지지! 영국 놈들한테 지원을 요청하고, 바다여우들의 총검으로 길을 열 수 있겠군!";
			link.l1.go = "terrapin_14";
		break;
		
		case "terrapin_14":
			dialog.text = "진정해, "+pchar.name+"! 증거가 필요해. 내가 말했듯이, 내가 틀렸을 수도 있고, 캐서린은 아직 런던에 있으면서 호위를 기다리며 출항 준비 중일 수도 있지.\n영국 놈들도 자기들 문제로 골치 아파서 라 로슈를 공격할 배짱은 없어. 하지만 우리가 맞고, 폭스 대령이 자기 딸에게 무슨 일이 생겼는지 알게 된다면...\n그자는 토르투가 주변에 봉쇄선을 치고 증원군을 기다릴 거야. 그리고 도시를 공격하겠지. 시폭스 놈들은 근접전에서 무시무시하니, 군인도 민간인도 피를 많이 볼 거다.\n그리고 결국, 난 확신하는데, 사흘 뒤엔 토르투가 폐허 위에 영국 깃발이 펄럭이게 될 거야. 그걸 정말 바라는 거냐?";
			link.l1 = "아니... 아니, 없어. 이제야 마르텐이 말한 몸값이 뭔지 알겠군.";
			link.l1.go = "terrapin_15";
		break;
		
		case "terrapin_15":
			dialog.text = "조심해야 해. 마르텐이 캐서린의 진짜 정체를 알고 있는지도 확실치 않아. 콜로넬 폭스를 협박하는 건 자살행위지, 특히 크롬웰 함대가 카리브 해에 도착하는 상황에선 더더욱.\n우리 때문에 캐서린이 죽으면, 우린 진짜 큰일 나는 거야. 콜로넬 폭스가 자기 딸을 우리가 죽였다고 믿으면 해적 연맹 전체를 박살낼 수도 있어.\n하지만 결국 캐서린이 죽어야 한다면, 절대 우리가 한 짓처럼 보이면 안 되고, 그녀가 우리 목표 달성에 도움이 되게 해야 해.\n제일 좋은 건 그 애를 아버지한테 돌려주는 거지. 구해준 사람은 두둑이 보상받을 테니까, 크크...";
			link.l1 = "스티븐, 너 천재구나! 나 토르투가로 간다. 몰리가 캐서린 폭스인지 확인해 볼게.";
			link.l1.go = "terrapin_16";
		break;
		
		case "terrapin_16":
			dialog.text = "시간 낭비하지 마, "+pchar.name+". 그리고 내 말이 맞는 게 밝혀지면, 그 계집애 반드시 살려둬라.";
			link.l1 = "내가 할 수 있는 건 다 하겠다.";
			link.l1.go = "terrapin_17";
		break;
		
		case "terrapin_17":
			DialogExit();
			AddQuestRecord("Terrapin", "7");
			pchar.questTemp.Terrapin = "tortuga1";
			pchar.questTemp.Terrapin.Room_close = "true": // не пускать в комнату таверны
		break;
		
		case "guardoftruth":
			dialog.text = "호호! 말해 봐, 친구! 어떤 문제든 우리가 확실하게 해결해 줄 테니!";
			link.l1 = "그럼 바로 본론으로 들어가지. 미겔 디초소를 아나?";
			link.l1.go = "guardoftruth_1";
		break;
		
		case "guardoftruth_1":
			dialog.text = "그 자 알아. 그 스페인 돈이 나한테 끝내주는 배를 팔았지 - 프리깃함이었어. 에이, 그 배가 얼마나 대단했는지 상상이나 해봐...";
			link.l1 = "짐작해 보지. 독특한 선체에, 최대 속력은 열여섯 노트? '산타 키테리아' 맞지?";
			link.l1.go = "guardoftruth_2";
		break;
		
		case "guardoftruth_2":
			dialog.text = "녀석의 선체랑 속도는 네 말이 맞아, 하지만 이름이 달랐어 - '산 마르틴'이었지. 나는 그놈한테 금을 엄청나게 쏟아부었어, 가진 거 전부였지. 내 모든 저축이 그 사기꾼 주머니로 곧장 들어갔다고.";
			link.l1 = "그 배 이름이 산 마르틴이 맞고 산타 키테리아가 아니라는 거 확실해? 그리고 언제 샀지? 또 왜 그를 악당이라고 부르는 거야?";
			link.l1.go = "guardoftruth_3";
		break;
		
		case "guardoftruth_3":
			dialog.text = "질문이 참 많구나! 하나씩 다 대답해주지. 우선, 그 배는 산 마르틴이 맞다. 내가 직접 알렉서스 일꾼들 도와서, 선미에 붙어 있던 그 교황쟁이 이름이 적힌 판자를 떼어냈지. 내가 그 배 이름을 '포춘'이라 붙였어. 그런 공주님 같은 배엔 훨씬 어울리는 이름이지.  
그 배는 1654년 겨울, 블레이즈 샤프가 살해되기 얼마 전에 샀다. 미겔을 왜 그렇게 불렀냐고? 그 개자식이 프로비던스 스페인 군기지에서 그 배를 훔쳐내는 데 성공했거든. 우리도 그놈들에게 한바탕 구경거리를 보여줬지, 산 후안 요새 바로 앞에서 말이야. 내가 반쯤 죽은 러거 두 척을 희생해서 싸움이 진짜처럼 보이게 만들었다. 배에 불을 지르고 침몰시키면서 프리깃과의 전투를 연출했지. 그리고 어둠이 깔리자마자 산 마르틴을 이슬라 테소로로 몰고 갔다... 나는 배를 얻었고, 디초소는 돈을 챙겼지. 그는 상관에게 프리깃이 해적들과의 전투에서 침몰했다고 보고했고, 산 후안 사령관도 그걸 확인해줬다.";
			link.l1 = "그래서 스페인 돈들이 저렇게 주머니를 채우는 거였군! 이런 개자식 같으니라고! 말해 봐, 그게 정말 1654년 겨울에 일어난 일이냐? 아니면 봄이었나? 그리고 프리깃이 폭풍에 손상된 거냐?";
			link.l1.go = "guardoftruth_4";
		break;
		
		case "guardoftruth_4":
			dialog.text = "겨울에... 젠장, 확실하지가 않아 - 봄이었을 수도 있지. 사실 잘 기억이 안 나. 프리깃은 멀쩡했어, 완전 새 배였지. 막 건조된 것처럼 보였거든. 그 배만 생각하면 분해서 눈물이 다 날 지경이야...";
			link.l1 = "왜? 그래, 그리고 네 멋진 프리깃함은 지금 어디 있지?";
			link.l1.go = "guardoftruth_5";
		break;
		
		case "guardoftruth_5":
			dialog.text = "그녀가 내 곁을 떠났기 때문이지. 놈들이 나를 함정에 빠뜨렸어, 내 부적을 블레이즈 시체에 올려놓고 내가 살인자라고 소문을 퍼뜨렸지. 그러다 마커스 타이렉스, 우리 암호 담당이 나한테 블랙 마크를 내릴 거라는 소문을 들었어. 그래서 그 엉망진창에서 잠시 벗어나려고 정의의 섬에 숨기로 했지, 네가 나를 거기서 찾았던 그곳에서 말이야\n프리깃으로는 거기 갈 수 없어서 블랙 파스터에게 그 배를 맡기고, 식량 가득 실은 브리그와 맞바꿨어. 그 교활한 디초소와 거래한 뒤엔 돈도 별로 없었거든. 식량을 팔아서 한두 달 안에 이슬라 테소로로 돌아가려고 했지... 뭐, 그 다음은 네가 다 알잖아.";
			link.l1 = "그리고 블랙 파스터는 널 기다리지도 않고, 그녀를 팔아버렸지\n";
			link.l1.go = "guardoftruth_6";
		break;
		
		case "guardoftruth_6":
			dialog.text = "정확히 그래. 그 여자는 한 영국인, 아니, 더 정확히 말하면 스코틀랜드 놈, 윌리엄 패터슨한테 팔렸지. 내가 그 계집애를 돌려받으려고 해볼 수도 있겠지만, 이 하이랜더는 만만치 않은 놈이야. 왕립 해군의 선장이자, 폭스 대령의 절친이지. 게다가, 네가 스벤손이랑 거래했던 것처럼 이 자식도 잭맨이랑 장사했어\n그 스코틀랜드 놈은 함대까지 끌고 다녀... 젠장, 내 배는 다시 못 보겠구만.";
			link.l1 = "알겠어. 지금 그 디초소가 어디 있는지 모르겠나?";
			link.l1.go = "guardoftruth_7";
		break;
		
		case "guardoftruth_7":
			dialog.text = "나도 모르겠어. 내가 내 포춘호를 산 이후로 그를 본 적이 없어.";
			link.l1 = "그런데 미겔은 왜 다른 놈한테 그걸 사겠다고 하지 않았지? 타이렉스나 바르바존, 샤프는 어때? 아니면 패터슨은?";
			link.l1.go = "guardoftruth_8";
		break;
		
		case "guardoftruth_8":
			dialog.text = "나도 모르겠어. 내가 기억하기로는 그때 패터슨은 여기 없었어. 자카리아, 자크, 마커스라면 절대 동의하지 않았을 거고, 나는... 나는 그 프리깃선을 정말 좋아했거든!";
			link.l1 = "알겠다고 했지만... 아무것도 모르겠군. 온통 수수께끼뿐이야...";
			link.l1.go = "guardoftruth_9";
		break;
		
		case "guardoftruth_9":
			dialog.text = "또 과거를 파헤치려고? 이번엔 어느 섬을 차지하고 싶어? 하하하!";
			link.l1 = "섬이 하나 있지... 아직 그곳으로 가는 길은 못 찾았어. 좋아, 스티븐, 정보 고맙다! 잘 있어라!";
			link.l1.go = "guardoftruth_10";
		break;
		
		case "guardoftruth_10":
			dialog.text = "행운을 빌지, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "guardoftruth_11";
		break;
		
		case "guardoftruth_11":
			DialogExit();
			AddQuestRecord("Guardoftruth", "60");
			pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
			// маленькая развлекуха
			pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
			pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;
		
		case "tieyasal":
			dialog.text = "그리고 난 항상 그렇듯이 너를 도와줄 수 있어서 기쁘다. 이번엔 뭘 원하는 거냐, "+pchar.name+"?";
			link.l1 = "또 네 옛 친구 미겔 디초소 얘기다. 그가 다시 이슬라 테소로에서 목격됐다는 걸 알고 있지. 그를 찾는 데 좀 도와줄 수 없겠나?";
			link.l1.go = "tieyasal_1";
		break;
		
		case "tieyasal_1":
			dialog.text = "이봐, 친구, 사실 그건 몰랐네. 여기서 그를 본 적 없어. '포춘'을 그에게서 산 이후로는 본 적도 없고. 그런데 그 스페인 돈이 왜 필요하지?";
			link.l1 = "난 그가 필요해. 미겔은 오래된 인디언 도시로 가는 길을 알아. 난 정말 거기에 가고 싶어.";
			link.l1.go = "tieyasal_2";
		break;
		
		case "tieyasal_2":
			dialog.text = "늘 그렇듯이, 친구야, 또다시 골치 아픈 일에 끼어들 셈이구나. 안타깝게도 내가 도와줄 수는 없어. 정착지를 돌아다니면서 사람들에게 물어봐. 아마 누군가 그를 봤을지도 몰라. 여기서는 꽤 유명한 인물이거든.";
			link.l1 = "이봐, 스티븐, 적어도 그놈이 어떻게 생겼는지는 말해줄 수 있겠어?";
			link.l1.go = "tieyasal_3";
		break;
		
		case "tieyasal_3":
			dialog.text = "글쎄, 그는 스물다섯에서 스물여덟 살쯤이고, 너만큼 키가 크며, 눈은 어둡고, 가발은 쓰지 않았어. 오른쪽 뺨에 군도 흉터가 있지.";
			link.l1 = "흠. 있잖아, 그 설명에 딱 맞는 놈들이 여럿 있지.";
			link.l1.go = "tieyasal_4";
		break;
		
		case "tieyasal_4":
			dialog.text = "그에 대해 특별한 다른 정보는 없어. 자신감 넘치고, 건방지며 아주 위험한 놈이지. 그에 대한 소문도 돌았었지...";
			link.l1 = "알겠다. 좋아, 그에 대해 알아봐 줄게. 행운을 빌어, 스티븐!";
			link.l1.go = "tieyasal_5";
		break;
		
		case "tieyasal_5":
			DialogExit();
			AddQuestRecord("Tieyasal", "2");
			npchar.quest.tieyasal = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "호호! 제대로 찾아왔구만! 얼른 말해 봐!";
			link.l1 = "해적을 두려워하지 않는 놈이 하나 있어. 우리를 우습게 보는 거지. 존중이 뭔지 뼈저리게 가르쳐 줘야 해. 하지만, 죽이지는 마라.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "허! 이게 누구야, 바로 그 늙은이 찰스 아니냐! 또 무슨 일에 휘말린 거지? 자, 자세히 말해 봐. 이번엔 누구를 노리는 거고, 그놈한테 뭘 가르쳐줘야 하지?";
			link.l1 = "유럽에서 온 손님이 있는데, 프랑스 재무부의 감찰관이자 남작인 노엘 포르게라는 자야. 여기서 프랑스 무역회사를 세우려 한다는데, 나랑 내 가까운 친구가 반대하고 있지. 남작을 설득하려고 했어, 여기서 무역하는 건 네덜란드 놈들, 영국 놈들, 그리고 특히 르바쇠르가 당한 뒤로 해적들 때문에 아주 위험하다고 말이야. 하지만 그 자는 들으려 하지 않았지. 놈이 직접 뼈저리게 느끼게끔 겁을 줘야 해.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "그래그래... 진짜 남작이라니!.. 우리가 그 자의 배를 털어볼까?";
			link.l1 = "계획은 이렇다: 그의 배가 곧 포르토프랭스에서 캡스터빌로 출항할 거다.\n출항한 뒤에 그 바론을 가로채서 인질로 잡아야 해.\n배를 침몰시키지 말고, 선원들도 죽이지 않는 게 좋겠지. 프랑스 놈들은 어쨌든 우리 친구니까.\n그 정도는 할 수 있겠지?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "글쎄, 장담은 못 해. 하지만 해볼게. 어떤 배지?";
			link.l1 = "'파보리'라는 브리그야.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "브리그 따위 내 프리깃상대도 안 돼. 우린 쉽게 처리할 거야. 만약 항복하면, 전원 살려주지.";
			link.l1 = "완벽해. 공포를 심어주고 항복할 기회를 줘라. 그 다음엔 남작을 쥐들이 들끓는 창고에 쳐넣어. 최대한 더러운 곳을 찾아보되, 하루 이상은 두지 마라. 오래 있으면 병들어 죽을 수도 있으니까. 그 다음엔 선실로 옮기고, 정의의 섬으로 가서 외진 곳에 가둬놔. 네 부하 몇 놈을 프랑스 상인으로 위장시켜서 진짜처럼 행동하게 해. 사흘 내내 남작한테 잔인한 해적들이 어떻게 쫓아오고, 약탈하고, 몸값을 요구하고, 고문하는지... 필요한 모든 세부사항까지 다 들려주게 해.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "하하하! 이렇게 웃기는 일은 오랜만이구나! 좋아, 친구야. 내가 그런 배우들을 찾아주지. 의심하지 마라, 그놈들 이야기를 들으면 네 남작은 바지에 똥을 지릴 거다! 칼자국이랑 달군 총봉 자국까지 다 보여줄 테니...\n ";
			link.l1 = "잘했군. 이제 그놈을 시켜서 푸앵시에에게 몸값 요구 편지를 쓰게 만들어라. 저런 거물치고 삼백오십만이면 그리 큰돈도 아니지.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "좋아. 이제 뭘 할 거지?";
			link.l1 = "그리고 나서 네가 남작을 터크스로 데려가. 거기서 몸값을 받고, 나한테 남작을 넘겨. 그리고 한 가지 더, 모든 프랑스 놈들이 토르투가와 르바쇠르 일로 책임지게 될 거라고 꼭 전해라.";
			link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "하하하! 이거 제대로 한방 먹였구만! 우리야, 뭐, 르바쇠 놈한테 뭘 했는지 알잖아, 그런데 이제는... 하하하!.. 좋아, 친구. 그렇게 해주지! 배가 곧 도착한다는 거지?";
			link.l1 = "곧이야. 경계 태세를 유지해야 해.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "신경 쓰지 마, 내가 실망시키지 않을 거야. 이건 내가 직접 처리할 테니까. 이 바론이 잡혔다는 소문이 들리면 나한테 와.";
			link.l1 = "좋아. 고맙다, 스티븐.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "70");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;
		
		case "patria_10":
			dialog.text = "당연하지, 친구야. 약속대로지. 사악한 해적들이 무고한 프랑스 상인들을 도륙하는 무시무시한 이야기, 채찍 소리, 신음과 비명. 숯불이 피워진 화로와 그을린 수갑. 그래야 제맛이지.";
			link.l1 = "자, 진정해! 그 놈은 살아있어야 해.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "걱정 마, 그 녀석은 살아 있을 거야. 손이 떨리면서도 그 편지를 썼더군. 여기 있다.";
			link.l1 = "거기 뭐라고 적혀 있지? 저 자식이 푸앵시한테 여기서 꺼내 달라고 빌고 있는 거야?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "정확해, 이 친구야! 저놈이 빌고 있잖아!";
			link.l1 = "이 편지는 버려라, 아니면 차라리 불태워라. 일주일 뒤 터크스에서 만나자. 우리가 몸값을 모으는 데 시간이 필요한 것처럼 보여야 한다.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "알겠어. 일주일 뒤, 북쪽 만에서. 돈 챙기는 거 잊지 마라: 그럴싸하게 보여야 하니까. 끝나면 나한테 와, 정산하자.";
			link.l1 = "당연하지, 해삼조차도 그 정도는 알았겠지. 나중에 보자! ";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "이봐, 개구리 처먹는 놈! 멈춰!";
			link.l1 = "난 안 움직여.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "여기 자네네 남작이다. 좀 험하게 다뤄졌지만 멀쩡히 살아있어. 이놈 맞지?";
			link.l1 = "그래.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "완벽해. 이제 돈 내놔, 아니면 이 녀석 끝장난다! 그리고 꼼수 부릴 생각 마라, 우린 이미 너를 조준하고 있으니까!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "여기.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "젠장! 그걸 배에 두고 왔네...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "하하하! 똑똑하구나, 프랑스 놈. 네 거룩함이나 가져가라. 그리고 푸앵시한테 돈 준비하라고 전해라. 프랑스 개자식들은 레바쇠르와 토르투가에서 네가 한 짓값을 다 치르게 될 거다. 그리고 너희 상인들은 물건이랑 배로 우리한테 값을 치르게 될 거야. 하하하! 군도에 남작들을 더 데려오는 것도 잊지 마라, 그놈들 덕에 우리가 이득을 많이 보거든! 하하하!";
			link.l1 = "내 배로 가 줘, 남작.";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "그리고 우리를 쫓을 생각도 하지 마, 선장. 내가 누군지 알잖아. 난 개구리 먹는 놈들 포로를 더 많이 잡고 있어. 내가 제때 돌아가지 않으면 내 놈들이 전부 죽여버릴 거야. 알겠어?";
			link.l1 = "때가 오면 너희랑 결판을 내주마, 이 저주받은 불경한 놈들아!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "하하하하!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "나랑 장난치는 거야?";
			link.l1 = "잠깐만, 내가 가져올게...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "아으, 스티븐, 네 멍청이가 또 무슨 짓을 한 거냐!";
			link.l1.go = "patria_25";
		break;
		
		case "patria_25":
			dialog.text = "찰스, 뭐 하고 있었어? 돈은 어디 있지? 내 부하들한테 이게 가짜라고 말 안 했거든... 그래서 이 멍청이가 네가 걔네를 속이려 한다고 생각했지...";
			link.l1 = "안됐군! 남작이 죽었어... 이제 푸앵시는 어쩔 셈이지?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_26":
			dialog.text = "그래, 이 친구야, 이건 네 잘못이야. 그건 네가 알아둬야 해. 어쩌면 그게 너한테 더 나을 수도 있겠지.";
			link.l1 = "내가 진짜 바보구나! 다 망쳐버렸어. 좋아, 푸앵시에 갈게... 내가 멍청이라서 미안하다, 스티븐. 또 보자.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "좀 쉬어야겠어, 감이 떨어지고 있잖아. 나중에 한 번 찾아와, 럼주랑 멋진 아가씨들 좀 붙여줄 테니까.";
			link.l1 = "고맙다, 시간 나면 찾아가겠다.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "천만에, 친구야. 난 올해 이렇게 재밌었던 적이 없었지! 나랑 내 놈들이 얼마나 웃었는지 몰라!.. 그래서 고맙다는 뜻으로 한마디 하려고. 여기 네 돈이다.";
			link.l1 = "네 몫은 챙겨둬야지.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "잊어버려. 우리 우정을 위해 한 일이야. 해안의 형제단이 너한테 진 빚이 훨씬 더 많지만, 너는 두블룬 한 닢도 요구하지 않았지.";
			link.l1 = "그래도 수고비랑 보상으로 최소 오만은 가져가. 고마워, 스티븐! 한때 그 난파선들로 이루어진 이상한 섬, 정의의 섬에서 너를 만난 게 정말 다행이야.";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "나도 그렇지. 찰스, 시간 날 때 언제든 나한테 들러!";
			link.l1 = "기꺼이!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "일주일이나 늦었군! 내가 내 놈들에게 이게 진짜가 아니라고 말하지 않았지...! 더는 못 기다리겠다고 하더니, 네 놈의 남작질을 끝장내기로 했어!";
			link.l1 = "내가 진짜 바보구나! 다 망쳐버렸잖아! 푸앵시에 뭐라고 말하지?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_34":
			dialog.text = "그래, 친구야, 이건 네 잘못이야, 그건 알고 있겠지. 어쩌면 그게 너한테 더 나을 수도 있겠군.";
			link.l1 = "좋아, 푸앵시에 갈게... 내가 바보였던 걸 용서해 줘, 스티븐, 또 보자..";
			link.l1.go = "patria_35";
		break;
		
		case "patria_35":
			dialog.text = "좀 쉬어야겠어, 감이 떨어지고 있잖아. 나중에 나한테 와, 럼주랑 멋진 아가씨들 좀 구해줄 테니까.";
			link.l1 = "고맙다, 시간 나면 한 번 찾아가마.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		// belamour legendary edition хвастаемся Фортуной
		case "check_out_my_frigate":
			dialog.text = "재미있군, 흥미가 생겼어. 자, 한 바퀴 돌자.";
			link.l1 = "...";
			link.l1.go = "check_out_my_frigate_01";
		break;
		
		case "check_out_my_frigate_01":
			DialogExit();
			chrDisableReloadToLocation = true;
			bDisableFastReload = true;
			DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
			pchar.questTemp.SharkFrigate = true;
		break;
		
		case "check_out_my_frigate_02":
			dialog.text = "내 비장 터지겠네! 내 두 눈을 못 믿겠어! 진짜 저거냐? 말해 봐, 진짜 저거냐? 저게 바로 '포춘'이냐?!";
			link.l1 = "그래, 친구야, 네 눈이 속이지 않았어. 저게 바로 그 배야. 그리웠냐?";
			link.l1.go = "check_out_my_frigate_03";
		break;
		
		case "check_out_my_frigate_03":
			dialog.text = "하하하, 믿기지가 않는군! 천 개의 악마가 따로 없네! 그런데 그걸 어디서 구한 거야?";
			link.l1 = "윌리엄 패터슨이라는 스코틀랜드 놈한테서 말이야. 그래, 그래, 그 검은 신부한테서 그걸 산 놈 맞다.";
			link.l1.go = "check_out_my_frigate_04";
		break;
		
		case "check_out_my_frigate_04":
			dialog.text = "이런 젠장... 뭐라고, 그놈이 '포춘'을 너한테 팔았다고? 그렇게 멋진 배를? 네가 이미 샀는데도?";
			link.l1 = "헤헤, 뭐, 거의 맞아. 이렇게 말하자면 되겠군: 우린 전혀 사이가 좋지 않았고, 내가 우리 다툼 때문에 입은 손해에 대한 보상으로 그 배를 가져왔지. 어차피 그 녀석은 배가 필요 없으니까.";
			link.l1.go = "check_out_my_frigate_05";
		break;
		
		case "check_out_my_frigate_05":
			dialog.text = "너 정말 나를 더 놀라게 하는군 ... 그 자는 영국 소속의 군대 선장이야. 원하면 식민지 함대까지 털 수 있는 놈이지. 나조차도 그놈한테 덤비진 못했어. 그런데 어떻게 확인했지? '포춘'을 그 함대에서 떼어내는 데 성공한 거야?";
			link.l1 = "아니, 함대는 침몰했어. 사실 쉽지 않았지. 전투는 치열했지만, 사람이 사는 곳에서 멀리 떨어진 곳에서 벌어졌고, 목격자는 내 선원들과 장교들뿐이었어. 대체로, 나는 영국 당국의 추적이 두렵지 않아. 윌리엄 패터슨은 그냥 평소처럼 모험하다가 사라져버렸지...\n";
			link.l1.go = "check_out_my_frigate_06";
		break;
		
		case "check_out_my_frigate_06":
			dialog.text = "이런 젠장... 내 제비를 다시 볼 희망은 오래전에 접었지. 뭐, 이 배가 너한테 충실히 봉사하길 바란다. 정말 잘 됐구나, 친구!";
			link.l1 = "뭐? 그 자가 필요 없다고? 나는 정당한 주인에게 돌려주고 싶었는데...";
			link.l1.go = "check_out_my_frigate_07";
		break;
		
		case "check_out_my_frigate_07":
			if(CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
			{
				dialog.text = "하하하, 친구야, '포춘'은 네가 갖고 있어라. 첫째, 네가 그 배의 정당한 주인이지. 전투에서 당당히 얻은 거니까. 이런 뒤에 배를 버리는 건 옳지 않아. 그리고 둘째, 난 이미 새 배가 있거든. 사실 '포춘'을 샀을 때는 다른 배로 바꿀 거라곤 생각도 못 했지. 하지만 다시 볼 거라 기대도 안 했으니, 알렉수스에게 새 프리깃을 주문했어. 그리고 말인데... 그 배, 정말 끝내주더라. 네가 한몫했다는 얘기도 들었지, 하하!\n";
			}
			else
			{
				dialog.text = "하하하, 친구야, '포춘'은 네가 가져라. 첫째, 그 배는 네가 정당한 주인이야. 네가 전투에서 정직하게 얻은 거니까. 이쯤에서 배를 버리는 건 옳지 않아. 그리고 둘째, 나한텐 이미 새 배가 만들어지고 있거든. 사실, 내가 '포춘'을 샀을 때는 다른 배로 바꿀 거라곤 생각도 안 했지. 하지만, 다시 볼 거라 기대도 안 했으니, 알렉수스에게 새 프리깃을 주문했어. 그 갑판에 다시 발을 딛게 될 날만을 손꼽아 기다리고 있지.";
			}
			link.l1 = "그럼 어쩔 수 없지, 이 아름다운 배는 내가 가지겠어, 스티븐!";
			link.l1.go = "check_out_my_frigate_08";
		break;
		
		case "check_out_my_frigate_08":
			dialog.text = "맞아. 내가 너한테 딱 하나 바라는 건 '포춘'을 잘 돌봐 달라는 거야. 믿어라, 그런 배는 어디 가도 못 구한다. 정말 유일무이하지. 그리고 난 그 배를 추억으로서 아끼고 있어. 내 친구가 이 배의 주인이 된다는 걸 알면 기쁠 거야, 아무 쓸모없는 놈이 아니라 말이지.";
			link.l1 = "좋아, 스티븐. '포춘'은 내가 반드시 지키겠다고 약속하지.";
			link.l1.go = "check_out_my_frigate_09";
		break;
		
		case "check_out_my_frigate_09":
			dialog.text = "그래, 그리고 한 가지 더...";
			link.l1 = "듣고 있지.";
			link.l1.go = "check_out_my_frigate_10";
		break;
		
		case "check_out_my_frigate_10":
			dialog.text = "이제 '포춘'을 가졌으니, 한 가지 거래를 제안하고 싶군.";
			link.l1 = "네 말 아주 잘 듣고 있어.";
			link.l1.go = "check_out_my_frigate_11";
		break;
		
		case "check_out_my_frigate_11":
			if(!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
			{
				dialog.text = "내가 말했듯이, 알렉서스가 지금 나를 위해 새 프리깃을 만들고 있어. 물론 그 녀석이 '포춘'보다 더 빠르게 만들긴 힘들겠지만, 크게 뒤지진 않을 거야. 그리고 내가 딱 한 가지를 위해 강력하면서도 빠른 배 두 척이 필요하지. 혼자서도 할 수 있을지 모르지만, 둘이 훨씬 낫지.";
				link.l1 = "좋아. 그런데 이게 무슨 일이지?";
				link.l1.go = "check_out_my_frigate_12";
			}
			else
			{
				dialog.text = "내가 말했듯이, 알렉서스가 최근에 나를 위해 새 프리깃을 만들었지. 물론 그 녀석이 '포춘'보다 빠를 것 같진 않지만, 크게 뒤지진도 않을 거야. 그리고 내가 꼭 필요한 게 강력하면서도 빠른 배 두 척이거든. 혼자서도 할 수 있을지 모르지만, 둘이 훨씬 낫지.";
				link.l1 = "좋아. 그런데 이게 무슨 일이지?";
				link.l1.go = "check_out_my_frigate_13";
			}
		break;
		// Фрегат Акулы не построен
		case "check_out_my_frigate_12":
			dialog.text = "아직 그 얘기를 하기엔 이르다. 내 새 배가 언제 조선소에서 나올지 아직 모르거든. 알렉서스가 자재 구하는 데 좀 애를 먹는 것 같아. 그런데 말인데, 기회가 된다면 그 녀석 좀 도와줘도 되겠지. 분명히 제대로 보수는 줄 거다. 내가 이미 꽤 큰 선금을 줬으니까. 자재만 다 구하면 한 달쯤 뒤엔 내 배가 준비될 거라 본다. 그때 널 기다릴게. 하지만 꼭 '포춘'호를 타고 미리 준비해서 와라, 그때는 시간이 별로 없을 테니까! 그리고 스페인 놈들이 네 목을 은쟁반에 올려놓고 싶어하지 않게 조심해라. 자세한 건 나중에 다 얘기해주지.";
			link.l1 = "좋아, 우리 배 만드는 놈한테 무슨 도움이 필요한지 물어볼게. 그리고 내가 알렉수스를 도운 뒤 한 달쯤 지나서, 네가 다시 항해할 때쯤 우리 얘기를 이어가자.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		// Фрегат Акулы построен
		case "check_out_my_frigate_13":
			dialog.text = "그 얘기는 아직 이르지. 내 배는 아직 조선소에서 나오지도 않았거든. 아직 장비도 갖춰야 해. 그러니 한 달은 지나야 널 기다릴 거다. 하지만 꼭 '포춘'호를 타고 미리 장비까지 갖추고 오면, 시간도 얼마 안 걸릴 거야! 그리고 스페인 놈들이 네 목을 은쟁반에 올려놓고 싶어 하지 않게 조심해라. 자세한 건 나중에 다 말해주지.";
			link.l1 = "좋아, 그럼 네가 다시 항해하게 되면 그때 우리 얘기를 계속하지.";
			link.l1.go = "check_out_my_frigate_14";
		break;
		
		case "check_out_my_frigate_14":
			dialog.text = "좋아, 됐어. 이제 나는 관저로 갈 거야, 괜찮다면 말이지. 일이라는 게, 말하자면 기다려주지 않으니까.";
			link.l1 = "곧 보자, 상어! 작별 인사는 안 할 거다.";
			link.l1.go = "check_out_my_frigate_15";
		break;
		
		case "check_out_my_frigate_15":
			DialogExit();
			sld = characterFromId("Dodson");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "reload", "reload3_back","SharkFrigateEnd", -1);
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		// belamour legendary edition на пару с Акулой
		case "SharkGoldFleet":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "내 건 준비됐어, 너는 어때? 내가 '포춘'호로 오라고 했잖아. 어디다 두고 왔는지는 모르겠지만, 다른 배로 이런 도박을 하는 건 너무 위험해. 그러니까 우리가 약속한 그 배에서 널 기다리고 있지. 그리고 너무 조급해하지 마라.";
				link.l1 = "젠장, 완전히 까먹었네, 이 쓰레기야! 기다려라: 내가 제대로 된 배로 다시 올 테니까.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "찰스, 내가 분명히 함대 없이 오라고 했지. 너랑 하려는 일에는 추가 배가 전혀 필요 없어. 네 소함대를 어디 딴 데로 옮기고 다시 와.";
				link.l1 = "그래, 완전히 잊고 있었군. 잠깐만 기다려. 함대 없이 곧 돌아올게.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "아, 거기 있었구나, 친구! 드디어 찾았네! 너 때문에 걱정하기 시작했잖아. 내 배는 거의 준비됐어. 지금은 티락스한테 보냈지. 지난달에 노획한 중형 갈레온에서 가져온 32파운드포로 무장시키라고 했거든. 이미 그 배로 터키까지 갔다가 돌아왔는데, 알렉서스가 정말 잘 해줬다고 말할 수 있겠어. 그런데 아직 그 배에 어울리는 이름을 못 정했어. 후보는 몇 개 있는데, 네가 골라줄 수 있겠어?";
			link.l1 = "당연히 도와주지! 배 이름을 뭐라고 붙이든, 그 이름대로 항해하는 거 아니겠어? 어떤 이름 후보가 있는데?";
			link.l1.go = "SharkGoldFleet_01";
		break;
		
		case "SharkGoldFleet_01":
			dialog.text = "지금까지 세 가지 선택지로 정했어.";
			link.l1 = "...";
			link.l1.go = "SharkGoldFleet_02";
		break;
		
		case "SharkGoldFleet_02":
			dialog.text = "첫 번째 선택지는 '팬텀'이야. 이 프리깃은 빠르고 강력하지. 그런 이름을 달면 아바나에서 쿠마나까지 구두쇠 놈들이 그 이름만 들어도 벌벌 떨 거다!";
			link.l1 = "그래, 그리고 안개 속에서 나타났다 사라졌다 해야 선원들이 진짜 세례라도 받으려 들겠지, 하하! 좋은 이름이야, 마음에 든다.";
			link.l1.go = "SharkGoldFleet_03";
		break;
		
		case "SharkGoldFleet_03":
			dialog.text = "나도 마음에 들어. 두 번째 선택지는 '상어'야. 그래서 뭐? 내 배에도 별명을 붙여주면 어때? 걔랑 이름을 같이 쓰는 거지, 하!";
			link.l1 = "'상어'에 상어가 있다니... 아이러니하군. 하지만 이제 모두가 이 배의 주인이 누군지 확실히 알겠지.";
			link.l1.go = "SharkGoldFleet_04";
		break;
		
		case "SharkGoldFleet_04":
			dialog.text = "여기서도 나 별반 다르지 않아. 그리고 세 번째 선택지는 '플러리'지. 내 배 근처엔 얼씬도 못 하게 모두 겁먹게 하려고, 하하하!";
			link.l1 = "옆에서 날아오는 포탄 세례를 맞을 수도 있으니까? 그래서 뭐, 나쁘지 않지.";
			link.l1.go = "SharkGoldFleet_05";
		break;
		
		case "SharkGoldFleet_05":
			dialog.text = "정확하지! 하지만 지금은 이 세 가지 이름 중에서 결정을 못 하겠어. 자, 도와줘라. 네가 원하는 대로 해.";
			link.l1 = "'팬텀'이라고 이름 짓자고 하지. 그러면 상인 놈들이 네가 수평선에만 보여도 바로 백기를 들 테니까!";
			link.l1.go = "SharkGoldFleet_05f";
			link.l2 = "'상어'라는 이름 마음에 드는군. 모두들 이 배가 풋내기 것이 아니라 해적 연맹의 우두머리 본인 거라는 걸 알아야지!";
			link.l2.go = "SharkGoldFleet_05a";
			link.l3 = "'플러리'라는 이름, 괜찮다고 본다. 어떤 전사든, 사략선장이든, 상인이든 이 배와 싸우기로 마음먹으면 무슨 일이 벌어질지 똑똑히 알게 될 거다.";
			link.l3.go = "SharkGoldFleet_05s";
		break;
		
		case "SharkGoldFleet_05f":
			pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
			dialog.text = "너 꼴 좀 봐라 - 군인 놈들도 곧 따라 하겠네, 하! 자, 결정됐지. 잔 들어, 친구야. 내 새 배를 위해 마시자고. '팬텀'을 위하여!";
			link.l1 = " 팬텀을 위하여!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05a":
			pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
			dialog.text = "그리고 내 길을 가로지르기 전에 세 번은 생각하게 해! 자, 결정됐군. 잔 들어, 친구. 내 새 배를 위해 한잔하자. '샤크'를 위하여!\n";
			link.l1 = ""상어"를 위하여!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_05s":
			pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
			dialog.text = "그리고 그놈이 아직도 결심한다면, 몰아치는 폭풍이 덮쳐서 열대 폭풍도 산들바람처럼 느껴질 거다! 자, 결정됐군. 잔 들어, 친구. 내 새 배를 위해 한잔하자. '플러리'를 위하여!";
			link.l1 = "플러리 만세!";
			link.l1.go = "SharkGoldFleet_06";
		break;
		
		case "SharkGoldFleet_06":
			dialog.text = "이 배가 충실히 봉사하고 패배의 쓰라림을 모르게 되길 바란다!\n자, 이제 본론으로 들어가자.";
			link.l1 = "난 네 말 잘 듣고 있어.";
			link.l1.go = "SharkGoldFleet_07";
		break;
		
		case "SharkGoldFleet_07":
			dialog.text = "말해 봐, Charles, '황금 함대'가 뭔지 아나?";
			link.l1 = "카-카! .. 럼주에 이미 목이 막혔군. 스티븐, 설마 카리브에서 가장 무장 센 호송대를 털려고 프리깃 두 척만 끌고 왔다는 건 아니겠지.";
			link.l1.go = "SharkGoldFleet_08";
		break;
		
		case "SharkGoldFleet_08":
			dialog.text = "글쎄, 아니지, 당연히 나도 죽으려고 덤비는 건 아니야. 호위대 전체를 털 생각은 절대 없어. 하지만 여기서 뭔가 하나쯤은 슬쩍할 수 있겠지.";
			link.l1 = "스티븐, 미안하지만 나 아직 준비 안 됐어. 그래, 우리가 스페인 함대에 끼어들면 저놈들이 우리를 산 채로 태워버릴 거야! 나 빼고 가.";
			link.l1.go = "SharkGoldFleet_09";
			link.l2 = "좋아, 우리가 사라지지 않은 곳에서... 나도 참여할 준비 됐어!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_09":
			pchar.questTemp.SharkGoldFleet = "RUinDeal";
			dialog.text = "아악! 아쉽군. 너 없이는 내가 너무 위험해. 좋아, 이제 더는 설득하지 않겠다만, 한번 생각은 해 봐라, 알겠지? 혹시라도 마음이 바뀌면 꼭 알려줘.";
			link.l1 = "내가 그렇게 한다면, 물론이지. 미안해, 스티븐.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_10":
			dialog.text = "이런 모험은 쉽게 포기하지 않아! 그런데 너는 어때? 혹시 마음이 바뀌었냐?";
			link.l1 = "아니, 친구야, 미안하지만 난 아직도 사양할게.";
			link.l1.go = "exit";
			link.l2 = "좋아, 우리가 사라지지 않은 곳에서... 나도 참여할 준비 됐어!";
			link.l2.go = "SharkGoldFleet_11";
		break;
		
		case "SharkGoldFleet_11":
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = "너는 준비됐을지 몰라도, 네 배는 아니야. 내가 '포춘'호로 오라고 했지. 어디에 두고 왔는지 모르겠지만, 다른 배로 이런 도박을 하는 건 너무 위험해. 그러니 우리가 약속한 그 배에서 널 기다리고 있겠다. 그리고 너무 조급해하지 마라.";
				link.l1 = "젠장, 완전히 까먹었네, 이 얼간이! 잠깐만 기다려. 내가 제대로 된 배로 다시 올게.";
				link.l1.go = "exit";
				break;
			}
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "하지만 아니야. 넌 아직 준비가 안 됐어, Charles. 내가 분명히 함대 없이 오라고 했지. 너랑 하려는 일에는 추가 배가 전혀 필요 없어. 함대를 어디든 옮겨놓고 다시 와.";
				link.l1 = "그래, 완전히 잊고 있었군. 잠깐만 기다려. 함대 없이 곧 돌아올게.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "천 개의 악마가, 바로 그 말을 듣고 싶었지! 그러니, 너랑 나랑 호위대에서 한 몫 챙기자고. 전리품도 잔뜩 있을 거야...";
			link.l1 = "훔치자는 거냐? 경비선들한테 안 들키고?";
			link.l1.go = "SharkGoldFleet_12";
		break;
		
		case "SharkGoldFleet_12":
			dialog.text = "맞아. 봐라, 아마 알겠지만 '황금 함대'는 포르토 벨로에 모였다가 거기서 아바나로 간다. 아바나를 지나면 그놈을 가로채는 건 이미 소용없어. 대서양을 건너 스페인으로 가는데, 그때는 경호가 너무 빡세서 완전 미친놈 아니면 덤비지도 못하지. 포르토 벨로에서 아바나로 이동할 때도 상황이 크게 다르진 않아. 물론 시도해볼 순 있겠지만, 그러려면 요새도 깨부술 수 있는 전대부터 모아야 해. 하지만 포르토 벨로에는 메인 전역에서 배들이 모여드니, 그때는 더 이상 특별히 보호받지도 않지.";
			link.l1 = "지금은 이동 시기와 그런 배들의 이름이 엄격히 비밀로 분류되어 있지. 우리가 포르토 벨로 근처에서 반 년씩이나 머물면서 항구로 들어오는 모든 스페인 배를 잡아챌 순 없잖아.";
			link.l1.go = "SharkGoldFleet_13";
		break;
		
		case "SharkGoldFleet_13":
			dialog.text = "당연히 안 그러지. 예를 들어 카르타헤나에서는 배들이 저절로 다니고, 네가 제대로 지적했듯이 그게 어떤 배들이고 언제 출항하는지는 오직 신만이 알지. 하지만 포르토 벨로에서 꽤 떨어진 곳에 위치하고 스페인 광산이 바로 옆에 있는 카라카스에서는 배들이 완전히 혼자 다니는 건 아니야.";
			link.l1 = "어떻게 완전히 혼자가 아닌 거지?";
			link.l1.go = "SharkGoldFleet_14";
		break;
		
		case "SharkGoldFleet_14":
			dialog.text = "카라카스에서 화물을 가득 실은 배가 혼자 또는 소수의 호위와 함께 출항한다는 걸 알아냈지. 그런데 마라카이보 만의 경도 어딘가에서 스페인 군함들이 그 배를 만나서 이후 안전을 보장해 준다더군. 어떻게 그놈들이 언제, 누구를 거기서 만나야 하는지 알 것 같나?";
			link.l1 = "뭔가 들었겠지...";
			link.l1.go = "SharkGoldFleet_15";
		break;
		
		case "SharkGoldFleet_15":
			dialog.text = "그래. 본선이 출항하기 전에, 카라카스에서 포르토 벨로로 연락선이 가서 만남의 장소와 날짜, 그리고 스페인 배의 이름을 보고하지. 그 다음 다시 돌아와서, 그 배를 정해진 시간과 장소에서 만날 거라는 확인을 전해. 그 모든 절차가 끝난 뒤에야, 우리 목표가 너와 함께 카라카스에서 출발하는 거지.";
			link.l1 = "하지만 우리가 급사를 가로채면 카라카스에 있는 배는 확인을 받지 못해서 항구를 떠나지 못할 거야. 이 일에 대해 무슨 생각이라도 있나? 그리고 급사 놈을 어떻게 잡을 건데? 언제 출발하는지도 모르잖아.";
			link.l1.go = "SharkGoldFleet_16";
		break;
		
		case "SharkGoldFleet_16":
			dialog.text = "여기서 약간의 문제가 있지. 스페인 놈들은 이런 일에 보통 특급 루거선을 쓰지만, 이건 위험해. 첫 번째 해적한테 바로 잡힐 확률이 너무 크거든. 그래서 배를 보내기 전에 오래 기다려야 할 수도 있어. 그러니까 기회만 있으면, 좋은 힘센데 빠른 배들―예를 들면 상선이나, 제대로 된 항로를 가는 사략선 같은 놈들―을 통해서 지시를 같이 보내지. \n마치 봉인된 우편처럼 말이야. 게다가, 따로 특급 배, 심지어 루거선 하나 보내는 것보다 훨씬 싸게 먹혀. 그리고 욕심 많은 스페인 관리 놈들은 돈 아끼면서 자기 주머니에 챙기는 걸 좋아하지, 크크.";
			link.l1 = "이해한 것 같아! 나도 그런 상인이 되어야 하나?";
			link.l1.go = "SharkGoldFleet_17";
		break;
		
		case "SharkGoldFleet_17":
			dialog.text = "그래, 맞아! 그리고 우리는 운이 좋았지. 내가 믿을 만한 소식통에게서 알아냈는데, 지금 카라카스에서 이런 심부름꾼을 찾아서 앞으로 3주 안에 편지를 보내려고 한대. 그런데 네겐 강력하고 빠른 배가 있잖아, 그것도 스페인 놈들이 만든 배란 말이지! 더 그럴듯하게 하려면 GVIK 면허를 한 번에 6개월짜리로 받아두고, 카라카스에서 포르토 벨로에 되팔아서 이익 볼 만한 물건도 충분히 사둬. 그다음엔 현지 항만청장한테 가서, 가는 길에 뭐라도 실어가야 하는지 물어봐. \n항만청에서 물어보면, 넌 스페인 놈이라고 해. 그리고, 절대 함대를 끌고 가지 마라. 괜히 눈에 띄면 우리 계획이 통째로 들통날 수도 있으니까.";
			link.l1 = "그리고 그놈들이 내게 줄 서류에서, 나는 그 배와 호송선이 만나는 날짜와 장소를 알아낼 수 있겠지?";
			link.l1.go = "SharkGoldFleet_18";
		break;
		
		case "SharkGoldFleet_18":
			dialog.text = "그렇게 간단하지 않아. 내가 말했잖아: 문서는 봉인되어 있어. 그리고 네가 직접 열 수도 없어. 포르토 벨로 항구청에서 그걸 열 거고, 거기서 답장을 써줄 거야. 그리고 네가 카라카스로 돌아간다고 친절하게 말해주면, 그 답장을 거기로 가져가 달라고 부탁할 거야. 물론, 답장도 봉인될 거고.";
			link.l1 = "그럼 내가 어떻게 만남의 장소와 날짜를 알 수 있지?";
			link.l1.go = "SharkGoldFleet_19";
		break;
		
		case "SharkGoldFleet_19":
			dialog.text = "머리를 잘 써서 어떻게든 엿봐야 할 거야... 예를 들어, 포르토 벨로에서 서류를 열어보고 답변을 작성할 때 말이지. 아니면 그냥 확인서를 줄 때 훔쳐서 그걸 카라카스로 가져가도 돼. 하지만 이건 좋은 방법이 아니야. 그렇게 하면 모든 게 꼬일 수 있거든.";
			link.l1 = "어렵지, 물론이지... 하지만 내가 해낼 수 있을 것 같아.";
			link.l1.go = "SharkGoldFleet_20";
		break;
		
		case "SharkGoldFleet_20":
			dialog.text = "나는 그럼 마커스에게서 내 배를 받아서 쿠라사오의 산타 마리아 곶 앞바다에 닻을 내리고 기다리겠다.\n네가 일을 끝내면 그냥 나한테 오면 돼.\n우리는 지정된 좌표에서 그 배를 가로채고, 곧장 여기서 빠져나갈 거다.\n이제 왜 배가 강력하면서도 빨라야 하는지 알겠지?\n난 스페인 군함대랑 싸우고 싶지 않거든.\n네가 놈들한테서 도망쳐야 할 거다.";
			link.l1 = "알겠어. 그럼 난 출발한다. 산타 마리아 곶에서 보자!";
			link.l1.go = "SharkGoldFleet_21";
		break;
		
		case "SharkGoldFleet_21":
			dialog.text = "그래, 거기서 만나자. 자, 행운을 빌지 친구! 우리 거래가 잘 풀리길 바란다.";
			link.l1 = "나도 그러길 바란다. 아무튼, 난 간다.";
			link.l1.go = "SharkGoldFleet_22";
		break;
		
		case "SharkGoldFleet_22":
			DialogExit();
			AddQuestRecord("SharkGoldFleet", "1");
			pchar.questTemp.SharkGoldFleet = "start";
			SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
			if(!bImCasual) SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
			else NewGameTip("Exploration mode: timer is disabled.");
		break;
		// провал
		case "SharkGoldFleet_23":
			dialog.text = "젠장, Charles! 다시는 널 못 볼 줄 알았잖아! 어디 갔었어? 약속한 곳에서 기다렸는데, 넌 끝내 안 왔지. 소식도 전혀 없고.";
			link.l1 = "미안하다, 스티븐. 내 임무를 완수하지 못했어.";
			link.l1.go = "SharkGoldFleet_24";
		break;
		
		case "SharkGoldFleet_24":
			NextDiag.CurrentNode = "First time";
			dialog.text = "에이, 저런 큰 놈을 놓쳤군 ... 뭐, 너무 속상해하지 마라. 다음엔 더 잘될 거다.";
			link.l1 = "그러길 바란다.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_25":
			if(GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = pchar.name+", 뭐야 이게? 내가 분명히 함대 없이 오라고 했잖아! 잘 들어, 우리한텐 쓸데없는 짐이 필요 없어. 그렇지 않으면 작전 전체가 망가질 수도 있다고! 네가 왜 그랬는지 모르겠지만, 이렇게는 안 돼. 당장 네 선단을 아무 데나 보내고 한 척만 타고 돌아와. 여기서 기다릴 테니까.";
				link.l1 = "그래, 그냥 이게 더 가능성 있어 보인다고 생각했을 뿐이야... 좋아, 알겠어. 여기서 기다려. 금방 돌아올게!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			}
			if(sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
			{
				dialog.text = pchar.name+", 뭐야 이게? 내가 '포춘'에 있으라고 했잖아! 잘 들어, 우리에겐 빠르고 강력한 배 두 척이 꼭 필요해. 아니면 작전 전체가 망할 수도 있다고! 대체 무슨 생각이었는지 모르겠지만, 이따위로는 안 돼. 당장 네 고물선을 '포춘'으로 바꾸고 돌아와. 여기서 기다릴 테니까.";
				link.l1 = "그래, 그냥 이 배가 더 좋아 보여서 그랬다... 좋아, 알겠다. 여기서 기다려라. 금방 돌아올 테니!";
				link.l1.go = "exit";
				NextDiag.TempNode = "SharkGoldFleet_25";
				break;
			} 
			dialog.text = "그리고 여기 있군, 내 친구! 자, 내 멋진 녀석이 마음에 드나?";
			link.l1 = "멋진 프리깃이군, 스티븐! 이런 건 나도 마다하지 않겠어...";
			link.l1.go = "SharkGoldFleet_26";
		break;
		
		case "SharkGoldFleet_26":
			dialog.text = "아니, 이제 '포춘'이 있잖아, 하하! 자, 어떻게 됐는지 말해 봐.";
			if(pchar.questTemp.SharkGoldFleet == "LightVarToShark")
			{
				link.l1 = "모든 게 완벽하게 진행됐지: 나는 정직하고 믿음직한 상인인 척하는 데 성공했어. 서류를 포르토 벨로로 가져가서, 항만청 책임자를 5분 동안 따돌리고, 화물선과 군함이 만나는 날짜와 좌표를 내 입맛대로 다시 써넣었지.";
				link.l1.go = "SharkGoldFleet_27";
			}
			else
			{
				link.l1 = "약간의 문제가 있었지. 편지는 사환을 통해 포르토 벨로로 보내졌어. 내가 그걸 가로채서 수신인에게 전달했고, 심지어 답장도 받았지. 하지만 항만 책임자가 내가 원래 문서를 가져올 사람이 아니라는 걸 눈치챘어. 그래서 싸우면서 빠져나와야 했지. 하지만 화물과 군함이 만나는 날짜와 좌표를 알아냈고, 답장도 카라카스로 전달했으니, 이제 생산품이 우리를 기다리고 있어!";
				link.l1.go = "SharkGoldFleet_30";
			}
		break;
		
		case "SharkGoldFleet_27":
			dialog.text = "잠깐만. 방금 '배들'이라고 했어?";
			link.l1 = "그래, 상어! 두 놈이 올 거야!";
			link.l1.go = "SharkGoldFleet_28";
		break;
		
		case "SharkGoldFleet_28":
			dialog.text = "하하하, 그래, 대박 터뜨릴 거다! 내 짐승도 이제 불시험을 치를 준비가 됐지. 하지만 아직 전투에 참여한 적은 없으니, 네가 전투를 이끌어라. 그리고 당분간은 네 함대에 합류하겠다.";
			link.l1 = "내가 직접 해안의 형제단 우두머리 스티븐 도드슨을 지휘하게 된 거냐? 이거 제대로 된 일거리군!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_29":
			NextDiag.TempNode = "SharkGoldFleet_33";
			pchar.questTemp.SharkGoldFleet.talk = true;
			AddQuestRecord("SharkGoldFleet", "22");
			AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
			SGF_SharkCompanion();
			pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
			pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
			if(bImCasual)
			{
				pchar.GenQuest.SeaHunter2Pause = true;
				SeaHunter_Delete();
			}
			dialog.text = "음, 너무 거만하게 굴지 마라. 내가 내 배에서 처음으로 싸우게 될 뿐이니까. 그리고 전리품 선박을 위해 쓸만한 장교들이 남아 있는지도 신경 써라. 그 배들의 창고는 꽉 차 있을 테고, 내 부하들 중 누구도 혼자서 그 배를 조종할 수 없을 거다... 됐다, 쓸데없는 말은 그만하자. 전리품이 우리를 기다리고 있으니까!\n";
			link.l1 = "맞아! 난 내 배로 갈 거야.";
			link.l1.go = "exit";
		break;
		
		case "SharkGoldFleet_30":
			dialog.text = "그래, 네가 물려받았지 ... 그럼 우리가 미리 대비해야겠군. 함대가 약속한 날짜보다 먼저 도착할 테니, 모두와 한꺼번에 싸워야 할 거야.";
			link.l1 = "왜 그렇게 말하는 거야?";
			link.l1.go = "SharkGoldFleet_31";
		break;
		
		case "SharkGoldFleet_31":
			dialog.text = "그리고 너도 머리 좀 굴려 봐라. 포르토 벨로 놈들은 화물 싣고 떠날 배가 카라카스를 반드시 출항할 거란 걸 알고 있지, 네가 회신서를 거기로 가져갔으니까. 근데 네가 정체를 드러냈으니, 이제 저놈들은 우리가 그 배를 가로채지 못하게 온 힘을 다 쏟을 거다. 내 생각엔, 저놈들 함대가 우리보다 먼저 도착할 거야. 내가 그 입장이라도 그렇게 하겠지. 그러니, 빡센 싸움 준비나 하자고. 늦게 물러서면 끝장이다.";
			link.l1 = "걱정하지 마라. 너랑 나는 바다의 늑대잖아, 이런 일쯤은 아무것도 아니지!";
			link.l1.go = "SharkGoldFleet_32";
		break;
		
		case "SharkGoldFleet_32":
			dialog.text = "네 진실이군. 좋아, 내 놈도 불시험을 치를 준비가 됐지. 하지만 아직 전투에 참가한 적은 없으니, 이번엔 네가 전투를 이끌어라. 그동안 나는 네 편대로 합류하지.";
			link.l1 = "내가 직접 해안의 형제단 두목 스티븐 도드슨을 지휘하게 된 거야? 이거 제대로 된 일이군!";
			link.l1.go = "SharkGoldFleet_29";
		break;
		
		case "SharkGoldFleet_33":
			NextDiag.TempNode = "SharkGoldFleet_33";
			dialog.text = "수다 떨 시간 없어, "+pchar.name+"! 약탈하러 가자!";
			link.l1 = "우리에게 행운이 따르길!";
			link.l1.go = "exit";
		break;
		// делим добычу на берегу
		case "SharkGoldFleet_34":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				dialog.text = "천 개의 악마가 날뛰겠군! 잘했어, Charles! 전리품이 내가 처음에 생각했던 것보다 훨씬 많았어! 이 항해, 확실히 해볼 만한 가치가 있었지.";
				link.l1 = "나도 완전히 동의해, 스티븐! 오늘은 분명히 우리 날이야!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					dialog.text = "잘했어, 친구야. 하지만 솔직히 말해서, 우리가 먹잇감을 꽤 많이 놓쳤지.";
					link.l1 = "나도 동의해, Steven. 우리 더 잘할 수도 있지. 그래도 지금 있는 것도 괜찮아!";
					link.l1.go = "SharkGoldFleet_35";
				}
				else
				{
					dialog.text = "젠장! 정말 좋은 생각이었는데... 그런데 결국 이번 항해에서 쓴 돈이 번 돈보다 더 많아졌잖아. Charles, 내가 너한테 지휘를 맡겼더니, 결국 다 말아먹었구나!";
					link.l1 = "아무 말도 하지 마... 나도 존나 열받았으니까. 얼마나 많은 먹잇감이 손아귀에서 빠져나갔는지 알아!..";
					link.l1.go = "SharkGoldFleet_37";
				}
			}
		break;
		
		case "SharkGoldFleet_35":
			dialog.text = "음, 우리 둘 다 잘했지. 나는 계획을 세우고 사환에 대한 정보를 알아냈고, 너는 그 계획을 멋지게 실행했어. 그리고 우리는 둘 다 먹잇감을 두고 동등하게 싸웠지. 그러니, 해적 동맹의 법에 따라 나누자고 제안한다: 똑같이!";
			link.l1 = "우리가 해내겠다!";
			link.l1.go = "SharkGoldFleet_36";
		break;
		
		case "SharkGoldFleet_36":
			dialog.text = "자, 이제 나는 이슬라 테소로로 간다. 배를 수리해야 하고, 내 새 배로 첫 성공적인 항해를 제대로 축하해야지. 행운을 빌어, 친구! 내 집에 언제든 찾아오면 반갑게 맞아주지!";
			link.l1 = "우리 거래가 이렇게 이익이 많이 나서 기쁘군. 언젠가 꼭 찾아가겠어. 행운을 빌지!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_37":
			dialog.text = "그래, 다 네가 챙겨라. 남은 게 있으면 말이지. 난 이런 꼬맹이들엔 관심 없어. 어차피 이 일에 널 끌어들인 건 나니까.";
			link.l1 = "그래, 내 잘못도 있어... 미안해, 스티븐.";
			link.l1.go = "SharkGoldFleet_38";
		break;
		
		case "SharkGoldFleet_38":
			dialog.text = "사과하지 마라, 난 아직도 네 덕분에 목숨을 건졌으니 그 은혜는 절대 잊지 않는다. 이제 난 정의의 섬으로 간다. 배를 수리하고 좀 씻겨야겠지... 뭐, 씻을 게 있긴 한지 모르겠지만... 행운을 빈다, 친구! 내 거처에 언제든 찾아오면 반갑게 맞아주지!";
			link.l1 = "좋아, 뭐든 일어날 수 있지, 패배도 있는 법이야. 중요한 건 우리가 살아 있다는 거다. 언젠가 꼭 찾아갈게, 친구! 행운을 빌어!";
			link.l1.go = "SharkGoldFleet_39";
		break;
		
		case "SharkGoldFleet_39":
			if(makeint(pchar.questTemp.SharkGoldFleet) > 74)
			{
				AddQuestRecord("SharkGoldFleet", "34");	
				ChangeCharacterComplexReputation(pchar, "fame", 10);
				ChangeCharacterComplexReputation(pchar, "authority", 5);
				ChangeOfficersLoyality("good_all", 2);
				AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 300);
				AddCharacterExpToSkill(PChar, "Fortune", 300);
				AddCharacterExpToSkill(PChar, "Sneak", 300);
			}
			else
			{
				if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
				{
					AddQuestRecord("SharkGoldFleet", "35");
					ChangeCharacterComplexReputation(pchar, "fame", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
					AddCharacterExpToSkill(pchar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 200);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
				}
				else
				{
					AddQuestRecord("SharkGoldFleet", "36");
					AddCharacterExpToSkill(pchar, "Leadership", 100);
					AddCharacterExpToSkill(PChar, "Fortune", 100);
					AddCharacterExpToSkill(PChar, "Sneak", 100);
				}
			}
			if(makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				if(GetSquadronGoods(pchar, GOOD_GOLD)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SILVER)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SANDAL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_SHIPSILK)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_ROPES)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes)/2));
				}
				if(GetSquadronGoods(pchar, GOOD_OIL)>0)
				{
					RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold)/2));
				}
			}
			SGF_GoodSwimReturn();
			SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
			CloseQuestHeader("SharkGoldFleet");
			DialogExit();
		break;
	}
}
