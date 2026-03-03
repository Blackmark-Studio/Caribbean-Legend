// городские тюрьмы
void ProcessDialogEvent()
{
	int amount, iGunQty, iGunGoods, iGunPrice, iTemp;
	int iTest;
	ref NPChar, sld, location;
	ref arItem;
	ref rColony;
	aref Link, NextDiag;
	string sTemp;
	float locx, locy, locz;
	bool  ok;
	// belamour для ночного приключения -->
	int i;
	int SoldQty = 0;
	int SoldNum[10];
	// <--

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

    // вызов диалога по городам -->
    NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Prison\" + NPChar.City + "_Prison.c";
    if (LoadSegment(NPChar.FileDialog2))
	{
        ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
    // вызов диалога по городам <--

	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	
		case "fight":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

		case "NoMoreTalkExit":
			LAi_CharacterDisableDialog(npchar);
			DialogExit();
		break;
		//---------------- Начальник тюрьмы ------------------
		case "First_officer":
			dialog.text = RandPhraseSimple("나는 감옥장이다. 여기서 무슨 일이냐?","무슨 일로 왔지? 감옥에는 왜 온 거야?");
			NextDiag.TempNode = "First_officer";
			if(startHeroType == 4 && NPChar.location == "SantaCatalina_prison" && !CheckAttribute(pchar, "questTemp.HelenSCprison"))
			{
				dialog.text = "맥아더 양? 당신을 보게 되어 놀랐군요. 내가 알기로는 당신 선원이나 스웬슨 선장 일행 중 누구도 체포하지 않았소.";
				link.l1 = "저 그냥 여기 있는 거요, 나리. 그게 안 되는 겁니까? 당신 몰래 죄수들이랑 얘기한 적 없소.";
				link.l1.go = "Helen_meeting";
				pchar.questTemp.HelenSCprison = true;
				break;
			}
			// --> Sinistra Длинные тени старых грехов
			if(CheckAttribute(pchar,"questTemp.DTSG_AntiguaTrevoga") && npchar.city == "SentJons")
			{
				dialog.text = "아, 샤를 드 모르... 너도 체포되어 네 장교와 함께 있어야 마땅하지만... 은행에서 있었던 일은 유감스러운 오해로 간주되었네.";
				link.l1 = "이 대화를 시작하는 방식이 마음에 드는군, 나리. "+GetFullName(NPChar)+". 모든 걸 설명할 수 있어.";
				link.l1.go = "DTSG_AntiguaTrevoga_2";
				break;
			}
			// <-- Длинные тени старых грехов
			
			//--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "jailskiper")
			{
				link.l1 = "장교님, 당신들 감옥에 폴케 들루크라는 사람이 있다고 들었습니다. 그의 석방을 위해 제가 할 수 있는 일이 있습니까?";
                link.l1.go = "Sharlie";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "freeskiper")
			{
				link.l1 = "장교님, 저입니다. 죄수 폴케 들루크에 관해 다시 왔습니다. 제가 그의 빚 권리를 샀으니, 이 사람을 제 보호 하에 풀어주길 원합니다. 여기 그의 채무 서류가 있으니, 한번 확인해 보십시오.";
                link.l1.go = "Sharlie_3";
				break;
			}	
			//<-- Бремя гасконца
			
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// Офицер с патентом
			if(IsOfficerFullEquip())
			{
				dialog.text = "안녕하십니까, 선장님. 무슨 일로 여기 오셨습니까?";
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "안녕하십니까, 부제독님! 무엇을 도와드릴까요?";
			}
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "각하, 총독님! 명령이 있으십니까?";
			}
			// <-- legendary edition
			link.l1 = "아, 별거 아니야. 그냥 도시를 둘러보다가 우연히 여기까지 오게 됐어.";
			link.l1.go = "exit";
			link.l2 = "사업 이야기를 좀 하고 싶었어.";
			if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakFort"))
			{
				if((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
				{
					link.l2.go = "F_ShipLetters_1";
				}
				else
				{
					link.l2.go = "quests";
				}		
			}
			else
			{
				if(CheckAttribute(pchar,"questTemp.ReasonToFast") && !CheckAttribute(pchar,"questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Prison1";
				}
				else
				{
					link.l2.go = "quests";
				}	
			}
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "감옥 안으로 들어가고 싶어.";
				link.l4.go = "ForGoodMove";		
			}
			if (CheckAttribute(pchar, "questTemp.jailCanMove.City") && npchar.city == pchar.questTemp.jailCanMove.City)
			{
				link.l5 = "이봐, 이라는 죄수가 무슨 죄를 지었는지 말해줄 수 있나? "+GetFullName(characterFromId(pchar.questTemp.jailCanMove.prisonerId))+"무슨 죄로 복역 중이오?";
				link.l5.go = "KnowAboutPrisoner";	
			}
			
			if(CheckAttribute(pchar,"GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
			{
				if(!CheckAttribute(pchar,"GenQuest.CaptainComission.PrisonFree"))
				{
					bool zMsm = (CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour")) && (!CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"));
					if(pchar.GenQuest.CaptainComission == "MayorTalkBad" || zMsm) //говорил с губером и отказался или узнал слухи, но не говорил с губером
					{
						link.l6 = "순시선의 전 선장에 대해 들었어 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+" "+pchar.GenQuest.CaptainComission.Name+" 여기서 구금되어 있습니다. 그와 이야기해도 되겠습니까?";
						link.l6.go = "CapComission_PrisonBad1";
					}
					if(pchar.GenQuest.CaptainComission == "MayorTalkGood")
					{
						link.l6 = "I "+GetFullName(pchar)+", 총독을 대신하여 그리고 그의 명령을 받아 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+"전 선장과 이야기해야 해 "+pchar.GenQuest.CaptainComission.Name+".";
						link.l6.go = "CapComission_PrisonGood1";
					}
				}	
			}
			if(CheckAttribute(pchar,"GenQuest.EncGirl"))
			{
				if(pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if(pchar.GenQuest.EncGirl.Father == "fort_keeper"  && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l9 = "이건 당신 딸에 관한 일이오...";
						link.l9.go = "EncGirl_1";
					}
				}
			}
			
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "begin" && NPChar.location == pchar.GenQuest.Marginpassenger.City + "_prison")
			{
				link.l12 = "당신과 볼 일이 있소, 장교 나리. 당신 임무와 관련된 일이니 흥미로울 거라 생각하오.";
				link.l12.go = "Marginpassenger";
			}
			
			// Warship, 16.05.11. Генер "Justice for sale".
			if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_prison")
			{
				link.l13 = "어떤 남자에 대해 이야기하고 싶소 - "+PChar.GenQuest.JusticeOnSale.SmugglerName+". 그가 당신의 포로가 맞지요, 내가 틀리지 않았다면.";
				link.l13.go = "JusticeOnSale_1";
			}
			
			// --> belamour ночной приключенец
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToJail"))
			{
				link.l14 = "안녕하세요, 장교님. 제가 알기로 얼마 전에 술 취한 시민이 거리에서 경비병과 싸우려다 체포되었습니다."; 
				link.l14.go = "NightAdventure_CitizenHomie";
			}
			
			if(CheckAttribute(pchar,"GenQuest.NightAdventureToPrisoner"))
			{
				link.l14 = "장교님, 제가 보초와 이야기했더니 그가 자신의 주장을 철회했습니다. 여기 그가 써준 증서가 있습니다."; 
				link.l14.go = "NightAdventure_HomieToPrisoner";
			}
			// <-- приключенец
			NextDiag.TempNode = "First_officer";
		break;
		
		// --> Jason Похититель
		case "Marginpassenger":
			dialog.text = "그래? 무슨 할 말이라도 있나?";
			link.l1 = "요즘 나는 길에서 붙잡히곤 해 "+pchar.GenQuest.Marginpassenger.Name+" 나를 위해 더러운 일을 꾸며주겠다고 제안한 자가 있었지. 그 일은 바로 "+이름+"이라는 사람을 붙잡아 몸값을 요구하는 것이었어. "+pchar.GenQuest.Marginpassenger.q1Name+". 그거야 "+pchar.GenQuest.Marginpassenger.Text+"...";
			link.l1.go = "Marginpassenger_1";
		break;
		
		case "Marginpassenger_1":
			dialog.text = "흠... 아주 흥미로운데 - 계속 말씀해 주시죠!";
			link.l1 = "그는 자신이 탄 배의 이름을 알고 있었어, "+pchar.GenQuest.Marginpassenger.q1Name+" 항해할 계획이었어. 지금은 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType),"Name")))+" '라고 불리는 '"+pchar.GenQuest.Marginpassenger.ShipName+"'. 그리고 그 배가 출항할 예정이었던 시간도 말해줬어.";
			link.l1.go = "Marginpassenger_2";
		break;
	
		case "Marginpassenger_2":
			dialog.text = "그래서 그가 네게 그 승객을 붙잡아서 몸값을 요구하라고 제안했단 말이냐?";
			link.l1 = "정확히 그렇지. 몸값을 받으려면 나는 가야 할 곳이 "+XI_ConvertString("Colony"+pchar.GenQuest.Marginpassenger.Targetcity)+", 어떤 이름을 가진 사람에게 "+pchar.GenQuest.Marginpassenger.q2Name+". 나는 이 정보를 얻으려고 그에게 돈을 줬지만, 물론 그 사람을 납치할 생각은 없었어.";
			link.l1.go = "Marginpassenger_3";
		break;
		
		case "Marginpassenger_3":
			dialog.text = "그래서 나를 보러 와서 알려주기로 한 건가?";
			link.l1 = "맞아요. 저 악당의 행동이 당신네 마을 시민들에게 위협이 된다고 확신하며, 적절한 조치를 취해 주시길 바랍니다.";
			link.l1.go = "Marginpassenger_4";
		break;
		
		case "Marginpassenger_4":
			dialog.text = "나에게 찾아온 것은 정말 옳은 선택이었소, "+GetAddress_Form(NPChar)+"! 이 녀석, "+pchar.GenQuest.Marginpassenger.Name+", 오래전부터 우리 감시 하에 있었소. 내가 조사해 보겠소. 만약 자네 말이 모두 사실로 확인된다면, 이 자식은 반년 동안 감옥에 쳐넣을 것이오. 그래야 존경받는 시민들에게 이런 음모를 꾸미지 못한다는 걸 뼈저리게 알게 될 테니!\n자네의 정직함과 선한 일에 기꺼이 나서 준 점에 대해, 반드시 우리 총독께 보고하겠소. 물론, 그분이 자네를 더 좋게 보게 될 것이오... 알겠지? 도와줘서 고맙소, 선장!";
			link.l1 = "흠... 천만에, 도와드릴 수 있어서 기뻤소. 안녕히 가시오!";
			link.l1.go = "Marginpassenger_5";
		break;
		
		case "Marginpassenger_5":
			DialogExit();
			NextDiag.CurrentNode = "First_officer";
			AddQuestRecord("Marginpassenger", "20");
			AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
			CloseQuestHeader("Marginpassenger");
			pchar.quest.Marginpassenger_InWorld.over = "yes"; //снять таймер
			DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
			AddCharacterExpToSkill(pchar, "Leadership", 100);//авторитет
			ChangeContrabandRelation(pchar, -25);
			if (GetCharacterIndex("MarginCap") != -1)
			{
				sld = characterFromId("MarginCap");
				sld.lifeday = 0;
				Map_ReleaseQuestEncounter(sld.id);
				Group_DeleteGroup("Sea_MarginCap1");
			}
		break;
		//<-- Похититель

		case "EncGirl_1":
			dialog.text = "귀 기울여 듣고 있네.";
			link.l1 = "도망자를 데려왔소.";
			link.l1.go = "EncGirl_2";
		break;
		
		case "EncGirl_2":
			dialog.text = "아이고, 선장님, 정말 감사합니다! 그 아이는 괜찮나요? 다친 데는 없나요? 왜 도망친 거죠? 왜요?\n그 아이는 이해하지 못하나요? 신랑은 부유하고 중요한 사람입니다! 젊음이란 순진하고 어리석지요... 심지어 잔인하기도 하고요. 명심하십시오!";
			link.l1 = "음, 당신이 그녀의 아버지이고 최종 결정은 당신에게 있지만, 결혼을 서두르지는 마십시오...";
			link.l1.go = "EncGirl_3";
		break;
		
		case "EncGirl_3":
			dialog.text = "네가 뭘 안다고 그래? 자식 있어? 없어? 나중에 자식 생기면 그때 나한테 와서 얘기하자고.\n나는 그녀를 가족에게 데려다 주는 사람에게 보상을 약속했어.";
			link.l1 = "고마워. 그녀를 계속 지켜봐야 해. 내 촉으로는 저걸로 끝나지 않을 것 같거든.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;
		
		// ------------------------- Повод для спешки -----------------------------
		case "ReasonToFast_Prison1":
			pchar.questTemp.ReasonToFast.SpeakOther = true;
			dialog.text = "듣고 있소, 선장.";
			link.l1 = "당신네 주둔지 장교와 해적들 사이의 범죄적 결탁에 대해 말씀드리고 싶소 (상황을 설명한다).";
			if(makeint(pchar.reputation.nobility) < 41)
			{
				link.l1.go = "ReasonToFast_Prison_BadRep";			
			}
			else
			{
				link.l1.go = "ReasonToFast_Prison_GoodRep";	
			}
		break;
		case "ReasonToFast_Prison_GoodRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "감사합니다,"+GetSexPhrase("나리","아가씨")+"! 당장 그 악당을 체포하라고 명령을 내리겠소.\n하지만 자네가 비용을 썼고, 시 재정은 유감스럽게도 텅 비었네...";
				link.l1 = "나리! 돈 때문에 그런 게 아닙니다...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_11";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "감사합니다, "+GetSexPhrase("나리","아가씨")+"! 당장 그 악당을 체포하라고 명령을 내리겠소.\n생각해 보시오! 우리는 그의 훌륭한 공로를 인정해서 직접 무기를 하사하려던 참이었소. 모든 오해가 풀려서 다행이오, 이제 부끄러울 일도 없소!";
				link.l1 = "언제나 정의를 실현할 준비가 되어 있소.";
				link.l1.go = "ReasonToFast_Prison_GoodRep_21";			
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "Mi"+GetSexPhrase("스터","ss")+"! 우리는 그 장교랑 그 놈의 졸개들이 더러운 짓을 하고 있다는 걸 한동안 의심하고 있었지. 하지만 네가 증인도 없이 그들을 처리한 건 성급한 행동이었다고 생각해.";
				link.l1 = "나리! 하지만 저는 제 몸을 지켜야 했습니다...";
				link.l1.go = "ReasonToFast_Prison_GoodRep_31";	
				pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;	
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";	
			}
		break;
		
		case "ReasonToFast_Prison_BadRep":
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_1") 
			{ 
				// вилка_А
				dialog.text = "선장님, 지금 무슨 짓을 하신 건지 아십니까?! 우리가 한 달 넘게 이 함정을 준비해 왔는데! 그런데 선장님의 장난 때문에 우리 순찰대와 전령의 만남이 엉망이 되어버렸습니다\n "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_GEN)+" 이제 와서 자랑하러 온 거야?! 그럼 이 작전의 모든 지출과 비용을 내가 어떻게 설명해야 하는지 네가 말해줄 수 있겠군?!";
				link.l1 = "각하! 요점 자체를 보려 하지 않으시는군요...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				
				if(pchar.questTemp.ReasonToFast.chain == "A0") ReasonToFast_RemoveVictim();
				if(pchar.questTemp.ReasonToFast.chain == "A1") pchar.quest.ReasonToFast_ClearLakey.over = "yes";
			}
			if(pchar.questTemp.ReasonToFast == "PatrolSuccess_2") 
			{ 
				// получена карта
				dialog.text = "이 지도를 좀 보자...\n장난하는 거야? 이 누더기 양피지가 증거라고?";
				link.l1 = "각하! 분명히 요점을 외면하고 계십니다...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";
				TakeItemFromCharacter(pchar, "mapQuest");	
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";	
			}
			if(pchar.questTemp.ReasonToFast == "PatrolDied") 
			{ 
				// патруль перебит
				dialog.text = "이제야 순찰대 전체를 파괴한 것에 대한 참신한 변명을 듣는군. 뭐, 적어도 네가 여기 온 덕분에 우리가 살인자를 찾으러 다닐 필요는 없어졌지.";
				link.l1 = "각하! 요점 자체를 애써 외면하고 계십니다...";
				link.l1.go = "ReasonToFast_Prison_BadRep1";			
				pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
				pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
			}		
		break;
		
		case "ReasonToFast_Prison_GoodRep_11":
			dialog.text = "그럼에도 불구하고, 나는 그대의 노력이 보상받아야 한다고 생각하오. 여기, 이 지도를 가져가시오. 최근 교수형에 처해진 해적의 소지품에서 발견된 것이오. 신의 뜻이라면, 어쩌면 그대가 정말 그 보물을 찾을 수도 있겠지만, 내 생각엔 가능성이 희박하군...";
			link.l1 = "고맙소, 정말 후하시군요!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "15");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, "mapQuest"); 
			arItem = ItemsFromID("mapQuest");
			ReasonToFast_GenerateTreasureMap(arItem);
			pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_21":
			dialog.text = "그대의 열정은 칭찬할 만하오. 부디, 이 검을 보상으로 받아주시오 – 그대에게 해줄 수 있는 최소한의 보답이오. 아, 그리고 이 지도도 가져가시오. 군도에는 이런 가짜가 아주 많을 테니.";
			link.l1 = "고마워, 정말 너그럽구나!";
			link.l1.go = "exit";
			AddQuestRecord("ReasonToFast", "14");
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
			pchar.questTemp.ReasonToFast = "GetMap";			
			ReasonToFast_SetHunterCoastal();
		break;
		case "ReasonToFast_Prison_GoodRep_31":
			dialog.text = "그럴 수도 있지, 그럴 수도... 뭐, 이 거래는 신의 정의와 우리 주님의 뜻에 의해 결정된 거라 하세.";
			link.l1 = "고맙소, 정말 후하시군요!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", 1); 
			AddQuestRecord("ReasonToFast", "16");
			CloseQuestHeader("ReasonToFast");
			DeleteAttribute(pchar,"ReasonToFast");			
		break;
		
		case "ReasonToFast_Prison_BadRep1":
			dialog.text = "감히 나한테 설교하지 마라! 내 눈에는 네가 이 악당들과 한통속인 게 뻔히 보인다! 경비병들, 이 '친절한 이'를 잡아라!";
			link.l1 = "말도 안 돼!";
			link.l1.go = "fight";
			
			pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1			= "EnterToSea";           	
            pchar.quest.ReasonToFast_ExitFromTown.function    				= "ReasonToFast_ExitFromTownFight";
			pchar.questTemp.ReasonToFast.canSpeakSailor = true;			
			pchar.TownEscape = true;
			Flag_PIRATE();
		break;
		// ------------------------- Повод для спешки -----------------------------
		
		// -------------------------- Операция 'Галеон' ----------------------------
		case "CapComission_PrisonBad1":
			dialog.text = "그와 무슨 볼일이 있소?";
			link.l1 = "나는 개인적으로 논의할 일이 몇 가지 있소.";
			link.l1.go = "CapComission_PrisonBad2";
		break;
		
		case "CapComission_PrisonBad2":
			dialog.text = "선장님, 이 일에 대해 묻는 자는 누구든 체포하여 관저로 보내라는 직접 명령을 받았습니다 "+pchar.GenQuest.CaptainComission.Name+"추가 심문을 위해.";
			link.l1 = "여기 참 잘 꾸며놨군! 죄수들이 잡혀가려고 스스로 찾아오다니!";
			link.l1.go = "CapComission_PrisonBad3";
		break;
		
		case "CapComission_PrisonBad3":
			dialog.text = "그럼에도 불구하고, 무기를 내놓으라고 요청하겠소!";
			link.l1 = "꺼져! 힘으로 뺏어가 보시지!";
			link.l1.go = "fight";
			CaptainComission_GenerateCaptainInPrison(); // данила . на всякий случай ,чтобы сгенерился нормально.
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonGood1":
			dialog.text = "네, 물론입니다. 저는 총독으로부터 이번 일에 대해 당신을 도와주라는 명령을 받았습니다. 이제 죄수를 만나보셔도 됩니다.";
			link.l1 = "감사합니다...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			AddDialogExitQuest("CaptainComission_GenerateCapJail");
		break;
		
		case "CapComission_PrisonFree1":
		if(CheckAttribute(pchar,"GenQuest.CaptainComission"))// лесник . разделение диалога если кеп убит или нет
		{
			dialog.text = "음, 선장님, 저는 이 죄수를 석방할 권한이 없습니다. 총독에게 허가를 요청하셔야 합니다.";
			link.l1 = "장교님, 저는 심문을 위해 선의를 가지고 행동하고 있습니다. 죄수는 당국에 협조하고 은닉처를 밝히기로 동의했습니다. 시간이 급합니다 – 밀수꾼들이 귀중한 화물을 찾아내면, 그 물건은 백성들에게서 영영 사라질 것입니다.";
			link.l1.go = "CapComission_PrisonFree2";
		}
         else
		 {
         	dialog.text = "그를 죽이지 말았어야 했소, 선장... 하지만 내겐 상관없소. 이제 그 대신 당신을 처형해야겠군. 경비병들! 저 자를 잡아라!";
            link.l2 = "너, 잘못 건드린 상대야!...";
             link.l2.go = "fight";
			 NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		 }			 
		break;
		
		case "CapComission_PrisonFree2":
			dialog.text = "하지만 내가 그에게 호위를 붙일 수도 있소.";
			link.l1 = "굳이 그럴 필요 없어 - 경비는 충분하네. 게다가, 은닉처 위치가 알려지는 건 원치 않거든.";
			link.l1.go = "CapComission_PrisonFree3";
		break;
		
		case "CapComission_PrisonFree3":
			dialog.text = "흠... 뭐, 알겠다. 하지만 네가 그 자를 대신해 목숨으로 책임져야 할 거다.";
			link.l1 = "물론이지.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			AddDialogExitQuest("OpenTheDoors");
		break;
		// -------------------------- Операция 'Галеон' ----------------------------
		
		case "F_ShipLetters_1":
			dialog.text = "지금 말해라, 듣고 있다.";
			link.l1 = "내게 선박 서류가 좀 있네. 주인이 잃어버린 것 같은데, 자네에게 흥미로울지도 모르겠군.";
			link.l1.go = "F_ShipLetters_2";
			pchar.questTemp.different.GiveShipLetters.speakFort = true;
		break;
		
		case "F_ShipLetters_2":			
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
			{
				dialog.text = "헛소리 집어쳐! 내 일 방해하지 마! 신경 쓰이면 항만 당국에나 가봐!";
				link.l1 = "글쎄, 뭐, 고맙긴 하지...";
				link.l1.go = "exit";
			}
			else
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					dialog.text = "그래, 이곳의 주인이지. 어쩌면 전리품일지도\n "+sti(pchar.questTemp.different.GiveShipLetters.price2)+" 페소가 당신의 경계심에 대한 충분한 보상이 될 것이오, 선장.";
					link.l1 = "아마도 아니오.";
					link.l1.go = "F_ShipLetters_3";	
					link.l2 = "관대한 제안이군. 그럼 서류는 자네 것이야!";
					link.l2.go = "F_ShipLetters_4";
				}
				else
				{
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
					{
						dialog.text = "오, 그거 정말 흥미롭군! 시 재무관이 기꺼이 보수를 줄 거라 믿네 "+sti(pchar.questTemp.different.GiveShipLetters.price4)+" 불법 무역 퇴치에 기여해 주신 대가로 드리는 페소입니다.";
						link.l1 = "그렇지 않을 수도 있지.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "관대한 제안이군. 그럼 서류는 당신 거야!";
						link.l2.go = "F_ShipLetters_4";
					}
					if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
					{
						dialog.text = "오, 주님! 당신이 저에게 와 주시다니 참으로 행운입니다. 제 불운한 동료가 기꺼이 당신께 값을 치를 것이라 생각합니다. "+sti(pchar.questTemp.different.GiveShipLetters.price3)+" 이 사건이 공개되지 않게 하려면 페소가 필요하다.";
						link.l1 = "아닐지도 모르지.";
						link.l1.go = "F_ShipLetters_3";
						link.l2 = "관대한 제안이군. 그럼 서류는 당신 거요!";
						link.l2.go = "F_ShipLetters_4";
					}
				}
			}
		break;
		
		case "F_ShipLetters_3":
			dialog.text = "여기가 내 도시야, 선장.";
			link.l1 = "그걸 기억해 두겠다.";
			link.l1.go = "exit";
		break;
		
		case "F_ShipLetters_4":
			TakeItemFromCharacter(pchar, "CaptainBook"); 
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 1)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price4)); 
				}
			}
			if(sti(pchar.questTemp.different.GiveShipLetters.variant) == 2)
			{
				if(!CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakUsurer_1"))
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2)); 
				}
				else
				{
					addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price3)); 
				}
			}
						
			if((sti(pchar.questTemp.different.GiveShipLetters.variant) == 0) || (sti(pchar.questTemp.different.GiveShipLetters.variant) == 2))
			{	
				ChangeCharacterComplexReputation(pchar,"nobility", -1); 
				OfficersReaction("bad"); 
			}	
			pchar.questTemp.different = "free";
			pchar.quest.GiveShipLetters_null.over = "yes"; //снимаем таймер 
			AddQuestRecord("GiveShipLetters", "8");			
			CloseQuestHeader("GiveShipLetters");
			DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

		
        case "ForGoodMove":
			//belamour legendary edition диалоги, если герой имеет звания и заслуги перед отечеством -->
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "물론이지, 다 볼 수 있어. 여기 모든 게 완벽하게 정돈되어 있으니까!";
				link.l1 = "좋아, 확인해 보자, 중위.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "물론입니다, 각하. 지나가셔도 됩니다.";
				link.l1 = "감사합니다, 장교님.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// Офицер с патентом
			if(IsOfficerFullEquip() && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "글쎄, 거절할 이유는 없군 - 어쨌든 당신은 그 배의 선장이자 그곳을 위해 일하고 있으니 "+NationNameGenitive(sti(npchar.nation))+". 들어오시오."; 
				link.l1 = "감사합니다, 장교님.";
				link.l1.go = "exit";
				pchar.questTemp.jailCanMove = true;
				break;
			}
			// <-- legendary edition
			dialog.text = NPCStringReactionRepeat("하지만 그게 왜 필요하지? 믿어, 거기엔 도둑놈들이랑 산적들 말고는 아무 흥미로운 것도 없어.","그 소원에 대해서는 이미 이야기했었지.","또야? 우리 이미 두 번이나 그 얘기 했잖아!","흠, 또 이런군...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("그럼에도 불구하고, 저는 당신의 카스메이트 견학에 함께하고 싶습니다. 매우 흥미롭군요!","그래, 맞아. 하지만 그 얘기를 하고 싶었어.","글쎄, 세 번째면 될지도...","네 죄수들이 내 곁을 떠나지 않길 바라지.",npchar,Dialog.CurrentNode);
			link.l1.go = "ForGoodMove_1";
		break;
		
        case "ForGoodMove_1":
			pchar.questTemp.jailCanMove.money = 20+hrand(3)*10;
			if (sti(colonies[FindColony(npchar.city)].jail))
			{
				dialog.text = "글쎄, 거절할 이유는 없겠군. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.money))+" - 그리고 감옥을 떠날 때까지는 복도를 자유롭게 돌아다니고 죄수들과 대화도 할 수 있습니다.";
				if (PCharDublonsTotal() >= sti(sti(pchar.questTemp.jailCanMove.money)))
				{
					link.l1 = "동의하네, 여기 네 돈이야!";
					link.l1.go = "ForGoodMove_agree";
				}
				link.l2 = "그건 안 돼. 복도에서 아무렇게나 돌아다니기엔 너무 많아.";
				link.l2.go = "exit";
			}
			else
			{
				dialog.text = RandPhraseSimple("아니, 규정상 이건 엄격히 금지되어 있다. 뭐? 여기가 서커스인 줄 아나? 꺼져, 내 업무 방해하지 말고.","내 감옥 안을 낯선 이들이 돌아다니게 둘 수는 없어. 제발, 그만 귀찮게 해!");
				link.l1 = "좋아, 네 말대로 하자...";
				link.l1.go = "exit";
			}
		break;
		
        case "ForGoodMove_agree":
            dialog.text = "좋아, 이제 탐험을 시작해도 된다...";
			link.l1 = "감사합니다, 장교님.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.money)));
		break;
		
        case "KnowAboutPrisoner":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "For murder."; break;
				case "1": sTemp = "He is accused of piracy."; break;
				case "2": sTemp = "For banditry and robbery."; break;
				case "3": sTemp = "He was caught stealing."; break;
				case "4": sTemp = "For petty theft."; break;
				case "5": sTemp = "For cheating."; break;
				case "6": sTemp = "For vagrancy and begging."; break;
			}
			dialog.text = sTemp;
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				link.l1 = "알겠소... 그 죄수를 내게 넘기시오, 장교. 내가 직접 이 죄수의 운명을 결정하겠소.";
				link.l1.go = "KnowAboutPrisoner_gengov";
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				link.l1 = "알겠소... 장교, 저 죄수를 내게 넘기시오. 이 죄수의 운명은 내가 직접 결정하겠소.";
				link.l1.go = "KnowAboutPrisoner_admiral";
				DeleteAttribute(pchar, "questTemp.jailCanMove.City");
				break;
			}
			link.l1 = "알겠소... 그런데 몸값을 치르거나, 보석을 내거나... 아니면 다른 방법으로 그를 풀어줄 수 있는 가능성은 없소?";
			link.l1.go = "KnowAboutPrisoner_" + pchar.questTemp.jailCanMove.ownerPrison;
			DeleteAttribute(pchar, "questTemp.jailCanMove.City");
		break;
		
        case "KnowAboutPrisoner_0":
			dialog.text = "당연히 아니지. 그 교수대에 오를 놈은 곧장 지옥으로 갈 거야. 총독께서 그 사건을 특별히 관리하고 계시거든!";
			link.l1 = "헤, 알겠군...";
			link.l1.go = "notFree_exit";
		break;	
		
		case "KnowAboutPrisoner_1":
			dialog.text = "농담하는 거야? 그 자식은 벌써 교수대에 갔겠지! 곧 밧줄이랑 결혼할 거라고. 그냥 잊어버려.";
			link.l1 = "알겠어. 그리고 벌써 잊어버렸지...";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_2":
			dialog.text = "그럴 생각 없어. 그 자는 우리 마을 사람들에게 많은 문제를 일으켰거든. 그러니 그 일은 부탁하지 마.";
			link.l1 = "흠, 알겠군.";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_3":
			dialog.text = "아마 아닐 거야. 그는 도둑이니까, 도둑은 감옥에 있어야 해.";
			link.l1 = "오! 잘 말했다, 부관!";
			link.l1.go = "notFree_exit";
		break;
		
        case "KnowAboutPrisoner_4":
			dialog.text = "잘 모르겠어. 그는 하찮은 물건만 훔쳤어. 풀어줄 수는 없지만, 감옥에서 썩게 두는 것도 분명 옳지 않아.";
			link.l1 = "좋아, 그럼 그를 내게 넘기시오, 중위. 내가 보석금을 내겠소—물론 합당한 금액으로.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_5":
			dialog.text = "풀어준다고? 그럴 것 같군. 내 생각엔 저 하찮은 범죄자를 여기 붙잡아 둘 이유가 없어.";
			link.l1 = "그렇다면 그를 내게 넘기시오, 중위. 내가 보석금을 내겠소. 물론 합당한 금액으로 말이오.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
		case "KnowAboutPrisoner_6":
			dialog.text = "흠... 네 말에도 일리가 있군. 이 떠돌이놈은 여기 있을 자격이 없어. 더럽고 병만 퍼뜨리고 있으니...";
			link.l1 = "그렇다면 그를 내게 넘기시오, 중위. 내가 보석금을 내겠소. 물론 합당한 금액으로 말이오.";
			link.l1.go = "KnowAboutPrisoner_free";
		break;
		
        case "KnowAboutPrisoner_free":
			pchar.questTemp.jailCanMove.ownerPrison.money = 50+hrand(10)*10;
			dialog.text = "좋아, 거래 성사다. "+FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money))+" 바로 돈을 내면, 지금 당장 그를 데려가도 된다.";
			if (PCharDublonsTotal() >= sti(pchar.questTemp.jailCanMove.ownerPrison.money))
			{
				link.l1 = LinkRandPhrase("훌륭하군! 나도 동의해!","거래 성사요, 장교!","훌륭하오. 그 기여금을 지불할 준비가 되었소.");
				link.l1.go = "KnowAboutPrisoner_agree";
			}
			link.l2 = "아니, 그건 너무 비싸군. 나는 사양하겠어.";
			link.l2.go = "KnowAboutPrisoner_exit";
		break;
		
        case "KnowAboutPrisoner_agree":
			dialog.text = "좋아, 그의 감방으로 가도 된다. 그 부랑자도 데려가라.";
			link.l1 = "고맙다.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			RemoveDublonsFromPCharTotal(sti(pchar.questTemp.jailCanMove.ownerPrison.money));
			Log_Info("You have given " + FindRussianDublonString(sti(pchar.questTemp.jailCanMove.ownerPrison.money)) + "");
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		
        case "KnowAboutPrisoner_exit":
			dialog.text = "글쎄, 선택은 네가 하는 거야. 다시 기회는 안 줄 거다...";
			link.l1 = "그럴 필요 없어.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_expansive";
		break;
		
        case "notFree_exit":
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId);
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_notFree";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		// belamour legendary edition -->
		// генерал-губернатор
		case "KnowAboutPrisoner_gengov":
			dialog.text = "물론입니다, 각하께서 원하신다면 이 불운한 자를 데려가십시오. 다만 조심하십시오, 아직도 범죄자이니...";
			link.l1 = "좋군. 걱정 마, 중위. 내가 뭘 하는지 잘 알고 있어.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// вице-адмирал
		case "KnowAboutPrisoner_admiral":
			dialog.text = "음... 나도 잘 모르겠군... 사실 죄수들을 그냥 풀어줄 수는 없어. 하지만 자네는 아직 부제독이니, 이 범죄자를 데려갈 권리는 있을 거야.";
			link.l1 = "좋군. 걱정 마, 중위. 내가 뭘 하는지 잘 알고 있어.";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
			sld = characterFromId(pchar.questTemp.jailCanMove.prisonerId)
			LAi_CharacterEnableDialog(sld);
			sld.dialog.currentnode = "ToPrisonHead_canMove";
		break;
		// <-- legendary edition
		//---------------- Протектор ------------------
        case "First_protector":
			// генерал-губернатор
			if(CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE)
			{
				dialog.text = "총독 나리, 각하! 들어오시지요. 하지만 조심하십시오. 이 범죄자들에게서 무슨 일이든 벌어질 수 있습니다...";
				link.l1 = "걱정 마, 병사야. 무슨 일 생기면 내가 처리할 테니까.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			// вице-адмирал
			if(isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation))
			{
				dialog.text = "안녕하십니까, 부제독님! 저는 여기서 근무 중입니다. 아무도 허가 없이 드나들지 못하게 감시하고 있지요. 하지만 부제독님께서는 물론 자유롭게 통과하실 수 있습니다.";
				link.l1 = "그래, 그거 참 멋지군.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First_protector";
				break;
			}
			if (sti(pchar.questTemp.jailCanMove))
			{
				dialog.text = RandPhraseSimple("지나가도 된다, 감시관이 허락했으니.","감옥장으로부터 명령을 받았습니다. 자유롭게 지나가도 됩니다.");
				link.l1 = "아주 좋군.";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison.money");
			}
			else
			{
				dialog.text = RandPhraseSimple("감옥장 허가 없이는 더 이상 들어갈 수 없다!","나는 교도소장에게만 대답한다! 그의 허락 없이 더 나아가려 하면, 끝장날 줄 알아!");
				link.l1 = RandPhraseSimple("알겠어","Alright")+", 병사.";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "First_protector";
		break;
		//---------------- Солдаты ------------------
        case "First_soldier":
            dialog.text = RandPhraseSimple("나는 근무 중이니, 귀찮게 하지 마.","가시오, 나는 너와 말하면 안 돼.");
			link.l1 = "좋아, 병사.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_soldier";
		break;
		//---------------- Заключенные ------------------
        case "First_prisoner": 
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) == RELATION_ENEMY)
			{
				dialog.text = LinkRandPhrase("호호, 정말 멋진 때 아니냐!","베어버려라, "+GetSexPhrase("동료","아가씨")+", 컷!!!","이런 젠장! 내 간수의 시체를 다시 볼 거란 희망은 완전히 버렸었는데!");
				link.l1 = RandPhraseSimple("헤헷!","아르르!");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.DeliverToBander")) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("잠깐만, "+GetSexPhrase("동료","아가씨")+"!! 날 풀어 줘!","들어봐, "+GetSexPhrase("동료","아가씨")+", 자비롭게 감방을 열어 주십시오.");
					link.l1 = "무슨 이유로?";
					link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
				}
			}
			else
			{
				dialog.text = LinkRandPhrase("나는 강도죄로 몰렸지만, 난 결백해!","으르렁, 잘 차려입은 잡놈아... 내 감방에 좀 앉아보고 싶으냐?! 크헤헤헤...","나는 죄가 없어!");
				link.l1 = RandPhraseSimple("닥쳐!","난 너 따위는 신경도 안 써...");
				link.l1.go = "NoMoreTalkExit";
				if (rand(10) > 6 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !CheckAttribute(pchar, "GenQuest.PrisonQuestLock") && !CheckAttribute(pchar, "quest.GivePrisonFree_Over") && !CheckAttribute(pchar, "quest.GivePrisonFree") && !CheckAttribute(pchar, "quest.DeliverToBander") && !sti(colonies[FindColony(npchar.city)].HeroOwn)) // Addon 2016-1 Jason пиратская линейка
				{
					dialog.text = RandPhraseSimple("잠깐, "+GetSexPhrase("동료","아가씨")+", 그렇게 서두르지 말고 좀 천천히 가!","서두르지 마, "+GetSexPhrase("동료","아가씨")+", 이야기하자.");
					link.l1 = "무슨 이유로?";
					if (rand(1))
					{
						link.l1.go = "Prisoner_1"; // на квест освобождения заключённого
					}
					else
					{
						link.l1.go = "Deliver_1"; // на квест передачу весточки
					}
				}
			}
		break;
		// -------------------- освобождение заключённого --------------------
        case "Prisoner_1":
            dialog.text = "내 말 좀 들어봐, 친구. 내가 못생겼다고 생각하지 마. 그냥 여기서 나가고 싶을 뿐이야...";
			link.l1 = "뭐?!";
			link.l1.go = "Prisoner_2";
			GetChestPlaceName();
			pchar.questTemp.jailCanMove.prisonerId = npchar.id; //запомним Id
			pchar.questTemp.jailCanMove.IsTrue = rand(4); //вид клада
			pchar.questTemp.jailCanMove.Item1 = GenQuestPrison_GenerateArtefact();
			pchar.questTemp.jailCanMove.Item2 = GenQuestPrison_GenerateBlade();
			pchar.questTemp.jailCanMove.Name = GetFullName(npchar); //имя перца
			npchar.nation = PIRATE;
		break;
        case "Prisoner_2":
            dialog.text = "네가 들은 대로야! 나 좀 도와주면 반드시 보답할게...";
			link.l1 = "이거 흥미로운데. 넌 누구고, 나한테 뭘 줄 수 있지?";
			link.l1.go = "Prisoner_3";
		break;
        case "Prisoner_3":
            dialog.text = "내 이름은 "+GetFullName(npchar)+". 내가 안전한 곳에 숨겨둔 물건들이 좀 있어. 나만 여기서 데리고 나가서 \n 나를 데려다 줘. "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Acc")+". 저기, 동굴에 내가 보물을 숨겨뒀지. 우리가 가져가서 나누자!";
			link.l1 = "네 보물창고에 뭐가 있는데? 그리고 네가 진실을 말하는지 내가 어떻게 알 수 있지?";
			link.l1.go = "Prisoner_4";
		break;
        case "Prisoner_4":
            dialog.text = "맹세코 진실만 말하고 있어! 그 은닉처 말인데, 보물도 있고 돈도 있어...";
			link.l1 = "아니, 이봐. 수상한 보물 때문에 내 목숨을 걸 순 없어. 미안하지만...";
			link.l1.go = "Prisoner_5";
			if (GetNationRelation2MainCharacter(sti(npchar.nation)) != RELATION_ENEMY)
			{			
				// belamour legendary edition адмирал и губернатор может договориться без денег
				bool bAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && npchar.nation == sti(Items[sti(pchar.EquipedPatentId)].Nation);
				bool bGenGov = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == GetBaseHeroNation());
				if(!bAdmiral && !bGenGov)
				{
				link.l2 = "음, 위험을 감수할 만한 가치가 있을지도 모르지... 내 제안은 이렇다네: 내가 감옥의 경비병들을 처리하고 자네를 내 배로 데려가겠네. 모든 일이 잘 풀리면, 우리가 그로토에 도착할 때까지 항상 내 곁에 있어 주었으면 하네\n  "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". 거래지?"; // belamour gen
				link.l2.go = "Prisoner_agree"; //силовой способ вызволения
				}
				link.l3 = "좋아, 도와줄게. 감옥장에게 이야기해 보겠다. 어쩌면 너를 보석으로 풀어줄 수 있을지도 몰라.";
				link.l3.go = "ToPrisonHead_agree"; //мирный способ вызволения
			}
			else
			{
				link.l2 = "좋아, 믿고 네 감방을 열어주겠다. 우리가 그로토에 도착할 때까지 항상 내 곁에 있어라. "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc")+". 거래지?";
				link.l2.go = "Prisoner_agree_3"; //силовой способ вызволения, когда тюремщики убиты
			}
		break;
        case "Prisoner_5":
            dialog.text = RandPhraseSimple("이런 젠장, 이 망할 놈아!","빌어먹을, 네가 나를 털었잖아, 이 쓰레기놈...");
			link.l1 = RandPhraseSimple("당신에게도 행운이 함께하길. 잘 가시오...","달은 개들이 짖는다고 신경 쓰지 않지...");
			link.l1.go = "NoMoreTalkExit";
		break;
        case "Prisoner_agree":
            dialog.text = "좋아. 내가 가릴 처지가 아니지.";
			link.l1 = "좋아. 이제 네 자물쇠를 부숴서 널 꺼내줄게, 그리고 우리가 이곳을 빠져나가자. 준비됐지?";
			link.l1.go = "Prisoner_agree_1";
		break;
        case "Prisoner_agree_1":
            dialog.text = "그래, "+GetSexPhrase("동료","아가씨")+", 준비됐어!";
			link.l1 = "그럼 시작하자!";
			link.l1.go = "Prisoner_agree_2";
		break;
        case "Prisoner_agree_2":
			string slai_group = GetNationNameByType(sti(npchar.nation))  + "_citizens";
			LAi_group_AttackGroup(slai_group, LAI_GROUP_PLAYER);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;

        case "Prisoner_agree_3":
            dialog.text = "좋아. 내가 가릴 처지가 아니지.";
			link.l1 = "좋아. 최대한 빨리 따라와. 아직 내 배로 가야 하니까. 지체하지 마!";
			link.l1.go = "Prisoner_agree_4";
		break;
        case "Prisoner_agree_4":
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_agree":
            dialog.text = "글쎄, 해보든지. 우리가 버텨내길 바라! 하지만 시간 낭비하지 마라 - 며칠 후면 난 여기서 나갈 거니까...";
			link.l1 = "여기서 기다려, 내가 다 준비할게.";
			link.l1.go = "NoMoreTalkExit";
			pchar.questTemp.jailCanMove.City = npchar.City; //город
			pchar.questTemp.jailCanMove.ownerPrison = rand(6); //характер преступления
			SetTimerCondition("GivePrisonFree_Over", 0, 0, 2, false);
			AddQuestRecord("GivePrisonFree", "5");
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
		break;

        case "ToPrisonHead_canMove":
            dialog.text = "그래, 뭐라고 할래, "+GetSexPhrase("동료","아가씨")+"?";
			link.l1 = "모든 준비가 끝났으니, 이제 여기서 데려갈 수 있습니다.";
			link.l1.go = "ToPrisonHead_canMove_1";
		break;
        case "ToPrisonHead_canMove_1":
            dialog.text = "그럼 여기서 나가자! 오, 주님, 얼마나 기쁜지!";
			link.l1 = "정리하자. 우리가 그 동굴에 도착할 때까지 항상 내 곁에 있어 줘. "+XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Dat")+", 한 걸음 이상 뒤처지지는 않을 거야. 만일을 위해서지. 동의하나?";
			link.l1.go = "ToPrisonHead_canMove_2";
		break;
        case "ToPrisonHead_canMove_2":
            dialog.text = "물론이오, 동의하지! 선택할 처지가 아니니 더더욱 그렇지.";
			link.l1 = "그럼 이제 자유다.";
			link.l1.go = "ToPrisonHead_canMove_exit";
		break;
        case "ToPrisonHead_canMove_exit":
			pchar.quest.GivePrisonFree_Over.over = "yes";
			ReOpenQuestHeader("GivePrisonFree");
			AddQuestRecord("GivePrisonFree", "1");
            AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
            AddQuestUserData("GivePrisonFree", "sIsland", XI_ConvertString(pchar.questTemp.jailCanMove.islandId+"Voc"));
			pchar.quest.GivePrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.GivePrisonFree_Death.win_condition.l1.character = npchar.id;
			pchar.quest.GivePrisonFree_Death.win_condition = "GivePrisonFree_Death";
			Pchar.quest.GivePrisonFree.win_condition.l1 = "location";
			Pchar.quest.GivePrisonFree.win_condition.l1.location = pchar.questTemp.jailCanMove.placeId;
			Pchar.quest.GivePrisonFree.win_condition = "GivePrisonFree";			
			DeleteAttribute(npchar, "LifeDay");
			GiveItem2Character(npchar, "unarmed");
			EquipCharacterbyItem(npchar, "unarmed");
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_group_Register("DeliveQuest_Prison");
			LAi_group_SetRelation("DeliveQuest_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			//LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "DeliveQuest_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "DeliveQuest_Prison");
			LAi_ActorFollowEverywhere(npchar, "", -1);
			DialogExit();
		break;

        case "ToPrisonHead_notFree":
			switch (pchar.questTemp.jailCanMove.ownerPrison)
			{
				case "0": sTemp = "murder"; break;
				case "1": sTemp = "piracy"; break;
				case "2": sTemp = "brigandry"; break;
				case "3": sTemp = "thievery"; break;
			}
            dialog.text = "그래, 뭐라고 할 텐가, "+GetSexPhrase("동료","아가씨")+"?";
			link.l1 = "당신의 석방을 주선하지 못했소. 당신은 다음과 같은 혐의로 기소되었소 "+sTemp+", 그래서 보석으로 풀려날 수 없습니다.";
			link.l1.go = "ToPrisonHead_notFree_1";
			DeleteAttribute(pchar, "questTemp.jailCanMove.ownerPrison");
		break;
		
        case "ToPrisonHead_notFree_1":
            dialog.text = "하지만 나는 누명을 썼어! 이런, 악마 같으니! 이제 어쩌지? 여기서 산 채로 썩게 생겼잖아!";
			link.l1 = "미안하다, 친구야, 내가 해줄 수 있는 게 없어.";
			link.l1.go = "ToPrisonHead_notFree_2";
			link.l2 = "이제 남은 방법은 하나뿐이야 - 힘으로 널 구하는 거지. 지금 네 자물쇠를 부숴서 널 꺼내줄게, 그리고 우리가 뚫고 나가자. 준비됐어?";
			link.l2.go = "Prisoner_agree_1";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		
        case "ToPrisonHead_notFree_2":
            dialog.text = RandPhraseSimple("저주받을 놈!","젠장, 네가 날 털었잖아, 이 년아...");
			link.l1 = "당신에게도 행운이 함께하길. 안녕히...";
			link.l1.go = "NoMoreTalkExit";
			AddQuestRecord("GivePrisonFree", "7");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
		break;

        case "ToPrisonHead_expansive":
			dialog.text = "그래서, 좋은 소식이라도 있나, "+GetSexPhrase("동료","아가씨")+"?";
			link.l1 = "네 보석금이 너무 비싸서, 그런 돈은 없어. 더 이상 도와줄 수 없겠다.";
			link.l1.go = "ToPrisonHead_notFree_2";
			pchar.quest.GivePrisonFree_Over.over = "yes";
		break;
		//==> в месте, где клад припрятан
        case "PrisonerInPlace":
			switch (sti(pchar.questTemp.jailCanMove.IsTrue))
			{
				case 0:
					dialog.text = "들어봐, 내가 다 확인해 봤는데 보물은 없었어. 이렇게 되어 아쉽군. 누가 우리보다 먼저 파냈나 봐.";
					link.l1 = "그게 어떻게 된 일이냐?!";
					link.l1.go = "PrisonerInPlace_1";
				break;
				case 1:
					dialog.text = "찾았다! 보물은 내가 두었던 그 자리에 아직 있다.";
					link.l1 = "훌륭해. 그럼, 우리 흩어지자고?";
					link.l1.go = "Node_1";
				break;
				case 2:
					dialog.text = "자, 여기 내 숨겨둔 거야. 많진 않지만 내가 가진 전부야. 약속대로, 절반은 네 거다.";
					link.l1 = "그래, 보물은 정말 보잘것없지. 그래도 없는 것보단 낫잖아.";
					link.l1.go = "Node_2";
				break;
				case 3:
					dialog.text = "선장님, 죄송하지만... 보물은 없습니다.";
					link.l1 = "뭐라고?! 이 사기꾼 녀석! 내가 너를 그 섬까지 데려다줬는데, 그 대가가 이거냐? 가만두지 않겠다!";
					link.l1.go = "Node_3";
				break;
				case 4:
                    ok = GetCharacterItem(pchar, "map_full") == 0 && GetCharacterItem(PChar, "map_part2") == 0;
                    if(GetCharacterItem(PChar, "map_part1") > 0 && !ok) // Первая половинка есть, но вторую дать нельзя
                    {
                        dialog.text = "들어봐, 내가 다 확인해 봤는데 보물은 못 찾았어. 이렇게 되어 아쉽군. 누군가 우리보다 먼저 파냈나 봐.";
                        link.l1 = "그게 어떻게 된 일이냐?!";
                        link.l1.go = "PrisonerInPlace_1";
                    }
                    else
                    {
                        dialog.text = "젠장... 어떻게 그럴 수가 있지? 그럴 리가 없어!";
                        link.l1 = "무슨 일이야, 이봐? 보물은 어디 있어? 설마 보물이 없다는 건 아니겠지!";
                        link.l1.go = "Node_4";
                    }
				break;
			}
		break;
			
		case "Node_1":
			dialog.text = "물론이지, 약속대로야. 보물의 절반은 네 거다.";
			link.l1 = "성스러운 주님, 정말 귀한 물건이 잔뜩 있군!";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			TakeNItems(pchar, "icollection", 1+hrand(1));
			TakeNItems(pchar, "chest", 4+hrand(4));
			TakeNItems(pchar, "jewelry1", 70+rand(15));
			TakeNItems(pchar, "jewelry2", 50+rand(15));
			TakeNItems(pchar, "jewelry3", 60+rand(15));
			TakeNItems(pchar, "jewelry4", 40+rand(10));
			TakeNItems(pchar, "jewelry5", 10+rand(10));
			TakeNItems(pchar, "jewelry46", 60+rand(20));
			TakeNItems(pchar, "jewelry47", 40+rand(15));
			TakeNItems(pchar, "jewelry40", 60+rand(20));
			AddQuestRecord("GivePrisonFree", "3_1");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_2":
			dialog.text = "선장님, 다른 것들 사이에 그 인디언 물건도 있습니다. 몫 외에 그것도 가져가셔도 됩니다.";
			link.l1 = "그래도 네 석방을 위해 쓸 만한 게 있군! 내놔.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received your share of the treasure");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item1;
			TakeNItems(pchar, sTemp, 1);
			TakeNItems(pchar, "jewelry5", 40+rand(10));
			TakeNItems(pchar, "jewelry6", 20+rand(20));
			TakeNItems(pchar, "jewelry17", 80+rand(20));
			TakeNItems(pchar, "jewelry13", 10+rand(10));
			TakeNItems(pchar, "jewelry10", 20+rand(20));
			TakeNItems(pchar, "jewelry12", 50+rand(20));
			TakeNItems(pchar, "jewelry11", rand(2)+1);
			AddQuestRecord("GivePrisonFree", "3_2");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_3":
			dialog.text = "잠깐만요, 선장님, 흥분하지 마시고 제 말 좀 들어보세요. 저도 선장이랑 똑같은 선원이었습니다. 억울하게 감옥에 갇힌 거예요, 맹세합니다. 선장님이 제 유일한 탈출 기회였고, 그래서 보물에 대해 거짓말할 수밖에 없었습니다.\n보물은 없지만, 거기에 좋은 물건 하나 숨겨뒀어요. 그걸 가져가시고, 저를 조용히 보내주세요. 언젠가 전투에서 그게 선장님을 살려줄지도 모릅니다.";
			link.l1 = "좋아, 어차피 너한테 큰 기대는 안 했어. 다행히 난 원한을 품는 성격은 아니거든.";
			link.l1.go = "PrisonerInPlace_3";
			Log_Info("You have received equipment");
			PlaySound("interface\important_item.wav");
			sTemp = pchar.questTemp.jailCanMove.Item2;
			TakeNItems(pchar, sTemp, 1);
			AddQuestRecord("GivePrisonFree", "3_3");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
		case "Node_4":
			dialog.text = "안 돼!!! 여기 없어! 젠장할 쪼가리... 선장님, 분명히 여기서 찾을 줄 알았는데! 하지만 내가 착각했던 모양이오! 그 종이 쪼가리에 뭔가 정말 애매하게 적혀 있었어...";
			link.l1 = "어이쿠... 자네, 정말 큰일에 휘말렸군. 그래도 자네 설명은 들어보고 싶어.";
			link.l1.go = "Node_4_1";
		break;
			
		case "Node_4_1":
			dialog.text = "나는 지도 조각을 가지고 있었어. 진짜 지도였다고, 맹세해! 하지만 그게 어느 섬을 가리키는지 알아내기가 정말 어렵더라고... 난 여기라고 생각했지... 하지만 지금 보시다시피, 내가 틀렸어.";
			link.l1 = "무슨 종이쪼가리야? 당장 내놔!";
			link.l1.go = "Node_4_2";
		break;
			
		case "Node_4_2":
			AddMapPart();
			dialog.text = "물론이오, 가져가시오. 선장님, 제발 저를 풀어주십시오... 부탁드립니다. 나는 정말로 보물이 거기 있다고 믿었소. 어쩌면 선장님이 그 위치를 알아내서 직접 차지할 수도 있겠지요. 간청하오.";
			link.l1 = "그렇군... 확실히 저 조각만으론 아무것도 알 수 없지. 지도 뒷부분이 필요해. 좋아, 이제 꺼져. 이제 보니 네 잘못이 아니었구나.";
			link.l1.go = "PrisonerInPlace_4";
		break;
			
		case "PrisonerInPlace_1":
			dialog.text = "아주 간단하지, "+GetSexPhrase("동료","아가씨")+". 인생이란 다 그런 거지.\n자, 너도 여기 왔으니, 원하면 남아서 더 찾아봐라. 난 이제 가야겠다!\n잘 있어, "+GetSexPhrase("내 친구","아가씨")+", 내 목숨을 구해줘서 고마워. 너를 평생 잊지 않을 거야!";
			link.l1 = "이 악당아! 네가 그냥 도망칠 수 있을 거라 생각해?! 이봐! 거기 서, 겁쟁이!";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "4");
			AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
			
        case "PrisonerInPlace_2":
			LAi_group_Delete("EnemyFight");
			DeleteAttribute(pchar, "questTemp.jailCanMove.islandId");	
			DeleteAttribute(pchar, "questTemp.jailCanMove.placeId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.prisonerId");
			DeleteAttribute(pchar, "questTemp.jailCanMove.IsTrue");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Sum");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Name");
			chrDisableReloadToLocation = false;
			LAi_LocationDisableMonstersGen(pchar.location, false);
			npchar.lifeDay = 0;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_SetActorType(npchar);
            LAi_ActorRunToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", -1);
			DialogExit();

            Pchar.quest.DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
            Pchar.quest.DeletePrisonGroup.win_condition.l1.location = pchar.location;
            Pchar.quest.DeletePrisonGroup.win_condition = "DeletePrisonGroup";
		break;
		
        case "PrisonerInPlace_3":
			dialog.text = "여기 있습니다. 감사합니다!";
			link.l1 = "잘 가...";
			link.l1.go = "PrisonerInPlace_2";
		break;
		
        case "PrisonerInPlace_4":
			dialog.text = "감사합니다, 선장님! 남은 평생 당신을 위해 기도하겠습니다!";
			link.l1 = "아, 닥쳐! 평안히 가라...";
			link.l1.go = "PrisonerInPlace_2";
			AddQuestRecord("GivePrisonFree", "3_4");
            AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Name);
			AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("GivePrisonFree");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item1");
			DeleteAttribute(pchar, "questTemp.jailCanMove.Item2");
		break;
        
		// -------------------- освобождение заключённого --------------------
		// ------------------------ передать маляву --------------------------
        case "Deliver_1":
			dialog.text = "나는 불린다 "+GetFullName(npchar)+". 당신에게 부탁이 있어, 헤헤...";
			link.l1 = "무슨 일이야?";
			link.l1.go = "Deliver_2";
		break;
        case "Deliver_2":
			dialog.text = "감옥 밖으로 편지를 보내야 해. 해줄 수 있겠어?";
			link.l1 = "그럼 내게 무슨 이득이 있는데?";
			link.l1.go = "Deliver_3";
		break;
        case "Deliver_3":
			dialog.text = "녀석들이 실망시키지 않을 거야, 내가 약속하지... 그래서? 할 거야?";
			link.l1 = "아니, 나는 관심 없어.";
			link.l1.go = "Prisoner_5";
			link.l2 = "글쎄, 내가 너무 힘들지 않다면 해줄 수 있지.";
			link.l2.go = "Deliver_agree";
		break;
        case "Deliver_agree":
			dialog.text = "좋아. 이제 내 말 잘 들어. 내 친구 두 명이 습격 때 잡히지 않으려고 한 집에서 내 소식을 기다리고 있어. 그런데 정확히 어느 집인지는 나도 몰라. 네가 직접 찾아봐야 해.";
			link.l1 = "수색이라니, 그게 무슨 말이야?";
			link.l1.go = "Deliver_4";
		break;
        case "Deliver_4":
			dialog.text = "수색이란 말 그대로 수색이지. 마을을 돌아다니고, 집들을 들여다보게 될 거야. 제대로 된 장소에 도착하면, 대화 없이 그냥 나올 수 없을 거다. 하지만 명심해, 나 같으면 거기서 이틀 이상은 머무르지 않을 거야. 그러니 지체하지 마.";
			link.l1 = "알겠소. 그럼, 서신을 내놓으시오.";
			link.l1.go = "Deliver_5";
		break;
        case "Deliver_5":
			pchar.questTemp.jailCanMove.Deliver.locationId = GetBanderLocation(npchar); //Id коммона
			if (pchar.questTemp.jailCanMove.Deliver.locationId == "none")
			{
				dialog.text = "흠, 있잖아, 난 그냥 네가 마음에 안 들어. 생각이 바뀌었어. 따라와, 거기서 멍하니 서 있지 말고!";
				link.l1 = "너 좀 봐라! 뭐, 네가 원한다면...";
				link.l1.go = "NoMoreTalkExit";
				DeleteAttribute(pchar, "questTemp.jailCanMove.Deliver");
			}
			else
			{
				dialog.text = "여기 있습니다. 감사합니다. "+GetSexPhrase("동료","아가씨")+"!";
				link.l1 = "전혀 아니오.";
				link.l1.go = "NoMoreTalkExit";
				GiveItem2Character(Pchar, "Malyava");
				pchar.questTemp.jailCanMove.Deliver.Id = npchar.id; //Id зэка
				pchar.questTemp.jailCanMove.Deliver.name = GetFullName(npchar); //имя зэка
				pchar.questTemp.jailCanMove.Deliver.City = npchar.city; //город (Id колонии)
				pchar.questTemp.jailCanMove.Deliver.good = rand(3); //опрокинут или нет
				pchar.questTemp.jailCanMove.Deliver.price = rand(6)*500+500; //цена услуги
				pchar.quest.DeliverToBander.win_condition.l1 = "location";
				pchar.quest.DeliverToBander.win_condition.l1.location = pchar.questTemp.jailCanMove.Deliver.locationId;
				pchar.quest.DeliverToBander.win_condition = "DeliverToBander";
				pchar.quest.DeliverToBander.again = true; 
				SetTimerCondition("DeliverToBander_over", 0, 0, 2, false);
				ReOpenQuestHeader("GivePrisonFree");
				AddQuestRecord("GivePrisonFree", "8");
				AddQuestUserData("GivePrisonFree", "sSex", GetSexPhrase("",""));
				AddQuestUserData("GivePrisonFree", "sCity", XI_ConvertString("Colony"+npchar.city+"Gen"));
				AddQuestUserData("GivePrisonFree", "sName", pchar.questTemp.jailCanMove.Deliver.name);
			}
		break;
		
		// Warship, 16.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "그래, 그는 밀수 혐의로 체포됐지. 그런데 왜 그 교수대에 오를 놈을 신경 쓰는 거야, "+GetAddress_Form(NPChar)+"?";
			link.l1 = "그의 패거리가 그의 탈출을 꾸미고, 더러운 짓거리를 계속할 계획이야.";
			link.l1.go = "JusticeOnSale_2";
			link.l2 = "그가 죄가 없었다고 들었어.";
			link.l2.go = "JusticeOnSale_3";
			
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");
		break;
		
		case "JusticeOnSale_2":
			dialog.text = "총독에게 반드시 알려야 합니다, "+GetAddress_Form(NPChar)+", 이 악당들은 모두 잡혀야 해!";
			link.l1 = "그렇게 하겠다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First_officer";
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "들어봐, "+GetFullName(PChar)+", 그 남자는 금지된 물건을 마을 한복판에서 팔려다가 붙잡혔소! 그런 그가 무죄라고 주장할 수 있겠소?";
			link.l1 = "그 비난이 근거 없고 아무런 증거도 없다던데, 맞습니까? 억울한 사람을 그냥 잡아둘 수는 없지요.";
			link.l1.go = "JusticeOnSale_4";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "우리에겐 증인도 물건도 없지만, 그게 뭐가 달라지진 않소, 선장님 "+GetFullName(PChar)+"! 저 자는 분명히 죄가 있어 - 불법 거래뿐만 아니라 다른 죄도 있을지 몰라. 어쨌든, 그 죄수에게 왜 그렇게 신경 쓰는 거지?";
			link.l1 = "혹시 내 말이 그 불운한 죄수의 보석 보증이 될 수 있을까?";
			link.l1.go = "JusticeOnSale_5_WithoutMoney";
			
			if(sti(PChar.money) >= 5000)
			{
				link.l2 = "이 5000페소가 그 불운한 죄수의 보석금으로 쓰일 수 있겠소?";
				link.l2.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5_WithoutMoney":
			if(GetCharacterSkill(PChar, SKILL_LEADERSHIP) > hrand(100) || sti(PChar.money) < 5000)
			{
				dialog.text = "좋아, "+GetAddress_Form(NPChar)+", 저 악당을 데리고 내가 마음을 바꾸기 전에 당장 나가.";
				link.l1 = "정의가 승리하는 걸 보니 정말 기쁘지 않나?";
				link.l1.go = "JusticeOnSale_6";
			}
			else
			{
				dialog.text = "아니, "+GetAddress_Form(NPChar)+", 그건 안 되겠군.";
				link.l1 = "그렇다면, 이 5,000페소가 좀 더 설득력 있는 제안이 될 수 있겠소?";
				link.l1.go = "JusticeOnSale_5";
			}
		break;
		
		case "JusticeOnSale_5":
			dialog.text = "좋아, "+GetAddress_Form(NPChar)+", 저 악당 데리고 어서 가. 내 마음이 바뀌기 전에.";
			link.l1 = "정의가 승리하는 걸 보니 기분 좋지 않나?";
			link.l1.go = "JusticeOnSale_6";
			AddMoneyToCharacter(PChar, -5000);
			PChar.GenQuest.JusticeOnSale.PrisonMoney = true;
		break;
		
		case "JusticeOnSale_6":
			DialogExit();
			sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_Smuggler", "mercen_"+(rand(9)+1), "man", "man", sti(PChar.rank)+5, PIRATE, -1, true, "marginal"));
			SetFantomParamFromRank(sld, sti(PChar.rank)+5, true);
			sld.name = PChar.GenQuest.JusticeOnSale.SmugglerName;
			sld.lastName = "";
			sld.dialog.filename = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "First time";
			sld.greeting = "Enc_Raiders"; 
			AddPassenger(PChar, sld, false);
			SetCharacterRemovable(sld, false);
			PChar.GenQuest.JusticeOnSale.SmugglerModel = sld.model;
			DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
			sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
			sld.DisableEncounters = true;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1  = "location";
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
			PChar.Quest.JusticeOnSale_ShoreEnterWithSmuggler.function = "JusticeOnSale_ShoreEnterWithSmuggler";
			Log_Info("Smuggler's captain on a board");
			PlaySound("interface\notebook.wav");
			LAi_Fade("", "");
			WaitDate("",0,0,0,0,60); // 280313 // лесник. прокрутка времени было так WaitDate("",0,0,0,2,5);
		break;
		// --> belamour ночной приключенец
		case "NightAdventure_CitizenHomie":
			dialog.text = "그래, 그런 난폭한 자가 있었지. 보초에게 무례하게 굴더니 결국 싸움까지 벌였어. 더 이상은 없어. 며칠 감옥에서 정신 좀 차릴 거야. 그런데 왜 그 자가 신경 쓰이오? 당신은 선장처럼 보이는데, 저 주정뱅이는 선원 같지도 않구만.";
			link.l1 = "그래, 맞아, 나는 선장이야. 사실 이 취객은 내 오랜 지인이거든. 제발 이 일은 아무한테도 말하지 마. 내가 알기로는, 그는 무기도 꺼내지 않았어. 이번 한 번만 나를 봐서 그를 풀어줄 수 있겠나?";
			link.l1.go = "NightAdventure_CitizenHomie_1";
		break;
		
		case "NightAdventure_CitizenHomie_1":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomie") // отпустил под честное слово
			{
				dialog.text = "그래, 내 좋은 친구지. 걱정 마, 아무한테도 말 안 할 테니까. 사실, 제대로 한 방도 못 먹였어, 그냥 시도만 했지. 그래서 감옥에 들어간 거야. 네가 부탁하니, 너를 존중해서 그를 풀어주겠다. 다음엔 좀 자제하라고 경고해 줘. 아니면, 술을 좀 덜 마시게 하든가.";
				link.l1 = "감사합니다, 장교님.";
				link.l1.go = "NightAdventure_CitizenHomieOK";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderNM" || pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieSolderGM") // поговорить с солдатом
			{
				dialog.text = "그래, 좋은 친구야. 걱정 마, 아무한테도 말 안 할게. 다만, 그가 잡히기 전에 보초 얼굴을 한 대 갈겼거든. 그래서 내가 그를 풀어줄 수는 없어. 물론, 보초가 고소를 취하겠다고 하면 얘기가 달라지지. 네가 직접 가서 얘기해 봐. 오늘 그가 도시 주변을 순찰 중이야.";
				link.l1 = "아니요, 그가 경비병을 때렸다면 도와줄 수 없습니다. 며칠은 감옥에 있어야 할 겁니다. 폐를 끼쳐 죄송합니다, 경관님.";
				link.l1.go = "CitizenHomieEnd";
				link.l2 = "좋아, 내가 가서 보초와 협상해 보겠다.";
				link.l2.go = "NightAdventure_CitizenHomieSolder";
			}
			
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_CitizenHomieOfficer") // выплата офицеру
			{
				dialog.text = "그래, 좋은 친구야. 걱정 마, 아무한테도 말 안 할게. 그런데 근무 중인 군인을 공격하는 건 범죄야. 내가 한 번 봐주고 그를 풀어줄 수는 있지만, 보석금을 내야 해.";
				link.l1 = "그걸 위해 내가 얼마나 내야 하지?";
				link.l1.go = "NightAdventure_CitizenHomieOfficer";
			}
		break;
		
		case "NightAdventure_CitizenHomieOK":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
		break;
		
		case "NightAdventure_CitizenHomieEnd":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_CitizenHomieSolder":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			for(i=0; i<MAX_CHARACTERS; i++)
			{
				if(Characters[i].location != npchar.City+"_town") continue;
				if(Characters[i].chr_ai.type != "patrol") continue;
				while(SoldQty < 10) // на всякий случай, чтобы не было выхода за границы массива
				{                   // генерируется 7 солдат + 3 мушкетера
					SoldNum[SoldQty] = Characters[i].index;
					SoldQty++;
				}
			}
			iTemp = rand(SoldQty);
			pchar.GenQuest.NightAdventureSolNum = SoldNum[iTemp];
		break;
		
		case "NightAdventure_HomieToPrisoner":
			DeleteAttribute(pchar,"GenQuest.NightAdventureToPrisoner");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "*읽는다* 그러니까... 그러니까... 뭐, 보초가 불만이 없다면 나도 없다. 친구 데려가도 된다. 대신 다음엔 좀 자제하라고 경고해라. 아니면 아예 술을 덜 마시게 해.";
			link.l1 = "감사합니다, 장교님.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_CitizenHomieOfficer":
			dialog.text = "글쎄, 무기를 들지 않았으니 1,500페소만 받지.";
			link.l1 = "그렇게 많은 돈을 줄 준비는 안 됐네. 뭐, 그 녀석이 며칠만 있다 갈 거라면 별 문제 없겠지. 어쩌면 술도 좀 덜 마시겠군.";
			link.l1.go = "NightAdventure_CitizenHomieEnd";
			if(sti(pchar.money) >= 1500)
			{
				link.l2 = "좋아, 보석금을 낼 준비가 됐어.";
				link.l2.go = "NightAdventure_CitizenHomieOfficer_1";
			}
		break;
		
		case "NightAdventure_CitizenHomieOfficer_1":
			AddMoneyToCharacter(pchar, -1500);
			DeleteAttribute(pchar,"GenQuest.NightAdventureToJail");
			pchar.quest.NightAdventure_SeaExit.over = "yes";
			pchar.quest.NightAdventure_JungleExit.over = "yes";
			SetFunctionLocationCondition("NightAdventure_CitizenHomieOK", npchar.City+"_town", false);
			dialog.text = "친구를 데려가도 된다. 다음엔 좀 자제하라고 경고해라. 아니면 아예 술을 덜 마시게 해라.";
			link.l1 = "감사합니다, 장교님.";
			link.l1.go = "exit";
		break;
		// <-- ночной приключенец
		
		// --> Sinistra Путеводная звезда
		case "PZ_BasTer_ComendantDialog":
			if (CheckAttribute(pchar, "questTemp.PZ_BasTerOpozdal"))
			{
				dialog.text = "학살을 벌이기보단 이렇게 와줘서 고맙군. 요즘은 그나마 누군가 이성적으로 행동해줘서 다행이야.";
				link.l1 = "그래서, 무슨 일로 이런 관심을 받는 겁니까, 장교 나리? 내가 중국인을 찾고 있다는 사실과 관련이 있습니까?";
				link.l1.go = "PZ_BasTer_ComendantDialog_Opozdal_1";
			}
			else
			{
				dialog.text = "자진해서 우리에게 온 건 다행이군. 요즘 말썽꾼들 때문에 골치가 아팠거든.";
				link.l1 = "글쎄, 보시다시피 저는 폭력적인 사람이 아니오. 하지만... 왜 제가 여기 있는 거요, 경관님? 이미 당신 부하들에게 물어봤지만 답을 못 들었소 - 혹시 내가 이 마을에서 어떤 중국인을 찾고 있어서 그런 거요?";
				link.l1.go = "PZ_BasTer_ComendantDialog_1";
			}
			DeleteQuestCondition("PZ_BasTerPeshera");
			npchar.Dialog.Filename = "Common_Prison.c";
			npchar.Dialog.CurrentNode = "First_officer";
		break;
		// <-- Путеводная звезда
		case "Helen_meeting":
			dialog.text = "왜, 당연히 아니지! 들어오시게. 우리 감옥은 언제나 환영이네. 아, 물론 좋은 의미로 말한 거야. 그런데, 무슨 일로 오셨나?";
			link.l1 = "아, 별거 아니야, 그냥 도시를 둘러보다가 우연히 여기까지 오게 됐어.";
			link.l1.go = "exit";
			link.l2 = "사업 이야기를 좀 하고 싶었어.";
			link.l2.go = "quests";
			if (!sti(pchar.questTemp.jailCanMove))
			{
				link.l4 = "감옥 안에 들어가고 싶어.";
				link.l4.go = "ForGoodMove";		
			}
			NextDiag.TempNode = "First_officer";
		break;
	}
}

void GetChestPlaceName()
{
	string islandId;
	int iTemp = rand(3);
	switch (iTemp)
	{
		case 0: 
			pchar.questTemp.jailCanMove.islandId = "Bermudes";
			pchar.questTemp.jailCanMove.placeId = "Bermudes_Cavern";
		break;
		case 1: 
			pchar.questTemp.jailCanMove.islandId = "Caiman";
			pchar.questTemp.jailCanMove.placeId = "Caiman_Grot";
		break;
		case 2: 
			pchar.questTemp.jailCanMove.islandId = "Dominica";
			pchar.questTemp.jailCanMove.placeId = "Dominica_Grot";
		break;
		case 3: 
			pchar.questTemp.jailCanMove.islandId = "Terks";
			pchar.questTemp.jailCanMove.placeId = "Terks_Grot";
		break;
	}
}

string GetBanderLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест мэра по поиску шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.GenQuest.SeekSpy.Location && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[rand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GenQuestPrison_GenerateArtefact() // артефакты
{
	string itemID;
	switch(rand(7))
	{
		case 0:
			itemID = "indian_5";
		break;
		case 1:
			itemID = "indian_7"; 
		break;
		case 2:
			itemID = "indian_8"; 
		break;
		case 3:
			itemID = "indian_9"; 
		break;
		case 4:
			itemID = "indian_10"; 
		break;
		case 5:
			itemID = "indian_11"; 
		break;
		case 6:
			itemID = "indian_3"; 
		break;
		case 7:
			itemID = "indian_6"; 
		break;
	}
	return itemID;
}

string GenQuestPrison_GenerateBlade() // клинки и другое
{
	string itemID;
	switch(rand(8))
	{
		case 0:
			itemID = GetGeneratedItem("blade_16");
		break;
		case 1:
			itemID = GetGeneratedItem("blade_15"); 
		break;
		case 2:
			itemID = GetGeneratedItem("blade_13"); 
		break;
		case 3:
			itemID = "cirass2"; 
		break;
		case 4:
			itemID = GetGeneratedItem("blade_10"); 
		break;
		case 5:
			itemID = "spyglass3"; 
		break;
		case 6:
			itemID = "cirass6"; 
		break;
		case 7:
			itemID = "cirass7"; 
		break;
		case 8:
			itemID = "cirass1"; 
		break;	
		
	}
	return itemID;
}
