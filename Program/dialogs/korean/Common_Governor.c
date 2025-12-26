// boal 25/04/04 общий диалог Governor
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Governor\" + NationShortName(sti(NPChar.nation)) + "_Governor.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
    
    ref offref, sld;
    int i, cn;
    int qty;
    int iSumm;
    string attrLoc;

    /// выкуп колонии
    ref CaptGovenor, FortColony;
    int f, colony_money;

    int k = 1000;
    if (CheckAttribute(Nations[sti(NPChar.nation)], "Fort"))
    {
        k = (300 - sti(Nations[sti(NPChar.nation)].Fort)*10);
    }
	bool ok;
	
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "CityGive_" , 0) != -1)
 	{
        i = findsubstr(attrLoc, "_" , 0);
	 	NPChar.quest.CityIdx = strcut(attrLoc, i+1, strlen(attrLoc)-1); // индех в конце
 	    Dialog.CurrentNode = "ColonyGive";
 	}
 	
	switch (Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOff");
		break;
		
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
		break;
		
		case "First time":
            NextDiag.TempNode = "First time";
			if (LAi_grp_playeralarm > 0)
			{
       			dialog.text = NPCharRepPhrase(pchar,LinkRandPhrase("네가 감히 총독 관저에 얼굴을 들이밀다니?! 정말 미쳤구나...","이 게으름뱅이들이 어떻게 적이 내 저택에 침입하게 놔둔 거지? 도무지 이해가 안 되는군...","분명히, 내 경비들이 한 푼의 값어치도 없다는 말이군, 어떤 부랑자가 내 저택 안을 돌아다니고 있다면..."),LinkRandPhrase("무엇이 필요하지, "+GetSexPhrase("기어가다","냄새나는 놈")+"?! 내 병사들이 이미 네 뒤를 쫓고 있다, "+GetSexPhrase("더러운 해적","악취나는 놈")+"!",""+GetSexPhrase("Filthy","Filthy")+" 살인자야, 당장 내 집에서 나가라! 경비병들!","나는 너 따위 안 무서워, "+GetSexPhrase("놈","놈")+"! 곧 우리 요새에서 교수형을 당하게 될 거다, 멀리 못 갈 거야..."));
				link.l1 = NPCharRepPhrase(pchar,RandPhraseSimple("군인들은 아무 쓸모도 없어...","넌 절대 날 잡지 못할 거야."),RandPhraseSimple("닥쳐, 이놈아, 아니면 그 더러운 혀를 뽑아버릴 테니까!","내가 말하는데, 이봐 친구야: 얌전히 앉아 있지 않으면 네 목을 잘라 저 문 밖에 있는 네 사냥개들에게 던져줄 거야..."));
				link.l1.go = "fight";
				break;
			}
			if (npchar.quest.meeting == "0")
			{
				dialog.text = "당신이 면담을 매우 끈질기게 요청했다고 들었습니다. 내 이름은 "+GetFullName(npchar)+". 나는 식민지 총독이오 "+NationNameGenitive(sti(NPChar.nation))+", 왕실의 대리인 "+NationKingsName(npchar)+" 이 바다에서. 이제, 부디 친절하게 말씀해 주시겠습니까, 방문 목적이 무엇인지, "+GetAddress_Form(NPChar)+".";
				link.l1 = "내 이름은 "+GetFullName(pchar)+".";
				link.l1.go = "node_1";
				npchar.quest.meeting = "1";
			}
			else
			{
				dialog.text = RandPhraseSimple("오, 또 너냐? 그래서, 총독에게서 뭘 원하는 거지 "+NationNameGenitive(sti(NPChar.nation))+" 이번에는?","또다시 나를 국정의 중요한 일에서 방해하는 건가? 무슨 용건이지, "+GetAddress_Form(NPChar)+"?");
				link.l1 = "왕실의 이름으로 일하는 것에 대해 당신과 이야기하고 싶소 "+NationNameGenitive(sti(NPChar.nation));
				link.l1.go = "work";
				link.l2 = "중요한 일로 당신과 이야기할 필요가 있어.";
				link.l2.go = "quests"; // файл нации
				//Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l3 = "초대를 받아서 레가타에 참가하러 왔소. 여기 내 초대장이오.";
					link.l3.go = "Regata";
				}
				//<-- Регата
				link.l10 = "미안하지만, 처리해야 할 일이 좀 있어.";
				link.l10.go = "exit";
			}
		break;
		
		case "node_1":
			dialog.text = "그래서 무슨 일로 여기까지 와서 내 중요한 국정 업무를 방해하는 것이오?";
			link.l1 = "왕관의 이름으로 일하는 것에 대해 당신과 이야기하고 싶었소 "+NationNameGenitive(sti(NPChar.nation));
			link.l1.go = "work";
			link.l2 = "중요한 일에 대해 당신과 이야기하려고 했소.";
			link.l2.go = "quests";
			//Jason --> Регата
			if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
			{
				link.l3 = "나는 레가타에 참가하려고 여기 왔어. 이게 내 초대장이야.";
				link.l3.go = "Regata";
			}
			//<-- Регата
			link.l10 = "그저 예의상 들른 것뿐이오, 다른 이유는 없소. "+GetAddress_FormToNPC(NPChar);
			link.l10.go = "node_2";
		break;

		case "node_2":
			dialog.text = "그렇다면, 내 사무실에서 나가 주시고 내 업무를 방해하지 말아 주십시오.";
			link.l1 = "그래, 그래, 물론이지. 귀찮게 해서 미안해.";
			link.l1.go = "exit";
		break;
		
		case "work":
            dialog.text = "일거리를 찾고 있다면, 식민지 총독들에게 이야기해 보시오. 그들은 똑똑하고 용감한 선장이 자주 필요하오.";
			link.l1 = "명심하겠소. 고맙소.";
			link.l1.go = "exit";
		break;
		
		//--> Jason регата
		case "Regata":
			dialog.text = "오, 훌륭하군요, 선장님! 다시 뵙게 되어 반갑습니다! 마침 잘 오셨습니다 – 며칠 후면 레가타가 시작될 예정이거든요. 전령이 전달했을 편지에서 레가타 규칙을 읽어보셨습니까?";
			link.l1 = "예, 나리, 했습니다.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);//уберем письмо
			TakeNationLicence(HOLLAND);//уберем лицензию
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		break;
		
		case "Regata_1":
			dialog.text = "그럼 5만 페소, 즉 상금에 쓰일 입장료는 준비했나?";
			if (makeint(Pchar.money) >= 50000)
			{
				link.l1 = "네, 물론입니다. 제 수고비를 받아 주십시오.";
				link.l1.go = "Regata_2";
			}
			link.l2 = "지금은 돈이 좀 부족하네. 하지만 가능한 한 빨리 꼭 가져오겠네.";
			link.l2.go = "Regata_nomoney";
		break;
		
		case "Regata_2":
			dialog.text = "좋소. 이기면 돈을 다섯 배로 돌려받게 될 것이오. 이제, 레가타 규칙을 어기지 않는 방법을 알아야 하오.\n자세한 내용은 헨리 스티븐슨과 상의하시오. 그는 관저 방에 있을 것이오. 그를 만나면 모든 것을 설명해 줄 것이오.";
			link.l1 = "알겠소. 말씀하신 대로 하겠소.";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -50000);
			pchar.quest.Regata_Guber.win_condition.l1 = "location";
			pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
			pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
			pchar.questTemp.Regata.Begin = "true";
			NextDiag.TempNode = "First time";
		break;
		
		case "Regata_nomoney":
			dialog.text = "좋아요, 하지만 너무 오래 걸리지 마십시오, 선장님. 곧 레가타가 시작될 테니까요.";
			link.l1 = "알겠습니다. 레가타가 시작되기 전에 돈을 가져오도록 하겠습니다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_1";
			pchar.questTemp.Regata.nomoney = "true";
		break;
		
		//регата-финал
		case "Regata_Final":
			dialog.text = "그리고 여기 우리 레가타의 우승자가 있습니다! 안녕하세요, 선장님 "+GetFullName(pchar)+"! 이 훌륭한 성공을 진심으로 축하드립니다! 요트 경주 우승자는 언제나 영국 식민지에서 인기가 많지요, 그럴 만도 합니다.";
			link.l1 = "감사합니다, 나리!";
			link.l1.go = "Regata_complete";
		break;
		
		case "Regata_complete":
			dialog.text = "이제 당신에게 가장 기쁜 부분으로 넘어가죠 - 시상식입니다. 1등 상금은 25만 페소입니다. 여기 있습니다!";
			link.l1 = "고마워!";
			link.l1.go = "Regata_complete_1";
		break;
		
		case "Regata_complete_1":
			AddMoneyToCharacter(pchar, 250000);
			int iGift;
			string sItem1, sItem2, sItem3, sAdd;
			
			iGift = 3;
			switch (iGift)
			{
				case 0:
					sItem1 = "blade_10";//корд
					sItem2 = "cirass6";
					sItem3 = "bussol";
					sAdd = "cord, duelist's vest and boussole";
				break;
				
				case 1:
					sItem1 = "blade_15";//маринера
					sItem2 = "cirass2";//рейтарский панцирь
					sItem3 = "bussol";
					sAdd = "marinera, reiter's armour and boussole";
				break;
				
				case 2:
					sItem1 = "blade_17";//бретта
					sItem2 = "cirass7";//карацена
					sItem3 = "bussol";
					sAdd = "bretta, karacena and boussole";
				break;
				
				case 3://
					sItem1 = "blade_20";//мадонна
					sItem2 = "cirass2";//офицерская кираса
					sItem3 = "bussol";
					sAdd = "'Madonna', officer's cuirass and boussole";
				break;
			}
			GiveItem2Character(pchar, sItem1);
			GiveItem2Character(pchar, sItem2);
			GiveItem2Character(pchar, sItem3);
			dialog.text = "또한, 귀하는 귀중한 상품 세트의 수령 자격이 있습니다: "+sAdd+". 이제 모두 네 거다.";
			link.l1 = "정말 기쁩니다, 나리! 정말로, 이렇게 될 줄은 몰랐습니다.";
			link.l1.go = "Regata_complete_2";
		break;
		
		case "Regata_complete_2":
			dialog.text = "모든 영국 식민지를 대표하여, 경기에 참가해 주셔서 기쁘게 감사 인사를 전합니다. 다시 한 번 승리를 축하드립니다! 내기를 하셨다면, 아직 상금을 받지 않으셨다면 지금이야말로 헨리 스티븐슨 나리를 찾아가 상금을 받으실 좋은 기회입니다. 행운을 빕니다, 선장님!";
			link.l1 = "친절한 말씀 감사합니다, 나리! 저 또한 이렇게 큰 행사에 참여할 기회를 주셔서 감사드립니다. 이제 작별을 고하고 물러가도록 하겠습니다.";
			link.l1.go = "Regata_complete_3";
		break;
		
		case "Regata_complete_3":
			DialogExit();
			NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}
