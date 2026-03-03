//Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	// вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--
	
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "뭘 원하지?";
			link.l1 = "아무것도 아니다.";
			link.l1.go = "exit";
			link.l2 = RandPhraseSimple("너한테 물어볼 게 있어.","정보가 필요하다.");
			link.l2.go = "quests";//(перессылка в файл города)
			
			if (npchar.quest.meeting == "0")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger"))//захват пассажира
				{
					dialog.text = "이봐, 선장! 그래, 너 말이야. 이리 와, 너한테 거래가 있어...";
					link.l1 = "그래서 무슨 일인데?";
					link.l1.go = "passenger";
					link.l2 = "나는 바빠, 친구. 다음에 보자.";
					link.l2.go = "exit_quest";
					npchar.quest.meeting = "1";
					DeleteAttribute(npchar, "talker"); //снимаем говорилку
					break;
				}
				dialog.text = LinkRandPhrase("이봐, 선장, 나 지금 사실 바빠. 뭐 필요해?","무슨 일이오, 선장?","선장님, 지금 말할 기분 아니야. 뭐 원하는 거야?");
				link.l1 = "인사, "+GetAddress_FormToNPC(NPChar)+". 잠깐 기다려, 너에게 물어볼 게 있어.";
				link.l1.go = "question";
				link.l2 = RandPhraseSimple("당신에게 물어볼 것이 있소.","정보가 필요해.");
				link.l2.go = "quests";//(перессылка в файл города)
				link.l3 = "별거 아니야, 난 선술집에 가는 길이야...";
				link.l3.go = "exit";
				npchar.quest.meeting = "1";
			}
			NextDiag.TempNode = "First time";
		break;

//----------------------------------------захват пассажиров для выкупа------------------------------------------
			case "passenger":
				DeleteAttribute(npchar, "talker");
				dialog.text = "흠. 자네는 배의 선장이지만 상인처럼 보이지는 않는군. 주머니에 동전 좀 있는 것 같은데... 두블룬 한 줌과 바꿀 만한 흥미로운 정보를 들어볼 생각 없나?";
				link.l1 = "먼저, 네 정보가 8리알 한 닢의 가치라도 있는지 증명해 봐.";
				link.l1.go = "passenger_1";
			break;
		
			case "passenger_1":
				dialog.text = "그래, 선장, 그래. 내가 부르는 값보다 훨씬 비싼 물건이지. 금을 주면 언제, 어떤 배로 아주 중요한 인물이 항해할지 알려주지. 그 사람을 잡으면 아주 좋은 값에 몸값을 받을 수 있을 거야... 심지어 사는 사람 이름까지 알려줄게. 거래하겠나?";
				link.l1 = "말도 안 돼! 난 유괴범이 아니야. 꺼져!";
				link.l1.go = "exit_quest";
				link.l2 = "그대가 진실을 말하고 있다는 걸 내가 어떻게 알 수 있지?";
				link.l2.go = "passenger_2";
			break;
		
			case "passenger_2":
				pchar.GenQuest.Marginpassenger.Dublon = 70+hrand(5)*10;
				dialog.text = "너를 속이는 건 정말 어리석은 짓이지, 바다의 사나이. 나는 이 마을에 살고 있고, 괜한 문제를 만들고 싶지 않아. 단지\n "+sti(pchar.GenQuest.Marginpassenger.Dublon)+" 두블론을 주면 내가 모든 정보를 제공하지. 훨씬 더 많이 벌 수 있을 거야.";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "일리가 있군. 금을 가져가고 이제 말해.";
					link.l1.go = "passenger_4";
				}
				link.l2 = "지금은 동전이 충분하지 않아.";
				link.l2.go = "passenger_3";
				link.l3 = "장난해? 헛된 약속에 진짜 금을 내라고? 꺼져...";
				link.l3.go = "exit_quest";
			break;
		
			case "passenger_3":
				dialog.text = "안 그래? 좋아, 선장. 나 며칠 더 기다릴 수 있어, 이 정보도 마찬가지고. 금을 가지고 오면 나를 찾아. 나 찾는 거 어렵지 않을 거야... 오늘은 말이지, 하하하!";
				link.l1 = "그렇게 이빨 드러내지 마라. 좋아, 금을 가져다주지... 마음이 바뀌지 않는다면 말이지. ";
				link.l1.go = "passenger_wait";
			break;
			
			case "passenger_wait":
			DialogExit();
				SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
				npchar.dialog.currentnode = "passenger_repeat";
			break;

			case "passenger_repeat":
				dialog.text = "내 금을 가져왔나?";
				if (PCharDublonsTotal() >= sti(pchar.GenQuest.Marginpassenger.Dublon))
				{
					link.l1 = "그래. 가져가. 이제 거짓말할 생각도 하지 마...";
					link.l1.go = "passenger_4";
				}
				link.l2 = "아직 아니야. 나중에...";
				link.l2.go = "exit";
				Nextdiag.Tempnode = "passenger_repeat";
			break;
			
			case "passenger_4"://установка параметров
				pchar.quest.Marginpassenger_Over.over = "yes"; //снять возможный таймер
				RemoveDublonsFromPCharTotal(sti(pchar.GenQuest.Marginpassenger.Dublon));
				pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
				pchar.GenQuest.Marginpassenger.City = npchar.city;
				pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city); 
				pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
				pchar.GenQuest.Marginpassenger.Days = 10+hrand(5);
				pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
				pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
				pchar.GenQuest.Marginpassenger.Chance = 0.8+frand(0.4);
				SelectMarginpassengerParameter();
				log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
				dialog.text = "화약을 잘 말려둬, 곧 필요할 테니까, 선장. 이제 들어봐, in "+FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days))+" 우리 식민지에서 배가 떠날 것이오, 그 배는 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" '라는 이름의"+pchar.GenQuest.Marginpassenger.ShipName+"' 그리고 그것은 ~로 향할 거야 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity+"Gen")+". 승객이 있을 거요 -  "+pchar.GenQuest.Marginpassenger.Text+", 이름은 "+pchar.GenQuest.Marginpassenger.q1Name+"\n선장 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")+"Gen"))+" 모든 상인들처럼 간이 쪼그라든 겁쟁이야, 하하하! 어쩌면 싸움도 피할 수 있겠지. 그냥 놈을 제대로 겁만 주면 스스로 목표물을 넘길 거야, 히히\n알다시피, "+pchar.GenQuest.Marginpassenger.Text1+", 아마 돈은 받겠지만, 그 다음엔 현지 당국이 널 쫓게 될 거야. 차라리 사냥감을 데려가는 게 낫겠어 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+". 거기 가면 이름이 \n "+pchar.GenQuest.Marginpassenger.q2Name+"\n"+pchar.GenQuest.Marginpassenger.Text2+" 네 이름조차 말할 필요도 없지. 네가 어디서 네 사람을 몸값 받고 풀어줄지는 네 결정이야, 하지만 감당 못할 일은 벌이지 마라... 하지만 "+sti(pchar.GenQuest.Marginpassenger.Dublon)*4+" 두블룬을 달라고 해도 돼, 알겠어?";
				link.l1 = "그래. 나는 내 배로 돌아가서 그걸 항해일지에 기록할 거야.";
				link.l1.go = "passenger_5";
			break;
		
			case "passenger_5":
				dialog.text = "정확해! 제대로 선택했군. 좋아, 선장, 이 쉬운 일 잘 해내길 바라. 아, 맞다, 거의 잊을 뻔했네: "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" 항구가 아니라 근처 만 중 한 곳에서 출항할 거야. 잘 지켜보라고. 행운을 빌고, 금화도 고맙다!";
				link.l1 = "천만에. 하룻밤에 다 써버리지 말라고.";
				link.l1.go = "exit_quest";
				npchar.lifeday = 0;
				ReOpenQuestHeader("Marginpassenger");
				AddQuestRecord("Marginpassenger", "1");
				AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.City));
				AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity));
				AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
				AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
				AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
				AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
				AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name")+"Voc")));
				AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
				AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
				pchar.GenQuest.Marginpassenger = "begin";
				SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
			break;
			
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 진정하고 무기를 집어넣어.","이봐, 진정하고 무기를 집어넣어.");
			link.l1 = LinkRandPhrase("좋아.","좋아.","원하시는 대로 하겠습니다.");
			link.l1.go = "exit";
		break;
		
		case "question":
			dialog.text = LinkRandPhrase("돌려 말하지 마시오, 선장님. 원하는 걸 바로 말씀하시오!","그래, 좋아. 뭐 원하는 거야?","질문 있나? 좋아, 선원, 듣고 있다.");
			link.l1 = LinkRandPhrase("요즘 소문 좀 들려줄 수 있겠어?","여기서 최근에 흥미로운 일이 있었나?","카리브에서 무슨 일이 벌어지고 있지?");
			link.l1.go = "rumours_marginal";
		break;
		
		case "exit_quest":
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_"+(rand(5)+11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "He wants to marry her and will pay a significant sum for the girl.";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "store keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the store keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's daughter";
				pchar.GenQuest.Marginpassenger.Text1 = "from her father, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_"+(rand(9)+11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "He has been planning to ingratiate himself with this family and he will pay a lot for the prisoner ";
		switch (hrand(4))
		{
			case 0: 
				pchar.GenQuest.Marginpassenger.Text = "trader's relative, shipmaster's";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipmaster";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_store";
			break;
			case 1: 
				pchar.GenQuest.Marginpassenger.Text = "shipyard's master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the shipyard's master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_shipyard";
			break;
			case 2: 
				pchar.GenQuest.Marginpassenger.Text = "tavern keeper's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the tavern keeper";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_tavern";
			break;
			case 3: 
				pchar.GenQuest.Marginpassenger.Text = "banker's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the banker";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_bank";
			break;
			case 4: 
				pchar.GenQuest.Marginpassenger.Text = "harbor master's relative";
				pchar.GenQuest.Marginpassenger.Text1 = "from his relative, the harbor master";
				pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City+"_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
