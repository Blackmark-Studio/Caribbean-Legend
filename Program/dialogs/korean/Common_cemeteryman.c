// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;	

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
    int iTemp;
	string sTemp;
	bool ok;
    
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = PCharRepPhrase(LinkRandPhrase("마을이 경계 태세야. 나도 이제 무기를 들어야 할 때인 것 같군...","너 지금 온 마을 경비병들에게 쫓기고 있는 거 아니야? 군인들, 이리 와라!","여기서 피신처는 못 찾을 거다. 대신 네 갈비뼈 밑에 차가운 강철 몇 인치는 맛보게 해주지!"),LinkRandPhrase("뭘 원해, 이 악당아?! 도시 경비대가 이미 네 뒤를 쫓고 있어, 멀리 못 갈 거다, "+GetSexPhrase("더러운 해적놈!","악당")+"!","멈춰라! "+GetSexPhrase("더러운 살인자! 경비병!!!","나는 너 따위 안 무서워! 곧 우리 요새에서 교수형당할 거다, 숨을 곳은 없어...")));
				link.l1 = PCharRepPhrase(RandPhraseSimple("살고 싶은 마음이 없는 모양이군...","왜 평화롭게 살고 싶지 않은 거지, 시민들아..."+XI_ConvertString("Colony"+npchar.city+"Gen")+"!"),RandPhraseSimple("지옥에나 떨어져라!","이 세상에서 네게 남은 시간은 이제 몇 초뿐이야..."));
				link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Lantern"))
			{
				dialog.text = "아-아-악! 아, 너였구나... 누구냐? 무슨 일로 묘지에 온 거야?";
				link.l1 = "내 이름은 "+GetFullName(pchar)+". 그런데 너는 누구고, 여기서 뭐 하는 거지? 그리고 왜 그렇게 겁에 질렸어?";
				link.l1.go = "Lantern_01";
				npchar.quest.meeting = "1";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
			{
				dialog.text = "그래서, 어땠어? 확인해 봤지? 이제 내 말 믿겠어?";
				link.l1 = "아니, 아직 지하 묘지에 내려가지 않았어. 조금만 더 기다려, 내가 다 확인해 볼게.";
				link.l1.go = "exit";
				break;
			}
			
			if(CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
			{
				dialog.text = "그래서? 살펴봤어? 봤냐?";
				link.l1 = "그래, 내가 했어! 네 말이 맞았어!";
				link.l1.go = "Lantern_10";
				link.l2 = "네가 생각했던 것과는 좀 달랐지.";
				link.l2.go = "Lantern_14";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = RandPhraseSimple("이봐, 선원! 내 이름은 "+GetFullName(npchar)+", 그리고 여기 살아 있는 영혼은 나 하나뿐이야. 사실 우리 모두 곧 죽게 될 거야, 하하하! 왜 온 거지?","안녕하세요! 살아 있는 사람을 오랜만에 보네요... 제 소개를 하겠습니다 - "+GetFullName(npchar)+", 그리고 이 묘지가 내 마지막 피난처요. 아마도 나는 여기 묻히게 될 거요. 무엇을 도와드릴까요?");
				link.l1 = "안녕하세요, "+npchar.name+"! 내 이름은 "+GetFullName(pchar)+", 그리고 나는 선장이오. 정글을 지나 여기까지 왔지. 이 아늑한 집 안에 누가 이렇게 대담하게 살고 있나 궁금해서 한번 들러봤소...";
				link.l1.go = "meeting";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = "아, 내 오랜 친구여, 선장 "+GetFullName(pchar)+"! 들어오시오, 들어오시오!";
				link.l1 = "환영하네, 친구! 정말 반갑군. 자네는 밤에 춤추는 해골이나 눈 위에 구리 동전을 올린 시체가 꿈에 나타난 적 있나?";
				link.l1.go = "talk";
			}
			NextDiag.TempNode = "First time";
		break;
		
		case "meeting":
			dialog.text = "그리고 내가 왜 두려워해야 하오, 선장? 우리가 두려워해야 할 것은 산 자들이지, 죽은 자들이 아니오 — 죽은 자들은 물지 않으니까. 에이! 한때는 전혀 다른 삶을 살았는데, 지금은 이 묘지의 관리인이 되었소. 무덤을 돌보고 있지. 가끔은 잡동사니를 거래하기도 하고...";
			link.l1 = "무슨 물건을 거래하는지 말씀해 주시겠소?";
			link.l1.go = "trade_info";
		break;
		
		case "talk":
			dialog.text = "이번에는 무슨 일로 나에게 왔나?";
			link.l1 = "오늘은 어떤 물건을 팔고 있나 보여줘.";
			link.l1.go = "trade";
			link.l2 = "당신에게 질문이 있어 묻고 싶소...";
			link.l2.go = "quests";
			link.l3 = "별일 아니야. 그냥 인사하러 왔어.";
			link.l3.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "trade_info":
			dialog.text = "나는 한가한 시간이 많아서 정글을 산책하며 쓸모 있는 식물이나 흥미로운 돌을 모으는 걸 좋아해. 그리고 그걸 마을에서 팔지. 값이 많이 나가진 않지만 없는 것보단 낫거든. 게다가 친구들한테 별별 것도 얻고...";
			link.l1 = "친구들? 다른 사람들이 가져온 걸 다시 파는 거냐?";
			link.l1.go = "trade_info_1";
		break;
		
		case "trade_info_1":
			dialog.text = "오호호... 아니, 나는 모든 걸 공짜로 받지. 묘지지기랑 친구할 자가 죽은 자들 말고 또 누가 있겠어?";
			link.l1 = "뭐... 시체를 털고 다니는 거야?";
			link.l1.go = "trade_info_2";
		break;
		
		case "trade_info_2":
			dialog.text = "나는 도둑질하지 않아; 그냥 더 이상 필요 없는 사람들한테서 물건을 가져갈 뿐이지. 여기에 묻힌 사람들은 정말 다양해—어떤 이들은 이름도 없고 우리 땅 출신도 아니야. 사령관이 마을에서 시체를 가져와서는 이렇게 말하지: '이건 네 거다.'\n "+npchar.name+", 마지막 길을 보내 주게.' 집 없는 자, 교수형당한 해적들, 수호자들에게 죽임당한 도적들—모두 이곳에 묻혔다. 그리고 늙은\n "+npchar.name+" 기독교 관습에 따라 시신을 매장한다.";
			link.l1 = "알겠어. 뭐, 돈은 돈이지. 가진 거 보여줘.";
			link.l1.go = "trade";
			link.l2 = "알겠습니다. 이제 가봐야겠군요. 만나서 즐거웠습니다.";
			link.l2.go = "exit";
		break;
		
		case "trade":
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
			NextDiag.TempNode = "First time";
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "exit_setOwner":
			LAi_SetOwnerTypeNoGroup(npchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Man_FackYou"://реакция на попытку залезть в сундук
			dialog.text = LinkRandPhrase("그리고 너, "+GetFullName(pchar)+", 너 도둑이야! 경비병들아!!!","이런 젠장! 내가 잠깐 한눈판 사이에 벌써 내 물건을 훔치려 하다니! 도둑 잡아라!!!","경비병! 도둑이야!!! 저 도둑 잡아라!!!");
			link.l1 = "이런 젠장!!!";
			link.l1.go = "fight";
		break;
		//belamour квест на получение фонаря -->
		case "Lantern_01":
			dialog.text = "휴, 그냥 여행자였군... 내 이름은 "+GetFullName(npchar)+", 나는 이 버려진 곳의 관리인이오.";
			link.l1 = "왜 묘지에 대해 그렇게 생각하시오? 오히려 이곳이야말로 우리 주님께서 의인들을 장례 후 데려가시는 곳이오.";
			link.l1.go = "Lantern_02";
		break;
		
		case "Lantern_02":
			dialog.text = "하지만 불의한 자들은 묻힌 뒤에도 여기에 남아 있는 모양이오! 지난 몇 밤 동안 지하 납골당에서 이상한 소리가 들려왔소. 신음 소리가 너무 오싹해서 소름이 돋을 지경이오... 길 잃은 영혼이 평안을 찾지 못하는 것 같소! 이제 나는 낮에만 잠을 자오. 밤에는 근무지를 떠날 수도, 눈을 붙일 수도 없으니...\n";
			link.l1 = "소리? 신음소리? 하지만 거기에는 죽은 자들 말고는 아무도 없어.";
			link.l1.go = "Lantern_03";
		break;
		
		case "Lantern_03":
			dialog.text = "내 말이 그 말이야, 알겠어? 유령이 널 눈치채기 전에 어서 나가는 게 좋을 거야... 안 그러면 나처럼 잠도 못 잘 테니까.";
			link.l1 = "음, 그래, 여기서 떠나는 게 좋겠어.";
			link.l1.go = "Lantern_04";
			link.l2 = "제가 도와드릴 수 있을까요? 오늘 밤에 그 이상한 소리들을 조사해 보겠습니다.";
			link.l2.go = "Lantern_05";
		break;
		
		case "Lantern_04":
			pchar.questTemp.Lantern = "NoLantern";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_05":
			dialog.text = "정신 나간 거 아니야?! 무기는 있는 것 같은데, 그걸로 언데드를 어떻게 상대할 생각이야? 거기서 죽기라도 하면 어쩔 건데? 유령이 자유롭게 돌아다닐 거고, 너까지 하인으로 부릴지도 몰라!";
			link.l1 = "글쎄, 그건 그냥 미신일 뿐이야...";
			link.l1.go = "Lantern_06";
		break;
		
		case "Lantern_06":
			dialog.text = "무슨 미신이냐고? 여기는 경건한 유럽 땅이 아니야, 젠장... 원주민들, 그 붉은 피부 녀석들 말이야, 뭐든지 불러낼 수 있지 - 그런데 이제 우리가 여기서 살아야 한다니!";
			link.l1 = "그래도 한번 해보지. 밤이 될 때까지 기다렸다가 지하 묘지로 내려가겠어.";
			link.l1.go = "Lantern_07";
		break;
		
		case "Lantern_07":
			dialog.text = "좋아, 네 마음대로 해. 하지만 해 뜨기 전까지 돌아오지 않으면, 나는 전부 잠그고, 문을 막고, 혼자서라도 여기서 나갈 거야! 갑판을 닦는 선원이든, 짐을 나르는 부두 노동자든 - 어쨌든 여기로 다시는 안 돌아올 거야!";
			link.l1 = "진정해... 다 잘될 거야.";
			link.l1.go = "Lantern_08";
		break;
		
		case "Lantern_08":
			dialog.text = "잠깐만... 이 등불을 가져가. 여분이 하나 있어. 거기선 필요할 거야. 완전히 깜깜하거든!";
			link.l1 = "고맙네, 그런 곳에서는 등불이 정말 유용하겠군.";
			link.l1.go = "Lantern_09";
		break;
		
		case "Lantern_09":
			GiveItem2Character(pchar, "lantern_belt");
			Log_Info("'Lantern' received");
			PlaySound("interface\important_item.wav");
			if(npchar.city == "Charles") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
			if(npchar.city == "Havana") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
			if(npchar.city == "Villemstad" || npchar.city == "PortRoyal") SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
			pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
			pchar.questTemp.Lantern = "ToCrypt";
			pchar.questTemp.Lantern.nation = npchar.nation;
			AddQuestRecord("NoiseCemetery", "1");
			AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId)); 
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_10":
			dialog.text = "그렇지? 거기 뭐가 있었어? 말해 봐!";
			link.l1 = "여자의 불안한 영혼이 있었어! 다행히도, 나는 현지 신부에게 내 검에 축복을 받아 사악한 것을 물리칠 수 있었지, 그래서 모든 게 잘 해결됐어. 이제 그 영혼은 더 이상 널 괴롭히지 않을 거야.";
			link.l1.go = "Lantern_11";
		break;
		
		case "Lantern_11":
			dialog.text = "오 주님, 우리의 죄 많은 영혼을 구하소서! 내가 경고했잖아! 그런데도 내 말을 믿지 않았지!";
			link.l1 = "그래, 나도 진심으로 유감이네. 하지만 이제는 다 괜찮아 – 내가 이곳에 성수를 뿌렸으니, 어떤 영혼도 무덤에서 감히 일어나지 못할 걸세. 안심하고 편히 자게.";
			link.l1.go = "Lantern_12";
		break;
		
		case "Lantern_12":
			dialog.text = "정말 감사합니다! 이게 저에게 얼마나 큰 의미인지 모르실 거예요! 자, 이걸 받아주세요. 많지는 않지만, 보상 없이 보내드릴 수는 없으니까요.";
			link.l1 = "고맙소, 거절할 수 없겠군. 행운을 빌겠소!";
			link.l1.go = "Lantern_13";
		break;
		
		case "Lantern_13":
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "3");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "Lantern_14":
			dialog.text = "아니라고? 그럼 도대체... 아니, 신의 이름으로, 거기서 무슨 일이 있었던 거지?";
			link.l1 = "유령은 전혀 없었어. 젊은 연인이 이 납골당을 만남의 장소로 선택한 거야. 그들의 부모가 이 결합을 반대해서, 둘만 있을 곳을 찾고 있었던 거지.";
			link.l1.go = "Lantern_15";
		break;
		
		case "Lantern_15":
			dialog.text = "혼자라고?.. 저 젊은 것들 말이지! 또 여기 오기만 해 봐라! 채찍으로 둘 다 쫓아내든가 지하 묘지에 가둬버려서 거기서 나오지 못하게 할 거다!!!";
			link.l1 = "이제 그놈들은 여기 다시 안 올 거야. 내가 그 자잘한 장난질이 이 지역 경비병을 제대로 겁먹게 했다고 말해줬거든. 원래 그게 목적이었지. 그리고 참고로, 어차피 문 자물쇠도 고장 났어.";
			link.l1.go = "Lantern_16";
		break;
		
		case "Lantern_16":
			dialog.text = "문제 없어, 내가 대신할게. 하지만 내가 그놈들을 잡기만 하면...";
			link.l1 = "그렇게 화내지 마. 우리도 다 그런 나이였잖아. 여기서 연애하려고 온 건 아닐 거야.";
			link.l1.go = "Lantern_17";
		break;
		
		case "Lantern_17":
			dialog.text = "그럴 수도 있지... 뭐, 주님께서 그들을 지켜주시길. 곤경에 처한 늙은이를 그냥 두지 않아줘서 고맙네. 자, 이걸 받아주게. 많지는 않지만, 보상 없이 보낼 수는 없지.";
			link.l1 = "고맙소, 거절할 수 없겠군. 행운을 빌겠소!";
			link.l1.go = "Lantern_18";
		break;
		
		case "Lantern_18":
			DialogExit();
			pchar.quest.NoiseCemetery_SeaExit.over = "yes";
			AddMoneyToCharacter(PChar, 1000);
			pchar.questTemp.Lantern = "Done";
			AddQuestRecord("NoiseCemetery", "4");
			CloseQuestHeader("NoiseCemetery");
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря 
	}
}
