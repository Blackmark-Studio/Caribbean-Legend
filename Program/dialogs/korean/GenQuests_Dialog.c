void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	ref rItem, rChar, sld, MerPrm;
	aref arTemp1, arTemp2;
	bool bTemp;
	int iBanditsCount, i, iMoney, iNation, iTmp, iGoods, iRank, iScl;
	String sTitle, sGroup, sTemp, sText; // belamour 
	float locx, locy, locz;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "이건 버그야. 개발자들에게 어떻게, 어디서 발견했는지 알려서 연락해.";
					link.l1 = RandSwear()+"내가 그들에게 알려주겠다!";
					link.l1.go = "exit";
					
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Soldier_")) // Солдеры по квесту "встреча в бухте"
			{
				dialog.text = "나는 너랑 얘기할 권한이 없어. 우리 장교한테 말해.";
					link.l1 = LinkRandPhrase("물론이지...","알겠어.","물론이지!");
					link.l1.go = "exit";
				break;
			}
			
			if(HasSubStr(NPChar.id, "ContraMeetManQuest_Officer_")) // Офицер по квесту "встреча в бухте"
			{
				dialog.text = "자기소개 해! 내가 누구랑 얘기하고 있는지 알고 싶으니까!";
					link.l1 = "내 이름은 "+GetFullName(PChar)+". 여기서 무슨 일이야?";
					link.l1.go = "ContraMeetManQuest_Sold_1";
				break;
			}
					
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && PChar.location == PChar.GenQuest.ContraMeetMan.ShoreID) // Квестовый чел по генеру "meeting in the cove" 
			{
				dialog.text = "선장, 네 이름이 "+GetFullName(PChar)+", 그렇지?";
					link.l1 = "그래, 네 말이 맞아.";
					link.l1.go = "ContraMeetManQuest_1";
					link.l2 = "아니. 넌 나를 다른 놈이랑 착각했군.";
					link.l2.go = "exit";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_QuestMan" && CheckAttribute(PChar, "GenQuest.ContraMeetMan.ContraIsDead")) // В комнате таверны после убицства контриков
			{
				LAi_LocationFightDisable(LoadedLocation, false);
				dialog.text = PChar.name+", 정말 고마워요! 당신이 아니었다면 내 운명은 참혹했을 거예요... 어떻게 감사드려야 할지 모르겠어요?";
					link.l1 = "난 아무것도 필요 없어...";
					link.l1.go = "ContraMeetManQuest_7";
					link.l2 = "작은 보상이라면 마다하지 않지.";
					link.l2.go = "ContraMeetManQuest_8";
					break;
			}
			
			if(NPChar.id == "ContraMeetManQuest_Contrick_0") // Контрик в комнате по квесту "встреча в бухте"
			{
				iMoney = (rand(3)+2)*500;
				PChar.GenQuest.ContraMeetMan.Money = iMoney;
				if(!CheckAttribute(PChar, "GenQuest.ContraMeetMan.ManIsTraitor")) // Просто платят деньги
				{
					dialog.text = "...흠, 맞아, 그 자가 분명해... 고맙다, "+GetSexPhrase("녀석","아가씨")+", 네 도움이 없었으면 우리는 정말 힘들 뻔했어, 이 도시에서 빠져나갈 방법이 전혀 없었거든. 자, 받아 "+FindRussianMoneyString(iMoney)+" 그리고 넌 꺼져도 돼. 우리는 우리 친구랑 '이야기' 좀 나눌 거니까...";
						link.l1 = "...";
						link.l1.go = "ContraMeetManQuest_3";
				}
				else
				{
					dialog.text = "...흠, 맞아, 그 자가 분명해... 고맙다, "+GetSexPhrase("녀석","아가씨")+", 네 도움이 없었으면 우리는 정말 곤란했을 거야, 마을을 빠져나갈 방법이 전혀 없었거든. 자, 받아 "+FindRussianMoneyString(iMoney)+" 그리고 너는 꺼져라. 이 더러운 배신자를 지금 당장 해치워 주지!";
						link.l1 = "물론이지. 또 보자고, 이봐들...";
						link.l1.go = "ContraMeetManQuest_4";
						link.l2 = "뭐?! 안 돼, 누구든 간에 사람을 죽이게 둘 수는 없어... 그리고 네 피 묻은 돈도 필요 없어!";
						link.l2.go = "ContraMeetManQuest_5";
				}
					break;
			}
			
			if(NPChar.id == "ContraDeliverQuest_Soldier_0") // Солдер в комнате
			{
				dialog.text = "그래... 여기 뭐가 있나? 해적들인가?! 너희들, 조사받으러 우리랑 사령관실로 가야겠다...";
					link.l1 = "우린 해적이 아니야! 난 이 사람을 알지도 못해! 이 사람이 방을 막 빌려 들어왔고, 나는 짐 쌀 시간도 없이 나가야 했어!";
					link.l1.go = "ContraDeliverQuest_Sold1";
					break;
			}
				
			if(CheckAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom") && NPChar.id == "ContraDeliverQuest_Contra_1")
			{
				dialog.text = "그래서 뭐라고 했지? 나한테 전할 말이 있다고?! 기다리고 있잖아!";
					link.l1 = "자, 여기 있어...";
					link.l1.go = "ContraDeliverQuest_1";
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.WaitOnRoom");
					DeleteAttribute(PChar, "GenQuest.ContraDeliver.GoToTavern");
					break;
			}
			
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "이봐, 너! 그래, 너 말이야. 보아하니 너는 괜찮고 돈 많은 사람이구나.";
					link.l1 = "너에겐 그렇게 말 못 하겠군.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_1";
					break;
			}
					
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.WayOfShortVariant") && NPChar.id == "Church_GenQuest2_Bandit_0")
			{
				dialog.text = "잠깐! 이봐, "+GetSexPhrase("동료","아가씨")+", 네 주머니가 얼마나 무거운지 보여 봐라!";
					link.l1 = "그래서, 벌써 교회 돈 다 탕진했냐?";
					link.l1.go = "Church_GenQuest_2_1";
					break;
			}
			
			if(NPChar.id == "ReasonToFast_Hunter")
			{
				if(GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > sti(pchar.questTemp.ReasonToFast.p2))
				{
					dialog.text = "이봐, 배 위에 있는 놈들! 히끅... 길 비켜라 - 형님들이랑 할 말이 있어...";
					link.l1 = "좀 어지럽지 않냐, 이봐? 가서 자고 정신 차려라.";
					link.l1.go = "ReasonToFast_Hunter1";
				}
				else
				{
					dialog.text = "이봐, 선장! 닻 내려!";
					link.l1 = "도대체 내가 왜 그래야 하지...";
					link.l1.go = "ReasonToFast_Hunter2";
				}
				link.l2 = "너무 무례한 거 아니야!?";
				link.l2.go = "ReasonToFast_Hunter3";	
			}
			
			if(NPChar.id == "PirateOnUninhabited_0")
			{
				dialog.text = RandPhraseSimple("만세! 드디어 주님께서 우리의 기도를 들으시고 이 버려진 해안에 용감한 선장을 보내주셨구나!","신의 은총이로다! 이제 이 동네 시체 파리들이 우리 썩은 뼈를 뜯어먹지 못하겠군!");
				link.l1 = "안녕, 좋은 사람아, 나는 선장이야 "+GetFullName(PChar)+". 여기서 꽤 곤란한 상황에 처한 것 같군.";
				link.l1.go = "PiratesOnUninhabited_3";
				link.l2 = "이봐, 나는 내 할 일이 있어서 네 문제에 신경 쓸 시간 없어.";
				link.l2.go = "PiratesOnUninhabited_1";
			}
			
			if(NPChar.id == "ShipWreck_0")
			{
				dialog.text = RandPhraseSimple("오, 선장님! 신께서 순풍을 보내시고 이 외딴 곳으로 인도해 주신 건 정말 큰 행운입니다!","선장님! 섭리께 감사드리오, 이 황량한 해안에 닻을 내려 주셔서!");
				link.l1 = "이봐, 좋은 사람아, 나는 선장이야 "+GetFullName(pchar)+". 여기서 큰 곤경에 처한 것 같군.";	
				link.l1.go = "ShipWreck_2";
				link.l2 = "좋은 사람이여, 나는 내 할 일이 있어서 그대 문제에 신경 쓸 시간 없다네.";
				link.l2.go = "ShipWreck_1";
			}
			
			if(NPChar.id == "Convict_0")
			{
				dialog.text = LinkRandPhrase("잠깐만, "+GetAddress_Form(pchar)+"! 귀한 시간 잠시 내주실 수 있겠습니까?","귀한 아가씨가 놓치겠소"+GetSexPhrase("테르","s")+" 이 보잘것없는 놈들의 간절한 부탁을 들어주시겠소?","고귀한 아가씨"+GetSexPhrase("테르","s")+", 부디 귀한 시간 잠시 내어 이 불쌍한 자와 이야기해 주십시오.");
				link.l1 = LinkRandPhrase("이딴 거 신경 쓸 시간 없어.","꺼져, 너 없이도 할 일이 많아.","날 내버려 둬, 너랑 얘기할 시간 없어.");
				link.l1.go = "Convict_0End";
				link.l2 = LinkRandPhrase("뭘 원해?","뭐 필요해?","무슨 일이야?");
				link.l2.go = "Convict_Begin";
			}
			
			// Warship, 15.05.11. Генер "Justice for sale".
			if(HasSubStr(NPChar.id, "JusticeOnSale_Jungle_"))
			{
				dialog.text = "이봐, 선장! 평범한 상점에서는 구할 수 없는 인디언 장신구나 물건에 관심 있어? 아니면 현금이 더 끌려?";
					link.l1 = "너 같은 거지들은 보통 뭘 요구하지, 뭘 내놓진 않지. 왜 이렇게 이상하게 공손한 거냐?";
					link.l1.go = "JusticeOnSale_1";
					link.l2 = "나 같은 놈들한텐 내 권총이 대신 말해 주지!";
					link.l2.go = "JusticeOnSale_2";
			}
		break;
		
		// Генератор "Situation in the hold - Ransom"
		case "Hold_GenQuest1":
			pchar.quest.Hold_GenQuest_FindCharTimeIsOver.over = "yes";
			dialog.text = "듣고 있소, 선장. 무슨 일로 오셨소?";
			link.l1 = "나는 미스터를 찾고 있어 "+pchar.GenQuest.Hold_GenQuest.Name+"?";
			link.l1.go = "Hold_GenQuest2";
		break;
		
		case "Hold_GenQuest2":
			dialog.text = RandPhraseSimple("나는 미스터다 "+pchar.GenQuest.Hold_GenQuest.Name+". 영광을 드릴 분이 누구시오?","그를 찾았군. 뭘 도와줄까?");
			link.l1 = "나는 선장이야 "+GetFullName(pchar)+", 너랑 얘기하고 싶은 게 있어서 "+pchar.GenQuest.Hold_GenQuest.CapName+".";
			link.l1.go = "Hold_GenQuest3";
		break;
		
		case "Hold_GenQuest3":
			sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
			pchar.GenQuest.Hold_GenQuest.RansomSum = makeint(3 * sti(sld.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(sld, "Leadership")*500 + GetCharacterSkillToOld(pchar, "commerce")*500); 
						
			switch(hrand(3))
			{
				case 0:
					dialog.text = "그게 누구지?";
					link.l1 = "잠깐만... 너는 "+pchar.GenQuest.Hold_GenQuest.Name+", 그리고 너는 몰랐지 "+pchar.GenQuest.Hold_GenQuest.CapName+"?";
					link.l1.go = "Hold_GenQuest40";
				break;
				case 1:
					dialog.text = "이런 젠장! 그 늙은 여우 소식 들은 지도 꽤 됐는데. 이번엔 또 무슨 일이 있었던 거야?";
					link.l1 = "이번에는 정말 큰일이야... 그가 포로로 잡혀 있어서 네 도움이 필요해.";
					link.l1.go = "Hold_GenQuest50";
				break;
				case 2:
					dialog.text = "좋아, 다 듣고 있어.";
					link.l1 = "그의 배가 해적들에게 공격당해서 지금은 포로로 잡혀 있소. 몸값 문제로 당신을 찾아가라고 하더군.";
					link.l1.go = "Hold_GenQuest60";
				break;
				case 3:
					dialog.text = "그래, 옛 친구 소식을 들으니 반갑군. 그 친구는 어떻게 지내고 있나?";
					link.l1 = "그의 처지는 상상조차 하기 힘들 정도로 절박하다.";
					link.l1.go = "Hold_GenQuest70";
				break;				
			}	
		break;
		
		case "Hold_GenQuest40":
			// dialog.text = "그래, 나다 "+pchar.GenQuest.Hold_GenQuest.Name+"! 하지만 내가 그걸 왜 알아야 하지 "+pchar.GenQuest.Hold_GenQuest.CapName+"?!";
			dialog.text = "그래, 내가 맞아 "+pchar.GenQuest.Hold_GenQuest.Name+"! 하지만 이름 "+pchar.GenQuest.Hold_GenQuest.CapName+" 아무 말도 안 해주네."; // belamour gen
			link.l1 = "미안하다. 내가 착각했을지도 모르겠군...";
			link.l1.go = "Hold_GenQuest41";
		break;
		
		case "Hold_GenQuest41":
			AddQuestRecord("HoldQuest", "10");
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName);
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest50":
			dialog.text = "이런 젠장! 내가 그 자를 어떻게 도와주란 말이야? 적들을 다 죽여서 풀어주라고? 하하하!";
			link.l1 = "아니, 아니야, 그럴 필요 없어. 너는 그냥 넘기기만 하면 돼 "+pchar.GenQuest.Hold_GenQuest.RansomSum+" 몸값으로 페소를.";
			link.l1.go = "Hold_GenQuest51";
		break;		
		
		case "Hold_GenQuest51":
			dialog.text = "이런 뻔뻔함이 어디 있나! 내가 왜 그놈 몸값을 내야 하지?! 내 친척도 아니고 친구도 아닌데!";
			link.l1 = "흠... 그는 당신이 그의 유일한 희망이라고 하더군. 그리고 당신이 빚을 졌다는 말도 했어...";
			link.l1.go = "Hold_GenQuest52";
		break;		
		
		case "Hold_GenQuest52":
			dialog.text = LinkRandPhrase("뭐 이런 건방진 놈이 다 있나! 참고로, 돈 빌린 건 저 자식이야! 그렇다고 내가 그놈을 몸값 받고 풀어주면 내 돈까지 다 받을 거란 기대는 안 해.","정말 못된 놈이야! 우리가 장사 몫을 나눌 때 날 속였는데, 이제 와서 자기 몸값을 내달라고 뻔뻔하게 굴다니!","이거 뜻밖인데! 내가 왜 그 녀석 몸값을 내야 하지?! 우리 그렇게 친하지도 않아.");
			link.l1 = "그럼, 내가 그에게 네가 몸값 지불을 거부했고 빚을 인정하지 않았다고 전해도 되겠군?";	
			link.l1.go = "Hold_GenQuest53";
		break;
		
		case "Hold_GenQuest53":
			dialog.text = "이런! 무슨 빚 얘기야? 나는 이미 다 설명했잖아! 그리고 이 바보 같은 이야기 말고 더 물을 게 없다면, 이제 그만 가봐도 되겠지.";
			link.l1 = "알겠어. 뭐, 너한테 더 물어볼 건 없지만, 네 친구한테는 물어볼 게 꽤 많지.";
			link.l1.go = "Hold_GenQuest54";
		break;
		
		case "Hold_GenQuest54":
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar)); // НПС вешать собрались? )))
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen				
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;
		
		case "Hold_GenQuest60":
			dialog.text = "흠... 그리고 네가 그를 붙잡고 있는 놈이구나... 뭐, 내가 그 녀석을 좀 도와주지.";
			link.l1 = "아주 좋아. 몸값은 "+pchar.GenQuest.Hold_GenQuest.RansomSum+" 페소.";
			link.l1.go = "Hold_GenQuest61";
		break;
		
		case "Hold_GenQuest61":
			dialog.text = "나를 오해했군: 나는 시의회 의원이야. 우리는 규약 준수를 감독하지.\n"+"경비병들!!! 경비병들! 저 자를 노예 거래와 선박 약탈 혐의로 체포하라 "+NationNameGenitive(sti(pchar.GenQuest.Hold_GenQuest.Nation))+"!";
			link.l1 = "그래, '동료'야, 이제 네게 가볼까...";
			link.l1.go = "Hold_GenQuest62";
		break;
		
		case "Hold_GenQuest62":
			LAi_SetImmortal(NPChar, false);
			AddQuestRecord("HoldQuest", "10");
			//AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
			AddQuestUserData("HoldQuest", "sName", pchar.GenQuest.Hold_GenQuest.CapName); // belamour gen	
			pchar.GenQuest.Hold_GenQuest = "prisoner_escaped";
			LAi_SetWarriorTypeNoGroup(NPChar);
   	        LAi_warrior_DialogEnable(NPChar, false);
            LAi_group_MoveCharacter(NPChar, "TmpEnemy");			
			LAi_group_Attack(NPChar, Pchar);
			LAi_group_SetRelation("TmpEnemy", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetCheckFunction("TmpEnemy", "Hold_GenQuest_AfterBattle");
			chrDisableReloadToLocation = true; 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);  
			AddDialogExitQuest("MainHeroFightModeOn"); 
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
			DialogExit();
		break;
		
		case "Hold_GenQuest70":
			dialog.text = "무슨 소리야?! 그리고 내가 그를 어떻게 도와야 하지?";
			link.l1 = "그는 포로로 잡혀 있고, 몸값에 대해 당신과 이야기해 달라고 내게 부탁했어.";
			link.l1.go = "Hold_GenQuest71";
		break;		
		
		case "Hold_GenQuest71":
			dialog.text = "물론이지, 물론. 내가 할 수 있는 건 다 해볼게. 그 사람들이 어디에 잡혀 있지? 그리고 몸값은 얼마야?";
			link.l1 = "해적들이 요구한다 "+pchar.GenQuest.Hold_GenQuest.RansomSum+" 페소지. 내가 항구에 돈을 전달해야 네 친구가 풀려날 거야.";
			link.l1.go = "Hold_GenQuest72";
		break;
		
		case "Hold_GenQuest72":
			dialog.text = "여기 돈이야. 다행히도 가진 게 충분했어.";
			link.l1 = "그래, 정말 다행이지. 이제 항구로 가 봐. 곧 네 동료를 다시 보게 될 거야.";
			link.l1.go = "Hold_GenQuest73";
		break;
		
		case "Hold_GenQuest73":
			addMoneyToCharacter(pchar, sti(pchar.GenQuest.Hold_GenQuest.RansomSum));
			AddQuestRecord("HoldQuest", "11");
			AddQuestUserData("HoldQuest", "sNameChar", GetFullName(NPChar)); // belamour gen 
			AddQuestUserData("HoldQuest", "sName", NPChar.Hold_GenQuest.Name); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.RansomSum);
			pchar.GenQuest.Hold_GenQuest = "prisoner_ransom";
			LAi_CharacterDisableDialog(NPChar);
			NPChar.LifeDay = 0;
			DialogExit();
			AddDialogExitQuestFunction("Hold_GenQuest_PrisonerEscaped");
		break;				
		// Генератор "Situation in the hold - Ransom"
		
		// Генератор "Situation in the hold - Partner in crime"
		case "Hold_GenQuest80":
			dialog.text = "안녕하십니까, 선장님, 아직 정식으로 인사드릴 영광이 없었습니다. 당신이 저를 찾고 있다고 들었습니다.";
			link.l1 = "정말로, 당신이 나리라면 "+pchar.GenQuest.Hold_GenQuest.Name+". 내가 선장이야 "+GetFullName(pchar)+", 너와 얘기하고 싶었어.";
			link.l1.go = "Hold_GenQuest81";
		break;
		
		case "Hold_GenQuest81":
			dialog.text = "무슨 일입니까, 선장 "+GetFullName(pchar)+"?";
			link.l1 = "네가 쉽게 내놓을 만한 물건을 가지고 있다고 들었어.";
			link.l1.go = "Hold_GenQuest82";
		break;
		
		case "Hold_GenQuest82":
			dialog.text = "도대체 무슨 뜻이야?";
			link.l1 = "그렇게 고집 부리지 마, 이 친구야. 네 그늘진 과거도, 보물 위치가 표시된 임시 지도를 가지고 있다는 것도 다 알고 있으니까."+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_ACC)+" 표시되어 있다.";
			link.l1.go = "Hold_GenQuest83";
		break;
		
		case "Hold_GenQuest83":
			dialog.text = "젠장! 난 그 악당을 항상 알고 있었지"+pchar.GenQuest.Hold_GenQuest.CapName+" 언젠가는 이걸 떠벌릴 줄 알았지! 내가 무슨 생각으로 그놈한테 이런 거래를 제안했을까?";
			link.l1 = "그만 징징대라. 해칠 생각 없어... 그냥 이 지도나 팔고 네 평소대로 살아.";
			link.l1.go = "Hold_GenQuest84";
		break;
		
		case "Hold_GenQuest84":
			dialog.text = "그렇게 확신할 수만 있다면 좋겠군... 그런데 그걸 위해 나한테 얼마나 줄 생각이지? 상자에 금이 엄청 많았던 거 알 텐데. 네 명이 들고 갔었지, 그들의 영혼에 주님의 평안이 있기를...";
			link.l1 = "But "+GetName(NAMETYPE_VIP,pchar.GenQuest.Hold_GenQuest.PirateName,NAME_NOM)+" 이미 그의 보물을 차지했을 수도 있지...";
			link.l1.go = "Hold_GenQuest85";
		break;
		
		case "Hold_GenQuest85":
			dialog.text = "맞는 말이야... 좋아, 너한테 그걸 팔 의향이 있어, 가격은 "+pchar.GenQuest.Hold_GenQuest.Sum+" 페소지. 어차피 난 죽은 자들을 감히 건드릴 생각 없어.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.Hold_GenQuest.Sum) && !CheckCharacterItem(pchar,"mapQuest") && !CheckCharacterItem(pchar,"map_full"))
			{
				link.l1 = "좋아. 거래 성사다.";
				link.l1.go = "Hold_GenQuest86";
			}	
			link.l2 = "아니, 이봐 좋은 사람, 그 쪼가리 종이는 이 돈의 가치가 없어. 잘 가라...";
			link.l2.go = "Hold_GenQuest87";
			pchar.quest.Hold_GenQuest_GetMapTimeIsOver.over = "yes";
		break;
		
		case "Hold_GenQuest86":		
			AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Hold_GenQuest.Sum));
			GiveItem2Character(pchar, "mapQuest"); 
			rItem = ItemsFromID("mapQuest");
			Hold_GenQuest_GenerateTreasureMap(rItem);
			AddQuestRecord("HoldQuest", "15");
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);						
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;	
		
		case "Hold_GenQuest87":
			NPChar.LifeDay = 0;
			LAi_CharacterDisableDialog(NPChar);
			AddQuestRecord("HoldQuest", "16");
			AddQuestUserData("HoldQuest", "sSex", GetSexPhrase("",""));
			AddQuestUserData("HoldQuest", "sPirateName", GetName( NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_GEN)); // belamour gen
			AddQuestUserData("HoldQuest", "sSum", pchar.GenQuest.Hold_GenQuest.Sum);			
			CloseQuestHeader("HoldQuest");
			DeleteAttribute(pchar,"GenQuest.Hold_GenQuest");				
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		// Генератор "Situation in the hold - Partner in crime"
		
		// Генератор "Shipwrecked"
		case "ShipWreck_1":
			dialog.text = "이게 어떻게 가능하단 말입니까, 선장님?! 신께서 이런 죄를 결코 용서하지 않으실 겁니다.";
			link.l1 = "그분께서 결정하실 일이야.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
		
		case "ShipWreck_2":
			pchar.GenQuest.ShipWreck.StartShipType = PiratesOnUninhabited_GenerateShipType(); 		
			pchar.GenQuest.ShipWreck.ShipTypeName = GenerateRandomNameToShip(sti(pchar.GenQuest.ShipWreck.Nation));			
			
			if(rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("안녕하십니까, 저는 "+pchar.GenQuest.ShipWreck.Name+"의 선장 "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Acc"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+", 내 배가 해안에서 멀지 않은 암초에 부딪혀 난파했어."+"선원 전체 중 겨우 몇 명만이 살아남았어. 조수가 우리를 이 황량한 해안으로 밀어냈지. 우리는 굶주림과 갈증에 시달렸고\n "+(5+hrand(7))+" 지금까지 몇 주째야","안녕하십니까, 저는 "+pchar.GenQuest.ShipWreck.Name+", 의 선장 "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". 우리 배가 여기서 멀지 않은 곳에 난파했어."+"난파 후에 이 해안에 겨우 도착했지만, 이곳은 사람이 살지 않는 것 같아. 우리는 어쩔 수 없이 조개랑 야자 열매로 버텼지\n "+(5+hrand(7))+" 벌써 몇 주째야.");
				link.l1 = RandPhraseSimple("그리고 너희 중에 몇이나 남았지?","그래서 너희 중에 몇이나 살아남았지?");
				link.l1.go = "ShipWreck_3";
			}
			else
			{						
				pchar.GenQuest.ShipWreck.Mutiny = "true"; // belamour gen кавычки
				pchar.GenQuest.ShipWreck.BadName = GenerateRandomName_Generator(sti(pchar.GenQuest.ShipWreck.Nation), "man");
				pchar.GenQuest.ShipWreck.City = GetQuestNationsCity(sti(pchar.GenQuest.ShipWreck.Nation));
				dialog.text = "아이고, 선장님, 우리 피해가 정말 끔찍합니다... 안녕하십니까, 저는 "+pchar.GenQuest.ShipWreck.Name+", 선장이자 선주인 "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name+"Gen"))+" '"+pchar.GenQuest.ShipWreck.ShipTypeName+". 아니, 전 선장이자 전 선주라고 해야겠군. "+"이 자식 "+pchar.GenQuest.ShipWreck.BadName+" 내가 고용한 곳은 "+XI_ConvertString("Colony"+pchar.GenQuest.ShipWreck.City+"Voc")+" 내 선원들을 반란으로 몰아넣었지. 결국 우리는 이 신이 버린 곳에 남겨졌어. 그 일이 일어났던 거야\n "+(5+hrand(7))+" 몇 주 전에.";
				link.l1 = "그리고 나서 어떻게 됐지? 네 선원 전부가 반란자 편에 섰어?";
				link.l1.go = "ShipWreck_4";			
			}
		break;
		
		case "ShipWreck_3":
			dialog.text = RandPhraseSimple("선원 전체 중 오직 "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" 살아남았지. 다른 놈들은 죽었어; 몇몇은 이미 여기서 상처와 열병으로 죽었어\n",
				"Only " + ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty)) + " 운이 좋았던 거지. 다른 놈들은 끝을 맞이했어... 바다 깊은 곳이나 이 해안의 모래언덕에서 말이야.");
			link.l1 = LinkRandPhrase("그래, 그건 참 딱한 운명이야. 하지만 그게 선원의 팔자지 - 누구든 네 처지가 될 수 있거든.","그렇군... 신께서는 모든 생명을 품고 계시지만, 너무 바쁘셔서 모두를 기억하진 못하시지.","그렇지. 사람이 계획해도, 신이 결정하지.");
			link.l1.go = "ShipWreck_5";	
		break;
		
		case "ShipWreck_4":
			dialog.text = "당연히 아니지! 많은 이들이 반란자들 편에 서길 거부했지만, 저 악당들이 무기고를 장악했어. 우리가 저항하지 않은 게 다행이야, 안 그랬으면 바로 죽었을 테니까. 여기서 이미 많은 사람들이 열병과 독충의 독에 쓰러졌어, 오직\n "+ShipWreck_GetStringQty(sti(pchar.GenQuest.ShipWreck.Qty))+" 살아남았어. 신이시여, 우리의 시련이 드디어 끝났구나.";
			link.l1 = RandPhraseSimple("그래, 그건 정말 운이 지독하게 없었던 거지.","뭐, 이런 버려진 곳에서는 별별 기이한 일이 다 일어날 수 있지.");
			link.l1.go = "ShipWreck_5";			
			link.l2 = "잠깐, 친구. 네가 반란을 일으키려고 상륙한 게 아니라는 걸 내가 어떻게 알 수 있겠어?";
			link.l2.go = "ShipWreck_6";			
		break;
		
		case "ShipWreck_5":
			dialog.text = RandPhraseSimple("선장님, 배에 빈 사물함이 몇 개쯤은 있기를 바랍니다. 우리 모두 가족이 있는데, 우리가 이렇게 이야기하는 동안 아마 우리를 잃었다고 슬퍼하고 있을 겁니다. 정말 감사하겠습니다.","선장님, 우리는 정말 절망적입니다. 당신만이 우리의 유일한 희망이에요. 제발, 우리를 외면하지 말고 이 신이 버린 땅에서 데려가 주십시오.");
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l1 = "오... 그래서 어디로 데려가면 되겠어?";
				link.l1.go = "ShipWreck_7";			
			}
			link.l2 = RandPhraseSimple(RandPhraseSimple("정말 미안하지만, 빈 해먹 하나도 없고, 선실은 말할 것도 없어. 선원들은 갑판에서 자고 있어; 당직 끝나고도 제대로 쉬지도 못해...","정말 실망시키고 싶진 않지만, 배가 과적되어서 사람들은 악천후 속에서 잠을 자야 해. 만약 병이 돌기라도 하면, 선원 절반을 잃게 될 거야."),RandPhraseSimple("정말 미안하지만, 내 배에는 여분의 선원 공간이 전혀 없어. 더 이상 승객을 태울 수 없다.","유감이지만 실망시켜야겠군, 내 배는 이미 과적 상태야. 전염병이라도 돌까 두렵거든."));
			link.l2.go = "ShipWreck_8";	
			if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "넌 노련한 선원이니 난파에서 살아남은 자가 있으면 그게 얼마나 불길한 징조인지 알겠지. 내 선원들이 너희 전부 바다에 내던져 버릴 거다.";
				link.l3.go = "ShipWreck_9";
			}
		break;
		
		case "ShipWreck_6":
			dialog.text = "무슨 소릴 하는 거야, "+GetAddress_Form(npchar)+" "+pchar.lastname+"?! 좀 봐줘! 나는 카리브에서 이름난 중개상이야! 뭐... 예전엔 그랬지. 지금은 배도 돈도 없으니 아니지만...";
			link.l1 = "어떻게 된 거지... 너희가 반란의 진짜 주동자였겠지, 이제 마땅한 대가를 치른 거야.";
			link.l1.go = "ShipWreck_18";
			if(GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "근데 저건 정말 악당이잖아 "+pchar.GenQuest.ShipWreck.BadName+"! 정말 그 자를 그냥 놔두고 네 운명에 순순히 따르려는 거냐?";
				link.l2.go = "ShipWreck_19";
			}	
		break;		
		
		case "ShipWreck_7":
			if(rand(1) == 0)
			{
				if(rand(100) < 90)
				{
					pchar.GenQuest.ShipWreck.variant = "1";
					dialog.text = "어느 정착지로든 "+NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation))+".";
					link.l1 = "그래, 빈 침상도 해먹도 충분히 있으니 배에 타.";
					link.l1.go = "ShipWreck_10";
					link.l2 = "흠... 우리 앞에 전투가 기다리고 있는데, 네가 내 배에 있는 게 더 안전할지, 아니면 이 아늑한 만에 있는 게 더 안전할지 모르겠군.";
					link.l2.go = "ShipWreck_11";
				}
				else
				{				
					dialog.text = "덩케르크로 가자! 우리 어머니가 거기 사셔...";
					link.l1 = "미쳤어, 뭐야?! 머리에 너무 많이 맞은 거 아니냐...";
					link.l1.go = "ShipWreck_12";					
					pchar.GenQuest.ShipWreck.Crazy = true; // получите психа на борт :-)
					
				}				
			}
			else
			{
				pchar.GenQuest.ShipWreck.variant = "2";
				dialog.text = "어디든 상관없어, 우리한텐 별로 중요하지 않거든. 어차피 줄 돈도 없으니까...";
				link.l1 = "그래, 빈 사물함이랑 해먹은 충분히 있어. 배에 타.";
				link.l1.go = "ShipWreck_10_1";
				link.l2 = "흠... 앞으로 전투가 기다리고 있는데, 내 배에 타는 게 더 안전할지, 아니면 이 아늑한 만에 있는 게 더 안전할지 모르겠군.";
				link.l2.go = "ShipWreck_11";		
			}						
		break;		

		case "ShipWreck_8":
			pchar.GenQuest.ShipWreck.FoodQty = sti(pchar.GenQuest.ShipWreck.Qty) * 10 + rand(10);
			pchar.GenQuest.ShipWreck.MedicamentQty = sti(pchar.GenQuest.ShipWreck.Qty) * 5 + rand(10);
			pchar.GenQuest.ShipWreck.AmunitionQty = sti(pchar.GenQuest.ShipWreck.Qty) * 3 + rand(5);
			pchar.GenQuest.ShipWreck.RumQty = sti(pchar.GenQuest.ShipWreck.Qty) * 7 + rand(10);
			if(GetFreeCrewQuantity(pchar) < sti(pchar.GenQuest.ShipWreck.Qty))
			{
				if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))
				{
					dialog.text = "하지만 거절한다면 우릴 분명 죽음으로 몰아넣는 거야! 좋아, 목숨을 걸고서라도 배까지 싸워 나가 보겠다!";
					link.l1 = "뭐야? 너희 꼴 좀 봐, 제대로 서 있지도 못하잖아...";
					link.l1.go = "ShipWreck_8_1";
					link.l2 = "시도해 봐라...";
					link.l2.go = "ShipWreck_16";
				}
				else
				{
					dialog.text = "하지만 우리를 여기 그냥 두고 갈 순 없잖아! 네가 도와주지 않으면 우리 모두 곧 죽고 말 거야!";
					if(GetSquadronGoods(pchar, GOOD_WEAPON) < sti(pchar.GenQuest.ShipWreck.AmunitionQty) || GetSquadronGoods(pchar, GOOD_RUM) < sti(pchar.GenQuest.ShipWreck.RumQty))
					{			
						link.l1 = "내가 해줄 수 있는 건 식량과 약을 충분히 남겨두고, 배 한 척을 주는 것뿐이야. 적어도 굶거나 목말라 죽지는 않겠지.\n항해에 관해서는 내가 따로 가르칠 필요도 없겠군.";
						link.l1.go = "ShipWreck_8_2";
					}
					else
					{
						if(rand(1) == 0)
						{
							link.l1 = "내가 해줄 수 있는 건 식량과 약을 충분히 남겨두고 배 한 척을 주는 것뿐이오. 적어도 굶주리거나 목말라 죽지는 않을 거요. 항해에 관해서라면, 내가 따로 가르칠 필요는 없겠지.";
							link.l1.go = "ShipWreck_8_2";
						}
						else
						{
							link.l1 = "한 달치 약, 탄약, 럼주, 식량은 충분히 남겨둘 수 있소. 내가 직접 돌아오거나, 아니면 누군가를 보내겠소.";
							link.l1.go = "ShipWreck_8_4";
						}
					}
				}
			}
			else
			{
				if(stf(pchar.reputation.nobility) <= REPUTATION_NEUTRAL) // плохиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						dialog.text = "하지만 거절하면 우리 모두 확실히 죽게 될 거야! 좋아, 목숨을 걸고서라도 배까지 싸워 나가 보자!";
						link.l1 = "뭐야? 너희 꼴 좀 봐, 다리도 제대로 못 가누잖아...";
						link.l1.go = "ShipWreck_8_1";
						link.l2 = "한번 해봐라...";
						link.l2.go = "ShipWreck_16";					
					}
					else
					{
						link.l1 = "내가 너한테 해줄 수 있는 거라곤 식량이랑 약품 좀 남겨주고 보트 하나 주는 것뿐이야. 적어도 굶주리거나 목말라 죽진 않겠지. 항해는, 내가 따로 가르칠 필요도 없잖아.";
						link.l1.go = "ShipWreck_8_2";					
					}
				}
				else // кибальчиш
				{
					if(GetSquadronGoods(pchar, GOOD_FOOD) < sti(pchar.GenQuest.ShipWreck.FoodQty) || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < sti(pchar.GenQuest.ShipWreck.MedicamentQty))				
					{
						if(rand(1) == 0)
						{
							dialog.text = "하지만 거절한다면, 우리 모두를 죽음으로 내모는 거야! 좋아, 목숨을 걸고서라도 배까지 싸워 나가 보겠다!";
							link.l1 = "뭐라고? 너희들 좀 봐, 제대로 서 있지도 못하잖아...";
							link.l1.go = "ShipWreck_8_1";
							link.l2 = "해봐도 좋아...";
							link.l2.go = "ShipWreck_16";						
						}
						else
						{
							dialog.text = "어떻게 우리한테 이럴 수가 있지?!.. 너는 해상 규율도 무시했을 뿐만 아니라, 네 명예까지 더럽혔어!";
							link.l1 = "내 명예를 논할 자격이 네게 있겠어, 꼬마야!";
							link.l1.go = "ShipWreck_16";
						}	
					}
					else
					{
						link.l1 = "내가 너한테 해줄 수 있는 건 식량이랑 약을 충분히 남겨두고, 배 한 척을 주는 것뿐이다. 적어도 굶주리거나 목말라 죽지는 않겠지.\n항해는 내가 따로 가르칠 필요도 없잖아.";
						link.l1.go = "ShipWreck_8_2";											
					}						
				}
			}			
		break;				
	
		case "ShipWreck_8_1":
			dialog.text = "네 말이 맞아, 우린 가망이 없어. 좋아, 신께서 심판하시길, 그리고 모두가 마땅히 받을 것을 받길 바라지.";
			link.l1 = "뭐, 내가 알아서 할 수 있지...";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;
	
		case "ShipWreck_8_2":
			dialog.text = "음... 너 때문에 우리도 별 수 없게 됐군... 사람이 사는 곳에 닿기 전에 폭풍이나 갈증에 죽지 않길 기도해야겠어...";
			link.l1 = "안녕히 가시오. 주님께서 그대를 지켜주시길...";
			link.l1.go = "ShipWreck_8_3";
		break;
		
		case "ShipWreck_8_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 25);
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_7";
			NextDiag.CurrentNode = NextDiag.TempNode;			
		break;
	
		case "ShipWreck_8_4":	
			dialog.text = "아무래도 선택의 여지가 없군요... 하지만 부탁드립니다, 선장님, 가능한 한 빨리 돌아오시거나 아니면 원정선을 보내주십시오.";
			link.l1 = "뭔가 생각해 볼게. 그냥 기다려.";
			link.l1.go = "ShipWreck_8_5";
		break;
	
		case "ShipWreck_8_5":		
			pchar.quest.ShipWreck_LocationExit.over = "yes";
			AddCharacterExpToSkill(pchar, "Leadership", 50); 
			RemoveCharacterGoods(pchar, GOOD_FOOD, sti(pchar.GenQuest.ShipWreck.FoodQty));
			RemoveCharacterGoods(pchar, GOOD_MEDICAMENT, sti(pchar.GenQuest.ShipWreck.MedicamentQty));			
			RemoveCharacterGoods(pchar, GOOD_WEAPON, sti(pchar.GenQuest.ShipWreck.AmunitionQty));
			RemoveCharacterGoods(pchar, GOOD_RUM, sti(pchar.GenQuest.ShipWreck.RumQty));			
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.FoodQty + " units of provision.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.MedicamentQty + "units of medicine.");		
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.AmunitionQty + " units of arms.");
			Log_SetStringToLog("You have spent " + pchar.GenQuest.ShipWreck.RumQty + " units of rum");	
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "11");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);			
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "10");
				AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			DialogExit();
			NextDiag.TempNode = "ShipWreck_8_6";
			NextDiag.CurrentNode = NextDiag.TempNode;	
			pchar.GenQuest.ShipWreck = "SailorsOnShore";
			SetFunctionTimerCondition("ShipWreck_SaveSailors", 0, 0, 30, false);
			pchar.GenQuest.ShipWreck.Shore = pchar.location;
			SaveCurrentQuestDateParam("GenQuest.ShipWreck");
			SetFunctionLocationCondition("ShipWreck_MeetInShore", pchar.GenQuest.ShipWreck.Shore, true);
		break;
	
		case "ShipWreck_8_6":			
			dialog.text = RandPhraseSimple("선장님, 제발 기억해 주십시오. 당신만이 우리의 유일한 희망입니다...","왜 아직도 머물고 있는 거야? 여기서 보내는 매 순간이 우리에겐 견딜 수가 없어...");
			link.l1 = "내가 할 수 있는 건 다 해보겠어. 잘 있어...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_6";		
		break;

		case "ShipWreck_8_7":			
			dialog.text = RandPhraseSimple("안녕히 가시오, 선장님... 우리는 여행을 준비해야 하오.","잘 가라... 그리고 우리 영혼을 구원하려면 촛불을 밝혀라...");
			link.l1 = "잘 가시오. 주님께서 그대를 지켜주시길...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_8_7";		
		break;
		
		case "ShipWreck_9":
			pchar.GenQuest.ShipWreck = "SailorsOnShoreFight"; // belamour gen
			dialog.text = "어떻게 우리한테 이럴 수가 있지?! 너는 해상 규율도 무시했을 뿐만 아니라, 네 명예까지 더럽혔어!";
			link.l1 = "내 명예를 논할 자격이 네가 있다고 생각하냐, 꼬마야!";
			link.l1.go = "ShipWreck_16";
		break;					
		
		case "ShipWreck_10":
			dialog.text = "감사합니다, 선장님! 선적은 오래 걸리지 않을 겁니다. 신이시여, 우리가 그 순간이 오길 얼마나 기도했는지 모릅니다!";
			link.l1 = "좋군. 네 고생도 곧 끝나길 바란다.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Nation_City";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.nation = sti(pchar.GenQuest.ShipWreck.Nation);
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "2");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
			}
			else
			{
				AddQuestRecord("ShipWrecked", "1");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				AddQuestUserData("ShipWrecked", "sNation", NationNameGenitive(sti(pchar.GenQuest.ShipWreck.Nation)));
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}
			
		break;							

		case "ShipWreck_10_1":
			dialog.text = "감사합니다, 선장님! 선적은 오래 걸리지 않을 겁니다. 신이시여, 우리가 이 순간이 오기를 얼마나 기도했는지 모릅니다!";
			link.l1 = "좋군. 네 고생도 곧 끝나길 바란다.";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";
			ReOpenQuestHeader("ShipWrecked");
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny"))
			{
				AddQuestRecord("ShipWrecked", "4");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
			}
			else
			{
				AddQuestRecord("ShipWrecked", "3");
				AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
				// --> belamour окончание по количеству персон
				if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailors");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " sailor");
				}
				// <-- belamour
				AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
				AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);
				// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				else
				{
					AddQuestUserData("ShipWrecked", "sText", "wrecked");
				}
				// <-- belamour
			}			
		break;							
				
		case "ShipWreck_11":
			dialog.text = "어서 가자고! 진짜야, 선장?! 우리가 죽음을 두려워한다고?! 한 번 속였으면 또 할 수 있지. 다만 이렇게 허무하게 죽고 싶진 않아. 여기서 썩어가긴 싫다고, 혼자서\n기꺼이 선장님의 선원으로 들어가서 용감하게 깃발 아래 싸우겠어. 제발 우리를 여기 버리지 말아줘...";
			link.l1 = "여기서 나가려고 뭐든 할 각오가 된 건 알겠어. 하지만 너희 꼴 좀 봐라, 대체 어떤 놈들이 선원이 될 수 있겠냐?";
			link.l1.go = "ShipWreck_14";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l2 = "좋은 생각이군. 너를 고용해도 되겠어.";
				link.l2.go = "ShipWreck_15";
			}	
		break;									
		
		case "ShipWreck_12":
			dialog.text = "아니, 아니야, 농담하는 거 아니야! 제발, 이 카리브의 도살장에서 날 데리고 나가 줘... 이 지옥에서 벗어나게 해줘! 나, 부자야... 아주 큰 부자라고. 교황조차도 평생 그만한 금을 본 적이 없을 거야. 금으로 널 가득 채워주겠어...";
			link.l1 = "이런... 좋아, 배에 타라...";
			link.l1.go = "ShipWreck_13";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			ChangeOfficersLoyality("bad_all", 1);
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "5");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty);
			AddQuestUserData("ShipWrecked", "ShipType", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].Name + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
			// --> belamour: нужно разделить, иначе получается с потерпевшего крушение бригантины
			if(ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(pchar.GenQuest.ShipWreck.StartShipType)].name == "SHIP_SCHOONER_W")
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "sText", "wrecked");
			}
			// <-- belamour
		break;							

		case "ShipWreck_13": // берем пассажирами
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			//Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.variant"))
			{
				if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
				if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			}	
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "ShipWreck_13_again";
			}
			DialogExit();
		break;
		
		case "ShipWreck_13_again":
			dialog.text = LinkRandPhrase("왜 꾸물거리고 있소, 선장? 닻 올리라고 명령하시오.","죄송합니다, 선장님, 하지만 출항 준비를 해야 합니다.","네가 여기 오기로 결심하다니, 우리 정말 운이 좋다!");
			link.l1 = "서둘러라. 배는 아무도 기다려주지 않는다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_13_again";		
		break;
		
		case "ShipWreck_14":
			dialog.text = "선장님, 우린 잃을 게 없소. 죽음은 이미 우리 뒤를 따라오고 있지... 더러운 코요테들에게 잡아먹히느니 차라리 정정당당하게 싸우다 죽겠소...";
			link.l1 = "오, 그럼 시비 거는 거냐?! 좋아, 우리 갈등을 끝내자"+GetSexPhrase(", 사내답게","")+"!";
			link.l1.go = "ShipWreck_16";
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;		
		
		case "ShipWreck_15":
			dialog.text = "맹세합니다, 선장님, 절대 후회하지 않으실 겁니다. 우리가 이 군도에서 최고의 선원이 될 테니까요.";
			link.l1 = "좋아! 배에 타라...";
			link.l1.go = "ShipWreck_17";			
		break;				
		
		case "ShipWreck_16":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetImmortal(rChar, false);
				if(CheckPassengerInCharacter(pchar, "ShipWreck_" + i)) 
				{
					RemovePassenger(pchar, rChar);
				}
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ShipWreckGroup");
			}

			LAi_Group_SetRelation("ShipWreckGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("ShipWreckGroup", LAI_GROUP_PLAYER, true);
			if(pchar.GenQuest.ShipWreck == "fight" || pchar.GenQuest.ShipWreck == "SailorsOnShoreFight") // belamour gen
			{
				LAi_group_SetCheck("ShipWreckGroup", "OpenTheDoors"); 
				LAi_group_SetCheckFunction("ShipWreckGroup", "ShipWreck_AfterBattle");
			}	
			DialogExit();		
		break;
		
		case "ShipWreck_17": // принимаем в команду
			if(pchar.GenQuest.ShipWreck.variant == "1") ChangeCharacterComplexReputation(pchar,"nobility", 1);			
			if(pchar.GenQuest.ShipWreck.variant == "2") ChangeCharacterComplexReputation(pchar,"nobility", 2);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;			
				rChar.Dialog.currentnode = "ShipWreck_17_again";
			}
			AddCharacterCrew(pchar, sti(pchar.GenQuest.ShipWreck.Qty));
			// --> belamour gen по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5) sText = "";	
			else sText = "";
			Log_Info("Your team has increased by " + pchar.GenQuest.ShipWreck.Qty + " man" + sText + ".");
			// <-- belamour gen 
			Achievment_SetStat(29, sti(pchar.GenQuest.ShipWreck.Qty));
			pchar.quest.ShipWreck_LocExit.over = "yes"; // Снимаем прерывание на выход из локации			
			DeleteAttribute(pchar, "GenQuest.ShipWreck");			
			AddCharacterExpToSkill(pchar, "Leadership", 50); 			
			DialogExit();
		break;

		case "ShipWreck_17_again":
			dialog.text = LinkRandPhrase("맹세합니다, 선장님, 절대 후회하지 않으실 겁니다.","옳은 선택을 하셨군요, 선장님.","선장님, 안심하시오. 당신도 우리만큼 운이 좋았소!");
			link.l1 = RandPhraseSimple("그러길 바란다.","서둘러. 배는 아무도 기다려주지 않아.");
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_17_again";
		break;
		
		case "ShipWreck_18":
			dialog.text = "선장님, 왜 그렇게 정직한 사람들을 의심해서 기분 상하게 하십니까? 얼굴들 좀 보세요, 정말로 저 사람들이 반란을 일으킬 거라고 생각하십니까?";
			link.l1 = "좋아, 그런데 이제 너를 어떻게 해야 하지?";
			link.l1.go = "ShipWreck_20";
		break;
		
		case "ShipWreck_19":
			dialog.text = "내가 뭘 할 수 있겠어? 적어도 지금은 살아 있잖아... 그리고 이렇게 살아남은 걸 신께 감사하지! 하지만 네가 내 배를 되찾게 도와주고 내 치욕을 갚아준다면, 저 악당이 훔쳐서 선창에 숨겨둔 건 뭐든지 네게 줄 용의가 있어.";
			link.l1 = "좋아, 거래 성사다.";
			link.l1.go = "ShipWreck_13";
			ShipWreck_SetCapToMap();
			SetFunctionTimerCondition("prosralisrok", 0, 0, 180, false); // таймер лесник тамймер на поиск корабля 																																   
			ReOpenQuestHeader("ShipWrecked");
			AddQuestRecord("ShipWrecked", "16");
			AddQuestUserData("ShipWrecked", "ShoreName", UpperFirst(XI_ConvertString(pchar.location + "Gen"))); // belamour gen
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			// --> belamour окончание по количеству персон
			if(sti(pchar.GenQuest.ShipWreck.Qty) >= 5)
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailors");
			}
			else
			{
				AddQuestUserData("ShipWrecked", "count", pchar.GenQuest.ShipWreck.Qty + " his sailor");
			}
			// <-- belamour
			AddQuestUserData("ShipWrecked", "sBadName", pchar.GenQuest.ShipWreck.BadName);
			AddQuestUserData("ShipWrecked", "ShipName", pchar.GenQuest.ShipWreck.ShipTypeName);	
		break;
		
		case "ShipWreck_20":
			dialog.text = "우리가 명령할 처지가 아니야. 네가 결정해, 아무 정착지에 데려가든가 아니면 우리를 네 선원으로 받아줘.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.ShipWreck.Qty))
			{
				link.l1 = "좋아, 내 선원으로 받아주지. 하지만 장난은 금물이야! 내 배에서는 규율이 엄격하다고!";
				link.l1.go = "ShipWreck_17";
			}
			link.l2 = "나는 너를 어디에도 데려가지 않아. 내 선원들만으로도 이미 건달이 충분하거든.";	
			link.l2.go = "ShipWreck_22";
			link.l3 = "좋아, 배에 타. 내가 어디로 데려가 줄게.";
			link.l3.go = "ShipWreck_10_1";
		break;		
		
		case "ShipWreck_22":
			dialog.text = "어쩔 수 없군... 우리에게 선택지가 없으니... 신의 자비로 이 위험한 곳에서 벗어날 수 있기를 기도할 수밖에. 신께서 허락하신다면, 아직 사람이 사는 땅에 닿을 수 있을지도 모르지...";
			link.l1 = "잘 가시오. 주님께서 그대를 지켜주시길...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("ShipWreck_DialogDisable");
		break;		
		
		case "ShipWreck_30":
			if(pchar.GenQuest.ShipWreck == "SailorsSaved")
			{
				dialog.text = "정말 감사합니다, 선장님 "+GetFullName(pchar)+"! 당신이 우리를 위해 해준 일이 너무 많아서 아무리 감사해도 다 갚을 수 없소. 우리 가진 것들이 구리 한 닢만큼의 가치도 없지만, 이 부적을 드리고 싶소. 해전이 잦은 선장에게 아주 유용할 거요.";
				link.l1 = "선물 고맙소! 이 장신구 정말 쓸모 있구만! 잘 가시오, 선장 "+pchar.GenQuest.ShipWreck.Name+" 여정에 행운이 함께하길 바라네.";
				link.l1.go = "ShipWreck_47";
			}
			else
			{
				dialog.text = "선장님, 정말 감사합니다. 우리를 위해 너무 많은 일을 해주셨으니, 어떤 보상도 저희의 감사함에 비하면 보잘것없을 것입니다. 부디, 저희의 작은 성의를 받아주십시오.";
				link.l1 = "정말, 굳이 이럴 필요까지는 없었는데... 당신이 나보다 돈이 훨씬 더 필요할 텐데 말이야. 그래도 참 고마워. 고맙고, 잘 가.";
				link.l1.go = "ShipWreck_31";
			}	
		break;
		
		case "ShipWreck_31":
			//addMoneyToCharacter(pchar, sti(pchar.rank) * 200 + rand(2000));
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			TakeNItems(pchar, "jewelry2", 15+hrand(10));
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony"+ Locations[FindLocation(PChar.location)].townsack + "Acc"));
			CloseQuestHeader("ShipWrecked");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_32":	
			dialog.text = "선장님, 이제부터는 선장님을 위해 세상 끝까지라도 따라갈 사람들이 있다는 걸 알아주십시오.\n감사할 만한 게 아무것도 없다는 게 안타깝군요.\n그래도... 제발 이 장신구를 받아주십시오. 저주받은 만에서 주운 것입니다.\n이게 선장님께 행운을 가져다주길 바랍니다.";
			link.l1 = "내 입장이라면 누구라도 똑같이 했을 거야. 잘 가라.";
			link.l1.go = "ShipWreck_33";
		break;
		
		case "ShipWreck_33":
			GiveItem2Character(pchar, pchar.GenQuest.ShipWreck.Prize);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddQuestRecord("ShipWrecked", "6");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + Locations[FindLocation(PChar.location)].townsack + "Acc")); // belamour gen: просто pchar.location ничего не даст
			CloseQuestHeader("ShipWrecked");		
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_34":
			dialog.text = RandPhraseSimple(RandPhraseSimple("선장님, 벌써 덩커크에 도착한 겁니까?","우리가 정말 덩케르크에 온 거야, 선장?"),RandPhraseSimple("선장님, 여기가 유럽입니까?","우리가 이렇게 빨리 유럽까지 항해한 거야?"));
			bTemp = !GetCharacterItem(pchar, "map_full") && !GetCharacterItem(pchar, "map_part2");
			bTemp = !GetCharacterItem(pchar, "map_part1") || bTemp;
			if(rand(100) > 75 && !isDay() && bTemp)
			{
				link.l1 = "아-하...";
				link.l1.go = "ShipWreck_40";
			}
			else
			{
				link.l1 = LinkRandPhrase("아직 아니야...","던커크? 유럽? 뭘 말하는 거야? 주위를 좀 봐!","이런 맙소사!");
				link.l1.go = "ShipWreck_35";
			}
		break;
		
		case "ShipWreck_35":
			dialog.text = LinkRandPhrase("하지만, 선장님, 약속하셨잖아요!","어떻게 약속을 어길 수 있지, 선장?","그럼 우리는 언제 유럽에 가는 거야?");
			if(rand(100) < 70)
			{
				link.l1 = "좋아. 이봐, 네 놈은 네 사람들과 네 짐 챙겨서 원하는 곳으로 가라.";
				link.l1.go = "ShipWreck_36";
			}
			link.l2 = RandPhraseSimple(LinkRandPhrase("정말 우리가 덩케르크에 꼭 가야 한다고 확신해?","있잖아, 내 배는 대양을 건너기엔 적합하지 않아.","선장, 그런데 카리브 해가 뭐가 문제야?"),LinkRandPhrase("하지만 내 계획은 달랐지...","도대체 왜 처음부터 유럽에 가고 싶어 하는 거야...","저 매혹적인 물라토 여자들을 생각해 봐! 유럽에서는 절대 못 만나지..."));
			link.l2.go = "ShipWreck_37";	
		break;
		
		case "ShipWreck_36":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			pchar.GenQuest.ShipWreck = "fight";
			dialog.text = "하지만 어떻게?.. 감히 이럴 수가?! 이게 무슨 배신이야?! 약속을 지키는 법을 가르쳐 주마!";
			link.l1 = "그래, 네가 원한 거니까...";
			link.l1.go = "ShipWreck_16";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		case "ShipWreck_37":
			dialog.text = LinkRandPhrase(RandPhraseSimple("안 돼! 난 반드시 덩케르크로 가야 해!","나한테 지리를 가르칠 게 아니라, 네 의무나 다 하라고!"),RandPhraseSimple("그 얘기는 더 이상 듣고 싶지 않아! 유럽으로 데려가기로 약속했잖아!","아니요, 선장님, 그건 안 됩니다. 우리는 유럽으로 항해 중입니다."),"나는 이 구멍 같은 곳에서 비참하게 남은 인생을 보낼 생각 없어!");
			link.l1 = "아, 이게 어떻게 끝날지 모르겠네...";
			link.l1.go = "ShipWreck_38";
		break;		
		
		case "ShipWreck_38":
			chrDisableReloadToLocation = false;			
			SetFunctionExitFromLocationCondition("ShipWreck_ExitFromTown", pchar.location, false);				
			if(!CheckAttribute(pchar,"GenQuest.ShipWreck.CrazyRec")) // mitrokosta исправлена блокировка поручения капитана
			{
				pchar.GenQuest.ShipWreck.CrazyRec = true;
				AddQuestRecord("ShipWrecked", "7");
			}
			DialogExit();
		break;
		
		case "ShipWreck_40":
			pchar.quest.ShipWreck_DeliveToCity.over = "yes";
			dialog.text = "봐라! 저게 바로 괜찮은 놈이지! 유럽! 피로 얼룩진 늙은 유럽! 그래, 그래, 그래!\n그래! 네가 약속한 대로 했으니, 나도 내 몫을 지키지. 자, 이게 지도 반쪽이다. 나머지 반쪽은 내 동료가 가지고 있었지. 평안히 잠들었을까, 아니면 물속에서 쉬고 있을까? 뭐, 상관없지. 이 모험에 나를 끌어들인 것도 그 녀석이었으니까.";
			link.l1 = "잠깐만, 그럼 너는 선원이 아니라고? 네 동료가 선장이었어?";
			link.l1.go = "ShipWreck_41";
		break;
		
		case "ShipWreck_41":
			dialog.text = "이런, 이런!.. 물론 아니지! 그래, 나는 뱃사람이 아니야. 그리고 그는 해안에서 더 멀리 항해하려다 거대한 파도에 휩쓸려 바다로 떨어졌어. 그때 내가 지휘를 맡아서 만에 들어가라고 명령했지... 암초 사이를 잘 빠져나가고 있었는데, 결국 치명적인 사고가 모든 걸 결정했어. 배가 암석 조각에 부딪혀 침몰하고 말았지...";
			link.l1 = "이거야말로 제대로 무능함을 보여주는군...";
			link.l1.go = "ShipWreck_42";
		break;
		
		case "ShipWreck_42":
			dialog.text = "이봐, 여기가 정말 덩커크 맞아? 생각해 봐, 겨우 6개월 지났는데 완전히 딴판이 됐잖아\n자, 여기 지도를 가져가. 아니, 정확히 말하면 일부만 주는 거야. 보물은 동굴 안에 있어! 어느 섬인지는 모르겠지만, 넌 노련한 선원이니까 언젠가 정확한 위치를 찾을 수 있을 거야... 해적 아아아르르르흐라는 놈의 수많은 재물이 분명히 있을 거라고 장담하지...";
			link.l1 = "고맙다, 이봐. 보물이 하나도 없어도 너무 실망하진 않을 거야. 잘 가라, 그리고 우리 다시는 안 보게 되길 바란다...";
			link.l1.go = "ShipWreck_43";
		break;
		
		case "ShipWreck_43":
			sld = CharacterFromID("ShipWreck_0");
			RemovePassenger(pchar, sld);
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			AddMapPart();
			AddQuestRecord("ShipWrecked", "9");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");	
			AddSimpleRumourCity(LinkRandPhrase(RandPhraseSimple("They say some loony recently showed up on the island. He is telling everyone that he had lost his documents, and no he's attempting to apply for a captain on a ship to Dunkirk.",
				"They say some maniac recently showed up on the island. He stole a spade at the local shop and now is digging a pit past the town gates..."),
				RandPhraseSimple("Just imagine, recently some visiting European in worn and dirty clothes attempted to get an audience with the governor! He claimed that he needed to see the governor of Dunkirk ass soon as possible.",
				"There was a scandal at the town hall recently. Some vagrant was caught, he claimed that he personally knew the governor of Dunkirk."),
				"Some psycho was looking for you recently. He claimed that you owed him money..."), pchar.location, 5, 3,"");
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_44":
			dialog.text = RandPhraseSimple("선장님, 우리를 잊지 않으셨다니 정말 기쁩니다! 우리 모두 선장님을 위해 기도하고 있었어요!","선장님, 우리의 구원이 가까워진 겁니까? 얼마나 간절히 기다리며 기도했는지 모릅니다! 일부 사람들은 이미 절망하기 시작했어요...");
			link.l1 = "안녕, "+pchar.GenQuest.ShipWreck.Name+"! 내가 동료들을 이런 상태로 두고 갈 수 있겠어? 어디로 가야 하지?";
			link.l1.go = "ShipWreck_45";
			link.l2 = "안녕, "+pchar.GenQuest.ShipWreck.Name+"! 유감이지만 나쁜 소식이 있어. 계획이 바뀌어서 널 배에 태울 수 없게 됐어.";
			link.l2.go = "ShipWreck_9";
		break;
		
		case "ShipWreck_45":
			dialog.text = "우린 어디로 가든 상관없어, 이 저주받은 곳에서 충분히 멀리만 가면 돼... 우리 짐을 싣기 시작해도 되겠나?";
			link.l1 = "그래, 그렇게 해. 곧 네 고생도 끝날 거야.";
			link.l1.go = "ShipWreck_46";
		break;

		case "ShipWreck_46":
			ChangeCharacterComplexReputation(pchar,"nobility", 4);			
			for(i = 0; i < sti(pchar.GenQuest.ShipWreck.Qty); i++)
			{
				rChar = CharacterFromID("ShipWreck_" + i);
				if(i == 0) 
				{
					AddPassenger(pchar, rChar, false);
					SetCharacterRemovable(rChar, false);	
				}
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.dialog.currentnode = "ShipWreck_13_again";
			}			
			pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen снять таймер на 30 дней	 
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1 = "Location_Type";
			pchar.quest.ShipWreck_DeliveToCity.win_condition.l1.location_type = "town";
			pchar.quest.ShipWreck_DeliveToCity.function = "ShipWreck_DeliveToCity";			
			pchar.GenQuest.ShipWreck = "SailorsSaved";
			if(CheckAttribute(pchar,"GenQuest.ShipWreck.Mutiny")) DeleteAttribute(pchar,"GenQuest.ShipWreck.Mutiny"));
			SetFunctionExitFromLocationCondition("ShipWreck_LocationExit", pchar.location, false);				
			DialogExit();			
		break;

		case "ShipWreck_47":
			AddCharacterExpToSkill(pchar, "Fortune", 50);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			GiveItem2Character(pchar, "indian_10");
			AddQuestRecord("ShipWrecked", "15");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			AddQuestUserData("ShipWrecked", "sName", pchar.GenQuest.ShipWreck.Name);
			CloseQuestHeader("ShipWrecked");				
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_48":
			dialog.text = "감사합니다, 선장님. 우리는 이미 절망하기 시작했지만, 선장님 덕분에 정말 다시 살아난 기분입니다.";
			link.l1 = "별일 아니었어... 잘 가.";
			link.l1.go = "ShipWreck_49";
		break;
		
		case "ShipWreck_49":
			AddQuestRecord("ShipWrecked", "17");
			AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("ShipWrecked");								
			DialogExit();
			AddDialogExitQuestFunction("ShipWreck_GoOut");
		break;
		
		case "ShipWreck_50":
			dialog.text = "도대체 나한테 뭘 원하는 거야?";
			link.l1 = "왔어"+GetSexPhrase("","")+" 누구라는 사람에게서 안부를 전해달라고"+pchar.GenQuest.ShipWreck.Name+". 그를 알아?"; // belamour gen
			link.l1.go = "ShipWreck_51";
		break;
		
		case "ShipWreck_51":
			dialog.text = "전에 그 악당을 목 졸라 죽이지 않은 게 아쉽군. 뭐, 이제 내 관용에 대한 대가를 치를 때가 온 것 같군...";
			link.l1 = "정말이지... 그리고 이제 시간이 다 되어버렸군...";
			link.l1.go = "ShipWreck_52";
		break;
		
		case "ShipWreck_52":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogFree(); // важный метод
			LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheckFunction(LAI_GROUP_BRDENEMY, "ShipWreck_afterCabinFight");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");				
		break;

		case "ShipWreck_53":
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			pchar.quest.ShipWreck_ShipSink.over = "yes";
			dialog.text = "잘했어, 선장! 다 약속한 대로 된 거지? 우리가 배를 가져가고, 너는 화물을 가져가는 거야?";
			link.l1 = "그래. 배를 가져가서 잘 써라.";
			link.l1.go = "exit";

			NextDiag.TempNode = "ShipWreck_53_again";		
			AddDialogExitQuestFunction("ShipWreck_SetShipNew");
		break;
		
		case "ShipWreck_53_again":
			dialog.text = "환영하오, 선장 "+GetFullName(pchar)+".";
			link.l1 = "그래서, 네 배는 마음에 드냐?";
			link.l1.go = "ShipWreck_53_again1";
		break;
		
		case "ShipWreck_53_again1":
			dialog.text = "헤헤, 삐걱거리고 끼익거리는 게 꼭 나 같군. 우리 둘 다 더 이상 바다를 오래 누빌 시간은 별로 안 남은 것 같아...";
			link.l1 = "그럼, 행운을 빌지...";
			link.l1.go = "exit";
			NextDiag.TempNode = "ShipWreck_53_again";		
		break;
		// Генератор "Shipwrecked"
		
		// Генератор "State convicts"
		case "Convict_0End":
			DialogExit();
			pchar.GenQuest.Convict = "close";
			chrDisableReloadToLocation = false;
			ChangeCharacterComplexReputation(pchar,"nobility", -1);
			AddDialogExitQuestFunction("Convict_DialogDisable");
		break;
		
		case "Convict_Begin":					
			switch(sti(pchar.GenQuest.Convict.var))
			{
				case 0:
					dialog.text = "선장님, 제발 우리에게 배나 작은 보트, 타르탄, 뭐든 구해 주십시오. 정말 아무거나 상관없습니다. 우리는 너무나 절박한 상황이라 이 척박한 곳에서 도망쳐야만 합니다. 하지만 정착지에는 갈 수 없습니다.";
					link.l1 = "그래서 그게 대체 어떤 상황인데?";
					link.l1.go = "Convict_11";
				break;
				case 1:
					dialog.text = "선장님, 혹시 우리에게 페소 몇 백만 빌려주실 수 있겠습니까? 부탁드리지 않으려 했지만, 정말 급하게 필요해서 그렇습니다.";
					link.l1 = "급하게 필요하다고? 네가 럼주를 다 마신 거겠지, 그게야말로 정말 급한 일이겠군.";
					link.l1.go = "Convict_12";			
				break;
				case 2:
					pchar.GenQuest.Convict.ToCity = FindColonyWithMayakExceptIsland(GetCharacterCurrentIslandId(pchar));	
					pchar.GenQuest.Convict.Mayak = GetMayakByCityName(pchar.GenQuest.Convict.ToCity);
					dialog.text = "선장님, 저희 보잘것없는 일행을 등대로 데려다주실 수 있겠습니까 "+XI_ConvertString("Colony"+pchar.GenQuest.Convict.ToCity+"Gen")+".";
					link.l1 = "너를 보니 겸손한 사람 같진 않군.";
					link.l1.go = "Convict_13";								
				break;
			}						
			link.l2 = LinkRandPhrase("나는 금요일에는 자선을 베풀지 않아.","이런 헛소리 들을 시간 없어.","나는 모르는 사람은 안 도와.");
			link.l2.go = "Convict_14";
			Convict_GetMineType();
			pchar.GenQuest.Convict.ShoreLocation = SelectQuestShoreLocation();
		break;
		
		case "Convict_11":
			dialog.text = "우린 도망자야... 어디서 왔냐면\n "+GetStrSmallRegister(XI_ConvertString("MineType"+pchar.GenQuest.Convict.MineType+"Gen"))+". 곧 전 주인이 눈치챌 거야... 그러면 우린 진짜로 죽는 거지.";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l1 = "돛 다루는 법은 아는 거냐?";
				link.l1.go = "Convict_11_1";
			}	
			link.l2 = "그럼 뭘로 계산할 건데?";
			link.l2.go = "Convict_11_2";
		break;
		
		case "Convict_12":
			dialog.text = "지금은 우리가 럼 생각할 때가 아니야. 탈출한 지 일주일이 지났고, 이제 우리는 정글에 숨어서 굶주리고 있어.";
			if(sti(pchar.money) >= 3000)
			{
				link.l1 = "그래, 돈을 준다고 치자... 그 다음엔 뭐지? 결국 순찰대한테 들킬 때까지 계속 숨어 있을 거야?";
				link.l1.go = "Convict_12_1";		
				link.l2 = "좋아, 얼마나 필요해?";
				link.l2.go = "Convict_12_2";
			}	
			link.l3 = "너 같은 놈들에게 할 말은 별로 없어—그저 처형대에 머리 올리는 것, 그게 전부다!";
			link.l3.go = "Convict_12_3";
		break;		
		
		case "Convict_12_1":
			if(hrand(1) == 0 && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				dialog.text = "그럼 우리가 뭘 더 할 수 있겠어? 선원 일이라도 기꺼이 하겠지만, 우린 도망자라 누가 우리를 써 주겠냐?";
				link.l1 = "돛을 다룰 줄 알고 겁먹지 않는다면 널 고용하지.";
				link.l1.go = "Convict_12_1_1";
			}
			else
			{
				dialog.text = "우리는 이미 이곳 선원들과 합의를 봤어. 여기서 나가려면 삼천만 더 있으면 돼.";
				link.l1 = "자, 여기 삼천이다. 그게 정말 도움이 된다면 말이지.";
				link.l1.go = "Convict_12_1_2";
			}
			link.l2 = "글쎄, 난 잘 모르겠군... 그건 네 문제니까 내가 해결해 줄 생각 없어.";
			link.l2.go = "Convict_12_1_End"; // выход из локи с закрытием квеста
		break;
		
		case "Convict_12_1_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "제발요, 선장님, 우리를 고용해 주세요, 절대 후회하지 않으실 겁니다! 우리는 함께 해적질을 해왔어요\n "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" 아드리아 해에서, 결국 그는 교수형을 당했고 우리는, "+pchar.GenQuest.Convict.ConvictQty+" 남자들은 이곳으로 추방당했다.";
			link.l1 = "좋아. 근처에 라고 알려진 곳이 있어 "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". 자정쯤에 거기서 널 데리러 갈게. 길 잃지 않길 바란다.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";		
		break;

		case "Convict_12_1_2":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			iTmp = hrand(3);
			if(iTmp <= 1)
			{
				dialog.text = "물론이지, 우리에게 큰 도움이 될 거야! 바람이 좋고 어부들이 실망시키지 않는다면 오늘 출항할 거야. 고마워, 선장. 신의 가호가 있기를...";
				link.l1 = "너도 행운을 빌어.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			if(iTmp == 2)
			{
				dialog.text = "이거야말로 행운이네! 이렇게 빨리 돈을 손에 넣을 줄은 꿈에도 몰랐지. 선장님, 우리 옛 상사에게서 빼앗은 장신구 하나를 드리겠소. 아마 선장님께도 행운을 가져다줄 거요.";
				link.l1 = "고맙다, 그거 참 괜찮은 일이네. 행운을 빌어.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			if(iTmp == 3)
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "이제 여기 돈을 쓸 줄 아는 통 큰 사내가 있구만, 돈 버는 법도 잘 아니까 겁낼 필요도 없지!\n어젯밤에 우리는 이 동네 밀수꾼들이 짐을 싣는 걸 봤어 "+MerPrm.QuestGoodsIdx+". 어두웠지만, 우리는 보트 중 하나 옆면에 적힌 배 이름을 간신히 알아볼 수 있었어, '"+MerPrm.ShipName+"... 그리고 그 배는 ... 깃발 아래에서 항해 중이다 "+MerPrm.nation+"이 정보가 쓸모 있을지도 모르겠군, 히히.";			
				link.l1 = "흠... 뭐, 그럴지도 모르지. 잘 가라, 추적자들아.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");			
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}
		break;
		
		case "Convict_12_2":
			dialog.text = "이런, 우리가 요구할 처지가 아니지. 뭐든지 줄 수 있는 것이라면, 뭐든 감사히 받겠어.";
			link.l1 = "300 페소.";
			link.l1.go = "Convict_12_2_1";
			link.l2 = "1000 페소.";
			link.l2.go = "Convict_12_2_2";
			link.l3 = "3,000 페소.";
			link.l3.go = "Convict_12_2_3";
		break;
		
		case "Convict_12_2_1":
			addMoneyToCharacter(pchar, -300);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
			dialog.text = "고맙소, 선장님, 신의 가호가 함께하길...";
			link.l1 = "너도 행운을 빌어.";
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_2":
			addMoneyToCharacter(pchar, -1000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 40);
			if(hrand(1) == 0)
			{
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				dialog.text = "이거야말로 행운이로군! 이렇게 빨리 돈을 손에 넣을 줄은 꿈에도 몰랐지. 선장님, 우리 옛 상사에게서 빼앗은 장신구 하나를 드리겠소. 아마 선장님께도 행운을 가져다줄 거요.";
				link.l1 = "고맙다, 그거 참 괜찮은 짓이었어. 행운을 빌지.";
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 20);
			}
			else
			{
				dialog.text = "감사합니다, 선장님, 신의 가호가 함께하길...";
				link.l1 = "너도 행운을 빌어.";
			}
			link.l1.go = "exit";
			pchar.GenQuest.Convict = "close";
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;

		case "Convict_12_2_3":
			addMoneyToCharacter(pchar, -3000);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Commerce", 60);
			if(hrand(1) == 0)
			{
				dialog.text = "이거야말로 행운이로군! 이렇게 빨리 돈을 손에 넣을 줄은 꿈에도 몰랐지. 선장님, 우리 옛 상사에게서 빼앗은 장신구 하나를 드리겠습니다. 아마 선장님께도 행운을 가져다줄지 몰라요.";
				link.l1 = "고맙다, 그거 참 괜찮은 짓이었어. 행운을 빌지.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Fortune", 30);
			}
			else
			{
				pchar.GenQuest.Find_Merchant.lastspeak_date = LastSpeakDate();
				GenerateMerchant();
				makeref(MerPrm, MerchantParam);
				dialog.text = "이제 여기 돈을 쓸 줄 아는 통 큰 사내가 있군, 돈 버는 법도 아는 놈이지!\n어젯밤에 우리는 이 동네 밀수꾼들이 짐을 싣는 걸 봤어 "+MerPrm.QuestGoodsIdx+". 어두웠지만, 우리는 보트 중 하나 옆면에 적힌 배 이름을 알아낼 수 있었어 '"+MerPrm.ShipName+"... 그리고 그 배는 ... 깃발 아래 항해하고 있어 "+MerPrm.nation+". 아마 이 정보가 쓸모 있을지도 모르겠군, 크크.";
				link.l1 = "흠... 뭐, 그럴지도 모르지. 잘 있어라, 추적자들아.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "7");
				AddQuestUserData("Convict", "sShipName", MerPrm.ShipName);
				AddQuestUserData("Convict", "sGoodName", MerPrm.QuestGoodsIdx);				
				CloseQuestHeader("Convict");
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
				AddCharacterExpToSkill(pchar, "Sneak", 30);
			}			
		break;
		
		case "Convict_12_1_End":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");	
			pchar.GenQuest.Convict = "close";
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_12_3":
			if(hrand(1) == 0)
			{
				dialog.text = "우리를 화로 몰아넣지 마시오, 선장님! 값진 장신구가 있으니, 제발 몸값으로 받아주시고 우리를 놓아주시오...";
				link.l1 = "그럼 내놔, 그리고 아직 기회 있을 때 꺼져라.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "이제 달리 선택지가 없다, 사람은 두 번 죽지 않아. 마지막 전투다, 녀석들아!";
				link.l1 = "그건 또 다른 이야기지!";
				link.l1.go = "Convict_Fight";
			}			
		break;
		
		case "Convict_13":
			dialog.text = "글쎄, 우리야 성인군자는 아니지만, 괜히 시비 걸 생각은 없어... 우리는 도망자라서 최대한 빨리 여기서 빠져나가야 해.";
			link.l1 = "통행료로 낼 만한 거 있냐?";
			link.l1.go = "Convict_13_1";		
			link.l2 = "아, 그렇군... 아니, 너 때문에 내 명성에 흠집을 낼 생각은 없어. 잘 가라.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_1":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "알겠어! 우린 이런 승선전투 같은 건 익숙하지. 거의 2년 동안 우리랑 고인이 된 "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" 지역 상인들을 공포에 떨게 했지만, 아아! 그는 교수형을 당했고, "+pchar.GenQuest.Convict.ConvictQty+" 우리 중 몇몇 놈들은 강제 노역형을 선고받았지.";
			link.l1 = "내 선원으로 들어올래? 나 후한 편이야"+GetSexPhrase("","")+", 하지만 평온한 삶을 약속할 수는 없어.";
			link.l1.go = "Convict_11_3";			
		break;
		
		case "Convict_11_2":
			dialog.text = "그래, 우리는 뭔가를 손에 넣었지 "+GetStrSmallRegister(XI_ConvertString("MineType"+pchar.GenQuest.Convict.MineType+"Gen"))+", 그러니 우리는 두 배로 지불할 수 있지. 그러니 가격은 합의된 걸로 믿는다. 그리고 감히 경비들을 데려오지 마라. 배신은 용서하지 않으니까..."; // belamour gen
			link.l1 = "좋아, 해변에서 기다려 "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Gen")+". 자정 가까워지면 너를 위한 보트가 올 거야... 그리고 꼼수 부리는 거 절대 보고 싶지 않아!"; // belamour gen
			link.l1.go = "Convict_11_4";
			link.l2 = "아니, 친구들아. 내가 너희에게 배를 넘겨주면 너희가 내 등을 칼로 찌를 수도 있잖아? 안 돼, 이 일에는 도와주지 않겠다.";
			link.l2.go = "Convict_11_5";
		break;
		
		case "Convict_11_3":
			dialog.text = "기꺼이, "+GetSexPhrase("나리","아가씨")+" 선장. 그런 건 우리도 잘 알고 있지, 그리고 그런 평판으로는 해군에 받아줄 리도 없으니까, 헤헤.";
			link.l1 = "알겠어. 근처에 라고 알려진 곳이 있어 "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". 자정이 지나면 거기서 널 데리러 갈게. 길 잃지 않길 바란다.";
			link.l1.go = "Convict_11_6";
		break;
		
		case "Convict_11_4":
			dialog.text = "하지만, "+GetSexPhrase("나리","아가씨")+" 선장, 우리 더 큰 위험을 감수하는 거 아니야? 만약 선장이 우리를 사령관한테 넘기기로 마음먹으면 어쩌지?";
			link.l1 = "그렇지... 좋아, 내가 새벽까지 안 가면 거래는 취소다.";
			link.l1.go = "Convict_11_7";			
		break;
		
		case "Convict_11_5":
			if(makeint(pchar.reputation.nobility) < 11 || makeint(pchar.reputation.nobility) > 79) //макс. репутатция 90
			{
				dialog.text = "아이고, 선장님, 우리는 당신만 믿고 있었는데...";
				link.l1 = "문제없어. 돈만 있으면 탈 배는 찾을 수 있지. 잘 가라.";
				link.l1.go = "exit";
				pchar.GenQuest.Convict = "close";
				ChangeCharacterComplexReputation(pchar,"nobility", -2);
				AddDialogExitQuestFunction("Convict_DialogDisable");
				AddDialogExitQuest("OpenTheDoors");
			}
			else
			{
				dialog.text = "영악하군, 선장. 딱 보면 알지. 분명히 곧장 사령관한테 달려갈 거잖아, 안 그래? 그리고 그걸로 무사히 넘어갈 수 있을 거라고 진짜 생각해?";
				link.l1 = "그래서 나를 막을 생각이냐, 보아하니?! 그럼 네놈도 당할 만큼 당해봐라!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "fight";
			}	
		break;
		
		case "Convict_11_6":
			pchar.GenQuest.Convict = "ToShore";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "1");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen"));	// belamour gen	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);	
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_11_7":
			pchar.GenQuest.Convict = "GetShip";
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "2");		
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Acc"));					
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();		
			AddDialogExitQuestFunction("Convict_DialogDisable");		
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_13_1":
			pchar.GenQuest.Convict.Sum = (sti(pchar.rank)+10)*100+1000;
			dialog.text = "뭔가 있긴 해. 우리 두목 금고를 뒤졌는데, 그 일로 소란이 벌어져서 싸우면서 빠져나와야 했지. 오직\n "+PChar.GenQuest.Convict.ConvictQty+" 놈들이 살아남았어.";
			link.l1 = "상황이 이러하니, 그 이하로는 태워줄 수 없어 "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+" 인당 페소.";
			link.l1.go = "Convict_13_2";
			if(GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty) && GetPassengersQuantity(pchar) < PASSENGERS_MAX)
			{
				link.l2 = "겁쟁이들이 아니구만. 내 선원으로 들어올래?";
				link.l2.go = "Convict_13_3";
			}
		break;
		
		case "Convict_13_2":
			dialog.text = "우리가 선택권이 있나? 좋아, "+FindRussianMoneyString(sti(pchar.GenQuest.Convict.Sum))+"...";
			link.l1 = "그럼 가라 "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation+"Dat")+". 자정이 지나면 너를 데리러 배를 보내겠다."; // belamour gen 
			link.l1.go = "Convict_13_4";
			pchar.GenQuest.Convict = "ToMayak";
			pchar.GenQuest.Convict.Sum = sti(pchar.GenQuest.Convict.Sum) * sti(pchar.GenQuest.Convict.ConvictQty);
		break;
		
		case "Convict_13_3":
			pchar.GenQuest.Convict.PirateName = "l" + rand(GetNamesCount(NAMETYPE_NICK) - 1);
			dialog.text = "왜 안 되겠어? 우리 그거 잘 알지, 같이 해적질도 했잖아\n "+GetName(NAMETYPE_NICK,pchar.GenQuest.Convict.PirateName,NAME_ABL)+" 안에 "+RandPhraseSimple("Gibraltar","영국 해협")+" 우리가 여기 갇히기 전에.";
			link.l1 = "좋아. 근처에 라고 불리는 곳이 있어 "+XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation)+". 자정쯤에 거기서 널 데리러 갈게. 길 잃지 않길 바란다.";
			link.l1.go = "Convict_11_6";
			pchar.GenQuest.Convict = "ToShore";
		break;
		
		case "Convict_13_4":
			ReOpenQuestHeader("Convict");
			AddQuestRecord("Convict", "8");					
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));		
			AddQuestUserData("Convict", "sIslandType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Convict.city) + "Gen"));
			AddQuestUserData("Convict", "sConvictNum", Convict_GetStringNum(sti(pchar.GenQuest.Convict.ConvictQty))); // belamour gen колво прописью
			AddQuestUserData("Convict", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Convict.ToCity + "Gen"));
			AddQuestUserData("Convict", "sSum", pchar.GenQuest.Convict.Sum);
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Dat"));	// belamour gen	 	
			SetFunctionTimerCondition("Convict_SetTimerMeet", 0, 0, 1, false);
			locations[FindLocation(pchar.GenQuest.Convict.ShoreLocation)].DisableEncounters = true;			
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
				
		case "Convict_14":
			dialog.text = RandPhraseSimple(RandPhraseSimple("이봐, 선장, 너도 한때는 가난했잖아, 주머니에 아무것도 없었지. 그런데 이제 와서 우리 같은 평민을 깔보는 거냐.","선장님, 평민들을 이렇게 대하는 건 옳지 않소. 우리 모두 같은 신 아래에 있지 않소."),RandPhraseSimple("헤, 요즘 사람들 정말 너무 이기적이야. 마치 앞으로도 이백 년은 더 살 것처럼 굴더라.","오, 보아하니 유럽에서 막 도착했군. 아직 우리 이 열대 쓰레기장의 악취는 못 맡아봤겠지."));
			link.l1 = LinkRandPhrase("나를 망신시키려는 거냐? 네 혓바닥을 몇 치는 잘라버릴 거다!","나 겁주려고 하는 거야? 모자 잘 잡아!","너 철학자라도 되냐? 내가 정신 차리게 두들겨줄게!");
			link.l1.go = "Convict_Fight";	
			pchar.GenQuest.Convict = "fight";
		break;
		
		case "Convict_Fight":
			LAi_SetPlayerType(pchar);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);	 
			LAi_LockFightMode(pchar, false); 
			LAi_SetFightMode(pchar, true);
			chrDisableReloadToLocation = true;
			iTemp = sti(PChar.GenQuest.Convict.ConvictQty);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID("Convict_" + i);
				DeleteAttribute(rChar, "City");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, "ConvictGroup");
				LAi_SetImmortal(rChar, false);
			}
			LAi_group_SetRelation("ConvictGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("ConvictGroup", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("ConvictGroup", "OpenTheDoors"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "Convict_15":
			dialog.text = LinkRandPhrase("그래서, 선장? 우리한테 배 구했어?","안녕, 선장. 그래서, 우리 거래는 어떻게 된 거야?","안녕하세요, 선장님. 우리가 걱정하기 시작했었소. 모든 일이 잘 끝난 것 같군요?");
			if(Convict_CheckShipType(SHIP_TARTANE) || Convict_CheckShipType(SHIP_WAR_TARTANE))
			{
				link.l1 = "그래, 여기 네 배야. 그리고 돈 잊지 마라. 내가 냈으니까. "+pchar.GenQuest.Convict.ShipPrice+" 그걸 위해 동전을 썼으니, 너 나한테 빚진 거야 "+sti(pchar.GenQuest.Convict.ShipPrice)* 2+", 우리가 약속한 대로.";
				link.l1.go = "Convict_15_1";
			}	
			link.l2 = "아니, 마음이 바뀌었어. 다른 놈을 구해. 잘 있어...";
			link.l2.go = "Convict_15_2";
		break;
		
		case "Convict_15_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "물론이지! 놈들이 우리 자유는 빼앗았지만, 양심까지는 못 뺏었어! 이 돈과 함께 우리의 한없는 감사도 받아 주시오. 정말 큰 도움을 받았어. 혹시 은괴로 보상해도 괜찮겠소?";
					link.l1 = "당연히 몰라. 여행 잘 다녀와라. 그리고 바다에서 나랑 마주치지 않게 기도나 해라, 만나면 바로 끝장내줄 테니까.";
					link.l1.go = "Convict_15_1_1End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Commerce", 30);
					TakeNItems(pchar, "jewelry6", makeint(sti(pchar.GenQuest.Convict.ShipPrice)/50));
				break;
				case 2:
					dialog.text = "선장, 있잖아, 우리 생각해보니까 인생에서 돈이 그렇게 중요한 건 아니더라고. 솔직히 지금은 우리가 선장보다 돈이 훨씬 더 필요해. 그런데 우리 전 상사한테서 훔친 게 하나 있어. 아마 금보다 선장한테 더 흥미로울지도 몰라. 한번 볼래?…";
					link.l1 = "그래, 네 말이 맞아. 정말 멋진 일이군. 좋아, 알겠어, 거래하자. 고맙다, 잘 가라.";
					link.l1.go = "Convict_15_1_2End";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Fortune", 30);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
				break;
				case 3:
					pchar.GenQuest.Convict = "FightInShore";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					dialog.text = "그렇게 많은 돈이 대체 왜 필요해, 선장? 어차피 넌 부자잖아, 그리고 우린 이 배를 못 얻으면 끝장이야. 그러니까... 그냥 네 돈을 뺏을 거야. 섭섭하게 생각하진 마.";
					link.l1 = "그게 네 마지막 실수였어. 배 없이도 아직은 헤엄쳐 도망칠 수 있었겠지만, 이제는 떠오르거나 가라앉는 수밖에 없어.";
					link.l1.go = "Convict_Fight";
					AddCharacterExpToSkill(pchar, "Leadership", 30);
					AddCharacterExpToSkill(pchar, "Sneak", 30);
				break;
			}
		break;
	
		case "Convict_15_1_1End":
			AddQuestRecord("Convict", "4");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;
	
		case "Convict_15_1_2End":
			AddQuestRecord("Convict", "5");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sShoreName", XI_ConvertString(pchar.GenQuest.Convict.ShoreLocation + "Gen")); // belamour gen
			CloseQuestHeader("Convict");
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuestFunction("Convict_SetConvictToShip");
			AddDialogExitQuest("OpenTheDoors");
			DialogExit();
		break;	
	
		case "Convict_15_2":
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");
			for(i = 0; i < sti(pchar.GenQuest.Convict.ConvictQty); i++)
			{
				sld = CharacterFromID("Convict_" + i);
				sld.LifeDay = 0;
			}	
			ChangeCharacterComplexReputation(pchar,"nobility", -2);	
			LAi_group_Delete("ConvictGroup");
			DeleteAttribute(pchar, "GenQuest.Convict");
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16":
			dialog.text = RandPhraseSimple("그래, 선장? 이제 짐 싣기 시작해도 되나?","드디어 왔군! 우리 걱정하기 시작했었어, 네가 마음을 바꾼 줄 알았지.");
			link.l1 = "미안하지만, 계획이 바뀌었어. 이제 다른 선장을 찾아봐야 할 거야.";
			link.l1.go = "Convict_16_1";
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				link.l2 = "배에 타, 나 시간 별로 없어.";
				link.l2.go = "Convict_16_2";			
			}			
			if(pchar.GenQuest.Convict == "ToShore" && GetFreeCrewQuantity(pchar) >= sti(pchar.GenQuest.Convict.ConvictQty))
			{
				link.l2 = "배에 타, 나 시간 별로 없어.";
				link.l2.go = "Convict_16_2";			
			}			
		break;
		
		case "Convict_16_1":
			if(rand(1) == 0)
			{
				dialog.text = "젠장할 놈! 분명히 우리 뒤쫓으라고 순찰대를 보냈겠지?! 이대로 넘어갈 줄 알지 마!";
				link.l1 = "무슨 소리야?! 죽고 싶어서 이래?!";
				link.l1.go = "Convict_Fight";
				pchar.GenQuest.Convict = "ShoreFight";
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			else
			{
				dialog.text = "Captain "+GetSexPhrase(", 너 약속을 지키는 놈이냐 아니냐?","?")+" 아니면 그냥 피투성이 수다쟁이냐...";
				link.l1 = "혀 조심하는 게 좋을 거다...";
				link.l1.go = "Convict_16_3";
			}
		break;
		
		case "Convict_16_2":
			if(pchar.GenQuest.Convict == "ToShore")
			{
				AddCharacterExpToSkill(pchar, "Leadership", 30);
				AddCharacterCrew(pchar, sti(pchar.GenQuest.Convict.ConvictQty));
				OfficersReaction("bad");
				pchar.GenQuest.Convict = "close";
				AddQuestRecord("Convict", "10");
				CloseQuestHeader("Convict");				
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			}
			if(pchar.GenQuest.Convict == "ToMayak")
			{
				AddQuestRecord("Convict", "10");
				sld = characterFromId("Convict_0");
				AddPassenger(pchar, sld, false);
				SetCharacterRemovable(sld, false); 
				SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
				SetFunctionLocationCondition("Convict_OnMayak", pchar.GenQuest.Convict.Mayak, true);
				locations[FindLocation(pchar.GenQuest.Convict.Mayak)].DisableEncounters = true;			
			}
			DialogExit();
			AddDialogExitQuestFunction("Convict_DialogDisable");
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_16_3":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			OfficersReaction("bad");
			pchar.GenQuest.Convict = "close";
			AddQuestRecord("Convict", "3");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Convict");				
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			AddDialogExitQuestFunction("Convict_DialogDisable");			
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
						
		case "Convict_17":
			dialog.text = LinkRandPhrase("오, 고마워, "+GetSexPhrase("친절한 남자","고운 아가씨")+".","고맙소, 선장님. 정말로 교수대에서 날 구해주셨소.","이렇게 훌륭한 항해, 정말 고맙다.");
			link.l1 = LinkRandPhrase("그런 건 다 좋은데, 나는 돈을 기다리고 있어.","이제 돈 낼 때다, 알지?","약속한 대로 현찰로 바로 내놔.");
			link.l1.go = "Convict_17_1";
		break;
		
		case "Convict_17_1":
			switch(sti(pchar.GenQuest.Convict.variant))
			{
				case 1:
					dialog.text = "물론이지, 무슨 질문이겠어! 여기 금괴로 네 돈이야, 그리고 우리의 진심 어린 감사를 받아 줘.";
					link.l1 = "너도 행운을 빌어. 잘 가라.";
					link.l1.go = "Convict_17_1_1End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Commerce", 80);
					TakeNItems(pchar, "jewelry5", makeint(sti(pchar.GenQuest.Convict.Sum)/200));
					break;
				case 2:
					dialog.text = "선장, 있잖아, 우리 생각해보니까 돈이란 게 인생에서 그렇게 중요한 건 아니더라고. 솔직히 말해서, 지금은 우리가 선장보다 훨씬 더 필요해. 그런데 우리 옛 상사한테서 훔친 게 하나 있어. 금보다 훨씬 더 선장님이 관심 가질 만한 물건일지도 몰라. 한번 볼래?…\n";
					link.l1 = "그래, 네 말이 맞아. 정말 멋진 일이군. 좋아, 됐다, 거래하자. 고맙고, 안녕히 가라.";
					link.l1.go = "Convict_17_1_2End";
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Fortune", 80);
					GiveItem2Character(pchar, pchar.GenQuest.Convict.Item);
					break;
				case 3:
					dialog.text = "왜 그렇게 많은 돈이 필요해? 너 원래 부자잖아. 네가 우리를 도왔으니, 다음엔 우리가 너를 도와줄게.";
					link.l1 = "그런 기회는 없을 거다. 기도나 해라, 이 악당들아. 나는 빚을 용서하지 않는다.";
					link.l1.go = "Convict_Fight";
					pchar.GenQuest.Convict = "MayakFight";
					SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);				
					AddCharacterExpToSkill(pchar, "Sailing", 80);
					AddCharacterExpToSkill(pchar, "Sneak", 80);			
					break;
			}
		break;
		
		
		case "Convict_17_1_1End":
			AddQuestRecord("Convict", "11");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	//belamour gen			
			AddQuestUserData("Convict", "sSum", makeint(pchar.GenQuest.Convict.Sum));
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;
		
		case "Convict_17_1_2End":
			AddQuestRecord("Convict", "12");
			AddQuestUserData("Convict", "sSex", GetSexPhrase("",""));
			AddQuestUserData("Convict", "sMayak", XI_ConvertString(pchar.GenQuest.Convict.Mayak + "Dat"));	// belamour gen	
			CloseQuestHeader("Convict");
			pchar.GenQuest.Convict = "close";
			SetFunctionExitFromLocationCondition("Convict_LocExit", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("OpenTheDoors");
		break;		
		// <-- Генератор "State convicts"
		
		// Генератор "A reason to hurry" -->
		// Встреча с ОЗГ на берегу
		case "ReasonToFast_Hunter1":
			dialog.text = "여기로 보낸 사람은 "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 자기 자신을...";
			link.l1 = GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+" 이미 몇 시간째 당신을 기다리며 답장을 준비하고 있었어. 당신이 떠나자마자 나를 보냈지.";
			link.l1.go = "ReasonToFast_Hunter4";
		break;
		
		case "ReasonToFast_Hunter2":
			dialog.text = "꽤 오랫동안 네 뒤를 쫓아왔는데, 네가 너무 빠르더라.";
			link.l1 = "그래서 어쩌라고?";
			link.l1.go = "ReasonToFast_Hunter6";		
		break;
		
		case "ReasonToFast_Hunter3":
			dialog.text = "차라리 총독이 부하들한테 얼마를 주는지 말해 보시지?";
			link.l1 = "젠장!";
			link.l1.go = "ReasonToFast_Fight";		
		break;
		
		case "ReasonToFast_Hunter4":
			dialog.text = "나 술 안 마셨어! 갑판장 찾고 있었을 뿐이야...";
			link.l1 = "이제 가... 내가 말해줄게 "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_DAT)+", 네가 정글에서 실종됐다는 거야.";
			link.l1.go = "ReasonToFast_Hunter5";		
			AddQuestRecord("ReasonToFast", "5");
			AddQuestUserData("ReasonToFast", "sName", GetName( NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN));
		break;
		
		case "ReasonToFast_Hunter5":
			LAi_SetPlayerType(pchar);
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_HunterGoOut");
		break;
		
		case "ReasonToFast_Hunter6":
			pchar.questTemp.ReasonToFast = "MeetHunterFail";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("ReasonToFast_PatrolAngry");
		break;
		
		case "ReasonToFast_Fight":
			LAi_SetPlayerType(pchar);
			pchar.questTemp.ReasonToFast = "PatrolAngry";
			pchar.questTemp.ReasonToFast.relation = GetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation));
			SetNationRelation2MainCharacter(sti(pchar.questTemp.ReasonToFast.GuardNation), RELATION_ENEMY); 
			pchar.GenQuest.HunterScore2Pause = 1; //НЗГ не начисляются
			pchar.GenQuest.ReputationNotChange = 1; //репутацию не менять
			sTemp = "Patrol" + pchar.questTemp.ReasonToFast.LocIdx + "_";
			sGroup = "PatrolGroup_" + pchar.questTemp.ReasonToFast.LocIdx;
			LAi_LocationFightDisable(&locations[FindLocation(pchar.questTemp.ReasonToFast.PatrolLocation)], false);	
			iTemp = sti(pchar.questTemp.ReasonToFast.PatrolNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("ReasonToFast_Hunter");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheck(sGroup, "ReasonToFast_PatrolDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		// бой с кэпом пиратского корабля
		case "ReasonToFast_FightCap": 
			dialog.text = "그리고 너 제법 똑똑하군. 네 수작이 들키지 않도록 신께 기도나 해라 "+GetName(NAMETYPE_MAIN,pchar.questTemp.ReasonToFast.p3,NAME_NOM)+".";
			link.l1 = "네가 말하지 않으면 그는 모를 거야... 그리고 너, 말 안 할 거지?";
			link.l1.go = "ReasonToFast_FightCap_1";
		break;
		
		case "ReasonToFast_FightCap_1":
			dialog.text = "왜? 당연히 하지, 아주 기꺼이!";
			link.l1 = "어차피 그 바보짓 때문에 넌 교수형 당할 거야. 그러니 시간 낭비하지 말고, 내가 널 교수대에서 도망치게 도와줄게.";
			link.l1.go = "ReasonToFast_FightCap_2";
		break;
		
		case "ReasonToFast_FightCap_2":
			dialog.text = "흠... 그래서 그걸 어떻게 할 건데?";
			link.l1 = "내가 직접 널 죽여주지...";
			link.l1.go = "ReasonToFast_FightCap_Last";
		break;
		
		case "ReasonToFast_FightCap_Last":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;		
		
		// встреча с лакеем в резиденции
		case "ReasonToFast_Lakey":
			dialog.text = "여기서 볼일 있나, "+GetSexPhrase("나리","아가씨")+"?";
			link.l1 = "아니, 아니오, 나는 총독의 매력적인 부인께 초대를 받아 이곳에 왔소. 이 정말 호화로운 저택을 감탄하며 구경하고 있던 중이오.";
			link.l1.go = "ReasonToFast_Lakey1";
			link.l2 = "네가 아는 사람들에게서 전갈이 왔어.";
			link.l2.go = "ReasonToFast_Lakey2";
			link.l3 = "그래. 널 법의 심판대에 세우고 싶어!";
			link.l3.go = "ReasonToFast_Lakey3";
			pchar.questTemp.ReasonToFast = "MeetLakey";
			pchar.questTemp.ReasonToFast.SpeakOther = true;			
		break;
		
		case "ReasonToFast_Lakey1":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "그래, 이렇게 아름다운 집에서 일할 수 있었던 건 정말 행운이었지.";
			link.l1 = "어쩐지...";
			link.l1.go = "ReasonToFast_Lakey11";
		break;

		case "ReasonToFast_Lakey11":
			NextDiag.TempNode = "ReasonToFast_Lakey11";
			dialog.text = "우리 정원도 꼭 둘러보는 거 잊지 마!";
			link.l1 = "고맙다, 이봐!";
			link.l1.go = "exit";			
			bDisableFastReload = false;
		break;
		
		case "ReasonToFast_Lakey2":
			dialog.text = "에이... "+pchar.questTemp.ReasonToFast.password+"?";
			link.l1.edit = 1;			
			link.l1 = ""; 
			link.l1.go = "ReasonToFast_Lakey21";
		break;

		case "ReasonToFast_Lakey3":
			dialog.text = "이대로 넘어갈 줄 알았냐, 배신자!";
			link.l1 = "가만히 있어, 이 악당놈아!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;			
		break;

		case "ReasonToFast_Lakey21":
			if(GetStrSmallRegister(pchar.questTemp.ReasonToFast.ShipName) == GetStrSmallRegister(dialogEditStrings[1]))
			{
				dialog.text = "빨리 해! 값진 건 다 챙기고 도망쳐!";
				link.l1 = "너도 도망치는 게 좋을 것 같다.";
				link.l1.go = "ReasonToFast_Lakey_exit";
				TakeNItems(pchar,"icollection", sti(pchar.questTemp.ReasonToFast.p8));
				TakeNItems(pchar,"Chest", sti(pchar.questTemp.ReasonToFast.p7));
				pchar.questTemp.ReasonToFast = "LakeyExitSuccess";					
				bDisableFastReload = true;		
				//chrDisableReloadToLocation = true;			
			}
			else
			{
				dialog.text = "음, 실례지만, 이만 가봐야겠어.";
				link.l1 = "가만히 있어, 이 악당 놈아!";
				link.l1.go = "ReasonToFast_Lakey_exit";
				pchar.questTemp.ReasonToFast = "LakeyExitFail";
				bDisableFastReload = false;
			}			 
		break;

		case "ReasonToFast_Lakey_exit":
			DialogExit();	
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			pchar.quest.ReasonToFast_ClearLakey.over = "yes"; //снимаем таймер
			ReasonToFast_SetHunterCoastal();
			AddDialogExitQuest("ReasonToFast_LakeyGoOut");
		break;		
		
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("너는 "+GetSexPhrase("도둑이군! 경비병들, 저 놈 잡아라","도둑이군! 경비병들, 저 여자 잡아!")+"!","믿을 수가 없군! 잠깐 한눈판 사이에 내 궤짝을 뒤지고 있잖아! 도둑이야, 잡아라!","이봐, 경비병들! 도둑이야! 저 도둑 잡아라!");
			link.l1 = "아아악, 악마 놈!";
			link.l1.go = "ReasonToFast_Lakey_exit";
			pchar.questTemp.ReasonToFast = "LakeyExitFail";
			bDisableFastReload = false;
		break; 
		// Генератор "A reason to hurry" <--
		
		// ситуации с капитаном захваченного корабля
		// взрыв на корабле
		case "ShipSituation11": // пираты или ДУ
			dialog.text = RandPhraseSimple("안녕, "+GetSexPhrase("동료","아가씨")+"! 너한테 깜짝 선물을 준비했지, 화약고에 도화선에 불을 붙였어. 곧 산산조각 날 거야!","거기서 뭐하고 있어? 화약고에 불이 났어! 곧 폭발할 거고, 그 불꽃놀이는 유럽에서도 보이겠어!");
			link.l1 = RandPhraseSimple("이 악당아, 날 속일 수 있을 거라 생각하지 마라! 싸워라, 이 겁쟁이 놈아!","배에서 쥐들이 도망치는 걸 보니, 너도 제일 먼저 달아나는 놈 중 하나냐?");
			link.l1.go = "ShipSituation12";
		break;
		
		case "ShipSituation12":
			dialog.text = RandPhraseSimple("너도 목숨이 아깝다면 도망치는 게 좋을 거야... 뭐, 난 시간이 없어. 배가 날 기다리고 있거든. 낚시나 실컷 즐겨!","영웅 놀이할 시간 없어, 배에 있는 녀석들이 날 기다리고 있거든. 낚시 잘 해라, 이긴 놈!");
			link.l1 = RandPhraseSimple("젠장! 방지판 잘라! 밧줄 풀어!","아이고, 이런 엉망진창에 어떻게 빠진 거야! 바닷길을 열어라! 물러서!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation21": // военный корабль (не флагман)
			dialog.text = "그래서 뭐?! 네가 이긴 줄 알아?! 천만에. 나는 화약고에 불질렀으니, 넌 이 배에서 살아나가지 못할 거다.";
			link.l1 = RandPhraseSimple("이 악당아, 나를 속일 수 있을 거라 생각하지 마라! 싸워라, 이 겁쟁이야!","배를 버리고 도망치는 쥐새끼들이 보이는데, 네가 제일 먼저냐?");
			link.l1.go = "ShipSituation22";
		break;
		
		case "ShipSituation22":
			dialog.text = RandPhraseSimple("나는 맹세에 묶여 있지만, 그렇다고 헛되이 죽어야 하는 건 아니지. 미안하지만 너한테 배에 탈 자리를 내주지 않은 건, 선원들이 이해하지 못할 거라서 그래.","배들이 접현해서 네 운명은 이미 결정됐어. 미안하지만, 내 보트가 기다리고 있거든...");
			link.l1 = RandPhraseSimple("젠장! 방지판 잘라! 출항해!","아이고, 이런 엉망진창에 어떻게 빠진 거야!\n바닷길을 열어라!\n물러서!");
			link.l1.go = "ShipSituation_End";
		break;
		
		case "ShipSituation31": // ОЗГ
			dialog.text = RandPhraseSimple("네가 이겼군! 지옥에 온 걸 환영하지! 내가 화약고에 불을 질렀다.","여기 있다, 이봐 좋은 친구! 그리고 끝났어; 내가 화약고에 불을 질렀지.");
			link.l1 = RandPhraseSimple("이 악당아, 나를 속일 수 있을 줄 알았냐! 싸워라, 이 겁쟁이 놈아!","배를 버리고 도망치는 쥐새끼들이 보이는데, 너도 제일 먼저 도망치는 놈 중 하나냐?");
			link.l1.go = "ShipSituation32";
		break;
		
		case "ShipSituation32":
			dialog.text = RandPhraseSimple("꽤 오랫동안 너를 쫓고 있었지. 내 배를 희생해야 해서 아쉽지만, 네 목값이면 새 배 두 척은 살 수 있으니까. 낚시나 실컷 해라!","어떻게 갈 건데? 불꽃놀이 터뜨리면서, 인도 왕자처럼?"+GetSexPhrase("ce","세스")+". 하지만 내가 패배자로 보이진 않을 거다; 네 목이 내 배보다 훨씬 더 값지거든. 이제 작별이다, 내 보트가 오래 기다려주진 않을 테니까...");
			link.l1 = RandPhraseSimple("젠장! 방지판 잘라! 닻 풀어!","오, 맙소사, 우리가 어떻게 이런 꼴이 된 거지!\n바닷길을 열어라!\n물러서!");
			link.l1.go = "ShipSituation_End";			
		break;
		
		case "ShipSituation_End":
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			NPChar.LifeDay = 0;
			LAi_LockFightMode(pchar, false);	
			Log_Info(XI_ConvertString("Ship can explode"));
			pchar.GenQuest.ShipSituation.Explosion = ShipSituation_4;	
			pchar.GenQuest.ShipSituation.Explosion.CapId = NPChar.CaptanId;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		
		// эпидемия
		case "ShipEpidemy1":
			AddCharacterExpToSkill(pchar, "Fortune", 200);
			dialog.text = RandPhraseSimple("잠깐만요, 선장님! 말 좀 하자.","잠깐만요, 선장님! 이게 선장님께 흥미로울 것 같은데요.");
			link.l1 = LinkRandPhrase("싸움 중에 왜 말을 하고 있어?!","죽은 자와 내가 무슨 이야기를 해야 한단 말이냐?","뭐야? 내 이름으로 유언장이라도 쓰려고?");
			link.l1.go = "ShipEpidemy2";
		break;
		
		case "ShipEpidemy2":
			dialog.text = "배 안에 병이 돌고 있어. 항해 중에 내 선원 중 4분의 1을 잃었지. 너희 모두 끝장이야...";
			link.l1 = RandPhraseSimple("이 썩어빠진 놈아! 네 배에 사고가 났으면 왜 신호를 보내지 않았어?!","바다 규율을 잊었나? 네 배에 재난이 닥쳤으면 돛대에 신호를 올렸어야지!");
			link.l1.go = "ShipEpidemy3";
		break;
		
		case "ShipEpidemy3":
			dialog.text = "우린 어차피 곧 죽을 운명이었지. 그래서 포기하지 않았던 거다, 너랑 네 악마들을 저세상으로 끌고 가고 싶었으니까! 이제야 완전히 만족한다. 네 더러운 짓, 마저 해라.";
			link.l1 = RandPhraseSimple("그 값 반드시 치르게 해주지!..","네가 먼저 죽는다는 생각, 마음에 드는군. 그리고 나는 지켜볼 거야.");
			link.l1.go = "ShipEpidemy31";
			link.l2 = RandPhraseSimple("내 칼에 네 더러운 피를 묻히진 않겠다. 살아도 된다, 하지만... 뭐 하려고? 난 내 선원들을 그 썩은 낡은 배에서 데리고 나간다.","그 일로 교수대에 보내야 마땅하지만, 지금은 그럴 필요 없다. 나는 내 부하들을 데리고 떠난다... 넌 살아남을 수 있겠지만, 네 목숨도 이제 얼마 남지 않았지...");
			link.l2.go = "ShipEpidemy32";
			pchar.GenQuest.ShipSituation.Epidemy.CapId = NPChar.CaptanId;
			pchar.GenQuest.ShipSituation.Epidemy = ShipSituation_4;
		break;
		
		case "ShipEpidemy31":
			pchar.GenQuest.QuestAboardCabinDialogIdx = NPChar.index;
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Died"; // вражеский кэп на волосок от смерти от переизбытка стали и свинца в организме
			LAi_LockFightMode(pchar, false);
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "ShipEpidemy32":
			DialogExit();
			LAi_SetActorType(NPChar); 
			LAi_ActorGoToLocation(NPChar, "reload", "reload1", "none", "", "", "", -1);
			LAi_LockFightMode(pchar, false);	
			pchar.GenQuest.ShipSituation.Epidemy.CapState = "Live"; // вражеский кэп остался в живых
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
		break;
		// ситуации с капитаном захваченного корабля
		
		// Генератор "A damsel in the jungle"
		case "EncGirl_Lover":
			dialog.text = "안녕하세요, 선장님, 당신이 나를 찾고 있다고 들었습니다.";
			link.l1 = "나는 그래, 네가 그렇다면\n "+pchar.GenQuest.EncGirl.sLoverId+".";
			link.l1.go = "EncGirl_Lover1";
		break;
		
		case "EncGirl_Lover1":
			dialog.text = "그래, 나다. 중요한 일이라도 있나?";
			link.l1 = "그게 너한테 중요한지 모르겠지만, 내가 가져왔어 "+pchar.GenQuest.EncGirl.name+". 그녀는 집에서 도망쳐 나와 지금 선술집에서 멀지 않은 곳에서 당신을 기다리고 있어.";
			link.l1.go = "EncGirl_Lover2";
		break;
		
		case "EncGirl_Lover2":
			dialog.text = "이런... 이럴 줄 알았지... 그런데 왜 그녀가 도망쳤지? 너한테 말이라도 했냐?";
			link.l1 = "그녀의 아버지가 그녀를 고리대금업자의 아들에게 시집보내려고 해.";
			link.l1.go = "EncGirl_Lover3";
		break;
		
		case "EncGirl_Lover3":
			pchar.GenQuest.EncGirl.LoverCity = GetQuestNationsCity(sti(pchar.GenQuest.EncGirl.nation));
			pchar.GenQuest.EncGirl.LoverIsland = GetIslandByCityName(pchar.GenQuest.EncGirl.LoverCity);
			dialog.text = "안 돼, 그런 일은 절대 허락할 수 없어! 선장님, 있잖아요, 내가 정말 어리석은 처지에 놓였어요... 사실 선장님께 우리를 데려다 달라고 부탁하려 했거든요 "+XI_ConvertString(pchar.GenQuest.EncGirl.LoverIsland+"Acc")+" 라는 마을로 "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+", 하지만 지금은 돈도 없고 아직 일자리도 못 찾았어. 우리 집안은 부유하고 내 앞날도 유망한데\n "+XI_ConvertString("Colony"+pchar.GenQuest.EncGirl.LoverCity)+"...\n내가 장담하는데, 내 부모님은 내가 젊은 약혼녀와 함께 돌아가는 걸 아주 기뻐하실 거야. 그리고 널 충분히 보상해 주실 거야. 그래서, 할 거야?";
			link.l1 = "...이봐, 난 완전히 다른 계획이 있어. 한 가지 조언을 해주지: 뱃사람으로 일자리 구해서 월급으로 신부 방을 빌려라. 사람들은 그렇게 유럽으로 가고, 네가 말한 그 정착지는 새 한 마리 날아갈 거리밖에 안 돼.";
			link.l1.go = "EncGirl_Lover4";
			link.l2 = "아, 젊은이... 네가 나한테 뭘 부탁하는지 알고 있나? 부모님의 허락도 없이 딸을 데려가 달라니? ... 그런데 이런 부탁을 거절할 남자가 어디 있겠나? 당연히 나도 끼지!";
			link.l2.go = "EncGirl_Lover5";
		break;
		
		case "EncGirl_Lover4":
			npchar.lifeDay = 0;
			AddDialogExitQuestFunction("EncGirl_LoverExit");	
			DialogExit();
		break;
		
		case "EncGirl_Lover5":
			AddDialogExitQuestFunction("EncGirl_ToLoverParents");	
			DialogExit();
		break;
		
		case "EncGirl_Lover6":
			AddSimpleRumourCityTip(RandPhraseSimple("Have you heard, " + pchar.GenQuest.EncGirl.name + " ran off with her lover. She decided not to bind her life to an invalid. That's surely the mistake of her parents, they should not have become tempted with the money of her fiance and try to give such a beauty in marriage to a fright.",  
				"Have you heard?" + pchar.GenQuest.EncGirl.name + " tricked both her dad and her would-be fiance. They say one noble captain helped her and her lover to get to another island, where her lover's parents lived... Imagine that, there still are people, who had not yet forgotten the taste of passion!"), pchar.GenQuest.EncGirl.LoverCity, 3, 2, "citizen,habitue", "");
			dialog.text = "감사합니다, 선장님. 당신의 도움을 평생 기억하겠습니다.";
			link.l1 = "별일 아니었어. 모든 일이 잘 풀리길 바란다.";
			link.l1.go = "EncGirl_Lover7";
		break;
		
		case "EncGirl_Lover7":
			switch (rand(4))
			{
				case 0:
					sTemp = "the shop";
					pchar.GenQuest.EncGirl.LoverFather = "store_keeper";
				break;
				case 1:
					sTemp = "the shipyard";					
					pchar.GenQuest.EncGirl.LoverFather = "shipyard_keeper";
				break;
				case 2:
					sTemp = "the port office";					
					pchar.GenQuest.EncGirl.LoverFather = "portman_keeper";
				break;
				case 3:
					sTemp = "the tavern";					
					pchar.GenQuest.EncGirl.LoverFather = "tavern_keeper";
				break;
				case 4:
					sTemp = "the bank";					
					pchar.GenQuest.EncGirl.LoverFather = "usurer_keeper";
				break;
			}	
			pchar.GenQuest.EncGirl.FatherLoc = sTemp;
			dialog.text = "내가 부모님께 너를 소개해 드리겠다고 약속했어. 혹시 시간이 나면 꼭 와 줘\n "+sTemp+", 우리 아버지가 거기서 일하시는데, 당신이 우리를 위해 해준 일을 꼭 말씀드릴게요. 분명히 당신을 뵙고 무척 기뻐하실 거예요.";
			link.l1 = "알겠어, 시간 나면 들를게. 둘 다 행복하게 잘 지내고 서로 잘 챙겨줘...";
			link.l1.go = "EncGirl_Lover8";
		break;
		
		case "EncGirl_Lover8":
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
			npchar.lifeday = 0;
			AddQuestRecord("JungleGirl", "16");
			AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("",""));
			AddQuestUserData("JungleGirl", "sText", pchar.GenQuest.EncGirl.FatherLoc);
			if((GetSummonSkillFromName(pchar, SKILL_FORTUNE) + GetSummonSkillFromName(pchar, SKILL_LEADERSHIP)) < 175)
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 0; // папочка жениха счастлив за сына :)
			}
			else
			{
				pchar.GenQuest.EncGirl.LoverFatherAngry = 1; // папочка жениха разъярен за то что сын притащил в дом шалаву :)
			}
			chrDisableReloadToLocation = false; 
			pchar.GenQuest.EncGirl = "toLoverFather";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1 = "Timer";
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.day = GetAddingDataDay(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.win_condition.l1.date.year = GetAddingDataYear(0, 0, 2);
			pchar.quest.EncGirl_GetLoverFather.function = "EncGirl_GenQuest_GetLoverFather";
			DialogExit();	
		break;
		// Генератор "A damsel in the jungle"
		
		// Генератор "Captain's request"
		case "CaptainComission_1":
			dialog.text = RandPhraseSimple("잠깐만! 잠깐만요, 선장님! 제발.","선장님, 제발, 기다려 주십시오, 부탁드립니다...");
			link.l1 = LinkRandPhrase("뭐야? 숨이라도 잃었나?","칼을 들어라, 이 겁쟁이 놈아!","무슨 일이야? 유언장이라도 쓰는 걸 깜빡했나?");
			link.l1.go = "CaptainComission_2";
		break;
		
		case "CaptainComission_2":
			dialog.text = "잠깐만... 나 지금 부상당해서 더는 싸울 힘이 없어... 자비를 구하는 건 아니야, 하지만 아직 끝내지 못한 일이 남아 있어. 제발, 죽어가는 자의 마지막 소원을 들어주겠다고 약속해 줘.";
			link.l1 = RandPhraseSimple("겁쟁이처럼 굴지 마, 선장. 사내답게 죽음을 맞이해!","선장님, 무슨 감상에 젖으셨습니까? 지금 우리 주위에서 전투가 벌어지고 있으니, 시작한 일이나 끝냅시다.");
			link.l1.go = "CaptainComission_21";
			link.l2 = "지금 말해, 빨리 해.";
			link.l2.go = "CaptainComission_22";
		break;
		
		case "CaptainComission_21":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_22":		
			if(rand(1) == 0) // "Ransom"
			{
				CaptainComission_Init(NPChar);
				dialog.text = "Tell "+pchar.GenQuest.CaptainComission.Name+" 정착지에서 온 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City)+", 내가 그의 부탁을 들어주지 못했다는 게... 내가 미처... 그가 나를 용서해 주길 바라네...";
				link.l1 = RandPhraseSimple("그게 다야?! 좋아, 내가 할 수 있지. 이봐, 친구...","알겠어, 시간 나면 그에게 전할게. 이봐, 친구...");
				link.l1.go = "CaptainComission_22_1";
				link.l2 = "난 그렇게 생각하지 않아. 이런 헛소리에 쓸 시간 없어. 시작한 일이나 끝내자.";
				link.l2.go = "CaptainComission_22_2";
			}
			else // "Operation 'Galleon'"
			{			
				CaptainComission_GaleonInit(NPChar);
				dialog.text = "순찰대 선장에게 전해 주시오 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.ShipTypeName+"' "+pchar.GenQuest.CaptainComission.Name+", 여기에 얼굴을 비추지 말라고 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+"... "+"당국은 그의 죽음의 진짜 정황을 알고 있다 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"... 시간이 없어, 곧 체포될 거야... 항해해서 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Acc")+" 에서 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+", 항해에 거의 열다섯 날이 걸릴 거야... 아아... 서둘러야 해..."; // belamour gen
				link.l1 = RandPhraseSimple("아무것도 약속할 순 없지만, 때가 되면 해볼게. 이봐, 친구...","알겠어, 시간 나면 그에게 전할게. 이봐, 친구...");
				link.l1.go = "CaptainComission_300";
			}					
		break;
		
		case "CaptainComission_22_1":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));	
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();	
		break;
		
		case "CaptainComission_22_2":
			dialog.text = "이렇게 잔인하다니! 그 대가를 치르게 될 거야.";
			link.l1 = "그리고 훨씬 더 많은 것들이...";
			link.l1.go = "CaptainComission_22_3";
		break;
		
		case "CaptainComission_22_3":
			ReOpenQuestHeader("CaptainComission1");
			AddQuestRecord("CaptainComission1", "1");
			AddQuestUserData("CaptainComission1", "sShipName", pchar.GenQuest.CaptainComission.ShipName);
			AddQuestUserData("CaptainComission1", "sCapName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City));
			SetFunctionTimerCondition("CaptainComission_Speak", 0, 0, 30, false);
			SetFunctionTimerCondition("CaptainComission_SellSlave", 0, 0, 15 + rand(5), false);
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			pchar.GenQuest.CaptainComission = "Begin_2";
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;
		
		case "CaptainComission_3":
			dialog.text = LinkRandPhrase("네 말 듣고 있다, "+GetAddress_Form(pchar)+".","뭐 원하는 거야?","무엇을 도와줄까?");
			if (pchar.GenQuest.CaptainComission == "Begin_1" || pchar.GenQuest.CaptainComission == "Begin_2") // лесник - доп.проверка если есть квест. для перехода .
			{	
			link.l1 = "너냐 "+pchar.GenQuest.CaptainComission.Name+"? 너랑 할 일이 있어, 선장 "+pchar.GenQuest.CaptainComission.CapName+" 당신에게 중요한 정보를 전해 달라고 했어.";
			link.l1.go = "CaptainComission_4";
			break;
			}
			link.l2 = "아니, 아무것도 없어...";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_3"; // лесник - переход чтобы не вызывал баг при повтороном обращении
		break;
		
		case "CaptainComission_4":
			dialog.text = "그랬어? 좋아. 그래서, 선장이란 자가\n "+pchar.GenQuest.CaptainComission.CapName+"나한테 알려주고 싶었던 거야?";
			link.l1 = "그가 당신의 부탁을 들어줄 수 없다고 전해 달라고 했어.";
			link.l1.go = "CaptainComission_5";
		break;
		
		case "CaptainComission_5":
			dialog.text = "무슨 소리야?! 나는 그 사람을 오래전부터 알아왔어, 정말 정직한 사람이야. 그런 말을 너한테 했을 리가 없어!";
			link.l1 = "그냥 그의 의지로 어쩔 수 없는 이유였다고 해 두자. 다시 말해, 그게 그의 마지막 소원이었지.";
			link.l1.go = "CaptainComission_6";
		break;
		
		case "CaptainComission_6":
			CaptainComission_GetPirateIsland();
			CaptainComission_GetFamilyType();
			if(pchar.GenQuest.CaptainComission == "Begin_1")
			{
				dialog.text = "아, 이건 완전히 말도 안 돼! 시간만 엄청 버렸잖아\n"+"선장님, 그렇다면 제게 도와주셔야겠습니다. 해적들이  "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Gen")+" 내 친척을 잡았다 "+pchar.GenQuest.CaptainComission.SlaveName+" 그놈들이 몸값을 요구하고 있어. 이 임무를 맡을 수 있겠나? 보상은 꽤 후할 거야.";
				link.l1 = "유감이지만, 나는 다른 계획이 있어.";
				link.l1.go = "CaptainComission_6_1";
				link.l2 = "좀 더 자세히 설명해 주면 도와주도록 하지.";
				link.l2.go = "CaptainComission_6_2";
			}
			
			if(pchar.GenQuest.CaptainComission == "Begin_2")
			{
				dialog.text = "아, 이건 완전히 엉망이잖아! 시간만 엄청 낭비했네\n그럼 상자들은 어떻게 된 거야?";
				link.l1 = "음... 무슨 상자 말이야?";
				link.l1.go = "CaptainComission_6_3";
				pchar.GenQuest.CaptainComission.CanFindChest = true;
			}	
		break;
		
		case "CaptainComission_6_1":
			dialog.text = "안타깝군, 선장... 네가 나를 도와줄 생각이 없다니 유감이야.";
			link.l1 = "그건 내 의지로 되는 일이 아니야, 친구. 이해해 줘야 해. 잘 가라.";
			link.l1.go = "CaptainComission_6_1End";
		break;
		
		case "CaptainComission_6_2":
			dialog.text = "어제 나는 편지를 받았어 "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", 몸값이 더 비쌀 거라고 알리면서 그를 노예로 팔아버리겠다고 협박했소. 전임 선장이 미리 알려줬어야 했는데 "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_ACC)+", 내가 이전 조건에 동의하고 선불을 지불했지. 하지만 이제야 왜 해적들이 판을 키웠는지 알겠군.";
			link.l1 = "그래서 네가 제안하는 게 뭐지?";
			link.l1.go = "CaptainComission_6_21";
		break;
		
		case "CaptainComission_6_3":
			dialog.text = "오, "+GetSexPhrase("놈","아가씨")+", 여기 뭔가 수상한 냄새가 나는군. 경고하겠소, 이건 매우 위험하며 심각한 결과를 초래할 수 있소. 선장 "+pchar.GenQuest.CaptainComission.CapName+" 금으로 가득 찬 상자 세 개가 있었는데, 그걸 넘겨야 했던 "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_DAT)+" 켜짐 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" 한 사람의 몸값으로 -  "+pchar.GenQuest.CaptainComission.SlaveName+". 그리고 그가 너를 우리에게 보내고 싶었다면, 그 상자들에 대해 말하는 걸 잊었을 리 없지.";
			link.l1 = "마지막 말을 하면서도 문장을 끝내지 않은 것 같았어. 나는 네가 더 이야기해 주길 바랐지.";
			link.l1.go = "CaptainComission_6_31";
		break;
		
		case "CaptainComission_6_1End":
			AddQuestRecord("CaptainComission1", "3");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCharType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			CloseQuestHeader("CaptainComission1");
			sld = CharacterFromID("CapComission_1"); // удаление если послал нахуй. лесник.
			sld.LifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			DialogExit();	
		break;
		
		case "CaptainComission_6_21":
			dialog.text = "어쩔 수 없군... 이미 필요한 금액, 15만 페소를 모아 두었네. 그 돈을 전달해 주길 바라네\n "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.PiratesCity+"Acc")+" 그리고 내 친척을 여기로 데려와라. 일이 끝나는 즉시 4만을 주겠다.";
			link.l1 = "좋아, 준비됐어.";
			link.l1.go = "CaptainComission_6_22";
			link.l2 = "유감이지만, 나는 다른 계획이 있어.";
			link.l2.go = "CaptainComission_6_1";			
		break;
		
		case "CaptainComission_6_22":
			dialog.text = "그럼 돈을 가져가시오. 주님의 축복이 함께하길. 하지만 제발, 서둘러 주시오. 나는 두렵소, \n "+ChangeNameCase(NAMETYPE_MAIN,pchar.GenQuest.CaptainComission.PirateName,NAME_NOM)+" 기다리지 않고 그 불쌍한 영혼을 노예로 팔아넘길 거야.";
			link.l1 = "여기서 기다려. 오래 걸리진 않을 거야.";
			link.l1.go = "CaptainComission_6_22End";
		break;
		
		case "CaptainComission_6_22End":
			AddQuestRecord("CaptainComission1", "4");
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sFamilyType", GetStrSmallRegister(XI_ConvertString("Family" + pchar.GenQuest.CaptainComission.FamilyType + "Gen")));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			addMoneyToCharacter(pchar, 150000);
			pchar.GenQuest.CaptainComission = "Begin_11";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "goodSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_6_31":
			dialog.text = "상관없어\n몸값을 모은 놈들은 신경도 안 써. 저놈들이 원하는 건 결과뿐이야. 살아 있고 멀쩡한 상태로 - "+pchar.GenQuest.CaptainComission.SlaveName+". 그러니 시간 낭비하지 마.";
			link.l1 = "내가 거절하면 어쩔 건데?";
			link.l1.go = "CaptainComission_6_32";
		break;
						
		case "CaptainComission_6_32":
			dialog.text = "사실, 네 동의는 필요 없어. 그냥 알려주는 거야, 네가 전달하지 않으면\n "+pchar.GenQuest.CaptainComission.SlaveName+" 살아서 당당히 선술집에 가면, 현상금 사냥꾼들을 보낼 거야...";
			link.l1 = "흠... 그거 심각하군. 내가 하면?";
			link.l1.go = "CaptainComission_6_33";
		break;
		
		case "CaptainComission_6_33":
			dialog.text = "그럼 더 이야기해 보도록 하지.";
			link.l1 = "좋아... 어떻게 되는지 한번 보자.";
			link.l1.go = "CaptainComission_6_33End";
		break;
		
		case "CaptainComission_6_33End":
			AddQuestRecord("CaptainComission1", "5");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCapName",pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission1", "sPirateName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
			AddQuestUserData("CaptainComission1", "sPirateCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.PiratesCity + "Acc"));
			AddQuestUserData("CaptainComission1", "sSlaveName",pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
			pchar.GenQuest.CaptainComission = "Begin_22";
			pchar.GenQuest.CaptainComission.AfterTavernSpeak = "badSpeak";
			pchar.GenQuest.CaptainComission.GetSlave = "NoSlave";
			pchar.GenQuest.CaptainComission.toMayor = true;
			SetFunctionTimerCondition("CaptainComission_30DaysIsLeft", 0, 0, 30, false);
			NextDiag.TempNode = "CaptainComission_7";
			NextDiag.CurrentNode = NextDiag.TempNode; 
			DialogExit();
		break;
		
		case "CaptainComission_7":
			if(pchar.GenQuest.CaptainComission.GetSlave == "NoSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("안녕하시오, 선장 "+GetFullName(pchar)+". 소식 있나?","그래서, 선장, 벌써 몸값을 전달했나?","안녕, 좋은 소식 가지고 온 거지?");
					if(makeint(pchar.money)>=150000)
					{
						link.l1 = "유감이지만 내 계획이 바뀌어서 우리 거래를 깨야겠어.";
						link.l1.go = "CaptainComission_7_1";
					}
					link.l2 = "아직 아니야. 그 일로 아직 바빠.";
					link.l2.go = "CaptainComission_7_2";
				}
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
				{
					dialog.text = LinkRandPhrase("오, 반갑소, 선장님 "+GetFullName(pchar)+". 좋은 소식이라도 있나?","그래서, 선장님, 우리 고생하는 친구를 구해 오셨소?","살아 있고 건강한 모습 보니 반갑소, 선장. 우리 둘 사이 일은 어떻게 되어가고 있소?");
					link.l1 = "아직 소식은 없지만, 내가 계속 알아보고 있어.";
					link.l1.go = "CaptainComission_7_3";
					link.l2 = "이봐, 친구, 왜 그 거래를 나한테 책임지라고 하는 거야?";
					link.l2.go = "CaptainComission_7_4";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "GetSlave")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("안녕하세요, 선장님 "+GetFullName(pchar)+". 소식 있나?","그래서, 선장님, 벌써 몸값을 전달하셨습니까?","안녕, 좋은 소식을 가지고 온 거지?");
					link.l1 = "그래. 네 부탁은 들어줬다, "+pchar.GenQuest.CaptainComission.SlaveName+" 내 배에 타고 있고 지금 상륙할 준비를 하고 있다.";
					link.l1.go = "CaptainComission_30";
				}
				else
				{
					dialog.text = LinkRandPhrase("오, 반갑소, 선장님 "+GetFullName(pchar)+". 좋은 소식이라도 있어?","그래서, 선장님, 우리 고생하는 친구를 구해 오셨습니까?","살아 있고 건강한 모습을 보니 반갑소, 선장. 우리 공동 일의 진행 상황은 어떤가?");	
					link.l1 = "우리가 얘기했던 그 남자를 데려왔어. 내 배에 타고 있어.";
					link.l1.go = "CaptainComission_32";
				}
			}
			if(pchar.GenQuest.CaptainComission.GetSlave == "SlaveDied")
			{
				if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
				{
					dialog.text = LinkRandPhrase("안녕하시오, 선장 "+GetFullName(pchar)+". 소식 있어?","그래, 선장. 벌써 몸값을 전달했나?","안녕, 좋은 소식 가지고 온 거지?");
					link.l1 = "안녕, "+pchar.GenQuest.CaptainComission.Name+", 실망시켜야겠군.";
					link.l1.go = "CaptainComission_50";
				}
				else
				{
					dialog.text = LinkRandPhrase("오, 반갑소, 선장님 "+GetFullName(pchar)+". 좋은 소식이라도 있나?","그래서, 선장님, 우리 고생하는 친구를 구해 오셨습니까?","살아 있고 건강한 모습을 보니 반갑소, 선장. 우리 공동 일의 진행 상황은 어떤가?");
					link.l1 = "네가 중재하려던 그 남자는 죽었어.";
					link.l1.go = "CaptainComission_60";
				}
			}
		break;
		
		case "CaptainComission_30":
			dialog.text = "감사합니다, 선장님, 우리 가족에게 큰 은혜를 베풀어 주셨습니다. 여기 보상입니다... 상자가 세 개 있는데, 정확히 4만 페소에 해당합니다. 부디 양해해 주십시오, 이제 그를 만나러 가야 합니다.";
			link.l1 = "물론이지, 즐거운 만남 되시고 두 분 모두 행운을 빌어.";
			link.l1.go = "CaptainComission_30_1";
			if(CheckAttribute(pchar, "GenQuest.CaptainComission.SlaveAddMoney"))
			{
				link.l2 = "그대의 조급함을 충분히 이해하오, 하지만 예기치 못한 상황들로 인해 내가 추가 비용을 부담할 수밖에 없었소.";
				link.l2.go = "CaptainComission_31";
			}	
		break;
		
		case "CaptainComission_30_1":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 3);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			AddQuestRecord("CaptainComission1", "14");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_31":
			//addMoneyToCharacter(pchar, 25000);
			TakeNItems(pchar, "chest", 2);
			Log_Info("You have received credit chests");
			PlaySound("interface\important_item.wav");
			dialog.text = "이해가 안 돼... 이미 네 보수 금액에 합의했잖아?";
			link.l1 = "우리는 받았지. 하지만 15만 페소 대신 20만 페소를 내야 했고, 바베이도스까지 가야 했던 건 말할 것도 없어.";
			link.l1.go = "CaptainComission_31_1";
		break;
		
		case "CaptainComission_31_1":
			dialog.text = "선장, 이건 전적으로 당신이 게을렀기 때문이오. 해적들은 내게 추가로 아무런 요구도 하지 않았소. 남의 고생을 이용해 이득을 보려 하다니, 참 이상한 녀석이군?";
			link.l1 = "좋아, 너한테 뭘 설명해 봐야 소용없다는 걸 알겠군...";
			link.l1.go = "CaptainComission_31_1End";
		break;
		
		case "CaptainComission_31_1End":
			AddQuestRecord("CaptainComission1", "15");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");			
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;

		case "CaptainComission_32":
			dialog.text = "훌륭하군! 우리가 잘 협력할 수 있을지 의심했었지.";
			link.l1 = "하지만 이 일에 돈을 많이 써야 했지.";
			link.l1.go = "CaptainComission_32_1";
		break;
		
		case "CaptainComission_32_1":
			GetSlaveSpeciality();
			dialog.text = "알아, 알아... 하지만 그건 네 잘못이기도 해. 우리가 금고에서 억지로 꺼낸 금 상자 세 개를 어떻게 네가 가라앉힐 수가 있냐, 그래서\n "+NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation))+" 그런 전문가가 있을 수도 있겠지 "+pchar.GenQuest.CaptainComission.SlaveSpeciality+"?";
			link.l1 = "알아둬라, 제대로 보상하지 않으면 그를 넘겨주지 않을 거다.";
			link.l1.go = "CaptainComission_32_2";
		break;
		
		case "CaptainComission_32_2":
			dialog.text = "음, 너도 똑똑한 놈이니 이제 흥정하기엔 너무 늦었다는 걸 알겠지. 우리가 네 배와 화물까지 전부 차지할 수도 있었어.\n하지만 보상은 미리 제공되었지. 그러니 정부는 "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+" 성공적인 작전을 축하하며 이 귀중한 선물과 소박한 보상을 드립니다.";
			link.l1 = "흠... 뭐, 없는 것보단 낫지. 네 소중한 전문가 데려가.";
			link.l1.go = "CaptainComission_32_2End";
		break;
		
		case "CaptainComission_32_2End":
			AddQuestRecord("CaptainComission1", "16");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSpeciality", pchar.GenQuest.CaptainComission.SlaveSpeciality);
			AddQuestUserData("CaptainComission1", "sNation", NationNameNominative(sti(pchar.GenQuest.CaptainComission.Nation)));
			CloseQuestHeader("CaptainComission1");			
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 15);			
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Item); 
			TakeNItems(pchar, "jewelry5", 100);
			PlaySound("interface\important_item.wav");
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_1":
			dialog.text = "아이고, 안타깝군! 이미 너무 많은 시간을 허비했어. 정말 실망이야, 선장!";
			link.l1 = "알겠어, 하지만 어쩔 수 없는 상황이었지. 여기 네 돈이야.";
			link.l1.go = "CaptainComission_7_1End";
		break;
		
		case "CaptainComission_7_1End":
			AddQuestRecord("CaptainComission1", "8");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			rChar = characterFromId("CapComission_1");
			rChar.lifeDay = 0; 
			pchar.quest.CaptainComission1_30DaysIsLeft.over = "yes";
			addMoneyToCharacter(pchar, -150000);
			ChangeCharacterComplexReputation(pchar,"nobility", -4);
			LAi_CharacterDisableDialog(NPChar);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_EndTavern");
		break;
		
		case "CaptainComission_7_2":
			dialog.text = "서둘러 주시겠습니까? 해적들이 또다시 거래 조건을 바꿀까 두렵습니다.";
			link.l1 = "걱정 마, 우리가 알아서 할게.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_3":
			dialog.text = "시간과 싸우고 있다는 걸 알고 있겠지?";
			link.l1 = "또 한 번이군! 내가 할게. 좀만 참아.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		case "CaptainComission_7_4":
			dialog.text = "신이시여, 우리를 구하소서! 부담 주는 건 아니고, 그냥 겸손한 청교도가 좀 도와주는 거야\n네 잘못이야. 네가 선장을 죽였잖아 "+pchar.GenQuest.CaptainComission.CapName+", 금을 잃고 아주 값진 놈을 몸값도 못 받고 놓쳤지. 이제 골치 아픈 일이고, 네 책임이야. 용서받을 생각도 하지 마... 전부 대가를 치르게 될 거다.";
			link.l1 = "꺼져!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_7";
		break;
		
		// диалоги с управляющим на плантации
		case "CaptainComission_10":
			dialog.text = "이봐, 뭐 필요한 거라도 있어?";
			link.l1 = "이 농장의 주인을 만날 수 있을까?";
			link.l1.go = "CaptainComission_10_1";
		break;
		
		case "CaptainComission_10_1":
			dialog.text = "여기 없어, 도망친 노예를 찾으러 갔어. 블레이드였나 블러드였나, 기억이 안 나... 그리고 나는 이 동네 관리인이지\n "+npchar.name+" 그리고 두목이 자리를 비운 동안 모든 일을 내가 처리하라고 허가받았지.";
			link.l1 = "그래? 그거 좋군... 그리고 노예를 파는 것도 네 일이냐?";
			link.l1.go = "CaptainComission_10_2";
		break;
		
		case "CaptainComission_10_2":
			dialog.text = "물론이지. 몇 개나 사고 싶은데?";
			link.l1 = "딱 하나.";
			link.l1.go = "CaptainComission_10_3";
		break;
		
		case "CaptainComission_10_3":
			dialog.text = "에이... 노예 한 명만 정말 필요한 거 맞아?";
			link.l1 = "물론이지, 내가 맞아. 그의 이름은 "+pchar.GenQuest.CaptainComission.SlaveName+".";
			link.l1.go = "CaptainComission_10_4";
		break;
		
		case "CaptainComission_10_4":
			if(rand(1) == 0)
			{
				dialog.text = "하지만 분명히 알겠지만, 노예 한 명만 따로 팔면 대량으로 팔 때보다 가격이 더 비싸질 거라는 거 알지?";
				link.l1 = "당연히 알지. 값이 얼마인지 말해 볼래?";
				link.l1.go = "CaptainComission_11";
			}
			else
			{
				if(rand(100) < makeint(sti(pchar.rank) + 0.75 * GetSummonSkillFromName(pchar, SKILL_FORTUNE)))
				{
					dialog.text = "흠... 네가 누구를 위해 중재하는지 알고 있겠지?";
					link.l1 = "무슨 뜻이야?";
					link.l1.go = "CaptainComission_12";
				}
				else
				{
					dialog.text = "오, 그 게으름뱅이 말인가. 난 걔한테 구리 한 닢도 안 주겠어. 여기 끌려온 이후로 제대로 일하는 걸 본 적이 없어. 대령이 왜 저런 국가 죄수들한테 돈을 낭비하는지 모르겠군. 흑인들은 이야기가 달라. 그들은 훌륭한 일꾼들이지, 타고나기를 힘세고 복종하는 게 피에 흐르고 있어. 내 말 믿어, 무슨 일이든 시킬 수 있다니까. 사탕수수 수확이든 집사 노릇이든, 약간만 ‘설득’해 주면 누구보다 잘 해낸다니까...\n";
					link.l1 = "이봐, 네 흑인 놈들 따위엔 전혀 관심 없어. 내가 신경 쓰는 건 네가 말한 그 게으름뱅이 하나뿐이야. 어차피 오래 못 살 놈이니까. 난 그 녀석을 총알받이로 쓸 거고, 그 녀석한테는 더 쳐줄 생각이야.";
					link.l1.go = "CaptainComission_13";
				}
			}
		break;
		
		case "CaptainComission_11":
			dialog.text = "그래, 그래. 가격 좀 보자고\n오! 15만 페소네.";
			link.l1 = "이런 젠장...";
			link.l1.go = "CaptainComission_11_1";
		break;
		
		case "CaptainComission_11_1":
			dialog.text = "가격은 가격표에 있을 거야. 여기. 그런데 말이지, 난 잘 이해가 안 돼. 다른 노예들은 적당한 값에 팔리는데, 저 녀석만 엄청난 돈에 팔리고 있잖아...";
			if(sti(pchar.money) >= 150000)
			{
				link.l1 = "여기서 무슨 일이 벌어지는지 알 것 같군... 좋아, 돈은 여기 있고, 저 사람은 내가 데려가겠다.";
				link.l1.go = "CaptainComission_14";
			}	
			link.l2 = "흠... 하지만 나는 인질 몸값을 치르는 게 아니라 평범한 노예를 사고 싶은 거야. 그 돈이면 제대로 장비 갖춘 배 한 척은 살 수 있지 않겠어?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_12":
			dialog.text = "저건 평범한 노예가 아니야. 비숍 대령이 직접 그를 감시하라고 명령까지 내렸거든.";
			link.l1 = "그래서 그 녀석을 돈 주고도 못 사는 거야?";
			link.l1.go = "CaptainComission_12_1";
		break;
		
		case "CaptainComission_12_1":
			dialog.text = "왜, 물론이지. 대령님이 그에게 값을 매겼어 - 가격표에 따르면 20만 페소야.";
			if(sti(pchar.money) >= 200000)
			{
				link.l1 = "이런 젠장! 그 대령도 분명 저 노예가 어떤 인간인지 알고 있을 텐데...";
				link.l1.go = "CaptainComission_16";
			}	
			link.l2 = "흠... 하지만 나는 인질 몸값을 지불하는 게 아니라 평범한 노예를 사려는 거야. 그 돈이면 제대로 갖춘 배 한 척은 살 수 있다고 생각하지 않아?";
			link.l2.go = "CaptainComission_15";	
		break;
		
		case "CaptainComission_13":
			dialog.text = "아, 그렇군. 실례했소. 주교가 남긴 가격표를 좀 보겠소.\n아, 여기 있군. 음... 어!.. 15만 페소라니!..";
			if(sti(pchar.money) >= 15000)
			{
				link.l1 = "분명 뭔가 착오가 있는 것 같군. 아무리 봐도 노예가 그 정도 값일 리가 없잖아. 아마 0이 하나 더 붙은 것 같은데, 실제로는 15,000페소가 맞을 거야. 그리고 그 녀석이 게으르고 멍청한 걸 생각하면, 그것도 너무 비싸지.";
				link.l1.go = "CaptainComission_17";
			}	
			link.l2 = "흠... 하지만 나는 인질 몸값을 치르는 게 아니라 그냥 평범한 노예를 사고 싶은 거야. 그 돈이면 제대로 갖춘 배 한 척은 살 수 있지 않겠어?";
			link.l2.go = "CaptainComission_15";
		break;
		
		case "CaptainComission_14":
			addMoneyToCharacter(pchar, -150000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 150000;
			dialog.text = "좋아! 정말 훌륭하군! 곧 그를 여기로 데려올 거야... 에... 차라도 한잔할래?";
			link.l1 = "아니, 됐어... 비숍 대령에게 안부 전해줘...";
			link.l1.go = "CaptainComission_14_1";
		break;
		
		case "CaptainComission_14_1":
			dialog.text = "누구에게서인지 물어봐도 되겠나?";
			link.l1 = "음... 됐다, 신경 쓰지 마. 잘 가라.";
			link.l1.go = "CaptainComission_14_1End";
		break;
		
		case "CaptainComission_14_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_15":
			dialog.text = "미안하지만 내가 해줄 수 있는 건 없어. 여기 가격표야.";
			link.l1 = "아, 그만 좀 해라, '가격표, 가격표...' 너희 중 누구도 주교 없이는 가장 간단한 것도 결정 못 하잖아. 그에게 전해... 아니, 됐다, 아무 말도 하지 마라.";
			link.l1.go = "CaptainComission_15_1";
		break;
		
		case "CaptainComission_15_1":
			dialog.text = "그래서 그 노예를 안 살 거란 말이지.";
			link.l1 = "아니. 잘 가.";
			link.l1.go = "CaptainComission_15_1End";
		break;
		
		case "CaptainComission_15_1End":
			OfficersReaction("bad");
			AddQuestRecord("CaptainComission1", "30");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			NextDiag.TempNode = "CaptainComission_19";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_16":
			dialog.text = "나 그 일에 대해선 아무것도 몰라. 난 그 노예를 팔라는 구체적인 지시만 받았어.";
			link.l1 = "헛소리 하지 마... 좋아, 됐다. 여기 돈이다. 노예를 데려와.";
			link.l1.go = "CaptainComission_16_1"; 
		break;
		
		case "CaptainComission_16_1":
			addMoneyToCharacter(pchar, -200000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 200000;
			dialog.text = "물론이지. 곧 여기로 데려올 거야.";
			link.l1 = "잘 가라.";
			link.l1.go = "CaptainComission_16_1End";
		break;
		
		case "CaptainComission_16_1End":
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_17":
			dialog.text = "흠... 그래, 네 말이 맞을지도 모르겠군. 뭔가 착오가 있었던 것 같아.";
			link.l1 = "좋아, 값에 합의했으니 이제 그를 데려가도 되겠나?";
			link.l1.go = "CaptainComission_17_1";
		break;
		
		case "CaptainComission_17_1":
			dialog.text = "네, 물론입니다. 곧 그를 이리로 데려오겠습니다.";
			link.l1 = "아주 좋아. 여기 네 돈이다... 잘 가라.";
			link.l1.go = "CaptainComission_17_1End";
		break;
		
		case "CaptainComission_17_1End":
			addMoneyToCharacter(pchar, -15000);
			pchar.GenQuest.CaptainComission.SlaveMoney = 15000;
			NextDiag.TempNode = "CaptainComission_18";
			NextDiag.CurrentNode = NextDiag.TempNode;
			pchar.GenQuest.CaptainComission.GetSlave = "GetSlave";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GetSlave");
		break;
		
		case "CaptainComission_18":
			dialog.text = "차 한잔 하시겠습니까, 선장님?";
			link.l1 = "아니, 됐어.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_19":
			dialog.text = "그를 사기로 결정했나?";
			link.l1 = "아니. 잘 가라.";
			link.l1.go = "exit";
		break;
		
		// диалоги с рабом
		case "CaptainComission_20":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "안녕하세요, 선장님. 무엇을 도와드릴까요? 이 고통이 드디어 끝났다니 믿기지 않네요.";
				link.l1 = "나에게 감사할 게 아니라, 오히려 네 친척에게 감사해야지 "+pchar.GenQuest.CaptainComission.Name+" 에서 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". 그는 몸값을 모았어.";
				link.l1.go = "CaptainComission_201";
			}
			else
			{
				dialog.text = "안녕하세요, 선장님. 제 몸값을 대신 내주셨다고 들었습니다. 그 점에 대해 감사드려야겠군요, 비록 선장님께서 단지 심부름꾼이셨다는 건 알지만요.";
				link.l1 = "새로 되찾은 자유가 그리 기뻐 보이지 않는데. 뭔가 걱정되는 거라도 있나?";
				link.l1.go = "CaptainComission_202";
			}
		break;
		
		case "CaptainComission_201":
			dialog.text = "제발, 만약 당신 계획에 크게 방해되지 않는다면, 저를 그에게 데려다 주십시오. 직접 감사 인사를 전하고 싶습니다.";
			link.l1 = "물론이지, 내가 데려다줄게. 따라와, 배로 안내하지.";
			link.l1.go = "CaptainComission_201_1";
		break;
		
		case "CaptainComission_201_1":
			AddQuestRecord("CaptainComission1", "11");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			DialogExit();
		break;
		
		case "CaptainComission_202":
			dialog.text = "내 자유를 확실히 보장받으려면, 그 값을 치른 자들의 이름을 알아야 해.";
			link.l1 = "글쎄, 내가 돈을 내긴 했지, 내 의지로 한 건 아니었지만.";
			link.l1.go = "CaptainComission_202_1";
		break;
		
		case "CaptainComission_202_1":
			dialog.text = "그래, 내 의심이 맞았군. 네가 그렇게 할 수밖에 없었던 건 \n "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "그래, 맞아 "+pchar.GenQuest.CaptainComission.Name+" 에서 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_202_2";
		break;
		
		case "CaptainComission_202_2":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta 
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "알겠어. 그들이 너한테 뭘 약속했는지는 모르겠지만, 조건은 이거야: 나를 의 선술집으로 데려가. "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", 거기라면 정말 안전할 거야. 대신 내가 가진 정보를 좀 나눠주지.";
			link.l1 = "괜찮아, 어차피 아직 아무것도 약속한 게 없으니까. 나랑 같이 가자, 내 배로 데려가 줄게.";
			link.l1.go = "CaptainComission_202_3";
			link.l2 = "나는 수상쩍은 정보 때문에 괜히 내게 문제를 끌어들이고 싶지 않아.";
			link.l2.go = "CaptainComission_203";
		break;
		
		
		
		case "CaptainComission_202_3":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			rChar = characterFromId("CapComission_1");
			ChangeCharacterAddress(rChar, "none", "");			
			rChar.lifeDay = 0; 
			AddQuestRecord("CaptainComission1", "12");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.quest.CapComission_DeliveSlave.win_condition.l1 = "location";
			pchar.quest.CapComission_DeliveSlave.win_condition.l1.location = pchar.GenQuest.CaptainComission.SlaveCity + "_tavern";
			pchar.quest.CapComission_DeliveSlave.function = "CaptainComission_DeliveSlave";
			LAi_SetActorType(NPChar);
			LAi_ActorFollow(NPChar, PChar, "OpenTheDoors", -1.0); //лесник  идем за ГГ
			DialogExit();
		break;
		
		case "CaptainComission_203":
			dialog.text = "유감이지만, 지금은 당신에게 말해줄 수 없어. 이건 우리 둘 다 곤란해질 수 있거든.";
			link.l1 = "더더욱 그렇지... 따라와, 그리고 멍청한 짓 하지 마. 다시 한 번 체포된 줄 알아.";
			link.l1.go = "CaptainComission_203_1";
		break;
		
		case "CaptainComission_203_1":
			AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0); //лесник - провожаем на корабль типа..
			DialogExit();
		break;
		
		case "CaptainComission_50":
			dialog.text = "뭐라고?! 해적들이 또 거래 조건을 바꿨다고? 하지만 나는 더 이상 사업에서 돈을 뺄 수 없어! 그렇게 하면 곧 파산하고 말 거야!";
			link.l1 = "아니오... 당신의 친척은 탈출을 시도하다 실패해서 바베이도스 플랜테이션에서 목숨을 잃었소.";
			link.l1.go = "CaptainComission_51";
		break;
		
		case "CaptainComission_51":
			ChangeCharacterComplexReputation(pchar,"nobility", -3);
			dialog.text = "아... 완전히 망했군... 어떻게 이런 일이 벌어진 거지?";
			link.l1 = "해적들은 몸값을 기다리지도 않고 그를 노예로 팔아넘겼어. 내가 바베이도스로 쫓아갔지만, 결국 구하지 못했지...";
			link.l1.go = "CaptainComission_52";
		break;
		
		case "CaptainComission_52":
			dialog.text = "제기랄! 무슨 일이야?\n좋소, 선장님. 참여해 주셔서 감사합니다. 그리고 내가 준 돈은 돌려주시오.";
			link.l1 = "내 지출이 예상보다 훨씬 많았으니, 네 돈은 내가 가지겠다... 잘 가라.";
			link.l1.go = "CaptainComission_53";
			if(sti(pchar.money) >= 150000)
			{
				link.l2 = "그래, 가져가... 도와주지 못해 미안해... 잘 가.";
				link.l2.go = "CaptainComission_54";
			}
		break;
		
		case "CaptainComission_53":
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			OfficersReaction("bad");			
			AddQuestRecord("CaptainComission1", "22");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_54":
			OfficersReaction("good");
			addMoneyToCharacter(pchar, -150000);
			AddQuestRecord("CaptainComission1", "23");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_60":
			dialog.text = "안됐군. 네가 얼마나 심각한지 정말 모르는구나...";
			link.l1 = "어쩔 수 없지. 이렇게 된 것도 오히려 다행이야. 잘 가라.";
			link.l1.go = "CaptainComission_61";
		break;
		
		case "CaptainComission_61":
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -15);
			AddQuestRecord("CaptainComission1", "32");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission1");
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeDay = 0; 			
			DeleteAttribute(pchar,"GenQuest.CaptainComission");			
			DialogExit();
		break;
		
		// диалог с рабом в колодках
		case "CaptainComission_70":
			dialog.text = "물 좀... 선장님, 물 좀 가져와...";
			link.l1 = "이봐, 친구, 너 아니냐 "+pchar.GenQuest.CaptainComission.SlaveName+"?";
			link.l1.go = "CaptainComission_71";
		break;
		
		case "CaptainComission_71":
			dialog.text = "그래... 나야...";
			link.l1 = "이봐! 여기서 넙치처럼 얕은 물에 쓸쓸히 죽고 싶지 않으면 정신 똑바로 차리고 내 말 들어. 바베이도스 등대가 어디 있는지 아냐?";
			link.l1.go = "CaptainComission_72";
		break;
		
		case "CaptainComission_72":
			dialog.text = "그래...";
			link.l1 = "기회가 생기면 바로 그리로 달려가. 내가 그런 기회를 만들어 볼게.";
			link.l1.go = "CaptainComission_73";			
		break;
		
		case "CaptainComission_73":	
			LAi_SetPlayerType(pchar); 
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			LAi_LockFightMode(pchar, false);			
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			for(i = 0; i < 3; i++)
			{
				if (GetCharacterIndex("SlaveGuard_" + i) == -1) continue;
				sld = CharacterFromID("SlaveGuard_" + i);			
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "SlaveGuards");
			}
						
			LAi_group_SetRelation("SlaveGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_SetRelation("SlaveGuards", sTemp, LAI_GROUP_NEITRAL);			
			LAi_group_SetAlarmReaction("SlaveGuards", sTemp, LAI_GROUP_NEITRAL, LAI_GROUP_FRIEND);
			LAi_group_FightGroups("SlaveGuards", LAI_GROUP_PLAYER, true);
			LAi_group_SetAlarm("SlaveGuards", LAI_GROUP_PLAYER, 0);
			LAi_group_SetCheck("SlaveGuards", "OpenTheDoors");
			LAi_group_SetCheckFunction("SlaveGuards", "CaptainComission_GuardsAfter");
			
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn"); 
		break;
		
		// диалог охранников раба
		case "CaptainComission_80":
			dialog.text = RandPhraseSimple("물어봐, 선장. 하지만 빨리 해, 나 근무 중이니까.","말해, 하지만 빨리 해라. 쓸데없는 걸로 귀찮게 하지 마.");
			link.l1 = RandPhraseSimple("어떤 노예를 찾고 싶은데, 어떻게 하면 될지 알려줄 수 있나? 이름은 "+pchar.GenQuest.CaptainComission.SlaveName+".","이 플랜테이션 어딘가에 이름이 이런 노예가 있을 거야 "+pchar.GenQuest.CaptainComission.SlaveName+". 내가 그와 어떻게 이야기할 수 있는지 말해 줄 수 있나?");
			link.l1.go = "CaptainComission_81";			
		break;
		
		case "CaptainComission_81":
			dialog.text = "오늘 그는 벌을 받고 감시를 받고 있다.";
			link.l1 = "고맙다.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_80";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_85":
			dialog.text = "고맙습니다... 선장님, 제 목숨을 구해주셨군요...";
			link.l1 = "바베이도스 등대로 달려가서 거기서 나를 기다려.";
			link.l1.go = "CaptainComission_86";
		break;
		
		case "CaptainComission_86":
			LAi_SetActorType(NPChar);
			LAi_ActorRunToLocation(NPChar, "reload", "reload2_back", "none", "", "", "OpenTheDoors", -1.0);
			sTemp = GetNationNameByType(GetCityNation("Bridgetown"))  + "_citizens";
			LAi_group_AttackGroup(sTemp, LAI_GROUP_PLAYER);
			DialogExit();
		break;
		
		case "CaptainComission_90":
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "goodSpeak")
			{
				dialog.text = "선장님, 어떻게 감사드려야 할지 모르겠습니다. 이 고통이 드디어 끝났다는 게 아직도 믿기지 않아요.";
				link.l1 = "네 친척에게는 이미 감사를 받았어 "+pchar.GenQuest.CaptainComission.Name+" 에서 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+". 나는 그의 지시에 따라 행동하지.";
				link.l1.go = "CaptainComission_91";
			}
			if(pchar.GenQuest.CaptainComission.AfterTavernSpeak == "badSpeak")
			{
				dialog.text = "감사합니다, 선장님. 누구를 위해 행동하는지는 모르겠지만, 아무리 초라한 자유라도 아무리 좋은 노예 생활보다 낫지요.";
				link.l1 = "무슨 뜻이야?";
				link.l1.go = "CaptainComission_92";
			}
		break;
		
		case "CaptainComission_91":
			dialog.text = "만약 당신 계획에 큰 지장이 없다면, 제발 저를 그에게 데려다 주십시오. 이 모든 것에 정말 너무 지쳤습니다.";
			link.l1 = "당연히 내가... 우리가 여기서 살아서 나갈 수만 있다면 말이지.";
			link.l1.go = "CaptainComission_91End";
		break;
		
		case "CaptainComission_91End":
			pchar.GenQuest.CaptainComission = "toOurTavern";
			rChar = CharacterFromID("CapComission_Slave");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_92":
			dialog.text = "내 자유를 위해 돈을 낸 자들의 이름을 알 수 있을까?";
			link.l1 = "사실, 나 돈 못 받았어. 선택의 여지가 없었지.";
			link.l1.go = "CaptainComission_93";
		break;
		
		case "CaptainComission_93":
			dialog.text = "그래, 내 의심이 맞았군. 너는 억지로 그렇게 하게 된 거였지, \n "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.Nation))+"?";
			link.l1 = "그래, 맞아 "+pchar.GenQuest.CaptainComission.Name+" 에서 온 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Gen")+".";
			link.l1.go = "CaptainComission_94";
		break;		
		
		case "CaptainComission_94":
			iNation = FindEnemyNation2NationWithoutPirates(sti(pchar.GenQuest.CaptainComission.Nation));	// mitrokosta
			if(iNation == -1) iNation = rand(NON_PIRATES);
			pchar.GenQuest.CaptainComission.SlaveCity = FindAlliedColonyForNation(iNation, true);
			pchar.GenQuest.CaptainComission.EnemyNation = iNation;
			LAi_SetImmortal(npchar, true);// лесник . откатил .  и защиту  чтоб умники не убили.
			dialog.text = "뭐라고 약속받았는지 모르겠지만, 조건은 이거야: 나를 의 선술집으로 데려가. "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.SlaveCity+"Gen")+", 거기라면 정말 안전할 거야. 대신 내가 가진 정보를 좀 나눠주지.";
			link.l1 = "그거면 됐지, 어차피 놈들은 아직 아무 약속도 안 했으니까. 나랑 같이 가자, 내 배까지 데려다줄게.";
			link.l1.go = "CaptainComission_95";
			link.l2 = "나는 수상쩍은 정보 때문에 괜히 내게 문제를 끌어들이고 싶지 않아.";
			link.l2.go = "CaptainComission_96";
		break;	
		
		case "CaptainComission_95":
		AddQuestRecord("CaptainComission1", "12"); // поставил запись в СЖ лесник
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);
			AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.SlaveCity + "Acc"));
			pchar.GenQuest.CaptainComission = "toEnemyTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_96":
			dialog.text = "유감이지만, 지금은 당신에게 밝힐 수 없어. 이건 우리 둘 모두에게 문제가 될 수 있거든.";
			link.l1 = "더더욱 그렇지... 따라와, 그리고 멍청한 짓 하지 마라. 다시 한 번 체포된 줄 알아.";
			link.l1.go = "CaptainComission_97";
		break;
		
		case "CaptainComission_97":	
            AddQuestRecord("CaptainComission1", "13");
			AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
			AddQuestUserData("CaptainComission1", "sSum", pchar.GenQuest.CaptainComission.SlaveMoney);		
			pchar.GenQuest.CaptainComission = "toTavern";
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GeneratePatrol");
		break;
		
		case "CaptainComission_100":		
			dialog.text = "감사합니다, 선장님. 이제야 드디어 안전해졌군요. 돈을 드리진 않겠습니다. 지식과 그 지혜로운 활용이 썩어 없어질 금속보다 훨씬 더 가치 있다고 확신하니까요.";
			link.l1 = "나는 정보를 기다리고 있다";
			link.l1.go = "CaptainComission_101";
		break;
		
		case "CaptainComission_101":
			GetSlaveSpeciality();
			dialog.text = "문제는, 나는 과학자이자, 전문가지. "+pchar.GenQuest.CaptainComission.SlaveSpeciality+" 그리고 "+NationNamePeople(sti(pchar.GenQuest.CaptainComission.EnemyNation))+" 꽤 오랜 시간 동안 나에게 협력을 제안해 왔지,"+"하지만 나는 군사 공학자이며 충성의 맹세를 지키지. 놈들이 나를 납치하려 했지만, 진짜 문제는 해적들이 내 정체와 중요성을 알게 되면서부터 시작됐지\n"+"결국 그놈들이 나를 잡아냈지. 하지만 그자들이 원한 건 오직 금뿐이었어; 내 지식 따위엔 관심도 없더군. 내 친구들도, 원수들도 제때 몸값을 내지 못해서 나는 플랜테이션에 팔려갔어. 그 다음 이야기는 알겠지.";
			link.l1 = "그래, 말 그대로 재수 없는 일이로군.";	
			link.l1.go = "CaptainComission_102";
		break;
		
		case "CaptainComission_102":
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					sTemp = "protecting your ship and its crew during combat.";
				break;	
				case 1:
					sTemp = "quickly reloading your cannons and firing aimed shot under conditions of dusting. ";
				break;					
				case 2:
					sTemp = "quickly managing the sails and maneuvering in combat.";
				break;					
			}
			dialog.text = "글쎄, 그렇게 말할 수도 있지. 그러니 내가 하는 말을 잘 듣기만 하면, 그 기술에 훨씬 더 능숙해질 거야. "+sTemp;
			link.l1 = "고맙다, 그 정보 정말 유용하군.";
			link.l1.go = "CaptainComission_103";
		break;
		
		case "CaptainComission_103":
			dialog.text = "그래, 잘 가. 그리고 모든 것에 감사해.";
			link.l1 = "고맙다. 잘 가라, 다음엔 잡히지 않도록 해.";
			link.l1.go = "CaptainComission_104";
		break;
		
		case "CaptainComission_104":
			AddQuestRecord("CaptainComission1", "21");
			CloseQuestHeader("CaptainComission1");
			// а теперь раздача слонов !!!!!!!
			switch(sti(pchar.GenQuest.CaptainComission.Speciality))
			{
				case 0:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_DEFENCE, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_REPAIR, 10);
					}					
				break;
				case 1:
					if(hrand(1) == 0) 
					{
						AddCharacterSkill(pchar, SKILL_CANNONS, 10);
					}
					else
					{
						AddCharacterSkill(pchar, SKILL_ACCURACY, 10);
					}	
				break;
				case 2:
					AddCharacterSkill(pchar, SKILL_SAILING, 10);
				break;
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "","OpenTheDoors", -1.0);
			NPChar.lifeDay = 0;
			DeleteAttribute(pchar,"GenQuest.CaptainComission");
			DialogExit();
		break;
		// Генератор "Captain's request"
		
		// Генератор "Operation 'Galleon'"
		case "CaptainComission_300":
			ReOpenQuestHeader("CaptainComission2");
			AddQuestRecord("CaptainComission2", "1");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //ПРАВКА
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCapName",  pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipTypeNom", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name"))));
			AddQuestUserData("CaptainComission2", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City1 + "Gen"));
			AddQuestUserData("CaptainComission2", "sCity11", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));			
			SetFunctionLocationCondition("CaptainComission_GenerateQuestContinuation", GetArealByCityName(pchar.GenQuest.CaptainComission.City), false);
			SetFunctionTimerCondition("CaptainComission_TimeIsOver", 0, 0, 15, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission");
			LAi_KillCharacter(NPChar);
			LAi_SetPlayerType(pchar); 
			pchar.GenQuest.CaptainComission = "Begin_1";
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			DialogExit();			
		break;
		
		// диалог с кэпом на палубе 
		case "CaptainComission_301":
		    if (!CheckAttribute(pchar,"GenQuest.pizdezh_uze_bil")) // проверка если разговор уже состоялся . чтобы не повторяться. лесник
			{
			pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			dialog.text = RandPhraseSimple("이봐, 나는 선장이야 "+GetFullName(NPChar)+", 무슨 일로 내 배 갑판에 왔지 '"+pchar.GenQuest.CaptainComission.ShipTypeName+"'?'","아, 내 배에 손님이 오는 건 언제나 반갑소. 선장 "+GetFullName(NPChar)+" 명령만 내리십시오.");
			link.l1 = "안녕, 내가 선장이야 "+GetFullName(pchar)+", 어떤 선장을 대신해서 행동 중 "+pchar.GenQuest.CaptainComission.CapName+". 그가 당신에게 곧 체포될 거라고 전해 달라고 했어 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". 당국이 알고 있어 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+"."; // ПРАВКА + belamour gen
			link.l1.go = "CaptainComission_302";
			break;
			}
			dialog.text = "여기서 대체 뭐 하는 거야? 다 준비해 놨잖아! 네 배로 돌아가!";
			link.l2 = "어... 그래, 맞아!";
			link.l2.go = "exit";
			NextDiag.TempNode = "CaptainComission_301"; // чтобы не было перехода на баг  - и т.д.  лесник 
			
		break;
		
		case "CaptainComission_302":
			dialog.text = "아, 참 안타깝군! 잠깐 생각 좀 해보자\n그런데 선장은 어디 있지? "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "그는 죽었어.";
			link.l1.go = "CaptainComission_303";
		break;
		
		case "CaptainComission_303":
			dialog.text = "젠장! 상황이 점점 더 나빠지고 있어... 이봐,\n "+GetFullName(pchar)+", 이런 상황을 맞이할 준비가 안 됐소, 선장 "+pchar.GenQuest.CaptainComission.CapName+" 그리고 나는 ~에서 만나기로 했어 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City+"Voc")+". 원래 계획은 그의 배에 화물을 싣는 거였어. 이제 선장이 죽었으니, 내가 정착지에 나타날 수도 없어\n이제 남은 건 너한테 부탁하는 것뿐인 것 같아.";
			link.l1 = "내가 동의할지는 네가 어떤 도움을 원하는지에 달려 있다.";
			link.l1.go = "CaptainComission_304";
		break;
		
		case "CaptainComission_304":
			pchar.GenQuest.CaptainComission.ShoreLocation = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "사람들과 보트 좀 도와줘. 화물을 저기서 옮겨야 해. "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+". 죽은 선장의 몫은 네가 가져도 된다.";
			link.l1 = "흠... 보아하니 네가 감당할 수 없는 일에 덤빈 것 같군. 더 많은 정보가 필요해.";
			link.l1.go = "CaptainComission_305";
			link.l2 = "유감이지만, 나는 그 일에 시간을 낭비할 처지가 아니오.";
			link.l2.go = "CaptainComission_306";
		break;
		
		case "CaptainComission_305":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "좋아, 자세한 내용을 알려주지\n"+"정기 순찰 중에 나는 깃발을 단 배 한 척을 마주쳤다 "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". 놈들이 내 항복 명령을 무시했어."+"짧은 추격 끝에 우리가 따라잡았을 때\n "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"' 그래서 놈들이 흑기를 올렸지. 요새가 꽤 멀어서 우리끼리 싸워야 했어. 놈들이 우리 앞돛대까지 박살내서, 결국 적들이 배에 올라오는 걸 피할 수가 없었지.\n"+"아슬아슬했지만, 성모 마리아와 머스킷 부대 덕분에 놈들을 전부 해치웠지. 우리가 알게 되었을 때의 기쁨을 상상해 봐라\n "+sTemp+" 로 가득 찼다. "+"우리는 이 정도 보상이면 우리 상처와 전우들의 죽음에 합당하다고 결정했다\n이미 어두워졌고, 우리는 가져갔다 "+sTemp+" 가장 가까운 만으로 가서 짐을 육지에 숨겼지. 그러고 나서 우리는 폭파시켰어\n "+sTemp+" 그리고 나는 침몰한 해적선을 보고했지. 물론, 화물에 대해서는 언급하지 않았어.";
			link.l1 = "아무래도 누군가 아직도 떠벌렸나 보군...";	
			link.l1.go = "CaptainComission_307";
		break;
		
		case "CaptainComission_306":
			dialog.text = "안타깝군, 선장... 네가 나를 도울 생각이 없다니 유감이야.";
			link.l1 = "그건 내 의지로 되는 일이 아니야, 내 친구. 이해해 줘야 해. 잘 가.";
			link.l1.go = "CaptainComission_306End";			
		break;
		
		case "CaptainComission_306End":
			AddQuestRecord("CaptainComission2", "3");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.CapName);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "", 1.5);			
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
		break;
		
		case "CaptainComission_307":
			dialog.text = "내 사람들은 아닌 것 같아. 아마도 화물 주인이 손해를 조금이라도 덜고 싶어서 그런 거겠지\n그래서? 네 도움이 필요하다는 건데, 도와줄 수 있겠나?";
			link.l1 = "그래, 좋아.";
			link.l1.go = "CaptainComission_308";
			link.l2 = "아니, 친구야. 첫째: 내 창고에 얼마나 많은 화물이 들어올지 나도 몰라. 그리고 둘째: 당국이 이미 그걸 찾아서 가져가고, 은신처에 매복조를 남겨뒀을 수도 있다는 보장이 없어.";
			link.l2.go = "CaptainComission_309";
		break;
		
		case "CaptainComission_308":
			dialog.text = "~에서 만나자 "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+" 그러면 자정이 막 지난 후에. 지금 내 위치는 비밀로 해야 해. 순찰대를 피해 다녀야 해."; // belamour gen
			link.l1 = "알겠어, 거기서 기다려.";
			link.l1.go = "CaptainComission_313";
//			bQuestDisableMapEnter = true;
		break;
		
		case "CaptainComission_309":
			dialog.text = "유감이지만, 네가 선택지를 안 주는군. 배 한 척으론 모든 화물을 실을 수 없어. 난 이 일에 내 경력과 목숨까지 걸었어. 네 선원들도 괜찮은 몫을 준다면 기꺼이 도와줄 거라 생각한다.";
			link.l1 = "그래서 네가 제안하는 게 뭐야?";
			link.l1.go = "CaptainComission_310";
		break;
		
		case "CaptainComission_310":
			dialog.text = "네 배는 내가 가져가고, 넌 여기 남겨두겠다 "+XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation+"Gen")+"."; // belamour gen
			link.l1 = "네가 성공할 것 같진 않군. 네 선원 전부를 베어 넘겨서라도 나는 내 배로 돌아갈 거다.";
			link.l1.go = "CaptainComission_311";
			link.l2 = "별 수 없군. 좋아, 폭력에 굴복하겠다...";
			link.l2.go = "CaptainComission_312";
		break;
		
		case "CaptainComission_311":
			pchar.GenQuest.CaptainComission.FightAfterDeck = true; //после резни на палубе - драка в море		
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "CaptainComission_FightInDeck", 3.5);
			DialogExit();
		break;
		
		case "CaptainComission_312":
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_toShore");
		break;
		
		case "CaptainComission_313": 		
			NextDiag.TempNode = "CaptainComission_314";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddQuestRecord("CaptainComission2", "7");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreNameDat", XI_ConvertString(pchar.GenQuest.CaptainComission.ShoreLocation + "Dat"));
			SetFunctionTimerCondition("CaptainComission_SailToShore", 0, 0, 1, false);
		    pchar.GenQuest.pizdezh_uze_bil = "true"; // лесник временная запоминалка для диалога 
			DialogExit();			
		break;
		
		case "CaptainComission_314":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = "선장님, 서둘러야 합니다. 순찰대가 우리를 발견할까 두렵습니다.";
			link.l1 = "좋아, 서두르자.";
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_315":
			dialog.text = "선장님, 모든 구명정을 내리라고 명령하십시오. 여러 번 왕복해야 할 테고, 순찰대가 만에 올까 두렵습니다. ";
			link.l1 = "걱정 마, 다 괜찮을 거야. 보트들이 이미 해안으로 오고 있어.";
			link.l1.go = "CaptainComission_316";
		break;
		
		case "CaptainComission_316":
			dialog.text = "젠장, 이제 귀찮은 손님까지 생겼군...";
			link.l1 = "정말이지, 바보 얘기만 하면 바로 나타난다니까...";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest.pizdezh_uze_bil"); // удаление проверки на повтор диалога лесник
			AddDialogExitQuestFunction("CaptainComission_GenerateShorePatrol");
		break;
		
		// диалог с патрулем на берегу
		case "CaptainComission_317":
			dialog.text = "선장님, 우리는 전범을 찾고 있습니다 "+pchar.GenQuest.CaptainComission.Name+", 당국의 눈을 피해 귀중한 화물을 숨긴 자로군. 서류를 내시오.";
			link.l1 = "무슨 서류요, 경관? 우리는 신선한 물을 보충하려고 상륙한 거요.";
			link.l1.go = "CaptainComission_318";
		break;
		
		case "CaptainComission_318":
			dialog.snd = "Voice\COGU\COGU004"; 
			dialog.text = "그리고 여기 그가 있네, "+pchar.GenQuest.CaptainComission.Name+" 그 자가 직접 나섰다. 둘 다 무기를 내려놓고 나를 따라와!";
			link.l1 = "정말 타이밍이 안 좋았군, 장교...";
			link.l1.go = "CaptainComission_319";
		break;
		
		case "CaptainComission_319":
			DialogExit();
			for (i = 1; i <= sti(pchar.GenQuest.CaptainComission.SoldierQty); i++)
			{
    			sTemp = "SoldierIDX" + i;
				sld = GetCharacter(sti(pchar.GenQuest.CaptainComission.(sTemp)));
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "CoastalGuards");
            }
			
			LAi_group_SetHearRadius("CoastalGuards", 100.0);			
		    sld = characterFromId("CapComission_1");
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);		
			LAi_group_SetRelation("CoastalGuards", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("CoastalGuards", LAI_GROUP_PLAYER, true);
            LAi_SetFightMode(Pchar, true);
				
		break;
		
		case "CaptainComission_320":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие если жив.
			pchar.GenQuest.CaptainComission.GoodsQty = makeint((sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) - sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Capacity")) + rand(250)) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));	
			pchar.GenQuest.CaptainComission.GoodsQtyNorm = sti(pchar.GenQuest.CaptainComission.GoodsQty);
			dialog.text = "증원군이 도착하기 전에 서둘러야 해. 적재는 거의 끝났고, 네 몫은 "+pchar.GenQuest.CaptainComission.GoodsQty+" 단위의 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+".";
			link.l1 = "훌륭해. 이제 떠날 시간이군. 너랑 거래해서 즐거웠어.";
			link.l1.go = "CaptainComission_321";
		break;
		
		case "CaptainComission_321":		
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;
			dialog.text = "그리고 한 가지만 더 부탁이 있어. 당국이 분명히 우리를 쫓아올 테니, 내 배를 호위해 줄 수 있겠나\n "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", 그것이 있는 곳은 "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+"?"; // belamour gen
			link.l1 = "아니야, 친구, 이제부터는 각자도생이야. 잘 가라...";
			link.l1.go = "CaptainComission_322";
			if (GetCompanionQuantity(pchar) < COMPANION_MAX)
			{
				link.l2 = "물론이지, 보상이 좋다면 해줄 수 있지.";
				link.l2.go = "CaptainComission_323";
			}				
		break;
		
		case "CaptainComission_322":
			Group_DeleteGroup("Sea_CapComission_1"); 
			sld = characterFromId("CapComission_1");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			sld.lifeDay = 0; 	
			CaptainComission_GenerateCoastalPatrol();
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			AddQuestRecord("CaptainComission2", "10");
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;
		
		case "CaptainComission_323":
			sld = characterFromId("CapComission_1");
			Fantom_SetCharacterGoods(sld, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoFreeSpace(sld), 1);
			pchar.GenQuest.CaptainComission.ConvoyMoney = makeint((sti(pchar.rank)*100 + sti(NPChar.rank)*170 + hRand(30)*20) * 2.5);
			pchar.GenQuest.CaptainComission.iDay  = 15 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "물론이지. 호위에 대해서라면 기꺼이 돈을 내겠어  "+pchar.GenQuest.CaptainComission.ConvoyMoney+" 페소지. 하지만 조건이 하나 더 있어: 걸리는 시간이 "+pchar.GenQuest.CaptainComission.iDay+" 며칠이야. 중요해.";	
			link.l1 = "좋아. 바로 출발하자.";
			link.l1.go = "CaptainComission_324";
			NextDiag.TempNode = "CaptainComission_325";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_324":
			pchar.GenQuest.CannotWait = 1; // лочим интерфейс отдыха 
			sld = characterFromId("CapComission_1");
			sTemp = LAi_FindNearestFreeLocator2Pchar("reload");
			LAi_SetActorType(sld);
			LAi_ActorSetStayMode(sld);
			CharacterIntoCompanionAndGoOut(pchar, sld, "reload", sTemp, 5, false);
			SetShipRemovable(sld, false);
			SetCharacterRemovable(sld, false);
			Group_ChangeCharacter(PLAYER_GROUP, "CapComission_1");
			AddQuestRecord("CaptainComission2", "11");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));		
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen"));
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(GetIslandByCityName(pchar.GenQuest.CaptainComission.ConvoyCity) + "Voc")); // belamour gen
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.ConvoyMoney);
			CaptainComission_GenerateCoastalPatrol();
			pchar.quest.CaptainComission_MapEnter.win_condition.l1 = "MapEnter";
			pchar.quest.CaptainComission_MapEnter.function = "CaptainComission_MapEnter"; 
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1 = "Character_sink";
			pchar.quest.CaptainComission_CapShip_Sink.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_CapShip_Sink.function = "CaptainComission_CapShip_Sink";
			DialogExit();
		break;
		
		case "CaptainComission_325":
			NextDiag.TempNode = "CaptainComission_314";
			dialog.text = LinkRandPhrase("선장님, 시간만 낭비하고 있습니다. 놈들이 언제든 우리를 찾을 수도 있어요.","선장님, 우리는 시간과 싸우고 있습니다. 그들이 저를 찾고 있다는 걸 잊지 마십시오.","선장님, 머뭇거릴 시간이 없습니다. 제 배는 너무 커서 순찰대의 눈을 피할 수 없습니다.");
			link.l1 = LinkRandPhrase("그래, 네 말이 맞아. 서둘러야 해.","그럼 더 지체 말고 당장 보트에 타라.","그렇다... 놈들 모아라. 이제 떠난다.");
			link.l1.go = "exit";
		break;
		
		case "CaptainComission_326_0":
			dialog.text = "선장님, 제 부하들과 얘기할 필요가 있습니다.";
			link.l1 = "계속해.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_326":
			sld = characterFromId("Blaze");
			dialog.text = "환영하오, 선장 "+pchar.CaptainComission.Name+". 그래서, 화물 전부 가져왔나? 그리고 선장은 어디 있지 "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" 죽었어. 물어봐야 했지\n "+NPCharSexPhrase(sld,"이 신사","이 아가씨")+" 도움을 청하려고. 내가 소개하지. 이분이 선장이야 "+pchar.CaptainComission.FullName+".";
			link.l1.go = "CaptainComission_327";
		break;
		
		case "CaptainComission_327":
			sld = characterFromId("Blaze");
			dialog.text = "And "+NPCharSexPhrase(sld,"그 자가 누구지? 그는","그 여자는 누구지? 그녀가\n")+" 우리 일에 대해 알고 있나?";
			link.l1 = "대체로 그래. 하지만 한 가지 문제가 있어 -"+NPCharSexPhrase(sld,"그는 확신하고 있다","그녀는 확신하고 있다")+", 화물의 절반이 ~의 것이라는 "+NPCharSexPhrase(sld,"그를","그녀의")+". 설득해야 해 "+NPCharSexPhrase(sld,"그를","그녀")+", 꼭 그런 것은 아니라는 거지.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialog");
		break;
		
		case "CaptainComission_328":
			dialog.text = "내 친구 "+GetFullName(pchar)+", 너는 이미 알아야 할 건 다 들었어. 우리는 네 화물창에 들어가야 해.";
			link.l1 = "네가 생각하기에 내 부하들이 그냥 서서 어떤 오합지졸들이 창고를 털어가는 걸 구경만 할 거 같아?";
			link.l1.go = "CaptainComission_329";
		break;
		
		case "CaptainComission_329":
			pchar.GenQuest.CaptainComission.GoodsSum = 2 * sti(pchar.GenQuest.CaptainComission.GoodsQtyNorm) * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost);
			dialog.text = "일리가 있군. 현찰로, 예를 들어, "+pchar.GenQuest.CaptainComission.GoodsSum+" 페소만 내면 네 선원들과 싸울 필요가 없겠지. 이건 우리 화물의 절반에 해당하니, 공평한 거래야. 동의하면 아무도 다치지 않을 거다.";
			link.l1 = "내가 거절하면 어쩔 건데?";
			link.l1.go = "CaptainComission_330";
		break;
		
		case "CaptainComission_330":
			dialog.text = "그렇다면, 폭력은 피할 수 없겠군. 네가 첫 번째 희생자가 될 거고, 이 아늑한 만에서 영원히 잠들게 될 거야. 네 선원들은 널 도와주러 올 수도 없지... 그거, 어떠냐?";
			link.l1 = "나한테 선택지를 안 주는군. 좋아, 다 죽여주지.";
			link.l1.go = "CaptainComission_331";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsSum))
			{
				link.l2 = "별 수 없지. 좋아, 여기 네 돈이다.";
				link.l2.go = "CaptainComission_332";
			}	
		break;
		
		case "CaptainComission_331":
			dialog.text = "그래, 그건 어울리는 결정이지 "+GetSexPhrase("고귀한 신사","용감한 숙녀")+".";
			link.l1 = "잔소리 그만해! 본론으로 들어가자!";
			link.l1.go = "CaptainComission_334";
			CaptainComission_ChangeCaptain();
		break;
		
		case "CaptainComission_332":
			dialog.text = "현명한 결정이군. 행운을 빌어.";
			link.l1 = "그거 먹고 체하길 바란다...";
			link.l1.go = "CaptainComission_333";
		break;
		
		case "CaptainComission_333":
		    LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);// лесник - разрешить снова драться после сдачи денег. но после драки кулаками не машут ..как говориться))
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsSum));
			AddQuestRecord("CaptainComission2", "17");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", UpperFirst(XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsSum);
			CloseQuestHeader("CaptainComission2");	
			ChangeOfficersLoyality("bad_all", 1);
			DialogExit();
			AddDialogExitQuestFunction("CaptainComission_GangExit");
		break;

		case "CaptainComission_334":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_group_MoveCharacter(rChar, sGroup);
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			LAi_group_SetCheckFunction(sGroup, "CaptainComission_GangDied");
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");		
		break;

		case "CaptainComission_340":
			dialog.text = "Captain "+GetFullName(pchar)+", 우리가 늦었어. 이제 더 이상 보상을 받을 자격이 없다는 걸 이해하길 바란다.";
			link.l1 = "그래, 알고 있지. 네 덕분에 이미 꽤 벌었어. 잘 가라...";
			link.l1.go = "CaptainComission_341";
		break;
		
		case "CaptainComission_341":
			Group_DeleteGroup("Sea_CapComission_1");			
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			AddQuestRecord("CaptainComission2", "15");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");	
			DeleteAttribute(pchar, "GenQuest.CaptainComission");					
			DialogExit();
		break;
		
		case "CaptainComission_Canoneer":
			dialog.text = "왕관의 영광을 위해 전투에서 크게 고생한 늙은 병사를 위해 럼주 한 잔 사줄 수 있겠나?";
			link.l1 = "이봐, 바텐더! 럼 좀 따라라!";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_Canoneer1";
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("CaptainComission_TalkCanoneer");
		break;
		
		case "CaptainComission_Canoneer1":
			dialog.text = "아, 고마워, "+GetAddress_Form(pchar)+", 기억을 완전히 잃어버린 불구자를 도와주다니 정말 친절하군...";
			link.l1 = "완전히, 그렇다고?";
			link.l1.go = "CaptainComission_Canoneer2";
		break;
		
		case "CaptainComission_Canoneer2":
			dialog.text = "물론이죠, 아가씨"+GetSexPhrase("테르","s")+" 선장... 전혀 기억이 안 나. 내 머리로 산탄포탄이 곧장 날아오는 것만 기억나. 이 구멍 좀 봐, 아마 내 기억이 전부 이 구멍으로 새어나간 모양이야.";
			link.l1 = "이봐, 그런 한심한 이야기는 집안 아낙네들한테나 해라. 나는 산탄에 직격당해서 기억도 머리도 한 번에 날아간 놈들을 봤다... 그런데 네가 지금 무슨 허구의 체인샷 타령이냐. 선장 얘기나 하자. "+pchar.GenQuest.CaptainComission.Name+". ";
			link.l1.go = "CaptainComission_Canoneer3";
		break;
		
		case "CaptainComission_Canoneer3":
			dialog.text = "아, 뭐, 알잖아. 어떻게든 먹고살아야지. 선장에 관해서라면\n "+pchar.GenQuest.CaptainComission.Name+", 나한테 쓸데없이 떠들어봤자 이득도 없어... 그 자에 대해 묻는 질문마다 백 닢씩 받았다면, 지금쯤 총독이 백성들한테 1년 동안 걷는 세금보다 내가 더 많은 금화를 모았겠지... ";
			link.l1 = "그 선장이 숨겨 놓은 화물을 팔아 보려고 했어?";
			link.l1.go = "CaptainComission_Canoneer4";
		break;
		
		case "CaptainComission_Canoneer4":
			dialog.text = "뭐? 또 다른 꼬치꼬치 캐는 놈이냐? 다시 말하지만, 난 어떤 선장도 기억 안 나. "+pchar.GenQuest.CaptainComission.Name+"! 나 지금 머리를 다쳤다고! 의사의 진단서도 있어! 더 뭘 원하냐?!";
			link.l1 = "이봐, 그렇게 흥분하지 마. 알잖아... 그는 너무 늦었어. 선장 "+pchar.GenQuest.CaptainComission.CapName+" 그 사람이 전해 달라고 했어 "+pchar.GenQuest.CaptainComission.Name+" 그 식민지에 얼굴을 비추지 말아야 해, 당국이 파괴된 경위에 대해 알고 있으니까 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+", 그리고 그는 체포될 거야.";
			link.l1.go = "CaptainComission_Canoneer5";
		break;
		
		case "CaptainComission_Canoneer5":
			dialog.text = "휴. 그렇게 돌려 말하지 말고 바로 말하지 그랬어. 선장에게 물어본 건 나였어. "+pchar.GenQuest.CaptainComission.CapName+" 우리 배가 돌아올 때 가로채려고. "+"그 피비린내 나는 싸움 직후에 부두로 옮겨졌지. 그 망할 해적이 거기서 자기 물건을 가지고 뭘 하고 있었던 거야?! 그놈 때문에 많은 녀석들이 죽었어.";
			link.l1 = "그런데 어떻게 살아남았지?";
			link.l1.go = "CaptainComission_Canoneer6";	
		break;
		
		case "CaptainComission_Canoneer6":
			dialog.text = "실수였지. 솔직히 말하면, 내 멍청한 실수였어. 내가 충분히 빠르지 못해서 우리 장정선이 위험 구역을 벗어나지 못했거든. 하지만 피해를 입은 건 나 혼자였어. 잔해에 맞고 물에 던져졌지. 어떻게 해변까지 도착했는지도 기억이 안 나.";
			link.l1 = "그런데 어떻게 심문에서 빠져나올 수 있었지?";
			link.l1.go = "CaptainComission_Canoneer7";
		break;
		
		case "CaptainComission_Canoneer7":
			dialog.text = "나는 놈들에게 내가 선상 전투 중에 다쳤다고, 화물에 대해서는 아무것도 모른다고 했지. 그리고 바보처럼 행동했어, 알지? 겨우 몸을 추스르고 일어난 참이었으니까, 바로 그들이 도착하기 직전에 말이야\n "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name")+"Acc"))+". 제대로 움직일 수가 없었어, 몸이 말을 안 듣더라고.";
			link.l1 = "이봐, 근데 짐에 대한 비밀을 누가 떠벌린 거야, 도대체?";
			link.l1.go = "CaptainComission_Canoneer8";
		break;
		
		case "CaptainComission_Canoneer8":
			dialog.text = "해적들이 부상당한 상인을 사칭해서 총독에게 편지를 보냈어. 그놈들은 선장의 끈질김에 복수하기로 했지. 이 모든 게 다 선장 잘못이야, 저 빌어먹을 고집 때문에 우리가 이런 곤경에 빠진 거라고.";
			link.l1 = "그런데 애초에 어떻게 그 해적을 만나게 된 거야?";
			link.l1.go = "CaptainComission_Canoneer9";
		break;
		
		case "CaptainComission_Canoneer9":
			dialog.text = "모르겠어. 평범한 순찰이었고, 평범한 배가 그 깃발 아래 항해하고 있었어\n "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". 선장이 왜 그걸 조사하기로 했는지 전혀 모르겠어. 하지만 경고 사격에도 아랑곳하지 않았고, 우리가 따라잡자 '졸리 로저'를 올렸지. "+"우리는 요새의 지원을 받지 못해서 싸움이 쉽지 않았어. 그 다음엔 백병전이 벌어졌지. 아직도 우리가 어떻게 그놈들을 이겼는지 모르겠어.\n"+"그래, 그리고 우리는 그 귀한 화물을 전부 봤지. 악마가 직접 우리한테 준 게 틀림없어. 우리는 화물을 육지에 숨기고 나서, 빼앗은 배를 산산조각 내버렸어. 너무 망가져서 쓸 수가 없었거든.";
			link.l1 = "총독의 부하들이 은닉처를 발견하면 네 모든 노력과 희생이 헛수고가 될까 봐 두렵지 않냐?";	
			link.l1.go = "CaptainComission_Canoneer10";
		break;
		
		case "CaptainComission_Canoneer10":
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			pchar.GenQuest.CaptainComission.CanoneerCity = Colonies[iTmp].id;			
			pchar.GenQuest.CaptainComission.Sum = 20000 + 2000 * sti(pchar.rank);
			dialog.text = "걔네들은 절대 못 찾아. 내가 동굴 입구를 제대로 날려버렸거든. 어차피 내가 전대에서 폭약 다루는 데는 최고였으니까. 내 숨겨둔 물건은 밀수꾼들만 찾을 수 있어. 이곳 구석구석을 다 아니까.\n"+"봐, 나도 전리품을 어떻게 해야 할지 전혀 모르겠어. 혼자서 팔 수도 없고 옮길 수도 없어. 게다가 머리가 깨진 놈이랑 거래할 사람도 없지. 동료들이 죽은 걸로 이득을 보고 싶진 않지만, 은닉처 위치는 알려줄 수 있어\n "+pchar.GenQuest.CaptainComission.Sum+"  나를 데려다 주면 페소 줄게 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.CanoneerCity)+".";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				link.l1 = "동의하지. 여기 네 돈이야. 이제 말해.";	
				link.l1.go = "CaptainComission_Canoneer11";
			}
			else
			{
				link.l1 = "젠장! 좋아, 여기서 기다려. 내가 돈 가져올게.";
				link.l1.go = "CaptainComission_Canoneer12";				
			}	
			link.l2 = "너무 많아, 이봐. 게다가 나한테 맞는 배도 없어. 뭐, 행운을 빌고 잘 가라...";
			link.l2.go = "CaptainComission_Canoneer13";
		break;
		
		case "CaptainComission_Canoneer11":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.Sum));
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "그래, 알았다. 오늘 밤 자정 넘어서 근처에서 만나자\n "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+". 그리고 선창에 공간을 꼭 확보해 둬 "+pchar.GenQuest.CaptainComission.GoodsQty+" 개. "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+"... 이걸 버리면 아깝지..."; // belamour gen
			link.l1 = "그건 내가 처리하지. 만에서 보자...";
			link.l1.go = "CaptainComission_Canoneer14";
		break;
		
		case "CaptainComission_Canoneer12":
			AddQuestRecord("CaptainComission2", "41");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); //Gen лесник
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.Sum);
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			SetFunctionTimerCondition("CaptainComission_CanoneerWaitMoney", 0, 0, 1, false);
			NextDiag.TempNode = "CaptainComission_Canoneer15";
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer13":
			AddQuestRecord("CaptainComission2", "40");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"))); // belamour gen
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(NPChar);
			pchar.GenQuest.CaptainComission = "close";
			SetFunctionExitFromLocationCondition("CaptainComission_ExitFromLoc", pchar.location, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer14":
			AddQuestRecord("CaptainComission2", "43");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); 
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);			
			AddQuestUserData("CaptainComission2", "sName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_NOM));
			AddQuestUserData("CaptainComission2", "sShipTypeQuest", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen")));
			AddQuestUserData("CaptainComission2", "sShipNameQuest", pchar.GenQuest.CaptainComission.VictimShipName);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat"));	// belamour gen
			LAi_CharacterDisableDialog(NPChar);
			SetFunctionTimerConditionParam("CaptainComission_TimeIsOver", 0, 0, 1, MakeInt(24 - GetHour()), false);
			SetFunctionTimerCondition("CaptainComission_MeetCanoneerInShoreTimer", 0, 0, 1, false);
			DialogExit();
			AddDialogExitQuest("CaptainComission_exit_sit");
		break;
		
		case "CaptainComission_Canoneer15":
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.Sum))	
			{
				dialog.text = "드디어 왔군. 걱정되기 시작했었어. 그냥 날 당국에 넘길 줄 알았거든.";
				link.l1 = "아직 미치지 않았어. 자, 네 돈이야. 이제 네 차례다.";
				pchar.quest.CaptainComission_CanoneerWaitMoney.over = "yes";// лесник . снят таймер ожилания бабла
				link.l1.go = "CaptainComission_Canoneer11";
			}	
			else
			{
				dialog.text = "그래서, 돈은 어디 있지?";	
				link.l1 = "젠장! 알았어, 여기서 기다려. 내가 가져올게.";
				link.l1.go = "exit";
				NextDiag.TempNode = "CaptainComission_Canoneer15";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
		break;
		
		case "CaptainComission_350":
			dialog.text = "선장님, 우리가 늦은 것 같습니다. 밀수꾼들이 이미 은닉처를 찾아냈습니다.";
			link.l1 = "내 전리품은 절대 포기하지 않아. 악마라도 내 것 못 뺏어가.";
			link.l1.go = "CaptainComission_351";
			link.l2 = "나 그만둘 거야, 네 경쟁자들은 네가 직접 처리해.";	
			link.l2.go = "CaptainComission_352";
		break;
		
		case "CaptainComission_351":
			DialogExit();
			AddDialogExitQuest("CaptainComission_GangDialog_1");
		break;
		
		case "CaptainComission_352":
			DialogExit();
			//SetFunctionExitFromLocationCondition("CaptainComission_NoGangDialog", pchar.location, false);
			 AddDialogExitQuestFunction("CaptainComission_NoGangDialog");   // лесник - исправлено . предыдцщий код не работал
		break;
		
		case "CaptainComission_360":
			dialog.text = "선장님, 여기 심각한 문제가 있습니다. 우리 함선들이 도착하기 전에 함대를 철수시키는 것이 좋겠습니다.";
			link.l1 = "이봐, 자네들, 남의 물건을 넘보는 것 같은데.";
			link.l1.go = "CaptainComission_361";
		break;
		
		case "CaptainComission_361":
			dialog.text = "오, 정말이야?! 네가 지금 누구한테 말하고 있는지 알기나 해?";
			link.l1 = "이봐, 친구. 나는 너한테 말하고 있어. 그 화물은 정당한 주인이 있고, 내가 그 사람을 대표하고 있지.";
			link.l1.go = "CaptainComission_362";
		break;
		
		case "CaptainComission_362":
			dialog.text = "우리가 신의 메시아라 해도 우리 일에 간섭하게 두지 않겠다! 목숨이 아깝다면 항로에서 비켜라!";
			link.l1 = "내 말 못 알아들었나? 그 화물은 내 거야, 그거 없이 절대 안 떠난다!";
			link.l1.go = "CaptainComission_363";
		break;
		
		case "CaptainComission_363":
			dialog.text = "말도 안 돼! 그렇게 갖고 싶으면 여기서 영원히 기다려라!";
			link.l1 = "운명이 누가 여기 영원히 남게 될지 결정할 거다.";
			link.l1.go = "CaptainComission_364";
		break;
				
		case "CaptainComission_364":
			LAi_SetPlayerType(pchar);
			sTemp = "Gang_";
			sGroup = "GangGroup_0";			
			LAi_LocationFightDisable(&locations[FindLocation(pchar.GenQuest.CaptainComission.ConvoyShore)], false);	
			iTemp = sti(pchar.GenQuest.CaptainComission.GangNum);
			chrDisableReloadToLocation = true;
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				rChar = CharacterFromID("CapComission_1");
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);						
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				rChar = CharacterFromID("CapComission_Canoneer");
				//LAi_SetWarriorType(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_group_MoveCharacter(rChar, LAI_GROUP_PLAYER);			
			}	
			for(i = 0; i < iTemp; i++)
			{
				rChar = CharacterFromID(sTemp + i);
				LAi_SetWarriorType(rChar);
				LAi_group_MoveCharacter(rChar, sGroup);
				LAi_SetImmortal(rChar, false);
			}			
			LAi_group_SetRelation(sGroup, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups(sGroup, LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck(sGroup, "OpenTheDoors"); 
			if(pchar.GenQuest.CaptainComission.variant == "A2")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckCaptainAfterBattle");
			}
			if(pchar.GenQuest.CaptainComission.variant == "A3")
			{
				LAi_group_SetCheckFunction(sGroup, "CaptainComission_CheckGangAfterBattle");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_365":
			dialog.text = "선장님, 부하들에게 서두르라고 명령하십시오. 순찰대가 언제든 올 수 있습니다. 게다가 밀수꾼들도 분명히 자기들 운송선을 기다리고 있었던 것 같습니다.";
			link.l1 = "그래, 서둘러야 해... 화물을 창고에 실어, 그리고 여기서 나가자.";
			link.l1.go = "exit";
			NextDiag.TempNode = "CaptainComission_365";
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		
		case "CaptainComission_366":
			dialog.text = "감사합니다, 선장님 "+GetFullName(pchar)+". 당신이 아니었더라면 밀수꾼들이 우리 화물을 빼앗아 갔을 것이고, 그것을 지키다 쓰러진 이들은 헛되이 죽었을 거요...";
			link.l1 = "그리고 나를 믿어줘서 고맙다.";
			link.l1.go = "CaptainComission_367";
		break;
		
		case "CaptainComission_367":
			dialog.text = "여기 내 목숨을 구해준 작은 장신구가 하나 있어. 제발 받아줘, 네 행운의 부적이 될지도 모르잖아. 그리고 다시 한 번 고맙다, 친구. 바람이 언제나 네 편이길 바랄게.";
			link.l1 = "선물 고맙다, 기대도 안 했는데. 그리고 주머니에 동전 있을 때 건강이나 잘 챙겨라.";
			link.l1.go = "CaptainComission_368";
		break;
		
		case "CaptainComission_368":
			LAi_SetActorType(NPChar);
			LAi_SetImmortal(NPChar, true);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.LifeDay = 0;
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "48");
			AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType),"Name") + "Gen"))); // лесник окончание
			AddQuestUserData("CaptainComission2", "sShipName", pchar.GenQuest.CaptainComission.ShipTypeName);
			AddQuestUserData("CaptainComission2", "sCharName", GetName( NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.CanoneerName, NAME_ABL));
			AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.CanoneerCity + "Gen"));
			CloseQuestHeader("CaptainComission2");
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_370":
			if(pchar.GenQuest.CaptainComission == "MayorTalkBad")
			{
				pchar.quest.CaptainComission_TimeIsOver.over = "yes";
			}	
			dialog.text = "오늘이 내가 방문하는 날인 것 같군. 나 필요해?";
			link.l1 = "네가 선장이라면 "+pchar.GenQuest.CaptainComission.Name+", 그렇다면 그래.";
			link.l1.go = "CaptainComission_371";
		break;
		
		case "CaptainComission_371":
			dialog.text = "...전 선장"+pchar.GenQuest.CaptainComission.Name+"...";
			link.l1 = "나는 "+GetFullName(pchar)+", 그리고 너한테 물어볼 게 몇 가지 있어.";
			link.l1.go = "CaptainComission_372";
		break;
		
		case "CaptainComission_372":
			dialog.text = "내가 왜 그들에게 대답해야 한다고 생각하지?";
			link.l1 = "Captain "+pchar.GenQuest.CaptainComission.CapName+" 의 파괴를 둘러싼 상황에 대해 경고해 달라고 내게 부탁했어 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Acc"))+" '"+pchar.GenQuest.CaptainComission.VictimShipName+" 당국에 알려졌어, "+"하지만 나는 항해 중에 에서 온 네 배를 보지 못했어 "+XI_ConvertString("Colony"+pchar.GenQuest.CaptainComission.City1+"Gen")+".";
			link.l1.go = "CaptainComission_373";	
		break;
		
		case "CaptainComission_373":
			dialog.text = "그리고 선장은 어디 있지 "+pchar.GenQuest.CaptainComission.CapName+"?";
			link.l1 = "그는 죽었어.";
			link.l1.go = "CaptainComission_374";
		break;
		
		case "CaptainComission_374":
			dialog.text = "알겠군... 그래서 그런 거였어, 응? 이제야 많은 것들이 이해가 가는군. 누가 우리가 약탈했다는 걸 떠벌린 모양이군 "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name")+"Gen"))+". "+"조만간 그놈들이 화물을 찾아내서 나를 목매달 거야. 선장 "+pchar.GenQuest.CaptainComission.CapName+" 죽었으니, 이제 아무도 나를 도울 수 없어\n너만 빼고\n "+GetFullName(pchar)+", 여기서 나를 꺼내 주면 그만한 보상을 해주지.";
			if(!CheckAttribute(pchar,"GenQuest.CaptainComission.GetRumour"))
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "총독이 화물 주인에게서 편지를 받았어. 그리고 그 안에 적힌 숫자들이 꽤 인상적이더라고, 알지?";
					link.l1.go = "CaptainComission_375";
				}
				else
				{
					link.l1 = "하지만 내가 눈 가리고 너를 도울 거라고는 생각하지 않겠지?";
					link.l1.go = "CaptainComission_375";
				}
			}			
			else
			{
				if(CheckAttribute(pchar,"GenQuest.CaptainComission.SpeakMayor"))
				{
					link.l1 = "총독이 화물 주인에게서 편지를 받았어. 그리고 거기 적힌 숫자들이 꽤 대단하더라고, 알지?";
					link.l1.go = "CaptainComission_375";				
				}
				else
				{
					link.l1 = "식민지에선 네가 밀수업자들과 거래를 한다는 소문이 돌고 있어...";
					link.l1.go = "CaptainComission_375";				
				}
			}
		break;
		
		case "CaptainComission_375":
			sTemp = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Name") + "Gen"));
			dialog.text = "전부 다 얘기해줘야겠군.\n"+"정기 순찰 중에 나는 깃발을 단 배 한 척을 마주쳤다 "+NationNameGenitive(sti(pchar.GenQuest.CaptainComission.Nation))+". 놈들은 내 항복 명령을 무시했어. "+"우리는 도착했었지 "+sTemp+" '"+pchar.GenQuest.CaptainComission.VictimShipName+"' 잠깐 쫓아가자마자 놈들이 흑기를 올렸어. 요새가 꽤 멀어서 우리끼리 싸워야 했지. 놈들이 우리 앞돛대까지 박살내는 바람에, 결국 접전을 피할 수 없었어.\n"+"아슬아슬했지만, 성모 마리아와 머스킷 부대 덕분에 놈들을 전부 해치웠어. 우리가 알게 됐을 때의 기쁨을 상상해 봐라\n "+sTemp+" 귀중품으로 가득 차 있었어. "+"우리 상처와 동료들의 죽음에 대한 정당한 보상이라고 결정했지\n이미 어두웠지만, 우리는 어떻게든 빼앗았어 "+sTemp+" 가장 가까운 만으로 가서 짐을 육지에 숨겼지. 그 다음엔 불태웠어\n "+sTemp+" 그리고 난 침몰한 해적선을 신고했지. 물론 화물에 대해서는 언급하지 않았어.";		
			link.l1 = "네가 나를 속여 봤자 소용없을 것 같군. 그래서 제안을 하나 하지. 네가 은닉처를 보여주면, 내가 네가 원하는 어디든 이 군도 안에서 데려다 주지.";
			link.l1.go = "CaptainComission_376";
		break;
		
		case "CaptainComission_376":
			dialog.text = "하하하... 아니, 선장, 내 몫 없이 이 정착지를 떠나진 않을 거야. 교수대에 매달리더라도 말이지.";
			link.l1 = "좋아. 네 몫 절반은 줄게.";
			link.l1.go = "CaptainComission_377";
			link.l2 = "흠... 있잖아, 네 안위를 위해 내 목숨까지 걸 생각은 없어. 잘 있어라...";
			link.l2.go = "CaptainComission_378";
		break;
		
		case "CaptainComission_377":
			dialog.text = "이제야 말이 통하는군. 준비됐어\n먼저, 네 배에 날 숨겨야 해. 내가 보물이 숨겨진 만을 알려주지.";
			link.l1 = "그럼 재빨리, 그리고 함께 움직이자. 내가 네 감방을 열 테니, 따라와. 뒤처지지 말고, 요새를 나갈 때까지 질문하지 마.";
			link.l1.go = "CaptainComission_379";
		break;
		
		case "CaptainComission_378":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			sld = CharacterFromID("CapComission_1");
			sld.LifeDay = 0;
			ChangeCharacterComplexReputation(pchar,"nobility", -5);			
			AddQuestRecord("CaptainComission2", "8");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			CloseQuestHeader("CaptainComission2");
			LAi_CharacterDisableDialog(npchar);// лесник - запрет диалога
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
		
		case "CaptainComission_379":
			AddQuestRecord("CaptainComission2", "21");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1 = "NPC_Death";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition.l1.character = "CapComission_1";
			pchar.quest.CaptainComission_PrisonFree_Death.win_condition = "CaptainComission_PrisonFree_Death";
			GetCharacterPos(npchar, &locx, &locy, &locz);	
			ChangeCharacterAddressGroup(npchar, npchar.location, "reload", LAi_FindNearestFreeLocator("reload", locx, locy, locz));
			LAi_group_Register("CapComission_Prison");
			LAi_group_SetRelation("CapComission_Prison", LAI_GROUP_PLAYER, LAI_GROUP_FRIEND);
			LAi_group_SetAlarmReaction(LAI_GROUP_PLAYER, "CapComission_Prison", LAI_GROUP_ENEMY, LAI_GROUP_FRIEND);
			LAi_group_MoveCharacter(npchar, "CapComission_Prison");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_CharacterDisableDialog(npchar);
			pchar.GenQuest.CaptainComission.PrisonFree = true;
			if(pchar.GenQuest.CaptainComission == "MayorTalkGood") 
			{
				chrDisableReloadToLocation = true;	
				sld = CharacterFromId(pchar.GenQuest.CaptainComission.City + "JailOff");	
				sld.dialog.currentnode = "CapComission_PrisonFree1";
			}	
			pchar.quest.CapComission_ExitFromPrison.win_condition.l1 = "ExitFromLocation";
            pchar.quest.CapComission_ExitFromPrison.win_condition.l1.location = pchar.location;
            pchar.quest.CapComission_ExitFromPrison.win_condition = "CaptainComission_ExitFromPrison"; 
			DialogExit();
		break;		
		
		case "CaptainComission_380":
			pchar.quest.CaptainComission_GetSecretTimeIsOut.over = "yes";
			pchar.quest.CaptainComission_PrisonFree_Death.over = "yes";
			DeleteAttribute(pchar,"GenQuest.CaptainComission.canSpeakCaptain");
			DeleteAttribute(pchar,"GenQuest.CaptainComission.PrisonFree");
			pchar.GenQuest.CaptainComission = "CanGetGoods";
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(GetArealByCityName(pchar.GenQuest.CaptainComission.City));
			dialog.text = "구해줘서 고맙다. 계속 가자 "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Dat")+", 내가 은닉처가 어디 있는지 보여줄게. 야만인들이 찾기 전에 서두르자.";	// belamour gen	
			link.l1 = "우리 전부 화물을 실을 수 있을 거라고 확신해?";
			link.l1.go = "CaptainComission_381";
		break;
		
		case "CaptainComission_381":
			pchar.GenQuest.CaptainComission.GoodsQty = makeint(sti(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipTypeVictim),"Capacity")) / sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Weight));
			dialog.text = "네 말이 맞아, 충분한 공간을 확보해 둬라\n "+pchar.GenQuest.CaptainComission.GoodsQty+" 조각의 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". 이렇게 피 묻은 귀중한 전리품을 잃는 건 아깝지. 두 번 다시 이런 기회는 없을 거야.";
			link.l1 = "내가 처리할게.";
			link.l1.go = "CaptainComission_382";
		break;
		
		case "CaptainComission_382":
			AddQuestRecord("CaptainComission2", "24");
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.GoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			SetFunctionLocationCondition("CaptainComission_MeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false); 
			SetFunctionTimerConditionParam("CaptainComission_CapEscapeTimer", 0, 0, 1, MakeInt(24 - GetHour()), false);
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			chrDisableReloadToLocation = false; // Откроем выход
			DeleteAttribute(pchar,"TownEscape");
			QuestOpenSeaExit();
			DialogExit();
			AddDialogExitQuest("CanEnterToMap");
		break;
		
		case "CaptainComission_383":
			dialog.text = "선장님, 우리는 목격자가 필요 없소. 제발, 이 사람들에게 만을 떠나라고 설득해 주십시오.";
			link.l1 = "좋아, 그렇게 하자.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("CaptainComission_GangDialogGetGoods");
		break;
		
		case "CaptainComission_384":
			dialog.text = "선장님, 죄송하지만 여기는 연습하기에 좋은 곳이 아닙니다. 저 부두는 이미 다른 사람이 쓰고 있습니다.";
			link.l1 = "신사 여러분, 나는 구경하러 온 게 아니오. 여기서 볼일이 있소.";
			link.l1.go = "CaptainComission_385";
		break;
		
		case "CaptainComission_385":
			dialog.text = "여기서 해파리나 잡고 있을 시간 없어, 그러니까 배 돌려서 당장 꺼져.";
			link.l1 = "내가 너한테 나가라고 설득하는 데 시간 낭비하고 싶지 않아. 알아서 나가면 살 수 있고, 여기 남으면 영영 끝이야.";
			link.l1.go = "CaptainComission_386";
		break;
		
		case "CaptainComission_386":
			dialog.text = "내 말이 잘 안 통하는 것 같군. 좋아, 네가 죽고 싶다면야...";
			link.l1 = "이제 좀 낫군!";
			link.l1.go = "CaptainComission_364";
		break;
		
		case "CaptainComission_387":
			LAi_LocationDisableOfficersGen(pchar.GenQuest.CaptainComission.ConvoyShore, false);
			pchar.GenQuest.CaptainComission.MaxGoodsQty = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods));
			if(sti(pchar.GenQuest.CaptainComission.MaxGoodsQty) > sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.MaxGoodsQty = pchar.GenQuest.CaptainComission.GoodsQty;
			dialog.text = "여기에 도착했어. 은닉처는 저 바위틈 안에 있어. 입구는 바위로 막혀 있지. 은닉처 안에는\n "+pchar.GenQuest.CaptainComission.GoodsQty+" 단위 "+GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name+"Gen"))+". 내 몫이 절반이라는 거 기억하지?";
			link.l1 = "그럼, 물론이지. 내 부하들이 짐을 싣는 동안 시간이 좀 있어. 자, 이제 너랑 네 화물을 어디로 데려가야 하는지 얘기해 보자.";
			link.l1.go = "CaptainComission_388";
			if (!CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{	
			link.l2 = "아주 좋아. 이제 말해 봐, 내가 나눠야 할 이유라도 있나?";
			link.l2.go = "CaptainComission_389";
			}
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				link.l3 = "Captain "+pchar.GenQuest.CaptainComission.Name+", 너한테 불쾌한 소식을 전해야겠군. 나는 총독 일을 하고 있어. 그리고 네가 숨긴 모든 화물을 그에게 넘길 생각이야. 감옥으로 돌아가서 네 운명을 기다리는 게 좋을 거다.";
				link.l3.go = "CaptainComission_389";
				link.l2 = "아주 좋아. 그런데 말이지... 처음엔 널 당국에 넘기려고 했어, 하지만 지금은 그럴 이유가 없지? 그리고 왜 너랑 나눠야 하지?";
			    link.l2.go = "CaptainComission_3899"; // // лесник . отдельный диалог в случае обмана всех.
			}	
		break;
		
		case "CaptainComission_388":
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			iTmp = FindNonEnemyColonyForAdventure(sti(pchar.GenQuest.CaptainComission.Nation),pchar.GenQuest.CaptainComission.City, true);			
			sTemp = Colonies[iTmp].id;
			pchar.GenQuest.CaptainComission.ConvoyIsland = GetArealByCityName(sTemp);
			pchar.GenQuest.CaptainComission.ConvoyShore = SelectQuestShoreLocationFromSea(pchar.GenQuest.CaptainComission.ConvoyIsland);
			pchar.GenQuest.CaptainComission.ConvoyCity = sTemp;			
			pchar.GenQuest.CaptainComission.iDay  = 20 + hRand(10);
			iGoods = GetSquadronFreeSpace(pchar, sti(pchar.GenQuest.CaptainComission.Goods)); 
			if(iGoods < sti(pchar.GenQuest.CaptainComission.GoodsQty)) pchar.GenQuest.CaptainComission.GoodsQty = iGoods;
			SetCharacterGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods), GetCargoGoods(pchar, sti(pchar.GenQuest.CaptainComission.Goods)) + sti(pchar.GenQuest.CaptainComission.GoodsQty));// перегруз
			dialog.text = "나는 가야 해 "+XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore+"Gen")+", 에 "+XI_ConvertString(GetIslandByCityName(sTemp)+"Voc")+" 위해 "+pchar.GenQuest.CaptainComission.iDay+" 일이지. 거기 있는 내 사람들이 화물을 팔 준비를 마쳤을 거야."; // belamour gen
			link.l1 = "좋아. 이제 떠날 시간이군.";
			link.l1.go = "CaptainComission_391";
		break;
		case "CaptainComission_3899": // лесник . отдельный диалог в случае обмана всех.
		    DeleteAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood");
			ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
		    pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "그래. 언제나 가슴이 아니라 머리를 믿어야 하지. 살면서 배우는 거야.\n이런 일이 올 줄은 몰랐지만, 나는 언제든 싸울 준비가 되어 있다. 배신에 대한 대가를 치르게 해주마.";
			link.l1 = "글쎄, 운이 좋으면...";
			link.l1.go = "CaptainComission_390";
			SetFunctionTimerConditionParam("CaptainComission_NaebalGubera", 0, 0, 1, MakeInt(24 - GetHour()), false);
		break;
		
		case "CaptainComission_389":
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник . снял событие ,иначе в СЖ не то пишут.
			dialog.text = "맞아. 항상 마음이 아니라 이성을 믿어야 하지. 살면서 배우는 거지\n이런 상황은 예상 못 했지만, 싸울 준비는 언제나 되어 있어. 배신에 대한 대가는 치르게 될 거다.";
			link.l1 = "나는 당신을 위해 준비되어 있소...";
			link.l1.go = "CaptainComission_390";
		break;
		
		
		case "CaptainComission_390":
			LAi_SetPlayerType(pchar);
			LAi_group_Delete("EnemyFight");
			chrDisableReloadToLocation = true;
			rChar = CharacterFromID("CapComission_1");
			LAi_SetWarriorType(rChar);
			LAi_SetImmortal(rChar, false);// лесник.  
			LAi_group_MoveCharacter(rChar, "EnemyFight");		
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors"); 			
			if(pchar.GenQuest.CaptainComission == "CapDuel")
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CaptainDiedDuel");
			}
			else
			{
				LAi_group_SetCheckFunction("EnemyFight", "CaptainComission_CheckCaptainDied");
			}	
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");						
		break;
		
		case "CaptainComission_391":
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			GetCharacterPos(NPChar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			pchar.GenQuest.CaptainComission.CapGoodsQty = sti(pchar.GenQuest.CaptainComission.GoodsQty)/2;
			if(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) > sti(pchar.GenQuest.CaptainComission.MaxGoodsQty)) pchar.GenQuest.CaptainComission.CapGoodsQty = pchar.GenQuest.CaptainComission.MaxGoodsQty;
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))AddQuestRecord("CaptainComission2", "53");// лесник. выбор записи в СЖ
			else AddQuestRecord("CaptainComission2", "26");// смотря по какому пути пошел 
			AddQuestUserData("CaptainComission2", "sGoodsQuantity", pchar.GenQuest.CaptainComission.MaxGoodsQty);
			AddQuestUserData("CaptainComission2", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Name + "Gen")));
			AddQuestUserData("CaptainComission2", "sSum1", pchar.GenQuest.CaptainComission.CapGoodsQty);
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sDays", pchar.GenQuest.CaptainComission.iDay);
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Dat")); // belamour gen
			AddQuestUserData("CaptainComission2", "sShoreType", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyIsland + "Gen")); // belamour gen
			OfficersReaction("bad");
			if(CheckAttribute(pchar,"GenQuest.CaptainComission.MayorTalkGood"))
			{
				ChangeCharacterComplexReputation(pchar,"nobility", -5);
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -10);
			}
			CaptainComission_GenerateCoastalPatrol();
			pchar.GenQuest.CaptainComission = "GetGoodsEscape";
			SetFunctionLocationCondition("CaptainComission_CapMeetInShore", pchar.GenQuest.CaptainComission.ConvoyShore, false);
			SaveCurrentQuestDateParam("GenQuest.CaptainComission.DeleiveCapShore");	
			DialogExit();
		break;
		
		case "CaptainComission_392":
			dialog.text = "우리가 늦은 것 같군... 손님들이 기다리지 않았고, 내가 직접 화물을 보관하고 팔 방법도 없어...";
			link.l1 = "이 점에 대해 특별한 제안이라도 있나?";
			link.l1.go = "CaptainComission_393";
		break;
		
		case "CaptainComission_393":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Captain "+GetFullName(pchar)+", 좀 어색한 건 알지만... 내 몫을 돈으로 받을 수 있을까? 그런가 해서, "+pchar.GenQuest.CaptainComission.GoodsPrice+" 페소가 괜찮은 타협이 될 수 있겠군.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				link.l1 = "그래, 괜찮은 값이야. 신경 안 써. 여기 돈이야, 잘 가라.";
				link.l1.go = "CaptainComission_394";
			}
			link.l2 = "오, 안 돼, 친구야, 그건 안 되지. 내가 너를 영원히 돌볼 순 없어. 네가 화물을 가져가고 싶지 않다면, 그냥 내가 가질 거야. 걱정 마, 내가 어떻게든 보관해서 결국 팔아치울 방법을 찾을 테니까.";
			link.l2.go = "CaptainComission_3951";
		break;
		
		case "CaptainComission_394":
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			dialog.text = "잠깐만요, 선장님. 저를 구해주셔서 감사드리고 싶어요. 사실 거의 희망을 잃을 뻔했거든요... 여기요, 이 장신구가 여러 어려운 상황에서 꽤 쓸모 있을 거예요... 이제 안녕히 가세요.";
			link.l1 = "고맙다. 그럴 줄은 몰랐지. 거래해서 즐거웠어.";
			link.l1.go = "CaptainComission_395";
		break;
		
		case "CaptainComission_3951": // лесник . верное назначение диалога
			pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes";
			dialog.text = "너한테 그런 짓을 당할 줄은 몰랐는데... 어쩔 수 없군, 결투를 신청할 수밖에.";
			link.l1 = "저는 당신을 위해 준비되어 있습니다...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
		break;
		
		case "CaptainComission_395":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "32");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen")); // belamour gen
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");	
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;

		case "CaptainComission_396_0":
			dialog.text = "선장님, 제 부하들과 얘기할 필요가 있습니다.";
			link.l1 = "계속해.";
			link.l1.go = "exit";
			InterfaceStates.Buttons.Save.enable = false; 
			AddDialogExitQuestFunction("CaptainComission_DialogInShore");
		break;
		
		case "CaptainComission_396":
			sld = characterFromId("Blaze");
			dialog.text = "환영하오, 선장 "+GetFullName(pchar)+". 그래서, 화물을 전부 가져왔나? 그리고 선장은 어디 있지 "+pchar.CaptainComission.CapName+"?";
			link.l1 = pchar.CaptainComission.CapName+" 죽었고, 나는 밀고로 체포당했지. 그리고 만약 선장이\n "+pchar.CaptainComission.FullName+" 나를 도와주지 않았다면, 너는 나도 화물도 못 봤을 거야.";
			link.l1.go = "CaptainComission_397";
		break;
		
		case "CaptainComission_397":
			sld = characterFromId("Blaze");
			dialog.text = "And "+NPCharSexPhrase(sld,"그자는 누구지? 그는","그 여자는 누구지? 그녀가")+" 우리 일에 대해 알고 있나?";
			link.l1 = "물론이지. "+NPCharSexPhrase(sld,"그가 뽑아냈어","그녀가 뽑아냈어")+" 나를 감옥에서 꺼내 주고 여기로 화물의 절반을 가져오기로 했지; 나머지 절반은 내가 약속했어 "+ NPCharSexPhrase(sld, "그를","그녀") +" 보상으로.";
			link.l1.go = "CaptainComission_398";
		break;
		
		case "CaptainComission_398":
			sld = characterFromId("Blaze");
			dialog.text = "에이, 선장, 그럴 수는 없어. 그건 네 문제야! 나는 배를 빼앗고 떠나자고 했지만, 넌 네 빌어먹을 출세만 신경 썼지. 그래서 이렇게 됐잖아, 네가 그렇게 아끼던 총독이 널 감옥에 쳐넣었네."+" 네 몫은 절반에도 못 미쳤어! 우리 목숨 걸고 포탄 아래서 싸운 게 네가 혼자 절반 챙기라고 그런 줄 알아?";
			link.l1 = "이봐, 보스운, 배가 완전히 난파된 거 기억 안 나? 거의 물에 잠길 뻔했잖아? 내가 이 자에게 절반을 주지 않았으면, 너는 화물 한 조각도 다시는 못 봤을 거라는 걸 모르겠어?";	
			link.l1.go = "CaptainComission_399";
		break;
		
		case "CaptainComission_399":
			dialog.text = "날 속일 수 있을 거라 생각하지 마! 네가 우리와 한패가 아니란 걸 우리가 어떻게 알아? 혹시 체포 같은 건 애초에 없었던 거 아니야? 아니면 네가 욕심이 지나쳐서 우리 물건을 훔치기로 한 건가? 우리가 칼 쓰는 법을 잊었다고 생각하는 거야?!\n";
			link.l1 = "미쳤구나. 네 귀에는 동전 소리밖에 안 들리는군.";
			link.l1.go = "CaptainComission_400";
		break;
		
		case "CaptainComission_400":
			sld = characterFromId("Blaze");
			dialog.text = "이봐, 얘들아! 우리 선장이 지금 어떻게 말하는지 좀 봐라! 정말이지, 탐욕이 완전히 그를 집어삼켰어! 우리 몫을 팔아넘겼다니까\n "+NPCharSexPhrase(sld,"악당놈","여자 모험가")+"!!";
			link.l1 = "지금 그 더러운 입 다물어, 아니면 영원히 조용하게 만들어 주겠다!";
			link.l1.go = "exit";
			AddDialogExitQuest("CaptainComission_ShoreGangDialog");
		break;
		
		case "CaptainComission_401":
			dialog.text = "죄송합니다, 선장님, 이런 어이없는 광경을 직접 보시고 심지어 참여까지 하시게 해서요. 불과 한 달 전만 해도 우리는 하나 된 선원이었고, 우리 모두가 기꺼이 친구를 구하기 위해 목숨도 내놓을 각오였다는 게 믿기지 않습니다.";
			link.l1 = "솔직히 말해서, 그건 상상도 안 가. 기분 나쁘게 듣지 마.";
			link.l1.go = "CaptainComission_402";
		break;
		
		case "CaptainComission_402":
			dialog.text = "안타깝게도, 내가 직접 화물의 보관과 판매를 조직할 기회가 없어...";
			link.l1 = "이 점에 대해 특별히 제안할 것이 있나?";
			link.l1.go = "CaptainComission_403";
		break;
		
		case "CaptainComission_403":
			pchar.GenQuest.CaptainComission.GoodsPrice = makeint(sti(pchar.GenQuest.CaptainComission.CapGoodsQty) * 0.75 * sti(Goods[sti(pchar.GenQuest.CaptainComission.Goods)].Cost));
			dialog.text = "Captain "+GetFullName(pchar)+", 좀 어색한 건 알지만... 내 몫을 돈으로 받을 수 있을까? 그런가 해서, "+pchar.GenQuest.CaptainComission.GoodsPrice+" 페소가 괜찮은 타협이 될 수도 있겠군.";
			if(sti(pchar.money) >= sti(pchar.GenQuest.CaptainComission.GoodsPrice))
			{
				pchar.quest.CaptainComission_Capitan_Cdox.over = "yes"; // на всякий случай .лесник
				pchar.quest.CaptainComission_Capitan_Cdoxul.over = "yes"; // лесник
				link.l1 = "좋아, 상관없어. 여기 네 돈이야, 그리고 잘 가라.";
				link.l1.go = "CaptainComission_404";
			}	
			link.l2 = "안 돼, 그건 안 통하지. 네 화물을 가져가든 창고에 두든 상관없지만, 나는 동전 한 푼도 안 줄 거야.";
			link.l2.go = "CaptainComission_405";
		break;
		
		case "CaptainComission_404":
			bTemp = false;
			if(hrand(1) == 0)
			{
			    NPChar.reputation = 60 + rand(20); 
				NPChar.alignment = "good"; 
			}	
			else
			{
			    NPChar.reputation = 10 + rand(20); 
				NPChar.alignment = "bad"; 			
			}
			if (NPChar.alignment == "good" && sti(pchar.reputation.nobility) > 50) bTemp = true; 
			if (NPChar.alignment == "bad" && sti(pchar.reputation.nobility) <= 50) bTemp = true;
			
			addMoneyToCharacter(pchar, -sti(pchar.GenQuest.CaptainComission.GoodsPrice));
			
			if(!bTemp || FindFreeRandomOfficer() < 0)
			{
				dialog.text = "잠깐만요, 선장님. 저를 구해주셔서 감사드리고 싶었습니다. 사실 거의 희망을 잃을 뻔했거든요... 여기요, 이 장신구가 여러 어려운 상황에서 분명히 도움이 될 거예요... 이제 안녕히 가십시오.";
				link.l1 = "고맙다. 이런 일은 예상 못 했지. 같이 거래해서 즐거웠어.";
				link.l1.go = "CaptainComission_406";
			}
			else
			{
				dialog.text = "잠깐만... 방금 생각났어... 있잖아, 내 경력은 이제 끝났고, 선원도 없고, 고향에서는 추방자 신세야. 분명히 입 다물고 손이 믿음직한 놈들이 필요할 거 아냐. 제발 나를 네 선원으로 받아줘. 절대 후회하지 않게 하겠어.";
				if(!CaptainComission_CheckAllPassengersHired())
				{
					link.l1 = "솔직히 말해서, 나는 한동안 네가 동의해 주길 기다리고 있었어. 물론이지. 배에서 보자.";
					link.l1.go = "CaptainComission_407";
				}	
				link.l2 = "흠... 있잖아, 네가 누구 밑에서 일하기엔 너무 약삭빠른 것 같은데. 잘 가라...";
				link.l2.go = "CaptainComission_408";
			}
		break;
		
		case "CaptainComission_405":
			dialog.text = "흠, 오늘은 정말 운이 없는 날인 것 같군... 좋아, 선장, 칼을 뽑고 한 번에 끝내자고...";
			link.l1 = "나는 당신을 위해 준비되어 있소...";
			link.l1.go = "CaptainComission_390";
			pchar.GenQuest.CaptainComission = "CapDuel";
			pchar.GenQuest.CaptainComission.Duel = true;
		break;
		
		case "CaptainComission_406":
			GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
			AddQuestRecord("CaptainComission2", "34");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);			
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			DialogExit();
		break;
	
		
		case "CaptainComission_407":	
			AddQuestRecord("CaptainComission2", "36");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");		
			npchar.CaptainComission = true;
			SetCharacterRemovable(Npchar, true);
			DeleteAttribute(pchar, "GenQuest.CaptainComission");
			NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
			NPChar.Dialog.CurrentNode = "hired";
            NPChar.greeting = "Gr_Officer"; 			
			NPChar.quest.OfficerPrice = sti(pchar.rank)*500;	
			NPChar.loyality = MAX_LOYALITY;
			DeleteAttribute(NPChar, "LifeDay");
			NPChar.id = "GenChar_" + NPChar.index;// лесник . смена ИД при взятии в оффы. 
			pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(NPChar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired"); 
			NPChar.quest.meeting = true; 
			DialogExit();
		break;		
		
		case "CaptainComission_408":
			AddQuestRecord("CaptainComission2", "35");
			AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("",""));
			AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
			AddQuestUserData("CaptainComission2", "sSum", pchar.GenQuest.CaptainComission.GoodsPrice);
			CloseQuestHeader("CaptainComission2");
			GetCharacterPos(pchar, &locx, &locy, &locz);
			LAi_SetActorType(NPChar);
			LAi_ActorGoToLocation(NPChar, "reload", LAi_FindNearestLocator("reload", locx, locy, locz), "none", "", "", "OpenTheDoors", 5.0);						
			NPChar.lifeDay = 0; 						
			DeleteAttribute(pchar, "GenQuest.CaptainComission");		
			DialogExit();
		break;		
		// Генератор "Operation 'Galleon'"
		
		// Квест "meeting in the cove" -->
		// Офицер
		case "ContraMeetManQuest_Sold_1":
			dialog.text = "네가 알 바 아니야. 이제 말해 봐, 여기서 뭘 뒤지고 있는 거지? 방금 체포된 남자를 찾고 있는 거 아니야?!";
				link.l1 = "남자?! 아니...";
				link.l1.go = "ContraMeetManQuest_Sold_2";
			break;
			
		case "ContraMeetManQuest_Sold_2":
			dialog.text = "잘됐군. 아니었으면 너도 저 자식이랑 같이 감옥에 갇혔을 거야. 그러니까 여기서 얼쩡거리지 마, 선원. 꺼져!";
				link.l1 = "그래, 나도 가는 게 좋겠지...";
				link.l1.go = "ContraMeetManQuest_Sold_3";
			break;
			
		case "ContraMeetManQuest_Sold_3":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			DeleteQuestCondition("ContraMeetManQuest_TimeIsLeft"); // Время больше не роляет
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "8");
			PChar.GenQuest.ContraMeetMan.ToTavernPatrolInShore = true;
			LAi_CharacterDisableDialog(NPChar);
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			ContraMeetManQuest_DeletePatrolFromShore(); // По выходу потрем всех из локации
			break;
			
		// Сам чел
		case "ContraMeetManQuest_1":
			dialog.text = "좋아! 이제 그 밀수꾼을 찾으러 선술집으로 가자. 여기서 오래 머물고 싶진 않아!";
				link.l1 = "그건 문제없지. 가자...";
				link.l1.go = "ContraMeetManQuest_2";
			break;
			
		case "ContraMeetManQuest_2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetActorType(NPChar);
			LAi_ActorFollowEverywhere(NPChar, "", -1);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "3");
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			PChar.GenQuest.ContraMeetMan.ToTavernWithMan = true;
			DeleteAttribute(&Locations[FindLocation(PChar.GenQuest.ContraMeetMan.ShoreID)], "DisableEncounters"); // Включаем случайки
			break;
		
		// Контрики в комнате таверны	
		case "ContraMeetManQuest_3":
			ContraMeetManQuest_ContersGoQut();
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "4");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ChangeContrabandRelation(PChar, 5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_4":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "5");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContraBeatMan();
			ChangeContrabandRelation(PChar, 5);
			ChangeCharacterComplexReputation(pchar,"nobility", -5);
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_5":
			dialog.text = "헤헤... 그런 것 같군, "+GetSexPhrase("녀석","아가씨")+", 곧 네놈도 그 자식이랑 지옥에서 만나게 될 거야... 이봐, 친구야 - 둘 다 배를 갈라버리자!";
				link.l1 = "이 더러운 돼지 놈아! 각오해라!";
				link.l1.go = "ContraMeetManQuest_6";
			break;
			
		case "ContraMeetManQuest_6":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraMeetManQuest_PlayerBeatContra();
			break;
			
		case "ContraMeetManQuest_7":
			dialog.text = "다시 한 번 감사하오, "+PChar.name+"... 작별이다...";
				link.l1 = "...";
				link.l1.go = "ContraMeetManQuest_9";
			break;
			
		case "ContraMeetManQuest_8":
			iMoney = (rand(3)+2)*500;
			PChar.GenQuest.ContraMeetMan.Money = iMoney;
			dialog.text = "보상이라고?! 아, 그래. 여기 – 가져가 "+FindRussianMoneyString(iMoney)+" 그리고 작별이오...";
				link.l1 = "잘 가라...";
				link.l1.go = "ContraMeetManQuest_10";
			break;
			
		case "ContraMeetManQuest_9":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "6");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
			
		case "ContraMeetManQuest_10":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraMeetMan.Money));
			sQuestTitle = PChar.GenQuest.ContraMeetMan.QuestTown + "ContraMeetManQuest";
			AddQuestRecordEx(sQuestTitle, "ContraMeetManQuest", "7");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraMeetMan.Money)));
			AddQuestUserData(sQuestTitle, "sDestination", XI_ConvertString(PChar.GenQuest.ContraMeetMan.ShoreID + "Dat"));
			CloseQuestHeader(sQuestTitle);
			ContraMeetManQuest_ContersGoQut();
			DeleteAttribute(PChar, "GenQuest.ContraMeetMan");
			break;
		// <-- Квест "meeting in the cove"
			
		// Квест на доставку письма контрику -->
		case "ContraDeliverQuest_Sold1":
			dialog.text = "헤! 우리가 그 헛소리를 믿을 거라고 생각해?! 이놈들아, 저 두 놈 잡아라!";
			//if(80 > rand(100) || sti(PChar.skill.Fortune) > rand(100)) // Попытка отмазаться
			//{
				link.l1 = "장교 나리, 죄 없는 두 사람을 붙잡으려 하다니 큰 실수를 저지르고 있소. 믿으시오, 나는 저 남자를 전혀 모르고, 관심도 없소."+" 네가 법을 잘 지키는 시민 둘을 붙잡아 두면, 네 지휘관이 꽤나 불쾌해할 거라고 확신한다...";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty";
			//}
			/*else // Тюрьма
			{
				link.l1 = "";
				link.l1.go = "ContraDeliverQuest_Sold2_Prison";
			}*/
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty":
			dialog.text = "흠... 그래, 네 말이 맞을지도 모르겠군. 사령관이 분명히 불쾌해할 거야. 있잖아 - 이 일은 그냥 없던 일로 하자.";
				link.l1 = "고맙소, 장교 나리, 덕분에 시간을 아꼈소. 다음에는 좀 더 조심해 주길 바라오; 강등당하고 싶진 않을 테지, 그렇지 않소?";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty1";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty1":
			dialog.text = "아니, 절대 안 되지. 그럼 흩어지시오. 또 보세...";
				link.l1 = "이제 좀 낫군!";
				link.l1.go = "ContraDeliverQuest_Sold2_Liberty2";
			break;
			
		case "ContraDeliverQuest_Sold2_Liberty2":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			ContraDeliverQuest_SoldiersGoOut();
			break;
		
		case "ContraDeliverQuest_1":
			iMoney = (rand(3)+2)*500;
			if(rand(1) == 0) // Денег не даёт
			{
				dialog.text = "좋아! 이제 꺼져라!";
					link.l1 = "뭐?! 그럼 돈은 어떻게 되는 거야? 우리 약속했잖아...";
					link.l1.go = "ContraDeliverQuest_NoMon";
			}
			else // Деньги или патруль
			{
				if(rand(2) == 1) // Патруль
				{
					dialog.text = "배달해 줘서 고맙다. 이제 꺼져도 되... 잠깐, 누가 오고 있어...";
						link.l1 = "뭐?!";
						link.l1.go = "ContraDeliverQuest_Patrol";
				}
				else // Просто отдает деньги
				{
					dialog.text = "좋아. 배달해 줘서 고맙다. 자, 받아라 "+FindRussianMoneyString(iMoney)". 그리고 밀수꾼들은 항상 좋은 사람을 기억한다는 걸 명심해...";
					link.l1 = "그러길 바라지. 잘 가라.";
					link.l1.go = "ContraDeliverQuest_GoWithMoney";
					PChar.GenQuest.ContraDeliver.Money = iMoney;
				}
			}
			
			ChangeContrabandRelation(PChar, 5); // Письмо доставили - повышаем отношение у контриков
			ChangeCharacterComplexReputation(pchar,"nobility", -5); // Помогли контрикам - репу понижаем
			RemoveItems(PChar, "letter_1", 1);
			BackItemDescribe("letter_1");
			DeleteAttribute(&Items[FindItem("letter_1")], "City");
			rChar = &Characters[GetCharacterIndex(Locations[FindLocation(PChar.location)].townsack + "_Smuggler")];
			SaveCurrentNpcQuestDateParam(rChar, "work_date");
			break;
			
		case "ContraDeliverQuest_Patrol":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_LocationFightDisable(LoadedLocation, true); // Чтоб не поубивали кого-нить
			ContraDeliverQuest_GeneratePatrolToRoom();
			break;
			
		case "ContraDeliverQuest_NoMon":
			dialog.text = "이봐... 너랑 나 사이엔 아무런 거래도 없었어. 네 돈은 그 거래를 한 놈한테 받아내.";
				link.l1 = "글쎄, 오늘은 정말 운이 없는 날이군, 더 무슨 말을 하겠어?! 좋아, 그럼 이만...";
				link.l1.go = "ContraDeliverQuest_GoWithoutMoney";
				link.l2 = RandSwear()+"그 대가를 치르게 될 거다! 죽을 준비나 해라!";
				link.l2.go = "ContraDeliverQuest_PrepareToFight";
			break;
			
		case "ContraDeliverQuest_GoWithoutMoney": // Уходим без денег
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			PChar.GenQuest.ContraDeliver.Complete.WithoutMoney = true;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "4");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ContraDeliver.QuestTown));
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
			
		case "ContraDeliverQuest_PrepareToFight":
			dialog.text = "감히 나에게 도전했군, "+GetSexPhrase("꼬맹이","오물")+"? 뭐야, 너 정말 뭐가 좋은 건지 전혀 모르는구나. 네 배를 갈라주마!";
				link.l1 = "...";
				link.l1.go = "ContraDeliverQuest_Fight";
			break;
			
		case "ContraDeliverQuest_Fight": // Бой
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LAi_SetImmortal(NPChar, false);
			LAi_ActorAttack(NPChar, PChar, "");
			LAi_SetFightMode(PChar, true);
			SetFunctionNPCDeathCondition("ContraDeliverQuest_ContraIsDead", NPChar.ID, false);
			break;
			
		case "ContraDeliverQuest_GoWithMoney": // Уходим с деньгами
			AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ContraDeliver.Money));
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			chrDisableReloadToLocation = false;
			bDisableFastReload         = false;
			sQuestTitle = PChar.GenQuest.ContraDeliver.QuestTown + "ContraDeliverQuest";
			AddQuestRecordEx(sQuestTitle, "ContraDeliverQuest", "3");
			AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(sti(PChar.GenQuest.ContraDeliver.Money)));
			CloseQuestHeader(sQuestTitle);
			DeleteAttribute(PChar, "GenQuest.ContraDeliver"); // Квест пройден - атрибуды потрем
			LAi_ActorGoToLocation(NPChar, "reload", "reload1_back", "none", "", "", "", 3.0);
			break;
		// <-- Квест на доставку письма контрику
			
		// Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем -->
		case "ChurchGenQuest_1_DeckDialog_1":
			if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap"))
			{
				if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern")) // Если ждёт в таверне
				{
					dialog.text = RandPhraseSimple("오백 명이나 되는 사내들! 그리고 죽은 자의 상자! 힉!","마셔라! 헉! 그리고 악마가 나머지 놈들은 - 헉! - 다 데려갔지!");
						link.l1 = "오... 그래. 안녕, 나리 "+GetFullname(NPChar)+".";
						link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_2";
						PChar.Quest.Church_GenQuest1_Timer.over = "yes";
				}
				else // на палубе своего шипа
				{
					if(!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
					{
						dialog.text = "좋아, 어디 보자... 돛천 세 장, 선체용 판자, 벨트랑 브레이스의 밧줄 교체...";
							link.l1 = "안녕하시오, 나리 "+GetFullName(NPChar)+". 내가 선장이야 "+PChar.name+".";
							link.l1.go = "ChurchGenQuest1_DialogShip_1";
					}
					else
					{
						dialog.text = LinkRandPhrase("당장 내 배에서 내려! 너 없이도 할 일이 많으니까!","책은 받았잖아, 또 뭘 원하는 거야?!","네가 시키는 건 다 했잖아, 이제 또 뭘 더 바라는데?!");
							link.l1 = "너무 흥분하지 마, 그러다 심장마비 올라!";
							link.l1.go = "exit";
					}					
				}
			}
			else
			{
				dialog.text = RandPhraseSimple("럼이다, 럼! 럼 좀 줘... 헉!","오랜만이야... 히끅... 저렇게 취한 건 정말 오래됐지...");
					link.l1 = "그래, 네 창고가 꽉 찼네... 이제 은신처로 갈 때가 된 거 아냐?";
					link.l1.go = "exit";
			}			
			NextDiag.TempNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_2":
			dialog.text = RandPhraseSimple("앉으시죠, 선장님! 뭐 한잔 하시겠습니까?","앉아, 선장! 뭐 마실래? 히끅...");
					link.l1 = "고맙지만, 난 괜찮은 놈이랑 기분 좋은 대화를 나누고 싶군.";
					link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_3";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_3":
			dialog.text = "너 지금... 히끅! 나 모욕하려는 거야?.. 저 선술집엔 제대로 된 놈 하나도 없어! 히끅! 죄다 강도에 살인자뿐이지! 전부 협잡꾼들이고, 저놈... 그중에서도 제일 악질이야! 두목이지, 목구멍에 바다장어나 쑤셔넣은 놈!";
				link.l1 = "너 말한 거야. 내가 얘기하고 싶은 사람은 바로 너라고. 그런데 도적 두목은 누구고, 그자가 왜...";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_4";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_4":
			dialog.text = "Mis"+GetSexPhrase("터","s")+"! 내 소중한 사람! 이름이 뭐였더라, 다시 한 번 말해줘? 나는 너를 존경해! 지금까지 늙은 뱃사람을 제대로 된 사람이라 불러준 영혼은 아무도 없었지! 널 위해서라면 뭐든지 하겠어! 가진 돈 전부, 마지막 페소까지 다 줄 수도 있어!.. 아, 방금 깜빡했다. 돈이 다 떨어졌거든. 리알도 한 푼 없어. 저 망할 놈, 그 갈취꾼이 마지막 동전까지 다 가져갔어, 지옥에서 악마들이 그놈 내장을 대포에 넣어 쏴버렸으면 좋겠군!";
				link.l1 = "선장 나리? 괜찮으십니까? 지금 헛소리하는 거 아십니까? 무슨 두루마리요?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_5";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_5":
			dialog.text = "아니, 아니야! 이 늙은 선장은 취했을지 몰라도 정신은 또렷하다고. 책이랑 두루마리는 신부님이 내게 주신 거야 "+PChar.GenQuest.ChurchQuest_1.ToName+", 내가 그들을 데려가던 중이었어 " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + ". 그리고 아침에 나는 현지 교회에 가서 그 신부에게 이 책들에 대해 이야기했지. 물론, 그는 책을 보고 싶어 하더군 — 알잖아, 그쪽 사람들, 성인전 같은 거에 미쳐 있으니까. 그래서 나는 선실 소년을 시켜 책이 든 상자를 가져오게 했어. 기다리는 동안 한 판 놀아볼까 해서 도박을 좀 했는데... 어쩌다 보니 돈을 다 잃어버렸지. 전부 다! 술값 낼 돈도 하나도 안 남았어! 그래서 선술집 주인이 책을 담보로 가져갔고, 두루마리도 같이 넘겨줬지...";
				link.l1 = "그래서 네가 신부가 맡긴 성서를, 그 거룩한 책들을 팔아버린 거냐\n  "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Gen")+"?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_6";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_6":
			dialog.text = "알아, 알아... 나는 영원히 지옥불에 타게 될 거야. 이제는 그 심부름을 시킨 신부님께도, 서류를 전달하던 사람에게도, 이 동네 사람들에게도 얼굴을 들 수가 없어... 이제 누가 내 영혼을 위해 기도해 주겠어? 그리고 만약 파문이라도 당하면 어쩌지? 아, 내 신세야... 술이나 한잔 해야겠군... ";
				link.l1 = "이봐, 진정해, 그렇게 나쁘진 않아. 네 짓거리는 형편없고 불경했지만, 그래도 내가 도와줄 준비가 되어 있어. 네 빚을 갚아주고 이 문서들도 사주지. 게다가, 언급된 두 신부 모두 이미 내가 아는 사람들이니, 나는 곧장 \n  " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " 거기에 서류를 전달하려고 그러는 거야. 거래할래?";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_7";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_7":
			dialog.text = "구세주! 신의 천사여... 물론이지, 나 동의해! 너한테 뭐든지 줄게... 전부 다! 술 한 잔만 더 마실 수 있다면...";
				link.l1 = "이미 충분히 마셨겠지... 에이, 됐다. 내가 바텐더한테서 럼주 좀 더 사줄게.";
				link.l1.go = "ChurchGenQuest1_DialogInTavernWithCap_8";
			break;
			
		case "ChurchGenQuest1_DialogInTavernWithCap_8":
			DialogExit();
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithCap");
			PChar.GenQuest.ChurchQuest_1.NeedToDialogWithBarmen = true;
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7_2");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			NextDiag.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
			break;
			
		case "ChurchGenQuest1_DialogShip_1":
			dialog.text = "...그리고 시트도! 시트도 갈아야 해!.. 아, 안녕하세요. 기분 상하지 마세요, 아가씨"+GetSexPhrase("테르","s")+" 이름이 뭐든 간에, 지금 보다시피 나는 꽤 바쁘니까, 할 말 있으면 빨리 해.";
				link.l1 = "내가 알기로는, 신부님 "+PChar.GenQuest.ChurchQuest_1.ToName+" 에서 성스러운 문서를 주었어 "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Voc")+". 그들을 데려다주겠다고 약속했잖아 " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " 어차피 그 방향으로 항해하고 있었으니까."; // belamour gen
				link.l1.go = "ChurchGenQuest1_DialogShip_2";
			break;
			
		case "ChurchGenQuest1_DialogShip_2":
			dialog.text = "나도 그쪽으로 가고 있었지, 그런데 저주받은 폭풍 때문에 내 낡은 배가 거의 박살나서 여기 얼마나 오래 갇혀 있는지 신만 아실 거야! 부두에 있는 사기꾼 놈들은 파도에 떠밀려온 썩은 판자를 선체용으로 팔아먹으려고 하고, 돛감으로는 자기네 할머니들이 젊었을 때 깔고 잤던 낡은 삼베천을 내밀고 있지.";
				link.l1 = "나리, 다음에는 기꺼이 훌륭한 이야기들을 듣겠지만, 지금은 당신이 에서 받은 책들과 원고들의 행방에 대해 더 알고 싶소. "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_1.ToColony+"Dat")+".";
				link.l1.go = "ChurchGenQuest1_DialogShip_3";
			break;
			
		case "ChurchGenQuest1_DialogShip_3":
			dialog.text = "아무도, 듣고 있나? 아무도 이 저주받은 문서 배달이 늦은 걸 내 탓이라 감히 하지 못해!";
				link.l1 = "아, 아니요, 그런 뜻은 전혀 아니었어요. 그냥 당신의 부담을 덜어주고 싶었을 뿐이에요. 사실은, 그게... "+PChar.GenQuest.ChurchQuest_1.ToName+" 에 전달될 책과 문서에 대해 매우 걱정하고 있어 " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + ". 사실, 지금 바로 그곳으로 항해할 거야.";
				link.l1.go = "ChurchGenQuest1_DialogShip_4";
			break;
			
		case "ChurchGenQuest1_DialogShip_4":
		if(rand(3) != 1)
		{
			dialog.text = "내가 보기엔, 아가씨"+GetSexPhrase("테르","s")+", 모든 항구마다 영적 조언자가 있다는 거군. 뭐, 그건 내 알 바 아니지. 그런 헛소리가 좋으면 책이나 챙겨서 꺼져! 잘 가라, 두 번 다시 보지 말자!";
				link.l1 = "감사합니다, 선장님. 수리 잘하시길 바랍니다.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_1";
		}
		else // Свитки не отдает
		{
			dialog.text = "그건 걱정하지 마, 아가씨"+GetSexPhrase("터","s")+", 그리고 이동하여 " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " 가볍게, 내가 그 서류들을 전달하기로 한 사람이 바로 나였으니, 어떤 대가를 치르더라도 내가 이 일을 해낼 거야. 그래야 거리마다 누구도 선장이라고 소리치며 떠들지 않게 말이지\n "+NPChar.name+" 약속을 지키지 않았어!";
				link.l1 = "하지만, 선장님, 사실 요점은...";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2";
		}
			break;
			
		case "ChurchGenQuest1_DialogShip_5_1":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2":
			dialog.text = "사실, 요점은 내가 너한테 볼일이 전혀 없다는 거야. 교황님이 내게 책을 전달하라고 임무를 주셨거든. " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Acc") + " 그리고 그걸 현지 신부에게 넘겨. 그런데 거기서 너는 못 봤다. 전혀! 행운을 빈다.";
//				link.l1 = "좋아, 그럼. 책임감은 있군, 그게 네 유일한 장점이지만. 행운을 빌어, 무례한 친구야";
//				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_1"; // Сваливаем, поверили ему
				link.l2 = "네 건방진 행동은 이제 지긋지긋하다. 네 멍청한 입놀림은 천사조차 폭력적으로 만들 수 있겠군. 나는 나의 성스러운 아버지의 뜻을 반드시 이뤄야 하니, 필요하다면 무기도 쓸 것이다!";
				link.l2.go = "ChurchGenQuest1_DialogShip_5_2_2"; // 
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_1":
			DialogExit();
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "11");
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete.NoManuscripts = true; // Квест выполнен без манускриптов
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_2":
			dialog.text = "조용히 해, 조용히, 선장 "+PChar.name+"! 너 왜 이래? 뭐, 네가 이 서류를 안 가져오면 저 신부님들이 다 너한테 엄청 화낼 거고, 하늘에 계신 아버지도 마찬가지겠지. 알겠다, 네 신학 보물 챙겨서 하느님의 축복과 함께 가라.";
				link.l1 = "내 입장을 이해해줄 뿐만 아니라 내 이름까지 기억해줘서 기쁘군. 멍청한 짓을 하려 할 때마다 내 이름을 떠올리도록 하라고.";
				link.l1.go = "ChurchGenQuest1_DialogShip_5_2_3"; // Сваливаем, поверили ему
			break;
			
		case "ChurchGenQuest1_DialogShip_5_2_3":
			DialogExit();
			AddItems(PChar, "Bible", 1);	// Даем рукописи
			items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";	// Меняем имя. Потом поменять обратно!
			ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible"); // Меняем дескрайб. Потом поменять обратно!
			items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
			sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "10");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown)); // belamour gen
			AddQuestUserData(sQuestTitle, "sCapName", GetFullName(NPChar));
			PChar.GenQuest.ChurchQuest_1.Complete = true; // Квест выполнен
			SetFunctionTimerCondition("Church_GenQuest1_DeleteCapitan", 0, 0, 1, false); // Трем судно кэпа
			break;
			
		// <-- Церковеый генератор. Квест № 1. Диалог кэпа, которого ищем
			
		case "Left_Time_Case":
			dialog.text = RandPhraseSimple("꺼져...","귀찮게 하지 마!");
				link.l1 = "...";
				link.l1.go = "exit";
				NextDiag.TempNode = "Left_Time_Case";
			break;
			
		case "Church_GenQuest_2_1":
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 1)
			{
				dialog.text = RandSwear()+"그런 말은 하지 말았어야지! 이제 네놈을 주님께 보내서 내 죄를 용서해 달라고 기도하게 해야겠군!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) == 2)
			{
				dialog.text = RandSwear()+"그런 말은 하지 말았어야지! 이제 네놈을 주님께 보내서 우리 죄를 용서해 달라고 기도하게 해야겠군!";
			}
			
			if(sti(PChar.GenQuest.ChurchQuest_2.BanditsCount) > 2)
			{
				dialog.text = RandSwear()+"그런 말은 하지 말았어야지! 이제 네놈을 주님께 보내서 우리 모두의 죄를 용서해 달라고 기도하게 만들어야겠군!";
			}
			
				link.l1 = "글쎄, 친구. 모두 각자 하나님께 책임질 거야!";
				link.l1.go = "exit";
				NPChar.money = sti(PChar.GenQuest.ChurchQuest_2.MoneyCount);
				LAi_LocationFightDisable(LoadedLocation, false);
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_1":
			dialog.text = "이봐, 왜 욕을 해? 나랑 볼일 있으면 어쩔 건데.";
				link.l1 = "이거야말로 소식이군! 있잖아, 너 같은 놈이랑 잡담할 시간 없어!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_2";
				LAi_LocationFightDisable(LoadedLocation, false);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_2":
			dialog.text = "나도 너랑 길게 얘기할 생각 없어. 하지만 혹시 값싸게 장신구 몇 개 사갈 생각 있냐?";
				link.l1 = "내가 장물아비처럼 보여?!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_3":
			if(rand(1) == 0)
			{
				dialog.text = "진정해, 진정해, 우리 중에 도둑은 없어! 이 꽃병은 우리가 정직하게 일해서 받은 거야! 봐봐... 순금에 진주로 장식되어 있지. 하지만 문제는 우리한테는 쓸모가 없다는 거야. 그래서 그냥 팔아서 돈을 나누고 싶은 거라고.";
					link.l1 = "자세히 좀 보자... 이런! 이건 성찬잔이잖아!!! 그러니까, 너희가 바로 그 교회를 약탈한 불경한 자들이구나 "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! 거기 있었군!";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_4";
					break;
			}
		
			dialog.text = "조용히 해, 아가씨"+GetSexPhrase("테르","s")+" 위선자 놈! 있잖아, 우리가 돈이 좀 모자라서 뭘 좀 팔기로 했어. 이 항아리 좀 봐... 순금에 진주까지 박혀 있지. 너한테만 특별가로, 천 코인에 넘기지.";
				link.l1 = "자세히 좀 보자... 이런! 이건 성찬잔이잖아!!! 그러니까, 너희가 교회를 약탈한 불경한 자들이로군 "+XI_ConvertString("Colony"+PChar.GenQuest.ChurchQuest_2.QuestTown+"Gen")+"?! 거기 있었군!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_1";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_4":
			dialog.text = "진정해, 아가씨"+GetSexPhrase("터","s")+"!.. 젠장, 내가 그 멍청이한테 때가 될 때까지 소란 피우지 말라고 했잖아...";
				link.l1 = "무슨 헛소리를 지껄이는 거야? 좋아, 선택해라:\n네가 훔친 전리품을 순순히 내놓든가, 아니면 내가 경비병을 부르겠다.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_5";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_5":
			dialog.text = "이봐, "+GetSexPhrase("좋은 사람","아가씨")+", 우리 싸움은 필요 없어, 그러니 이 일은 평화롭게 해결하자. 제발 믿어줘, 우리가 그 교회를 진짜로 약탈한 게 아니야, 돈도 없어. 그래, 강도 짓하는 척하고 몇 페소랑 저 금 장신구를 받긴 했지. 그리고 이 금잔은 밀수꾼들한테 돈을 주고 남은 유일한 거였어...";
				link.l1 = "그래서, 네가 하려는 말은...";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_6";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_6":
			dialog.text = "그 저주받은 신부가 우리를 고용했단 말이야, 내 말이 그거야! 그런데 왜 굳이 너를 우리한테 보낸 거지?.. 뭐, 이제 우리도 퉁친 셈이다. 이 항아리 가져가서 그 위선자한테 보여 줘. 직접 보면 그 자식이 얕은 바다에 걸린 오징어처럼 꿈틀거릴 거다!";
				link.l1 = "잔이나 내놓고 꺼져, 내가 마음 바꾸기 전에.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_7";
				link.l2 = "말은 번지르르하게 잘하는군, 하지만 내가 그렇게 만만한 줄 아냐? 날 설득하고 싶으면, 내 칼부터 설득해 봐라.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_8";
				// Тут давать чашу, если будет
				ChurchGenQuest2_GiveCup();
				PChar.GenQuest.ChurchQuest_2.Complete.PriestIsThief = true;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_7":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
				LAi_ActorRunToLocation(rChar, "reload", "reload1_back", "none", "", "", "", -1);
			}
			
			// Разрешим генерацию энкаунтеров, откроем выходы
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_1");
			AddQuestUserData(sQuestTitle, "sName", PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName);
			break;
			
		case "Church_GenQuest_2_ShoreBandit_8":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "10_2");
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_1":
			if(PChar.GenQuest.ChurchQuest_2.BanditsCount == 1)
			{
				dialog.text = RandSwear()+"내가 그 놈들한테 뭐랬어? 손 더럽히지 말고 신부한테서는 돈만 챙기라고 했잖아!";
			}
			else
			{
				dialog.text = RandSwear()+"내가 그 탐욕스러운 놈들한테 말하지 않았나? 욕심 많은 손은 가만히 두고 신부한테서는 돈만 챙기라고!";
			}
			
					link.l1 = "무슨 헛소릴 하는 거야? 좋아, 선택해. 네가 훔친 전리품을 순순히 내놓든가, 아니면 내가 경비병을 부르겠다.";
					link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2":
			dialog.text = "나는 다른 선택을 하고 있으니, 입 다물고 네 돈주머니나 내놔. 그러면 목숨은 살려주지.";
				link.l1 = "지금 우리 주님을 뵐 수 있도록 도와주겠소!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_1";
				link.l2 = "좋아, 내가 돈을 좀 주겠다. 하지만 내 자의로 주는 거니까, 너랑 네 친구들이 이제는 정직하게 살고 더 이상 도둑질로 자신을 더럽히지 않길 바란다.";
				link.l2.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_2";
				link.l3 = "에이... 좋아, 우리 의견 차이는 접어두고 대화 처음으로 돌아가자. 그래서 그 물건 값으로 얼마를 원했지?";
				link.l3.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3";
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_1":
			// Не забыть чашу!
			ChurchGenQuest2_GiveCup();
			PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
			NPChar.money = ((rand(3) + 6) * 1000);
			PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_1");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_2":
			AddMoneyToCharacter(PChar, -sti(PChar.money)/2); // Забираем половину денег
			PChar.GenQuest.ChurchQuest_2.Complete.Without_All = true; // Полностью проигрышный вариант. Остаемся ни с чем
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "First time";
			}
			
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "11_2");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("",""));
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3":
			iMoney = makeint(makeint(Pchar.money)/20)*10;
			dialog.text = "나도 괜한 문제는 원하지 않아, "+GetAddress_Form(pchar)+", 하지만 이제 값이 올랐지. 그 귀한 잔을 위해 네가 가진 모든 걸 내놔야겠다.";
			if(iMoney >= makeint(Pchar.rank)*300)
			{
				link.l1 = "이 탐욕스러운 놈들아! 나는 겨우 "+FindRussianMoneyString(iMoney)+" 나랑 같이 있어. 이거나 챙기고 꺼져!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1";
			}
			else
			{
				link.l1 = "잘못 골랐군, 욕심 많은 쥐새끼야. 내 덕 볼 생각은 꿈도 꾸지 마!"+GetSexPhrase(" 나는 바람처럼 자유롭지 - 오늘은 여기 있다가 내일은 사라지고, 오늘은 가난하지만 내일은 부자가 될 거야...","")+"";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2";
			}
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_1":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
			ChurchGenQuest2_GiveCup();	// Даем чашу
			AddMoneyToCharacter(PChar, -(makeint(makeint(Pchar.money)/20)*10));
			PChar.GenQuest.ChurchQuest_2.Complete.Only_With_Cup = true;
			iBanditsCount = PChar.GenQuest.ChurchQuest_2.BanditsCount;
			for(i=0; i<iBanditsCount; i++)
			{
				rChar = CharacterFromID("Church_GenQuest2_Bandit_" + i);
				LAi_SetCitizenType(rChar);
				rChar.LifeDay = 0;
				rChar.Dialog.Currentnode = "Left_Time_Case"; // Диалог не забыть поменять.
			}
			
			DeleteAttribute(LoadedLocation, "DisableEncounters");
			chrDisableReloadToLocation = false;
			sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
			AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_3");
			AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("",""));
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.BanditsInShore");
			break;

		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_2":
			dialog.text = "특히 오늘은 그런 말을 하려는 거 아니야 "+GetSexPhrase("너는 가난하구나","너 돈 없잖아")+"?!";
				link.l1 = "그래, 욕심 많은 친구야, 네가 실망할 만도 하지. 이제 나는 가봐야겠어, 할 일이 많거든.";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3";	
			break;
			
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_3":
			dialog.text = "멈춰! 우리가 그걸 확인할 거다. 만약 네가 거짓말을 했다면, 네 거짓 혀를 개미굴에 쑤셔 넣어 주마!";
				link.l1 = "그 말 했으니, 이제 끝장이야!";
				link.l1.go = "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4";
			break;
			
		// Можно этот кэйс - Church_GenQuest_2_ShoreBandit_Real_Band_2_1
		case "Church_GenQuest_2_ShoreBandit_Real_Band_2_3_4":
				// ГГ как-бы может обыскать трупики и забрать все барахло...
				PChar.GenQuest.ChurchQuest_2.Complete.With_All = true;
				NPChar.money = ((rand(3) + 6) * 1000);
				PChar.GenQuest.ChurchQuest_2.MoneyCount = NPChar.money;
				DialogExit();
				NextDiag.CurrentNode = NextDiag.TempNode;
				AddDialogExitQuest("Church_GenQuest2_BanditsIsEnemies");
				sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
				AddQuestrecordEx(sQuestTitle, "ChurchGenQuest2", "11_4");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("As a real gentleman, I am honest","I am honest"));
			break;
			
		///////////////////////////////////////////////////////////////////////////////////////////////////
		// ГЕНЕР "PIRATES ON AN UNINHABITED ISLAND"
		///////////////////////////////////////////////////////////////////////////////////////////////////
		
		case "PiratesOnUninhabited_1":
			dialog.text = "오, 결정할 건 없어. 우린 다 알아서 할 수 있거든. 대신 네 배는 우리가 가져가고 여기서 나갈 거야.";
			link.l1 = "조건이 하나 있어. 먼저, 내 칼을 네가 빼앗아야 해...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_2":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				LAi_SetImmortal(CharacterFromID("PirateOnUninhabited_" + i), false);
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_3":
			PChar.GenQuest.PiratesOnUninhabited.MainPirateName = GetRandName(NAMETYPE_NICK, NAME_GEN);
			PChar.GenQuest.PiratesOnUninhabited.BadPirateName = GetRandName(NAMETYPE_ORIG, NAME_NOM);
			
				i = PiratesOnUninhabited_GenerateShipType();
				PChar.GenQuest.PiratesOnUninhabited.StartShipType = i;
			
			if(hrand(1) == 0)
			{
				PChar.GenQuest.PiratesOnUninhabited.Shipwrecked = true;
				
				dialog.text = "안녕하세요, 선장님! 섭리 그 자체가 당신을 구원하라고 보낸 것 같군요 "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+" 그리고 그 녀석들과 그의 부하들. 여긴 정말 절박한 상황이야."+"Our "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[i].Name))+" 폭풍에 휩쓸려 이 근처 암초에 좌초했고, 살아남은 선원들은 파도에 밀려 해안으로 떠밀려왔지."+"For "+(5+hrand(7))+"몇 주 동안이나 우리는 수평선을 바라보며, 우리를 구하러 올 배의 돛이 보이길 바랐지.";
				link.l1 = RandPhraseSimple(RandPhraseSimple("그래, 그건 참 안타까운 운명이야. 하지만 선원의 삶이란 게 다 그런 거지, 누구든 네 처지가 될 수 있어.","그렇군... 신께서는 모든 생명을 품고 계시지만, 너무 바쁘셔서 모두를 기억하진 못하시지."),RandPhraseSimple("그렇지. 사람이 계획해도, 결국 신이 결정하지.","그래, 그건 정말 운이 없었던 거지."));
				link.l1.go = "PiratesOnUninhabited_4";
			}
			else
			{
				dialog.text = "정말 심각했어! 그 악당놈 "+PChar.GenQuest.PiratesOnUninhabited.BadPirateName+" 떠나는 것 말고는 아무런 벌도 생각나지 않았어 "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+" 사람 없는 섬에서, 마치 털 빠진 똥개처럼! "+"그자는 태양과 갈증이 우리를 어부의 건조대 위에 놓인 마른 고등어처럼 바짝 말려버리길 바랐지!\n하지만 그 자가 틀렸어. 신의 섭리가 우리 편이었으니까, 너를 이곳에 보내 우리를 구하게 했잖아...";
				link.l1 = RandPhraseSimple("그렇게 서두르지 마, 친구. 내가 보기엔 너희는 자유로운 직업을 가진 놈들이고, 여기 온 것도 우연이 아니지.","벌써 구원 얘기부터 나오나? 내가 알기로 너 여기 온 건 뭔가 특별한 공로 때문이라던데.");
				link.l1.go = "PiratesOnUninhabited_41";
			}
		break;
		
		case "PiratesOnUninhabited_4":
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = 5 + hrand(5);
			
			dialog.text = RandPhraseSimple("선장님, 제발 좋은 마음으로 도와주십시오  "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" 가난에 찌든 놈들입니다. 우리에겐 자비로우신 주님 말고는 당신만이 유일한 희망이에요.","선장님, 배에 남는 사물함이 있습니까 "+PiratesOnUninhabited_GetStringNum(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))+" 거지 같은 놈들인가?");
			
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l1 = "오... 그래서 어디로 데려가길 원하는 거야?";
				link.l1.go = "PiratesOnUninhabited_5";
			}
			
			link.l2 = RandPhraseSimple(RandPhraseSimple("정말 미안하지만, 빈 해먹 하나도 없고, 선실은 말할 것도 없어. 선원들은 갑판에서 자고 있어; 당번이 끝나도 제대로 쉬지도 못해...","정말 실망시키고 싶지 않지만, 배가 과적되어서 사람들은 악천후 속에서 잠을 자야 해. 만약 질병이라도 돌면, 선원 절반을 잃게 될 거야."),RandPhraseSimple("정말 미안하지만, 내 배에는 여분의 선원 공간이 전혀 없어. 더 이상 승객을 태울 수 없어.","실망시키게 되어 미안하지만, 내 배는 이미 선원들로 가득 찼어. 전염병이 돌까 두렵거든..."));
			link.l2.go = "PiratesOnUninhabited_21";
			
			if(stf(PChar.reputation.nobility) <= REPUTATION_NEUTRAL)
			{
				link.l3 = "너는 노련한 선원이니, 난파에서 살아남은 자가 있다는 게 얼마나 불길한 징조인지 알겠지. 내 선원들이 너희 전부 바다에 던져버릴 거다.";
				link.l3.go = "PiratesOnUninhabited_7";
			}
		break;
		
		case "PiratesOnUninhabited_5":
			dialog.text = "흠... 있잖아, 여러 가지 이유로 우리는 당국과 최대한 멀리 있고 싶어... 제발, 사람이 사는 섬이나 본토의 어느 만이라도 데려다 주면, 그다음부터는 우리가 알아서 할 수 있어.";
			link.l1 = "그래, 빈 침상하고 해먹은 충분히 있어. 배에 타라.";
			link.l1.go = "PiratesOnUninhabited_10";
			link.l2 = "흠... 운이 없군... 앞으로 전투가 기다리고 있는데, 내 배에 타는 게 더 안전할지, 아니면 이 아늑한 만에 있는 게 더 나을지 나도 모르겠어.";
			link.l2.go = "PiratesOnUninhabited_6";
		break;
		
		case "PiratesOnUninhabited_6":
			dialog.text = "오, 선장님! 요즘은 아내랑 침대에 있어도 안심할 수 없는 세상이라오, 하하, 하물며 바다에서는 말할 것도 없지... 저 불한당들 좀 보시오, 하나같이 맨손으로 대포에 맞서 싸울 기세라오. 안전이나 편안함 따위는 전혀 바라지 않는 놈들이라 얼굴만 봐도 알 수 있다니까!";
			link.l1 = "저놈들 얼굴에는 자기들을 도운 바보를 등 뒤에서 찌를 의지만 보이는군.";
			link.l1.go = "PiratesOnUninhabited_7";
			link.l2 = "흠... 그거, 사실 좋은 생각이군. 그런데 말이야, 친구, 네 깡패들이 내 선원으로 들어올 생각이 있나?";
			link.l2.go = "PiratesOnUninhabited_8";
		break;
		
		case "PiratesOnUninhabited_7":
			dialog.text = "안타깝군, 선장... 우리가 우호적으로 해결할 수 없다는 걸 알겠어. 이제 바다의 규율을 상기시켜 줘야겠군. 그리고 명심해, 백병전에서는 우리가 누구에게도 뒤지지 않는다는 걸...";
			link.l1 = "이제야 네가 어떤 놈인지 제대로 알겠군...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", -3.0);
		break;
		
		// Берем их в команду
		case "PiratesOnUninhabited_8":
			dialog.text = "당연하지! 녀석들은 기꺼이 네 승선대에 합류할 거야! 싸움에서 녀석들을 이길 자는 아마 데이비 존스밖에 없을걸! 하하하!";
			link.l1 = "좋아, 그럼. 배에 타라...";
			link.l1.go = "PiratesOnUninhabited_9";
		break;
		
		case "PiratesOnUninhabited_9":
			bTemp = CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked");
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.LifeDay = 0;
				
				if(bTemp)
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				}
				else
				{
					rChar.Dialog.currentnode = "PiratesOnUninhabited_43_again";
				}
			}
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount));
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			OfficersReaction("bad");
			
			//PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			//DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_10":
			dialog.text = "감사합니다, 선장님! 선적은 오래 걸리지 않을 겁니다. 신이시여, 우리가 그 순간이 오기를 얼마나 간절히 기도했는지!";
			link.l1 = "좋아, 그럼.";
			link.l1.go = "PiratesOnUninhabited_11";
		break;
		
		// Берем их в пассажирами - держать курс на населенный остров
		case "PiratesOnUninhabited_11":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			OfficersReaction("good");
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			
			if(!CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.TreasureMap"))
			{
				if(CheckAttribute(PChar, "GenQuest.PiratesOnUninhabited.Shipwrecked"))
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "1");
					AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
					// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
					if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					else
					{
						AddQuestUserData(sTitle, "sText", "wrecked pirate");
					}
					// <-- belamour gen
				}
				else
				{
					AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "11");
					AddQuestUserData(sTitle, "pirateName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
				}
			}
			else
			{
				AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "5");
				AddQuestUserData(sTitle, "shipTypeName", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Gen"))); // belamour gen
				// --> belamour gen: нужно разделить, иначе получается с потерпевшего крушение бригантины 
				if(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_BRIGANTINE" || ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name == "SHIP_SCHOONER_W")
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				else
				{
					AddQuestUserData(sTitle, "sText", "wrecked pirate");
				}
				// <-- belamour gen
			}
			
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1 = "ExitFromLocation";
			PChar.Quest.PiratesOnUninhabited_LocExitGood.win_condition.l1.location = PChar.location;
			PChar.Quest.PiratesOnUninhabited_LocExitGood.function = "PiratesOnUninhabited_LocationExit_Good";
			
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnShore.win_condition.l1.location_type = "seashore";
			PChar.Quest.PiratesOnUninhabited_OnShore.again = true;
			PChar.Quest.PiratesOnUninhabited_OnShore.function = "PiratesOnUninhabited_OnShore";
			
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1 = "Location_Type";
			PChar.Quest.PiratesOnUninhabited_OnMayak.win_condition.l1.location_type = "mayak";
			PChar.Quest.PiratesOnUninhabited_OnMayak.again = true;
			PChar.Quest.PiratesOnUninhabited_OnMayak.function = "PiratesOnUninhabited_OnShore";
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_11_Again":
			dialog.text = LinkRandPhrase("왜 머뭇거리고 있소, 선장? 닻을 올리라고 명령하시오.","죄송합니다, 선장님, 하지만 우리는 출항 준비를 해야 합니다.","네가 여기 오기로 결심해서 우리는 정말 운이 좋다!");
			link.l1 = "서둘러. 배는 아무도 기다려주지 않아.";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_11_Again";
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове
		case "PiratesOnUninhabited_12":
			if(hrand(1) == 0)
			{
				// Успешное завершение квеста - даст награду
				dialog.text = "감사합니다, 선장님. 정말로, 우리가 우리의 운을 믿은 게 옳았군요... 제발, 이 보석을 받아 주십시오. 그 불운한 만에서 발견한 것입니다. 선장님께 행운을 가져다주길 바랍니다.";
				link.l1 = "이런 선물을 받을 줄은 몰랐어.";
				link.l1.go = "PiratesOnUninhabited_13";
			}
			else
			{
				// Требуют денег
				dialog.text = "선장님, 제발, 우리가 너무 건방지다고 생각하지 마십시오. 정말 돈이 너무 없습니다. 아시다시피 가진 걸 다 잃어버렸거든요. 페소 몇 줌만 빌려주실 수 있겠습니까? 기회가 되면 꼭 갚겠습니다...";
				link.l1 = "이런 젠장! 정말 뻔뻔하기가 끝이 없군. 뭐, 내가 이미 다 해줬으니 이제 너한테 해줄 수 있는 건 당국에 네 얘기를 안 하는 것뿐이겠다.";
				link.l1.go = "PiratesOnUninhabited_15";
				link.l2 = "그래... 그래서 얼마를 원하는 거지?";
				link.l2.go = "PiratesOnUninhabited_17";
			}
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_13":
			AddItems(PChar, "jewelry4", 1);
			
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				
				rChar.Dialog.currentnode = "PiratesOnUninhabited_14";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "2");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_14":
			dialog.text = LinkRandPhrase("감사합니다, 선장님.","선장님, 정말 감사드립니다.","우리가 당신을 위해 기도하겠소, 선장님 "+PChar.name+"!");
			link.l1 = "행운을 빌지. 잘 가라...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_14";
		break;
		
		case "PiratesOnUninhabited_15":
			dialog.text = "헤, 선장... 있잖아, 우리 잘 지냈잖아... 널 죽이면 정말 아쉬울 것 같은데...";
			link.l1 = "한번 해 보시지!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
		break;
		
		case "PiratesOnUninhabited_16":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "3");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Gen"))); // belamour gen
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_17":
			iMoney = sti(PChar.rank) * 500;
			PChar.GenQuest.PiratesOnUninhabited.Money = iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			
			dialog.text = "그래, 말해봐, "+iMoney+" 우리 한 명당 페소만 주면 괜찮겠지... 물론, 이 보상이 우리 고생과 고통에 비해 너무 적다고 생각하지 않는다면 말이야, 히히...";
			link.l1 = RandPhraseSimple("반대로, 나는 이게 너무 과하다고 확신한다... 너희들 목에 올가미를 거는 게 제일 좋겠군.","그 정도 돈이면 내가 직접 너희를 야자수에 원숭이처럼 매달아 버릴 거다!");
			link.l1.go = "PiratesOnUninhabited_18";
			
			if(sti(PChar.money) >= iMoney * sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				link.l2 = "알겠어, 가져가. 더 이상 빚진 거 없길 바란다?";
				link.l2.go = "PiratesOnUninhabited_19";
			}
		break;
		
		case "PiratesOnUninhabited_18":
			dialog.text = "이런 관대함이라니! 솔직히, 우리는 항상 원하는 걸 얻는다는 걸 이미 알았을 거라 생각했어. 그리고 이번에도 절대 물러서지 않을 거야...";
			link.l1 = "한번 해 보시지!";
			link.l1.go = "PiratesOnUninhabited_16";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_19":
			dialog.text = "아이고, 선장님, 무슨 말씀을 하시는 겁니까?! 우리가 교회에 발을 들일 일이 있다면, 꼭 선장님 이름으로 촛불을 켜겠습니다... 하하!";
			link.l1 = "그러길 바란다...";
			link.l1.go = "PiratesOnUninhabited_20";
			
			iMoney = sti(PChar.GenQuest.PiratesOnUninhabited.Money);
			
			AddMoneyToCharacter(PChar, -iMoney);
			AddMoneyToCharacter(NPChar, iMoney);
		break;
		
		case "PiratesOnUninhabited_20":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_CharacterDisableDialog(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			ChangeCharacterComplexReputation(pchar,"nobility", 2.0);
			OfficersReaction("good");
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "4");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "sSex1", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.location + "Acc")));
			CloseQuestHeader(sTitle);
			
			NPChar.SaveItemsForDead = true; // сохранять на трупе вещи
			NPChar.DontClearDead = true;  // не убирать труп через 200с
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_21":
			if(GetFreeCrewQuantity(PChar) >= sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount))
			{
				// Игрок врет - свободное место есть
				dialog.text = "아이고, 선장님, 무슨 말씀을 하시는 겁니까?! 우리가 교회에 발을 들이게 된다면, 꼭 선장님 이름으로 촛불을 켤게요... 하하!";
				link.l1 = "그러길 바란다...";
				link.l1.go = "PiratesOnUninhabited_23";
			}
			else
			{
				dialog.text = "헤헤, 선장, 그거 별로 문제도 아니지. 내 부하들이랑 나는 네 배에 있는 해먹 열두 개쯤 지금 차지하고 있는 놈들한테서 얼마든지 비워줄 수 있어...";
				link.l1 = "흠... 그거 협박처럼 들리는데...";
				link.l1.go = "PiratesOnUninhabited_22";
			}
		break;
		
		case "PiratesOnUninhabited_22":
			dialog.text = "사실, 이건 협박이 맞아. 네 배가 필요하고, 네가 허락하든 말든 나는 이곳을 나갈 거야!";
			link.l1 = "이제야 네가 어떤 놈인지 제대로 보이네...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_23":
			dialog.text = "알겠소, 선장. 완벽히 이해하지... 교수대에 매달리길 애원하는 불쌍한 해적들을 누가 돌보고 싶겠나?.. 하지만... 내가 거래를 제안하면 어떻겠소? 당신이 우리를 사람이 사는 섬이나 본토의 어느 만이라도 데려다 주면, 그 대가로 내가 보물 지도를 주겠소. 거래하겠소?";
			link.l1 = "흠... 그런데 이 지도가 위조된 게 아니라는 걸 어떻게 보장할 수 있지?";
			link.l1.go = "PiratesOnUninhabited_25";
			link.l2 = "하, 네 지도 값어치라면 그려진 종이만큼이나 싸구려겠군...";
			link.l2.go = "PiratesOnUninhabited_24";
		break;
		
		case "PiratesOnUninhabited_24":
			dialog.text = "음... 너 때문에 우리도 어쩔 수 없게 됐군... 그래도 우리는 네가 허락하든 말든 이곳을 빠져나갈 거야!";
			link.l1 = "이제야 네가 진짜 어떤 놈인지 제대로 볼 수 있게 됐군...";
			link.l1.go = "PiratesOnUninhabited_2";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_25":
			dialog.text = "그럼 네가 우리를 가까운 항구 당국에 넘기지 않을 거란 보장은 어떻게 하지? 우리 둘 다 서로의 패를 보지 않고 게임을 하고 있잖아...";
			link.l1 = "좋아, 거래 성사다.";
			link.l1.go = "PiratesOnUninhabited_11";
			PChar.GenQuest.PiratesOnUninhabited.TreasureMap = true;
		break;
		
		// Базар с главарем уже в другой бухте на обитаемом острове. Вариант, когда нам обещали карту сокровищ
		case "PiratesOnUninhabited_26":
			// PChar.GenQuest.PiratesOnUninhabited.MainPirateName - имя в родительном падеже
			
			dialog.text = "감사합니다, 선장님 "+PChar.name+". 당신은 완수했소"+GetSexPhrase("","")+" 네 약속, 이제 시간이야 "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_DAT)+" 내 것도 이뤄야지. 지금 지도는 없지만, 보물이 어디 있는지는 알려주지. 만으로 가라...";
			link.l1 = "오, 이제 와서 그렇게 말하는 거냐! 처음부터 나를 속일 생각이었구만...";
			link.l1.go = "PiratesOnUninhabited_27";
			link.l2 = "나는 처음부터 네놈을 믿을 수 없다는 걸 알았지...";
			link.l2.go = "PiratesOnUninhabited_30";
			link.l3 = "해적을 믿으면 저렇게 되는 거야. 너희는 도대체 어떤 놈들이냐? 너희한테는 성스러운 것도 아무것도 없구나!";
			link.l3.go = "PiratesOnUninhabited_33";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
		break;
		
		case "PiratesOnUninhabited_27":
			dialog.text = "소란 피우지 마... 난 성인은 아니지만, 약속은 지킨다!";
			link.l1 = "또 나를 믿으라고? 내일이면 온 군도가 나를 비웃게 될 텐데?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		case "PiratesOnUninhabited_28":
			dialog.text = "흠... 아무래도 평화롭게 끝나진 않겠군. 하지만, 신만이 아시겠지, 난 이런 걸 원한 게 아니었어...";
			link.l1 = "칼을 뽑아라, 안 그러면 네 놈을 쥐처럼 짓밟아 주지!";
			link.l1.go = "PiratesOnUninhabited_29";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_29":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "6");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
			
			// Конец квеста
		break;
		
		case "PiratesOnUninhabited_30":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "내가 또 뭘 할 수 있었겠어? 내 놈들과 그 썩은 웅덩이에 남아서 썩어 죽으라고? 내 말 끝까지 듣는 게 좋을 거야..."+XI_ConvertString(sTitle+"Gen")+" 선장 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" 그놈이 전리품을 숨겨 놓은 은닉처가 있어. 하지만 조심해라\n"+GetSexPhrase("","")+", 그는 거기에 자주 들르지. 정신만 똑바로 차리면 은닉처를 찾는 건 어렵지 않을 거야..."; // belamour gen
			link.l1 = "또 나를 믿으라고? 그랬다가는 내일이면 군도 전체가 나를 비웃게 될 텐데?";
			link.l1.go = "PiratesOnUninhabited_28";
			link.l2 = "좋아. 하지만 또 한 번만 날 바보로 만들면, 널 찾아낼 거야.";
			link.l2.go = "PiratesOnUninhabited_31";
		break;
		
		case "PiratesOnUninhabited_31":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
				rChar.Dialog.currentnode = "PiratesOnUninhabited_32";
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "7");
			AddQuestUserData(sTitle, "capName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_NOM));
			AddQuestUserData(sTitle, "toShore", LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.TreasureShore + "Gen"))); // belamour gen
			
			// Таймер для клада. По прошествии 10 дней в кладе будут всякие бакланы и т.д.
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1 = "Timer";
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
			PChar.Quest.PiratesOnUninhabited_TreasureLose.function = "PiratesOnUninhabited_TreasureLose"; // belamour gen
			
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1 = "Location";
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.win_condition.l1.Location = PChar.GenQuest.PiratesOnUninhabited.TreasureShore;
			PChar.Quest.PiratesOnUninhabited_InTreasureLoc.function = "PiratesOnUninhabited_InTreasureLoc";
			
			DialogExit();
			
			// Курс в бухту, которую назвал пират. У нас сроку 10 дней, котом клад пропадёт
		break;
		
		case "PiratesOnUninhabited_32":
			sTemp = ChangeNameCase(NAMETYPE_NICK, PChar.GenQuest.PiratesOnUninhabited.MainPirateName, NAME_ACC);
			
			dialog.text = LinkRandPhrase("들어봐 "+sTemp+", 저 녀석 말이 맞아.","화내지 마 "+sTemp+", 그는 그냥 다른 선택지가 없었을 뿐이야.","감사합니다, 선장님.");
			link.l1 = "행운을 빌지...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_32";
		break;
		
		case "PiratesOnUninhabited_33":
			sTitle = PiratesOnUninhabited_GenerateTreasureShore(&sTemp);
			PChar.GenQuest.PiratesOnUninhabited.TreasureShore = sTitle;
			PChar.GenQuest.PiratesOnUninhabited.TreasureBox = sTemp;
			
			dialog.text = "그럼 내가 뭘 더 할 수 있었겠어? 내 놈들과 그 썩은 웅덩이에 남아서 썩어 죽으라고? 내 말 끝까지 듣는 게 좋을 거다..."+XI_ConvertString(sTitle+"Gen")+" 선장 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" 그놈이 전리품을 숨겨두는 은신처가 있어. 하지만 조심해, 자주 들르거든. 정신만 바짝 차리면 은신처를 찾는 건 어렵지 않을 거야..."; // belamour gen
			link.l1 = "또 나를 믿으라고? 그러면 내일은 카리브 제도 전체가 나를 비웃겠지?";
			link.l1.go = "PiratesOnUninhabited_28";
		break;
		
		// Пираты в бухте с сокровищем
		case "PiratesOnUninhabited_34":
			dialog.text = "너 누구야?"+GetSexPhrase(" 놈"," 아가씨")+"? 그런데 이런 황량한 곳엔 무슨 일로 온 거지?";
			link.l1 = "나는 식수 보급을 위해 잠시 멈췄다.";
			link.l1.go = "PiratesOnUninhabited_35";
			link.l2 = "나는 대신해서 왔다 "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+".";
			link.l2.go = "PiratesOnUninhabited_38";
			NextDiag.TempNode = "PiratesOnUninhabited_34";
		break;
		
		case "PiratesOnUninhabited_35":
			dialog.text = "그걸 하기에 여긴 참 안 좋은 곳이야... 좋아, 천천히 해.";
			link.l1 = "아-하...";
			link.l1.go = "exit";
			link.l2 = "네가 뭔데 나한테 이래라저래라야?";
			link.l2.go = "PiratesOnUninhabited_36";
		break;
		
		case "PiratesOnUninhabited_36":
			dialog.text = "내가 모두에게 뭐 하라고 지시한다. 그리고 너무 똑똑하다고 생각하는 놈들은 야자수에 매달리게 될 거다.";
			link.l1 = "네 혓바닥을 뽑아버릴 거다, 이 개새끼야.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "PiratesOnUninhabited_37":
			DialogExit();
			LAi_Group_SetRelation("PiratesOnUninhabited_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		break;
		
		case "PiratesOnUninhabited_38":
			dialog.text = "그런데 왜 직접 오지 않았지?";
			link.l1 = "그는 원하지 않았고, 그는 거기에 남아 있었어 "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+" 그리고 나를 기다리고 있지."; // belamour gen
			link.l1.go = "PiratesOnUninhabited_39";
		break;
		
		case "PiratesOnUninhabited_39":
			dialog.text = "그 늙은 악당! 또 우리를 속이려고 하는 거지, 안 그래? 그건 안 돼. 우리가 같이 있을 때만 돈을 받을 수 있다고 전해 줘!";
			link.l1 = "그는 돈 없이 돌아오지 말라고 했고, 누구도 배에 태우지 말라고 했어...";
			link.l1.go = "PiratesOnUninhabited_40";
		break;
		
		case "PiratesOnUninhabited_40":
			dialog.text = "그래, 그놈을 그렇게 믿는다면 여기 남아 있어라. 하지만 우리는 네 배랑 돈을 가져가서 \n "+LowerFirst(XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore+"Gen"))+". 우리는 정말로 얼굴을 보고 싶어 죽겠어 "+PChar.GenQuest.PiratesOnUninhabited.MainPirateName+"."; // belamour gen
			link.l1 = "그가 그렇게 그립다면, 헤엄쳐서 가든가... 아니면 여기서 죽든가.";
			link.l1.go = "PiratesOnUninhabited_37";
			AddDialogExitQuest("MainHeroFightModeOn");
			PChar.GenQuest.PiratesOnUninhabited.UseMainPiratename = true;
		break;
		
		// Ветка из PiratesOnUninhabited_3
		case "PiratesOnUninhabited_41":
			iBanditsCount = 5 + hrand(5);
			iMoney = GetFreeCrewQuantity(PChar);
			
			PChar.GenQuest.PiratesOnUninhabited.PiratesCount = iBanditsCount;
			
			dialog.text = "너 참 약삭빠른 사람이군. 하지만 우리와 선장과의 갈등에 대해 내가 확실히 말해두겠네 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_ABL)+" 순전히 이념적인 성격이야. 나는 언젠가 그의 더러운 짓거리가 벌을 받을 거라고 경고했지, 그리고 이제 내\n  "+iBanditsCount+" 우리 동료들이 신과 정의를 사랑한 죄로 고통받고 있어.";
			link.l1 = "어떻게 그런 일이... 너희가 반란의 진짜 주동자였겠지, 그러니 당연한 대가를 받은 거야.";
			link.l1.go = "PiratesOnUninhabited_42";
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l2 = "물론이지... 그래도 선장님의 의견을 듣고 싶군 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_GEN)+" 그 자신이 당신과의 불화에 대해 이야기했어.";
				link.l2.go = "PiratesOnUninhabited_44";
			}
		break;
		
		case "PiratesOnUninhabited_42":
			dialog.text = "선장님, 왜 정직한 사람들을 의심해서 기분 상하게 하십니까? 저 얼굴들을 한번 보십시오... 정말로 저들이 반란자라고 생각하십니까? 저들은 그저 겸손한 사람들일 뿐입니다... 하지만 정의로운 대의와 훌륭한 지휘 아래에서는 누구에게도 뒤지지 않는 싸움꾼들이지요! 저 한 사람 한 사람 모두 제가 직접 보증할 수 있습니다.";
			link.l1 = "좋아, 그런데 이제 너를 어떻게 해야 하지?";
			link.l1.go = "PiratesOnUninhabited_43";
		break;
		
		case "PiratesOnUninhabited_43":
			iBanditsCount = sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount);
			iMoney = GetFreeCrewQuantity(PChar);
			
			dialog.text = "원하는 대로 해. 네가 결정해, 우리를 정착지로 데려가든, 아니면 네 선원으로 받아주든, 내 눈엔 너 괜찮은 선장 같아.";
			
			if(iMoney >= iBanditsCount)
			{
				link.l1 = "좋아, 내 선원으로 받아주지. 하지만 장난은 금물이야! 내 배에서는 규율이 엄격하다고!";
				link.l1.go = "PiratesOnUninhabited_9"; // Берем в команду
			}
			
			link.l2 = "나는 너를 어디에도 데려가지 않아. 내 선원들만 해도 이미 깡패들이 넘쳐나.";
			link.l2.go = "PiratesOnUninhabited_24"; // Рубилово и конец квеста
			
			if(iMoney >= iBanditsCount - 1 && GetPassengersQuantity(PChar) < PASSENGERS_MAX)
			{
				link.l3 = "좋아, 배에 타. 내가 어디로 데려가 줄게.";
				link.l3.go = "PiratesOnUninhabited_11"; // В пассажиры и на остров
			}
		break;
		
		case "PiratesOnUninhabited_43_again":
			dialog.text = LinkRandPhrase("맹세합니다, 선장님, 절대 후회하지 않으실 겁니다.","옳은 선택을 했군, 선장.","선장님, 안심하십시오. 당신도 우리만큼 운이 좋았으니!");
			link.l1 = RandPhraseSimple("그러길 바란다.","서둘러라. 배는 아무도 기다려주지 않는다.");
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_43_again";
		break;
		
		case "PiratesOnUninhabited_44":
			sTitle = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.PiratesOnUninhabited.StartShipName = sTitle;
			
			dialog.text = "그건 쉽게 해결할 수 있지. 그는 계속 항해하고 있어  "+GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Name+"Voc"))+" '"+sTitle+" 노예 무역을 하고 있지... 이렇게 하자고: 우리가 그를 찾으면, 너는 화물을 가져가고 우리는 배를 가져간다. 아, 그리고 그에게 이것에 대해 아는지 물어봐도 돼\n "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_ACC)+". 그 이름을 듣고 겁에 질려 바지에 지리지 않길 바라지, 왜냐면 그건 내 배거든..."; // belamour gen
			link.l1 = "좋아, 거래 성사다.";
			link.l1.go = "PiratesOnUninhabited_45";
		break;
		
		case "PiratesOnUninhabited_45":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				rChar.Dialog.currentnode = "PiratesOnUninhabited_11_Again";
				rChar.location = "none"; // Убираем из локации при выходе   исправлено с NPChar на rChar - лесник
				rChar.location.locator = ""; // лесник  - так же исправлено .  тогда бага не будет.
			}
			
			Log_Info("Your crew was increased by " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " men.");
			
			ChangeCharacterComplexReputation(pchar,"nobility", 3.0);
			
			AddCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1)
			AddPassenger(PChar, NPChar, false); // Главного в пассажиры
			SetCharacterRemovable(NPChar, false);
			//NPChar.FaceId = 101; // лесник потом подобрать аву бандиту.   
			
			PChar.Quest.PiratesOnUninhabited_LocExit.over = "yes"; // Снимаем прерывание на выход из локации
			
			sTemp = XI_ConvertString(PChar.location + "Gen"); // belamour gen
			
			sTitle = "PiratesOnUninhabited" + PChar.location;
			ReOpenQuestHeader(sTitle);
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "13");
			AddQuestUserDataForTitle(sTitle, "shoreName", sTemp);
			AddQuestUserData(sTitle, "shoreName", sTemp);
			// --> belamour окончание по количеству персон
			if(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) >= 5)
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailors");
			}
			else
			{
				AddQuestUserData(sTitle, "count", PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " sailor");
			}
			// <-- belamour
			AddQuestUserData(sTitle, "badCapName", ChangeNameCase(NAMETYPE_ORIG, PChar.GenQuest.PiratesOnUninhabited.BadPirateName, NAME_ABL));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name + "Voc")) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'"); // belamour gen
			
			PChar.GenQuest.PiratesOnUninhabited.StartShore = PChar.location;
			
			PiratesOnUninhabited_SetCapToMap(); // Ставим корабль на карту
			
			DialogExit();
		break;
		
		// Диалог с кэпом в каюте
		case "PiratesOnUninhabited_46":
			dialog.text = "도대체 나한테 뭘 원하는 거야?";
			link.l1 = "나는 ~을(를) 대신해 인사하러 왔어 "+ChangeNameCase(NAMETYPE_NICK,PChar.GenQuest.PiratesOnUninhabited.MainPirateName,NAME_GEN)+". 그 사람을 아는 거지?";
			link.l1.go = "PiratesOnUninhabited_47";
			
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";
			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		break;
		
		case "PiratesOnUninhabited_47":
			dialog.text = "전에 그 악당을 목 졸라 죽이지 못한 게 아쉽군. 뭐, 이제 내 관용에 대한 대가를 치를 때가 온 것 같아...";
			link.l1 = "정말이지... 그리고 이제 시간이 다 되어버렸군...";
			link.l1.go = "PiratesOnUninhabited_48";
		break;
		
		case "PiratesOnUninhabited_48":
			LAi_CharacterDisableDialog(NPChar);
			LAi_Group_Attack(NPChar, Pchar);
			
			LAi_SetCurHPMax(NPChar);
			QuestAboardCabinDialogFree(); // важный метод
			
			LAi_Group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
			LAi_Group_SetCheckFunction(LAI_GROUP_BRDENEMY, "PiratesOnUninhabited_CapDeath");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_49":
			dialog.text = "잘했어, 선장! 그럼 약속대로지? 우리가 배를 가져가고, 너는 화물을 가져가는 거야?";
			link.l1 = "그래. 배를 가져가서 잘 써라.";
			link.l1.go = "PiratesOnUninhabited_50";
		break;
		
		case "PiratesOnUninhabited_50":
			NPChar.LifeDay = 0;
			NPChar.location = "none"; // Убираем из каюты
			NPChar.location.locator = "";
			
			RemovePassenger(PChar, NPChar);
			RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "14");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			ChangeAttributesFromCharacter(CharacterFromID("PiratesOnUninhabited_BadPirate"), NPChar, true);
			DialogExit();
			
		break;
		
		// На палубе, когда корабль с нашим пиратом отпустили
		case "PiratesOnUninhabited_50_Deck1":
			dialog.text = "환영하오, 선장 "+PChar.name+".";
			link.l1 = "그래서, 네 배는 마음에 드냐?";
			link.l1.go = "PiratesOnUninhabited_50_Deck2";
		break;
		
		case "PiratesOnUninhabited_50_Deck2":
			dialog.text = "헤헤... 삐걱거리고 끼익거리는 게 꼭 나 같군. 우리 둘 다 더 이상 바다를 오래 누빌 시간은 별로 남지 않은 것 같아...";
			link.l1 = "그럼, 행운을 빌지...";
			link.l1.go = "exit";
			NextDiag.TempNode = "PiratesOnUninhabited_50_Deck1";
		break;
		
		// В бухте, вариант, когда корабль, который нужно было захватить, утопили
		case "PiratesOnUninhabited_51":
			dialog.text = "왜 내 배를 침몰시켰어?! 우리 약속 기억이나 하냐?";
			link.l1 = "뭐? 내가 그 자식한테 침몰당하고 싶었던 건 아니잖아. 간신히 살아남은 거 안 보여?";
			link.l1.go = "PiratesOnUninhabited_52";
		break;
		
		case "PiratesOnUninhabited_52":
			if(hrand(1) == 1)
			{
				dialog.text = "누가 그렇게 싸우냐? 그런 배를 잃다니! 도대체 뭐야! 너 같은 애송이가 여기서 뭘 하고 있는 거냐?";
				link.l1 = "네 혓바닥을 뽑아버릴 거다, 이 잡놈아.";
				link.l1.go = "PiratesOnUninhabited_53";
			}
			else
			{
				iMoney = sti(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].Price);
				iMoney = MakeInt((iMoney / 1.2 + hrand(iMoney - (iMoney / 1.2))) * 1.2);
				dialog.text = "누가 그렇게 싸우냐? 그런 배를 잃다니! 그게 나한테 얼마나 비쌌는지 알기나 해? "+FindRussianMoneyString(iMoney)+"! 이제 나한테 빚졌군...";
				link.l1 = "너한테 너무 벅찬 거 아니야? 내가 이미 한 번 신세를 져줬다는 거 잊지 마라.";
				link.l1.go = "PiratesOnUninhabited_54";
				
				if(sti(PChar.money) >= iMoney)
				{
					link.l2 = "빌어먹을 너랑 그 저주받은 배도 다 꺼져라! 돈이나 챙기고 다시는 내 눈에 띄지 마라!";
					link.l2.go = "PiratesOnUninhabited_55";
				}
			}
		break;
		
		case "PiratesOnUninhabited_53":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetImmortal(rChar, false);
				rChar.LifeDay = 0;
			}
			
			LAi_Group_SetRelation("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("PiratesOnUninhabitedGroup", LAI_GROUP_PLAYER, true);
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "15");
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			AddDialogExitQuest("MainHeroFightModeOn");
			
			DialogExit();
		break;
		
		case "PiratesOnUninhabited_54":
			dialog.text = "지금 와서 그 호의가 나한테 무슨 소용이 있겠어?! 만약 선장이 "+ChangeNameCase(NAMETYPE_ORIG,PChar.GenQuest.PiratesOnUninhabited.BadPirateName,NAME_NOM)+" 지금 내 배랑 함께 바닷속에 가라앉았지! 이제 내 몫도, 내 배도 다시는 못 찾게 됐어! 이런 팔자라니, 거지처럼 시궁창에서 죽게 생겼군!!!";
			link.l1 = "하지만 왜지? 내가 너를 위해 장대한 장례식을 치러줄 수 있어. 바로 여기서, 괜찮다면 말이야...";
			link.l1.go = "PiratesOnUninhabited_53";
		break;
		
		case "PiratesOnUninhabited_55":
			for(i = 0; i < sti(PChar.GenQuest.PiratesOnUninhabited.PiratesQty); i++)
			{
				rChar = CharacterFromID("PirateOnUninhabited_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_SetImmortal(rChar, false);
				LAi_CharacterDisableDialog(rChar);
				rChar.LifeDay = 0;
			}
			
			sTitle = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
			AddQuestRecordEx(sTitle, "PiratesOnUninhabited", "16");
			AddQuestUserData(sTitle, "sSex", GetSexPhrase("",""));
			AddQuestUserData(sTitle, "ship", GetStrSmallRegister(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'");
			CloseQuestHeader(sTitle);
			
			DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");
			
			DialogExit();
		break;
		
		// КОНЕЦ
		
		// Warship, 15.05.11. Генер "Justice for sale".
		case "JusticeOnSale_1":
			dialog.text = "우리끼리... 합의를 볼 수도 있지 않을까 싶네? 우리한테 한 가지 신세를 지면, 우리가 갚아주지, 헤헤.";
			link.l1 = "부탁이라고? 그래서 조건이 뭔데, 뭘 내놓겠다는 거야?";
			link.l1.go = "JusticeOnSale_3";
		break;
		
		case "JusticeOnSale_2":
			LAi_Group_SetRelation("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_Group_FightGroups("JusticeOnSaleGroup_" + LoadedLocation.index, LAI_GROUP_PLAYER, true);
			
			DialogExit();
			LAi_SetFightMode(PChar, true);
		break;
		
		case "JusticeOnSale_3":
			dialog.text = "우리 선장 "+PChar.GenQuest.JusticeOnSale.SmugglerName+" 현지 순찰대에게 붙잡혔어  "+XI_ConvertString("Colony"+PChar.GenQuest.JusticeOnSale.CityId+"Gen")+". 놈들이 그를 감옥에 가뒀지만, 교수형에 처할 증거는 부족해. 우리가 직접 끌어낼 수도 없어\n"+"당신은 존경받는 사람이오. 사람들이 당신을 알아보지. 아마 협상하거나, 보석금을 내주거나, 아니면 그냥 그를 사버릴 수도 있지 않겠소? 우리를 믿으시오, 우리가 그 사람을 데려가면 곧바로 섬을 떠날 테니 당신의 평판에는 아무런 해가 없을 것이오!"; // belamour gen
			link.l1 = "내가 도와줄 수 있다고 치자. 그런데 내 보수는 어떻게 할 건데?";
			link.l1.go = "JusticeOnSale_4";
			link.l2 = "지옥으로 꺼져라, 악마 같은 놈! 너랑은 상종 안 해!";
			link.l2.go = "JusticeOnSale_5";
		break;
		
		case "JusticeOnSale_4":
			dialog.text = "인디언 장신구랑 부적 좀 볼래? 꽤 희귀한 거야... 아니면 바로 현금이 더 좋아? 몇 천 페소 정도면 어때?";
			link.l1 = "지옥으로 꺼져라, 악마 같은 놈! 너하고는 상종 안 해!";
			link.l1.go = "JusticeOnSale_5";
			link.l2 = "나는 인디언 장신구에 관심이 있어. 나도 동의하지.";
			link.l2.go = "JusticeOnSale_6";
			link.l3 = "현찰이야말로 선원의 제일가는 친구지. 돈은 냄새도 없다는 거, 우리 모두 알잖아. 나도 동의해.";
			link.l3.go = "JusticeOnSale_7";
		break;
		
		case "JusticeOnSale_5":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			DialogExit();
		break;
		
		case "JusticeOnSale_6":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 0; // Подрякушки.
			dialog.text = "감사합니다, 선장. 보상금 외에도 보석금만큼 더 드리겠습니다. 우리 선장에 관해서는 지휘관과 직접 이야기해 보시는 게 좋겠군요. 어쩌면 그를 설득할 수 있을지도 모르죠. 선장을 구출하면, 저희에게 오십시오 "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", 거기에 우리 배가 닻을 내렸지 - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+"'. 우리는 해변에서 기다릴게."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_7":
			PChar.GenQuest.JusticeOnSale.ShipName = GenerateRandomNameToShip(PIRATE);
			PChar.GenQuest.JusticeOnSale.ShipType = PiratesOnUninhabited_GenerateShipType();
			PChar.GenQuest.JusticeOnSale.RewardType = 1; // Монеты.
			
			dialog.text = "고마워, 선장. 보상금 외에 보석금만큼도 따로 챙겨줄게. 우리 선장에 관해선 지휘관과 얘기해보는 게 좋겠지. 설득할 수 있을지도 모르니까. 선장을 빼내면, \n "+XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId+"Dat")+", 거기에 우리 배가 닻을 내렸지 - "+LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.JusticeOnSale.ShipType)].name))+" '"+PChar.GenQuest.JusticeOnSale.ShipName+". 우리는 해안에서 기다리고 있을게."; // belamour gen
			link.l1 = "...";
			link.l1.go = "JusticeOnSale_8";
		break;
		
		case "JusticeOnSale_8":
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_Jungle_" + i);
				LAi_CharacterDisableDialog(rChar);
			}
			ReOpenQuestHeader("JusticeOnSale");
			AddQuestRecord("JusticeOnSale", "1");
			AddQuestUserData("JusticeOnSale", "cityName", XI_ConvertString("Colony" + PChar.GenQuest.JusticeOnSale.CityId + "Gen")); // belamour gen
			PChar.GenQuest.JusticeOnSale.MayorWait = true;
			PChar.GenQuest.JusticeOnSale.PrisonWait = true;
			
			DialogExit();
		break;
		
		case "JusticeOnSale_9":
			if(hrand(1) == 0)
			{
				if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
				{
					// Награда побрякушками.
					dialog.text = "왔습니다, 선장님! 그 뚱뚱한 관리 놈들을 잘 속이셨군요! 여기 보상입니다. 얘들아, 장신구 가져와라!";
				}
				else
				{
					// Награда золотом.
					dialog.text = "도착했소, 선장님! 그 뚱뚱한 관료놈들 제대로 속이셨군요! 여기 보상입니다. 얘들아, 상자 가져와라!";
				}
				
				link.l1 = "내 몫 내놔, 그리고 꺼져!";
				link.l1.go = "JusticeOnSale_10";
			}
			else
			{
				// Массакра.
				dialog.text = "왔어, 선장! 다 잘 준비해놨구만. 그런데 말이지... 우린 증인이 필요 없어, 그래서... 선장님께 감사 인사하자, 얘들아!";
				link.l1 = RandSwear()+"처음 만났을 때 바로 널 쏴버렸어야 했는데!";
				link.l1.go = "JusticeOnSale_11";
			}
			chrDisableReloadToLocation = false;
		break;
		
		case "JusticeOnSale_10":
			DialogExit();
			if(sti(PChar.GenQuest.JusticeOnSale.RewardType) == 0)
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddItems(PChar, "indian_"+(1+hrand(10)), 1);
				}
				else
				{
					AddItems(PChar, "obereg_"+(1+hrand(10)), 1);
				}
			}
			else
			{
				if(CheckAttribute(PChar, "GenQuest.JusticeOnSale.PrisonMoney"))
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 700 + hrand(2000));
				}
				else
				{
					AddMoneyToCharacter(PChar, sti(PChar.rank) * 500 + hrand(1000));
				}
			}
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_Type_Actor_Reset(rChar);
				LAi_ActorGoToLocation(rChar, "reload", LAi_FindNearestFreeLocator2Pchar("reload"), "none", "", "", "", 3.0);
			}
			AddQuestRecord("JusticeOnSale", "3");
			CloseQuestHeader("JusticeOnSale");
		break;
		
		case "JusticeOnSale_11":
			AddQuestRecord("JusticeOnSale", "4");
			CloseQuestHeader("JusticeOnSale");
			for(i = 0; i < sti(PChar.GenQuest.JusticeOnSale.EncQty); i++)
			{
				rChar = CharacterFromID("JusticeOnSale_ShorePirate_" + i);
				LAi_SetWarriorTypeNoGroup(rChar);
				LAi_Group_MoveCharacter(rChar, "JusticeOnSale_ShoreGroup");
			}
			
			LAi_Group_SetRelation("JusticeOnSale_ShoreGroup", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			AddDialogExitQuest("MainHeroFightModeOn");
			DialogExit();
		break;
		
		// belamour постоялец-->
		case "Unwantedpostor_room":
			dialog.text = ""+GetSexPhrase("너 누구야? 그리고 왜 내 방에 함부로 들어오는 거지?","이런 젠장. 누구냐? 여긴 내 방이야, 물론이지. 하지만 이런 손님이라면 나쁘지 않군. 사랑의 배달이라도 온 거냐?")+"";
			link.l1 = ""+GetSexPhrase("이제 네 방 아니야. 주점 주인이 나한테 방을 빌려줬고, 넌 돈도 안 내니까 곧 나가야지. 좋게 나갈 수도 있고, 힘들게 나갈 수도 있어. 선택은 네가 해.","꿈 꾸냐? 우리한테는 청소가 일이지. 그러니까 네 꼴도 치워. 이제 여긴 내 방이야. 너랑 달리 나는 항상 주인한테 돈을 내거든.")+"";
			link.l1.go = "Unwantedpostor_room_1";
		break;
		
		case "Unwantedpostor_room_1":
			If(sti(pchar.reputation.fame) > 60)
			{
				dialog.text = ""+GetSexPhrase("너에 대해 들어본 것 같아. 좋아, 네가 이겼다, 내가 나갈게, 아직은 살고 싶으니까...","흠, 네 소문은 많이 들었지. 네가 말만 날카로운 게 아닌 것 같군. 알았어, 화내지 마. 방은 네 거야.")+"";
				link.l1 = ""+GetSexPhrase("좋은 결정을 내렸군.","착하지.")+"";
				link.l1.go = "Unwantedpostor_peace";
				break;
			}
			dialog.text = ""+GetSexPhrase("그런 거였군, 응? 좋아, 난 힘든 길을 선택하지.","이 망할 년아! 내가 좋게 대해주려고 했는데...")+"";
			link.l1 = ""+GetSexPhrase("원하시는 대로...","그걸 '친절하다'고 부르나? 불쌍하군. 아니, 어쩌면 그렇지도 않지.")+"";
			link.l1.go = "Unwantedpostor_fight";
		break;
		
		case "Unwantedpostor_peace":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			DeleteAttribute(PChar, "GenQuest.Unwantedpostor");
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 180, false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "Fortune", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Sneak", sti(sTemp));
			AddCharacterExpToSkill(pchar, "Leadership", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_fight":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			LAi_SetFightMode(pchar, true);
			sld = characterFromId("Berglar_Unwantedpostor"); 
			LAi_SetWarriorType(sld);
			LAi_Group_MoveCharacter(sld, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_SetCheckMinHP(sld, 10, true, "Unwantedpostor_Win");
			LAi_SetCheckMinHP(pchar, 10, true, "Unwantedpostor_Lose");	
		break;
		
		case "Unwantedpostor_Win":
			dialog.text = ""+GetSexPhrase("알았어, 그만해! 죽이지 마. 나 갈게.","멈춰! 이제 어쩌라고, 이 방 하나 때문에 서로 죽이라 이거야?! 다 가져라, 목에 걸려라. 냄새나는 놈...")+"";
			link.l1 = ""+GetSexPhrase("옳은 결정이야. 다음엔 머리를 좀 써라. 나처럼 착한 사람만 있는 건 아니니까, 어떤 놈들은 실수로라도 널 죽일 수도 있어.","놈들.")+"";
			link.l1.go = "Unwantedpostor_Win_1";
		break;
		
		case "Unwantedpostor_Win_1":
			DialogExit();
			sld = CharacterFromID("Berglar_Unwantedpostor");
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) DeleteAttribute(PChar, "GenQuest.Unwantedpostor"); // полуночная драка
			SetFunctionTimerCondition("Unwantedpostor_NextQuest", 0, 0, 170+rand(20), false);
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sTemp = 40*MOD_SKILL_ENEMY_RATE/2;
			AddCharacterExpToSkill(pchar, "FencingL", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingS", sti(sTemp));
			AddCharacterExpToSkill(pchar, "FencingH", sti(sTemp));
			AddDialogExitQuest("sleep_in_tavern");
			TavernWaitDate("wait_day");
		break;
		
		case "Unwantedpostor_Lose":
			dialog.text = ""+GetSexPhrase("그래, 나 쫓아냈냐? 여기서 꺼져라, 안 그러면 베어버릴 테니까.","그래, 너희가 할 줄 아는 건 떠드는 것뿐이군. 내가 아직 기분이 좋아서 다행인 줄 알아. 아니었으면 더 끔찍한 꼴을 당했을 거다. 썩 꺼져!")+"";
			link.l1 = ""+GetSexPhrase("젠장...","젠장, 내가 널 얕봤군... 알았어, 알았다고, 지금 나간다.")+"";
			link.l1.go = "Unwantedpostor_Lose_1";
		break;
		
		case "Unwantedpostor_Lose_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); //разрешить драться
			chrDisableReloadToLocation = false; // открыть локацию
			sld = CharacterFromID("Berglar_Unwantedpostor");
			sld.lifeday = 0;
			if(CheckAttribute(pchar,"GenQuest.Unwantedpostor")) pchar.GenQuest.Unwantedpostor = "Lose"; // если драка за полночь перевалит
			DoQuestReloadToLocation(Locations[FindLocation(pchar.location)].fastreload+"_tavern", "reload", "reload2_back", "");	
		break;
		// <-- belamour постоялец
		
		// belamour пьяный матрос -->
		case "GuiltySailor":
			dialog.text = "어?.. 꺼져, 풋내기야, 난 아무하고나... 딸꾹!.. 술 안 마신다.";
			link.l1 = "지금 당장 한 대 쳐줄 테니, 일주일은 술도 못 마실 거다.";
			link.l1.go = "GuiltySailor_1";
		break;
		
		case "GuiltySailor_1":
			dialog.text = "뭐?! 네가 지금 누구한테 말하는지 아냐? 나는 배 '"+pchar.ship.name+"! 선장한테만 알리면, 넌 도시에서 빠져나갈 시간도 없을 거야! 아직 멀쩡할 때 꺼져라."; 
			link.l1 = "...";
			link.l1.go = "GuiltySailor_2";
		break;
		
		case "GuiltySailor_2":
			dialog.text = "...";
			link.l1 = "...";
			link.l1.go = "GuiltySailor_3";
		break;
		
		case "GuiltySailor_3":
			dialog.text = "선장?..";
			link.l1 = "한 달 동안 갑판을 닦아야 할 거다.";
			link.l1.go = "GuiltySailor_4";
		break;
		
		case "GuiltySailor_4":
			NPChar.Dialog.currentnode = "GuiltySailor_Again";
			SetFunctionTimerCondition("GuiltySailor_NextQ", 0, 0, 45+rand(45), false);
			DialogExit();
		break;
		
		case "GuiltySailor_Again":
			dialog.text = "미안해요, 선장님!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "GuiltySailor_Again";
		break;
		// <-- пьяный матрос
		
		// belamour хороший специалист -->
		case "ExpertSailor":
			int ExpertSailorVar = 1 + hrand(2);
			dialog.text = "안녕, 선장! 네가 선장인 거 다 알고 있지.";
			link.l1 = "안녕. 내가 선장인 걸 어떻게 알았지?";
			link.l1.go = "ExpertSailor_"+ExpertSailorVar;
		break;
		
		case "ExpertSailor_1": // матрос
			dialog.text = "하, 나는 바다에서 잔뼈가 굵은 뱃사람이야. 바다를 누빈 지도 십 년이 넘었지. 주로 항해 일에 종사했어. 잔잔한 바다든 폭풍이 치는 바다든, 루거선이든 전함이든 다 타봤다네. 사실 지난달에 힘든 전투 끝에 부상을 입었어. 맹렬한 폭풍이 몰아쳤고, 아무도 돛대에 오르려 하지 않길래 내가 직접 올라갔지. 하지만 그 대가를 치르고 말았어. 다행히 발목만 삐어서 몇 주 동안 걷지 못했을 뿐이야. 그래서 육지로 보내졌지. 이제는 많이 나아져서 이렇게 앉아 기회를 기다리고 있다네.";
			link.l1 = "흥미롭군. 이런 일에 전문가가 한 명 있으면 나쁠 것 없지. 내 선원으로 들어올 생각 있나?";
			link.l1.go = "ExpertSailor_1_1";
		break;
		
		case "ExpertSailor_1_1":
			dialog.text = "왜 안 되겠어? 벌써부터 배 갑판이랑 신선한 바람에 부풀린 돛 소리가 그리워지네. 필요하다면 네 일행도 지도해 줄 수 있어. 하지만 미리 말해두지, 나는 바로 천 페소를 요구할 거야. 안 그러면 내 주머니는 이미 텅 비었거든. 뭐, 사실 다른 일행들도 다 마찬가지지. 나는 정직한 사람이야.";
			link.l1 = "아니, 난 아마 거절할 거야. 선원 한 명당 천 페소씩 주고 데려오면 파산하겠지. 나한테 탓하지 마.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "거래지. 실력 좋은 전문가에게 천 페소쯤이야 아깝지 않지. 잠깐만... 여기. 그리고 배에서 기다릴 테니.";
				link.l2.go = "ExpertSailor_payS";
			}
		break;
		
		case "ExpertSailor_nomoney":
			DialogExit();
			NPChar.Dialog.currentnode = "ExpertSailor_Again";
		break;
		
		case "ExpertSailor_payS":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Sailors", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_2": // канонир
			dialog.text = "하, 나는 바다에서 잔뼈가 굵은 놈이지. 10년 넘게 바다를 누볐어. 대부분 대포 옆에 붙어 있었지. 팔코넷, 캐러네이드, 컬버린, 세이커... 이런 걸로 쏘기도 했고, 루거선에서도 일했고 전열함에서도 복무했어. 사실 지난달에 힘든 전투 끝에 부상을 입었지. 산탄이 튕겨서 맞았는데, 심각한 건 아니고 다리에 긁힌 자국만 남았어. 그래서 뭍으로 내쳐졌지. 이제는 괜찮아져서 여기 앉아 기회를 기다리고 있어.";
			link.l1 = "흥미롭군. 이런 일에 전문가가 있다면 나쁠 것 없지. 내 일행에 들어올 생각 있나?";
			link.l1.go = "ExpertSailor_2_1";
		break;
		
		case "ExpertSailor_2_1":
			dialog.text = "왜 안 되겠어? 난 이미 포갑판이 그립고, 화약 타는 냄새랑 대포 일제사격의 굉음도 그리워. 필요하다면 네 팀도 지도해 줄 수 있지. 하지만 미리 경고하는데, 천 페소는 받아야 해. 아니면 내 주머니는 계속 비어 있을 거야. 그리고 다른 팀원들처럼 나도 정직한 사람이거든.";
			link.l1 = "아니, 난 아마 거절할 거야. 선원 한 명당 천 페소씩 주고 계약하면 나 파산하겠지. 나한테 탓하지 마.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "좋아. 실력 있는 전문가에게 천 페소쯤이야 아깝지 않지. 잠깐만... 여기. 그리고 배에서 기다릴게.";
				link.l2.go = "ExpertSailor_payС";
			}
		break;
		
		case "ExpertSailor_payС":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Cannoners", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_3": // солдат
			dialog.text = "하, 나는 바다에서 잔뼈가 굵은 놈이지. 십 년 넘게 바다를 누볐어. 주로 백병전에서 싸웠지: 해적이든 정규군이든 다 상대해 봤고, 온갖 무기를 다룰 줄 알아. 러거선에서도 복무했고, 전함에서도 일했지. 사실 지난달에 힘든 전투 끝에 부상을 입었어. 등에 작은 세이버 흠집 하나—겁쟁이가 정면승부를 못 하더라고. 대신 내가 그놈을 죽였지. 아, 그 상처를 보고 놈들 표정 좀 봤어야 했는데, 하하. 그래서 나를 육지로 보냈지. 이제는 괜찮아져서 여기 앉아 기회를 기다리고 있어.";
			link.l1 = "흥미롭군. 이런 일에 전문가가 있다면 나쁠 게 없지. 내 선원으로 들어올래?";
			link.l1.go = "ExpertSailor_3_1";
		break;
		
		case "ExpertSailor_3_1":
			dialog.text = "왜 안 되겠어? 벌써부터 칼 부딪히는 소리, 배들이 서로 다가오며 내는 삐걱임, 전투의 아드레날린이 그리워지거든. 필요하다면 네 팀을 지도해줄 수도 있지. 하지만 내 주머니가 이미 텅 비었으니, 선불로 천 페소는 받아야겠어. 그리고 팀의 다른 녀석들처럼, 나도 정직한 사내야.";
			link.l1 = "아니, 난 아마 거절할 거야. 선원 한 명당 천 페소씩 주고 데려오면 파산하고 말지. 나한테 뭐라 하지 마.";
			link.l1.go = "ExpertSailor_nomoney";
			if(GetFreeCrewQuantity(pchar) > 0 && sti(pchar.money) >= 1000)
			{
				link.l2 = "좋아. 실력 있는 전문가라면 천 페소쯤 내는 건 상관없지. 잠깐만... 여기. 그리고 배에서 기다리고 있을게.";
				link.l2.go = "ExpertSailor_payA";
			}
		break;
		
		case "ExpertSailor_payA":
			DialogExit();
			AddMoneyToCharacter(pchar, -1000);
			AddCharacterCrew(pchar, 1);
			ChangeCrewExp(pchar, "Soldiers", 10);
			AddCrewMorale(pchar, 1);
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
		break;
		
		case "ExpertSailor_Again":
			dialog.text = "바다에서 행운을 빌어, 선장님!";
			link.l1 = "너도 그래.";
			link.l1.go = "exit";
			NextDiag.TempNode = "ExpertSailor_Again";
		break;
		// <-- хороший специалист
		
		//belamour ночной приключенец -->
		// матрос -->
		case "NightAdventure_Sailor":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "누, 누구냐?";
			link.l1 = "나는 선장이야 "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "미안하다, 친구, 나 지금 급해.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_SailorTavern":          link.l1.go = "NightAdventure_Sailor_1_1"; break; // до таверны
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1"; break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1"; break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1"; break; 
				case "NightAdventure_SailorBoat":      		 link.l1.go = "NightAdventure_Sailor_3_1"; break; // до пирса
				case "NightAdventure_SailorShip":            link.l1.go = "NightAdventure_Sailor_3_1"; break;
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";       break; // наезд
			}
		break;
		// до таверны 
		case "NightAdventure_Sailor_1_1":
			dialog.text = "선장?.. 힉! 선장... 나를 주, 주점까지 좀 데려다줘... 힉!.. 어? 제발. 여기 이 식민지에서... 길을 잃은 것 같아, 응... 힉!..";
			link.l1 = "비켜, 나 바빠!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "좋아, 가자. 너 혼자서는 거기까지 못 갈 것 같으니까.";
			link.l2.go = "NightAdventure_Sailor_1_2";
		break;
		
		case "NightAdventure_Sailor_1_2":
			dialog.text = "그냥... 헉!.. 천천히, 제발. 나... 헉!.. 지금... 일어설 수가... 없어...";
			link.l1 = "좋아, 가자, 천천히.";
			link.l1.go = "NightAdventure_Sailor_tavern";
		break;
		
		case "NightAdventure_Sailor_tavern":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorTavern"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// шулер
		case "NightAdventure_Sailor_2_1":
			dialog.text = "선장님?.. 히끅!.. 선장님... 도와줘!";
			link.l1 = "비켜, 나 바빠!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "너 왜 이래?";
			link.l2.go = "NightAdventure_Sailor_2_2";
		break;
		
		case "NightAdventure_Sailor_2_2":
			dialog.text = "저기... 선술집에... 힉!.. 카드 사기꾼이 있어!";
			link.l1 = "그래서 뭐가 문제야? 어느 식민지의 어느 선술집이든 카드 사기꾼들은 지천에 널렸지.";
			link.l1.go = "NightAdventure_Sailor_2_3";
		break;
		
		case "NightAdventure_Sailor_2_3":
			dialog.text = "선장님, 그, 그쪽은... 이해 못 하셔... 힉!... 그가 나를, 나를... 페소 한 푼도 안 남기고 떠났어! 힉!.. 그리고는... 나를 내쫓았지... 힉!..";
			link.l1 = "그래서, 이제 나한테 뭘 원하는 거야?";
			link.l1.go = "NightAdventure_Sailor_2_4";
		break;
		
		case "NightAdventure_Sailor_2_4":
			dialog.text = "나랑 같이 가... 힉!... 저 놈 좀 처리해 줘! 내 돈 돌려주게... 힉!... 만들어! 힉!..";
			link.l1 = "술에 취한 놈 상대로는 카드 고수일 필요도 없어. 다음엔 술 좀 덜 마셔라.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "그래, 이게 나한테 왜 필요하지, 응? .. 좋아, 가자. 네 카드 사기꾼 한번 보자.";
			link.l2.go = "NightAdventure_Sailor_2_5";
		break;
		
		case "NightAdventure_Sailor_2_5":
			dialog.text = "그냥... 딸꾹!.. 천, 천천히 해 줘. 나... 딸꾹!.. 서, 설 수가... 없어...";
			link.l1 = "좋아, 천천히 가자.";
			link.l1.go = "NightAdventure_Sailor_gambler";
		break;
		
		case "NightAdventure_Sailor_gambler":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = "NA_SailorGambler"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		// диалог в таверне с матросом
		case "NA_SailorTavern":
			dialog.text = "선장님... 힉!.. 정말 고마워요... 덕분에 살았어요! 나... 여기요... 힉!.. 이거 받으세요.";
			link.l1 = "자, 됐어... 이제 그렇게 마시지 마. 아니면 적어도 괜히 문제 만들지 말라고.";
			link.l1.go = "NA_SailorTavern_1";
		break;
		
		case "NA_SailorTavern_1":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор про  шулера
		case "NA_SailorGambler":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShuler0")
			{
				dialog.text = "선장님!.. 그... 딸꾹!.. 카드 사기꾼이!..";
				link.l1 = "누구, 나? 카드 사기꾼이라고?";
				link.l1.go = "NA_SailorGamblerBelka";
			}
			else	
			{
				dialog.text = "저기 있어요, 선장님! 히끅!.. 저, 저기 테이블에 앉아 있어요...";
				link.l1 = "가자...";
				link.l1.go = "NA_SailorGamblerCards"; 
			}
					
		break;
		// шулер сбежал
		case "NA_SailorGamblerBelka": 
			dialog.text = "아니... 힉!... 샤퍼!... 그 녀석이 사라졌어!...";
			link.l1 = "글쎄, 그는 떠났으니 널 기다리지 않은 거야.";
			link.l1.go = "NA_SailorGamblerBelka_1";
		break;
		
		case "NA_SailorGamblerBelka_1":
			dialog.text = "그리고 뭐가... 다, 다음이야? 힉!..";
			link.l1 = "이제 와서 네가 할 수 있는 건 없어. 난 밤에 식민지 전체를 뒤지면서 그 녀석을 찾을 생각 전혀 없어. 그렇게 술 마시지 마라. 아니면 적어도 취한 채로 도박은 하지 말라고.";
			link.l1.go = "NA_SailorGamblerBelka_2";
		break;
		
		case "NA_SailorGamblerBelka_2":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		// шулер остался таверне
		case "NA_SailorGamblerCards":
			DialogExit();
			pchar.quest.NightAdventure_Intavern.over = "yes";
			iNation = npchar.nation
			iRank = MOD_SKILL_ENEMY_RATE+sti(pchar.rank);
			iScl = 15 + 2*sti(pchar.rank);
			sld = GetCharacter(NPC_GenerateCharacter("NightAdventure_CardProf", "citiz_"+(rand(9)+11), "man", "man", iRank, iNation, 1, false, "soldier"));
			FantomMakeCoolFighter(sld, iRank, iScl, iScl, "blade_04", "pistol1", "bullet", iScl*2);
			sld.dialog.filename    = "GenQuests_Dialog.c";
			sld.dialog.currentnode = "NightAdventure_CardProf";
			sld.greeting = "player";
			sld.SaveItemsForDead = true;
			sld.DontClearDead = true;
			AddMoneyToCharacter(sld, sti(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(sld, "totem_13");
			FreeSitLocator(pchar.location, "sit_front4");
			ChangeCharacterAddressGroup(sld, pchar.location, "sit", "sit_front4");
			LAi_SetSitType(sld);
			chrDisableReloadToLocation = false;
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// разговор с самим шулером
		case "NightAdventure_CardProf":
			dialog.text = "주사위 게임 한 판 어때? 할래?";
			link.l1 = "말도 안 돼. 이 배의 선장은 나고, 나는 카드 사기꾼이랑 놀지 않아. 하지만 저기 있는 착한 사람한테 돈 안 돌려주면 네 갈비뼈는 쉽게 부러뜨릴 수 있어.";
			link.l1.go = "NightAdventure_CardProf_1";
		break;
		
		case "NightAdventure_CardProf_1":
			dialog.text = "카드 사기꾼들이랑?! 내가 카드 사기꾼이라고? 돈을 누구한테 돌려주라고, 저 술주정뱅이한테?! 나를 모욕하는군, 선장...";
			link.l1 = "더 심하게 나올 수도 있어. 돈 내놔.";
			link.l1.go = "NightAdventure_CardProf_2";
		break;
		
		case "NightAdventure_CardProf_2":
			dialog.text = "그래, 난 카드 사기꾼이 아니야! 나는 정정당당하게 게임하지. 운이 이기는 거고, 네 친구는 그냥 운이 없었던 거야, 그게 다야.";
			link.l1 = "운이라고? 주사위 좀 줘 봐. 얼마나 운이 따르는지 내가 직접 볼게.";
			link.l1.go = "NightAdventure_CardProf_3";
		break;
		
		case "NightAdventure_CardProf_3":
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveMoney") // отдал деньги
			{
				AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money));
				dialog.text = "알았어, 알았어, 진정해, 선장. 자, 내가 그 주정뱅이를 이겼고, 좀 속임수도 썼지만, 다른 놈들도 다 그렇게 해. 여기 그의 돈이야.";
				link.l1 = "그거면 됐다. 그리고 내 친구가 이게 전부가 아니라고 하면, 내가 다시 찾아올 거라는 거 이해하지?";
				link.l1.go = "NightAdventure_CardProf_GiveMoney";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerGiveOk") // играл честно
			{
				dialog.text = "그래, 여기 내 주사위야. 두 세트 다 있지. 확인해 봐. 숨길 거 없어.";
				link.l1 = "그래... 원페어... 꽝... 원페어... 트리플... 꽝... 꽝... 투페어... 트리플... 꽝... 원페어...";
				link.l1.go = "NightAdventure_CardProf_Ok";
			}
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorShulerFight") // драка
			{
				dialog.text = "그래, 여기 내 주사위야. 두 세트 다 있어. 확인해 봐. 숨길 건 아무것도 없어.";
				link.l1 = "그래... 포카드... 포카드... 풀하우스... 풀하우스... 포카드... 포커... 풀하우스... 포커... 포카드... 풀하우스... 흠, 이걸 나한테 어떻게 설명할 건데?";
				link.l1.go = "NightAdventure_CardProf_Fight";
			}
		break;
		// разошлись миром
		case "NightAdventure_CardProf_GiveMoney":
			dialog.text = "모두 이해했어, 여기 전액이야. 너랑 네 친구에게 행운을 빌어.";
			link.l1 = "너도 그래.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_1";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_1":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_GiveMoney_2";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// матрос забирает свои деньги
		case "NightAdventure_CardProf_GiveMoney_2":
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			dialog.text = "하지만... 그 녀석, 인정하기 싫어했어! 힉!..";
			link.l1 = "그래, 피하려고 했어. 자, 돈 가져가.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_3";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_3":
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
			dialog.text = "선장님... 힉!.. 정말 고마워요... 덕분에 살았어요! 나... '옆으로 토함'... 자요... 힉!.. 이거 받아요.";
			link.l1 = "자, 으으... 됐다... 이제 그렇게 마시지 마. 적어도 취했을 땐 도박하지 말라고.";
			link.l1.go = "NightAdventure_CardProf_GiveMoney_4";
		break;
		
		case "NightAdventure_CardProf_GiveMoney_4":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// играл честно
		case "NightAdventure_CardProf_Ok":
			dialog.text = "그래? 납득했어?";
			link.l1 = "흠, 정말 그냥 평범한 주사위인 것 같군 ...";
			link.l1.go = "NightAdventure_CardProf_Ok_1";
		break;
		
		case "NightAdventure_CardProf_Ok_1":
			dialog.text = "내가 말했잖아. 그리고 네 친구는 그냥 취했을 뿐이야. 자기 패배를 인정하지 못해서 너까지 여기로 데려온 거라고.";
			link.l1 = "좋아, 그 일은 미안하게 됐어. 행운을 빌지.";
			link.l1.go = "NightAdventure_CardProf_Ok_2";
		break;
		
		case "NightAdventure_CardProf_Ok_2":
			DialogExit();
			chrDisableReloadToLocation = true;
			LAi_CharacterDisableDialog(npchar);
			sld = characterFromId(pchar.GenQuest.NightAdventureId);
			sld.dialog.currentnode = "NightAdventure_CardProf_Ok_3";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		// подходит матрос
		case "NightAdventure_CardProf_Ok_3":
			dialog.text = "그래서... 힉!.. 뭐라고?.. 그... 힉!.. 사기꾼은 아니라고?..";
			link.l1 = "음, 그는 공정하게 게임을 한 것 같군.";
			link.l1.go = "NightAdventure_CardProf_Ok_4";
		break;
		
		case "NightAdventure_CardProf_Ok_4":
			dialog.text = "그리고 이제... 다, 다음은 뭐지? 히끅!..";
			link.l1 = "글쎄, 이제 네가 할 수 있는 건 없어. 그는 정정당당하게 널 이겼지. 그렇게 술 마시지 마라. 아니면 적어도 취했을 땐 도박하지 마.";
			link.l1.go = "NightAdventure_CardProf_Ok_5";
		break;
		
		case "NightAdventure_CardProf_Ok_5":
			DialogExit();
			chrDisableReloadToLocation = false;
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// драка 
		case "NightAdventure_CardProf_Fight":
			dialog.text = "운이야. 그냥 운이 좋았을 뿐이지. 운이라는 건 변덕스러운 여자라구.";
			link.l1 = "흠, 정말이군. 좋아, 그럼 너랑 놀아주지. 하지만 잘 들어, 난 이 주사위로 논다!";
			link.l1.go = "NightAdventure_CardProf_Fight_1";
		break;
		
		case "NightAdventure_CardProf_Fight_1":
			dialog.text = "이거?.. 그러니까... 아니, 너랑 놀기 싫어! 네가 날 모욕했잖아. 그리고 어차피, 나 지금 빈털터리야...";
			link.l1 = "혹시 내가 이 선술집에 있는 모두에게 네 주사위 얘기를 해줄까? 아니면 직접 보여줄까? 그러고 나서 네가 운에 대해 설명해보는 거지. 어때?";
			link.l1.go = "NightAdventure_CardProf_Fight_2";
		break;
		
		case "NightAdventure_CardProf_Fight_2":
			dialog.text = "뭐?! 네가 뭔데 이래?! 날 협박하려는 거야?! 당장 꺼지지 않으면 지금 바로 네 몸에 구멍 몇 개 내줄 테니까!";
			link.l1 = "나는 여기 남아서 모두에게 네 주사위를 보여주겠어.";
			link.l1.go = "NightAdventure_CardProf_Fight_3";
		break;
		
		case "NightAdventure_CardProf_Fight_3":
			dialog.text = "자, 이리 와라, 썩은 고기야!";
			link.l1 = "바지 잃어버리지 마라.";
			link.l1.go = "NightAdventure_CardProf_Fight_4";
		break;
		
		case "NightAdventure_CardProf_Fight_4":
			LAi_LocationDisableOfficersGen(pchar.location, true); // офицеров не  пускать
			SetFunctionLocationCondition("NightAdventure_Duel", Locations[FindLocation(pchar.location)].fastreload+"_town", false);
			pchar.quest.NightAdventure_KillPhant.over = "yes";
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// матрос на выходе
		case "NightAdventure_CardProf_Fight_5":
			dialog.text = "선장님?.. 당신이... 헉!.. 싸움을 했다고?.. 그리고 이 녀석이... 헉!.. 더 날카롭다고?";
			link.l1 = "지 혼자 얻어맞았어. 이제 아무하고도 안 놀 거야.";
			link.l1.go = "NightAdventure_CardProf_Fight_6";
		break;
		
		case "NightAdventure_CardProf_Fight_6":
			dialog.text = "하지만... 그 녀석, 인정하기 싫어했어! 히끅!..";
			link.l1 = "그래, 그 자식 피하려고 했어. 그냥 네 돈이 없었던 거야. 아마 다 써버렸겠지.";
			link.l1.go = "NightAdventure_CardProf_Fight_7NM";
			link.l2 = "그래, 그 자가 피하려고 했지. 자, 네 돈이다.";
			link.l2.go = "NightAdventure_CardProf_Fight_7";
		break;
		
		case "NightAdventure_CardProf_Fight_7NM": // скажем, что нет денег
			ChangeCharacterComplexReputation(pchar,"nobility", -5); 
			ChangeOfficersLoyality("bad", 2); 
			dialog.text = "그리고 이제... 다, 다음은 뭐야? 힉!..";
			link.l1 = "뭐, 이제 어쩔 수 없지. 그 녀석이 정정당당하게 이긴 거야. 그렇게 술 마시지 마라. 아니면 적어도 취했을 땐 도박하지 말라고.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
		break;
		
		case "NightAdventure_CardProf_Fight_7": // деньги есть
			AddMoneyToCharacter(pchar, - makeint(pchar.GenQuest.NightAdventure_money));
			ChangeCharacterComplexReputation(pchar,"nobility", 3); 
			ChangeOfficersLoyality("good", 1); 
			dialog.text = "ㅅ-선장님... 힉!.. 정말 고마워요... 덕분에 살았어요! 나... '옆으로 토함'... 자요... 힉!.. 이거 받아요.";
			link.l1 = "자, 으으... 됐다... 이제 그렇게 마시지 마라. 아니면 적어도 취했을 땐 도박하지 말라고.";
			link.l1.go = "NightAdventure_CardProf_Fight_End";
			AddMoneyToCharacter(pchar, makeint(pchar.GenQuest.NightAdventure_money)/2);
		break;
		
		case "NightAdventure_CardProf_Fight_End": 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			DeleteAttribute(pchar,"GenQuest.NightAdventure_money");
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			DialogExit();
			
		break;
		// проводить до пирса
		case "NightAdventure_Sailor_3_1":
			dialog.text = "선장?.. 히끅!.. 선, 선장... 나를 부두까지 좀 데려다줘... 히끅!.. 응? 제발. 나... 히끅!.. 배로 가야... 돛대장... 늦으면 욕할 거야... 히끅!..";
			link.l1 = "비켜, 나 지금 바빠!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "좋아, 가자. 너 혼자서는 거기 못 갈 것 같으니까\n";
			link.l2.go = "NightAdventure_Sailor_3_2";
		break;
		
		case "NightAdventure_Sailor_3_2":
			dialog.text = "그냥... 힉!.. 천천히, 제발. 나... 힉!.. 못... 버티겠어...";
			link.l1 = "좋아, 천천히 가자.";
			link.l1.go = "NightAdventure_Sailor_3_3";
		break;
		
		case "NightAdventure_Sailor_3_3":
			DialogExit();
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_SailorBoat")
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorBoat"; 
			}
			else
			{
				pchar.GenQuest.NightAdventureNode = "NA_SailorShip"; 
			}
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocatorCondition("NightAdventure_ToBoat",  npchar.City+"_town", "quest", "quest1", false)
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		// вариант просто проводить
		case "NA_SailorBoat":
			dialog.text = "선장님... 힉!.. 정말 고마워요... 진짜 큰 도움 받았어요! 나... '옆으로 토함'... 자요... 힉!.. 이거 받아요.";
			link.l1 = "자, 으... 됐다... 이제 그렇게 마시지 마라. 아니면 적어도 모험을 찾아다니진 마.";
			link.l1.go = "NA_SailorBoat_1";
		break;
		
		case "NA_SailorBoat_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			if(GetDataDay() < 7) AddMoneyToCharacter(pchar, 10);
			if(GetDataDay() >= 7  && GetDataDay() < 13)  {GiveItem2Character(pchar, "slave_01");  Log_Info("You've received Harpoon");}
			if(GetDataDay() >= 13 && GetDataDay() < 19)  {GiveItem2Character(pchar, "potion5");   Log_Info("You've received Ginger root");}
			if(GetDataDay() >= 19 && GetDataDay() < 25)  {GiveItem2Character(pchar, "cartridge"); Log_Info("You've received Paper cartridge");}
			if(GetDataDay() >= 25) 
			{
				if(GetDataDay() == 25) {GiveItem2Character(pchar, "amulet_8");  Log_Info("You've received amulet 'Anchor'");}
				if(GetDataDay() == 26) {GiveItem2Character(pchar, "amulet_9");  Log_Info("You've received amulet 'Encolpion'");}
				if(GetDataDay() == 27) {GiveItem2Character(pchar, "obereg_7");  Log_Info("You've received amulet 'Fisher'");}
				if(GetDataDay() >  27) {GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			}
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", -1); 
			DeleteAttribute(pchar,"GenQuest.NightAdventureNode");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// просится на корабль
		case "NA_SailorShip":
			dialog.text = "선장님!.. 배예요!";
			link.l1 = "무슨 '배'?";
			link.l1.go = "NA_SailorShip_1";
		break;
		
		case "NA_SailorShip_1":
			dialog.text = "배, 배가!.. 어디 있지?.. 힉!..";
			link.l1 = "분명히 그는 떠났어. 선술집에서 술 좀 덜 마셔라. 배 전체가 취한 선원 한 놈만 기다릴 순 없지.";
			link.l1.go = "NA_SailorShip_2";
		break;
		
		case "NA_SailorShip_2":
			dialog.text = "하지만 나는... 힉!... 안 취했어... 거의... 아마도...";
			link.l1 = "아, 그래, 맞아. 행운을 빌지.";
			link.l1.go = "NA_SailorShip_3";
		break;
		
		case "NA_SailorShip_3":
			dialog.text = "잠깐만요, 선장님! 저, 저를... 헉!.. 배에 데려가 주세요! 이제는... 헉!.. 술 안 마실게요...";
			if(GetFreeCrewQuantity(pchar) > 0)
			{
				link.l1 = "좋아, 어쩔 수 없지. 하지만 바로 배로 가. 그리고 어디서 술 취한 채로 걸리기만 해 봐, 다음 항구에 도착할 때까지 갑판이나 닦게 해줄 테니까.";
				link.l1.go = "NA_SailorShip_4";
			}
			link.l2 = "그래서 네가 내 임금으로 술이나 퍼마시고, 나는 식민지의 모든 선술집이랑 골목마다 널 찾아다녀야 한다고? 아니, 난 그런 행복 필요 없어.";
			link.l2.go = "NA_SailorShip_6";
			
		break; 
		
		case "NA_SailorShip_4": 
			AddCharacterCrew(pchar, 1);
			dialog.text = "네, 선장님!.. 힉!..";
			link.l1 = "...";
			link.l1.go = "NA_SailorShip_5";
		break;
		
		case "NA_SailorShip_5": 
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "NightAdventure_OpenLoc", 5.0); // побежит вдохновленный 
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NA_SailorShip_6": 
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorTurnToLocator(pchar, "reload", "reload4_back");
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "NightAdventure_OpenLoc", -1);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		// пьяные наезды
		case "NightAdventure_Bull":
			switch (rand(5))
			{
				case 0:
				dialog.text = "선장?.. 히끅!.. 너는... 땅쥐... 히끅!.. 선장이 아니야!..";
				link.l1 = "너 같은 놈은 백 명도 넘게 갑판 싸움에서 베어 넘겼으니, 꺼져라, 주정뱅이.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 1:
				dialog.text = "선장... 힉!.. 그 습격 때 그 물통의 선장인가?.. 힉!..";
				link.l1 = "바다에서 저 구유가 수평선에 보이면, 그냥 바로 물에 뛰어드는 게 나을 거다. 내 배랑 맞붙는 것보단 상어랑 싸우는 게 더 살아남을 확률이 높으니까. 이제 꺼져!";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 2:
				dialog.text = "선장?.. 힉!.. 너는 선장도 아니고 젖이나 마시는 놈이지!.. 네, 네 엄마는 아직 계집애였어... 힉!.. 내가 이미 바다를 누비고 다닐 때 말이야...";
				link.l1 = "하지만 네 어머니는 아마도 나 같은 어린 녀석이 선장이 되고, 너는 여전히 갑판이나 닦는 주정뱅이 뱃사람으로 남았다는 걸 알면 기뻐하시겠지.";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 3:
				dialog.text = "선장?.. 조심해... 헉!.. 선장... 네 이빨 다 부숴버릴 거야... 헉!.. 눈 깜빡일 틈도 없을 걸!..";
				link.l1 = "반동에 죽는다. 나가! 감히 내 이빨을 부숴봐라...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 4:
				dialog.text = "선장?.. 보니까... 히끅!.. 뭔가 거렁뱅이 같은데...";
				link.l1 = "아직 거울을 안 본 것 같은데...";
				link.l1.go = "NightAdventure_End";
				break;
				
				case 5:
				dialog.text = "선, 선장님?.. 나는... 히끅!.. 당신 배에서... 일하겠다고도... 히끅!.. 안 했을 거야...";
				link.l1 = "그리고 아무도 내 배에 타라고 초대하지 않았으니, 네가 동의할 이유도 없었지. 비켜.";
				link.l1.go = "NightAdventure_End";
				break;
			}
		break;
		
		case "NightAdventure_End":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_Again";
		break;
		
		case "NightAdventure_Again":
			NextDiag.TempNode = "NightAdventure_Again";
			dialog.text = "히끅!..";
			link.l1 = "자, 자라.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_SailorAgain":
			dialog.text = "히익!.. 그래... 아직 멀었냐?.. ";
			link.l1 = "거의 다 왔으니, 좀만 참아.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- матрос
		// горожанин -->
		case "NightAdventure_Citizen":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "누, 누구냐... 힉!.. 너 뭐야?..";
			link.l1 = "나는 선장이야 "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "미안하다, 친구야, 나 지금 급해.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_CitizenHomie":          link.l1.go = "NightAdventure_Citizen_1_1"; break; // выручить приятеля
				case "NightAdventure_CitizenHomieSolderNM":  link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_CitizenHomieSolderGM":  link.l1.go = "NightAdventure_Citizen_1_1"; break;
				case "NightAdventure_CitizenHomieOfficer":   link.l1.go = "NightAdventure_Citizen_1_1"; break; 
				case "NightAdventure_SailorShuler0":         link.l1.go = "NightAdventure_Sailor_2_1";  break; // шулер
				case "NightAdventure_SailorShulerGiveMoney": link.l1.go = "NightAdventure_Sailor_2_1";  break;
				case "NightAdventure_SailorShulerGiveOk":    link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_SailorShulerFight":     link.l1.go = "NightAdventure_Sailor_2_1";  break; 
				case "NightAdventure_Bull":                  link.l1.go = "NightAdventure_Bull";        break;// наезд
			}
		break;
		
		// дружок
		case "NightAdventure_Citizen_1_1":
			dialog.text = "선장?.. 힉!.. 선장... 도와줘! 나... 아니... 힉!.. 내 친구가... 정말로 네 도움이 필요해! 제발.";
			link.l1 = "나는 한밤중에 만나는 술주정뱅이들 문제까지 다 해결해 줄 생각 없어.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "좋아, 거기 있는 네 친구한테 무슨 일이 있었는지 말해 봐.";
			link.l2.go = "NightAdventure_Citizen_1_2";
		break;
		
		case "NightAdventure_Citizen_1_2":
			dialog.text = "내 친구가... 음, 그게 말이지... 그냥 취했어. 그냥... 딱히 이유 없이... 헉! ... 취해버렸어...";
			link.l1 = "물론이지, 근무 중에 술 마시던 선원들은 내가 아주 과격한 방법으로 정신 차리게 했지. 하지만 네 친구한테는 그럴 필요 없을 것 같아.";
			link.l1.go = "NightAdventure_Citizen_1_3";
		break;
		
		case "NightAdventure_Citizen_1_3":
			dialog.text = "아니! 그... 그 자는 경비대랑 있어! 그가... 그들과 말싸움을 했어. 그리고 싸움이 붙었지. 그리고 그는... 헉!.. 감옥에 끌려갔어... 그냥 취한 거야!";
			link.l1 = "이제 나한테 뭘 바라는 거야? 그 녀석 잘못이지. 술을 좀 덜 마시든가, 아니면 적어도 혼자 문제를 만들러 다니지 말았어야지...";
			link.l1.go = "NightAdventure_Citizen_1_4";
		break;
		
		case "NightAdventure_Citizen_1_4":
			dialog.text = "간수한테 말해 봐, 선장... 헉! .. 선장님! 그가 풀어줄 거야... 풀어줘! 흠... 여기 있네... 헉!.. 운이 좋구만... 내 친구가 방금... 싸웠어... 음... 그리고 내 얼굴에 한 방 먹이려고 했는데... 근데... 헉!.. 무기를 못 들었지...";
			link.l1 = "이제 밤마다 술주정뱅이들을 감옥에서 끌어내는 것 말고는 할 일이 없군, 그놈들이 간수랑 싸움이나 벌이고 말이야. 아니, 며칠은 그냥 거기 앉아 있게 둬. 다음번엔 두 번 생각하게 될지도 모르지.";
			link.l1.go = "NightAdventure_End";
			link.l2 = "그래, 엿이나 먹어라. 좋아, 감옥지기랑 얘기해볼게.";
			link.l2.go = "NightAdventure_Citizen_1_5";
			if(GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && !CheckNationLicence(HOLLAND))
			{
				link.l2 = "간수는 내 억양을 별로 안 좋아할 거야. 나중에 총독한테 그냥 일러바칠 테니까. 그러니 나 없이 가.";
				link.l2.go = "NightAdventure_Citizen_RE";
			}
			if(ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 0) <= -15)
			{
				link.l2 = "미안한데, 친구야, 나한텐 이 지역 감방으로 가는 길이 막혀 있어. 간수놈이 내 초상화를 성물처럼 모시고 있거든, 그래서 그놈들 호의 넘치는 감방에 눌러앉을 생각은 없어. 그러니 미안하지만, 도와줄 수 없겠어.";
				link.l2.go = "NightAdventure_Citizen_NR";
			}
		break;
		
		case "NightAdventure_Citizen_1_5":
			DialogExit();
			pchar.GenQuest.NightAdventureToJail = true;
			DeleteAttribute(pchar,"GenQuest.GenQuest.NightAdventure_money");
			chrDisableReloadToLocation = true; //закрыть локацию пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_CitizenHomiePresent":
			dialog.text = "고, 고맙습니다... 선장님. 제 친구도요. 여, 여기... 이거 받으세요.";
			link.l1 = "다음에는 네 친구가 술 취해서 경비병과 싸우겠다고 덤빌 때 잘 좀 챙겨라. 선장들이 거리를 돌아다니며 술주정뱅이들 때문에 감시인과 흥정하려고 나서는 일이 매일 밤 있는 건 아니거든. 행운을 빈다.";
			link.l1.go = "NightAdventure_CitizenHomiePresent_1";
		break;
		
		case "NightAdventure_CitizenHomiePresent_1":
			DialogExit();
			LAi_SetPlayerType(pchar);
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 5.0);
			sld = characterFromId("NightAdventure_Homie");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 5.0);
			if(GetDataDay() < 7) 						{GiveItem2Character(pchar, "indian_2");  Log_Info("You've received amulet 'Gunpowder tester'");}
			if(GetDataDay() >= 7  && GetDataDay() < 13) {GiveItem2Character(pchar, "obereg_5");  Log_Info("You've received amulet 'Jade turtle'");}
			if(GetDataDay() >= 13 && GetDataDay() < 19) {GiveItem2Character(pchar, "obereg_6");  Log_Info("You've received amulet 'Monkey's fist'");}
			if(GetDataDay() >= 19 && GetDataDay() < 25) {GiveItem2Character(pchar, "obereg_8");  Log_Info("You've received amulet 'Merchant's beads'");}
			if(GetDataDay() == 25) 		    			{GiveItem2Character(pchar, "indian_9");  Log_Info("You've received amulet 'Baldo'");}
			if(GetDataDay() == 26) 	    				{GiveItem2Character(pchar, "obereg_11"); Log_Info("You've received amulet 'Pilgrim'");}
			if(GetDataDay() >= 27 && GetDataDay() < 31) {GiveItem2Character(pchar, "obereg_4");  Log_Info("You've received amulet 'Gypsy's fan'");}
			if(GetDataDay() == 31) 	    				{GiveItem2Character(pchar, "amulet_11"); Log_Info("You've received amulet 'Cimaruta'");}
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_Citizen_RE":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE)  < (rand(100)+rand(100)))
			{
				dialog.text = "오!.. 그러니까 내가 어떻게... 헉!.. 내... 친구를... 풀어주는지 알아... 헉!.. 경비병들! 도시에 첩자가 있어!.. 헉!..";
				link.l1 = "네 친구를 구하려고 아주 형편없는 방법을 골랐군.";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "아, 이-이방인... 헉! .. 너... 너 문제 생길 거야... 헉! .. 좋아... 여기 내가... 헉! .. 다 통제하고 있어.";
				link.l1 = "물론이지. 무슨 일 생기면 바로 너한테 올게.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Citizen_NR":
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) + GetSummonSkillFromName(pchar, SKILL_FORTUNE) < (rand(100)+rand(100)))
			{
				dialog.text = "아... 그러니까 너... 히익! .. 너 범죄자구나! 경비병!";
				link.l1 = "아, 이제 그렇게 말하는 거냐!";
				link.l1.go = "NightAdventure_Fight";
			}
			else
			{
				AddCharacterExpToSkill(pchar, SKILL_SNEAK, 100);
				AddCharacterExpToSkill(pchar, SKILL_FORTUNE, 100);
				dialog.text = "오, 이게... 딸꾹! .. 미안해. 만약에... 내가 대신... 딸꾹! .. 간수랑 흥정해주고, 너는... 딸꾹! .. 내 친구를 위해서 해주면 어때?..";
				link.l1 = "아니, 나 대신 흥정할 필요 없어, 고마워. 행운을 빌어.";
				link.l1.go = "NightAdventure_End";
			}
		break;
		
		case "NightAdventure_Fight":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			LAi_group_Attack(NPChar, Pchar);
		break;
		// контрабандист 
		case "NightAdventure_Pirate": 
			LAi_RemoveLoginTime(npchar);
			dialog.text = "누, 누구냐... 히끅!.. 너 누구야?...";
			link.l1 = "나는 선장이야 "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "미안하다, 친구, 나 지금 급해.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_Bull":          		 link.l1.go = "NightAdventure_Bull";       break; // пьяные наезды
				case "NightAdventure_PiratePeace":           link.l1.go = "NightAdventure_PirateCave"; break; // до пещеры
				case "NightAdventure_PirateBad":             link.l1.go = "NightAdventure_PirateCave"; break;
			}
		break;
		
		case "NightAdventure_PirateCave":
			dialog.text = "선장?.. 히끅!.. 선장... 저기, 도시 근처 동굴까지 좀 데려다줘... 히끅!.. 응? 제발.";
			link.l1 = "동굴로 간다고? 이해가 안 돼. 왜 동굴에 가는 거지? 그리고 왜 내가 필요한 거야?";
			link.l1.go = "NightAdventure_PirateCave_1";
		break;
		
		case "NightAdventure_PirateCave_1":
			dialog.text = "저기 있잖아... 선장님... 헉!.. 술 마실 돈이 다 떨어졌어... 그리고... 헉!.. 동굴에... 내가 숨겨둔 게 있어, 그러니까... 헉!.. 근데 나... 그게... 혼자서 그... 그... 정글을... 헉!.. 밤에 가기 무서워서... 그래서...";
			link.l1 = "비켜, 나 지금 바빠!";
			link.l1.go = "NightAdventure_End";
			link.l2 = "좋아, 가자. 너 혼자서는 거기 못 갈 것 같으니까\n";
			link.l2.go = "NightAdventure_PirateCave_2";
		break;
		
		case "NightAdventure_PirateCave_2":
			dialog.text = "그냥... 헉!.. 천천히, 제발. 나... 헉!.. 더는... 못 버티겠어...";
			link.l1 = "좋아, 천천히 가자.";
			link.l1.go = "NightAdventure_PirateCave_3";
		break;
		
		case "NightAdventure_PirateCave_3":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_SailorAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode = true; // что взяли квест
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			string NAIsland = GetIslandByCityName(npchar.city);
			string NACave = "absent. Tell belamour that you are";
			// найти пещеру на острове
			i = Findlocation(NAIsland+"_Grot");
			if(i != -1) NACave = NAIsland+"_Grot";
			i = Findlocation(NAIsland+"_Cave");
			if(i != -1) NACave = NAIsland+"_Cave";
			// для мейна и капстервиля
			i = Findlocation(npchar.city+"_Cave");
			if(i != -1) NACave = npchar.city+"_Cave";
			i = Findlocation(npchar.city+"_Grot");
			if(i != -1) NACave = npchar.city+"_Grot";
			
			log_testinfo("Cave "+NACave+" on the island " +NAIsland);
			SetFunctionLocationCondition("NightAdventure_InCave", NACave, false);
			SetFunctionLocationCondition("NightAdventure_InFort", npchar.city+"_ammo", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_PirateCave_4": // диалог в пищере
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PiratePeace")
			{
				AddMoneyToCharacter(pchar, 1000);
				TakeNItems(pchar, "potionrum", 1);   
				TakeNItems(pchar, "potionwine", 1);
				PlaySound("interface\important_item.wav");
				Log_Info("You've received an alcohol")
				dialog.text = "선장님... 히끅!.. 정말 고마워요... 덕분에 살았어요! 나... 자, 여기요... 히끅!.. 이거 받아요.";
				link.l1 = "어서, 으... 됐다... 이제 그렇게 마시지 마.";
				link.l1.go = "NightAdventure_PirateCave_4_1";
				break;
			} 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_PirateBad")
			{
				dialog.text = "훌륭해요, 선장님! 동의해 주셔서 기쁩니다.";
				link.l1 = "그래, 네 숨겨둔 물건은 어디 있지? 잠깐만, 너 취한 것 같지 않은데.";
				link.l1.go = "NightAdventure_PirateCave_5";
				break;
			} 
		break;
		
		case "NightAdventure_PirateCave_4_1": // мирный исход
			DialogExit();
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 5.0); 
			SetFunctionTimerCondition("NightAdventure_KillPhant", 0, 0, 0, false);
		break;
		
		case "NightAdventure_PirateCave_5": // драка
			dialog.text = "그래, 나 많이 안 마셨어. 걱정하지 마. 그리고 그 은닉물 말인데... 이봐, 녀석들!";
			link.l1 = "...";
			link.l1.go = "NightAdventure_PirateCave_6";
		break;
		
		case "NightAdventure_PirateCave_6": 
			DialogExit();
			AddDialogExitQuestFunction("NightAdventure_PiratesInCave");
		break;
		
		case "NightAdventure_PirateCave_7": 
			dialog.text = "이봐, 여기 내가 숨겨둔 물건을 가져왔어. 니들이 이걸 열어야 해. 물론, 이 보물이 알아서 잘 열려주면 더 좋겠지만 말이야. 선장, 어떻게 생각해?";
			link.l1 = LinkRandPhrase("차라리 술에 취해 기억을 잃는 게 더 나을 것 같군. 적어도 살아는 있을 테니까. 이제 남은 길은 단 하나뿐이야... "," 네가 전함 선장을 털기로 한 걸 보니, 머리가 썩 좋은 것 같진 않군 ... "," 이걸 시도하다니, 네 목숨이 아까운 줄 모르는 모양이군...");
			link.l1.go = "NightAdventure_PirateCave_8F";
			link.l2 = "좋아, 원만하게 끝내는 게 낫겠지. 그런데 얼마나 필요하지?";
			link.l2.go = "NightAdventure_PirateCave_8A";
		break;
		
		case "NightAdventure_PirateCave_8F": 
			dialog.text = "그래서, 우리는 쉽게 은닉처를 열지는 않는 거야?";
			link.l1 = "네 목숨의 마지막 은닉처였던 것 같군.";
			link.l1.go = "NightAdventure_PirateCave_9F";
		break;
		
		case "NightAdventure_PirateCave_9F": 
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			sld = CharacterFromID(pchar.GenQuest.NightAdventureId);
			sld.SaveItemsForDead   = true; // сохранять на трупе вещи
			sld.DontClearDead = true;  // не убирать труп через 200с
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
			LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
			LAi_SetFightMode(pchar, true);
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
		break;
		
		case "NightAdventure_PirateCave_8A": // испугался
			iMoney = sti(pchar.money)/3;
			dialog.text = "오, 우리는 욕심쟁이가 아니야. 그냥\n "+FindRussianMoneyString(iMoney)+"."; 
			link.l1 = "네 목숨의 마지막 은닉처였던 것 같군.";
			link.l1.go = "NightAdventure_PirateCave_9F";
			link.l2 = "좋아, 네 마음대로 해. 다시는 술 취한 놈은 도와주지 않겠다...";
			link.l2.go = "NightAdventure_PirateCave_9A";
		break;
		
		case "NightAdventure_PirateCave_9A": 
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_PirateCaveAgain";
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false); 
			iMoney = sti(pchar.money)/3;
			AddMoneyToCharacter(pchar, -iMoney);
			AddMoneyToCharacter(npchar, iMoney);
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			for(i=0 ; i < 3; i++)
			{
				sld = CharacterFromID("NAPirat_" + i);
				sld.dialog.currentnode = "NightAdventure_PirateCaveAgain";
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			LAi_Group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_NEITRAL);
		break;
		
		case "NightAdventure_PirateCaveAgain": 
			dialog.text = "선장님, 당신의 관대함에 놀랐소. 우리에게 더 나눠주실 생각은 없으시오?";
			link.l1 = "이미 너한테 다 줬어. 난 간다...";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_PirateCaveAgain";
		break;
		
		// дворянин -->
		case "NightAdventure_Noble":
			LAi_RemoveLoginTime(npchar);
			dialog.text = "누, 누구냐... 힉!.. 너 누구야?…";
			link.l1 = "나는 선장이야 "+GetFullName(pchar)+".";
			if (pchar.id == "Knippel")
			{
				link.l1 = "미안하다, 친구, 나 지금 급해.";
				link.l1.go = "exit";
				LAi_CharacterDisableDialog(npchar);
				break;
			}
			switch(pchar.GenQuest.NightAdventureVar)
			{
				case "NightAdventure_NobleGame":             link.l1.go = "NightAdventure_NobleGame";  break; // карты
				case "NightAdventure_NobleGameDuel":         link.l1.go = "NightAdventure_NobleGame";  break; 
				case "NightAdventure_NobleWhore": 			 link.l1.go = "NightAdventure_NobleWhore"; break; // жрица
			}
		break;
		// карты
		case "NightAdventure_NobleGame": 
			dialog.text = "선장?.. 힉!.. 오, "+GetAddress_Form(NPChar)+" ... 미, 미안해... 히끅!.. 내... 상태 때문에. 나랑 한잔 할래? 히끅!.. 부, 부탁이야."; 
			link.l1 = "미안하다, "+GetAddress_Form(NPChar)+", 하지만 나 바빠."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "합류하라고? 미안한데, 오늘은 술 안 마실 거야.."; 
			link.l2.go = "NightAdventure_NobleGame_1";
		break;
		
		case "NightAdventure_NobleGame_1":
			dialog.text = "오, 너는... 힉!.. 마실 필요 없어! 그게 말이지... 음... 친구랑 한잔 했거든... 그래서... 이미 취했어... 알겠지?";
			link.l1 = "좋아. 그래서, 정신 좀 차리게 도와줄까?";
			link.l1.go = "NightAdventure_NobleGame_2";
		break;
		
		case "NightAdventure_NobleGame_2": 
			dialog.text = "별로 아니야! 난 괜찮아. 이제 나, 놀고 싶어... 카드, 아무튼 놀고 싶어... 헉!.. 그치만 이런 한심한... 페소로는... 이런 누더기 놈들이랑은... 헉!.. 주점에서... 안 해... 진짜 신사랑 하고 싶어! 헉!.. 제대로 판돈 걸고!.."; 
			link.l1 = "미안하다, "+GetAddress_Form(NPChar)+", 뭐라고 해야 할까... 난 도박을 별로 안 좋아해. 선원들 월급도 줘야 하고, 배도 관리해야 하잖아..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "흠, 좋아, 한 판 하자. 선술집에 갈까?"; 
			link.l2.go = "NightAdventure_NobleGame_3";
		break;
		
		case "NightAdventure_NobleGame_3": 
			dialog.text = "좋아! 그냥... 헉!.. 천천히, 부-탁이야. 나... 헉!.. 제대로... 설 수가... 없어..."; 
			link.l1 = "좋아, 천천히 가자."; 
			link.l1.go = "NightAdventure_NobleGame_4";
		break;
		
		case "NightAdventure_NobleGame_4":
			DialogExit();
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleGame_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_Intavern", npchar.City+"_tavern", true);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleGame_5": 
			pchar.quest.NightAdventure_Intavern.over = "yes";
			FreeSitLocator(pchar.location, "sit_front4");
			FreeSitLocator(pchar.location, "sit_base4");
			dialog.text = "그 테이블로... 히익!.. 가자!"; 
			link.l1 = "좋아, 가자."; 
			link.l1.go = "NightAdventure_NobleGame_6";
		break;
		
		case "NightAdventure_NobleGame_6": 
			DialogExit();
			//if(CheckAttribute(pchar, "IsMushketer")) SetMainCharacterToMushketer("", false);
			LAi_Fade("NightAdventure_NobleGameDialogPrep", "NightAdventure_NobleGameDialog");
		break;
		
		case "NightAdventure_NobleGame_7": 
			dialog.text = "너는 모를 거야... 선장님, 내가 얼마나... 헉! 진짜 귀족을 만나서 얼마나 기쁜지! 헉!.. 이 황야에는... 보통은... 헉!.. 쓰레기들만..."; 
			link.l1 = "그래, 이 근처 식민지에선 흔하디흔한 거지. 자, 한 판 할까?"; 
			link.l1.go = "NightAdventure_NobleGame_8";
		break;
		
		case "NightAdventure_NobleGame_8": 
			dialog.text = "그래, 한 판 하자! 힉!.. 뭐 걸 건데?.."; 
			if(sti(pchar.money) > 10000)
			{
				link.l1 = "우린 1000페소를 걸고 게임하는 거야."; 
				link.l1.go = "NightAdventure_NobleGame_9_1";
			}
			if(sti(pchar.money) > 20000)
			{
				link.l2 = "우리는 2,000페소를 걸고 게임하는 거야."; 
				link.l2.go = "NightAdventure_NobleGame_9_2";
			}
			link.l3 = "흠, 미안한데, 지금 내 주머니가 비어 있는 것 같아..."; 
			link.l3.go = "NightAdventure_NobleGame_Голодранец";
		break;
		
		case "NightAdventure_NobleGame_Голодранец": 
			dialog.text = "뭐, 뭐라고?.. 너... 히익!.. 나랑 놀 돈이... 없어?.."; 
			link.l1 = "뭐, 그럴 수도 있지. 다음에 또 한 판 하자, 걱정 마."; 
			link.l1.go = "NightAdventure_NobleGame_Голодранец_1";
		break;
		
		case "NightAdventure_NobleGame_Голодранец_1": 
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_9_1": 
			DialogExit();
			npchar.money = 15000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 1000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_9_2": 
			DialogExit();
			npchar.money = 30000;
			pchar.questTemp.NA.Cards = true; 
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate     = 2000; 
			LaunchCardsGame();
		break;
		
		case "NightAdventure_NobleGame_Win": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Win");
			dialog.text = "히익!.. 정말 재밌었어, 선장! 히익!.."; 
			link.l1 = "나도 동의해. 적어도 일은 잠시 쉬어가."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd";
		break;
		
		case "NightAdventure_NobleGame_Lose": 
			DeleteAttribute(pchar, "questTemp.NA.Cards.Fail");
			dialog.text = "히익!.. 재밌었어, 선장! 히익!.."; 
			link.l1 = "나도 동의해. 적어도 일은 잠시 쉬어가자."; 
			link.l1.go = "NightAdventure_NobleGame_Lose_1";
		break;
		
		case "NightAdventure_NobleGame_Lose_1": 
			dialog.text = "가끔은 그냥... 헉!.. 누군가랑... 헉!.. 좋은 시간을 보내야 할 때가 있지. 정말 고마워... 헉!.. 같이 있어줘서!"; 
			if(pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleGameDuel")
			{		
				link.l1 = "그래, 방금 산산조각이 났지. 그런데 내가 이길 만한 모든 상황에서도 네가 어떻게 이겼던 거냐?"; 
				link.l1.go = "NightAdventure_NobleGame_Duel";
				break;
			}	
			link.l1 = "마찬가지로, 게임과 대화에 감사드립니다."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd": 
			dialog.text = "가끔은 그냥... 헉!.. 좋은... 헉!.. 사람들과 시간을 보내야 해. 정말 고마워... 헉!.. 함께해 줘서!"; 
			link.l1 = "마찬가지로, 게임과 대화에 감사드립니다."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
		break;
		
		case "NightAdventure_NobleGame_HappyEnd_1":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			chrDisableReloadToLocation = false; // открыть локацию
			LAI_SetPlayerType(pchar);           
			DoQuestReloadToLocation(pchar.location, "tables", "stay4", "");
			ChangeCharacterAddressGroup(npchar, "none", "", "");
		break;
		
		case "NightAdventure_NobleGame_Duel": 
			dialog.text = "그냥 운이었어, 선장님... 힉!.."; 
			link.l1 = "그냥 운만은 아닌 것 같은데...."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_1";
		break;
		
		case "NightAdventure_NobleGame_Duel_1": 
			dialog.text = "무슨 뜻이야? 내가 부정하게 했다는 거야? 너도 다 봤잖아, 우리 같은 덱에서 카드를 뽑았다고!"; 
			link.l1 = "그래, 봤어. 그리고 방금 전까지만 해도 네 혀가 제대로 안 움직이더니, 지금은 술 안 마신 사람처럼 말 잘하네."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_2";
		break;
		
		case "NightAdventure_NobleGame_Duel_2": 
			dialog.text = "아, 젠장! 제대로 걸렸군! 좋아, 인정하지, 숨기지 않을게. 나 취한 거 아니었어. 하지만 알기나 해? 사람들이 얼마나 쉽게 속는지, 부자인 척 술 취한 놈들이 카드나 한 판 하자고 하면 말이야. 내기할 게 있는 놈들은 거의 다 제일 먼저 선술집으로 달려가, 틀림없이 부자지만 술에 취한 귀족한테 한몫 챙길 수 있을까 싶어서 말이지. 그런데 말이야, 내 속을 이렇게 꿰뚫어본 건 네가 처음이야."; 
			link.l1 = "그래서, 이제 어쩔 거야? 순순히 내 돈 돌려줄래?"; 
			link.l1.go = "NightAdventure_NobleGame_Duel_3";
		break;
		
		case "NightAdventure_NobleGame_Duel_3": 
			dialog.text = "하하하, 웃기지 마라, 선장. 당연히 환불 따위는 안 해준다! 그리고 나한테 억지 부릴 생각도 하지 마. 나는 언제든지 존경받는 귀족이 떠돌이 선장한테 모욕당했다고 연기할 수 있거든. 그러니 내 충고는 이거다: 패배를 인정하고 그냥 꺼져라."; 
			link.l1 = "글쎄, 다음에 운이 나빠서 내 손에 잡히는 일이 없길 진심으로 바란다. 그땐 지금처럼 웃지 못할 테니까. 잘 가라."; 
			link.l1.go = "NightAdventure_NobleGame_HappyEnd_1";
			link.l2 = "그리고 내 조언 하나 하자면, 시간 내서 칼 하나 장만해 둬라."; 
			link.l2.go = "NightAdventure_NobleGame_Duel_4";
		break;
		
		case "NightAdventure_NobleGame_Duel_4": 
			dialog.text = "감히 그럴 리가... 여긴 선술집이야, 사람들로 가득하다고..."; 
			link.l1 = "그래서 나는 그냥 떠돌이 선장일 뿐인데, 예의 따위 신경 쓸 이유가 있나? 밤에 항구 선술집에서 무슨 일이 일어나겠어... 나는 칼 다루는 솜씨가 너보다 훨씬 낫지."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_5";
		break;
		
		case "NightAdventure_NobleGame_Duel_5": 
			dialog.text = "아, 그래서 그런 거였군?! 이제 누가 진짜 주인인지 보자고!"; 
			link.l1 = "명령만 내리십시오..."; 
			link.l1.go = "NightAdventure_NobleGame_Duel_6";
		break;
		
		case "NightAdventure_NobleGame_Duel_6": 
			DeleteAttribute(pchar, "questTemp.NA.Cards");
			SetFunctionLocationCondition("NightAdventure_KillPhant", NPChar.City+"_town", false);
			npchar.money = 0;
			AddMoneyToCharacter(npchar, makeint(pchar.GenQuest.NightAdventure_money));
			GiveItem2Character(npchar, "totem_13");
			npchar.SaveItemsForDead   = true; // сохранять на трупе вещи
			npchar.DontClearDead = true;  // не убирать труп через 200с
			chrDisableReloadToLocation = false; // открыть локацию
			PChar.questTemp.duel.enemy = NPChar.id;
			AddDialogExitQuestFunction("Duel_Prepare_Fight");
			DialogExit();
		break;
		// жрица
		case "NightAdventure_NobleWhore": 
			dialog.text = "선장?.. 힉!.. 오, "+GetAddress_Form(NPChar)+" ... 미, 미안해... 히끅!.. 내 이, 이 꼴 때문에. 나 좀 도와줄 수 있겠어? 히끅!.. 제, 제발."; 
			link.l1 = "미안하다, "+GetAddress_Form(NPChar)+", 하지만 나 바빠."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "오... 듣고 있어."; 
			link.l2.go = "NightAdventure_NobleWhore_1";
		break;
		
		case "NightAdventure_NobleWhore_1": 
			dialog.text = "그게 말이지... 음... 나 벌써 좀 취했거든... 보이잖아... 딸꾹!.. 그렇지?"; 
			link.l1 = "솔직히 말해서, 그래. 술 좀 깨는 데 도움이 필요해?"; 
			link.l1.go = "NightAdventure_NobleWhore_2";
		break;
		
		case "NightAdventure_NobleWhore_2": 
			dialog.text = "별로 아니야! 나 괜찮아. 여자 좀 원해. 근데 너무 취했어... 딸꾹!.. 마담이 나 쫓아낼 거야, 그래서. 혹시... 딸꾹!... 나 대신 좀 흥정해줄 수 있어? 돈 줄게."; 
			link.l1 = "미안해, "+GetAddress_Form(NPChar)+", 하지만 어떻게 말해야 할지... 난 창관엔 안 가. 명예, 평판... 알잖아 ..."; 
			link.l1.go = "NightAdventure_NobleEnd";
			link.l2 = "아, 알겠어, 도와줄게."; 
			link.l2.go = "NightAdventure_NobleWhore_3";
		break;
		
		case "NightAdventure_NobleWhore_3": 
			dialog.text = "그냥... 헉!.. 천천히, 제발. 나... 헉!.. 못... 버티겠어..."; 
			link.l1 = "좋아, 천천히 가자."; 
			link.l1.go = "NightAdventure_NobleWhore_4";
		break;
		
		case "NightAdventure_NobleWhore_4":
			DialogExit();
			if(npchar.city != "Charles" || npchar.city != "Tortuga") // вход только с парадного
			{
				LocatorReloadEnterDisable(npchar.city+"_town", "reload91", true);
			}
			NPChar.Dialog.currentnode = "NightAdventure_NobleTownAgain"; 
			pchar.GenQuest.CantRun = true; // ме-е-едленно ))
			bDisableFastReload = true; // ножками
			LAi_SetActorType(pchar);
			LAi_SetPlayerType(pchar); // обновить для ходьбы
			pchar.GenQuest.NightAdventure_money = 3000+(rand(4)*500);
			pchar.GenQuest.NightAdventureNode =  "NightAdventure_NobleWhore_5"; // для выбора диалога
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
			SetFunctionLocationCondition("NightAdventure_InBrothel", npchar.City+"_Brothel", false);
			SetFunctionLocationCondition("NightAdventure_JungleExit", npchar.City+"_Exittown", false);
			pchar.quest.NightAdventure_SeaExit.win_condition.l1 = "EnterToSea";
			pchar.quest.NightAdventure_SeaExit.function = "NightAdventure_SeaExit";
		break;
		
		case "NightAdventure_NobleWhore_5": 
			pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhoreMoney";
			AddMoneyToCharacter(pchar, 5000);
			dialog.text = "여기 돈이야... 헉!... 나 여기서 기다릴게."; 
			link.l1 = "좋아, 곧 돌아올게."; 
			link.l1.go = "NightAdventure_NobleWhore_6";
		break;
		
		case "NightAdventure_NobleWhore_6": 
			LAi_SetCitizenType(npchar);
			chrDisableReloadToLocation = false;
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload1_back", true); 
			LocatorReloadEnterDisable(npchar.city + "_SecBrRoom", "reload2", true); 
			NPChar.Dialog.currentnode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "그, 그냥... 나한테... 히끅!.. 제일 좋은 거... 가져와!.. 그래..."; 
			link.l1 = "알았어, 좋아, 이해했어."; 
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleWhore_7": // заказ исполнен
			dialog.text = "히익!.. 얼마나 더 기다려야 해?"; 
			link.l1 = "이 식민지에서 제일 예쁜 아가씨가 위층에서 널 기다리고 있어."; 
			link.l1.go = "NightAdventure_NobleWhore_8";
		break;
		
		case "NightAdventure_NobleWhore_8": 
			dialog.text = "그래!.. 오늘 저녁... 정말 멋지다... 고, 고마워, "+GetAddress_Form(NPChar)+". 남은 돈은... 헉!... 가져가. 그리고 나는... 가라앉아... 내... 아름다운... 아-가씨 품에...";
			link.l1 = "그래, 잘 놀아."; 
			link.l1.go = "NightAdventure_NobleWhore_9";
		break;
		
		case "NightAdventure_NobleWhore_9": 
			DialogExit();
			chrDisableReloadToLocation = true; // закрыть пока бежит
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "", "", "", "NightAdventure_OpenBrothel", -1);
		break;
		
		case "NightAdventure_NobleBrothelAgain":
			NextDiag.TempNode = "NightAdventure_NobleBrothelAgain";
			dialog.text = "히익!.. 얼마나 더 기다려야 해?";
			link.l1 = "곧 협상할 테니, 좀 참아.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleEnd":
			DialogExit();
			SetFunctionExitFromLocationCondition("NightAdventure_KillPhant", pchar.location, false);
			NPChar.Dialog.currentnode = "NightAdventure_NobleEndAgain";
		break;
		
		case "NightAdventure_NobleEndAgain":
			NextDiag.TempNode = "NightAdventure_NobleEndAgain";
			dialog.text = "힉!..";
			link.l1 = "자네, 잠 좀 자야겠어.";
			link.l1.go = "exit";
		break;
		
		case "NightAdventure_NobleTownAgain":
			dialog.text = "히익!.. 그래... 아직 멀었냐?..";
			link.l1 = "거의 다 왔으니, 좀만 참아.";
			link.l1.go = "exit";
			NextDiag.TempNode = "NightAdventure_SailorAgain";
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_Actor2WaitDialog(npchar, pchar);
		break;
		// <-- ночной приключенец
		
		// belamour квест на получение фонаря Xenon -->
		case "CemeteryMan":
			dialog.text = "어? 너 누구야? 여기서 뭐 하는 거야?";
			link.l1 = "나도 너한테 똑같이 물을 수 있지.";
			link.l1.go = "CemeteryMan_1";
		break;
		
		case "CemeteryMan_1":
			dialog.text = "우리? 아, 우리는... 음... 여기서 꽃을 모으고 있어...";
			link.l1 = "무덤 꽃이라고? 그래, 네 허브 모으기는 잘 되고 있냐?";
			link.l1.go = "CemeteryMan_2";
		break;
		
		case "CemeteryMan_2":
			dialog.text = "그 여자... 약초랑 관련 있나?";
			link.l1 = "그래... 이제 여기서 무슨 일이 벌어지고 있는지 알 것 같군.";
			link.l1.go = "CemeteryMan_3";
		break;
		
		case "CemeteryMan_3":
			dialog.text = "우린 약탈자가 아니야! 우리를 그렇게 말하지 마! 우린 그냥...";
			link.l1 = "뭐가 어쨌다고?";
			link.l1.go = "CemeteryMan_4";
		break;
		
		case "CemeteryMan_4":
			dialog.text = "음, 우리... 우리 아버지가 서로 만나는 걸 금지했어! 그녀 아버지도 마찬가지고! 그래서 우리... 우리 둘만 있을 수 있는, 아무도 없는 곳을 찾고 있었어. 어차피 이 방 문 자물쇠도 고장 나서 들어오기도 쉽고...\n";
			link.l1 = "이제야 그 불안한 영혼의 으스스한 신음 소리가 무엇이었는지 알겠군...";
			link.l1.go = "CemeteryMan_5";
		break;
		
		case "CemeteryMan_5":
			DialogExit();
			sld = characterFromId("CemeteryCouple_2");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		
		case "CemeteryMan_6":
			dialog.text = "그래, 다 알아냈으면 이제 우리 좀 내버려 두지 않을래?";
			link.l1 = "무덤에서 데이트를 잡는 게 두렵지 않아? 썩 좋은 장소는 아닌데...";
			link.l1.go = "CemeteryMan_7";
		break;
		
		case "CemeteryMan_7":
			dialog.text = "우린 미신 같은 거 안 믿어! 그리고 무섭다 해도, 우리가 무슨 선택이 있겠어? 도시에서는 부모님이 바로 알았을 거야. 하지만 여기선 아무도 우리 일 고자질 안 해. 그러니까 지금은 이게 최선이야.";
			link.l1 = "정말 미안한데, 다른 곳을 찾아줄 수 있겠나? 오해하지 말게, 다 이해하지. 젊음이란 게 그런 거니까. 하지만 자네들의 데이트 때문에 매일 밤 지하실에서 들려오는 소리와 신음에 묘지 관리인이 혼비백산했네.";
			link.l1.go = "CemeteryMan_8";
		break;
		
		case "CemeteryMan_8":
			dialog.text = "음... 경비병을 겁주는 건 우리 계획에 없었지. 하지만, 그럼 어디서 만나라는 거야? 아니면 그냥 하늘 아래서 데이트하자고?";
			link.l1 = "사랑에는 경계가 없지. 아무도 방해하지 않을 만한 다른 곳을 찾아봐. 그러면 아무도 너희를 방해하지 않을 거야. 아마도. 그리고 부모님과도 확실히 정리하는 게 좋아 – 영원히 숨어 지낼 생각은 아니잖아?";
			link.l1.go = "CemeteryMan_9";
		break;
		
		case "CemeteryMan_9":
			dialog.text = "좋아, 뭔가 방법을 생각해 볼게... 더 이상 경비병을 겁주지 않겠어; 내 약속이야.";
			link.l1 = "훌륭하군. 행운을 빌어!";
			link.l1.go = "CemeteryMan_10";
		break;
		
		case "CemeteryMan_10":
			sld = characterFromId("CemeteryCouple_1");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld = characterFromId("CemeteryCouple_2");
			sld.lifeDay = 0;
			ChangeCharacterAddressGroup(sld, "none", "", "");
			pchar.questTemp.Lantern = "ToKeeper";
			DeleteAttribute(pchar,"questTemp.Lantern.nation");
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			AddQuestRecord("NoiseCemetery", "2");
			DialogExit();
		break;
		
		case "CemeteryGirl":
			dialog.text = "뭐라고?!";
			link.l1 = "아, 아무것도 아니야...";
			link.l1.go = "CemeteryGirl_1";
		break;
		
		case "CemeteryGirl_1":
			DialogExit();
			sld = characterFromId("CemeteryCouple_1");
			sld.dialog.currentnode = "CemeteryMan_6";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.3);
		break;
		// <-- квест на получение фонаря 

		//замечание по обнажённому оружию от персонажей типа citizen // лесник вставил в ген.квесты чтобы не было пустого диалога .
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"이봐, 나는 이 도시 시민이야. 그러니 칼 좀 내려줘.","이봐, 나는 이 도시 시민이야. 그러니 칼 좀 내려줘.");
			link.l1 = LinkRandPhrase("좋아.","원하시는 대로...","말씀대로...");
			link.l1.go = "exit";
		break;																																																				  
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			break;
	}
}

void ChurchGenQuest2_GiveCup()
{
	AddItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	rItem.Name = "itmname_ChurchGenQuest2Cup"; // rItem.Name = "itmname_bible";
	rItem.City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_2.QuestTown + "Gen");
	rItem.Weight = 15.0; // rItem.Weight = 2;
	rItem.picIndex = 13; // itm.picIndex = 6;
	rItem.picTexture = "ITEMS_31"; // itm.picTexture = "ITEMS_9";
	ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest2Cup");
}

// Для генера "Пираты на необитаемом острове"
String PiratesOnUninhabited_GetStringNum(int _num)
{
	String retValue = "";
	
	switch(_num)
	{
		case 5: retValue = "five"; break;
		case 6: retValue = "six"; break;
		case 7: retValue = "seven"; break;
		case 8: retValue = "eight"; break;
		case 9: retValue = "nine"; break;
		case 10: retValue = "ten"; break;
	}
	
	return retValue;
}

int PiratesOnUninhabited_GenerateShipType()
{
	int rank = sti(PChar.rank);
	int retShipType;
	
	if(rank < 5)
	{
		switch(hrand(1))
		{
			case 0: retShipType = SHIP_LUGGER; break;
			case 1: retShipType = SHIP_SLOOP; break;
		}
	}
	
	if(rank >= 5 && rank < 20)
	{
		switch(hrand(3))
		{
			case 0: retShipType = SHIP_SLOOP; break;
			case 1: retShipType = SHIP_BRIGANTINE; break;
			case 2: retShipType = SHIP_SCHOONER_W; break;
			case 3: retShipType = SHIP_BRIG; break;
		}
	}
	
	if(rank >= 20)
	{
		switch(hrand(2))
		{
			case 0: retShipType = SHIP_CORVETTE; break;
			case 1: retShipType = SHIP_GALEON_H; break;
			case 2: retShipType = SHIP_FRIGATE; break;
		}
	}
	
	return retShipType;
}

String PiratesOnUninhabited_GenerateTreasureShore(ref _boxId)
{
	String retShoreId;
	
	switch(hrand(4))
	{
		case 0:
			retShoreId = "Shore9";
			_boxId = "box1";
		break;
		
		case 1:
			retShoreId = "Shore55";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	
		case 2:
			retShoreId = "Shore_ship1";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 3:
			retShoreId = "Shore_ship2";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
		
		case 4:
			retShoreId = "Shore_ship3";
			_boxId = "box" + (1 + rand(1)); // Сундук пусть рандомится и при с/л
		break;
	}
	
	return retShoreId;
}

void PiratesOnUninhabited_SetCapToMap()
{
	int temp;
	String group = "PiratesOnUninhabited_SeaGroup";
	ref character = GetCharacter(NPC_GenerateCharacter("PiratesOnUninhabited_BadPirate", "", "man", "man", sti(pchar.rank) + 5, PIRATE, -1, true, "soldier"));		
	character.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType), true, character);
	character.Ship.Name = PChar.GenQuest.PiratesOnUninhabited.StartShipName;
    SetBaseShipData(character);
    SetCrewQuantityFull(character);
    Fantom_SetCannons(character, "pirate");
    Fantom_SetBalls(character, "pirate");
	Fantom_SetUpgrade(character, "pirate");
	
	character.Ship.Mode = "pirate";	
	SetCaptanModelByEncType(character, "pirate");

	DeleteAttribute(character, "SinkTenPercent");
	DeleteAttribute(character, "SaveItemsForDead");
	DeleteAttribute(character, "DontClearDead");
	DeleteAttribute(character, "AboardToFinalDeck");
	DeleteAttribute(character, "SinkTenPercent");
	
	character.AlwaysSandbankManeuver = true;
	character.AnalizeShips = true;  //анализировать вражеские корабли при выборе таска
	character.DontRansackCaptain = true; //не сдаваться
	
	SetAllPerksToChar(character, false);
	
	Group_FindOrCreateGroup(group);
	Group_SetTaskAttackInMap(group, PLAYER_GROUP);
	Group_LockTask(group);
	Group_AddCharacter(group, character.id);
	Group_SetGroupCommander(group, character.id);
	SetRandGeraldSail(character, PIRATE);
	
	character.fromCity = SelectAnyColony(""); // Колония, из бухты которой выйдет
	character.fromShore = GetIslandRandomShoreId(GetArealByCityName(character.fromCity));
	character.toCity = SelectAnyColony(character.fromCity); // Колония, в бухту которой придёт
	character.toShore = GetIslandRandomShoreId(GetArealByCityName(character.toCity));
	
	character.mapEnc.type = "trade";
	character.mapEnc.worldMapShip = "quest_ship";
	character.mapEnc.Name = LowerFirst(XI_ConvertString(ShipsTypes[sti(PChar.GenQuest.PiratesOnUninhabited.StartShipType)].name)) + " '" + PChar.GenQuest.PiratesOnUninhabited.StartShipName + "'";
	
	Map_CreateTrader(character.fromShore, character.toShore, "PiratesOnUninhabited_BadPirate", GetMaxDaysFromIsland2Island(GetArealByCityName(character.toCity), GetArealByCityName(character.fromCity)) + 3);
	
	temp = GetCharacterFreeSpace(character, GOOD_SLAVES); // Сколько влезет рабов
	AddCharacterGoodsSimple(character, GOOD_SLAVES, makeint(temp / 2 + hrand(temp / 2)) - 1);
	
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1 = "Character_sink";
	PChar.Quest.PiratesOnUninhabited_ShipSink.win_condition.l1.character = "PiratesOnUninhabited_BadPirate";
	PChar.Quest.PiratesOnUninhabited_ShipSink.function = "PiratesOnUninhabited_ShipSink";
	
	Log_TestInfo("Pirates on an uninhabited island: cap left " + character.fromCity + " and went to: " + character.toShore);
}
// belamour gen количество каторжан прописью -->
String Convict_GetStringNum(int iCQTY)
{
	String ConvictStr = "";
	
	switch(iCQTY)
	{
		case 2: ConvictStr = "two"; break;
		case 3: ConvictStr = "three"; break;
		case 4: ConvictStr = "four"; break;
		case 5: ConvictStr = "five"; break;
		case 6: ConvictStr = "six"; break;
		case 7: ConvictStr = "seven"; break;
	}
	
	return ConvictStr;
}
// <-- gen
