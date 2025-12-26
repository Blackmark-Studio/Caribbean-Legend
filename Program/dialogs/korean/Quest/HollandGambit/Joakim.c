// Жоаким Мерриман - португальский сумрачный гений
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbySeekIsland" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "안녕하십니까, 나리! 저는 요아킴 메리먼 박사입니다. 혹시 선장님을 뵙는 영광을 누리는 것입니까 "+GetFullName(pchar)+"?";
					link.l1 = "그래, 그게 나다. 그런데 도대체 어떻게 내 이름을 아는 거지? 전에 만난 기억이 없는데.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					dialog.text = "만나서 반갑소, 선장. 걸음걸이만 봐도 내 기분을 아주 좋게 해줄 소식이 있겠구려. 윰 시밀의 해골을 가져왔소?";
					link.l1 = "네가 말한 해골을 가지고 있다. 마치 불타는 용광로처럼 에너지가 번쩍거린다네.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "선장, 더 할 말 있소?";
				link.l1 = "아니오, 메리먼 나리. 나는 떠나겠소..";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "JoakimMeeting" && !CheckAttribute(npchar, "quest.HWICHoll.Task"))
				{
					dialog.text = "안녕하십니까, 나리! 저는 요아킴 메리먼 박사입니다. 혹시 선장님을 뵙는 영광을 누리는 것입니까 "+GetFullName(pchar)+"?";
					link.l1 = "그래, 그게 나다. 그런데 대체 어떻게 내 이름을 아는 거지? 전에 만난 기억이 없는데.";
					link.l1.go = "JoakimSeekSkull";
					break;
				}
				if (CheckCharacterItem(pchar, "SkullAztec"))
				{
					DelLandQuestMark(npchar);
					DelMapQuestMarkCity("Villemstad");
					dialog.text = "만나서 반갑습니다, 선장님. 걸음걸이만 봐도 저를 아주 기쁘게 해줄 소식이 있겠군요. 윰 시밀의 해골을 가지고 오셨습니까?";
					link.l1 = "네가 말한 해골을 내가 가지고 있다네. 그것은 마치 불타는 화덕처럼 에너지가 번쩍거리고 있지.";
					link.l1.go = "JoakimFindSkull";
					break;
				}
				dialog.text = "선장, 더 하실 말씀이 있소?";
				link.l1 = "아니오, Merriman 박사. 나는 떠나겠소.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "좋은 하루요. 내게 바라는 게 있소?";
			link.l1 = "아니오, 미안합니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Landlady"://хозяйка дома
			dialog.text = "닥터 메리먼을 만나러 오셨다면, 그는 여기 없습니다. 이제 더 이상 여기서 살지 않아요.";
			link.l1 = "알겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady";
		break;
		
		case "Landlady_1"://хозяйка дома
			dialog.text = "닥터 메리먼을 만나러 오셨다면, 지금 집에 없다는 말씀을 드려야겠군요.\n현재 여행 중이시라 언제 돌아오실지 저도 모릅니다.";
			link.l1 = "알겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_1";
		break;
		
		case "Landlady_2"://хозяйка дома
			dialog.text = "닥터 메리먼을 만나러 왔다면, 그는 여기 없어. 이제 이곳에 살지 않아.";
			link.l1 = "알겠소.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Landlady_2";
		break;
		
		case "JoakimSeekSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "선장, 당신의 일이 생각만큼 비밀스럽지는 않소! 하지만 놀라지 마시오, 제안이 있소! 나는 과학자요, 일종의 자연 철학자로서 스페인령 본토와 서인도 제도의 인디언 이교도들의 매혹적인 문화를 연구하고 있소. 내 집까지 함께 걸으며, 응접실에서 아주 수익성 있는 세부 사항에 대해 이야기해 주겠소?";
			link.l1 = "내 호기심과 관심을 끌었군. 앞장서게.";
			link.l1.go = "JoakimSeekSkull_1";
		break;
		
		case "JoakimSeekSkull_1":
			dialog.text = "이걸 거절하지는 못할 거요, 나리! 내 집은 여기서 멀지 않소. 따라오시오!";
			link.l1 = "...";
			link.l1.go = "JoakimSeekSkull_2";
		break;
		
		case "JoakimSeekSkull_2":
			DialogExit();
			AddLandQuestMark(npchar, "questmarkmain");
			LAi_ActorGoToLocation(npchar, "reload", "houseSp1", "Villemstad_houseSp1_room", "goto", "goto1", "JoakimInRoom", -1);
		break;
		
		case "JoakimSeekSkull_3":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			dialog.text = "여기서는 남의 귀를 걱정하지 않고 이야기할 수 있소. 최근에 내 이웃 솔로몬 슈네우르를 방문했더군. 나는 그냥 지나가던 참이었는데, 용서하게나, 선장, 솔로몬과 나눈 대화의 일부를 우연히 엿듣고 말았소. 그 이야기가 너무 흥미로워서 끝까지 듣지 않을 수 없었지!";
			link.l1 = "남의 말을 엿듣는 주제에 다른 엿듣는 놈들을 무서워하나 보군?";
			link.l1.go = "JoakimSeekSkull_4";
		break;
		
		case "JoakimSeekSkull_4":
			dialog.text = "자, 자, 선장님! 전혀 그런 게 아닙니다! 솔로몬은 제 이웃이고 자주 저를 찾아옵니다. 우리 둘은 종교가 달라도 좋은 친구지요! 그의 불운에 대해서는 저도 압니다... 빌렘스타드에 있는 모두가 다 알지요! 솔로몬은 아침, 점심, 저녁 할 것 없이 누구든 들어줄 사람만 있으면 자기 고생담을 떠벌리니까요. 하지만 그 이야기는 이쯤 하죠. 그 늙은 유태인은 이미 당신에게 자기 금과 함께 어떤 이름 모를 섬에 숨겨둔 오래된 비취 해골 이야기를 했겠지요. 그 얘기도 들으셨습니까?";
			link.l1 = "그가 해골에 대해 말하긴 했지만, 옥으로 만들어졌다는 얘기는 안 했어. 그리고 그 해골이 자기 할아버지의 것이라고도 했지. 사실을 말하자면, 나는 그게 카발라의 무슨 끔찍한 물건이거나, 아니면 그 영감이 좀 미쳤다고 생각했어.";
			link.l1.go = "JoakimSeekSkull_5";
		break;
		
		case "JoakimSeekSkull_5":
			dialog.text = "아니요, 선장님, 솔로몬은 제정신입니다. 다만 괴짜일 뿐이죠. 해골은 실제로 존재합니다. 고대 인디언의 보물, 윰 시밀의 비취 해골이에요! 그 늙은 유대인이 어떻게 그걸 손에 넣었는지는 저도 전혀 모릅니다. 저는 평생의 절반을 그 해골을 찾아 헤맸습니다\n솔로몬이 집안 재산을 숨겨둔 그 섬을 찾아내십시오. 해골은 분명 그의 상자 안에 있을 겁니다. 그 비취 해골을 저에게 가져오면 오십만 페소를 드리겠습니다.";
			link.l1 = "오백? 그 정도 돈으론 시간 낭비지... 잠깐만... 방금 오십만 피스 오브 에잇이라고 했어?! 농담하는 거지? 내 평생 그만한 돈이 한데 모인 걸 본 적도 없어!";
			link.l1.go = "JoakimSeekSkull_6";
		break;
		
		case "JoakimSeekSkull_6":
			dialog.text = "아직 젊은 사람이군, 선장... 자, 할 텐가? 자네가 옥 해골을 내게 주면 나는 오십만 피스의 에잇을 주지. 거래하겠나?";
			link.l1 = "하, 낡은 해골에 한몫 잡을 수 있다면야? 당연히 나도 끼지.";
			link.l1.go = "JoakimSeekSkull_7";
		break;
		
		case "JoakimSeekSkull_7":
			dialog.text = "훌륭하군. 이익을 이해하는 사람과 일하는 건 언제나 즐거운 일이오. 더 필요하면 내 집에서 나를 찾으시오. 행운을 빌겠소!";
			link.l1 = "감사합니다, Merriman 박사. 너무 오래 기다리게 하진 않겠습니다.";
			link.l1.go = "exit";
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			AddDialogExitQuestFunction("CheckIslandCoordinates");//вот тут-то мы и проверим, есть ли у нас координаты острова, и далее будем исходить из результата.
		break;
		
		case "JoakimFindSkull":
			PlaySound("Voice\English\hambit\Joakim Merriman-02.wav");
			dialog.text = "오, 맞아요! 그 힘에 대해선 정말 옳은 말씀입니다... 하지만 이제 말은 그만하고, 보여 주시오. 나는 기대에 떨고 있소.";
			link.l1 = "여기, 자, 받아요. 내가 실수한 건 아니겠지?";
			link.l1.go = "JoakimFindSkull_1";
			DelLandQuestMark(npchar);
		break;
		
		case "JoakimFindSkull_1":
			RemoveItems(PChar, "SkullAztec", 1);
			dialog.text = "아, 믿을 수가 없군! 그래, 바로 이거야. 훌륭하오, 선장, 정말 훌륭하오! 드디어! 마침내 내 손에 들어왔어! 이 순간을 수년 동안 기다려 왔소!";
			link.l1 = "당신이 약속한 돈은 어떻게 된 거요, 메리먼 박사?";
			link.l1.go = "JoakimFindSkull_2";
		break;
		
		case "JoakimFindSkull_2":
			AddMoneyToCharacter(pchar, 500000);
			dialog.text = "아, 네, 물론이죠! 오십만 피스의 에잇입니다. 가져가세요, 받을 자격이 있으니.";
			link.l1 = "거래하게 되어 기쁘군. 이렇게 작은 것이 이렇게 큰 값어치를 지닌다니, 믿기 어렵군...";
			link.l1.go = "JoakimFindSkull_3";
		break;
		
		case "JoakimFindSkull_3":
			dialog.text = "작은 거라고? 네가 뭘 아는지나 있나. 이건... 에이, 네 무식한 머리로는 이 소중한 해골에 깃든 엄청난 힘의 규모를 도저히 이해 못 하겠지. 사실 말이지, 나도 더 이상 시간 낼 여유가 없어\n그동안 해주신 일들, 고맙소, 선장. 이제 작별을 고할 때요. 나는 가야겠소.";
			link.l1 = "안녕히 계십시오, 메리먼 박사. 언젠가 다시 만날 수도 있겠군요.";
			link.l1.go = "JoakimFindSkull_4";
		break;
		
		case "JoakimFindSkull_4":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			sld = characterFromId("Landlady");
			sld.Dialog.Filename = "Quest\HollandGambit\Joakim.c";
			sld.dialog.currentnode = "Landlady_2";
			SetFunctionTimerCondition("Caleuche_StartTotal", 0, 0, 180, false); // таймер на Калеуче
		break;
		
		case "JoakimSeekSkull_8":
			PlaySound("Voice\English\hambit\Joakim Merriman-01.wav");
			DelLandQuestMark(npchar);
			dialog.text = "여기서 이야기할 수 있소, 선장. 나는 그대가 내 이웃 솔로몬의 딸, 아비가일 슈네우어와 가까운 사이임을 알고 있소. 그녀가 그대의 배를 타고 연인에게 떠났지... 하지만 그건 별로 중요하지 않소.";
			link.l1 = "무슨 말씀을 하시려는 겁니까, 의사 선생?";
			link.l1.go = "JoakimSeekSkull_9";
		break;
		
		case "JoakimSeekSkull_9":
			dialog.text = "솔로몬을 안다면, 그가 난파와 어딘가 이름 모를 섬에 숨겨둔 잃어버린 보물 이야기도 알겠군. 그 이야기는 이미 윌렘스타트에 있는 모두에게 다 했지.";
			link.l1 = "내가 그 일에 대해 들었을 뿐만 아니라 그 늙은 유대인의 불행에 신경까지 쓴다고 생각하는 이유가 무엇이오?";
			link.l1.go = "JoakimSeekSkull_10";
		break;
		
		case "JoakimSeekSkull_10":
			dialog.text = "솔로몬이 마음에 안 드나? 장담하는데, 그는 그냥 해 없는 괴짜 노인일 뿐이야. 신경 쓰지 말게. 이제 사업 이야기를 하지\n나는 솔로몬과 여러 번 긴 대화를 나눴지. 내가 수년간 찾아 헤맨 고대의 귀중한 유물이 이 늙은 유대인 소유라는 걸 알았을 때 내 기분이 어땠는지 상상도 못 할 거야! 미친 노인은 그 보잘것없는 돈과 함께 그 유물을 어느 섬에 숨겨두고는 위치조차 기억 못 하더군\n난 그 유물이 꼭 필요하다. 가져오면 오십만 피스의 에잇을 주지.";
			link.l1 = "팔십만 레알이라고? 농담하는 거지, 의사 양반. 내 평생 그렇게 많은 돈을 한 번에 본 적이 없어!";
			link.l1.go = "JoakimSeekSkull_11";
		break;
		
		case "JoakimSeekSkull_11":
			dialog.text = "아직 젊은 사람이군. 자, 할 텐가? 자네가 해골을 넘기면 나는 오십만 피스의 에잇을 주겠네. 거기에 솔로몬의 돈도 자네가 가져가도 돼. 노인의 말로는 이십만 페소쯤 있을 거라더군... 그러니 자네 몫은 모두 칠십만 피스의 에잇이 되는 셈이지. 어때, 선장?";
			link.l1 = "이런, 벼락 맞을 소리군! 당연히 거래하지! 그런데 이 섬을 어떻게 찾으라는 거지?";
			link.l1.go = "JoakimSeekSkull_12";
		break;
		
		case "JoakimSeekSkull_12":
			dialog.text = "애비게일에게 가서 이야기해 봐. 혹시 기억나는 게 있을지도 몰라. 솔로몬에게도 물어봐. 내가 그 섬이 어디 있는지 알았다면 애초에 네 도움을 청하지도 않았겠지.";
			link.l1 = "알겠소. 어리석은 질문을 해서 미안하오. 이제 이 섬을 찾아야겠군. 내 보수는 꼭 준비해 두시오.";
			link.l1.go = "JoakimSeekSkull_13";
		break;
		
		case "JoakimSeekSkull_13":
			dialog.text = "정확합니다. 우리가 서로 이해하게 되어 기쁩니다, 선장님. 수색에 행운을 빕니다. 언제든 여기 제 집에서 저를 찾으실 수 있습니다.";
			link.l1 = "너무 오래 기다리게 하진 않겠소, Merriman 박사. 안녕히 계시오!";
			link.l1.go = "JoakimSeekSkull_14";
		break;
		
		case "JoakimSeekSkull_14":
			DialogExit();
			pchar.questTemp.HWIC.Self = "SeekAbiIsland";
			AddQuestRecord("Holl_Gambit", "3-55");
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload3", true);//закроем комнату Аби
			npchar.quest.HWICHoll.Task = "true";
			LAi_SetOwnerType(npchar);
			NextDiag.CurrentNode = "First time";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
			AddMapQuestMarkCity("SentJons", false);
		break;
		
		// калеуче
		case "caleuche":
			PlaySound("Voice\English\LSC\Chymiset-03.wav");
			dialog.text = "그래, 그래! 제물의 돌이 내 적들의 피로 붉게 물들었도다! 움 키밀께서 내게 죽은 자를 지배하는 힘을 내리셨다! 이 힘으로 곧 산 자들까지 내 발아래 둘 것이다!";
			link.l1 = "참 극적이군, 메리맨. 네 저 걷는 시체 군대를 가지고 뭘 할 셈이지? 혹시 시저 흉내라도 내서 세상을 정복하려는 거냐?";
			link.l1.go = "caleuche_1";
			CreateLocationParticles("large_smoke", "goto", "goto37", 0.5, 0, 0, "");
		break;
		
		case "caleuche_1":
			dialog.text = "조용히 해라, 이 멍청이! 내가 내 비밀 계획을 독백으로 다 털어놓을 거라 생각했느냐?! 뭐, 어차피 네놈이 이 자리에서 살아남지 못할 테니 굳이 숨길 이유도 없지! 내 언데드 군단이 먼저 카리브 해의 모든 어두운 동굴과 던전을 점령할 것이다. 내 전초기지들은 모든 마을에 배치되어 내 신호만을 기다리고 있다. 그리고 때가 오면, 내 걷는 시체들이 진군하여 산 자들의 땅을 휩쓸 것이다!\n안타깝게도 네놈은 그 광경을 보지 못하겠구나, 이 한심한 착한 척쟁이, 주인공 흉내나 내는 꼬마야! 네놈은 내 성역에 들어왔고, 살아서 나가지 못할 것이다! 내가 암흑의 군대를 이끌 것이다!";
			link.l1 = "이봐, 친구, 너 따위가 이끌 수 있는 건 잭이랑 똥밖에 없어. 그런데 잭은 방금 이 마을을 떠났거든.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			PlaySound("Types\warrior04.wav");
			dialog.text = "오호호! 나와 내 해골 하인들에게 감히 도전하겠다는 건가?! 그럼 내 진짜 모습을 똑똑히 보고, 두려움에 떨도록 해라!";
			link.l1 = "덤벼 봐라.";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			npchar.model = "Meriman_2";
			Characters_RefreshModel(npchar);
			PlaySound("Ambient\Teno_inside\teleporter.wav");
			dialog.text = "";
			link.l1 = "아아악! 달콤하신 예수님!";
			link.l1.go = "caleuche_4";
		break;
		
		case "caleuche_4":
			PlaySound("Voice\English\hambit\Joakim Merriman-04.wav");
			dialog.text = "이제 누가 네 앞에 서 있는지 알겠냐, 이 징징대는 구더기야?! 너랑 반드시 결판을 내야겠다! 유믹 시밀께서 직접 나를 돌보신다! 네 영혼을 삼켜주마!";
			link.l1 = "좋아, 멍청아. 한판 붙자.";
			link.l1.go = "caleuche_5";
		break;
		
		case "caleuche_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "goto", "goto37", "none", "", "", "Caleuche_MerrimanTeleport", -1);
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "goto", "goto37");
			pchar.questTemp.Caleuche.Merriman_hide = "true";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이오, 나리! 경비병들아, 저 자를 잡아라\n","도둑이다, 저 아가씨야! 경비병들, 저녀석을 잡아라\n")+"!!!","저것 좀 봐! 내가 잠깐 등 돌린 사이에 내 상자를 뒤졌군! 도둑이다! 도둑 잡아라!!!","경비병들! 도둑이다! 저 도둑 잡아라!!!");
			link.l1 = "젠장!";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
