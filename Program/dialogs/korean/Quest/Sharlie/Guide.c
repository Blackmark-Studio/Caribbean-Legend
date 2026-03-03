// гид
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
			dialog.text = "뭐 원하는 거라도 있어?";
			link.l1 = "아니, 아무것도 없어.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		case "guide_0":
			PlaySound("Voice\English\LE\Greguar\Greguar_01.wav");
			dialog.text = "식민지에 오신 것을 환영합니다, 나리! 제 소개를 드리겠습니다:\n "+GetFullName(npchar)+". 좋은 옛 고향에서 온 건가?";
			link.l1 = "안녕하십니까, 나리. 제 이름은 "+GetFullName(pchar)+"그래, 방금 배에서 내렸소.";
			link.l1.go = "guide_1";
		break;
		
		case "guide_1":
			DelLandQuestMark(npchar);
			dialog.text = "신사분을 보고 도와드려야겠다고 생각했소. 신세계에는 이곳만의 규칙이 있지, 그걸 모르면 큰 대가를 치르게 되오. 지위 있는 사람들끼리는 뭉쳐야 하오. 여기엔 동전 몇 닢에 당신을 팔아넘길 잡놈들이 널렸으니\n"+"제가 안내해 드리고 기본적인 것들을 알려드려도 되겠습니까?";
			link.l1 = "정말 친절하시군요, 나리! 기꺼이 하겠습니다.";
			link.l1.go = "guide_2";
			link.l2 = "감사합니다, 나리, 하지만 제 길은 제가 찾겠습니다.";
			link.l2.go = "guide_exit";
		break;
		
		case "guide_exit":
			dialog.text = "원하시는 대로 하겠습니다, 나리. 아무튼, 만나서 반가웠습니다. 이런 고귀한 신사는 이곳에 드문 손님이지요. 행운을 빕니다!";
			link.l1 = "당신에게도 마찬가지요, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_exit_1";			
		break;
		
		case "guide_exit_1":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_2":
			dialog.text = "훌륭해! 카리브 해의 도시들은 모두 같은 구조를 따르지. 생피에르만 익혀 두면 다른 항구들도 모두 이해가 될 거야.";
			link.l1 = "";
			link.l1.go = "guide_tavern";		
		break;
		
		case "guide_tavern":
			dialog.text = "선술집—항구의 중심지다. 침대, 럼주, 소문을 얻고 선원이나 장교를 고용할 수 있다. \n카드놀이를 하거나 일거리를 찾고, 밀수업자나 보물지도 장수와 거래할 수도 있다.";
			link.l1 = "";
			link.l1.go = "guide_market";
			locCameraFromToPos(-2.08, 5.32, 68.88, true, -15.00, 0.90, 55.00);
		break;
		
		case "guide_market":
			dialog.text = "시장. 보급품이 필요해? 대장장이가 칼, 갑옷, 탄환을 팔고, 약초 여인은 강장제를 팔지. 집시와 수도사는 부적을 거래하고, 고물상은 손재주 있는 자들을 위해 잡동사니를 내놓아.";
			link.l1 = "";
			link.l1.go = "guide_brothel";
			locCameraFromToPos(-13.58, 4.11, 69.06, true, -45.00, -6.00, 52.00);
		break;
		
		case "guide_brothel":
			dialog.text = "매음굴. 숙련된 여인과 함께하는 시간만큼 기분을 북돋우는 것도 없지. 기력이 떨어졌다면 들러서 새사람이 되어 나가게.";
			link.l1 = "";
			link.l1.go = "guide_bank";
			locCameraFromToPos(-2.75, 7.07, 61.10, true, 60.00, -6.60, 42.65);
		break;
		
		case "guide_bank":
			dialog.text = "은행. 돈을 빌리거나 투자하고, 페소를 두블룬으로 환전할 수 있으며, 보석을 팔기에 가장 좋은 곳이다.";
			link.l1 = "";
			link.l1.go = "guide_prison";
			locCameraFromToPos(3.07, 7.64, 51.99, true, 45.00, -8.30, 4.50);
		break;
		
		case "guide_prison":
			dialog.text = "감옥. 진짜 악당은 별로 없고, 대부분은 떠돌이들이지. 그놈들에게서 일거리를 얻고 싶으면 사령관에게 말해. 약간의 뇌물만 있으면 감방 문이 열릴 거야.";
			link.l1 = "";
			link.l1.go = "guide_townhall";
			locCameraFromToPos(-50.52, 5.79, 38.60, true, -47.65, 3.95, 33.52);
		break;
		
		case "guide_townhall":
			dialog.text = "총독 관저. 상인들과 선장들이 중요한 일로 이곳을 찾는다. 총독과 친하게 지내라—그의 말 한마디가 그 나라가 너를 대하는 방식을 좌우한다.";
			link.l1 = "";
			link.l1.go = "guide_12";
			locCameraFromToPos(3.14, 7.39, 37.55, true, 1.06, 8.45, 14.14);
		break;
		
		case "guide_12":
			dialog.text = "내가 너를 붙잡아 두고 있는 건가, 친구?";
			link.l1 = "나리, 저는 제 형을 찾으러 왔습니다. 그가 생피에르에 있다고들 하더군요. 꽤 중요한 인물이라던데… 총독께서 분명히 알고 계시겠지요…";
			link.l1.go = "guide_13";
			SetCameraDialogMode(npchar);
		break;
		
		case "guide_13":
			dialog.text = "아, 알겠소. 우리 총독은 자크 디엘 뒤 파르케 나리요. 분명 곧 당신을 만나 줄 것이오.";
			link.l1 = "또 누구에게 물어볼 수 있을까? 각하를 바로 귀찮게 하고 싶진 않은데.";
			link.l1.go = "guide_14";
		break;
		
		case "guide_14":
			dialog.text = "네 형이 마르티니크에서 유명하다면, 마을 사람들에게 물어보게—누군가는 알 테니. 그리고 이름이 뭐지?";
			link.l1 = "미셸 드 몽페르.";
			link.l1.go = "guide_15";
		break;
		
		case "guide_15":
			dialog.text = "이름은 들어봤지만, 만난 적은 없소. 주변에 물어보거나, 아니면 곧장 총독에게 가보시오. 행운을 빌겠소, 나리. 또 이야기합시다!";
			link.l1 = "감사합니다, "+GetFullName(npchar)+"!";
			link.l1.go = "guide_16";
		break;
		
		case "guide_16":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			LAi_group_MoveCharacter(npchar, "FRANCE_CITIZENS"); // пока идем заниматься Мишелем
			chrDisableReloadToLocation = false;//открыть локацию
			DoQuestCheckDelay("NgtF3", 1.0);
			QuestPointerToLoc("FortFrance_town", "reload", "reload3_back");
		break;
		
		case "guide_21":
			dialog.text = "아, 또 만났군! 기사단 요새에 들어갔다고 들었어. 확실히 높은 사람들과 어울리는구먼. 형을 찾았나?";
			link.l1 = "찾았어... 어떤 의미로는.";
			link.l1.go = "guide_22";
		break;
		
		case "guide_22":
			dialog.text = "용서하십시오만, 그 대답에서 기쁨이 별로 느껴지지 않는군요...";
			link.l1 = "맞아요. 다음 배를 타고 집으로 돌아가길 바랐는데, 운명이 비웃는군요. 여기서 꼼짝없이 갇혀버렸어요—얼마나 오래 있을지 누가 알겠어요—게다가 이제는 뱃사람이 되는 법까지 배워야 한다니.";
			link.l1.go = "guide_23";
		break;
		
		case "guide_23":
			dialog.text = "놀랍지 않소. 자네가 율리시스호로 항해했다는 소문이 퍼졌네. 낙담하지 말게—배를 소유하고 선장이라는 칭호를 가진 건 결코 작은 일이 아니니. 자네, 배를 살 계획이지?";
			link.l1 = "그래, 젠장, 해야지. 하지만 조선소가 어디 있는지도 모르고, 항해법도 모르고, 돈을 마련하는 방법도 몰라. 아무것도 몰라!";
			link.l1.go = "guide_24";
		break;
		
		case "guide_24":
			dialog.text = "돈은 없지만, 그 외에는 뭐든 도와드릴 수 있습니다. 계속 구경하시겠습니까?";
			link.l1 = "맞아—지식이 곧 힘이지.";
			link.l1.go = "guide_25";
			link.l2 = "감사합니다, 나리, 하지만 여기서부턴 제가 알아서 하겠습니다.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_exit_11":
			dialog.text = "기쁘군. 자금이 필요하면 마을의 실세들과 이야기해 보게—상점 상인에게 가보는 것도 좋겠지\n"+"행운을 빌어요, "+pchar.name+"—대담하게 나서면 해낼 수 있을 거야.";
			link.l1 = "";
			link.l1.go = "guide_exit_12";			
		break;
		
		case "guide_exit_12":
			DialogExit();
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
		break;
		
		case "guide_25":
			dialog.text = "그럼 따라오시오! 우선 중요한 건—배들이오.";
			link.l1 = "";
			link.l1.go = "guide_shipyard";
		break;
		
		case "guide_shipyard":
			dialog.text = "조선소. 여기서 배를 사거나 수리할 수 있다.\n대부분 작은 선체지만, 가끔 괜찮은 배도 나온다.\n대포와 멋진 돛도 있다.";
			link.l1 = "";
			link.l1.go = "guide_port";
			locCameraFromToPos(-23.25, 7.74, 77.79, true, -27.85, 5.36, 73.65);
		break;
		
		case "guide_port":
			dialog.text = "부두—바다로 나아가는 관문이오. 배를 소유하게 되면, 당신의 선박이 여기에서 기다릴 것이오. 지금은 항해사, 경리, 포수를 고용하시오—이들이 바다에서의 삶을 한결 편하게 만들어 줄 것이오.";
			link.l1 = "";
			link.l1.go = "guide_portoffice";
			locCameraFromToPos(-8.55, 4.06, 91.31, true, 40.00, -8.00, 0.00);
		break;
		
		case "guide_portoffice":
			dialog.text = "항만 사무소. 여기서 배를 정박시키거나 정직한 일거리를 구하시오—화물 운송, 호위, 우편 배달 등. 일을 많이 완수할수록 보수가 더 좋아지오.";
			link.l1 = "";
			link.l1.go = "guide_store";
			locCameraFromToPos(48.38, 9.48, 43.95, true, 43.69, 5.47, 48.13);
		break;
		
		case "guide_store":
			dialog.text = "상점. 선장들은 여기서 식량, 럼주, 약, 화약, 탄환을 구하지. 뭐 하나라도 빠지면 선술집에 있는 밀수꾼을 찾아가. 유능한 급사 없이는 무역이 시간과 돈 낭비일 뿐이야.";
			link.l1 = "";
			link.l1.go = "guide_gate";
			locCameraFromToPos(-21.10, 6.60, 45.21, true, -30.00, 3.70, 45.00);
		break;
		
		case "guide_gate":
			dialog.text = "야생으로 가는 문. 위험하지만 요새에 가거나, 보물을 사냥하거나, 다른 정착지로 건너갈 때 유용하다.";
			link.l1 = "";
			link.l1.go = "guide_45";
			locCameraFromToPos(50.58, 5.74, 23.21, true, 100.00, 0.00, 20.00);
			//AddQuestRecordInfo("Guide_OnLand", "1");
		break;
		
		case "guide_45":
			dialog.text = "모든 식민지가 낯선 이를 반기는 건 아니오. 밤까지 기다리기 싫다면, 바다에서 다른 깃발을 올리고 은밀하게 움직이거나, 무역 허가증을 사는 것도 방법이오.";
			link.l1 = "";
			link.l1.go = "guide_46";
		break;
		
		case "guide_46":
			dialog.text = "잘 듣는구나, 친구야. 재미 좀 볼래? 성문 밖에서 연습 결투 한 판 하자.";
			link.l1 = "물론이지! 완벽하게 들리는군.";
			link.l1.go = "guide_47";
			link.l2 = "감사합니다, 나리, 하지만 이제부터는 제가 하겠습니다.";
			link.l2.go = "guide_exit_11";
		break;
		
		case "guide_47": // телепортируем за городские ворота
			DialogExit();
			LAi_SetActorType(npchar);
			DoQuestReloadToLocation("FortFrance_ExitTown", "goto", "goto19", "Guide_ExitTown");
		break;
		
		case "guide_49":
			dialog.text = "친구여, 검술에는 익숙한가 보군?";
			link.l1 = "하! 난 이미 한 번의 백병전을 겪었고, 심지어—\n";
			link.l1.go = "guide_50";
			if (GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "unarmed")
			{
				GiveItem2Character(pchar, "blade_05");
				EquipCharacterByItem(Pchar, "blade_05");
			}
		break;
		
		case "guide_50":
			dialog.text = "훌륭하군. 갈까?";
			link.l1 = "춤추자!";
			link.l1.go = "guide_56";
			npchar.quest.guide_win = 0;
		break;
		
		case "guide_56": // махач
			LAi_SetPlayerType(pchar);
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			LAi_SetCurHPMax(npchar); 
			LAi_GetCharacterMaxEnergy(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_group_Delete("EnemyFight");
			if (MOD_SKILL_ENEMY_RATE <= 6)	// На первых трёх сложностях Валинье будет ослаблен
			{
				LAi_SetHP(npchar, LAi_GetCharacterMaxHP(npchar) * 0.7, LAi_GetCharacterMaxHP(npchar) * 0.7);
				npchar.rank = 1;
				SetSelfSkill(npchar, 1, 1, 1, 1, 1);
			}
			DialogExit();
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			// ставим проверяльщики
			LAi_SetCheckMinHP(pchar, 1, true, "Guide_HeroFail");
			LAi_SetCheckMinHP(npchar, 1, true, "Guide_HeroWin");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			AddDialogExitQuest("MainHeroFightModeOn");
			//DoQuestCheckDelay("GuideFight_tutorial", 1.0);
		break;
		
		case "guide_57": // побил гида с первого раза
			dialog.text = "너... 너는 검을 다룰 줄 아는 사람이구나. 잘했네, 나리. 아직 더 연습이 필요하지만, 진정한 검술의 달인이 될 잠재력이 있소.";
			link.l1 = "정말 감사합니다. 이제 어쩌지?";
			link.l1.go = "guide_62"; // нода на выход
			if (MOD_SKILL_ENEMY_RATE >= 6)
			{
				link.l2 = "연습을 더 하라고? 진심이야? 이 비참한 곳에 발을 들인 순간부터 그 거만한 태도에 진절머리가 난다고!";				//Пасхалка Корсары 2 для сложности СФ и выше
				link.l2.go = "guide_64";
			}
			AddComplexSelfExpToScill(50, 50, 50, 50);
			AddCharacterExpToSkill(pchar, "Leadership", 80);
		break;
		
		case "guide_58": // побил гида со второго или третьего раза
			dialog.text = "훨씬 낫군! 봐라, 집중만 하면 돼. 연습이 더 필요하니, 언젠가는 괜찮은 검객이 될 거야.";
			link.l1 = "정말 감사합니다. 이제 어떻게 하지?";
			link.l1.go = "guide_62"; // нода на выход
			AddComplexSelfExpToScill(20, 20, 20, 20);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
		break;
		
		case "guide_59": // побили первый раз
			dialog.text = "내가 이겼소, 나리. 더 빨리 움직이시오, 내 찌르기를 받아내고, 뒤로 물러서시오. 재경기 하겠소?";
			link.l1 = "위! 자비는 없다, 나리!";
			link.l1.go = "guide_56";
			link.l2 = "아니, 이제 충분하다. 수업을 끝내자. 이제 뭐하지?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_60": // побили второй раз
			dialog.text = "또 이겼군, "+pchar.name+"! 주도권을 잃지 마라. 내 공격을 받아내고, 속임수에도 속지 마라. 내가 강하게 칠 것 같으면, 그냥 막지 말고 피하거나 받아쳐라. 다시 한 번!\n";
			link.l1 = "오라, 나리, 이번엔 내가 당신을 혼쭐내주겠소!";
			link.l1.go = "guide_56";
			link.l2 = "아니, 이제 충분하다. 수업은 여기서 끝내자. 이제 뭐하지?";
			link.l2.go = "guide_62"; // нода на выход
		break;
		
		case "guide_61": // побили третий раз
			dialog.text = "배워야 할 게 많구나, "+pchar.name+". 걱정 마라, 아직 검술을 익힐 시간은 충분히 있으니. 하지만 조심해라, 무기를 제대로 다루기 전까지는 절대 무리하지 마라.";
			link.l1 = "고려해 보겠소, 나리. 하지만 솔직히 말해, 자네는 정말 운이 좋았던 거요! 이 지독한 더위... 이것만 아니었으면 자네를 혼쭐내줬을 텐데. 젠장, 검술 수업은 여기까지 하세. 이제 어쩔 셈인가?";
			link.l1.go = "guide_62"; // нода на выход
		break;
		
		case "guide_62":
			dialog.text = "이제 작별을 고할 시간이군요, 나리. 즐거운 시간이었습니다. 제 설명과 훈련이 도움이 되었기를 바라며, 앞으로도 유용하게 쓰이길 바랍니다. 언젠가 다시 만날 수 있기를 기대하겠습니다.\n그리고 필요한 돈에 대해서는 우리 도시의 중요한 인물들과 이야기해 보십시오. 오늘 제가 안내한 모든 장소를 방문해서 그 주인들과 대화해 보세요. 여기저기 물어보고, 정글이나 요새까지도 걸어가 보십시오. 일거리를 찾거나... 뭐, 저는 신부도 아니고 판사도 아니니, 사람들 집을 살펴보고 잠긴 적 없는 상자에서 쓸만한 물건이 있나 확인해 보세요. 다만, 주인이 등을 돌렸을 때 하시고, 아니면 경비병에게 잡힐 테니 조심하십시오.\n행운을 빕니다, "+pchar.name+", 나는 그대 안에 진정한 위대함의 불씨가 있다고 강하게 느끼오. 최선을 다해 그 불씨를 거대한 불길로 키우시오!";
			link.l1 = "감사합니다, 나리. 저야말로 즐거웠습니다. 행운을 빕니다!";
			link.l1.go = "guide_63";
		break;
		
		case "guide_63":
			LAi_SetCurHPMax(pchar); 
			LAi_GetCharacterMaxEnergy(pchar);
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			DoQuestReloadToLocation("FortFrance_Town", "quest", "quest2", "");
		break;
		
		case "guide_64": // решили убить Валинье
			dialog.text = "입 다물라, 나리! 더 이상 그런 무례는 용납하지 않겠소. 하지만 새로운 환경에 대한 반응임을 이해하니, 이번만은 무례를 용서하겠소. 그러나 앞으로는 말조심하시오. 안녕히 가시오, 드 모르 나리.";
			link.l1 = "기분 상하게 하려는 건 아니오, Valinnie 나리. 지금 우리가 루브르에 있다면, 당신도 말조심했을 테지! 이제 시골뜨기에게 마지막 교훈을 줄 때다. 각오하시오!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Guide_DlgExit_64");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
