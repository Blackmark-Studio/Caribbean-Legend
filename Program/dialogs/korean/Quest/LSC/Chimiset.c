// колдун ривадос - Чимисет
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
			dialog.text = "뭐 필요해?";
			link.l1 = "아니, 됐어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		//-------------------------------------в тюрьме на Тартарусе-----------------------------
		// вариант R
		case "KillChad":
			dialog.text = "잠깐, 멈춰! 제발, 끔찍한 실수를 저지르기 전에 내 말 좀 들어줘.";
			link.l1 = "듣고 있어...";
			link.l1.go = "KillChad_1";
			LAi_RemoveCheckMinHP(npchar); //убираем проверяльщик, если ещё есть
		break;
		
		case "KillChad_1":
			dialog.text = "나를 죽이라고 들었지? 위층에서 채드랑 얘기하는 거 들었어. 너를 탓하진 않아 - 채드가 선택지를 주지 않았으니까 - 하지만 내가 죽으면 채드가 널 그냥 놔줄 거라고 생각하는 건 착각이야.";
			link.l1 = "흠... 그런데 왜 안 하겠어? 내가 아는 건, 너를 죽이지 않으면 내 미래가 암울하다는 것뿐이야.";
			link.l1.go = "KillChad_2";
		break;
		
		case "KillChad_2":
			dialog.text = "날 죽이면 너한텐 미래 따윈 없어. 들어, 나르발 놈들이랑 차드는 내가 사라지길 바라지만, 직접 손대기엔 겁이 많아서 못 해. 날 죽이는 자는 영원히 저주받을 테니까. 그래서 대신 해줄 놈을 찾는 거야.\n차드는 네가 리바도스가 아니라는 걸 알아. 널 속이고 있지. 네가 날 죽이면, 그놈들도 똑같이 널 해치고 네 시체로 샤크를 속일 거다.";
			link.l1 = "상어?! 상어 도드슨? 그가 여기 있다고? 제발, 신이시여, 말해 줘, 이 리바도스라는 놈들은 도대체 누구야?";
			link.l1.go = "KillChad_3";
		break;
		
		case "KillChad_3":
			dialog.text = "거짓말이 아니었군... 정말 처음 왔구나... 흠... 하지만 지금 설명할 때가 아니야! 도망쳐야 해. 내게 계획이 있는데, 들어줄래?";
			link.l1 = "아니. 있잖아, 마법사. 나 방금 신비한 차원의 문을 통과해서 살아남았거든, 그러니 네 저주 따윈 안 무섭다. 미안하지만 - 최대한 고통 없이 끝내주지.";
			link.l1.go = "KillChad_fightfail";
			link.l2 = "좋아, 들어줄게. 네 계획이 뭐지?";
			link.l2.go = "KillChad_4";
		break;
		
		case "KillChad_fightfail":
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "afraid", "", -1);
			LAi_SetImmortal(npchar, false);
			pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
			pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
			pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;
		
		case "KillChad_4":
			dialog.text = "저기 상자가 하나 있어. 그 안에는 쓸 만한 무기랑 물약이 들어 있지. 자물쇠가 잠겨 있지만 오래되고 망가져서 쇠지렛대를 찾아 부숴버려.\n상자 안에 있는 건 전부 챙기고, 무장한 다음 계단으로 가. 거기가 방어하기 좋은 자리야. 놈들은 한 번에 한 명씩밖에 덤빌 수 없을 거야. 다만 머스킷병들만 조심해.\n네가 검을 잘 다루길 바란다. 나는 너무 늙어서 싸움에 도와줄 수가 없어. 만약 저놈들을 전부 죽이고 살아남는다면, 리바도스—내 가족—의 보호를 보장하지.";
			link.l1 = "좋아... 내 대신 신들에게 기도해 줘. 이번 싸움은 쉽지 않을 거야. 위층에 있는 녀석들, 만만해 보이지 않거든.";
			link.l1.go = "KillChad_5";
		break;
		
		case "KillChad_5":
			DialogExit();
			pchar.quest.LSC_fightfail.over = "yes"; //снять прерывание
			LAi_SetImmortal(npchar, true);
			ref location = &Locations[FindLocation(pchar.location)];
			location.private1.key = "crowbar";
			location.private1.key.delItem = true;
			NextDiag.CurrentNode = "KillChad_6";
		break;
		
		case "KillChad_6":
			dialog.text = "시간 낭비하지 마! 자물쇠를 부숴, 빨리!";
			link.l1 = "그래, 그래, 하고 있어!";
			link.l1.go = "exit";
			NextDiag.TempNode = "KillChad_6";
		break;
		
		case "Chad_die":
			dialog.text = "잘했어! 너는 진정한 전사구나. 내 목숨을 네게 빚졌어, 이방인. 이름이 뭐지?";
			link.l1 = ""+pchar.name+". "+GetFullName(pchar)+". 그쪽 이름은?";
			link.l1.go = "Chad_die_1";
		break;
		
		case "Chad_die_1":
			dialog.text = "나는 치미셋, 리바도스의 주술사이자 우리 추장 블랙 에디의 조언자다. 내가 풀려나고 목숨을 구한 걸 블랙 에디가 알면 분명 기뻐할 거다. 너는 나, 블랙 에디, 그리고 모든 리바도스의 친구야. 이제부터 너는 언제나 프로텍터호의 환영받는 손님이 될 거다...";
			link.l1 = "잠깐만... 치미세, 아직도 이해가 안 된다면, 나 여기 온 지 몇 시간밖에 안 됐어! 내가 지금 어디에 있는지, 너희 리바도스가 누구인지, 그리고 샤크 도드슨은 어디서 찾을 수 있는지 설명해 줄 수 있겠어?";
			link.l1.go = "Chad_die_2";
		break;
		
		case "Chad_die_2":
			dialog.text = "여기는 버려진 배들의 도시라고 불리지만, 그 이름은 조롱에 가깝소; 도시라고 부르기엔 너무 초라하오.\n이곳은 수백 척의 난파선이 모여 이루어진 섬이오. 중심부의 난파선들이 우리가 사는 공간을 이루고 있지. 이 섬의 주민들은 섬을 둘러싼 폭풍과 해류로 인한 난파에서 살아남은 사람들이오.\n내가 속한 리바도스는 오랜 세월 함께 살아온 자유 흑인들의 씨족이오. 여기에는 또 다른 세 집단이 있소: 우리 아프리카 조상들을 이곳으로 데려온 자들의 후손인 나르발 씨족, 샤크 도드슨의 해적들, 그리고 따로 지내는 평민들이오.\n샤크는 이 섬의 우두머리로 여겨지며, 스스로를 '제독'이라 부르오. 그는 얼마 전에 도착해 폭력으로 권력을 잡았지. 섬의 식량이 저장된 산 아우구스틴을 점령했소. 이제 우리는 샤크가 정한 값에 우리 식량을 다시 사야 하오. 당신과 채드가 나눈 대화를 엿들은 바로는, 이미 해적 창고에 다녀온 듯하군.\n채드 캐퍼는 샤크의 보선장이자 감옥지기였소. 레이튼 덱스터, 샤크의 일등항해사와 함께, 이 자들과 그 해적들은 내 리바도스와 나르발 씨족과 더불어 이 섬을 지배하는 세 세력 중 하나를 이루고 있소.";
			link.l1 = "왜 챗 캐퍼가 너를 죽이라고 했지?";
			link.l1.go = "Chad_die_3";
		break;
		
		case "Chad_die_3":
			dialog.text = "채드는 리바도스의 숙적인 나르발들과 거래를 맺었어. 그들의 도움을 받아 샤크를 죽이고 그 자리를 차지하려 했지.\n나르발들은 자신들의 우두머리였던 앨런 밀로우가 살해된 일로 제독에게 원한을 품고 있어. 그들은 샤크가 범인이라고 믿지만, 사실이 아니야. 앨런을 죽인 건 채드였고, 그 범죄의 유일한 목격자가 바로 나야.\n그래서 채드는 나를 죽이고 싶어 했지만, 직접 손대는 건 두려워했지. 해적들은 전투에선 두려움이 없지만, 강력한 마법엔 경외심을 가져. 그래서 너를 이용하려 한 거야.\n채드와 나르발들은 샤크를 죽이고, 그 죄를 리바도스에게 뒤집어씌우려 했지.";
			link.l1 = "왜 너를 탓하겠어?";
			link.l1.go = "Chad_die_4";
		break;
		
		case "Chad_die_4":
			dialog.text = ""+pchar.name+", 나중에 이야기하자. 상어 놈들의 해적이 나타나기 전에 서둘러야 해. 채드의 시체를 뒤져서 열쇠를 챙기고, 그의 책상도 확인해 봐. 거기에 중요한 문서가 있을지도 몰라.\n상어 도드슨에게 가. 그는 섬 북쪽 끝에 있는 대형 선박 산 아우구스틴에 있을 거야. 그 배에서 플루토로 이어지는 밧줄다리가 있어. 채드가 그를 배신하려고 했다고, 이 모든 일의 배후에는 나르발들이 있다고, 우리 리바도스는 아무 관련 없다고 전해.\n네가 프로텍터에 있는 나를 찾아오면 뭐든 기꺼이 알려주지. 이제 가자!";
			link.l1 = "좋아, Chimiset. 나중에... 그 보호자에서 널 찾을게. 가자!";
			link.l1.go = "Chad_die_5";
		break;
		
		case "Chad_die_5":
			dialog.text = "마지막으로 한 가지 더 말하자면, 우리 배들, 특히 프로텍터호는 이방인 출입이 금지되어 있어. 리바도스 사람이거나 암호를 알아야 들어갈 수 있지. 나도 알려주고 싶지만, 암호는 매주 바뀌고 나는 여기 너무 오래 있어서 지금 암호를 몰라.\n먼저 산 아우구스틴에 들러. 네가 샤크와 얘기하는 동안 내가 우리 사람들에게 네가 누구인지 알려주마. 우리가 기다리고 있을 테니, 샤크와 얘기하기 전까지는 프로텍터호 근처엔 가지 마!";
			link.l1 = "알겠어. 산 아우구스틴으로 갈게. 곧 보자!";
			link.l1.go = "Chad_die_6";
		break;
		
		case "Chad_die_6":
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Notsearchbody");
			LAi_SetActorType(npchar);
			LAi_ActorFollow(npchar, pchar, "", -1);
			pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
			pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
			pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
			sld = characterFromId("SharkMush_17");
			sld.lifeday = 0;
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("SharkSold_1"+(i+3));
				sld.lifeday = 0;
			}
			AddSimpleRumourCityTip("They say that you are a friend of clan Rivados. Interesting... congratulations.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("They say that you saved the Rivados wizard Chimiset from Tartarus. Now, you are a welcome guest on their ships.", "LostShipsCity", 5, 1, "LSC", "");
			AddSimpleRumourCityTip("So, it was you who set Chimiset free! Interesting. Now you are a friend of Rivados but an enemy of Narwhals. I'm not sure whether to congratulate or pity you...", "LostShipsCity", 5, 1, "LSC", "");
		break;
		
		// вариант N
		case "prisoner":
			dialog.text = "낯선이, 나한테 뭘 원하는 거지?";
			link.l1 = "네 이름이 치미셋 맞지?";
			link.l1.go = "prisoner_1";
		break;
		
		case "prisoner_1":
			dialog.text = "그래, 맞아. 나한테 볼일 있어?";
			link.l1 = "그래. 나는 제독 샤크 도드슨에게서 왔어. 너를 풀어주라는 명령을 받았지. 하지만 조건이 하나 있어. 내 질문에 반드시 답해야 해.";
			link.l1.go = "prisoner_2";
		break;
		
		case "prisoner_2":
			dialog.text = "도드슨이 나를 풀어주기로 했다고? 그 소식은 반갑군 - 물론, 이게 속임수가 아니라면 말이지.";
			link.l1 = "속임수가 아니야, 하지만 네 도움이 필요해. 치미셋, 이 섬에 낮에는 돌이지만 자정이 되면 금으로 변하는 인디언 우상이 있다는 게 사실이냐? 내가 미쳤다고 생각하지는 마...";
			link.l1.go = "Friend_2";
		break;
		
		case "prisoner_3":
			dialog.text = "더 물어볼 거 있나?";
			link.l1 = "그래. '화이트 보이'라는 남자를 아나?";
			link.l1.go = "prisoner_4";
		break;
		
		case "prisoner_4":
			dialog.text = "백인 꼬마? 물론 알지. 그건 올레 크리스티안센이야. 이제 다 컸고, 더 이상 소년처럼 보이지 않지만, 정신은 여전히 어린애 그대로지.";
			link.l1 = "그렇소? 어디서 그를 찾을 수 있는지 말해 주시오?";
			link.l1.go = "prisoner_5";
		break;
		
		case "prisoner_5":
			dialog.text = "그는 종종 악셀 요스트의 상점이나 카펜테로의 선술집, 아니면 그냥 거리에서 산책하는 모습을 볼 수 있어. 피부가 창백하고, 흰 머리에, 소박한 태도를 지녔지. 보면 바로 알아볼 거야.";
			link.l1 = "훌륭해! 한 가지만 더 묻지. 여기서 네이선리얼 호크라는 이름의 남자를 본 적 있나? 얼마 전에 이곳에 나타났을 텐데, 심각하게 아플 수도 있어.";
			link.l1.go = "prisoner_6";
		break;
		
		case "prisoner_6":
			dialog.text = "그런 이름을 가진 사람은 모릅니다. 그가 리바도스 배에 없는 건 확실히 말씀드릴 수 있고, 공용 구역에서도 본 적이 없습니다.\n하지만 나르발 영토에 대해서는 말할 수 없군요. 리바도스는 거기 가지 않으니까요.";
			link.l1 = "알겠어. 도와줘서 고마워, Chimiset!";
			link.l1.go = "prisoner_7";
		break;
		
		case "prisoner_7":
			dialog.text = "이제 상어가 나를 풀어줄까?";
			link.l1 = "그래. 더 물어볼 건 없어. 차드 카퍼가 널 풀어줄 거야. 자, 난 가봐야겠군...";
			link.l1.go = "prisoner_8";
		break;
		
		case "prisoner_8":
			dialog.text = "멈춰! 돌아와.";
			link.l1 = "그래? 또 생각난 거라도 있어?";
			link.l1.go = "prisoner_9";
		break;
		
		case "prisoner_9":
			dialog.text = "정확히는 아니야... (목소리를 낮추며) 너는 카퍼의 부하가 아닌 것 같군. 그놈을 믿지 마. 그는 살인자야.\n얼마 전, 그는 알란 밀로우를 무장도 안 한 채, 냉혈하게 죽였어. 그가 바로 나르발 클랜의 우두머리였지. 나는 내 감방에서 그걸 봤어: 채드가 그냥 들어와서 그를 찔러 죽였지.
제독의 부하들 중 일부가 그를 암살하려 한다는 소문도 들었어. 샤크에게 전해 줘―그리고 그와 내가 직접 마주 앉아 얘기할 때 더 말해주겠다고 전해 줘.";
			link.l1 = "흠. 좋아, 이 일은 도드슨에게 말해주지. 또 보자!";
			link.l1.go = "prisoner_10";
		break;
		
		case "prisoner_10":
			DialogExit();
			sld = characterFromId("Capper");
			sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
			if (!CheckAttribute(npchar, "quest.capper_talk")) chrDisableReloadToLocation = true;//закрыть локацию
			else chrDisableReloadToLocation = false;//открыть локацию
			sld = characterFromId("Dodson");
			sld.dialog.currentnode = "entrance_10"; // ноду Акуле
			LSC_SetWhiteBoy(); // поставим белого мальчика
			NextDiag.CurrentNode = "prisoner_11";
			AddQuestRecord("SharkHunt", "20");
		break;
		
		case "prisoner_11":
			dialog.text = "상어한테 가서 내가 말한 걸 전부 전해 줘. 나도 이 우리에서 곧 나갈 수 있으면 좋겠는데...";
			link.l1 = "가는 중이야.";
			link.l1.go = "exit";
			NextDiag.TempNode = "prisoner_11";
		break;
		
		//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
		case "Friend":
			dialog.text = "여기 있었군, 친구! 다시 한 번 나를 구해주고, 카퍼 대신 나를 믿어줘서 고맙다.\n이 부적들을 네 수고에 대한 보상으로 받아라. 분명 쓸모가 있을 거야.";
			link.l1 = "고마워! 이렇게까지 해줄 줄은 몰랐는데...";
			link.l1.go = "Friend_1";
		break;
		
		case "Friend_1":
			GiveItem2Character(pchar, "indian_1");
			GiveItem2Character(pchar, "indian_11");
			GiveItem2Character(pchar, "amulet_1");
			PlaySound("interface\important_item.wav");
			dialog.text = "이제 이야기할 수 있겠군. 나에게 궁금한 게 있다 했지?";
			link.l1 = "그래. 네 도움이 필요해. 치미세트, 내가 미쳤다고 생각하지 마... 그런데 이 섬에 낮에는 돌이고 자정이 되면 금으로 변하는 인디언 우상이 있나?";
			link.l1.go = "Friend_2";
		break;
		
		// нода пересечения
		case "Friend_2":
			dialog.text = "나는 그대가 미쳤다고 생각하지 않아; 그런 우상이 있었지.\n하지만 아침 햇살을 받으면 금으로 변하고, 나머지 낮과 밤에는 돌로 남아 있네...\n우리는 여러 번 사악한 나르발 녀석들을 그 우상에게 데려갔고, 우상은 하나도 빠짐없이 모두 삼켜버렸지. 하지만 이제는 더 이상 그러지 않아.";
			link.l1 = "더 이상... 우상이 사라졌다는 말이야?";
			link.l1.go = "Friend_3";
		break;
		
		case "Friend_3":
			dialog.text = "우상은 산 헤로니모 호에 있었어. 그 배는 몇 년 전에 침몰하면서 우상도 함께 가라앉았지.";
			link.l1 = "젠장! 나는 그 우상을 써서 이 정의의 섬을 떠나려고 했는데... 그 배가 어디에 있었지?";
			link.l1.go = "Friend_4";
		break;
		
		case "Friend_4":
			dialog.text = "나르발 영토에서 멀지 않은 곳, 피닉스 난파선 근처야. 맑은 날이면 산 헤로니모가 바닷속에 가라앉아 있는 게 보여.";
			link.l1 = "아! 그럼 모래톱에 걸려 있다는 거야? 그럼 내가 헤엄쳐서 갈 수 있겠네--\n";
			link.l1.go = "Friend_5";
		break;
		
		case "Friend_5":
			dialog.text = "안 돼, 친구. 첫째, 너무 깊어. 둘째, 거대한 게들이 많아. 산 헤로니모에 도달하기도 전에 널 갈기갈기 찢어버릴 거야.";
			link.l1 = "아으... 알겠다, 이건 좀 더 생각해 봐야겠군. 적어도 그 조각상이 실제로 있고 어디에 있는지는 알게 됐으니.";
			if (CheckAttribute(npchar, "quest.chimiset_die")) link.l1.go = "prisoner_3";
			else
			{	
				if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_1";
				else link.l1.go = "Friend_6";
			}
			AddQuestRecord("LSC", "4");
		break;
		// нода пересечения
		
		case "Friend_6":
			dialog.text = "질문이 더 있는 것 같군. 물어봐, 친구.";
			link.l1 = "샤크 도드슨이 나더러 채드의 공범들을 찾아보라고 했어. 채드의 상자에서 편지를 발견했지. 어떤 명사수와 소총에 관한 내용이 있어. 샤크를 아주 멀리서 암살하려는 것 같아. 치미셋, 너는 어떻게 생각해?";
			link.l1.go = "Friend_7";
		break;
		
		case "Friend_7":
			dialog.text = "제독을 쏘려고 한다고? 음, 잠깐 생각 좀 해보자... 문제는 제독이 거의 자기 관저를 떠나지 않는다는 거야. 그리고 나올 때면 해적 여섯 명 정도가 호위하지.\n하지만... 제독은 늦은 저녁이면 선미 갤러리를 산책하는 걸 좋아해. 그게 습관이지.\n제독 관저를 조준할 수 있는 곳은 두 군데야: 산타 플로렌티나의 선수와 퓨리의 돛대. 그래도 내가 아는 어떤 명사수도 그런 사격은 못 할 거야.\n정말 독수리 눈을 가진 데다 뛰어난 소총이 있어야 해. 그런 총을 구할 수 있는 사람이 정의의 섬에 있는지 물어보는 게 좋겠어.";
			link.l1 = "편지에... 슈투첸이 언급되어 있었어. 그런 총을 가진 사람 본 적 있어?";
			link.l1.go = "Friend_8";
		break;
		
		case "Friend_8":
			dialog.text = "아니. 그런 무기에 대해서는 들어본 적도 없어. 사람들에게 물어봐. 어쩌면 우리가 모르는 걸 아는 이가 있을지도 몰라.";
			link.l1 = "좋아. 네 정보는 정말 유용했어, 고마워. 아, 마지막으로 한 가지만 더 묻지... '화이트 보이'라는 사람을 알고 있나?";
			link.l1.go = "Friend_9";
		break;
		
		case "Friend_9":
			dialog.text = "화이트 보이? 그래, 그건 올레 크리스티안센의 별명이야. 이제는 어른이 되었고 더 이상 소년처럼 보이지 않지만, 정신은 여전히 어린아이 그대로지.";
			link.l1 = "그래서, 그는 바보란 말이오? 어디서 그를 찾을 수 있는지 말해 보시오?";
			link.l1.go = "Friend_10";
		break;
		
		case "Friend_10":
			dialog.text = "그는 종종 악셀 요스트의 가게나 카펜테로의 선술집, 아니면 거리에서 산책하는 모습을 볼 수 있어. 피부가 창백하고, 머리가 하얗고, 행동이 소박해. 보면 바로 알아볼 거야.";
			link.l1 = "좋아. 고마워, Chimiset, 정말 큰 도움이 되었어!";
			link.l1.go = "Friend_11";
		break;
		
		case "Friend_11":
			dialog.text = "리바도스의 친구라면 언제든 도와주지. 궁금한 게 더 있으면 나를 찾아오게.";
			link.l1 = "지금은 그래야겠어 - 이제 가봐야 해. 안녕!";
			if (CheckAttribute(pchar, "questTemp.LSC.Mary")) link.l1.go = "freedom_2";
			else link.l1.go = "Friend_12";
		break;
		
		case "Friend_12":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
			pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
			AddQuestRecord("SharkHunt", "11");
		break;
		
		case "freedom":
			dialog.text = "그리고 여기 내 자유와 목숨을 구해준 은인이 있군. 내 형제들이 나를 그 살인자 카퍼에게서 구해낼 수 있도록 도와줘서 고맙네.\n이 부적들을 수고에 대한 보상으로 받아주게. 분명 도움이 될 거라 생각하네.";
			link.l1 = "고마워! 이렇게 될 줄은 몰랐는데...";
			link.l1.go = "Friend_1";
		break;
		
		case "freedom_1":
			dialog.text = "오늘은 내가 또 뭘 해줄 수 있지?";
			link.l1 = "말해 봐, 치미셋. '화이트 보이'라는 사람 알아?";
			link.l1.go = "Friend_9";
		break;
		
		case "freedom_2":
			DialogExit();
			NextDiag.CurrentNode = "Chimiset_wait";
			LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;
		
		//--> информационный блок
		case "Chimiset_wait": // стал другом
			if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
			{
				dialog.text = "오! 내 친구야 "+pchar.name+"! 네가 익사했다는 소문을 들었는데! 로아(loa) 신들이 너를 마음에 들어 한 모양이군...";
				link.l1 = "나는 살아 있고 건강해, Chimiset. 걱정해 줘서 고마워. 네가 말한 로아에 대해서라면, 네 말이 맞을지도 몰라. 내가 쿠쿨칸을 지나올 때 분명히 그들이 나를 보살펴 준 것 같아...";
				link.l1.go = "exit";
				npchar.quest.return_isl = "true";
				break;
			}
			dialog.text = "무슨 일로 여기 온 거야, 친구?";
			/*if (!CheckAttribute(npchar, "quest.story"))
			{
				link.l1 = "나에게 나르발족 우두머리가 어떻게 죽었는지 말해 줘. 너만이 그걸 봤잖아.";
				link.l1.go = "story";
			}*/
			if (!CheckAttribute(npchar, "quest.crab"))
			{
				link.l2 = "산 헤로니모 근처 바닥에 게들이 있다고 했지. 그게 뭐야?";
				link.l2.go = "crab";
			}
			link.l9 = "아무것도 아니야, Chimiset. 그냥 네가 보고 싶었어, 친구야.";
			link.l9.go = "exit";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "story":
			dialog.text = "내가 직접 본 대로 모두 기록하겠소.";
			link.l1 = "감사합니다.";
			link.l1.go = "exit";
			npchar.quest.story = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		
		case "crab":
			dialog.text = "그들이 어디서 왔는지, 왜 그렇게 거대한 크기로 자랐는지는 아무도 모릅니다. 사실 우리는 이 괴물들에 대해 아는 것이 거의 없습니다.\n난파선들 사이, 얕은 바닷물에서 무리를 이루어 사는 녀석들도 있지만, 대부분은 바다 밑바닥을 배회하며 물고기와 우리가 버린 쓰레기를 먹고 삽니다.\n이놈들은 위험한 존재입니다; 집게발로 팔다리를 잘라낼 수 있고, 턱에는 바라쿠다의 몸에 가득한 독과 비슷한 위험한 독이 들어 있습니다. 게에게 물리면 치료하지 않을 경우 치명적입니다. 다행히도, 일반적인 해독제나 혼합약으로 이 독을 중화할 수 있습니다.\n예전에는 우리 중에 게 사냥꾼이 한 명 있었습니다 - 용감하게 바닥까지 잠수해 게를 그들의 영역에서 잡던 사내였죠. 그는 우리에게 게 고기를 가져다주곤 했는데, 그 고기는 정말 맛있는 요리가 됩니다. 또 내게는 그들의 독을 가져다주었고, 나는 그 독을 몇몇 비약의 핵심 재료로 썼습니다.\n그가 창조주 곁으로 간 것이 정말 안타깝습니다 - 모두가 그를 사랑했고, 또 부러워했거든요.";
			link.l1 = "그는 어떻게 죽었지?";
			link.l1.go = "crab_1";
		break;
		
		case "crab_1":
			dialog.text = "자기가 사냥하던 게들에게 잡아먹혔지. 내가 경고하는데, 그놈들 근처에서는 조심해.";
			link.l1 = "그러겠다.";
			link.l1.go = "exit";
			npchar.quest.crab = "true";
			NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
	}
}
